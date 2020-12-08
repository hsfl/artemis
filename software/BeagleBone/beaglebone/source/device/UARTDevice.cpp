
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
// Define the beaglebone black cape. The cape manager may be 8 or 9
#define BONEPATH_9	"/sys/devices/bone_capemgr.9/slots"
#define BONEPATH_8	"/sys/devices/bone_capemgr.8/slots"

using namespace std;
using namespace artemis;

#define HEX(x) setw(2) << setfill('0') << hex << (int)(x)  //!< Macro for filling in leading 0 on HEX outputs


UARTDevice::UARTDevice(unsigned int device, unsigned int baud_rate) : device(device), baud_rate(baud_rate), file(-1) {
	filename = UART_PATH + to_string(device);
}


int UARTDevice::Open() {
	
	FILE *uart;
	char buf[11] = "/dev/tty";
	int baud;

	// Open the slot for UART
	// Try for bone_capemgr.9 first
//	uart = fopen(BONEPATH_9, "w");
//	if ( uart == NULL ) {
//		printf("bone_capemgr.9 doesn't exist. Trying bone_capemgr.8");
		
//		uart = fopen(BONEPATH_8, "w");
//		if ( uart == NULL ) {
//			printf("Slots didn't open\n");
//			return -1;
//		}
//	}
//	fseek(uart,0,SEEK_SET);
	
	
	
//	fprintf(uart, "BB-UART1");
	strcat(buf, "O1");
//	fflush(uart);
//	fclose(uart);

	//  Open uart port for UART tx/rx
	file = open(buf, O_RDWR | O_NOCTTY);
	if ( file < 0 ){
		printf("port failed to open\n");
		return -1;
	}
	
	//save current attributes
	bzero(&uartTermios, sizeof(uartTermios));
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
		printf("Incorrect baud rate");
		return -1;
	}

	// Choose the control/input/output/local modes for UART operation
	// I would suggest you read the manual here: http://man7.org/linux/man-pages/man3/termios.3.html
	uartTermios.c_cflag = baud | CS8 | CLOCAL | CREAD;
	uartTermios.c_iflag = IGNPAR | ICRNL | IGNCR;
	uartTermios.c_oflag = 0;
	uartTermios.c_lflag = 0;

	uartTermios.c_cc[VTIME] = 0;
	uartTermios.c_cc[VMIN]  = 0;
	
	// Choose the control/input/output/local modes for UART operation
	// I would suggest you read the manual here: http://man7.org/linux/man-pages/man3/termios.3.html
	uartTermios.c_cflag = baud | CS8 | CLOCAL | CREAD;
	uartTermios.c_iflag = IGNPAR | ICRNL | IGNCR;
	uartTermios.c_oflag = 0;
	uartTermios.c_lflag = 0;

	uartTermios.c_cc[VTIME] = 0;
	uartTermios.c_cc[VMIN]  = 0;

	// Clean the line and set the attributes

	tcflush(file, TCIFLUSH);
	tcsetattr(file, TCSANOW, &uartTermios);

	return 0;
}

void UARTDevice::Close() {
	close(file);
	file = -1;
}

UARTDevice::~UARTDevice() {
	Close();
}

size_t UARTDevice::InWaiting() const {
	int bytes_available;
	ioctl(file, FIONREAD, &bytes_available);
	return bytes_available;
}

void UARTDevice::WriteByte(uint8_t byte) {
	write(file, &byte, 1);
}
void UARTDevice::Write(uint8_t byte[], unsigned int len) {
	write(file, byte, len);
}
size_t UARTDevice::Read(uint8_t out[], size_t len) {
	return read(file, out, len);
}
void UARTDevice::Drain() {
	tcdrain(file);
}
