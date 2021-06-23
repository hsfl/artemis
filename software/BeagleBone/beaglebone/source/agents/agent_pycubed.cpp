
#include "CubeSat.h"
#include "SimpleAgent/SimpleAgent.h"
#include "device/PyCubed.h"
#include "utility/Configuration.h"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <net/if.h>
#include <linux/if_tun.h>

// The interval between iterations in the run_agent() function
#define SLEEP_TIME 1

#define PYCUBED_UART 1
#define PYCUBED_BAUD 9600

using namespace std;
using namespace artemis;
using namespace rapidjson;

// |----------------------------------------------|
// |                   Variables                  |
// |----------------------------------------------|

//! The agent object which allows for communication with COSMOS
SimpleAgent *agent;
//! The handler object used to communicate with the PyCubed
PyCubed *handler = nullptr;
unsigned int uart, baud;

Document config;


//! The CPU device representing the PyCubed
static cpustruc *pycubed;
//! The IMU device located on the PyCubed
static imustruc *imu;
//! The GPS device located on the PyCubed
static gpsstruc *gps;
//! The radio device located on the PyCubed
static rxrstruc *radio;
//! The battery device located on the battery board
static battstruc *battery;

string PowerUse = "node_powuse";
string PowerGeneration = "node_powgen";
string BatteryCapacity = "node_battcap";
string BatteryCharge = "node_battlev";

//! A timer
Timer connection_timer;

//! Timer used for radio kill requests
Timer kill_timer;
bool first_kill_received = false;
bool sent_startup_confirmation = false;



// |----------------------------------------------|
// |                  Prototypes                  |
// |----------------------------------------------|


//! Sets up the PyCubed
int32_t InitPyCubed();
//! Tries to connect to the PyCubed
bool ConnectPyCubed();
//! Handles operations with the PyCubed
void UpdatePyCubed();

/**
 * @brief Shutdown callback function
 */
void Shutdown();

//! Command callback function
void RunCommand(const std::string &cmd);

// |----------------------------------------------|
// |                    Requests                  |
// |----------------------------------------------|

/**
 * @brief Checks if the PyCubed can be reached
 * @return True if the PyCubed is connected
 */
string Request_IsUp(int32_t &error);

/**
 * @brief Sends a message to the PyCubed
 * @param message_type The message type
 * @param message_args A comma-separated list of arguments, not including the checksum
 * @return True if the message was sent successfullly
 */
string Request_SendMessage(vector<string> &args, int32_t &error);

/**
 * @brief Returns the latest CPU data received
 * @return The CPU data as a JSON string
 */
string Request_GetCPUData(int32_t &error);

/**
 * @brief Returns the latest IMU data received
 * @return The IMU data as a JSON string
 */
string Request_GetIMUData(int32_t &error);

/**
 * @brief Returns the latest GPS data received
 * @return The GPS data as a JSON string
 */
string RequestGetBatteryCharge(int32_t &error);
/**
 * @brief Returns the latest GPS data received
 * @return The GPS data as a JSON string
 */
string Request_GetGPSData(int32_t &error);

/**
 * @brief Returns the latest power use data received
 * @return The power data as a JSON string
 */
string Request_GetPowerData(int32_t &error);

/**
 * @brief Returns the latest temperature data received
 * @return The temperature data as a JSON string
 */
string Request_GetTemperatureData(int32_t &error);

/**
 * @brief Sends a message to the PyCubed to kill the radio
 * @return True if the message was sent successfully
 */
string Request_KillRadio(int32_t &error);

/**
 * @brief Spoofs the given string as input from the PyCubed.
 * @param input The input string
 */
string Request_Spoof(vector<string> &args, int32_t &error);


// |----------------------------------------------|
// |                 Main Function                |
// |----------------------------------------------|

