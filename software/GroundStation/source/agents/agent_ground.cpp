
// Internal headers
#include "SimpleAgent/SimpleAgent.h"
#include "utility/message.h"

#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace artemis;
using namespace std;


using CommandID = decltype(IncomingMessage::contents.command_response.command_id);

SimpleAgent *agent;

queue<IncomingMessage> incoming_messages;
queue<OutgoingMessage> outgoing_messages;

std::vector<CommandID> waiting_command_ids;


int FetchMessages();

/**
 * @brief Handles the next incoming message
 * @return True if there are more messages in the queue
 */
bool HandleNextIncomingMessage();

CommandID SendCommand(const string &command);


int main(int argc, char *argv[]) {
	
	agent = new SimpleAgent("ground", "cubesat");
	agent->SetLoopPeriod(1);
	
	
	
	agent->Finalize();
	agent->DebugPrint();
	
	
	while ( agent->StartLoop() ) {
		
		// Fetch and handle incoming messages
		FetchMessages();
		while ( HandleNextIncomingMessage() );
		
	}
	
	delete agent;
	
	
	
	return 0;
}


int FetchMessages() {
	
	int num_pushed = 0;
	
	unsigned char bytes[sizeof(IncomingMessage)];
	
	
	// fetch any new messages here
	
	
	return num_pushed;
}

bool HandleNextIncomingMessage() {
	
	// Get the next element
	IncomingMessage message = incoming_messages.front();
	incoming_messages.pop();
	
	switch ( message.type ) {
		case IncomingMessageType::CommandResponse:
			break;
		case IncomingMessageType::Invalid:
			printf("[Warning] Received invalid message\n");
			break;
		default:
			printf("[Error] Received message of invalid type '%hhu'\n", message.type);
			break;
	}
	
	
	
	return incoming_messages.size() != 0;
}




CommandID SendCommand(const string &command) {
	
	CommandID id;
	
	do id = rand();
	while ( std::find(waiting_command_ids.begin(), waiting_command_ids.end(), id) != waiting_command_ids.end());
	
	OutgoingMessage message;
	
	// Fill in message here
	
	
	outgoing_messages.push(message);
	
	
	
	waiting_command_ids.push_back(id);
	
	
	return id;
}




