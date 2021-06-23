
#include "SimpleAgent/SimpleAgent.h"
#include "device/RaspberryPi.h"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <dirent.h>


// The interval between iterations in the run_agent() function
#define SLEEP_TIME 1

using namespace std;
using namespace artemis;

//! The agent object which allows for communication with COSMOS
SimpleAgent *agent;
//! The device representing the Raspberry Pi
cpustruc *raspi;
//! The device representing the camera
camstruc *camera;
//! A few custom devices for holding info from other agents
devicestruc *pycubed, *tempsensors, *sunsensors, *switches, *heater;
//! The shutdown flag
bool perform_shutdown = false;
//! Indicates how long we've been connected to the Raspberry Pi
Timer up_time_timer;
bool connected = false;

//! The hostname of the Raspberry Pi (e.g. raspberrypi.local)
std::string hostname;
//! The username used (e.g. pi)
std::string username;

// =========== Function Prototypes ===========
//! Attempts to connect to the Raspberry Pi by pinging it
void ConnectRaspi();
//! Updates the Raspberry Pi
void UpdateRaspi();
//! Reads and stores SOH data from other agents
//void GrabSOHData();
//! Calls a system command on the Raspberry Pi
void SystemCall(const std::string &command, std::string &output);
//! Sets default values for agent SOH data
//void SetDefaultSOHData();

////! Request to return JSON-formatted agent data
//string Request_GetData(int32_t &error);
//! Request to run a shell command on the Raspberry Pi over SSH
string Request_SSH(vector<string> &args, int32_t &error);
//! Takes a test picture on the Raspberry Pi over SSH
string Request_Picture(int32_t &error);
//! Pings the Raspberry Pi
string Request_Ping(int32_t &error);
//! Shuts down the Raspberry Pi if it is connected
string Request_Shutdown(int32_t &error);
//! Sets the current SOH string for the payload script
string Request_SetImageSize(vector<string> &args, int32_t &error);
// ===========================================


