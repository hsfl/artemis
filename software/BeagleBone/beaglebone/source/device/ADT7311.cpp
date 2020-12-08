
#include "device/ADT7311.h"

#include <cmath>

// The maxmium possible speed in Hz for IO with this device.
// Need to verify this value
#define MAX_SPEED 10000000


using namespace std;
using namespace artemis;



ADT7311::ADT7311(unsigned int bus, unsigned int device) : SPIDevice(bus, device) {
	
}
ADT7311::~ADT7311() {
	
}

bool ADT7311::Open() {
	
	if ( SPIDevice::Open() ) {
		// Set the IO mode
		SetMode(SPIMODE::MODE2); // Need to verify the mode
		
		// Set the maximum data transfer speed
		SetSpeed(MAX_SPEED);
		
		return true;
	}
	
	return false;
}


void ADT7311::ReadState() {
	
	// Make sure the device is initialized
	if ( !IsOpen() )
		return;
	
	// Read configuration register
	config.raw_data = Read8Bit(Register::Config);
	
	// Read status register
	status.raw_data = Read8Bit(Register::Status);
	
	// Read temperature data
	temp_data.raw_data = Read16Bit(Register::Temperature);
	
	// Read low setpoint
	low_setpoint = Read16Bit(Register::LowSetPoint);
	
	// Read high setpoint
	high_setpoint = Read16Bit(Register::HighSetPoint);
	
	// Read crit setpoint
	crit_setpoint = Read16Bit(Register::CritSetPoint);
	
	// Read hyst setpoint
	hyst_setpoint = Read8Bit(Register::HystSetPoint);
}

void ADT7311::SetConfiguration(Configuration &config) {
	
	if ( !IsOpen() )
		return;
	
	// Write to the configuration register
	Write8Bit(Register::Config, config.raw_data);
}

float ADT7311::GetTemperature() const {
	if ( !IsOpen() ) {
		return -1;
	}
	
	// 13-bit resolution
	if ( config.resolution == 0 ) {
		
		// Convert the binary values to decimal, with a formula depending on the sign
		if ( temp_data.sign == 0 ) // Negative values
			return (temp_data.temperature - 65536) / 128.0f;
		else // Positive values
			return temp_data.temperature / 128.0f;

	}
	// 16-bit resolution
	else {
		// TODO
		return 0;
	}
}


void ADT7311::SetLowSetpoint(int16_t temp) {
	// Convert to two's complement
	uint16_t write_temp = static_cast<uint16_t>(temp);
	
	// Write to the low setpoint register
	Write16Bit(Register::LowSetPoint, write_temp);
}
void ADT7311::SetHighSetpoint(int16_t temp) {
	// Convert to two's complement
	uint16_t write_temp = static_cast<uint16_t>(temp);
	
	// Write to the high setpoint register
	Write16Bit(Register::HighSetPoint, write_temp);
}
void ADT7311::SetHystSetpoint(uint8_t temp) {
	// Write to the hyst. setpoint register
	Write8Bit(Register::HystSetPoint, temp);
}
void ADT7311::SetCritSetpoint(int16_t temp) {
	// Convert to two's complement
	uint16_t write_temp = static_cast<uint16_t>(temp);
	
	// Write to the critical setpoint register
	Write16Bit(Register::CritSetPoint, write_temp);
}



uint8_t ADT7311::GetCommand(CommandMode mode, Register reg) {
	// Format command as 'cXXX000', where 'c' is 1 for read or 0 for write, and 'XXX' is the register address
	return ((uint8_t)mode << 6) | ((uint8_t)reg << 3);
}


void ADT7311::Write8Bit(Register reg, uint8_t value) {
	uint8_t send[2], receive[2];
	
	// Create send buffer
	send[0] = GetCommand(CommandMode::Write, reg);
	send[1] = value;
	
	// Issue command
	Transfer(send, receive, 2);
	
}
void ADT7311::Write16Bit(Register reg, uint16_t value) {
	uint8_t send[3], receive[3];
	
	// Create send buffer
	send[0] = GetCommand(CommandMode::Write, reg);
	send[1] = value >> 8; // Most significant byte
	send[2] = value & 0x00FF; // Least significant byte
	
	// Issue command
	Transfer(send, receive, 3);
}
uint8_t ADT7311::Read8Bit(Register reg) {
	uint8_t send[2], receive[2];
	
	// Create send buffer
	send[0] = GetCommand(CommandMode::Read, reg);
	send[1] = 0;
	
	// Issue command
	Transfer(send, receive, 2);
	
	// Return the 8-bit value shifted in
	return receive[1];
}
uint16_t ADT7311::Read16Bit(Register reg) {
	uint8_t send[3], receive[3];
	
	// Create send buffer
	send[0] = GetCommand(CommandMode::Read, reg);
	send[1] = 0;
	send[2] = 0;
	
	// Issue command
	Transfer(send, receive, 3);
	
	// Return the 16-bit value shifted in
	return ((uint16_t)receive[1] << 8) | (uint16_t)receive[2];
}
