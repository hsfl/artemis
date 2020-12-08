
#ifndef CUBESAT_DEVICE_SWITCH
#define CUBESAT_DEVICE_SWITCH

#define SWITCH_COUNT 3

#define SWITCH_HEATER_NAME "sw_heater"
#define SWITCH_TEMPSENSOR_NAME "sw_temp"
#define SWITCH_SUNSENSOR_NAME "sw_ss"
#define SWITCH_PAYLOAD_NAME "sw_raspi"

#warning Determine the correct pins
#define SWITCH_HEATER_KEY "P9_14"
#define SWITCH_TEMPSENSOR_KEY "P9_14"
#define SWITCH_SUNSENSOR_KEY "P9_14"
#define SWITCH_PAYLOAD_KEY "P9_14"

#include "device/GPIO.h"


namespace artemis {
	
	
	enum class SwitchID : int {
		Heater = 0, // name: "heater"
		TempSensor = 1, // name: "temp"
		SunSensor = 2, // name: "ss"
		Payload = 3, // name: "payload"
	};
	
	struct SwitchedDeviceInfo {
		const char *name; // The name of the device (e.g. "temp")
		const char *key; // The pin key for the switch (e.g. "P9_14")
	};
	
	enum class SwitchState : int {
		Invalid = -1,
		Off = 0,
		On = 1
	};
	
	/**
	 * @brief A class for controlling the switched lines to the EPS.
	 * Inherits from the GPIO class
	 */
	class PDUSwitch : protected GPIO {
	public:
		using GPIO::GetPinKey;
		using GPIO::GetPinNumber;
		
		PDUSwitch(const char *name);
		virtual ~PDUSwitch();
		
		bool IsValid() const {
			return (int)switch_id >= 0 && (int)switch_id < SWITCH_COUNT;
		}
		
		/**
		 * @brief Sets the state of the switch
		 * @param state The state of the switch
		 * @return The state the switch was set to
		 */
		SwitchState SetState(SwitchState state);
		
		/**
		 * @brief Returns the state of the switch
		 * @return The state of the switch
		 */
		SwitchState GetState();
		
		static const char* GetSwitchName(SwitchID switch_id);
		static SwitchID GetSwitchID(const char *switch_name);
		static const char* GetSwitchPinKey(SwitchID switch_id);
		static int GetSwitchPin(SwitchID switch_id);
		static int GetSwitchPin(const char *switch_name);
		
	private:
		static SwitchedDeviceInfo switch_info[SWITCH_COUNT + 1];
		
		const char *name;
		SwitchID switch_id;
		
	};
	
	
}


#endif