int main(int argc, char** argv) {
	
	// Set the username and hostname
	switch ( argc ) {
		// Set defaults for username and hostname
		case 1:
            hostname = "raspberrypi.local";
			username = "pi";
			break;
		// Set a default for the username
		case 2:
			username = "pi";
			hostname = argv[1];
			break;
		// Use the given username and hostname
		case 3:
			username = argv[1];
			hostname = argv[2];
			break;
		// Incorrect usage
		default:
			printf("usage: agent_raspi [[username] hostname]\n");
			printf("Default arguments are 'pi' and 'raspberrypi.local'\n");
			exit(1);
			break;
	}
	printf("Using username='%s' and hostname='%s'\n", username.c_str(), hostname.c_str());
	
	
	
	// Create the agent
	agent = new SimpleAgent(CUBESAT_AGENT_RASPI_NAME);
    agent->set_activity_period(SLEEP_TIME);
	
    int32_t status = 0;
	// Add the camera device
    devicestruc* device_ptr;
    status = agent->add_device("camera", DeviceType::CAM, &device_ptr);
    if(status < 0){
        printf("Error adding device CAM\n");
        camera = nullptr;
    }
    else {
        camera = static_cast<camstruc*>(device_ptr);
        camera->enabled = false;
        camera->pwidth = 1280;
        camera->pheight = 700;
    }

	// Add the Raspberry Pi
    status = agent->add_device("raspi", DeviceType::CPU, &device_ptr);
    if(status < 0){
        printf("Error adding device CPU\n");
        raspi = nullptr;
    }
    else {
        raspi = static_cast<cpustruc*>(device_ptr);
        raspi->utc = Time::Now();
        raspi->temp = 273.15;
        raspi->load = 0;
        raspi->gib = 0;
        raspi->maxgib = 0.5;
        raspi->boot_count = 0;
        raspi->uptime = 0;
    }

    status = agent->add_generic_device_prop_alias("raspi",{"utc","volt","amp","uptime","temp","uptime","boot_count"});
    if(status < 0){
        printf("Error creating SOH list (pycubed)[%s]\n", cosmos_error_string(status).c_str());
    }

    // create alias: device_cpu_gib_xxx -> raspi_memory_usage
    status = agent->add_custom_device_prop_alias("raspi", "gib", "raspi_memory_usage");
    if(status < 0){
        printf("Error creating alias: raspi gib [%s]\n", cosmos_error_string(status).c_str());
    }


    // create alias: device_cpu_maxgib_xxx -> raspi_max_memory
    status = agent->add_custom_device_prop_alias("raspi", "maxgib", "pycubed_max_memory");
    if(status < 0){
        printf("Error creating alias: raspi maxgib [%s]\n", cosmos_error_string(status).c_str());
    }

	
//	// Add custom devices to hold SOH data
//    tempsensors = agent->add_device("agent_temp", DeviceType::TSEN, error);
//    sunsensors = agent->add_device("agent_sun", DeviceType::SSEN, error);
//    heater = agent->add_device("agent_heater", DeviceType::HTR, error);
//    pycubed = agent->add_device("agent_pycubed", DeviceType::CPU, error);
//    switches = agent->add_device("agent_switch", DeviceType::SWCH, error);
	
	
    agent->set_soh();

    status = agent->save_node();
    if(status < 0){
        printf("Error saving node [%s]", cosmos_error_string(status).c_str());
    }
		
	// Add requests
//    agent->add_request("agent_data", Request_GetData, "", "Prints data collected from other agents");
    agent->add_request("command", Request_SSH, "command arg1 arg2 ...", "Runs a command on the Raspberry Pi (an ssh \n\t\tkeygen pair MUST be established before this \n\t\trequest can work)");
    agent->add_request("capture", Request_Picture, "", "Takes a picture with the Raspberry Pi camera (an ssh \n\t\tkeygen pair MUST be established before this \n\t\trequest can work)");
    agent->add_request("is_up", Request_Ping, "","Checks if the Raspberry Pi is up");
    agent->add_request("shutdown_raspi", Request_Shutdown, "", "Attempts to shut down the Raspberry Pi");
    agent->add_request("set_image_size", Request_SetImageSize, "pixel_height pixel_width", "Sets the configurationfor the size of the image");

	
	
	// Run the main loop for this agent
	while ( agent->StartLoop() ) {
		// Check if the Raspberry Pi is up
		ConnectRaspi();
		
		// Perform necessary I/O with the Raspberry Pi
		UpdateRaspi();
//		GrabSOHData();
	}
	
	delete agent;
	
	
	return 0;
}


void ConnectRaspi() {
	
	std::string ping_cmd = "ping -c1 -W1 " + hostname + " > /dev/null  && echo 'UP' || echo 'DOWN'";
	std::string response;
	const int kNumAttempts = 3;
	
	raspi->utc = Time::Now();
	
	// Attempt to connect some number of times
	for (int i = 0; i < kNumAttempts; ++i) {
		// Run the ping command to check if the raspi is up
		SystemCall(ping_cmd, response);
		
		// Check the output of the ping command
		if ( response.find("UP") != string::npos ) {
			printf("RaspberryPi is UP\n");
			
			// Set the connection time
            if ( !connected ) {
				up_time_timer.Start();
			}
			
            connected = true;
            raspi->uptime = (int)up_time_timer.Seconds();
			
			return;
		}
		else
			printf("Cannot reach Raspbery Pi. Attempting to reconnect...\n");
	}
	
    connected = false;
    raspi->uptime = 0;
	
	printf("Failed to connect to Raspberry Pi. Will attempt on next cycle.\n");
}