int main(int argc, char** argv) {
    int32_t error = 0;
	
	if ( GetConfigDocument("pycubed", config) ) {
		uart = config["uart"].GetInt();
		baud = config["baud"].GetInt();
	}
	else {
		uart = PYCUBED_UART;
		baud = PYCUBED_BAUD;
	}
	
	switch ( argc ) {
		case 3:
			baud = atoi(argv[2]);
		case 2:
			uart = atoi(argv[1]);
			break;
		case 1:
			break;
		default:
			printf("usage: agent_pycubed [uart=1 [baud]]\n");
			exit(1);
	}
	printf("Using PyCubed on UART%d at %d baud\n", uart, baud);
	
	// Initialize the Agent
	agent = new SimpleAgent(CUBESAT_AGENT_PYCUBED_NAME);
	agent->set_activity_period(SLEEP_TIME);

    error = agent->set_value(PowerUse, 0.);
    error = agent->set_value(PowerGeneration, 0.);
    error = agent->set_value(BatteryCapacity, 3.5f * 4);
    error = agent->set_value(BatteryCharge, 0.);
    error = agent->append_soh_list({PowerUse, PowerGeneration, BatteryCapacity, BatteryCharge});

	
    agent->add_request("is_up", Request_IsUp, "", "Checks if the PyCubed is reachable");
    agent->add_request("send", Request_SendMessage, "msgtype arg1 arg2 ...", "Sends a message to the PyCubed");
    agent->add_request("cpu", Request_GetCPUData, "", "Returns the latest CPU data received");
    agent->add_request("imu", Request_GetIMUData, "", "Returns the latest IMU data received");
    agent->add_request("gps", Request_GetGPSData, "", "Returns the latest GPS data received");
    agent->add_request("temperature", Request_GetTemperatureData, "", "Returns the latest temperature data received");
    agent->add_request("power", Request_GetPowerData, "", "Returns the latest power data received");
    agent->add_request("kill_radio", Request_KillRadio, "", "Sends a message to the PyCubed to kill the radio");
    agent->add_request("spoof", Request_Spoof, "msgtype arg1 arg2 ...", "Spoofs the given string as input from the PyCubed. Do not include checksum or syncword");
	
	// Initialize the PyCubed
    error = InitPyCubed();
    if(error < 0){
        exit(error);
    }

	
	// Finish adding properties
    agent->set_soh();

    error = agent->save_node();
    if(error < 0){
        printf("Error saving node [%s]", cosmos_error_string(error).c_str());
    }
	
	// Run the main loop for this agent
	while ( agent->StartLoop() ) {
		
		// Try to connect to the PyCubed
		ConnectPyCubed();
		
		// Update the PyCubed
		UpdatePyCubed();
	}
	
	// Tidy up
	handler->Close();
	
	delete handler;
	delete agent;
	
	
	return 0;
}


