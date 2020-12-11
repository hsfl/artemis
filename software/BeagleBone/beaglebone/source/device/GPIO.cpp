
#include "device/GPIO.h"

#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <fstream>
#include <algorithm>

using namespace artemis;

PinInfo GPIO::pin_table[] = {
    { "USR0", "USR0", 53, -1, -1, 1 },
    { "USR1", "USR1", 54, -1, -1, 1 },
    { "USR2", "USR2", 55, -1, -1, 1 },
    { "USR3", "USR3", 56, -1, -1, 1 },
    { "DGND", "P8_1", 0, -1, -1, -1 },
    { "DGND", "P8_2", 0, -1, -1, -1 },
    { "GPIO1_6", "P8_3", 38, -1, -1, 1 },
    { "GPIO1_7", "P8_4", 39, -1, -1, 1 },
    { "GPIO1_2", "P8_5", 34, -1, -1, 1 },
    { "GPIO1_3", "P8_6", 35, -1, -1, 1 },
    { "TIMER4", "P8_7", 66, -1, -1, 0 },
    { "TIMER7", "P8_8", 67, -1, -1, 0 },
    { "TIMER5", "P8_9", 69, -1, -1, 0 },
    { "TIMER6", "P8_10", 68, -1, -1, 0 },
    { "GPIO1_13", "P8_11", 45, -1, -1, 0 },
    { "GPIO1_12", "P8_12", 44, -1, -1, 0 },
    { "EHRPWM2B", "P8_13", 23, 4, -1, 0 },
    { "GPIO0_26", "P8_14", 26, -1, -1, 0 },
    { "GPIO1_15", "P8_15", 47, -1, -1, 0 },
    { "GPIO1_14", "P8_16", 46, -1, -1, 0 },
    { "GPIO0_27", "P8_17", 27, -1, -1, 0 },
    { "GPIO2_1", "P8_18", 65, -1, -1, 0 },
    { "EHRPWM2A", "P8_19", 22, 4, -1, 0 },
    { "GPIO1_31", "P8_20", 63, -1, -1, 1 },
    { "GPIO1_30", "P8_21", 62, -1, -1, 1 },
    { "GPIO1_5", "P8_22", 37, -1, -1, 1 },
    { "GPIO1_4", "P8_23", 36, -1, -1, 1 },
    { "GPIO1_1", "P8_24", 33, -1, -1, 1 },
    { "GPIO1_0", "P8_25", 32, -1, -1, 1 },
    { "GPIO1_29", "P8_26", 61, -1, -1, 0 },
    { "GPIO2_22", "P8_27", 86, -1, -1, 1 },
    { "GPIO2_24", "P8_28", 88, -1, -1, 1 },
    { "GPIO2_23", "P8_29", 87, -1, -1, 1 },
    { "GPIO2_25", "P8_30", 89, -1, -1, 1 },
    { "UART5_CTSN", "P8_31", 10, -1, -1, 1 },
    { "UART5_RTSN", "P8_32", 11, -1, -1, 1 },
    { "UART4_RTSN", "P8_33", 9, -1, -1, 1 },
    { "UART3_RTSN", "P8_34", 81, 2, -1, 1 },
    { "UART4_CTSN", "P8_35", 8, -1, -1, 1 },
    { "UART3_CTSN", "P8_36", 80, 2, -1, 1 },
    { "UART5_TXD", "P8_37", 78, -1, -1, 1 },
    { "UART5_RXD", "P8_38", 79, -1, -1, 1 },
    { "GPIO2_12", "P8_39", 76, -1, -1, 1 },
    { "GPIO2_13", "P8_40", 77, -1, -1, 1 },
    { "GPIO2_10", "P8_41", 74, -1, -1, 1 },
    { "GPIO2_11", "P8_42", 75, -1, -1, 1 },
    { "GPIO2_8", "P8_43", 72, -1, -1, 1 },
    { "GPIO2_9", "P8_44", 73, -1, -1, 1 },
    { "GPIO2_6", "P8_45", 70, 3, -1, 1 },
    { "GPIO2_7", "P8_46", 71, 3, -1, 1 },
    { "DGND", "P9_1", 0, -1, -1, -1 },
    { "DGND", "P9_2", 0, -1, -1, -1 },
    { "VDD_3V3", "P9_3", 0, -1, -1, -1 },
    { "VDD_3V3", "P9_4", 0, -1, -1, -1 },
    { "VDD_5V", "P9_5", 0, -1, -1, -1 },
    { "VDD_5V", "P9_6", 0, -1, -1, -1 },
    { "SYS_5V", "P9_7", 0, -1, -1, -1 },
    { "SYS_5V", "P9_8", 0, -1, -1, -1 },
    { "PWR_BUT", "P9_9", 0, -1, -1, -1 },
    {"SYS_RESETn", "P9_10", 0, -1, -1, -1 },
    { "UART4_RXD", "P9_11", 30, -1, -1, 0 },
    { "GPIO1_28", "P9_12", 60, -1, -1, 0 },
    { "UART4_TXD", "P9_13", 31, -1, -1, 0 },
    { "EHRPWM1A", "P9_14", 50, 6, -1, 0 },
    { "GPIO1_16", "P9_15", 48, -1, -1, 0 },
    { "EHRPWM1B", "P9_16", 51, 6, -1, 0 },
    { "I2C1_SCL", "P9_17", 5, -1, -1, 0 },
    { "I2C1_SDA", "P9_18", 4, -1, -1, 0 },
    { "I2C2_SCL", "P9_19", 13, -1, -1, 1 },
    { "I2C2_SDA", "P9_20", 12, -1, -1, 1 },
    { "UART2_TXD", "P9_21", 3, 3, -1, 0 },
    { "UART2_RXD", "P9_22", 2, 3, -1, 0 },
    { "GPIO1_17", "P9_23", 49, -1, -1, 0 },
    { "UART1_TXD", "P9_24", 15, -1, -1, 0 },
    { "GPIO3_21", "P9_25", 117, -1, -1, 1 },
    { "UART1_RXD", "P9_26", 14, -1, -1, 0 },
    { "GPIO3_19", "P9_27", 115, -1, -1, 0 },
    { "SPI1_CS0", "P9_28", 113, 4, -1, 1 },
    { "SPI1_D0", "P9_29", 111, 1, -1, 1 },
    { "SPI1_D1", "P9_30", 112, -1, -1, 0 },
    { "SPI1_SCLK", "P9_31", 110, 1, -1, 1 },
    { "VDD_ADC", "P9_32", 0, -1, -1, -1 },
    { "AIN4", "P9_33", 0, -1, 4, -1 },
    { "GNDA_ADC", "P9_34", 0, -1, -1, -1 },
    { "AIN6", "P9_35", 0, -1, 6, -1 },
    { "AIN5", "P9_36", 0, -1, 5, -1 },
    { "AIN2", "P9_37", 0, -1, 2, -1 },
    { "AIN3", "P9_38", 0, -1, 3, -1 },
    { "AIN0", "P9_39", 0, -1, 0, -1 },
    { "AIN1", "P9_40", 0, -1, 1, -1 },
    { "CLKOUT2", "P9_41", 20, -1, -1, 0 },
    { "GPIO0_7", "P9_42", 7, 0, -1, 0 },
    { "DGND", "P9_43", 0, -1, -1, -1 },
    { "DGND", "P9_44", 0, -1, -1, -1 },
    { "DGND", "P9_45", 0, -1, -1, -1 },
    { "DGND", "P9_46", 0, -1, -1, -1 },
	{ NULL, NULL, 0, 0, 0, 0}
};

