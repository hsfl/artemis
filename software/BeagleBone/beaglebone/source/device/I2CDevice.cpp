
#include "device/I2CDevice.h"
#include <iostream>
#include <sstream>
#include <fcntl.h>
#include <stdio.h>
#include <iomanip>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#define I2C_PATH "/dev/i2c-"

using namespace std;
using namespace artemis;


I2CDevice::I2CDevice() {
	file = -1;
	bus = -1;
	device = -1;
}

/**
 * Constructor for the I2CDevice class. It requires the bus number and device number. The constructor
 * opens a file handle to the I2C device, which is destroyed when the destructor is called
 * @param bus The bus number. Usually 0 or 1 on the BBB
 * @param device The device ID on the bus.
 */
I2CDevice::I2CDevice(uint8_t bus, uint8_t device) : bus(bus), device(device), file(-1) {
	
}

I2CDevice::~I2CDevice() {
	Close();
}


std::string I2CDevice::GetDevicePath() const {
	return I2C_PATH + std::to_string(bus);
}

/**
 * Open a connection to an I2C device
 * @return -1 on failure to open to the bus or device, 0 on success.
 */
bool I2CDevice::Open() {
	if ( IsOpen() )
		return false;
	
	// Open the device
	file = open(GetDevicePath().c_str(), O_RDWR);
	
	// Check if an error occurred
	if ( file < 0 ) {
		perror("Failed to open I2C bus");
		file = -1;
		return false;
	}
	
	// Set up the device
	if ( ioctl(file, I2C_SLAVE, device) != 0 ) {
		perror("Failed to connect to I2C device");
		close(file);
		file = -1;
		return false;
	}
	
	// Try writing to the device to see if it is actually available
	unsigned char buffer[3];
	buffer[0] = 0x00;
	buffer[1] = 0;
	buffer[2] = 0;
	
	if ( write(file, buffer, 3) != 3 ) {
		close(file);
		file = -1;
		return -1;
	}
	
	return true;
}

void I2CDevice::Close(){
	if ( IsOpen() ) {
		close(file);
		file = -1;
	}
}


bool I2CDevice::WriteRegister(uint8_t registerAddress, uint16_t value){
	if ( !IsOpen() )
		return false;
	
	// Set up the data buffer
	unsigned char buffer[3];
	buffer[0] = registerAddress;
	buffer[1] = value >> 8;
	buffer[2] = value & 0x00FF;
	
	// Write to the device
	if ( write(file, buffer, 3) != 3 ) {
		perror("Failed write to the I2C device");
		return false;
	}
	
	return true;
}


bool I2CDevice::Write(uint8_t value){
	if ( !IsOpen() )
		return false;
	
	unsigned char buffer[1] = {value};
	
	// Write to the device
	if ( write(file, buffer, 1) != 1 ) {
		perror("Failed write to the I2C device");
		return false;
	}
	
	return true;
}


int I2CDevice::ReadRegister(uint8_t registerAddress) {
	if ( !IsOpen() )
		return -1;
	
	// Write the register address
	Write(registerAddress);
	
	// Read from the register
	uint8_t buffer[2];
	if ( read(this->file, buffer, 2) != 2 ) {
		perror("Failed to read from I2C device");
		return -1;
	}
	
	return buffer[0] | (buffer[1] << 8);
}


int I2CDevice::ReadRegisters(uint8_t *out, uint8_t first_addr, uint8_t len) {
	if ( !IsOpen() )
		return -1;
	
	// Write the first address
	this->Write(first_addr);
	
	
	int bytes_read;
	if ( (bytes_read = read(this->file, out, len)) != (int)len ) {
		perror("Failed to read in full buffer from I2C device");
		return 0;
	}
	
	return bytes_read;
}



