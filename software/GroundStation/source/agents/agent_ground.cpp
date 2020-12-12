
// Internal headers
#include "SimpleAgent/SimpleAgent.h"
#include "utility/files.h"

#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace artemis;
using namespace std;

//! A command ID used to identify responses to specific commands
using CommandID = decltype(IncomingMessage::contents.command_response.command_id);

//! The agent
SimpleAgent *agent;

IMU *imu;
GPS *gps;
TemperatureSensor *temp_sensors[5];
SunSensor *sun_sensors[6];

//! A queue of incoming messages
queue<IncomingMessage> incoming_messages;
//! A queue of outgoing messages
queue<OutgoingMessage> outgoing_messages;
//! A list of commands that have not received responses yet
std::vector<CommandID> waiting_command_ids;

IncomingFolder incoming("ground");
OutgoingFolder outgoing("ground");



void FetchOutgoingMessages();
void FetchIncomingMessages();

/**
 * @brief Handles the next incoming message
 * @return True if there are more messages in the queue
 */
bool HandleNextIncomingMessage();

void SendNextOutgoingMessage();



int main(int argc, char *argv[]) {
	
	// Create the agent
	agent = new SimpleAgent("ground", "ground");
	agent->SetLoopPeriod(1);
	
	// Add devices
	imu = agent->NewDevice<IMU>("imu");
	imu->Post(imu->utc = 0);
	imu->Post(imu->magnetic_field = Vec3(0, 0, 0));
	imu->Post(imu->acceleration = Vec3(0, 0, 0));
	imu->Post(imu->angular_velocity = Vec3(0, 0, 0));
	
	gps = agent->NewDevice<GPS>("gps");
	gps->Post(gps->utc = 0);
	gps->Post(gps->location = Location(0, 0, 0));
	gps->Post(gps->velocity = Vec3(0, 0, 0));
	gps->Post(gps->satellites_used = 0);
	
	
	agent->Finalize();
	agent->DebugPrint();
	
	
	while ( agent->StartLoop() ) {
		
		// Fetch outgoing messages from the outgoing folder
		FetchOutgoingMessages();
		// Fetch incoming messages from the radio
		FetchIncomingMessages();
		
		// Go through the incoming messages
		while ( HandleNextIncomingMessage() );
		
		// Send outgoing messages through the radio
		while ( outgoing_messages.size() != 0 )
			SendNextOutgoingMessage();
		
	}
	
	delete agent;
	
	
	
	return 0;
}

void FetchIncomingMessages() {
	// Communicate with the radio, then push the received
	// messages to the incoming queue
}

void FetchOutgoingMessages() {
	
	
	vector<string> files;
	
	
	OutgoingMessage out_msg;
	files = outgoing.GetAllFiles();
	for (const string &file : files) {
		if ( outgoing.ReadMessage(file, out_msg) )
			outgoing_messages.push(out_msg);
		outgoing.RemoveFile(file);
	}
}

bool HandleNextIncomingMessage() {
	
	if ( incoming_messages.size() == 0 )
		return false;
	
	// Get the next element
	IncomingMessage message = incoming_messages.front();
	incoming_messages.pop();
	
	switch ( message.type ) {
		case IncomingMessageType::IMUTelemetry:
			printf("Received IMU telemetry message\n");
			imu->utc = message.timestamp;
			imu->acceleration = Vec3(message.contents.imu_telem.acceleration[0],
					message.contents.imu_telem.acceleration[1],
					message.contents.imu_telem.acceleration[2]);
			imu->angular_velocity = Vec3(message.contents.imu_telem.angular_velocity[0],
					message.contents.imu_telem.angular_velocity[1],
					message.contents.imu_telem.angular_velocity[2]);
			imu->magnetic_field = Vec3(message.contents.imu_telem.magnetic_field[0],
					message.contents.imu_telem.magnetic_field[1],
					message.contents.imu_telem.magnetic_field[2]);
			break;
		case IncomingMessageType::GPSTelemetry:
			printf("Received GPS telemetry message\n");
			gps->utc = message.timestamp;
			gps->location = Location(message.contents.gps_telem.latitude,
									 message.contents.gps_telem.longitude,
									 message.contents.gps_telem.altitude);
			break;
		case IncomingMessageType::CommandResponse:
			printf("Received command response message\n");
			
			// Copy the received message to the incoming folder
			incoming.WriteMessage(message);
			break;
		case IncomingMessageType::Invalid:
			printf("[Warning] Received invalid message\n");
			break;
		default:
			printf("[Error] Received message of unsupported type '%hhu'\n", message.type);
			break;
	}
	
	
	return incoming_messages.size() != 0;
}


void SendNextOutgoingMessage() {
	printf("Sending message...\n");
	
	
	OutgoingMessage &message = outgoing_messages.front();
	
	// Use the radio to send the message
	
	outgoing_messages.pop();
	
}



