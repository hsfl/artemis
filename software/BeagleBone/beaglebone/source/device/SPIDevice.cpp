/*
 * SPIDevice.cpp  Created on: 22 May 2014
 * Copyright (c) 2014 Derek Molloy (www.derekmolloy.ie)
 * Made available for the book "Exploring BeagleBone"
 * See: www.exploringbeaglebone.com
 * Licensed under the EUPL V.1.1
 *
 * This Software is provided to You under the terms of the European
 * Union Public License (the "EUPL") version 1.1 as published by the
 * European Union. Any use of this Software, other than as authorized
 * under this License is strictly prohibited (to the extent such use
 * is covered by a right of the copyright holder of this Software).
 *
 * This Software is provided under the License on an "AS IS" basis and
 * without warranties of any kind concerning the Software, including
 * without limitation merchantability, fitness for a particular purpose,
 * absence of defects or errors, accuracy, and non-infringement of
 * intellectual property rights other than copyright. This disclaimer
 * of warranty is an essential part of the License and a condition for
 * the grant of any rights to this Software.
 *
 * For more details, see http://www.derekmolloy.ie/
 */

// See http://exploringbeaglebone.com/chapter8/

#include "device/SPIDevice.h"
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
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>


#define SPI_PATH "/dev/spidev"

using namespace std;
using namespace artemis;

#define HEX(x) setw(2) << setfill('0') << hex << (int)(x)  //!< Macro for filling in leading 0 on HEX outputs


/**
 * The constructor for the SPIDevice that sets up and opens the SPI connection.
 * The destructor will close the SPI file connection.
 * @param bus The SPI bus number X (first digit after spidevX.Y)
 * @param device The device on the bus Y (second digit after spidevX.Y)
 */
SPIDevice::SPIDevice(unsigned int bus, unsigned int device) : file(-1), bus(bus), device(device), is_open(false) {
	filename = SPI_PATH + to_string(bus) + "." + to_string(device);
	mode = SPIDevice::MODE2;
	this->bits = 8;
	this->speed = 500000;
	this->delay = 0;
}

/**
 * This method opens the file connection to the SPI device.
 * @return 0 on a successful open of the file
 */
bool SPIDevice::Open(){
	
	if ( (this->file = ::open(filename.c_str(), O_RDWR)) < 0 ) {
		perror("Failed to open SPI device");
		return false;
	}
	
	
	if ( SetMode(this->mode) < 0 || SetSpeed(this->speed) < 0 || SetBitsPerWord(this->bits) < 0 ) {
		close(file);
		return false;
	}
	
	return (is_open = true);
}

/**
 * Generic method to transfer data to and from the SPI device. It is used by the
 * following methods to read and write registers.
 * @param send The array of data to send to the SPI device
 * @param receive The array of data to receive from the SPI device
 * @param length The length of the array to send
 * @return -1 on failure
 */
int SPIDevice::Transfer(unsigned char send[], unsigned char receive[], int length) {
	struct spi_ioc_transfer	transfer;
	memset(&transfer, 0, sizeof(transfer));
	
	transfer.tx_buf = (unsigned long) send;
	transfer.rx_buf = (unsigned long) receive;
	transfer.len = length;
	transfer.speed_hz = this->speed;
	transfer.bits_per_word = this->bits;
	transfer.delay_usecs = this->delay;
	transfer.tx_nbits = 0;        // no. bits for writing (default 0)
	transfer.rx_nbits = 0;        // no. bits for reading (default 0)
	transfer.cs_change = 0;       // affects chip select after transfe
	transfer.pad = 0;             // interbyte delay
	
	int status = ioctl(this->file, SPI_IOC_MESSAGE(1), &transfer);
	if ( status < 0 ) {
		perror("SPI_IOC_MESSAGE failed");
		return -1;
	}
	
	return status;
}

/**
 * A method to read a single register at the SPI address
 * @param registerAddress the address of the register from the device datasheet
 * @return the character that is returned from the address
 */
unsigned char SPIDevice::ReadRegister(unsigned int registerAddress) {
	unsigned char send[2], receive[2];
	memset(send, 0, sizeof send);
	memset(receive, 0, sizeof receive);
	
	send[0] = (unsigned char) (0x80 | registerAddress);
	Transfer(send, receive, 2);
	
	return receive[1];
}

/**
 * A method to read a number of registers as a data array
 * @param number the number of registers to read
 * @param fromAddress the starting address of the block of data
 * @return the data array that is returned (memory allocated by the method)
 */
