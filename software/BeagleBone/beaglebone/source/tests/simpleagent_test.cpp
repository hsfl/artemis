
#include "SimpleAgent/SimpleAgent.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace artemis;

SimpleAgent *agent;

//float Temperature;



// A simple request that gives a friendly greeting
string SayHi(int32_t &error);

int main() {
    int32_t error = 0;
	
    agent = new SimpleAgent("my_agent"); // Create the SimpleAgent
	agent->set_activity_period(2); // Set the agent to run at 2 second intervals
	
	// Create a temperature sensor
    /*TemperatureSensor *my_sensor = agent->NewDevice<TemperatureSensor>("my_sensor");
	my_sensor->Post(my_sensor->utc = Time::Now()); // Set and post the UTC timestamp property
    my_sensor->Post(my_sensor->temperature = 0); // Set and post the temperature property */

    devicestruc *my_sensor;
    error = agent->add_device("my_sensor", DeviceType::TSEN, &my_sensor);
    if (error < 0){
        printf("Error adding temperature sensor\n");
    }

    vector<string> soh_props = {"utc","temp"};
    error = agent->append_soh_list("my_sensor", soh_props);
    if (error < 0){
        printf("Error creating SOH List/n");
    }

	// Post the UTC node property
    //agent->AddNodeProperty<Node::UTC>(Time::Now());
    my_sensor->utc = Time::Now();


	// Add a request that can be called externally
    //agent->AddRequest("say_hi", SayHi, "Gives you a friendly greeting",
    //				  "Prints a greeting inside the agent and returns the greeting as well");
    agent->add_request("say_hi", SayHi, "Gives you a friendly greeting", "Prints a greeting inside the agent and returns the greeting as well");

	// Finish setting up the SimpleAgent
    //agent->Finalize(); // Let the agent know we're done posting properties
    agent->set_soh();

	int counter = 0;
	
	// Here comes the main loop...
	while ( agent->StartLoop() ) {
		
		// Update the node timestamp
        //agent->utc = Time::Now();
		
		// Update values in the sensor. Since these values were posted,
		// the new values can be viewed externally
		my_sensor->utc = Time::Now(); // Set the timestamp to the current time
        my_sensor->temp = counter; // Set the temperature to a counter value
		
		// Increment the counter (in place of actually
		// doing stuff with hardware)
		++counter;
	}
	
	// Free any memory associated with the SimpleAgent
	delete agent;
	
	return 0;
}

string SayHi(int32_t &error) {
    printf("Hey there! (inside agent)\n");
    return "Hey there (outside agent)";
}
