
#include "SimpleAgent/SimpleAgent.h"
#include "device/GPIO.h"

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
string Request_Switch_On(vector<string> &args, int32_t &error);

/**
 * @brief (Device Request) Disables a switch
 * @param sw The switch device
 */
//void Request_Switch_Off(Switch *sw);
string Request_Switch_Off(vector<string> &args, int32_t &error);

/**
 * @brief (Device Request) Returns the state of a switch
 * @param sw The switch device
 */
string Request_Switch_State(vector<string> &args, int32_t &error);

/**
 * @brief (Agent Request) Returns a JSON-formatted list of switches
 * @return The list as a JSON-formatted string
 */
string Request_List(int32_t &error);

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

//! Holds the parsed switch configuration
Document switch_config;

//! A map of switch names to Switch devices
std::unordered_map<std::string, devicestruc*> switches;
std::unordered_map<std::string, GPIO*> gpios;

// |----------------------------------------------|
// |                 Main Function                |
// |----------------------------------------------|

int main(int argc, char** argv) {
    int32_t error;
	// Create the agent
	agent = new SimpleAgent(CUBESAT_AGENT_SWITCH_NAME);
	agent->set_activity_period(SLEEP_TIME);
    agent->add_request("list", Request_List, "", "Lists available switches");
    agent->add_request("config", Request_Config, "", "Returns the switch configuration");
    agent->add_request("on", Request_Switch_On, "switch_name", "Turns on the switch");
    agent->add_request("off", Request_Switch_Off, "switch_name", "Turns off the switch");
    agent->add_request("state", Request_Switch_State, "switch_name", "Gets the switch state");
	
	// Parse the switch configuration
	if ( !GetConfigDocument("switches", switch_config) ) {
		printf("Fatal: failed to find configuration file\n");
		return 1;
	}
	assert(switch_config.IsArray());
	
	
    devicestruc *sw;
	GPIO *gpio;
	string switch_name, switch_pin;
	bool default_state;

    vector<string> soh_props = {"utc","enabled","volt","amp","power"};
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
//		sw = agent->NewDevice<Switch>(switch_name);
        sw = agent->add_device(switch_name, DeviceType::SWCH, error);
		
		// Store the switch configuration
        //sw->SetCustomProperty<std::string>("pin", switch_pin);
        //sw->SetCustomProperty<GPIO*>("handler", gpio);
		
		// Post some properties
        sw->utc = Time::Now();
        sw->volt = default_state ? 3.3 : 0.0;
        sw->enabled = false;
//		sw->Post(sw->utc = Time::Now());
//		sw->Post(sw->volt = default_state ? 3.3 : 0.0);
//		sw->Post(sw->enabled = false);
		
//		// Add device requests
//        sw->AddRequest("on", Request_Switch_On, "\n\t\tTurns on the switch");
//        sw->AddRequest("off", Request_Switch_Off, "\n\t\tTurns off the switch");
//        sw->AddRequest("state", Request_Switch_State, "\n\t\tReturns the state of the switch");
		
		// Store the switch device by name
		switches[switch_name] = sw;
        gpios[switch_name] = gpio;
		
        error = append_soh_list(switch_name, soh_props);
        if(error < 0){
            printf("Error creating SOH List\n");
        }
//		agent->GetLog().RegisterDevice(switch_name, sw)
//				.RegisterProperty("utc", sw->utc)
//				.RegisterProperty("enabled", sw->enabled)
//				.RegisterProperty("voltage", sw->voltage)
//				.RegisterProperty("current", sw->current)
//				.RegisterProperty("power", sw->power);
	}
	
	
	// Finish up the initialization
    //agent->Finalize();
    agent->set_soh();
	agent->DebugPrint();
	
	// Run the main loop for this agent
	while ( agent->StartLoop() ) {
		
		
		// Update switch info
		for (auto pair : switches) {
            string switch_name = pair.first;
            gpio = gpios[switch_name];
			
			pair.second->utc = Time::Now();
			pair.second->enabled = gpio->DigitalRead() == GPIOValue::High;
            pair.second->volt = pair.second->enabled ? 3.3 : 0;
		}
	}
	
	return 0;
}



// |----------------------------------------------|
// |                   Requests                   |
// |----------------------------------------------|

string Request_Switch_On(vector<string> &args, int32_t &error) {
    if(args.size() == 0) {
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_EMPTY;
        return "\"usage: switch_name\"";
    }
    string switch_name = args[0];

    if(gpios.find(switch_name) == gpios.end()){
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_NAME;
        return "\"unknown switch\"";
    }
    GPIO *gpio = gpios[switch_name];
    gpio->DigitalWrite(GPIOValue::High);
    switches[switch_name]->utc = Time::Now();
    switches[switch_name]->enabled = false;
    switches[switch_name]->volt = 3.3;

    return "\"Success\"";
}

string Request_Switch_Off(vector<string> &args, int32_t &error)
{
    if(args.size() == 0) {
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_EMPTY;
        return "\"usage: switch_name\"";
    }
    string switch_name = args[0];
    if(gpios.find(switch_name) == gpios.end()){
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_NAME;
        return "\"unknown switch\"";
    }
    GPIO *gpio = gpios[switch_name];
	gpio->DigitalWrite(GPIOValue::Low);
    switches[switch_name]->utc = Time::Now();
    switches[switch_name]->enabled = false;
    switches[switch_name]->volt = 0;

    return "\"Success\"";
}

string Request_Switch_State(vector<string> &args, int32_t &error) {
    if(args.size() == 0) {
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_EMPTY;
        return "\"usage: switch_name\"";
    }
    string switch_name = args[0];
    if(gpios.find(switch_name) == gpios.end()){
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_NAME;
        return "\"unknown switch\"";
    }
    return switches[switch_name]->enabled ? "\"on\"" : "\"off\"";
}

string Request_List(int32_t &error) {
	stringstream ss;
    GPIO *gpio;
	
	// Generate JSON-formatted switch info
	ss << "{";
	for (auto pair : switches) {
        string switch_name = pair.first;
        gpio = gpios[switch_name];
		
		ss << '"' << pair.first << "\": {" << std::endl;
		ss <<	"\"enabled\": " << (pair.second->enabled ? "true" : "false") << ", " << std::endl;
        ss <<	"\"pin\": \"" << gpio->GetPinKey() << "\"" << std::endl;
		ss << "},";
	}
	ss << "}";
	
	return ss.str();
}

string Request_Config(int32_t &error) {
	string config;
	GetConfigString("switches", config);
	return config;
}
