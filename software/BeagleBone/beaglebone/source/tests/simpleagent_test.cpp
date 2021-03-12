
#include "SimpleAgent/SimpleAgent.h"

using namespace std;
using namespace artemis;

// A simple request that gives a friendly greeting
string SayHi() {
	printf("Hey there! (inside agent)\n");
	return "Hey there (outside agent)";
}

int main() {
	
	
	SimpleAgent *agent = new SimpleAgent("my_agent"); // Create the SimpleAgent
	agent->set_activity_period(2); // Set the agent to run at 2 second intervals
	
	// Create a temperature sensor
	TemperatureSensor *my_sensor = agent->NewDevice<TemperatureSensor>("my_sensor");
	my_sensor->Post(my_sensor->utc = Time::Now()); // Set and post the UTC timestamp property
	my_sensor->Post(my_sensor->temperature = 0); // Set and post the temperature property
	
	// Post the UTC node property
	agent->AddNodeProperty<Node::UTC>(Time::Now());
	
	// Add a request that can be called externally
	agent->AddRequest("say_hi", SayHi, "Gives you a friendly greeting",
					  "Prints a greeting inside the agent and returns the greeting as well");
	
	// Finish setting up the SimpleAgent
	agent->Finalize(); // Let the agent know we're done posting properties
	
	int counter = 0;
	
	// Here comes the main loop...
	while ( agent->StartLoop() ) {
		
		// Update the node timestamp
		agent->SetNodeProperty<Node::UTC>(Time::Now());
		
		// Update values in the sensor. Since these values were posted,
		// the new values can be viewed externally
		my_sensor->utc = Time::Now(); // Set the timestamp to the current time
		my_sensor->temperature = counter; // Set the temperature to a counter value
		
		// Increment the counter (in place of actually
		// doing stuff with hardware)
		++counter;
	}
	
	// Free any memory associated with the SimpleAgent
	delete agent;
	
	return 0;
}