void UpdateRaspi() {
    if ( !connected ) {
		
		if ( perform_shutdown ) {
			printf("Cannot shut down the Raspberry Pi: it is not connected\n");
			perform_shutdown = false;
		}
		
		return;
	}
	
	if ( perform_shutdown ) {
		
		printf("Attempting to shut down Raspberry Pi\n");
		
		// Create the command string
		string command = "ssh " + username + "@" + hostname + " sudo shutdown now";
		
		
		// Call the command
		string output;
		SystemCall(command, output);
		
		perform_shutdown = false;
	}
}


//void GrabSOHData() {
//    static RemoteAgent agent_temp = agent->find_agent(CUBESAT_NODE_NAME, CUBESAT_AGENT_TEMP_NAME);
//    static RemoteAgent agent_sunsensor = agent->find_agent(CUBESAT_NODE_NAME, CUBESAT_AGENT_TEMP_NAME);
//    static RemoteAgent agent_heater = agent->find_agent(CUBESAT_NODE_NAME, CUBESAT_AGENT_TEMP_NAME);
//    static RemoteAgent agent_switch = agent->find_agent(CUBESAT_NODE_NAME, CUBESAT_AGENT_TEMP_NAME);
//    static RemoteAgent agent_pycubed = agent->find_agent(CUBESAT_NODE_NAME, CUBESAT_AGENT_TEMP_NAME);

	
//	// Get values from agent_temp
//    if ( agent_temp.exists ) {
//        auto values = agent->send_request_getvalue(agent_temp, {"device_tsen_temp_000", "device_tsen_utc_000",
//											"device_tsen_temp_001", "device_tsen_utc_001",
//											"device_tsen_temp_002", "device_tsen_utc_002",
//											"device_tsen_temp_003", "device_tsen_utc_003",
//											"device_tsen_temp_004", "device_tsen_utc_004"});
//		if ( !values.empty() ) {
//			tempsensors->SetCustomProperty<bool>("active", true);
			
//			tempsensors->SetCustomProperty<float>("temp_eps", values["device_tsen_temp_000"].nvalue);
//			tempsensors->SetCustomProperty<float>("temp_obc", values["device_tsen_temp_001"].nvalue);
//			tempsensors->SetCustomProperty<float>("temp_raspi", values["device_tsen_temp_002"].nvalue);
//			tempsensors->SetCustomProperty<float>("temp_battery", values["device_tsen_temp_003"].nvalue);
//			tempsensors->SetCustomProperty<float>("temp_pycubed", values["device_tsen_temp_004"].nvalue);
			
//			tempsensors->SetCustomProperty<double>("utc_eps", values["device_tsen_utc_000"].nvalue);
//			tempsensors->SetCustomProperty<double>("utc_obc", values["device_tsen_utc_001"].nvalue);
//			tempsensors->SetCustomProperty<double>("utc_raspi", values["device_tsen_utc_002"].nvalue);
//			tempsensors->SetCustomProperty<double>("utc_battery", values["device_tsen_utc_003"].nvalue);
//			tempsensors->SetCustomProperty<double>("utc_pycubed", values["device_tsen_utc_004"].nvalue);
			
//			raspi->temperature = values["device_tsen_temp_002"].nvalue;
//		}
//		else
//			tempsensors->SetCustomProperty<bool>("active", false);
//	}
//	else
//		tempsensors->SetCustomProperty<bool>("active", false);
	
//	// Get values from agent_sunsensor
//    if ( agent_sunsensor.exists ) {
//        auto values = agent->send_request_getvalue(agent_sunsensor, {"device_ssen_temp_000", "device_ssen_utc_000",
//												 "device_ssen_temp_001", "device_ssen_utc_001",
//												 "device_ssen_temp_002", "device_ssen_utc_002",
//												 "device_ssen_temp_003", "device_ssen_utc_003",
//												 "device_ssen_temp_004", "device_ssen_utc_004",
//												 "device_ssen_temp_005", "device_ssen_utc_005"});
//		if ( !values.empty() ) {
//			sunsensors->SetCustomProperty<bool>("active", true);
			
