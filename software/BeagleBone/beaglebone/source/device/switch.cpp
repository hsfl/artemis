
#include "device/switch.h"

#include <cstdlib>
#include <cstring>
#include <stdio.h>

using namespace std;
using namespace artemis;

SwitchedDeviceInfo PDUSwitch::switch_info[] = {
	{SWITCH_HEATER_NAME, SWITCH_HEATER_KEY},
	{SWITCH_TEMPSENSOR_NAME, SWITCH_TEMPSENSOR_KEY},
	{SWITCH_SUNSENSOR_NAME, SWITCH_SUNSENSOR_KEY},
	{NULL, NULL}
};

PDUSwitch::PDUSwitch(const char *name) : GPIO(GetSwitchPin(name)), name(name) {
	
	switch_id = GetSwitchID(name);
	
	
	// Set the GPIO to OUTPUT mode
	if ( IsValid() ) {
		GPIO::SetMode(GPIOMode::Output);
	}
	
}
PDUSwitch::~PDUSwitch() {
	
}



SwitchState PDUSwitch::SetState(SwitchState state) {
	if ( !IsValid() )
		return SwitchState::Invalid;
	
	return (SwitchState)GPIO::DigitalWrite((GPIOValue)state);
}

SwitchState PDUSwitch::GetState() {
	if ( !IsValid() )
		return SwitchState::Invalid;
	
	return (SwitchState)GPIO::DigitalRead();
}


const char* PDUSwitch::GetSwitchName(SwitchID switch_id) {
	
	if ( (int)switch_id < 0 || (int)switch_id >= SWITCH_COUNT )
		return NULL;
	else
		return switch_info[(int)switch_id].name;
}
SwitchID PDUSwitch::GetSwitchID(const char *switch_name) {
	if ( switch_name == NULL )
		return (SwitchID)-1;
	
	for (int i = 0; i < SWITCH_COUNT; ++i) {
		if ( strcmp(switch_info[i].name, switch_name) == 0 ) {
			return (SwitchID)i;
		}
	}
	
	return (SwitchID)-1;
}
const char* PDUSwitch::GetSwitchPinKey(SwitchID switch_id) {
	if ( (int)switch_id < 0 || (int)switch_id >= SWITCH_COUNT )
		return NULL;
	else
		return switch_info[(int)switch_id].key;
}
int PDUSwitch::GetSwitchPin(SwitchID switch_id) {
	if ( (int)switch_id < 0 || (int)switch_id >= SWITCH_COUNT )
		return -1;
	else
		return GetPinByKey(switch_info[(int)switch_id].key);
}
int PDUSwitch::GetSwitchPin(const char *switch_name) {
	return GetSwitchPin(GetSwitchID(switch_name));
}
