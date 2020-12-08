
#include <iostream>
#include <fstream>
#include  <iomanip>
#include "device/GPIO.h"
#include "device/switch.h"
#include "support/configCosmos.h"

 
using namespace std;
using namespace artemis;

void TestGPIOClass(const char *pin_key, int blink_count = 5) {
	cout << "Blinking GPIO pin '" << pin_key << "' for " << blink_count << " times" << endl;
	
	// Get the pin number by key
	// For P9_14, the pin number is 50
	Pin pin = GPIO::GetPinByKey(pin_key);
	
	// Create a new GPIO object for the pin
	GPIO gpio(pin);
	
	// Set the GPIO mode to OUTPUT
	gpio.SetMode(GPIOMode::Output);
	
	// Blink the output a few times
	for (int i = 0; i < blink_count * 2; ++i) {
		gpio.DigitalWrite((GPIOValue)(i % 2));
		COSMOS_SLEEP(1);
	}
}


int main(int argc, char ** argv) {
	
	switch ( argc ) {
		case 2:
			TestGPIOClass(argv[1]);
			break;
		case 3:
			TestGPIOClass(argv[1], atoi(argv[2]));
			break;
		default:
			printf("Usage: gpio_test pin_key [blink_count]\n");
			printf("Ex: gpio_test P9_14 10\n");
			break;
	}
	
	
	
	
    return 0;
}

