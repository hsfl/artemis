
#include "SimpleAgent.h"

using namespace std;
using namespace artemis;

SimpleAgent* SimpleAgent::instance = nullptr;

SimpleAgent::SimpleAgent(const std::string &name, std::string node,
			bool crash_if_not_open) : Agent(node, name), telem_log(name, node) {
	
	// Throw an exception if another SimpleAgent already is running
	if ( SimpleAgent::instance != nullptr ) {
		throw MultipleSimpleAgentException("Another SimpleAgent is already running in this process");
	}
	SimpleAgent::instance = this;
	
	
	// Check if the agent started successfully
	if ( !IsOpen() ) {
		printf("Could not start agent '%s' on node '%s'\n", name.c_str(), node.c_str());
		
		if ( crash_if_not_open )
			exit(1);
	}
	else {
		AddRequest("print", _Request_DebugPrint, "Prints all added devices and requests");
	}
	
	// Reset the telemetry log
	telem_log.Purge();
	
	
	// Set some initial loop properties
	this->loop_started = false;
	SetLoopPeriod(1);
}

//===============================================================
//======================== MISCELLANEOUS ========================
//===============================================================

void SimpleAgent::CrashIfNotOpen() {
	
	// Crash if the agent isn't running
	if ( !IsOpen() ) {
		printf("Fatal: failed to open agent '%s' on node '%s'\n",
			   agentName.c_str(), nodeName.c_str());
		exit(1);
	}
}

void SimpleAgent::Finalize() {
		
	// Add the posted properties from each device
	std::vector<std::string> keys;
	
	for (auto device_pair : devices) {
		device_pair.second->StorePostedProperties(keys);
	}
	

	// Format the state of health string using a stringstream
	std::stringstream ss;
	
	// Add all posted properties
	ss << "{";
	for (const std::string &key : keys) {
		ss << "\"" << key << "\",";
	}
	for (auto node_property_pair : node_properties) {
		if ( node_property_pair.second.post )
			ss << "\"" << node_property_pair.second.cosmos_name << "\", ";
	}
	ss << "}";
	
	
	// Set the state of health string
	this->set_sohstring(ss.str());
}


bool SimpleAgent::StartLoop() {
	// Check if the agent is actually running
	if ( !this->IsRunning() )
		return false;
	
	// Check if this is the first time this function has been called
	if ( !loop_started ) {
		loop_started = true;
		
		// Since this isn't the first iteration, idle until the next one should start
		this->finish_active_loop();
	}
	
	// Idle until the next loop should start
	this->finish_active_loop();
	
	// Update the node timestamp
	this->cinfo->node.utc = currentmjd();
	
	// Flush the telemetry log
	telem_log.WriteEntries();
	
	// Start the active loop
	this->start_active_loop();
	
	return true;
}

//===============================================================
//======================== REMOTE AGENTS ========================
//===============================================================

RemoteAgent SimpleAgent::FindAgent(const std::string &name, const std::string &node, float wait_sec, bool crash_if_failed) {
	
	// Try to find the other agent
	beatstruc beat = this->find_agent(node, name, wait_sec);
	
	// Check if an error occurred
	if ( beat.utc == 0. || !beat.exists ) {
		printf("Could not find agent '%s' running on node '%s'\n", name.c_str(), node.c_str());
		
		if ( crash_if_failed )
			exit(1);
	}
	
	// Return the other agent
	return RemoteAgent(node, name, GetComplexAgent(), beat);
}

//===============================================================
//========================== REQUESTS ===========================
//===============================================================



//===============================================================
//============================ DEBUG ============================
//===============================================================

void SimpleAgent::DebugPrint(bool print_all) const {
	
	// Print all devices
	printf("Devices\n");
	for (auto device_pair : devices) {
		printf("|\t| Device '%s'\n", device_pair.first.c_str());
		device_pair.second->DebugPrint();
	}
	
	// Print all requests
	printf("Requests\n");
	for (auto request_pair : requests)
		printf("|\t| Request '%s': %s\n", request_pair.first.c_str(), request_pair.second->GetSignatureString().c_str());
	
	// Print all node properties
	printf("Node Properties\n");
	for (auto node_property_pair : node_properties) {
		if ( print_all || node_property_pair.second.post )
			printf("|\t| Property '%s' (aka %s): %s\n",
				   node_property_pair.second.readable_name.c_str(),
				   node_property_pair.second.cosmos_name.c_str(),
				   node_property_pair.second.value_string.c_str());
	}
}

std::string SimpleAgent::GetDebugString(bool print_all) const {
	
	std::stringstream ss;
	
	// Print all devices
	ss << "Devices\n";
	for (auto device_pair : devices) {
		ss << "|\t| Device '" << device_pair.first << "'\n";
		device_pair.second->GetDebugString(ss);
	}
	
	// Print all requests
	ss << "Requests\n";
	for (auto request_pair : requests) {
		ss << "|\t| Request '" << request_pair.first << "': " << request_pair.second->GetSignatureString() << std::endl;
	}
	
	// Print all node properties
	ss << "Node Properties\n";
	for (auto node_property_pair : node_properties) {
		if ( print_all || node_property_pair.second.post )
			ss << "|\t| Property '" << node_property_pair.second.readable_name
				  << "' (aka " << node_property_pair.second.cosmos_name
				  << "): " << node_property_pair.second.value_string << "\n";
	}
	
	return ss.str();
}


//===============================================================
//=========================== SUPPORT ===========================
//===============================================================

int32_t artemis::RequestProxy(std::string &request_str_, std::string &response, Agent *agent_) {
	
	std::string request_str = request_str_;
	
	// The request string is messed up for some reason, so we need to fix it:
	request_str.assign(request_str.c_str(), strlen(request_str.c_str()));
	
	// Split the request string into arguments
	std::vector<std::string> arguments;
	istringstream iss(request_str);
	string arg;
	
	while ( getline(iss, arg, ' ') )
		arguments.push_back(arg);
	
	// Get the request name and remove it from the argument list
	std::string request_name = arguments[0];
	arguments.erase(arguments.begin());
	
	// Find the SimpleAgent request
	SimpleAgent *agent = SimpleAgent::GetInstance();
	AgentRequest *request = agent->GetRequest(request_name);
	
	// Make sure the request exists
	if ( request == nullptr ) {
		printf("[SimpleAgent] No matching request named '%s'\n", request_name.c_str());
		return -1;
	}
	
	// Clear the request error
	agent->RaiseRequestError("");
	
	// Call the request
	std::string response_str;
	bool success = request->Invoke(arguments, response_str);
	
	// Check if the request callback raised an error
	const std::string& request_err = agent->GetLastRequestError();
	
	// Print the error if one was raised
	if ( !request_err.empty() ) {
		response = request_err;
		
		return 0;
	}
	else {
		// Print the response
		response = response_str.c_str();
		
		// Return the status of the operation
		return success;
	}
}



std::string artemis::_Request_DebugPrint() {
	return SimpleAgent::GetInstance()->GetDebugString();
}


