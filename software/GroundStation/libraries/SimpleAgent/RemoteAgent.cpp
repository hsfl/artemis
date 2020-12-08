
#include "RemoteAgent.h"

using namespace std;
using namespace cubesat;


bool RemoteAgent::Connect(float wait_sec, bool crash_if_failed) {
	
	// Indicate success if the agent is already open
	if ( IsOpen() )
		return true;
	
	// Find the agent
	beat = agent->find_agent(node_name, agent_name, wait_sec);
	
	// Check if an error occurred
	if ( !IsOpen() ) {
		printf("Could not find agent '%s' running on node '%s'\n", agent_name.c_str(), node_name.c_str());
		
		if ( crash_if_failed )
			exit(1);
	}
	
	return IsOpen();
}

std::unordered_map<std::string, Json::Value> RemoteAgent::GetCOSMOSValues(std::vector<std::string> keys) {
	std::unordered_map<std::string, Json::Value> values;
	
	// Return default values if the agent isn't connected
	if ( !IsOpen() ) {
		return values;
	}
	
	// Call the request
	std::string output;
	int status = agent->send_request(beat, "soh", output, wait_time);
	
	// Check if an error occurred
	if ( status < 0 ) {
		beat.utc = 0.;
		beat.exists = false;
		printf("Error sending request to [%s:%s]: %s\n", node_name.c_str(), agent_name.c_str(), cosmos_error_string(status).c_str());
		return values;
	}
	
	// Parse the output
	Json jresult;
	status = jresult.extract_object(output);
	
	
	if ( status >= 0 ) {
		
		// For now, just store all of the returned values
		for (Json::Member member : jresult.Members) {
			values[member.value.name] = member.value;
		}
	}
	
	return values;
}


