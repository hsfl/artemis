
// Internal headers
#include "SimpleAgent/SimpleAgent.h"
#include "device/ADT7311.h"

#include "utility/Configuration.h"

#include <iostream>
#include <fstream>

// The interval between iterations in the run_agent() function
#define SLEEP_TIME 5

using namespace std;
using namespace artemis;
using namespace rapidjson;




// |----------------------------------------------|
// |                  Prototypes                  |
// |----------------------------------------------|


//! Updates the temperature readings for a non-pycubed-connected sensor
void UpdateSensor(const std::string &name);


//! Request for displaying temperatures
string Request_Temperature(vector<string> &args, int32_t &error);

//! Request for checking a sensor is connected
string Request_Connected(vector<string> &args, int32_t &error);

//! Request for listing sensors
string Request_List(int32_t &error);

/**
 * @brief Returns the temperature sensor configuration JSON
 * @return The configuration JSON string
 */
string Request_Config(int32_t &error);


// |----------------------------------------------|
// |                   Variables                  |
// |----------------------------------------------|

//! Allows for usage of COSMOS
SimpleAgent *agent;

Document sensor_config;

//! The sensor configuration
ADT7311::Configuration default_sensor_config;

//! A map of sensor names to TemperatureSensor devices
unordered_map<string, devicestruc*> sensor_data;
unordered_map<string, ADT7311*> sensor_interface;
unordered_map<string, string> sensor_source;


// |----------------------------------------------|
// |                 Main Function                |
// |----------------------------------------------|

int main() {
    int32_t error = 0;
	
	// Create the agent
	agent = new SimpleAgent(CUBESAT_AGENT_TEMP_NAME);
	agent->set_activity_period(SLEEP_TIME);
    agent->add_request("list", Request_List, "", "Returns a list of sensors");
    agent->add_request("config", Request_Config, "", "Returns the temperature sensor configuration");
	
	// Parse the sensor configuration
	if ( !GetConfigDocument("temp_sensors", sensor_config) ) {
		printf("Fatal: failed to find configuration file\n");
		return 1;
	}
	
	// Create a default configuration register value
	default_sensor_config.fault_queue = 0;
	default_sensor_config.ct_pin_polarity = 0;
	default_sensor_config.int_pin_polarity = 0;
	default_sensor_config.int_ct_mode = 0;
	default_sensor_config.operation_mode = 0;
	default_sensor_config.resolution = 0;
	
	
	string name, type;
	int bus, cs;
    devicestruc *sensor;
    ADT7311* handler;
    vector<string> soh_props = {"utc","temp","enabled"};
	// Initialize the temperature sensor devices using the JSON
	for (auto &sensor_obj : sensor_config.GetArray()) {
		
		name = sensor_obj["name"].GetString();
		type = sensor_obj["type"].GetString();
		
		// Create a new temperature sensor device
        sensor = agent->add_device(name, DeviceType::TSEN, error);
        sensor_data[name] = sensor;
		
		
		// Initialize the device as a sensor
		if ( type == "sensor" ) {
			
			bus = sensor_obj["bus"].GetInt();
			cs = sensor_obj["cs"].GetInt();
			
            handler = new ADT7311(bus, cs);
            sensor_interface[name] = handler;
		}
        else {
            sensor_source[name] = sensor_obj["key"].GetString();
        }

        sensor->utc = Time::Now();
        sensor->enabled = false;
        sensor->temp = 0;

        error = agent->add_generic_device_prop_alias(name, soh_props);
        if(error < 0){
            printf("Error creating aliases %s [%s]\n",name.c_str(), cosmos_error_string(error).c_str());
        }
	}
	
	// Finish up
    agent->set_soh();
	
	// Start executing the agent
	while ( agent->StartLoop() ) {
		
		// Update sensor readings
        for (auto it : sensor_data) {
			UpdateSensor(it.first);
		}
	}
	
	
	
	// Free sensor devices
    for (auto it : sensor_interface) {
        ADT7311 *handler = it.second;
        handler->Close();
        delete handler;
	}
	
	// Free the agent
	delete agent;
	
	return 0;
}


