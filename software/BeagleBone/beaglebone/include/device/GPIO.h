
#ifndef CUBESAT_DEVICE_GPIO
#define CUBESAT_DEVICE_GPIO

#include <stdint.h>

#define SYSFS_GPIO_DIR "/sys/class/gpio"

namespace artemis {
	
	typedef unsigned int Pin;
	
	struct PinInfo {
		const char *name;
		const char *key;
		Pin gpio;
		int pwm_mux_mode;
		int ain;
		int isAllocatedByDefault;
	};
	
	//! The mode (i.e. direction) of a GPIO pin
	enum class GPIOMode : int {
		//! An invalid state
		Invalid = -1,
		//! Input (read) mode
		Input = 0,
		//! Output (write) mode
		Output = 1,
	};
	
	//! The value of a GPIO pin
	enum class GPIOValue : int {
		//! An invalid state
		Invalid = -1,
		//! Low voltage (zero) value
		Low = 0,
		//! High voltage (one) value
		High = 1
	};
	
	
	/**
	 * @brief Utility class for controlling GPIO pins
	 */
	class GPIO {
	public:
		/**
		 * @brief Default constructor. Does not correspond to a valid pin.
		 */
		GPIO() : pin(-1) {}
		/**
		 * @brief Initializes the GPIO with the given pin number
		 * @param pin The absolute pin number
		 */
		GPIO(Pin pin);
		/**
		 * @brief Initializes the GPIO with the given pin key
		 * @param pin_key The pin key (e.g. P9_14)
		 */
		GPIO(const char *pin_key);
		/**
		 * @brief Destructor
		 */
		virtual ~GPIO();
		
		
		/**
		 * @brief Sets the direction of the GPIO pin as either input or output
		 * @param mode The mode
		 * @return The new mode
		 */
		GPIOMode SetMode(GPIOMode mode);
		/**
		 * @brief Gets the direction of the GPIO pin
		 * @return The mode
		 */
		GPIOMode GetMode();
		
		/**
		 * @brief Sets the pin to either high or low
		 * @param value The value to set
		 * @return The current value
		 */
		GPIOValue DigitalWrite(GPIOValue value);
		/**
		 * @brief Gets the current value of the GPIO pin
		 * @return The current value
		 */
		GPIOValue DigitalRead();
		
		/**
		 * @brief Returns the key of the pin
		 * @return The pin key
		 */
		inline const char* GetPinKey() const {
			return GetKeyByPin(pin);
		}
		/**
		 * @brief Returns the number of the pin
		 * @return The pin number
		 */
		inline int GetPinNumber() const {
			return pin;
		}
		
		
		/**
		 * @brief Gets the number of a pin, given its key
		 * @param key The pin key
		 * @return The pin number
		 */
		static Pin GetPinByKey(const char *key);
		/**
		 * @brief Gets the number of a pin, given its name
		 * @param name The pin name
		 * @return The pin number
		 */
		static Pin GetPinByName(const char *name);
		/**
		 * @brief Gets the name of a pin, given its number
		 * @param pin The pin number
		 * @return The pin name
		 */
		static const char* GetNameByPin(Pin pin);
		/**
		 * @brief Gets the key of a pin, given its number
		 * @param pin The pin number
		 * @return The pin key
		 */
		static const char* GetKeyByPin(Pin pin);
		
	protected:
		//! A lookup table for pin attributes
		static PinInfo pin_table[97];
		
		//! The pin number
		Pin pin;
	};
	

}

#endif