int32_t InitPyCubed() {
    int32_t status = 0;
	// Create a new PyCubed device
	handler = new PyCubed(uart, baud);
	handler->SetShutdownCallback(Shutdown);
	handler->SetCommandCallback(RunCommand);
	
	// Add the PyCubed CPU device

    devicestruc *device_ptr;
    status = agent->add_device("pycubed", DeviceType::CPU, &device_ptr);
    if(status < 0){
        printf("Error adding device CPU\n");
        pycubed = nullptr;
        return status;
    }
    else {
        pycubed = static_cast<cpustruc*>(device_ptr);

        pycubed->utc = Time::Now();
        pycubed->gib = 0;
        pycubed->maxgib = 0.0037252903; // MR25H40MDF RAM
        pycubed->volt = 0;
        pycubed->amp = 0;
        pycubed->uptime = 0;
        pycubed->temp = 273.15;
    }


    status = agent->add_generic_device_prop_alias("pycubed",{"utc","uptime","temp"});
    if(status < 0){
        printf("Error creating aliases (pycubed) [%s]\n",  cosmos_error_string(status).c_str());
    }

    // create alias: device_cpu_gib_xxx -> pycubed_memory_usage
    status = agent->add_custom_device_prop_alias("pycubed", "gib", "pycubed_memory_usage");
    if(status < 0){
        printf("Error creating alias: pycubed gib [%s]\n", cosmos_error_string(status).c_str());
    }

    // create alias: device_cpu_maxgib_xxx -> pycubed_max_memory
    status = agent->add_custom_device_prop_alias("pycubed", "maxgib", "pycubed_max_memory");
    if(status < 0){
        printf("Error creating alias: pycubed maxgib [%s]\n", cosmos_error_string(status).c_str());
    }

	// Add the battery pack
    status = agent->add_device("battery", DeviceType::BATT, &device_ptr);
    if(status < 0){
        printf("status adding device BATT\n");
        battery = nullptr;
        return status;
    } else {
        battery = static_cast<battstruc*>(device_ptr);
        battery->utc = Time::Now();
        battery->temp = 273.15;
        battery->capacity = 3.5f * 4;
        battery->charge = 3.5f * 4;
        battery->efficiency = 0.85f;
        battery->percentage = 100;
        battery->volt = 0;
        battery->amp = 0;
    }




    status = agent->add_request("battery_charge", RequestGetBatteryCharge, "","battery level");
	
    status = agent->add_generic_device_prop_alias("battery",{"utc","cap","eff","volt","amp","charge","percentage","temp"});
    if(status < 0){
        printf("Error creating aliases (battery) [%s]\n",  cosmos_error_string(status).c_str());
    }
	
	// Add the IMU
    status = agent->add_device("imu", DeviceType::IMU, &device_ptr);
    if(status < 0){
        printf("Error adding device IMU[%s]\n",  cosmos_error_string(status).c_str());
        imu = nullptr;
        return status;
    }
    else {
        imu = static_cast<imustruc*>(device_ptr);
        imu->utc = Time::Now();
        imu->temp = 273.15;
    }



    status = agent->add_generic_device_prop_alias("imu",{"utc","volt","amp","power","temp"});
    if(status < 0){
        printf("Error creating aliases (imu)[%s]\n",  cosmos_error_string(status).c_str());;
    }

    // create alias: device_imu_mag_000 -> imu_magnetic_field
    status = agent->add_custom_device_prop_alias("imu","mag", "imu_magnetic_field");
    if(status < 0){
        printf("Error creating alias for: imu_magnetic_field [%s]\n", cosmos_error_string(status).c_str());
    }

    // create alias: device_imu_omega_000 -> imu_angular_velocity
    status = agent->add_custom_device_prop_alias("imu","omega", "imu_angular_velocity");
    if(status < 0){
        printf("Error creating alias for: imu_angular_velocity [%s]\n", cosmos_error_string(status).c_str());
    }

    // create alias: device_imu_alpha_000 -> imu_acceleration
    status = agent->add_custom_device_prop_alias("imu","alpha", "imu_acceleration");
    if(status < 0){
        printf("Error creating alias for: imu_acceleration [%s]\n", cosmos_error_string(status).c_str());
    }

	// Add the GPS
    status = agent->add_device("gps", DeviceType::GPS, &device_ptr);
    if(status < 0){
        printf("Error adding device (GPS)[%s]\n", cosmos_error_string(status).c_str());
        gps = nullptr;
        return status;
    }
    gps = static_cast<gpsstruc*>(device_ptr);
    gps->utc = Time::Now();
    status = agent->add_generic_device_prop_alias("gps", {"utc","volt","amp","power","temp"});
    if(status < 0){
        printf("Error creating SOH list (imu)[%s]\n", cosmos_error_string(status).c_str());
    }

    // create alias: device_gps_sats_used_000 -> gps_satellites_used
    status = agent->add_custom_device_prop_alias("gps","sats_used", "gps_satellites_used");
    if(status < 0){
        printf("Error creating alias for: gps_satellites_used [%s]\n", cosmos_error_string(status).c_str());
    }

    // create alias: device_gps_geocv_000 -> gps_velocity
    status = agent->add_custom_device_prop_alias("gps","geocv", "gps_velocity");
    if(status < 0){
        printf("Error creating alias for: gps_velocity [%s]\n", cosmos_error_string(status).c_str());
    }

    // create alias: device_gps_geods_000 -> gps_location
    status = agent->add_custom_device_prop_alias("gps","geods", "gps_location");
    if(status < 0){
        printf("Error creating alias for: gps_velocity [%s]\n", cosmos_error_string(status).c_str());
    }

    return status;
}

