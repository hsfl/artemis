
#include "device/UARTDevice.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <termios.h>
#include <linux/types.h>
#include <sys/ioctl.h>


#define UART_PATH "/dev/ttyO"

using namespace std;
using namespace artemis;


UARTDevice::UARTDevice(unsigned int device, unsigned int baud_rate) : device(device), baud_rate(baud_rate), file(-1) {
	filename = UART_PATH + to_string(device);
}

bool UARTDevice::Open() {
	
	//  Open the UART device
	file = open(filename.c_str(), O_RDWR | O_NOCTTY);
	
	// Check if an error occurred in opening the device
	if ( file < 0 ){
		printf("UARTDevice: failed to open port '%s'\n", filename.c_str());
		return false;
	}
	
	// Determine the baud rate flag
	int baud;
	switch ( baud_rate ) {
		case 1200:
			baud = B1200;
			break;
		case 1800:
			baud = B1800;
			break;
		case 2400:
			baud = B2400;
			break;
		case 4800:
			baud = B4800;
			break;
		case 9600:
			baud = B9600;
			break;
		case 19200:
			baud = B19200;
			break;
		case 38400:
			baud = B38400;
			break;
		case 57600:
			baud = B57600;
			break;
		case 115200:
			baud = B115200;
			break;
		case 230400:
			baud = B230400;
			break;
		case 460800:
			baud = B460800;
			break;
		case 500000:
			baud = B500000;
			break;
		case 576000:
			baud = B576000;
			break;
		case 921600:
			baud = B921600;
			break;
		case 1000000:
			baud = B1000000;
			break;
		case 1152000:
			baud = B1152000;
			break;
		case 1500000:
			baud = B1500000;
			break;
		case 2000000:
			baud = B2000000;
			break;
		case 2500000:
			baud = B2500000;
			break;
		case 3000000:
			baud = B3000000;
			break;
		case 3500000:
			baud = B3500000;
			break;
		case 4000000:
			baud = B4000000;
			break;
		default:
			Close();
			printf("UARTDevice: invalid baud rate '%d'\n", baud_rate);
			return false;
	}
	
	// Set UART attributes
	bzero(&uartTermios, sizeof(uartTermios));
	uartTermios.c_cflag = baud | CS8 | CLOCAL | CREAD;
	uartTermios.c_iflag = IGNPAR | ICRNL | IGNCR;
	uartTermios.c_oflag = 0;
	uartTermios.c_lflag = 0;
	uartTermios.c_cc[VTIME] = 0;
	uartTermios.c_cc[VMIN]  = 0;

	// Clear out previous data
	tcflush(file, TCIFLUSH);
	
	// Set the attributes
	tcsetattr(file, TCSANOW, &uartTermios);

	return true;
}

void UARTDevice::Close() {
	if ( file >= -1 ) {
		close(file);
		file = -1;
	}
}

UARTDevice::~UARTDevice() {
	Close();
}

size_t UARTDevice::InWaiting() const {
	if ( !IsOpen() )
		return 0;
	
	int bytes_available;
	
	// Get the number of bytes available in the UART
	ioctl(file, FIONREAD, &bytes_available);
	
#if !CUBESAT_DISABLE_UART_SPOOFING
	// Add in the spoofed bytes
	for (const SpoofedInput &input : spoofed_input)
		bytes_available += input.length - input.index;
#endif
	
	return bytes_available;
}

bool UARTDevice::WriteByte(uint8_t byte) {
	if ( IsOpen() )
		return write(file, &byte, 1) >= 0;
	else
		return false;
}
bool UARTDevice::Write(uint8_t byte[], unsigned int len) {
	if ( IsOpen() )
		return write(file, byte, len) >= 0;
	else
		return false;
}
size_t UARTDevice::Read(uint8_t out[], size_t len) {
	size_t len_read = 0;
	
#if !CUBESAT_DISABLE_UART_SPOOFING
	size_t left_in_spoof;
	size_t left_requested;
	
	// Read from spoofed input, if available
	while ( spoofed_input.size() != 0 && len_read < len ) {
		
		SpoofedInput &input = spoofed_input.front();
		left_in_spoof = input.length - input.index;
		left_requested = len - len_read;
		
		// Check whether the spoofed input is long enough to
		// read until the end of the requested length
		if ( left_in_spoof <= left_requested ) {
			
			// Copy out what's left in the spoofed input
			memcpy(out + len_read, input.input + input.index,
				   left_in_spoof);
			len_read += left_in_spoof;
			
			// Remove the spoofed input from the front of the queue
			spoofed_input.erase(spoofed_input.begin());
		}
		else {
			
			// Copy out the spoof data until the requested length
			// is reached
			memcpy(out + len_read, input.input + input.index,
				   left_requested);
			input.index += left_requested;
			len_read += left_requested;
			
			return len_read;
		}
	}
#endif
	
	if ( !IsOpen() )
		return len_read;
	else
		// Read the lest of the data from the actual UART
		return len_read + read(file, out + len_read, len - len_read);
}
size_t UARTDevice::ReadLine(uint8_t out[], size_t len) {
	size_t read_count = 0;
	int read_status;
	
	// Read character by character until the newline is reached
	do {
		// Check if we've read the maximum number of characters
		if ( read_count >= len )
			break;
		
		read_status = Read(out++, 1);
		read_count += read_status;
	} while ( (char)*(out - 1) != '\n' && read_status > 0 );
	
	// Replace the newline with a terminating character
	if ( read_count != 0 )
		*(out - 1) = (uint8_t)'\0';
	
	return read_count;
}
void UARTDevice::Drain() {
	tcdrain(file);
	spoofed_input.clear();
}

void UARTDevice::SpoofInput(uint8_t input[], unsigned int len) {
#if !CUBESAT_DISABLE_UART_SPOOFING
	spoofed_input.push_back(SpoofedInput());
	memcpy(spoofed_input.back().input, input, len);
	spoofed_input.back().length = len;
#endif
}


