
// Internal headers
#include "SimpleAgent/SimpleAgent.h"

#include <iostream>
#include <fstream>
#include <unordered_map>

#include "utility/Configuration.h"

#define SLEEP_TIME 10

using namespace std;
using namespace artemis;
using namespace rapidjson;


struct TemperatureDependency {
	//! The name of this dependency
	string name;
	
	//! The COSMOS state of health key to get
	//! temperatures from for this dependency
	string source;
	
	//! The temperature to enable the heater at
	float enable_temp;
	
	//! The temperature to disable the heater at
	float disable_temp;
	
	//! The current temperature
	float current_temp;
};


// |----------------------------------------------|
// |                  Prototypes                  |
// |----------------------------------------------|

/**
 * @brief Retrieves the temperatures from agent_temp
 * @return True if the temperatures were successfully obtained
 */
bool GetTemperatures();

/**
 * @brief Switchs a heater on or off via agent_switch
 * @param enabled Set to true to enable a heater, or false to disable a heater
 * @return True if successful, false if not
 */
bool SetHeaterState(bool enabled);

/**
 * @brief Enables the heater
 */
bool Request_Enable();

/**
 * @brief Disables the heater
 */
bool Request_Disable();

/**
 * @brief Gets the state of the heater
 * @return "on" if it's on, "off" if it's off
 */
string Request_Get();

/**
 * @brief Returns the heater configuration JSON
 * @return The configuration JSON string
 */
string Request_Config();

// |----------------------------------------------|
// |                   Variables                  |
// |----------------------------------------------|

//! The agent
SimpleAgent *agent;

//! The heater device
Heater *heater;

//! The switch which controls the heater
string heater_switch;

//! A list of the COSMOS names for temperature dependencies
vector<string> agent_temp_keys;

//! Represents the temperature dependencies
vector<TemperatureDependency> temperature_dependencies;

//! Holds the parsed heater configuration
Document heater_config;

// |----------------------------------------------|
// |                 Main Function                |
// |----------------------------------------------|

int main(int argc, char** argv) {
	
	// Create the agent
	agent = new SimpleAgent(CUBESAT_AGENT_HEATER_NAME, CUBESAT_NODE_NAME, true);
	agent->SetLoopPeriod(SLEEP_TIME);
    agent->AddRequest({"on", "enable"}, Request_Enable, "", "Enables the heater");
    agent->AddRequest({"off", "disable"}, Request_Disable, "", "Disables the heater");
    agent->AddRequest("get", Request_Get, "", "Returns the state of the heater");
    agent->AddRequest("config", Request_Config, "", "Returns the heater configuration");
	
	
	// Parse the configuration
	if ( !GetConfigDocument("heater", heater_config) ) {
		printf("Fatal: failed to find configuration file\n");
		return 1;
	}
	heater_switch = heater_config["switch"].GetString();
	
	// Add the heater device
	heater = agent->NewDevice<Heater>(heater_config["name"].GetString());
	heater->Post(heater->utc = Time::Now());
	heater->Post(heater->enabled = false);

	// Load all temperature dependencies
	for (auto &sensor_obj : heater_config["sensors"].GetArray()) {
		
		// Load the temperature dependecy
		TemperatureDependency dependency;
		dependency.name = sensor_obj["name"].GetString();
		dependency.source = sensor_obj["source"].GetString();
		dependency.enable_temp = sensor_obj["enable_temp"].GetFloat();
		dependency.disable_temp = sensor_obj["disable_temp"].GetFloat();
		dependency.current_temp = 1e6; // A temporary value
		
		// Store the dependency
		temperature_dependencies.push_back(dependency);
		
		// Store the dependency key
		agent_temp_keys.push_back(dependency.source);
	}
	
	// Initialize the telemetry log
	agent->GetLog().RegisterDevice("heater", heater)
			.RegisterProperty("utc", heater->utc)
			.RegisterProperty("enabled", heater->enabled)
			.RegisterProperty("voltage", heater->voltage)
			.RegisterProperty("current", heater->current)
			.RegisterProperty("power", heater->power);
	
	// Let the agent know all the devices have been set up
	agent->Finalize();
	agent->DebugPrint();
	
	// Make sure the heater is disabled
	SetHeaterState(false);
	
	
	// Start executing the agent
	while ( agent->StartLoop() ) {
		
		// Update sensor readings
		if ( !GetTemperatures() )
			continue;
		
		
		bool any_enable = false;
		
		// Flag to indicate whether all temperature dependencies
		// indicate that the heater should be disabled
		bool all_disable = true;
		
		// Check if the heater should be enabled
		for (TemperatureDependency &dependency : temperature_dependencies) {
			if ( dependency.current_temp < dependency.enable_temp ) {
				printf("Warning: temperature of '%s' (%.2f C) is too low.\n",
					   dependency.name.c_str(), dependency.current_temp - 273.15);
				any_enable = true;
			}
			else if ( dependency.current_temp < dependency.disable_temp ) {
				all_disable = false;
			}
		}
		
		// If any temperatures are too low, enable the heater
		if ( any_enable && !heater->enabled ) {
			SetHeaterState(true);
		}
		// If all temperatures are above the disable temperature, disable the heater
		else if ( all_disable && heater->enabled ) {
			SetHeaterState(false);
		}
		
		heater->utc = Time::Now();
	}
	
	return 0;
}


bool GetTemperatures() {
	static RemoteAgent agent_temp = agent->FindAgent(CUBESAT_AGENT_TEMP_NAME);
	
	// Attempt to reconnect to agent_temp
	if ( !agent_temp.Connect() ) {
		return false;
	}
	
	// Get the temperature and timestamp values from agent_temp
	auto values = agent_temp.GetCOSMOSValues(agent_temp_keys);
	
	// Check if the values were not retrieved
	if ( values.empty() ) {
		printf("Failed to get temperatures from agent_temp\n");
		return false;
	}
	
	// Store the temperatures
	for (TemperatureDependency &dependency : temperature_dependencies) {
		dependency.current_temp = values[dependency.source].nvalue;
	}
	
	return true;
}


bool SetHeaterState(bool enabled) {
	static RemoteAgent agent_switch = agent->FindAgent(CUBESAT_AGENT_SWITCH_NAME);
	
	cout << "Attempting to " << (enabled ? "enable" : "disable") << " heater" << endl;
	
	// Check if agent_switch has been connected to yet
	if ( !agent_switch.Connect() ) {
		return false;
	}
	
	
	
	
	// Send a request to enable or disable the heater
	string response = agent_switch.SendDeviceRequest(heater_switch, enabled ? "on" : "off");
	
	// Check if an error occurred
	if ( response.empty() ) {
		printf("Failed to send enable/disable request to agent_switch\n");
		return false;
	}
	
	// Set the heater properties
	heater->utc = Time::Now();
	heater->enabled = enabled;
	
	// Indicate success
	return true;
}


bool Request_Enable() {
	return SetHeaterState(true);
}
bool Request_Disable() {
	return SetHeaterState(false);
}
string Request_Get() {
	return heater->enabled ? "\"on\"" : "\"off\"";
}
string Request_Config() {
	string config;
	GetConfigString("heater", config);
	return config;
}

