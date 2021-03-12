
#include "SimpleAgent/SimpleAgent.h"
#include "device/GPIO.h"
//#include "device/switch.h"

#include "utility/Configuration.h"

#include <iostream>
#include <fstream>
#include <sstream>

// The interval between iterations in the run_agent() function
#define SLEEP_TIME 5

using namespace std;
using namespace artemis;
using namespace rapidjson;


// |----------------------------------------------|
// |                  Prototypes                  |
// |----------------------------------------------|

/**
 * @brief (Device Request) Enables a switch
 * @param sw The switch device
 */
void Request_Switch_On(Switch *sw);

/**
 * @brief (Device Request) Disables a switch
 * @param sw The switch device
 */
void Request_Switch_Off(Switch *sw);

/**
 * @brief (Device Request) Returns the state of a switch
 * @param sw The switch device
 */
string Request_Switch_State(Switch *sw);

/**
 * @brief (Agent Request) Returns a JSON-formatted list of switches
 * @return The list as a JSON-formatted string
 */
string Request_List();

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

//! Holds the parsed switch configuration
Document switch_config;

//! A map of switch names to Switch devices
std::unordered_map<std::string, Switch*> switches;

// |----------------------------------------------|
// |                 Main Function                |
// |----------------------------------------------|

int main(int argc, char** argv) {
	
	// Create the agent
	agent = new SimpleAgent(CUBESAT_AGENT_SWITCH_NAME);
	agent->set_activity_period(SLEEP_TIME);
    agent->AddRequest("list", Request_List, "", "Lists available switches");
    agent->AddRequest("config", Request_Config, "", "Returns the switch configuration");
	
	// Parse the switch configuration
	if ( !GetConfigDocument("switches", switch_config) ) {
		printf("Fatal: failed to find configuration file\n");
		return 1;
	}
	assert(switch_config.IsArray());
	
	
	Switch *sw;
	GPIO *gpio;
	string switch_name, switch_pin;
	bool default_state;
	
	// Loop over the JSON array of switch configurations
	for (auto &switch_obj : switch_config.GetArray()) {
		
		// Grab the switch configuration
		switch_name = switch_obj["name"].GetString();
		switch_pin = switch_obj["pin"].GetString();
		default_state = switch_obj["default_state"].GetBool();
		
		// Create the GPIO handler for the switch
		gpio = new GPIO(switch_pin.c_str());
		gpio->SetMode(GPIOMode::Output);
		gpio->DigitalWrite(default_state ? GPIOValue::High : GPIOValue::Low);
		
		// Create the switch device
		sw = agent->NewDevice<Switch>(switch_name);
		
		// Store the switch configuration
		sw->SetCustomProperty<std::string>("pin", switch_pin);
		sw->SetCustomProperty<GPIO*>("handler", gpio);
		
		// Post some properties
		sw->Post(sw->utc = Time::Now());
		sw->Post(sw->voltage = default_state ? 3.3 : 0.0);
		sw->Post(sw->enabled = false);
		
		// Add device requests
        sw->AddRequest("on", Request_Switch_On, "\n\t\tTurns on the switch");
        sw->AddRequest("off", Request_Switch_Off, "\n\t\tTurns off the switch");
        sw->AddRequest("state", Request_Switch_State, "\n\t\tReturns the state of the switch");
		
		// Store the switch device by name
		switches[switch_name] = sw;
		
		
		// Add the switch to the telemetry log
		agent->GetLog().RegisterDevice(switch_name, sw)
				.RegisterProperty("utc", sw->utc)
				.RegisterProperty("enabled", sw->enabled)
				.RegisterProperty("voltage", sw->voltage)
				.RegisterProperty("current", sw->current)
				.RegisterProperty("power", sw->power);
	}
	
	
	// Finish up the initialization
	agent->Finalize();
	agent->DebugPrint();
	
	// Run the main loop for this agent
	while ( agent->StartLoop() ) {
		
		
		// Update switch info
		for (auto pair : switches) {
			gpio = pair.second->GetCustomProperty<GPIO*>("handler");
			
			pair.second->utc = Time::Now();
			pair.second->enabled = gpio->DigitalRead() == GPIOValue::High;
			pair.second->voltage = pair.second->enabled ? 3.3 : 0;
		}
	}
	
	
	// Delete GPIO handlers
	for (auto pair : switches)
		delete pair.second->GetCustomProperty<GPIO*>("handler");
	
	delete agent;
	
	
	return 0;
}



// |----------------------------------------------|
// |                   Requests                   |
// |----------------------------------------------|

void Request_Switch_On(Switch *sw) {
	GPIO *gpio = sw->GetCustomProperty<GPIO*>("handler");
	gpio->DigitalWrite(GPIOValue::High);
	sw->utc = Time::Now();
	sw->enabled = true;
	sw->voltage = 3.3;
}

void Request_Switch_Off(Switch *sw) {
	GPIO *gpio = sw->GetCustomProperty<GPIO*>("handler");
	gpio->DigitalWrite(GPIOValue::Low);
	sw->utc = Time::Now();
	sw->enabled = false;
	sw->voltage = 0;
}

string Request_Switch_State(Switch *sw) {
	return sw->enabled ? "on" : "off";
}

string Request_List() {
	stringstream ss;
	GPIO *handler;
	
	// Generate JSON-formatted switch info
	ss << "{";
	for (auto pair : switches) {
		handler = pair.second->GetCustomProperty<GPIO*>("handler");
		
		ss << '"' << pair.first << "\": {" << std::endl;
		ss <<	"\"enabled\": " << (pair.second->enabled ? "true" : "false") << ", " << std::endl;
		ss <<	"\"pin\": \"" << handler->GetPinKey() << "\"" << std::endl;
		ss << "},";
	}
	ss << "}";
	
	return ss.str();
}

string Request_Config() {
	string config;
	GetConfigString("switches", config);
	return config;
}
