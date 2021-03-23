
#include "SimpleAgent/SimpleAgent.h"
#include "SimpleAgent/Telemetry.h"

 
using namespace std;
using namespace artemis;


TelemetryLog telemlog("telemlog", "cubesat");

bool Request_Purge();
//bool Request_Purge() {
//	return telemlog.Purge();
//}

bool Request_Finalize();
//bool Request_Finalize() {
//	return telemlog.Finalize();
//}


int main(int argc, char ** argv) {
	
	int32_t error;
    
    
	SimpleAgent *agent = new SimpleAgent("telemlog", "cubesat");
	agent->add_request("purge", Request_Purge, "", "");
	agent->add_request("finalize", Request_Finalize, "", "");
	agent->set_activity_period(1);
	
	
	devicestruc *tsen = agent->add_device("tsen", DeviceType::TSEN, error);
    if (error < 0){
        printf("Error adding temp sensor\n");
    }
    
    devicestruc *gps = agent->add_device("gps", DeviceType::GPS, error);
    if (error < 0){
        printf("Error adding gps\n");
    }
    
    vector<string> soh_props = {"tsen", {"utc", "temp"}, "gps", {"utc", "geods", "geocv"}};
    agent->append_soh_list(soh_props);
//    telemlog.RegisterDevice("tsen", tsen)
//            .RegisterProperty("utc", tsen->utc)
//			.RegisterProperty("temp", tsen->temperature);
	
//	telemlog.RegisterDevice("ssen", gps)
//			.RegisterProperty("utc", gps->utc)
//			.RegisterProperty("pos", gps->location)
//			.RegisterProperty("vel", gps->velocity);
	
	
	int i = 0;
	
	while ( agent->StartLoop() ) {
		++i;
		
		tsen->utc = Time::Now();
		gps->utc = Time::Now();
		
        tsen->temp = tsen->temp + 1;
		
        gps->geods = Location(i * 2, i / 2, i);
        gps->geocv = Vec3(i / 2, i * 2, i + 1);
		
		
		telemlog.WriteEntries();
		
	}

	
    return 0;
}

bool Request_Purge(){
    return telemlog.Purge();
}


bool Request_Finalize(){
    return telemlog.Finalize();
}