//			sunsensors->SetCustomProperty<float>("lux_plusx", values["device_ssen_temp_000"].nvalue);
//			sunsensors->SetCustomProperty<float>("lux_minusx", values["device_ssen_temp_001"].nvalue);
//			sunsensors->SetCustomProperty<float>("lux_plusy", values["device_ssen_temp_002"].nvalue);
//			sunsensors->SetCustomProperty<float>("lux_minusy", values["device_ssen_temp_003"].nvalue);
//			sunsensors->SetCustomProperty<float>("lux_plusz", values["device_ssen_temp_004"].nvalue);
//			sunsensors->SetCustomProperty<float>("lux_minusz", values["device_ssen_temp_005"].nvalue);
			
//			sunsensors->SetCustomProperty<double>("utc_plusx", values["device_ssen_utc_000"].nvalue);
//			sunsensors->SetCustomProperty<double>("utc_minusx", values["device_ssen_utc_001"].nvalue);
//			sunsensors->SetCustomProperty<double>("utc_plusy", values["device_ssen_utc_002"].nvalue);
//			sunsensors->SetCustomProperty<double>("utc_minusy", values["device_ssen_utc_003"].nvalue);
//			sunsensors->SetCustomProperty<double>("utc_plusz", values["device_ssen_utc_004"].nvalue);
//			sunsensors->SetCustomProperty<double>("utc_minusz", values["device_ssen_utc_005"].nvalue);
//		}
//		else
//			sunsensors->SetCustomProperty<bool>("active", false);
//	}
//	else
//		sunsensors->SetCustomProperty<bool>("active", false);
	
//	// Get values from agent_heater
//    if ( agent_heater.exists ) {
//        auto values = agent->send_request_getvalue(agent_heater ,{"device_htr_volt_000", "device_htr_utc_000"});
		
//		if ( !values.empty() ) {
//			heater->SetCustomProperty<bool>("active", true);
			
//			heater->SetCustomProperty<bool>("enabled", values["device_htr_volt_000"].nvalue != 0.0);
//			heater->SetCustomProperty<double>("utc", values["device_htr_utc_000"].nvalue);
//		}
//	}
	
//	// Get values from agent_switch
//    if ( agent_switch.exists ) {
//        auto values = agent->send_request_getvalue(agent_switch, {"device_swch_volt_000", "device_swch_utc_000",
//											  "device_swch_volt_001", "device_swch_utc_001",
//											  "device_swch_volt_002", "device_swch_utc_002"});
//		if ( !values.empty() ) {
//			switches->SetCustomProperty<bool>("active", true);
			
//			switches->SetCustomProperty<bool>("sw_temp", values["device_swch_volt_000"].nvalue != 0.0);
//			switches->SetCustomProperty<bool>("sw_sunsensor", values["device_swch_volt_001"].nvalue != 0.0);
//			switches->SetCustomProperty<bool>("sw_heater", values["device_swch_volt_002"].nvalue != 0.0);
			
//			switches->SetCustomProperty<double>("utc_temp", values["device_swch_utc_000"].nvalue);
//			switches->SetCustomProperty<double>("utc_sunsensor", values["device_swch_utc_001"].nvalue);
//			switches->SetCustomProperty<double>("utc_heater", values["device_swch_utc_002"].nvalue);
//		}
//		else
//			switches->SetCustomProperty<bool>("active", false);
//	}
//	else
//		switches->SetCustomProperty<bool>("active", false);
	
