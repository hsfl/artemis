
#ifndef CUBESAT_DEVICE_OPT3001
#define CUBESAT_DEVICE_OPT3001

#include "device/I2CDevice.h"

namespace artemis {
	
	/**
	 * @brief Provides access to the OPT3001 temperature sensor.
	 */
	class OPT3001 : protected I2CDevice {
	public:
		/**
		 * @brief Configuration flags corresponding to the configuration register on the device.
		 */
		union Configuration {
			struct {
				uint8_t FaultCount : 2;
				uint8_t MaskExponent : 1;
				uint8_t Polarity : 1;
				uint8_t Latch : 1;
				uint8_t FlagLow : 1;
				uint8_t FlagHigh : 1;
				uint8_t ConversionReady : 1;
				uint8_t OverflowFlag : 1;
				uint8_t ModeOfConversionOperation : 2;
				uint8_t ConversionTime : 1;
				uint8_t RangeNumber : 4;
			};
			uint16_t raw_data;
		};
		
		/**
		 * @brief Stores data pulled from the result register
		 */
		union DeviceID {
			uint16_t raw_data;
			
			struct {
				uint16_t result  : 12;
			};
		};
		
		/**
		 * @brief Stores data pulled from the result register
		 */
		union ResultData {
			uint16_t raw_data;
			
			struct {
				uint16_t result  : 12;
				uint8_t exponent : 4;
			};
		};
		
		/**
		 * @brief Register addresses
		 */
		enum class Register : uint8_t {
			Result       = 0x00,
			Config       = 0x01,
			LowLimit     = 0x02,
			HighLimit    = 0x03,
			Manufacturer = 0x7E,
			DeviceID     = 0x7F
		};
		
		
		
	public:
		using I2CDevice::Open;
		using I2CDevice::Close;
		using I2CDevice::IsOpen;
		using I2CDevice::GetBusAddr;
		using I2CDevice::GetDeviceAddr;
		
		OPT3001();
		/**
		 * @brief Constructs a new OPT3001 with the given bus and device numbers.
		 * @param bus The I2C bus number
		 * @param device The device address
		 */
		OPT3001(uint8_t bus, uint8_t device);
		OPT3001(const OPT3001 &other) = delete; // Forbid copy construction for safety
		/**
		 * @brief Destructor
		 */
		virtual ~OPT3001();
		
		
		/**
		 * @brief Updates information by reading device registers.
		 */
		void ReadState();
		
		/**
		 * @brief Writes the configuration data
		 * @param config The configuration to use
		 */
		bool SetConfiguration(Configuration config);
		
		/**
		 * @brief Returns configuration details for this device.
		 * @return The configuration
		 */
		inline Configuration GetConfiguration() const {
			return config;
		}
		
		/**
		 * @brief Retrieves the latest lux reading
		 * @return The lux
		 */
		float GetLux() const;
		
		/**
		 * @brief Retrieves the upper limit for lux
		 * @return The upper limit
		 */
		float GetHighLimit() const;
		
		/**
		 * @brief Retrieves the lower limit for lux
		 * @return The lower limit
		 */
		float GetLowLimit() const;
		
		
		inline ResultData GetResultRegister() const {
			return result;
		}
		
		inline ResultData GetLowLimitRegister() const {
			return low_limit;
		}
		
		inline ResultData GetHighLimitRegister() const {
			return high_limit;
		}
		
		inline uint16_t GetManufacturerID() const {
			return manufacturer_id;
		}
		
		inline uint16_t GetDeviceID() const {
			return device_id;
		}
		
		
		
		
	private:
		// Data pulled from Result, High Limit, and Low Limit registers
		ResultData result;
		ResultData low_limit;
		ResultData high_limit;
		
		// The configuration used
		Configuration config;
		
		uint16_t manufacturer_id;
		uint16_t device_id;
	};
	
}


#endif
