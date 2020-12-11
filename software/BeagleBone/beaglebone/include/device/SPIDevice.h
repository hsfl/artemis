/*
 * SPIDevice.h  Created on: 22 May 2014
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

#ifndef CUBESAT_DEVICE_SPIDEVICE
#define CUBESAT_DEVICE_SPIDEVICE

#include<string>
#include<stdint.h>


namespace artemis {
	
	/**
	 * @class SPIDevice
	 * @brief Generic SPI Device class that can be used to connect to any type of SPI device and read or write to its registers
	 */
	class SPIDevice {
	public:
		
		enum SPIMODE{
			MODE0 = 0,   // Low at idle, capture on rising clock edge
			MODE1 = 1,   // Low at idle, capture on falling clock edge
			MODE2 = 2,   // High at idle, capture on falling clock edge
			MODE3 = 3    // High at idle, capture on rising clock edge
		};
		
		
		SPIDevice(unsigned int bus, unsigned int device);
		virtual ~SPIDevice();
		
		virtual bool Open();
		virtual void Close();
		
		inline bool IsOpen() const {
			return is_open;
		}
		inline int GetBus() const {
			return bus;
		}
		inline int GetDeviceAddr() const {
			return device;
		}
		
		virtual unsigned char ReadRegister(unsigned int registerAddress);
		virtual int ReadRegisters(unsigned char *out, unsigned int number, unsigned int fromAddress=0);
		virtual int WriteRegister(unsigned int registerAddress, unsigned char value);
		virtual void DebugDumpRegisters(unsigned int number = 0xff);
		virtual int Write(unsigned char value);
		virtual int Write(unsigned char value[], int length);
		
		virtual int SetSpeed(uint32_t speed);
		virtual int SetMode(SPIDevice::SPIMODE mode);
		virtual int SetBitsPerWord(uint8_t bits);
		virtual int Transfer(unsigned char send[], unsigned char receive[], int length);
		
		
	protected:
		std::string filename;
		int file;
		unsigned int bus;
		unsigned int device;
		
		SPIMODE mode;
		uint8_t bits;
		uint32_t speed;
		uint16_t delay;
		
		bool is_open;
		
	};

}

#endif