//	// Get values from agent_pycubed
//    if ( agent_pycubed.exists ) {
//        auto values = agent->send_request_getvalue(agent_pycubed, {"device_imu_mag_x_000", "device_imu_mag_y_000", "device_imu_mag_z_000",
//											  "device_imu_accel_x_000", "device_imu_accel_y_000", "device_imu_accel_z_000",
//											  "device_imu_omega_x_000", "device_imu_omega_y_000", "device_imu_omega_z_000", "device_imu_utc_000",
//											  "device_cpu_volt_000", "device_cpu_amp_000", "device_cpu_utc_000",
//											  "device_batt_volt_000", "device_batt_amp_000", "device_batt_utc_000",
//											  "device_gps_utc_000", "device_gps_geods_000", "device_gps_geocv_000", "device_gps_sats_used_000"});
		
//		if ( !values.empty() ) {
//			pycubed->SetCustomProperty<bool>("active", true);
			
//			pycubed->SetCustomProperty<double>("imu_utc", values["device_imu_utc_000"].nvalue);
//			pycubed->SetCustomProperty<float>("imu_mag_x", values["device_imu_mag_x_000"].nvalue);
//			pycubed->SetCustomProperty<float>("imu_mag_y", values["device_imu_mag_y_000"].nvalue);
//			pycubed->SetCustomProperty<float>("imu_mag_z", values["device_imu_mag_z_000"].nvalue);
//			pycubed->SetCustomProperty<float>("imu_accel_x", values["device_imu_accel_x_000"].nvalue);
//			pycubed->SetCustomProperty<float>("imu_accel_y", values["device_imu_accel_y_000"].nvalue);
//			pycubed->SetCustomProperty<float>("imu_accel_z", values["device_imu_accel_z_000"].nvalue);
//			pycubed->SetCustomProperty<float>("imu_gyro_x", values["device_imu_omega_000"].nvalue);
//			pycubed->SetCustomProperty<float>("imu_gyro_y", values["device_imu_omega_y_000"].nvalue);
//			pycubed->SetCustomProperty<float>("imu_gyro_z", values["device_imu_omega_z_000"].nvalue);
			
//			pycubed->SetCustomProperty<float>("power_utc", values["device_cpu_utc_000"].nvalue);
//			pycubed->SetCustomProperty<float>("sys_voltage", values["device_cpu_volt_000"].nvalue);
//			pycubed->SetCustomProperty<float>("sys_current", values["device_cpu_amp_000"].nvalue);
//			pycubed->SetCustomProperty<float>("batt_voltage", values["device_batt_volt_000"].nvalue);
//			pycubed->SetCustomProperty<float>("batt_current", values["device_batt_amp_000"].nvalue);
			
//			pycubed->SetCustomProperty<float>("gps_utc", values["device_gps_utc_000"].nvalue);
//			pycubed->SetCustomProperty<float>("gps_latitude", values["device_gps_geods_lat_000"].nvalue);
//			pycubed->SetCustomProperty<float>("gps_longitude", values["device_gps_geods_lon_000"].nvalue);
//			pycubed->SetCustomProperty<float>("gps_altitude", values["device_gps_geods_h_000"].nvalue);
//			pycubed->SetCustomProperty<float>("gps_velocity_x", values["device_gps_geocv_x_000"].nvalue);
//			pycubed->SetCustomProperty<float>("gps_velocity_y", values["device_gps_geocv_y_000"].nvalue);
//			pycubed->SetCustomProperty<float>("gps_velocity_z", values["device_gps_geocv_z_000"].nvalue);
//			pycubed->SetCustomProperty<int>("gps_satellites", (int)values["device_gps_sats_used_000"].nvalue);
			
//		}
//		else
//			pycubed->SetCustomProperty<bool>("active", false);
//	}
//	else
//		pycubed->SetCustomProperty<bool>("active", false);
//}


void SystemCall(const std::string &command, std::string &output) {
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
	if ( !pipe ) {
		throw std::runtime_error("popen() failed!");
	}
	
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	
	output = result;
}


//string Request_GetData() {
	
//	stringstream ss;
//	ss << "{";
	