GPIO::GPIO(Pin pin) : pin(pin) {
	if ( pin < 0 ) {
		printf("GPIO initialized with invalid pin\n");
	}
}
GPIO::GPIO(const char *pin_key) {
	pin = GetPinByKey(pin_key);
	if ( pin < 0 ) {
		printf("GPIO initialized with invalid pin\n");
	}
}
GPIO::~GPIO() {
	
}


GPIOMode GPIO::SetMode(GPIOMode mode) {
	if ( pin < 0 )
		return GPIOMode::Invalid;
	
	char path[50];
	
	// Get the path to the GPIO control file
	snprintf(path, sizeof(path), SYSFS_GPIO_DIR "/gpio%u/direction", pin);
	
	// Attempt to open the GPIO control file
	std::ofstream stream(path);
	if ( !stream ) {
		fprintf(stderr, "Unable to set direction GPIO no. %u key: %s\n", pin, GetKeyByPin(pin));
		return GPIOMode::Invalid;
	}
	
	// Write the desired GPIO direction
	if ( mode == GPIOMode::Output )
		stream << "out";
	else
		stream << "in";
	
	stream.close();
	
	return mode;
}
GPIOMode GPIO::GetMode() {
	if ( pin < 0 )
		return GPIOMode::Invalid;
	
	
	char path[50], direction;
	
	// Get the path to the GPIO control file
	snprintf(path, sizeof(path), SYSFS_GPIO_DIR "/gpio%u/direction", pin);
	
	// Attempt to open the GPIO control file
	std::ifstream stream(path);
	if ( !stream ) {
		fprintf(stderr, "Unable to get direction GPIO no. %u key: %s\n", pin, GetKeyByPin(pin));
		return GPIOMode::Invalid;
	}
	
	// Read the GPIO direction character
	stream >> direction;
	stream.close();
	
	// Return the GPIO direction
	return (direction == 'i') ? GPIOMode::Input : GPIOMode::Output;
}

