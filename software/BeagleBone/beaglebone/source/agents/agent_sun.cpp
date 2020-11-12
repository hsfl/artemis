
// Internal headers
#include "SimpleAgent/SimpleAgent.h"
#include "device/OPT3001.h"

#include "rapidjson/document.h"

#include <iostream>
#include <fstream>
#include <unordered_map>

// The interval between iterations in the run_agent() function
#define SLEEP_TIME 1


using namespace std;
using namespace cubesat;
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


// Request callbacks

float Request_Sensor_Lux(SunSensor *sensor);
bool Request_Sensor_Connected(SunSensor *sensor);
string Request_Sensor(string sensor_name);
string Request_List();


// |----------------------------------------------|
// |                   Variables                  |
// |----------------------------------------------|

// The agent object which allows for communication with COSMOS
SimpleAgent *agent;

Document sensor_config;


OPT3001::Configuration default_sensor_config;
OPT3001::Configuration active_config;

//! A map of sensor names to SunSensor devices
unordered_map<string, SunSensor*> sensors;



//! The sun sensor JSON configuration
const char *sensor_config_json =
#include "config/sun_sensors.json"
;

// |----------------------------------------------|
// |                 Main Function                |
// |----------------------------------------------|

int main() {
	
	// Create the agent
	agent = new SimpleAgent(CUBESAT_AGENT_SUNSENSOR_NAME);
	agent->SetLoopPeriod(SLEEP_TIME);
	agent->AddRequest("sensor", Request_Sensor, "Returns the status of a sensor");
	agent->AddRequest("list", Request_List, "Returns a list of sensors");
	
	
	// Parse the sensor configuration
	sensor_config.Parse(sensor_config_json);
	
	string name;
	int bus, address;
	Vec3 orientation;
	SunSensor *sensor;
	
	// Initialize the sun sensor devices using the parsed JSON
	for (auto &sensor_obj : sensor_config.GetArray()) {
		
		// Grab the JSON fields for this sun sensor
		name = sensor_obj["name"].GetString();
		bus = sensor_obj["bus"].GetInt();
		address = sensor_obj["address"].GetInt();
		orientation = Vec3(sensor_obj["orientation"].GetArray()[0].GetInt(),
						   sensor_obj["orientation"].GetArray()[1].GetInt(),
						   sensor_obj["orientation"].GetArray()[2].GetInt());
		
		// Create a new sun sensor device
		sensor = agent->NewDevice<SunSensor>(name);
		sensor->SetCustomProperty<OPT3001*>("handler", new OPT3001(bus, address));
		sensor->SetCustomProperty<Vec3>("orientation", orientation);
		
		sensor->Post(sensor->utc = Time::Now());
		sensor->Post(sensor->enabled = false); // true = connected, false = not connected
		sensor->Post(sensor->temperature = 0); // Represents the lux readings
		
		// Add device requests
		sensor->AddRequest("connected", Request_Sensor_Connected, "Returns true if the sun sensor is connected");
		sensor->AddRequest("lux", Request_Sensor_Lux, "Returns the lux of the sun sensor");
		
	}
	
	agent->Finalize();
	agent->DebugPrint();
	
	// Run the main loop for this agent
	while ( agent->StartLoop() ) {
		
		// Update the sensors
		for (auto pair : sensors) {
			UpdateSensor(pair.first);
		}
		
	}
	
	// Finish up with the sensors
	for (auto pair : sensors) {
		OPT3001 *handler = pair.second->GetCustomProperty<OPT3001*>("handler");
		handler->Close();
		delete handler;
	}
	
	// Delete the agent
	delete agent;
	
	return 0;
}


void UpdateSensor(const std::string &name) {
	SunSensor *sensor = sensors[name];
	OPT3001 *opt3001 = sensor->GetCustomProperty<OPT3001*>("handler");
	
	sensor->utc = Time::Now();
	
	// Make sure the sensor is open
	if ( !opt3001->IsOpen() ) {
		printf("Opening sensor '%s' on I2C-%d at address 0x%02x... ",
			   name.c_str(), opt3001->GetBusAddr(), opt3001->GetDeviceAddr());
		
		if ( opt3001->Open() < 0 ) {
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
		sensor->temperature = opt3001->GetLux();
		
		printf("Sensor '%s' finished converting: %.2f lx\n", name.c_str(), (float)sensor->voltage);
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

float Request_Sensor_Lux(SunSensor *sensor) {
	return sensor->temperature;
}
bool Request_Sensor_Connected(SunSensor *sensor) {
	OPT3001 *handler = sensor->GetCustomProperty<OPT3001*>("handler");
	return handler != nullptr && handler->IsOpen();
}

string Request_Sensor(string sensor_name) {
	SunSensor *sensor = sensors[sensor_name];
	
	// Generate the response
	stringstream ss;
	ss << "{" << std::endl;
	ss << "\t\"name\": \"" << sensor_name << "\", " << std::endl;
	ss << "\t\"utc\": " << (double)sensor->utc << ", " << std::endl;
	ss << "\t\"lux\": " << (float)sensor->temperature << ", " << std::endl;
	ss << "\t\"connected\": " << (sensor->enabled ? "true" : "false") << std::endl;
	ss << "}" << std::endl;
	
	return ss.str();
}

string Request_List() {
	
	SunSensor *sensor;
	
	stringstream ss;
	ss << "[";
	
	for (auto pair : sensors) {
		sensor = pair.second;
		
		ss << "\t{" << std::endl;
		ss << "\t\t\"name\": \"" << pair.first << "\", " << std::endl;
		ss << "\t\t\"utc\": " << (double)sensor->utc << ", " << std::endl;
		ss << "\t\t\"lux\": " << (float)sensor->temperature << ", " << std::endl;
		ss << "\t\t\"connected\": " << (sensor->enabled ? "true" : "false") << std::endl;
		ss << "\t}," << std::endl;
	}
	
	ss << "]";
	
	return ss.str();
}
