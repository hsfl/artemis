
#include "device/OPT3001.h"

#include <cmath>


using namespace std;
using namespace artemis;



OPT3001::OPT3001(uint8_t bus, uint8_t device) : I2CDevice(bus, device) {
	
}
OPT3001::~OPT3001() {
	
}

int32_t OPT3001::ReadState() {
	if ( !IsOpen() )
        return ErrorNumbers::COSMOS_GENERAL_ERROR_NOTSTARTED;
	
    int32_t status;
    int16_t temp;
	// Read result register
    status = ReadRegister((uint8_t)Register::Result, temp);
    if(status < 0){
        return status;
    }
    result.raw_data = temp;
	
	// Read configuration register
    status = ReadRegister((uint8_t)Register::Config, temp);
    if(status < 0){
        return status;
    }
    config.raw_data = temp;
	
	// Read low limit register
    status = ReadRegister((uint8_t)Register::LowLimit, temp);
    if(status < 0){
        return status;
    }
    low_limit.raw_data = temp;
	
	// Read high limit register
    status = ReadRegister((uint8_t)Register::HighLimit, temp);
    if(status < 0){
        return status;
    }
    high_limit.raw_data = temp;
	
	// Read manufacturer ID register
    status = ReadRegister((uint8_t)Register::Manufacturer, temp);
    if(status < 0){
        return status;
    }
    manufacturer_id = temp;
	
	// Read device ID register
    status = ReadRegister((uint8_t)Register::DeviceID, temp);
    if(status < 0){
        return status;
    }
    device_id = temp;
    return status;
	
}

int32_t OPT3001::SetConfiguration(Configuration config) {
	if ( !IsOpen() )
        return ErrorNumbers::COSMOS_GENERAL_ERROR_NOTSTARTED;
	
	// Should we do 'this->config = config'? Maybe, but maybe the state of the device
	// since the last call to ReadState() should be kept instead
	return WriteRegister((uint8_t)Register::Config, config.raw_data) == 0;
}

float OPT3001::GetLux() const {
	// Convert the temperature from binary values to decimal
	return 0.01f * pow(2, result.exponent) * result.result;
}

float OPT3001::GetHighLimit() const {
	// Convert the temperature from binary values to decimal
	return 0.01f * pow(2, high_limit.exponent) * high_limit.result;
}

float OPT3001::GetLowLimit() const {
	// Convert the temperature from binary values to decimal
	return 0.01f * pow(2, low_limit.exponent) * low_limit.result;
}

