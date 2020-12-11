
#ifndef CUBESAT_DEVICE_I2CDEVICE
#define CUBESAT_DEVICE_I2CDEVICE

#include <stdint.h>
#include <string>


namespace artemis {
	
	/**
	 * @brief Utility class for communicating with I2C devices
	 */
	class I2CDevice {
	public:
		/**
		 * @brief Default constructor. Not a valid device.
		 */
		I2CDevice();
		/**
		 * @brief Initializes the I2CDevice using the given bus and device
		 * @param bus The bus number of the I2C device
		 * @param device The device address of the I2C device
		 */
		I2CDevice(uint8_t bus, uint8_t device);
		/**
		 * @brief Closes the connection to the device
		 */
		virtual ~I2CDevice();
		
		/**
		 * @brief Attempts to open the device
		 * @return 0 if successful
		 */
		virtual bool Open();
		/**
		 * @brief Closes the device, if still open.
		 */
		virtual void Close();
		
		inline bool IsOpen() const {
			return file >= 0;
		}
		inline int GetBusAddr() const {
			return bus;
		}
		inline int GetDeviceAddr() const {
			return device;
		}
		std::string GetDevicePath() const;
		
		/**
		 * Write a single value to the I2C device. Used to set up the device to read from a
		 * particular address.
		 * @param value the value to write
		 * @return True on success
		 */
		virtual bool Write(uint8_t value);
		/**
		 * Write a single byte value to a single register.
		 * @param registerAddress The register address
		 * @param value The value to be written to the register
		 * @return True on success
		 */
		virtual bool WriteRegister(uint8_t register_addr, uint16_t value);
		/**
		 * Method to read a number of registers from a single device. This is much more efficient than
		 * reading the registers individually. The from address is the starting address to read from, which
		 * defaults to 0x00.
		 * @param number the number of registers to read from the device
		 * @param fromAddress the starting address to read from
		 * @return a pointer of type unsigned char* that points to the first element in the block of registers
		 */
		virtual int ReadRegisters(uint8_t *out, uint8_t first_addr, uint8_t len);
		/**
		 * Read a single register value from the address on the device.
		 * @param registerAddress the address to read from
		 * @return the byte value at the register address, or -1 on failure
		 */
		virtual int ReadRegister(uint8_t register_addr);
		
		
	private:
		//! The I2C bus number
		int bus;
		//! The device address
		int device;
		//! The file handle
		int file;
	};

}

#endif
