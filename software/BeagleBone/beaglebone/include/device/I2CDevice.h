
#ifndef CUBESAT_DEVICE_I2CDEVICE
#define CUBESAT_DEVICE_I2CDEVICE

#include <stdint.h>
#include <string>


namespace artemis {
	
	
	class I2CDevice {
	public:
		I2CDevice();
		I2CDevice(uint8_t bus, uint8_t device);
		virtual ~I2CDevice();
		
		virtual int Open();
		virtual void Close();
		
		inline bool IsOpen() const {
			return is_open;
		}
		inline int GetBusAddr() const {
			return bus;
		}
		inline int GetDeviceAddr() const {
			return device;
		}
		std::string GetDevicePath() const;
		
		
		virtual int Write(uint8_t value);
		virtual int WriteRegister(uint8_t register_addr, uint16_t value);
		virtual int ReadRegisters(uint8_t *out, uint8_t first_addr, uint8_t len);
		virtual uint16_t ReadRegister(uint8_t register_addr);
		
		
	private:
		int bus;
		int device;
		int file;
		bool is_open = false;
	};

}

#endif
