
#include "SimpleAgent/SimpleAgent.h"
#include "utility/files.h"

#include <iostream>


using namespace std;
using namespace artemis;

IncomingFolder incoming("ground");
OutgoingFolder outgoing("ground");



int main(int argc, char **argv) {
	
	vector<string> command_files;
	vector<int> command_ids;
	
	while ( true ) {
		
		
		command_ids = outgoing.GetCommandIDs();
		
		for (int id : command_ids) {
			outgoing.RemoveFile("cmd" + std::to_string(id));
			
			IncomingMessage msg;
			strcpy(msg.contents.command_response.response,  "Hello there!");
			msg.type = IncomingMessageType::CommandResponse;
			msg.length = offsetof(IncomingMessage, contents) + sizeof(IncomingMessage::contents.command_response.command_id) + strlen(msg.contents.command_response.response) + 1;
			msg.contents.command_response.command_id = id;
			msg.timestamp = currentmjd();
			msg.checksum = GetChecksum(msg);
			incoming.WriteMessage(msg);
			
			printf("Spoofing response to command %d\n", id);
		}
		
		
		IncomingMessage msg;
		msg.type = IncomingMessageType::IMUTelemetry;
		msg.timestamp = currentmjd();
		msg.contents.imu_telem.acceleration[0] = rand() % 10000;
		msg.contents.imu_telem.acceleration[1] = rand() % 10000;
		msg.contents.imu_telem.acceleration[2] = rand() % 10000;
		msg.contents.imu_telem.magnetic_field[0] = rand() % 10000;
		msg.contents.imu_telem.magnetic_field[1] = rand() % 10000;
		msg.contents.imu_telem.magnetic_field[2] = rand() % 10000;
		msg.contents.imu_telem.angular_velocity[0] = rand() % 10000;
		msg.contents.imu_telem.angular_velocity[1] = rand() % 10000;
		msg.contents.imu_telem.angular_velocity[2] = rand() % 10000;
		msg.length = offsetof(IncomingMessage, contents) + sizeof(msg.contents.imu_telem);
		msg.checksum = GetChecksum(msg);
		incoming.WriteMessage(msg);
		
		sleep(1);
	}
	
	
	
	
}



