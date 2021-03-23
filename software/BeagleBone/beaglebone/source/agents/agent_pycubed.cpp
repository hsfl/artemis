
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
devicestruc *pycubed;
//! The IMU device located on the PyCubed
devicestruc *imu;
//! The GPS device located on the PyCubed
devicestruc *gps;
//! The radio device located on the PyCubed
devicestruc *radio;
//! The battery device located on the battery board
devicestruc *battery;

string PowerUse = "powuse";
string PowerGeneration = "powgen";
string BatteryCapacity = "battcap";
string BatteryCharge = "battlev";

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

    agent->set_value(PowerUse, 0.);
    agent->set_value(PowerGeneration, 0.);
    agent->set_value(BatteryCapacity, 3.5f * 4);
    agent->set_value(BatteryCharge, 0.);
    agent->append_soh_list("node",{PowerUse, PowerGeneration, BatteryCapacity, BatteryCharge});

	
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
    int32_t error = 0;
	// Create a new PyCubed device
	handler = new PyCubed(uart, baud);
	handler->SetShutdownCallback(Shutdown);
	handler->SetCommandCallback(RunCommand);
	
	// Add the PyCubed CPU device
    pycubed = agent->add_device("pycubed", DeviceType::CPU, error);
    if(error < 0){
        printf("Error adding device CPU\n");
    }
    pycubed->utc = Time::Now();
    pycubed->cpu.gib = 0;
    pycubed->cpu.maxgib = 0.0037252903; // MR25H40MDF RAM
    pycubed->volt = 0;
    pycubed->amp = 0;
    pycubed->cpu.uptime = 0;
    pycubed->temp = 273.15;

    error = agent->add_generic_device_prop_alias("pycubed",{"utc","volt","amp","uptime","temp"});
    if(error < 0){
        printf("Error creating aliases (pycubed) [%s]\n",  cosmos_error_string(error).c_str());
    }

    // create alias: device_cpu_gib_xxx -> pycubed_memory_usage
    error = agent->add_custom_device_prop_alias("pycubed", "gib", "pycubed_memory_usage");
    if(error < 0){
        printf("Error creating alias: pycubed gib [%s]\n", cosmos_error_string(error).c_str());
    }

    // create alias: device_cpu_maxgib_xxx -> pycubed_max_memory
    error = agent->add_custom_device_prop_alias("pycubed", "maxgib", "pycubed_max_memory");
    if(error < 0){
        printf("Error creating alias: pycubed maxgib [%s]\n", cosmos_error_string(error).c_str());
    }

	// Add the battery pack
    battery = agent->add_device("battery", DeviceType::BATT, error);
    if(error < 0){
        printf("Error adding device BATT\n");
    }
    battery->utc = Time::Now();
    battery->temp = 273.15;
    battery->batt.capacity = 3.5f * 4;
    battery->batt.charge = 3.5f * 4;
    battery->batt.efficiency = 0.85f;
    battery->batt.percentage = 100;
    battery->volt = 0;
    battery->amp = 0;

    agent->add_request("battery_charge", RequestGetBatteryCharge, "","battery level");
	
    error = agent->add_generic_device_prop_alias("battery",{"utc","capacity","efficiency","volt","amp","charge","percentage","temp"});
    if(error < 0){
        printf("Error creating aliases (battery) [%s]\n",  cosmos_error_string(error).c_str());
    }
	
	// Add the IMU
    imu = agent->add_device("imu", DeviceType::IMU, error);
    if(error < 0){
        printf("Error adding device IMU[%s]\n",  cosmos_error_string(error).c_str());
    }

    imu->utc = Time::Now();
    imu->temp = 273.15;

    error = agent->add_generic_device_prop_alias("imu",{"utc","volt","amp","power","temp"});
    if(error < 0){
        printf("Error creating aliases (imu)[%s]\n",  cosmos_error_string(error).c_str());;
    }

    // create alias: device_imu_mag_000 -> imu_magnetic_field
    error = agent->add_custom_device_prop_alias("imu","mag", "imu_magnetic_field");
    if(error < 0){
        printf("Error creating alias for: imu_magnetic_field [%s]\n", cosmos_error_string(error).c_str());
    }

    // create alias: device_imu_omega_000 -> imu_angular_velocity
    error = agent->add_custom_device_prop_alias("imu","omega", "imu_angular_velocity");
    if(error < 0){
        printf("Error creating alias for: imu_angular_velocity [%s]\n", cosmos_error_string(error).c_str());
    }

    // create alias: device_imu_alpha_000 -> imu_acceleration
    error = agent->add_custom_device_prop_alias("imu","alpha", "imu_acceleration");
    if(error < 0){
        printf("Error creating alias for: imu_acceleration [%s]\n", cosmos_error_string(error).c_str());
    }

	// Add the GPS
    gps = agent->add_device("gps", DeviceType::GPS, error);
    if(error < 0){
        printf("Error adding device (GPS)[%s]\n", cosmos_error_string(error).c_str());
    }
    gps->utc = Time::Now();
    error = agent->add_generic_device_prop_alias("gps", {"utc","volt","amp","power","temp"});
    if(error < 0){
        printf("Error creating SOH list (imu)[%s]\n", cosmos_error_string(error).c_str());
    }

    // create alias: device_gps_sats_used_000 -> gps_satellites_used
    error = agent->add_custom_device_prop_alias("gps","sats_used", "gps_satellites_used");
    if(error < 0){
        printf("Error creating alias for: gps_satellites_used [%s]\n", cosmos_error_string(error).c_str());
    }

    // create alias: device_gps_geocv_000 -> gps_velocity
    error = agent->add_custom_device_prop_alias("gps","geocv", "gps_velocity");
    if(error < 0){
        printf("Error creating alias for: gps_velocity [%s]\n", cosmos_error_string(error).c_str());
    }

    // create alias: device_gps_geods_000 -> gps_location
    error = agent->add_custom_device_prop_alias("gps","geods", "gps_location");
    if(error < 0){
        printf("Error creating alias for: gps_velocity [%s]\n", cosmos_error_string(error).c_str());
    }

    return error;
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
        pycubed->cpu.uptime = 0;
		
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
    pycubed->cpu.uptime = (int)connection_timer.Seconds();
	
	// Store battery info
	battery->utc = Time::Now();
    battery->volt = power_info.batt_voltage;
    battery->amp = power_info.batt_current;
    battery->temp = temp_info.batt_temp;
	
	// Store IMU info
	imu->utc = Time::Now();
    imu->temp = temp_info.cpu_temp;
    imu->imu.mag = imu_info.magnetometer;
    imu->imu.alpha = imu_info.acceleration;
    imu->imu.omega = imu_info.gyroscope;
	
	// Store GPS info
	gps->utc = Time::Now();
    gps->gps.geods.lat = gps_info.latitude;
    gps->gps.geods.lon = gps_info.longitude;
    gps->gps.geods.h = gps_info.altitude;
    gps->gps.geocv.col[0] = gps_info.speed;
    gps->gps.sats_used = gps_info.sats_used;
	
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
    string pycubed_utc = agent->get_soh_name("pycubed", "utc", error);
    string pycubed_volt = agent->get_soh_name("pycubed", "volt", error);
    string pycubed_current = agent->get_soh_name("pycubed", "amp", error);
    string pycubed_uptime = agent->get_soh_name("pycubed", "uptime", error);
    string pycubed_temp = agent->get_soh_name("pycubed", "temp", error);
    vector<string> names ={pycubed_utc, pycubed_volt, pycubed_current, "pycubed_memory_usage","pycubed_max_memory", pycubed_uptime ,pycubed_temp};
    string jstring =  agent->get_values( names, error);
    return jstring;
}