bool ConnectPyCubed() {
	
	// It's all good if we're already connected
	if ( handler->IsOpen() )
		return true;
	
	// Try to open the PyCubed device
	if ( handler->Open() ) {
		
		// Mark the time the PyCubed was connected to
		connection_timer.Start();
		
		printf("Successfully opened PyCubed device at %s\n", handler->GetDevicePath().c_str());
		return true;
	}
	else {
		printf("Failed to open PyCubed device at %s\n", handler->GetDevicePath().c_str());
		
		// Close the device just in case
		handler->Close();
		return false;
	}
}

void UpdatePyCubed() {
	
	pycubed->enabled = handler->IsOpen();
	
	
	// Make sure the PyCubed is connected
	if ( !handler->IsOpen() ) {
		
		// Set the PyCubed connection status
		pycubed->enabled = false;
        pycubed->uptime = 0;
		
		// Update timestamps
		pycubed->utc = Time::Now();
		battery->utc = Time::Now();
		imu->utc = Time::Now();
		gps->utc = Time::Now();
        agent->set_value("node_utc", Time::Now());
		
		return;
	}
	
	// Send startup confirmation
    if ( !sent_startup_confirmation ) {
		handler->StartupConfirmation();
        sent_startup_confirmation = true;
	}
	
	// Receive messages from pycubed
	handler->ReceiveMessages();
	
	// Get the latest device information
	PyCubedIMUInfo imu_info = handler->GetIMUInfo();
	PyCubedGPSInfo gps_info = handler->GetGPSInfo();
	PyCubedPowerInfo power_info = handler->GetPowerInfo();
	PyCubedTempInfo temp_info = handler->GetTempInfo();
	
	// Store CPU info
	pycubed->utc = Time::Now();
    pycubed->volt = power_info.sys_voltage;
    pycubed->amp = power_info.sys_current;
    pycubed->temp = temp_info.cpu_temp;
    pycubed->uptime = (int)connection_timer.Seconds();
	
	// Store battery info
	battery->utc = Time::Now();
    battery->volt = power_info.batt_voltage;
    battery->amp = power_info.batt_current;
    battery->temp = temp_info.batt_temp;
	
	// Store IMU info
	imu->utc = Time::Now();
    imu->temp = temp_info.cpu_temp;
    imu->mag = imu_info.magnetometer;
    imu->alpha = imu_info.acceleration;
    imu->omega = imu_info.gyroscope;
	
	// Store GPS info
	gps->utc = Time::Now();
    gps->geods.lat = gps_info.latitude;
    gps->geods.lon = gps_info.longitude;
    gps->geods.h = gps_info.altitude;
    gps->geocv.col[0] = gps_info.speed;
    gps->sats_used = gps_info.sats_used;
	
	// Store node info
    agent->set_value(PowerUse, power_info.batt_current * power_info.batt_voltage);
    agent->set_value(BatteryCharge, 0); // ?
}


void Shutdown() {
	
	// 1. Shut down agents (not agent_switch)
	system("agent " CUBESAT_NODE_NAME " " CUBESAT_AGENT_TEMP_NAME " shutdown");
	system("agent " CUBESAT_NODE_NAME " " CUBESAT_AGENT_SUNSENSOR_NAME " shutdown");
	system("agent " CUBESAT_NODE_NAME " " CUBESAT_AGENT_HEATER_NAME " shutdown");
	system("agent " CUBESAT_NODE_NAME " " CUBESAT_AGENT_RASPI_NAME " shutdown");
	
	// 2. Turn off hardware components (agent_switch)
	system("agent " CUBESAT_NODE_NAME " " CUBESAT_AGENT_SWITCH_NAME " disable all");
	
	// 3. Give PyCubed permission to take over
	handler->Handoff();
	agent->Shutdown();
	
	// 4. Shut down the BeagleBone
	system("shutdown -h now");
	
	exit(0);
}