GPIOValue GPIO::DigitalWrite(GPIOValue value) {
	if ( pin < 0 )
		return GPIOValue::Invalid;
	
	char path[50];
	
	// Get the path to the GPIO value file
	snprintf(path, sizeof(path), SYSFS_GPIO_DIR "/gpio%u/value", pin);
	
	// Attempt to open the GPIO value file
	std::ofstream stream(path);
	if ( !stream ) {
		fprintf(stderr, "Unable to set value GPIO no. %u key: %s\n", pin, GetKeyByPin(pin));
		return GPIOValue::Invalid;
	}
	
	// Write the requested value
	stream << (int)value;
	stream.close();
	
	return value;
}

GPIOValue GPIO::DigitalRead() {
	if ( pin < 0 )
		return GPIOValue::Invalid;
	
	char path[50], value;
	
	// Get the path to the GPIO value file
	snprintf(path, sizeof(path), SYSFS_GPIO_DIR "/gpio%u/value", pin);
	
	// Attempt to open the GPIO value file
	std::ifstream stream(path);
	if ( !stream ) {
		fprintf(stderr, "Unable to get value GPIO no. %u key: %s\n", pin, GetKeyByPin(pin));
		return GPIOValue::Invalid;
	}
	
	// Read the GPIO value
	stream >> value;
	stream.close();
	
	return (value == '1') ? GPIOValue::High : GPIOValue::Low;
}



Pin GPIO::GetPinByKey(const char *key) {
	PinInfo *p;
	
	// Search the pin table for the corresponding pin number
	for (p = pin_table; p != NULL; ++p) {
		if ( strcmp(p->key, key) == 0 )
			return p->gpio;
	}
	
	return -1;
}
Pin GPIO::GetPinByName(const char *name) {
	PinInfo *p;
	
	// Search the pin table for the corresponding pin number
	for (p = pin_table; p != NULL; ++p) {
		if ( strcmp(p->name, name) == 0 )
			return p->gpio;
	}
	
	return -1;
}
const char* GPIO::GetNameByPin(Pin pin) {
	PinInfo *p;
	
	// Search the pin table for the corresponding pin number
	for (p = pin_table; p != NULL; ++p) {
		if ( p->gpio == pin )
			return p->name;
	}
	
	return NULL;
}
const char* GPIO::GetKeyByPin(Pin pin) {
	PinInfo *p;
	
	// Search the pin table for the corresponding pin number
	for (p = pin_table; p != NULL; ++p) {
		if ( p->gpio == pin )
			return p->key;
	}
	
	return NULL;
}

