
#include <iostream>
#include <fstream>
#include  <iomanip>
#include "device/temp_sensors.h"
#include "support/configCosmos.h"
#include "device/ADT7311.h"

 
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
		printf("SPI bus number must be either 0 or 1\n");
		return;
	}
	// Check if device address is valid
	else if ( addr < 0 || addr > 0xFF ) {
		printf("Device address must range from 0 to 0xFF\n");
		return;
	}
	
	
	printf("Testing temperature sensor on bus %d at address %#04x for %d seconds.\n", bus, addr, duration);
	
	// Number of samples to take each second
	const int samples_per_sec = 5;
	
	// Store some statistics
	float temp = 0;
	float total_temp = 0;
	float min_temp = 0;
	float max_temp = 0;
	
	// Print the configuration
	ADT7311::Configuration config;
	config.fault_queue = 0;
	config.ct_pin_polarity = 0;
	config.int_pin_polarity = 0;
	config.int_ct_mode = 0;
	config.operation_mode = 0;
	config.resolution = 0;
	
	printf("========== ADT7311 Configuration ==========\n");
	printf("Fault Queue:      %d (", config.fault_queue); PrintBinary(config.fault_queue, 2); printf(")\n");
	printf("CT Pin Polarity:  %d (", config.ct_pin_polarity); PrintBinary(config.ct_pin_polarity, 1); printf(")\n");
	printf("INT Pin Polarity: %d (", config.int_pin_polarity); PrintBinary(config.int_pin_polarity, 1); printf(")\n");
	printf("INT/CT Mode:      %d (", config.int_ct_mode); PrintBinary(config.int_ct_mode, 1); printf(")\n");
	printf("Operation Mode:   %d (", config.operation_mode); PrintBinary(config.operation_mode, 2); printf(")\n");
	printf("Resolution:       %d (", config.resolution); PrintBinary(config.resolution, 1); printf(")\n");
	printf("===========================================\n\n");
	printf("Connecting to ADT7311\n");
	
	// Create the sensor object
	ADT7311 sensor(bus, addr);
	printf("Setting configuration\n");
	sensor.SetConfiguration(config);
	
	
	for (int i = 0; i < duration * samples_per_sec; ++i) {
		
		// Update sensor
		sensor.ReadState();
		
		// Get temperature
		temp = sensor.GetTemperature();
		printf("Sample %d: Read temperature as %f C\n", i + 1, temp);
		
		// Other stuff
		if ( i == 0 )
			min_temp = max_temp = temp;
		else {
			if ( temp < min_temp )
				min_temp = temp;
			if ( temp > max_temp )
				max_temp = temp;
		}
		
		total_temp += temp;
		
		// Wait for a bit
		COSMOS_SLEEP(1.0f / samples_per_sec);
	}
	
	// Print temperature stats
	printf("Collected %d samples over %d seconds\n", duration * samples_per_sec, duration);
	printf("==========================\n");
	printf("Average: %f C\n", total_temp / (duration * samples_per_sec));
	printf("Minimum: %f C\n", min_temp);
	printf("Maximum: %f C\n", max_temp);
	
	
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
			printf("Usage: temp_test spi_bus dev_addr [duration_sec]\n");
			printf("Ex: temp_test 1 0x68\n");
			break;
	}
	
	
	return 0;
}

