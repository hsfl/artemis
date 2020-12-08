
#ifndef CUBESAT_DEVICE_ADT7311
#define CUBESAT_DEVICE_ADT7311

#include "device/SPIDevice.h"

namespace artemis {
	
	
	
	/**
	 * @brief Provides access to the ADT7311 temperature sensor.
	 */
	class ADT7311 : protected SPIDevice {
	public:
		
		/**
		 * @brief Register addresses
		 */
		enum class Register : uint8_t {
			Status = 0x00,
			Config = 0x01,
			Temperature = 0x02,
			Manufacturer_ID = 0x03,
			CritSetPoint = 0x04,
			HystSetPoint = 0x05,
			HighSetPoint = 0x06,
			LowSetPoint = 0x07
		};
		
		
		/**
		 * @brief Configuration flags
		 */
		union Configuration {
			uint8_t raw_data;
			
			struct {
				uint8_t fault_queue : 2;
				uint8_t ct_pin_polarity : 1;
				uint8_t int_pin_polarity : 1;
				uint8_t int_ct_mode : 1;
				uint8_t operation_mode : 2;
				uint8_t resolution : 1;
			};
		};
		/**
		 * @brief Stores temperature data for 13-bit resolution mode
		 */
		union TemperatureData {
			uint16_t raw_data;
			
			struct {
				uint8_t low_flag : 1;
				uint8_t high_flag : 1;
				uint8_t crit_flag : 1;
				uint16_t temperature : 12;
				uint8_t sign : 1;
			};
		};
		
		/**
		 * @brief Stores data from the Status register
		 */
		union StatusData {
			uint8_t raw_data;
			
			struct {
				uint8_t _unused : 4; // Don't use this
				uint8_t low_flag : 1;
				uint8_t high_flag : 1;
				uint8_t crit_flag : 1;
				uint8_t rdy : 1;
			};
		};
		
		/**
		 * @brief Stores data from the Manufacturer ID register
		 */
		union ManufacturerData {
			uint8_t raw_data;
			
			struct {
				uint8_t revision_id : 3;
				uint8_t manufacturer_id : 5;
			};
		};
		
		
	public:
		using SPIDevice::Open;
		using SPIDevice::Close;
		using SPIDevice::IsOpen;
		using SPIDevice::GetBus;
		using SPIDevice::GetDeviceAddr;
		
				
		ADT7311() : SPIDevice(0, 0) {} // TODO: remove this
		/**
		 * @brief Constructs a new ADT7311 object with the given bus and device address
		 * @param bus The bus address
		 * @param device The device address
		 */
		ADT7311(unsigned int bus, unsigned int device);
		/**
		 * @brief Destructor
		 */
		virtual ~ADT7311();
		
		
		virtual bool Open() override;
		
		/**
		 * @brief Reads and stores information from the device.
		 */
		void ReadState();
		
		/**
		 * @brief Writes to the configuration register.
		 * @param config The configuration data.
		 */
		void SetConfiguration(Configuration &config);
		
		/**
		 * @brief Writes to the low setpoint register
		 * @param temp The low setpoint temperature in celcius
		 */
		void SetLowSetpoint(int16_t temp);
		
		/**
		 * @brief Writes to the high setpoint register
		 * @param temp The high setpoint temperature in celcius
		 */
		void SetHighSetpoint(int16_t temp);
		
		/**
		 * @brief Writes to the hyst. setpoint register
		 * @param temp The hyst. temperature in celcius
		 */
		void SetHystSetpoint(uint8_t temp);
		
		/**
		 * @brief Writes to the critical setpoint register
		 * @param temp The critical temperature in celcius
		 */
		void SetCritSetpoint(int16_t temp);
		
		/**
		 * @brief Retrieves the low setpoint value
		 * @return The low setpoint in celcius
		 */
		inline int16_t GetLowSetpoint() const {
			return static_cast<int16_t>(low_setpoint);
		}
		
		/**
		 * @brief Retrieves the high setpoint value
		 * @return The high setpoint in celcius
		 */
		inline int16_t GetHighSetpoint() const {
			return static_cast<int16_t>(high_setpoint);
		}
		
		/**
		 * @brief Retrieves the critical setpoint value
		 * @return The critical setpoint in celcius
		 */
		inline int16_t GetCritSetpoint() const {
			return static_cast<int16_t>(crit_setpoint);
		}
		
		/**
		 * @brief Retrieves the hyst. setpoint value
		 * @return The hyst. setpoint in celcius
		 */
		inline uint8_t GetHystSetpoint() const {
			return hyst_setpoint;
		}
		
		/**
		 * @brief Returns the latest temperature reading
		 * @return The temperature in celcius
		 */
		float GetTemperature() const;
		
		/**
		 * @brief Checks if the low temperature flag was triggered
		 * @return True if set, false if not
		 */
		inline bool GetLowTempFlag() const {
			return status.low_flag;
		}
		
		/**
		 * @brief Checks if the high temperature flag was triggered
		 * @return True if set, false if not
		 */
		inline bool GetHighTempFlag() const {
			return status.high_flag;
		}
		
		/**
		 * @brief Checks if the critical temperature flag was triggered
		 * @return True if set, false if not
		 */
		inline bool GetCritTempFlag() const {
			return status.crit_flag;
		}
		
		inline Configuration GetConfiguration() const {
			return config;
		}
		
		inline TemperatureData GetTemperatureRegister() const {
			return temp_data;
		}
		
		inline StatusData GetStatusRegister() const {
			return status;
		}
		
		inline ManufacturerData GetManufacturerRegister() const {
			return manufacturer_data;
		}
		
		inline uint16_t GetCritSetpointRegister() const {
			return crit_setpoint;
		}
		
		inline uint8_t GetHystSetpointRegister() const {
			return hyst_setpoint;
		}
		
		inline uint16_t GetLowSetpointRegister() const {
			return low_setpoint;
		}
		
		inline uint16_t GetHighSetpointRegister() const {
			return high_setpoint;
		}
		
		
		
	private:
		// Register data
		Configuration config; // Config register value
		StatusData status; // Status register value
		TemperatureData temp_data; // Temperature register value
		ManufacturerData manufacturer_data;
		
		// Setpoint register data
		uint16_t low_setpoint; // Low setpoint register value
		uint16_t high_setpoint; // High setpoint register value
		uint16_t crit_setpoint; // Critical setpoint register value
		uint8_t hyst_setpoint; // Hysteresis setpoint register value
		
		
		// ================ SPI helper stuff ================
		enum CommandMode : uint8_t {
			Write = 0,
			Read = 1,
		};
		
		uint8_t GetCommand(CommandMode mode, Register reg);
		void Write8Bit(Register reg, uint8_t value);
		void Write16Bit(Register reg, uint16_t value);
		uint8_t Read8Bit(Register reg);
		uint16_t Read16Bit(Register reg);
	};
	
}


#endif
