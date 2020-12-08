
#include "SimpleAgent/SimpleAgent.h"
#include "SimpleAgent/Telemetry.h"

 
using namespace std;
using namespace artemis;


TelemetryLog telemlog("telemlog", "cubesat");


bool Request_Purge() {
	return telemlog.Purge();
}

bool Request_Finalize() {
	return telemlog.Finalize();
}


int main(int argc, char ** argv) {
	
	
	SimpleAgent *agent = new SimpleAgent("telemlog", "cubesat");
	agent->AddRequest("purge", Request_Purge);
	agent->AddRequest("finalize", Request_Finalize);
	agent->SetLoopPeriod(1);
	
	
	TemperatureSensor *tsen = agent->NewDevice<TemperatureSensor>("tsen");
	GPS *gps = agent->NewDevice<GPS>("gps");
	
	telemlog.RegisterDevice("tsen", tsen)
			.RegisterProperty("utc", tsen->utc)
			.RegisterProperty("temp", tsen->temperature);
	
	telemlog.RegisterDevice("ssen", gps)
			.RegisterProperty("utc", gps->utc)
			.RegisterProperty("pos", gps->location)
			.RegisterProperty("vel", gps->velocity);
	
	
	int i = 0;
	
	while ( agent->StartLoop() ) {
		++i;
		
		tsen->utc = Time::Now();
		gps->utc = Time::Now();
		
		tsen->temperature = tsen->temperature + 1;
		
		gps->location = Location(i * 2,	i / 2, i);
		gps->velocity = Vec3(i / 2, i * 2, i + 1);
		
		
		telemlog.WriteEntries();
		
	}
	
	
	
	
	
	
    return 0;
}