void RunCommand(const std::string &cmd) {
	printf("$%s\n", cmd.c_str());
	system(cmd.c_str());
}

//===============================================================
//========================== REQUESTS ===========================
//===============================================================

string Request_IsUp(int32_t &error) {
    return handler->IsOpen() ? "true" : "false";
}

string Request_SendMessage(vector<string> &args, int32_t &error) {
	
	// Make sure the PyCubed is connected first
	if ( !handler->IsOpen() )
        return "false";
	
	// Parse the string into a vector of arguments
    if(args.size() == 0) {
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_EMPTY;
        return "incorrect usage";
    }
    string message_type = args[0];
    args.erase(args.begin());
	
	// Send the message
    return handler->SendMessage(message_type, args) ? "true" : "false";
}

string Request_Spoof(vector<string> &args, int32_t &error) {
    if(args.size() == 0) {
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_EMPTY;
        return "incorrect usage";
    }
	stringstream spoofed;
	
	// Compute the checksum of the message
    string input = args[0];
	int checksum = 0;
	for (char c : input)
		checksum ^= c;
	
	// Format the message string
	spoofed << '$' << input << "," << std::setfill('0') << std::setw(2) << std::hex << checksum;
	spoofed << '\n';
	
	// Pass the message to the PyCubed
	handler->SpoofInput((uint8_t*)spoofed.str().c_str(), spoofed.str().size());
    return "";
}


string Request_GetCPUData(int32_t &error) {

    vector<string> names ={"pycubed_utc", "pycubed_volt", "pycubed_amp", "pycubed_memory_usage","pycubed_max_memory", "pycubed_uptime" ,"pycubed_temp"};
    string jstring;
    error =  agent->get_values(names, jstring);
    return jstring;
}

string Request_GetIMUData(int32_t &error) {
    vector<string> names = {"imu_utc","imu_temp","imu_magnetic_field","imu_acceleration", "imu_angular_velocity"};
    string jstring;
    error =  agent->get_values(names, jstring);

    return jstring;
}

string Request_GetGPSData(int32_t &error) {
    vector<string> names = {"gps_utc","gps_location","gps_satellites_used"};

    string jstring;
    error =  agent->get_values(names, jstring);
    return jstring;
}

string Request_GetPowerData(int32_t &error) {
    vector<string> names = {"battery_utc","battery_cap","battery_charge", "battery_eff","battery_percentage","battery_volt","battery_amp","battery_temp"};
    string jstring;
    error=  agent->get_values(names, jstring);
    return jstring;
}
string Request_GetTemperatureData(int32_t &error) {
    vector<string> props = {"pycubed_utc", "pycubed_temp", "battery_temp"};
    string jstring;
    error =  agent->get_values(props, jstring);
    return jstring;
}
string Request_KillRadio(int32_t &error) {
	if ( !handler->IsOpen() ) {
		cout << "[Error] Attempted to kill the radio, but no PyCubed is connected." << endl;
        return "false";
	}
	
	if ( first_kill_received ) {
		first_kill_received = false;
		
		if ( kill_timer.Seconds() < 5 ) {
			cout << "Second kill request received. Killing the radio..." << endl;
            return handler->KillRadio() ? "true" : "false";
		}
		else {
            return "false";
		}
	}
	else {
		first_kill_received = true;
	}
    return "true";
}

string RequestGetBatteryCharge(int32_t &error){

    string json ;
    error = agent->get_device_values("battery",{"charge"}, json);
    return json;
}





