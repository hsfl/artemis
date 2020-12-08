
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


#define BBB_I2C_0 "/dev/i2c-0"
#define BBB_I2C_1 "/dev/i2c-1"
#define BBB_I2C_2 "/dev/i2c-2"

using namespace std;
using namespace artemis;

#define HEX(x) setw(2) << setfill('0') << hex << (int)(x)


I2CDevice::I2CDevice() {
	file = -1;
	bus = -1;
	device = -1;
	is_open = false;
}

/**
 * Constructor for the I2CDevice class. It requires the bus number and device number. The constructor
 * opens a file handle to the I2C device, which is destroyed when the destructor is called
 * @param bus The bus number. Usually 0 or 1 on the BBB
 * @param device The device ID on the bus.
 */
I2CDevice::I2CDevice(uint8_t bus, uint8_t device) : bus(bus), device(device), file(-1), is_open(false) {
	
}

std::string I2CDevice::GetDevicePath() const {
	switch ( bus ) {
		case 0:
			return BBB_I2C_0;
			break;
		case 1:
			return BBB_I2C_1;
			break;
		case 2:
			return BBB_I2C_2;
			break;
		default:
			return "";
	}
}

/**
 * Open a connection to an I2C device
 * @return -1 on failure to open to the bus or device, 0 on success.
 */
int I2CDevice::Open() {
	if ( IsOpen() )
		return -1;
	
	string name = GetDevicePath();
	
	if ( name.empty() )
		return -1;
	
	file = open(name.c_str(), O_RDWR);
	
	if ( file < 0 ) {
		perror("Failed to open I2C bus");
		file = -1;
		return -1;
	}
	
	if ( ioctl(file, I2C_SLAVE, device) != 0 ) {
		perror("Failed to connect to I2C device");
		close(file);
		return -1;
	}
	
	// Try writing to the device to see if it is actually available
	unsigned char buffer[3];
	buffer[0] = 0x00;
	buffer[1] = 0;
	buffer[2] = 0;
	
	if ( write(file, buffer, 3) != 3 ) {
		close(file);
		return -1;
	}
	
	is_open = true;
	return 0;
}

/**
 * Write a single byte value to a single register.
 * @param registerAddress The register address
 * @param value The value to be written to the register
 * @return -1 on failure to write, 0 on success.
 */

int I2CDevice::WriteRegister(uint8_t registerAddress, uint16_t value){
	if ( !IsOpen() )
		return -1;
	
	unsigned char buffer[3];
	buffer[0] = registerAddress;
	buffer[1] = value >> 8;
	buffer[2] = value & 0x00FF;
   
	if ( write(file, buffer, 3) != 3 ) {
	  perror("Failed write to the I2C device");
	  return -1;
	}
	
	return 0;
}

/**
 * Write a single value to the I2C device. Used to set up the device to read from a
 * particular address.
 * @param value the value to write to the device
 * @return -1 on failure to write, 0 on success.
 */
int I2CDevice::Write(uint8_t value){
	if ( !IsOpen() )
		return -1;
	
	unsigned char buffer[1] = {value};
	
	if ( write(file, buffer, 1) != 1 ) {
		perror("Failed write to the I2C device");
		return -1;
	}
	
	return 0;
}

/**
 * Read a single register value from the address on the device.
 * @param registerAddress the address to read from
 * @return the byte value at the register address.
 */
uint16_t I2CDevice::ReadRegister(uint8_t registerAddress) {
	if ( !IsOpen() )
		return -1;
	
	Write(registerAddress);
	
	uint8_t buffer[2];
	
	if ( read(this->file, buffer, 2) != 2 ) {
		perror("Failed to read from I2C device");
		return -1;
	}
	
	return buffer[0] | (buffer[1] << 8);
}

/**
 * Method to read a number of registers from a single device. This is much more efficient than
 * reading the registers individually. The from address is the starting address to read from, which
 * defaults to 0x00.
 * @param number the number of registers to read from the device
 * @param fromAddress the starting address to read from
 * @return a pointer of type unsigned char* that points to the first element in the block of registers
 */
int I2CDevice::ReadRegisters(uint8_t *out, uint8_t first_addr, uint8_t len) {
	if ( !IsOpen() )
		return -1;
	
	this->Write(first_addr);
	
	int bytes_read;
	
    if ( (bytes_read = read(this->file, out, len)) != (int)len ) {
       perror("Failed to read in full buffer from I2C device");
	   return 0;
    }
	
	return bytes_read;
}

/**
 * Close the file handles and sets a temporary state to -1.
 */
void I2CDevice::Close(){
	if ( IsOpen() ) {
		close(file);
		file = -1;
	}
}

/**
 * Closes the file on destruction, provided that it has not already been closed.
 */
I2CDevice::~I2CDevice() {
	Close();
}

