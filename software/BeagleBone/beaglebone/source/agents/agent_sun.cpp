
// Internal headers
#include "SimpleAgent/SimpleAgent.h"
//#include "SimpleAgent/DeviceJSON.h"
#include "device/OPT3001.h"

#include "utility/Configuration.h"

#include <iostream>
#include <fstream>
#include <unordered_map>

// The interval between iterations in the run_agent() function
#define SLEEP_TIME 5


using namespace std;
using namespace artemis;
using namespace rapidjson;



// |----------------------------------------------|
// |                  Prototypes                  |
// |----------------------------------------------|


//! Initializes the sensor devices
void InitSensors();
//! Initializes a sensor
void InitSensor(int index);
//! Attempts to connect a sensor
bool ConnectSensor(int index);
//! Wraps up communication with the sensor devices
void DestroySensors();
//! Grabs the latest readings from a sensor device
void UpdateSensor(const std::string &name);
//! Enables/disables power to sensors via agent_switch
void SetSensorPower(bool enabled);


// |----------------------------------------------|
// |                   Requests                   |
// |----------------------------------------------|
//! Returns the lux read by a sensor
string Request_Sensor_Lux(vector<string> &args, int32_t &error);
//! Returns whether or not a sensor can be reached
string Request_Sensor_Connected(vector<string> &args, int32_t &error);
//! Returns the latest telemetry for a sensor
string Request_Sensor(vector<string> &args, int32_t &error);
//! Returns a list of sensors
string Request_List(int32_t &error);
/**
 * @brief Returns the sun sensor configuration JSON
 * @return The configuration JSON string
 */
string Request_Config(int32_t &error);

// |----------------------------------------------|
// |                   Variables                  |
// |----------------------------------------------|

// The agent object which allows for communication with COSMOS
SimpleAgent *agent;

Document sensor_config;


OPT3001::Configuration default_sensor_config;
OPT3001::Configuration active_config;

//! A map of sensor names to SunSensor devices
unordered_map<string, devicestruc*> sensor_data;
unordered_map<string, OPT3001*> sensor_interface;


// |----------------------------------------------|
// |                 Main Function                |
// |----------------------------------------------|

int main() {
    int32_t error = 0;
	// Create the agent
	agent = new SimpleAgent(CUBESAT_AGENT_SUNSENSOR_NAME);
	agent->set_activity_period(SLEEP_TIME);
    agent->add_request("sensor_status", Request_Sensor, "sensor_name", "Returns the status of a sensor");
    agent->add_request("list", Request_List, "", "Returns a list of sensors");
    agent->add_request("config", Request_Config, "", "Returns the sun sensor configuration");
    agent->add_request("connected", Request_Sensor_Connected, "sensor_name","Returns true if the sun sensor is connected");
    agent->add_request("lux", Request_Sensor_Lux,"sensor_name", "Returns the lux of the sun sensor");
	
	// Parse the sensor configuration
	if ( !GetConfigDocument("sun_sensors", sensor_config) ) {
		printf("Fatal: failed to find configuration file\n");
		return 1;
	}
	
    string sensor_name;
	int bus, address;
//	Vec3 orientation;
    devicestruc *sensor;
    OPT3001* interface;
    vector<string> soh_props = {"utc","enabled","volt","amp","power"};
	
	// Initialize the sun sensor devices using the parsed JSON
	for (auto &sensor_obj : sensor_config.GetArray()) {
		
		// Grab the JSON fields for this sun sensor
        sensor_name = sensor_obj["name"].GetString();
		bus = sensor_obj["bus"].GetInt();
		address = sensor_obj["address"].GetInt();
//		orientation = Vec3(sensor_obj["orientation"].GetArray()[0].GetInt(),
//						   sensor_obj["orientation"].GetArray()[1].GetInt(),
//						   sensor_obj["orientation"].GetArray()[2].GetInt());
		
		// Create a new sun sensor device
        sensor = agent->add_device(sensor_name, DeviceType::SSEN, error);
        interface = new OPT3001(bus, address);
		

        sensor->utc = Time::Now();
        sensor->enabled = false; // true = connected, false = not connected
        sensor->temp = 0; // Represents the lux readings

		// Store sensor
        sensor_data[sensor_name] = sensor;
        sensor_interface[sensor_name] = interface;

        // Add the sun sensor to the soh
        agent->append_soh_list(sensor_name, soh_props);
        // TODO create alias from temp to lux
        // add device_ssen_lux_000 to soh string
        string lux_alias = agent->create_device_value_alias(sensor_name, "temp", "lux", error);
        if(error < 0){
            printf("Error creating alias: lux\n");
        }
        agent->append_soh_list(lux_alias);

	}
	
    agent->set_soh();
	
	// Run the main loop for this agent
	while ( agent->StartLoop() ) {
		
		// Update the sensors
        for (auto pair : sensor_data) {
			UpdateSensor(pair.first);
		}
		
	}
	
	// Finish up with the sensors
    for (auto pair : sensor_interface) {
        pair.second->Close();
        delete pair.second;
	}
	
	// Delete the agent
	delete agent;
	
	return 0;
}


