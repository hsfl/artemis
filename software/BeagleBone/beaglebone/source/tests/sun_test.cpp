
#include <iostream>
#include <fstream>
#include  <iomanip>
#include "device/temp_sensors.h"
#include "support/configCosmos.h"
#include "device/OPT3001.h"

 
using namespace std;
using namespace artemis;

void PrintBinary(uint8_t byte, int bits) {
	printf("0b");
	
	for (int i = 8 - bits; i < 8; i++) {
		printf("%d", !!((byte << i) & 0x80));
	}
}


void TestSensor(int bus, int addr, int duration = 5) {
	
	// Check if duration is valid
	if ( duration < 1 ) {
		printf("Duration must be greater than zero\n");
		return;
	}
	// Check if bus is valid
	else if ( bus < 0 || bus > 2 ) {
		printf("I2C bus number must be either 0, 1, or 2\n");
		return;
	}
	// Check if device address is valid
	else if ( addr < 0 || addr > 0xFF ) {
		printf("Device address must range from 0 to 0xFF\n");
		return;
	}
	
	
	printf("Testing sun sensor on bus %d at address %#04x for %d seconds.\n", bus, addr, duration);
	
	// Number of samples to take each second
	const int samples_per_sec = 5;
	
	// Store some statistics
	float lux = 0;
	float total_lux = 0;
	float min_lux = 0;
	float max_lux = 0;
	
	
	// Print the configuration
	printf("========== OPT3001 Configuration ==========\n");
	OPT3001::Configuration config;
	printf("Fault Count:        %d (", config.FaultCount); PrintBinary(config.FaultCount, 2); printf(")\n");
	printf("Mask Exponent:      %d (", config.MaskExponent); PrintBinary(config.MaskExponent, 1); printf(")\n");
	printf("Polarity:           %d (", config.Polarity); PrintBinary(config.Polarity, 1); printf(")\n");
	printf("Latch:              %d (", config.Latch); PrintBinary(config.Latch, 1); printf("\n)");
	printf("Flag Low:           %d (", config.FlagLow); PrintBinary(config.FlagLow, 1); printf(")\n");
	printf("Flag High:          %d (", config.FlagHigh); PrintBinary(config.FlagHigh, 1); printf(")\n");
	printf("Conversion Ready:   %d (", config.ConversionReady); PrintBinary(config.ConversionReady, 1); printf(")\n");
	printf("Overflow Flag:      %d (", config.OverflowFlag); PrintBinary(config.OverflowFlag, 1); printf(")\n");
	printf("Mode of Conversion: %d (", config.ModeOfConversionOperation); PrintBinary(config.ModeOfConversionOperation, 2); printf(")\n");
	printf("Conversion Time:    %d (", config.ConversionTime); PrintBinary(config.ConversionTime, 1); printf(")\n");
	printf("Range Number:       %d (", config.RangeNumber); PrintBinary(config.RangeNumber, 4); printf(")\n");
	printf("===========================================\n\n");
	printf("Connecting to OPT3001\n");
	
	// Create the sensor object
	OPT3001 sensor(bus, addr);
	printf("Setting configuration\n");
	sensor.SetConfiguration(config);
	
	
	for (int i = 0; i < duration * samples_per_sec; ++i) {
		
		// Update sensor
		sensor.ReadState();
		
		// Get lux
		lux = sensor.GetLux();
		printf("Sample %d: Read illuminance as %f lx\n", i + 1, lux);
		
		// Other stuff
		if ( i == 0 )
			min_lux = max_lux = lux;
		else {
			if ( lux < min_lux )
				min_lux = lux;
			if ( lux > max_lux )
				max_lux = lux;
		}
		
		total_lux += lux;
		
		// Wait for a bit
		COSMOS_SLEEP(1.0f / samples_per_sec);
	}
	
	// Print illuminance stats
	printf("Collected %d samples over %d seconds\n", duration * samples_per_sec, duration);
	printf("==========================\n");
	printf("Average: %f lx\n", total_lux / (duration * samples_per_sec));
	printf("Minimum: %f lx\n", min_lux);
	printf("Maximum: %f lx\n", max_lux);
	
	
}


int main(int argc, char ** argv) {
	
	switch ( argc ) {
		case 3:
			TestSensor(atoi(argv[1]), (int)strtol(argv[2], NULL, 0));
			break;
		case 4:
			TestSensor(atoi(argv[1]), (int)strtol(argv[2], NULL, 0), atoi(argv[3]));
			break;
		default:
			printf("Usage: sun_test i2c_bus dev_addr [duration_sec]\n");
			printf("Ex: sun_test 1 0x68\n");
			break;
	}
	
	
	return 0;
}