string Request_GetIMUData(int32_t &error) {
    string imu_utc = agent->get_soh_name("imu", "utc", error);
    string imu_temp = agent->get_soh_name("imu", "temp", error);

    vector<string> names = {imu_utc,imu_temp,"imu_magnetic_field","imu_acceleration", "imu_angular_velocity"};
    string jstring =  agent->get_values( names, error);

    return jstring;
}

string Request_GetGPSData(int32_t &error) {
    string gps_utc = agent->get_soh_name("gps", "utc", error);
    vector<string> names = {gps_utc,"gps_location","gps_satellites_used"};
    string jstring =  agent->get_values(names, error);
    return jstring;
}

string Request_GetPowerData(int32_t &error) {
    vector<string> props = {"utc","capacity","charge", "efficiency","percentage","volt","amp","temp"};
    string jstring =  agent->get_device_values("battery", props, error);
    return jstring;
}
string Request_GetTemperatureData(int32_t &error) {
    string pycubed_temp = agent->get_soh_name("pycubed","temp", error);
    string pycubed_utc = agent->get_soh_name("pycubed","utc", error);
    string battery_temp = agent->get_soh_name("battery","temp", error);
    vector<string> props = {pycubed_utc, pycubed_temp, battery_temp};
    string jstring =  agent->get_values(props, error);
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

    return agent->get_device_values("battery",{"charge"}, error);
}