void UpdateSensor(const std::string &name) {
	
	// Fetch some information
    devicestruc *sensor = sensor_data[name];
	
	// Update the timestamp
	sensor->utc = Time::Now();
	
	// Check whether the device is physical
    if ( sensor_interface.find(name) != sensor_interface.end() ) {
		
        ADT7311 *handler = sensor_interface[name];
		
		// We compare against the manufacturer ID to see if the sensors are connected
		const int kManufacturerID = 0b11000;
		
		// Make sure the sensor is open before continuing
		if ( !handler->IsOpen() ) {
			
			if ( handler->Open() ) {
				// Read the sensor state
				handler->ReadState();
				
				// Check if the manufacturer register has the correct value
				if ( handler->GetManufacturerRegister().manufacturer_id != kManufacturerID ) {
					handler->Close(); // Close the device to prevent dangling file descriptors
					
					sensor->enabled = false;
					
					printf("Failed to open temperature sensor '%s' on SPI Bus %d at CS %02x\n",
						   name.c_str(), handler->GetBus(), handler->GetDeviceAddr());
					
					return;
				}
			}
			else {
				sensor->enabled = false;
				printf("Failed to connect to sensor '%s'\n", name.c_str());
				return;
			}
		}
		
		// 1. Read the state of the sensor
		handler->ReadState();
		ADT7311::Configuration config = handler->GetConfiguration();
		
		// 2. Check if the sensor is finished reading the temperature
		// (11 = ready, otherwise not ready)
		if ( config.operation_mode == 0b11 ) {
            sensor->temp = handler->GetTemperature();
			
            printf("Sensor '%s' finished converting: %.2f C\n", name.c_str(), (float)sensor->temp);
		}
		// Wake up the sensor if it is idling
		else {
			// Set the sensor to "one shot mode"
			config.operation_mode = 0b01;
			handler->SetConfiguration(config);
			
			printf("Waking up sensor '%s'\n", name.c_str());
		}
	}
	// Handle a remote sensor
	else {
        static RemoteAgent agent_pycubed = agent->find_agent(CUBESAT_NODE_NAME, CUBESAT_AGENT_PYCUBED_NAME);
		
		
        if ( agent_pycubed.exists ) {
			
            string source_id = sensor_source[name];
            int32_t error = 0;
            auto values = agent->send_request_getvalue(agent_pycubed, {source_id}, error);
			
			// Check if the request failed
			if ( values.empty() )
				return;
			
            sensor->temp = values[source_id].nvalue;
			sensor->enabled = true;
		}
		else {
			printf("Failed to connect to agent_pycubed\n");
			sensor->enabled = false;
		}
	}
}








// |----------------------------------------------|
// |                    Requests                  |
// |----------------------------------------------|



string Request_Sensor_Temperature(vector<string> &args, int32_t &error) {
    if(args.size() == 0) {
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_ARGS;
        return "incorrect usage";
    }
    string sensor_name = args[0];
    if(sensor_data.find(sensor_name) == sensor_data.end()){
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_ARGS;
        return "unknown sensor";
    }
    return std::to_string(sensor_data[sensor_name]->temp );

}

string Request_Connected(vector<string> &args, int32_t &error) {
    if(args.size() == 0) {
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_ARGS;
        return "incorrect usage";
    }
    string sensor_name = args[0];
    if(sensor_data.find(sensor_name) == sensor_data.end()){
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_ARGS;
        return "unknown sensor";
    }
    return sensor_data[sensor_name]->enabled ? "true" : "false";
}

string Request_List(int32_t &error) {
	stringstream ss;
	
	
	// Generate a JSON list of sensor info
	ss << "{";
    for (auto it : sensor_data) {
		ss <<	"\"" << it.first << "\": {";
		ss <<		"\"utc\": " << it.second->utc << ", ";
        ss <<		"\"temp\": " << it.second->temp << ",";
		ss <<		"\"enabled\": " << (it.second->enabled ? "true" : "false");
		ss <<	"},";
	}
	ss << "}";
	
	return ss.str();
}
string Request_Config(int32_t &error) {
	string config;
	GetConfigString("temp_sensors", config);
	return config;
}

