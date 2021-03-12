
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
 * @return 0 if the temperatures were successfully obtained, error otherwise
 */
int32_t GetTemperatures();

/**
 * @brief Switchs a heater on or off via agent_switch
 * @param enabled Set to true to enable a heater, or false to disable a heater
 * @return 0 if sucessful, error otherwise
 */
int32_t SetHeaterState(bool enabled);

/**
 * @brief Enables the heater
 */
string Request_Enable(int32_t &error);

/**
 * @brief Disables the heater
 */
string Request_Disable(int32_t &error);

/**
 * @brief Gets the state of the heater
 * @return "on" if it's on, "off" if it's off
 */
string Request_GetHeaterState(int32_t &error);

/**
 * @brief Returns the heater configuration JSON
 * @return The configuration JSON string
 */
string Request_Config(int32_t &error);

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
    agent->set_activity_period(SLEEP_TIME);
    agent->add_request("enable", Request_Enable, "", "Enables the heater");
    agent->add_request("on", Request_Enable, "", "Enables the heater");
    agent->add_request( "disable", Request_Disable, "", "Disables the heater");
    agent->add_request("off", Request_Disable, "", "Disables the heater");
    agent->add_request("get_heater_state", Request_GetHeaterState, "", "Returns the state of the heater");
    agent->add_request("config", Request_Config, "", "Returns the heater configuration");
	
	
	// Parse the configuration
	if ( !GetConfigDocument("heater", heater_config) ) {
		printf("Fatal: failed to find configuration file\n");
		return 1;
	}
	heater_switch = heater_config["switch"].GetString();
	
	// Add the heater device
    int32_t error = 0;
    string devname_heater = heater_config["name"].GetString();
    devicestruc* heater = agent->add_device(devname_heater, DeviceType::HTR, error);
    heater->utc = Time::Now();
    heater->enabled = false;

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
    vector<string> soh_props = {"utc","enabled","volt","amp","power"};

	
    agent->append_soh_list(devname_heater, soh_props);
    agent->set_soh();
	agent->DebugPrint();
	
	// Make sure the heater is disabled
	SetHeaterState(false);
	
	
	// Start executing the agent
	while ( agent->StartLoop() ) {
		
		// Update sensor readings
        if ( (error = GetTemperatures()) < 0 )
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
            error = SetHeaterState(true);
		}
		// If all temperatures are above the disable temperature, disable the heater
		else if ( all_disable && heater->enabled ) {
            error = SetHeaterState(false);
		}
		
		heater->utc = Time::Now();
	}
	
	return 0;
}


int32_t GetTemperatures() {
    beatstruc agent_temp = agent->find_agent(agent->nodeName, CUBESAT_AGENT_TEMP_NAME);
    if(!agent_temp.exists){
        cout << "Could not locate agent_temp" << endl;
        return ErrorNumbers::COSMOS_GENERAL_ERROR_NO_ANSWER;
    }
    cout << "Sending request to agent_temp: getvalue" << endl;
    // Send a request to enable or disable the heater
    std::unordered_map<std::string, Json::Value> values = send_request_getvalue(agent_temp, agent_temp_keys);
	
	// Check if the values were not retrieved
    if ( values.size() > 0  ) {
        printf("Failed to get temperatures from agent_temp [%s]\n", cosmos_error_string(error));
        return error;
	}
	
	// Store the temperatures
	for (TemperatureDependency &dependency : temperature_dependencies) {
		dependency.current_temp = values[dependency.source].nvalue;
	}
	
    return 0;
}


int32_t SetHeaterState(bool enabled) {

    beatstruc agent_switch = agent->find_agent(agent->nodeName, CUBESAT_AGENT_SWITCH_NAME);
    if(!agent_switch.exists){
        cout << "Could not locate agent_switch" << endl;
        return ErrorNumbers::COSMOS_GENERAL_ERROR_NO_ANSWER;
    }

    string request = heater_switch + ":" + enabled ? "on" : "off";
    string response;
    cout << "Sending request to agent_switch: " << request << endl;
    // Send a request to enable or disable the heater
    int32_t error = send_request(agent_switch, request, response);

	// Check if an error occurred
    if ( error < 0 ) {
		printf("Failed to send enable/disable request to agent_switch\n");
        return error;
	}
	
	// Set the heater properties
	heater->utc = Time::Now();
	heater->enabled = enabled;
	
	// Indicate success
    return 0;
}


string Request_Enable(int32_t &error) {
    error = SetHeaterState(true);
    if(error >=0 ){
        return "Success";
    }
    return "Fail";
}
string Request_Disable(int32_t &error) {
    error = SetHeaterState(false);
    if(error >= 0){
        return "Success";
    }
    return "Fail";
}
string Request_GetHeaterState(int32_t &error) {
	return heater->enabled ? "\"on\"" : "\"off\"";
}
string Request_Config(int32_t &error) {
	string config;
	GetConfigString("heater", config);
	return config;
}