//	ss <<	"\"agent_temp\": {";
//	ss <<		"\"active\": " << (tempsensors->GetCustomProperty<bool>("active") ? "true" : "false") << ", ";
//	ss <<		"\"temp_eps\": " << tempsensors->GetCustomProperty<float>("temp_eps") << ", ";
//	ss <<		"\"temp_obc\": " << tempsensors->GetCustomProperty<float>("temp_obc") << ", ";
//	ss <<		"\"temp_raspi\": " << tempsensors->GetCustomProperty<float>("temp_raspi") << ", ";
//	ss <<		"\"temp_battery\": " << tempsensors->GetCustomProperty<float>("temp_battery") << ", ";
//	ss <<		"\"temp_pycubed\": " << tempsensors->GetCustomProperty<float>("temp_pycubed");
//	ss <<	"}, ";
	
//	ss <<	"\"agent_sun\": {";
//	ss <<		"\"active\": " << (sunsensors->GetCustomProperty<bool>("active") ? "true" : "false") << ", ";
//	ss <<		"\"ss_plusx\": " << sunsensors->GetCustomProperty<float>("lux_plusx") << ", ";
//	ss <<		"\"ss_minusx\": " << sunsensors->GetCustomProperty<float>("lux_minusx") << ", ";
//	ss <<		"\"ss_plusy\": " << sunsensors->GetCustomProperty<float>("lux_plusy") << ", ";
//	ss <<		"\"ss_minusy\": " << sunsensors->GetCustomProperty<float>("lux_minusy") << ", ";
//	ss <<		"\"ss_plusz\": " << sunsensors->GetCustomProperty<float>("lux_plusz") << ", ";
//	ss <<		"\"ss_minusz\": " << sunsensors->GetCustomProperty<float>("lux_minusz");
//	ss <<	"}, ";
	
//	ss <<	"\"agent_pycubed\": {";
//	ss <<		"\"active\": " << (pycubed->GetCustomProperty<bool>("active") ? "true" : "false") << ", ";
//	ss <<		"\"imu\": {";
//	ss <<			"\"accel\": [";
//	ss <<				 pycubed->GetCustomProperty<float>("imu_accel_x") << ", ";
//	ss <<				 pycubed->GetCustomProperty<float>("imu_accel_y") << ", ";
//	ss <<				 pycubed->GetCustomProperty<float>("imu_accel_z");
//	ss <<			"], ";
//	ss <<			"\"mag\": [";
//	ss <<				 pycubed->GetCustomProperty<float>("imu_mag_x") << ", ";
//	ss <<				 pycubed->GetCustomProperty<float>("imu_mag_y") << ", ";
//	ss <<				 pycubed->GetCustomProperty<float>("imu_mag_z");
//	ss <<			"], ";
//	ss <<			"\"gyro\": [";
//	ss <<				 pycubed->GetCustomProperty<float>("imu_gyro_x") << ", ";
//	ss <<				 pycubed->GetCustomProperty<float>("imu_gyro_y") << ", ";
//	ss <<				 pycubed->GetCustomProperty<float>("imu_gyro_z");
//	ss <<			"]";
//	ss <<		"}, ";
//	ss <<		"\"gps\": {";
//	ss <<			"\"utc\": " << pycubed->GetCustomProperty<float>("gps_utc") << ", ";
//	ss <<			"\"latitude\": " << pycubed->GetCustomProperty<float>("gps_latitude") << ", ";
//	ss <<			"\"longitude\": " << pycubed->GetCustomProperty<float>("gps_longitude") << ", ";
//	ss <<			"\"altitude\": " << pycubed->GetCustomProperty<float>("gps_altitude") << ", ";
//	ss <<			"\"satellites\": " << pycubed->GetCustomProperty<int>("gps_satellites") << ", ";
//	ss <<			"\"velocity\": [";
//	ss <<				 pycubed->GetCustomProperty<float>("gps_velocity_x") << ", ";
//	ss <<				 pycubed->GetCustomProperty<float>("gps_velocity_y") << ", ";
//	ss <<				 pycubed->GetCustomProperty<float>("gps_velocity_z");
//	ss <<			"]";
//	ss <<		"}, ";
//	ss <<		"\"power\": {";
//	ss <<			"\"batt_voltage\": " << pycubed->GetCustomProperty<float>("batt_voltage") << ", ";
//	ss <<			"\"batt_current\": " << pycubed->GetCustomProperty<float>("batt_current") << ", ";
//	ss <<			"\"sys_voltage\": " << pycubed->GetCustomProperty<float>("sys_voltage") << ", ";
//	ss <<			"\"sys_current\": " << pycubed->GetCustomProperty<float>("sys_current");
//	ss <<		"}";
//	ss <<	"}, ";
	
