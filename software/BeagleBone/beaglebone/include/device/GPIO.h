
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
	
	enum class GPIOMode : int {
		Invalid = -1,
		Input = 0,
		Output = 1,
	};
	
	enum class GPIOValue : int {
		Invalid = -1,
		Low = 0,
		High = 1
	};
	
	
	
	class GPIO {
	public:
		GPIO() : pin(-1) {}
		GPIO(Pin pin);
		GPIO(const char *pin_key);
		virtual ~GPIO();
		
		GPIOMode SetMode(GPIOMode mode);
		GPIOMode GetMode();
		
		GPIOValue DigitalWrite(GPIOValue value);
		GPIOValue DigitalRead();
		
		inline const char* GetPinKey() const {
			return GetKeyByPin(pin);
		}
		inline int GetPinNumber() const {
			return pin;
		}
		
		
		static Pin GetPinByKey(const char *key);
		static Pin GetPinByName(const char *name);
		static const char* GetNameByPin(Pin pin);
		static const char* GetKeyByPin(Pin pin);
		
	protected:
		static PinInfo pin_table[97];
		
		Pin pin;
	};
	

}

#endif
