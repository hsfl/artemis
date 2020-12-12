
#include "utility/message.h"
#include "support/timelib.h"

#include <stdlib.h>
#include <cstring>

using namespace std;
using namespace artemis;

unsigned char artemis::GetChecksum(const IncomingMessage &message) {
	unsigned char *p = (unsigned char*)&message;
	p += offsetof(IncomingMessage, type);
	
	unsigned char checksum = 0;
	
	for (unsigned i = 0; i < message.length - offsetof(IncomingMessage, type); ++i)
		checksum ^= *p++;
	
	return checksum;
}

unsigned char artemis::GetChecksum(const OutgoingMessage &message) {
	unsigned char *p = (unsigned char*)&message;
	p += offsetof(IncomingMessage, type);
	
	unsigned char checksum = 0;
	
	for (unsigned i = 0; i < message.length - offsetof(OutgoingMessage, type); ++i)
		checksum ^= *p++;
	
	return checksum;
}


IncomingMessage artemis::BytesToIncomingMessage(char *bytes, unsigned int max_length) {
	
	IncomingMessage message;
	
	// Set the message length
	unsigned int length = stol(std::string(bytes, 0, sizeof(message.length)));
	
	// Make sure the message length isn't too large
	if ( message.length > max_length ) {
		message.type = IncomingMessageType::Invalid;
		return message;
	}
	
	// Copy the message
	memset(&message, 0, sizeof(message));
	memcpy(&message, bytes, length);
	
	// Check the checksum
	if ( GetChecksum(message) != message.checksum )
		message.type = IncomingMessageType::Invalid;
	
	
	return message;
}

bool artemis::PrepareOutgoingMessage(OutgoingMessage &message) {
	
	// Find the minimum length of the message
	unsigned int length = offsetof(OutgoingMessage, contents);
	
	switch ( message.type ) {
		case OutgoingMessageType::Command:
			length = strlen(message.contents.command.command) + 1 + sizeof(message.contents.command.command_id);
			break;
		default:
			printf("[Error] Outgoing message type '%hhu' is invalid\n", message.type);
			return false;
	}
	
	// Set the length
	message.length = length;
	
	// Set the checksum
	message.checksum = GetChecksum(message);
	
	// Set the timestamp
	message.timestamp = currentmjd();
	
	return true;
}

unsigned int artemis::OutgoingMessageToBytes(const OutgoingMessage &message, char *bytes, unsigned int max_length) {
	
	// Make sure the message isn't too long
	if ( message.length >= max_length ) {
		printf("[Error] Message type is too long to store\n");
		return 0;
	}
	
	memcpy(bytes, &message, message.length);
	
	return message.length;
}


