
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
int32_t I2CDevice::Open() {
	if ( IsOpen() )
        return 0;
	
	// Open the device
	file = open(GetDevicePath().c_str(), O_RDWR);
	
	// Check if an error occurred
	if ( file < 0 ) {
		file = -1;
        return -errno;
	}
	
	// Set up the device
	if ( ioctl(file, I2C_SLAVE, device) != 0 ) {
		close(file);
		file = -1;
        return -errno;
	}
	
	// Try writing to the device to see if it is actually available
	unsigned char buffer[3];
	buffer[0] = 0x00;
	buffer[1] = 0;
	buffer[2] = 0;
	
	if ( write(file, buffer, 3) != 3 ) {
		close(file);
		file = -1;
        return -errno;
	}
	
    return 0;
}

void I2CDevice::Close(){
	if ( IsOpen() ) {
		close(file);
		file = -1;
	}
}


int32_t I2CDevice::WriteRegister(uint8_t registerAddress, uint16_t value){
    if ( !IsOpen() ){
        return ErrorNumbers::COSMOS_GENERAL_ERROR_NOTSTARTED;
    }

	
	// Set up the data buffer
	unsigned char buffer[3];
	buffer[0] = registerAddress;
	buffer[1] = value >> 8;
	buffer[2] = value & 0x00FF;
	
	// Write to the device
    int32_t status = write(file, buffer, 3);
    if (  status < 0 ) {
        return -errno;
	}
	
	return true;
}


int32_t I2CDevice::Write(uint8_t value){
    if ( !IsOpen() ) {
        return ErrorNumbers::COSMOS_GENERAL_ERROR_NOTSTARTED;
    }
	
	unsigned char buffer[1] = {value};
	
	// Write to the device
    int32_t status = write(file, buffer, 1);
    if (  status < 0 ) {
        return -errno;
	}
	
    return status;
}


int32_t I2CDevice::ReadRegister(uint8_t registerAddress, int16_t &out) {
	if ( !IsOpen() )
		return -1;
	
	// Write the register address
	Write(registerAddress);
	
	// Read from the register
	uint8_t buffer[2];
    int32_t status =  read(this->file, buffer, 2);
    if(status < 0){
        return status;
    }
    if ( status != 2 ) {
        return ErrorNumbers::COSMOS_GENERAL_ERROR_BAD_SIZE;
	}
	
    out = buffer[0] | (buffer[1] << 8);
    return status;
}


int32_t I2CDevice::ReadRegisters(uint8_t *out, uint8_t first_addr, uint8_t len) {
	if ( !IsOpen() )
        return ErrorNumbers::COSMOS_GENERAL_ERROR_NOTSTARTED;
	
	// Write the first address
	this->Write(first_addr);
	
	
    int32_t bytes_read;
	if ( (bytes_read = read(this->file, out, len)) != (int)len ) {
        return ErrorNumbers::COSMOS_GENERAL_ERROR_BAD_SIZE;
	}
	
	return bytes_read;
}



