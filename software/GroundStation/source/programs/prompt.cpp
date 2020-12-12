
#include "SimpleAgent/SimpleAgent.h"
#include "utility/files.h"

#include <iostream>


using namespace std;
using namespace artemis;

IncomingFolder incoming("ground");
OutgoingFolder outgoing("ground");

void PrintHelp();
void SendCommand();
void Clear();


int main(int argc, char **argv) {
	system("clear");
	cout << "Welcome to the Artemis ground station interactive prompt." << endl;
	cout << "For a list of commands, type 'help'." << endl;
	cout << "To exit, type 'exit'." << endl;
	
	string input;
	
	while ( true ) {
		cout << ">> ";
		getline(cin, input);
		
		
		if ( input.empty() )
					continue;
		else if ( input == "exit" )
			break;
		else if ( input == "help" || input == "h" )
			PrintHelp();
		else if ( input == "cmd" )
			SendCommand();
		else if ( input == "clear" )
			Clear();
		else
			printf("Unknown command. Type 'help' to see available commands.\n");
		
		
		
	};
	
	return 0;
}


void PrintHelp() {
	
	cout << "\thelp\t- Prints a list of available commands" << endl;
	cout << "\texit\t- Exits the program" << endl;
	cout << "\tclear\t- Clears the screen" << endl;
	cout << "\tcmd\t- Sends a command to the cubesat" << endl;
	
	
}

void SendCommand() {
	int obc;
	string command;
	
	cout << "\t0\t PyCubed" << endl;
	cout << "\t1\t BeagleBone" << endl;
	cout << "\t2\t Raspberry Pi" << endl;
	
	do {
		cout << "Enter the number of the destination OBC: ";
		cin >> obc;
		cin.ignore();
	} while ( obc < 0 || obc > 2);
	
	cout << "Enter the command to run: ";
	getline(cin, command);
	
	int id = outgoing.GenerateCommandID();
	
	OutgoingMessage msg;
	msg.type = OutgoingMessageType::Command;
	msg.contents.command.obc = obc;
	msg.contents.command.command_id = id;
	memcpy(msg.contents.command.command, command.c_str(), command.length() + 1);
	
	if ( PrepareOutgoingMessage(msg) ) {
		outgoing.WriteMessage(msg);
		printf("\tWaiting for response...\n");
		
		Timer timer;
		timer.Start();
		
		vector<int> received_ids;
		
		do {
			received_ids = incoming.GetCommandResponseIDs();
			if ( std::find(received_ids.begin(), received_ids.end(), id) != received_ids.end() ) {
				IncomingMessage response;
				if ( !incoming.ReadMessage("cmd" + std::to_string(id), response) ) {
					printf("\tReceived invalid or corrupted response.\n");
				}
				else {
					printf("\tReceived response:\n");
					printf("\t\tLength: %u\n", response.length);
					printf("\t\tTimestamp: %f\n", response.timestamp);
					printf("\t\tContents: %s\n", response.contents.command_response.response);
				}
				return;
			}
		} while ( timer.Seconds() < 5 );
		
		printf("\tError: no response received in time.\n");
		return;
	}
	else {
		printf("\tError: failed to send message.\n");
	}
}

void Clear() {
	system("clear");
}

