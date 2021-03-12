
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
float Request_Temperature(TemperatureSensor *sensor);

//! Request for checking a sensor is connected
bool Request_Connected(TemperatureSensor *sensor);

//! Request for listing sensors
string Request_List();

/**
 * @brief Returns the temperature sensor configuration JSON
 * @return The configuration JSON string
 */
string Request_Config();


// |----------------------------------------------|
// |                   Variables                  |
// |----------------------------------------------|

//! Allows for usage of COSMOS
SimpleAgent *agent;

Document sensor_config;

//! The sensor configuration
ADT7311::Configuration default_sensor_config;

//! A map of sensor names to TemperatureSensor devices
unordered_map<string, TemperatureSensor*> sensors;


// |----------------------------------------------|
// |                 Main Function                |
// |----------------------------------------------|

int main() {
	
	// Create the agent
	agent = new SimpleAgent(CUBESAT_AGENT_TEMP_NAME);
	agent->set_activity_period(SLEEP_TIME);
    agent->AddRequest("list", Request_List, "", "Returns a list of sensors");
    agent->AddRequest("config", Request_Config, "", "Returns the temperature sensor configuration");
	
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
	TemperatureSensor *sensor;
	// Initialize the temperature sensor devices using the JSON
	for (auto &sensor_obj : sensor_config.GetArray()) {
		
		name = sensor_obj["name"].GetString();
		type = sensor_obj["type"].GetString();
		
		// Create a new temperature sensor device
		sensor = agent->NewDevice<TemperatureSensor>(name);
		sensors[name] = sensor;
		
		
		// Initialize the device as a sensor
		if ( type == "sensor" ) {
			
			bus = sensor_obj["bus"].GetInt();
			cs = sensor_obj["cs"].GetInt();
			
			sensor->SetCustomProperty<ADT7311*>("handler", new ADT7311(bus, cs));
			sensor->SetCustomProperty<bool>("physical", true);
		}
		// Initialize the device as remote
		else {
			//sensor->SetCustomProperty<std::string>("source", sensor_obj["key"].GetString());
			sensor->SetCustomProperty<bool>("physical", false);
		}
		sensor->Post(sensor->utc = Time::Now());
		sensor->Post(sensor->enabled = false);
		sensor->Post(sensor->temperature = 0);
		
		// Add the temperature sensor to the telemetry log
		agent->GetLog().RegisterDevice(name, sensor)
				.RegisterProperty("utc", sensor->utc)
				.RegisterProperty("enabled", sensor->enabled)
				.RegisterProperty("temperature", sensor->temperature)
				.RegisterProperty("voltage", sensor->voltage)
				.RegisterProperty("current", sensor->current)
				.RegisterProperty("power", sensor->power);
		
	}
	
	// Finish up
	agent->Finalize();
	agent->DebugPrint();
	
	// Start executing the agent
	while ( agent->StartLoop() ) {
		
		// Update sensor readings
		for (auto it : sensors) {
			UpdateSensor(it.first);
		}
	}
	
	
	
	// Free sensor devices
	for (auto it : sensors) {
		if ( sensor->GetCustomProperty<bool>("physical") ) {
			ADT7311 *handler = sensor->GetCustomProperty<ADT7311*>("handler");
			handler->Close();
			delete handler;
		}
	}
	
	// Free the agent
	delete agent;
	
	return 0;
}


void UpdateSensor(const std::string &name) {
	
	// Fetch some information
	TemperatureSensor *sensor = sensors[name];
	bool is_physical = sensor->GetCustomProperty<bool>("physical");;
	
	// Update the timestamp
	sensor->utc = Time::Now();
	
	// Check whether the device is physical
	if ( is_physical ) {
		
		ADT7311 *handler = sensor->GetCustomProperty<ADT7311*>("handler");
		
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
			sensor->temperature = handler->GetTemperature();
			
			printf("Sensor '%s' finished converting: %.2f C\n", name.c_str(), (float)sensor->temperature);
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
		
		
		if ( agent_pycubed.Connect() ) {
			
			string source_id = sensor->GetCustomProperty<string>("source");
            auto values = agent->send_request_getvalue(agent_pycubed, {source_id});
			
			// Check if the request failed
			if ( values.empty() )
				return;
			
			sensor->temperature = values[source_id].nvalue;
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



float Request_Sensor_Temperature(TemperatureSensor *sensor) {
	return sensor->temperature;
}

bool Request_Connected(TemperatureSensor *sensor) {
	return sensor->enabled;
}

string Request_List() {
	stringstream ss;
	
	
	// Generate a JSON list of sensor info
	ss << "{";
	for (auto it : sensors) {
		ss <<	"\"" << it.first << "\": {";
		ss <<		"\"utc\": " << it.second->utc << ", ";
		ss <<		"\"temp\": " << it.second->temperature << ",";
		ss <<		"\"enabled\": " << (it.second->enabled ? "true" : "false");
		ss <<	"},";
	}
	ss << "}";
	
	return ss.str();
}
string Request_Config() {
	string config;
	GetConfigString("temp_sensors", config);
	return config;
}