int SPIDevice::ReadRegisters(unsigned char *out, unsigned int number, unsigned int fromAddress) {
	unsigned char send[number + 1], receive[number + 1];
	memset(send, 0, sizeof send);
	
	send[0] =  (unsigned char) (0x80 | 0x40 | fromAddress); //set read bit and MB bit
	Transfer(send, receive, number + 1);
	memcpy(out, receive + 1, number);  // ignore the first (address) byte in the array returned
	
	return number;
}

/**
 *  A write method that writes a single character to the SPI bus
 *  @param value the value to write to the bus
 *  @return returns 0 if successful
 */
int SPIDevice::Write(unsigned char value) {
	unsigned char null_return = 0x00;
	
	Transfer(&value, &null_return, 1);
	
	return 0;
}

/**
 *  A write method that writes a block of data of the length to the bus.
 *  @param value the array of data to write to the device
 *  @param length the length of the data array
 *  @return returns 0 if successful
 */
int SPIDevice::Write(unsigned char value[], int length) {
	unsigned char null_return = 0x00;
	
	Transfer(value, &null_return, length);
	
	return 0;
}

/**
 *  Writes a value to a defined register address (check the datasheet for the device)
 *  @param registerAddress the address of the register to write to
 *  @param value the value to write to the register
 *  @return returns 0 if successful
 */
int SPIDevice::WriteRegister(unsigned int registerAddress, unsigned char value) {
	unsigned char send[2], receive[2];
	
	memset(receive, 0, sizeof receive);
	send[0] = (unsigned char) registerAddress;
	send[1] = value;
	
	Transfer(send, receive, 2);
	
	return 0;
}

/**
 *  A simple method to dump the registers to the standard output -- useful for debugging
 *  @param number the number of registers to dump
 */
void SPIDevice::DebugDumpRegisters(unsigned int number){
	
	cout << "SPI Mode: " << this->mode << endl;
	cout << "Bits per word: " << (int)this->bits << endl;
	cout << "Max speed: " << this->speed << endl;
	cout << "Dumping Registers for Debug Purposes:" << endl;
	
	unsigned char registers[256];
	ReadRegisters(registers, number);
	
	for (int i = 0; i < (int)number; i++) {
		cout << HEX(*(registers+i)) << " ";
		
		if ( i % 16 == 15 )
			cout << endl;
	}
	
	cout << dec;
}

/**
 *   Set the speed of the SPI bus
 *   @param speed the speed in Hz
 */
int SPIDevice::SetSpeed(uint32_t speed){
	this->speed = speed;
	if (ioctl(this->file, SPI_IOC_WR_MAX_SPEED_HZ, &this->speed) < 0){
		perror("SPI: Can't set max speed HZ");
		return -1;
	}
	if (ioctl(this->file, SPI_IOC_RD_MAX_SPEED_HZ, &this->speed) < 0){
		perror("SPI: Can't get max speed HZ.");
		return -1;
	}
	return 0;
}

/**
 *   Set the mode of the SPI bus
 *   @param mode the enumerated SPI mode
 */
int SPIDevice::SetMode(SPIDevice::SPIMODE mode){
	this->mode = mode;
	if ( ioctl(this->file, SPI_IOC_WR_MODE, &this->mode) < 0 ) {
		perror("SPI: Can't set SPI mode.");
		return -1;
	}
	
	if ( ioctl(this->file, SPI_IOC_RD_MODE, &this->mode) < 0 ) {
		perror("SPI: Can't get SPI mode.");
		return -1;
	}
	
	return 0;
}

/**
 *   Set the number of bits per word of the SPI bus
 *   @param bits the number of bits per word
 */
int SPIDevice::SetBitsPerWord(uint8_t bits){
	this->bits = bits;
	
	if ( ioctl(file, SPI_IOC_WR_BITS_PER_WORD, &this->bits) == -1 ) {
		perror("SPI: Can't set bits per word.");
		return -1;
	}
	
	if ( ioctl(file, SPI_IOC_RD_BITS_PER_WORD, &this->bits) == -1 ) {
		perror("SPI: Can't get bits per word.");
		return -1;
	}
	
	return 0;
}

/**
 *   Close the SPI device
 */
void SPIDevice::Close() {
	
	if ( is_open || file > 0 ) {
		close(file);
		file = -1;
		is_open = false;
	}
}

/**
 *   The destructor closes the SPI bus device
 */
SPIDevice::~SPIDevice() {
	Close();
}