//	ss <<	"\"agent_switch\": {";
//	ss <<		"\"active\": " << (switches->GetCustomProperty<bool>("active") ? "true" : "false") << ", ";
//	ss <<		"\"enabled\": [";
//	ss <<			(switches->GetCustomProperty<bool>("sw_temp") ? "true" : "false") << ", ";
//	ss <<			(switches->GetCustomProperty<bool>("sw_sunsensor") ? "true" : "false") << ", ";
//    ss <<			(switches->GetCustomProperty<bool>("sw_heater") ? "true" : "false");
//	ss <<		"]";
//	ss <<	"}, ";
	
//	ss <<	"\"agent_heater\": {";
//	ss <<		"\"active\": " << (heater->GetCustomProperty<bool>("active") ? "true" : "false") << ", ";
//	ss <<		"\"enabled\": " << (heater->GetCustomProperty<bool>("enabled") ? "true" : "false");
//	ss <<	"},";
	
//	ss <<	"\"agent_raspi\": {";
//	ss <<		"\"active\": true";
//	ss <<	"}";
	
//	ss << "}";
	
//	// Return the JSON string
//	return ss.str();
//}


string Request_SSH(vector<string> &args, int32_t &error) {

	
	// Make sure we actually have arguments
    if ( args.size() == 0){
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_ARGS;
		return "Usage: ssh command";
    }
	
	// Create the command string
    std::string command = "ssh " + username + "@" + hostname;
    for(string a: args){
        command += " " + a;
    }
	
	// Call the command
    std::string output;
	printf("$ %s\n", command.c_str());
	SystemCall(command, output);
	printf("%s\n", output.c_str());
	
	// Return the output of the shell command
	return output;
}

string Request_Picture(int32_t &error) {

    // Create the command string
    std::string take_picture = "ssh " + username + "@" + hostname + " rm -f test.jpeg && ssh " + username + "@" + hostname + " raspistill -o test.jpeg";


    // Call the command
    std::string output;
    printf("$ %s\n", take_picture.c_str());
    SystemCall(take_picture, output);
    printf("%s\n", output.c_str());

    // Return the output of the shell command
    return "picture taken";
}

string Request_Ping(int32_t &error) {
	std::string ping_cmd = "ping -c1 -W1 " + hostname + " > nul  && echo 'UP' || echo 'DOWN'";
	std::string response;
	const int kNumAttempts = 3;
	
	// Attempt to connect some number of times
	for (int i = 0; i < kNumAttempts; ++i) {
		// Run the ping command to check if the raspi is up
		SystemCall(ping_cmd, response);
		
		// Check the output of the ping command
		if ( response.find("UP") != string::npos ) {
			return "UP";
		}
	}
	return "DOWN";
}
string Request_Shutdown(int32_t &error) {
	perform_shutdown = true;
	return "OK";
}
string Request_SetImageSize(vector<string> &args, int32_t &error) {
    if(args.size() < 2){
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_ARGS;
        return "";
    }

    camera->pheight = stoi(args[0]);
    camera->pwidth = stoi(args[1]);
    return "";
	
}