void UpdateSensor(const std::string &name) {
    devicestruc *sensor = sensor_data[name];
    OPT3001 *opt3001 = sensor_interface[name];
	
	sensor->utc = Time::Now();
	
	// Make sure the sensor is open
	if ( !opt3001->IsOpen() ) {
		printf("Opening sensor '%s' on I2C-%d at address 0x%02x... ",
			   name.c_str(), opt3001->GetBusAddr(), opt3001->GetDeviceAddr());
		
        if ( !opt3001->Open() ) {
			opt3001->Close();
			sensor->enabled = false;
			printf(" failed.\n");
			return;
		}
		else {
			sensor->enabled = true;
			printf(" succeeded.\n");
		}
	}
	
	
	// 1. Read from the sensor
	opt3001->ReadState();
	OPT3001::Configuration config = opt3001->GetConfiguration();
	
	
	// 2. Check if the sensor is finished reading the lux
	// (0 = not ready, 1 = ready)
	if ( config.ConversionReady == 1 ) {
		
		// Use the temperature field since there's no built-in lux field
        sensor->temp = opt3001->GetLux();
		
        printf("Sensor '%s' finished converting: %.2f lx\n", name.c_str(), (float)sensor->volt);
	}
	
	
	// 3. Wake up the sensor if it is idling
	// (00 = idling, 01 = single-shot, 10/11 = continuous conversion)
	if ( config.ModeOfConversionOperation == 0 ) {
		
		// Write "single-shot" mode to the configuration register
		config.ModeOfConversionOperation = 1;
		opt3001->SetConfiguration(config);
		
		printf("Waking up sensor '%s'\n", name.c_str());
	}
}

// |----------------------------------------------|
// |                    Requests                  |
// |----------------------------------------------|

string Request_Sensor_Lux(vector<string> &args, int32_t &error) {
    if(args.size() == 0) {
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_EMPTY;
        return "\"usage: sensor_name\"";
    }
    string sensor_name = args[0];
    if(sensor_data.find(sensor_name) == sensor_data.end()) {
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_NAME;
        return "\"unknown sensor\"";
    }
    return to_string(sensor_data[sensor_name]->temp);

}
string Request_Sensor_Connected(vector<string> &args, int32_t &error) {
    if(args.size() == 0) {
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_EMPTY;
        return "\"usage: sensor_name\"";
    }
    string sensor_name = args[0];
    if(sensor_interface.find(sensor_name) == sensor_interface.end()) {
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_NAME;
        return "\"unknown sensor\"";
    }
    if(sensor_interface[sensor_name] != nullptr && sensor_interface[sensor_name]->IsOpen() ){
        return "true";
    }
    return "false";

}

string Request_Sensor(vector<string> &args, int32_t &error){
    if(args.size() == 0) {
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_EMPTY;
        return "\"usage: sensor_name\"";
    }
    string sensor_name = args[0];
    if(sensor_data.find(sensor_name) == sensor_data.end()) {
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_NAME;
        return "\"unknown sensor\"";
    }
    devicestruc *sensor = sensor_data[sensor_name];
	
	// Generate the response
	stringstream ss;
	ss << "{" << std::endl;
	ss << "\t\"name\": \"" << sensor_name << "\", " << std::endl;
	ss << "\t\"utc\": " << (double)sensor->utc << ", " << std::endl;
    ss << "\t\"lux\": " << (float)sensor->temp << ", " << std::endl;
	ss << "\t\"connected\": " << (sensor->enabled ? "true" : "false") << std::endl;
	ss << "}" << std::endl;
	
	return ss.str();
}

string Request_List(int32_t &error) {
	
    devicestruc *sensor;
	
	stringstream ss;
	ss << "[";
	
    for (auto pair : sensor_data) {
		sensor = pair.second;
		ss << "\t{" << std::endl;
		ss << "\t\t\"name\": \"" << pair.first << "\", " << std::endl;
		ss << "\t\t\"utc\": " << (double)sensor->utc << ", " << std::endl;
        ss << "\t\t\"lux\": " << (float)sensor->temp << ", " << std::endl;
		ss << "\t\t\"connected\": " << (sensor->enabled ? "true" : "false") << std::endl;
		ss << "\t}," << std::endl;
	}
	
	ss << "]";
	
	return ss.str();
}
string Request_Config(int32_t &error) {
	string config;
	GetConfigString("sun_sensors", config);
	return config;
}
