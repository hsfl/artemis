
#include <iostream>
#include <fstream>
#include  <iomanip>
#include "device/GPIO.h"
#include "device/switch.h"
#include "support/configCosmos.h"

 
using namespace std;
using namespace artemis;


void TestSwitch(const char *device_name, int blink_count = 5) {
	cout << "Blinking switch '" << device_name << "' for " << blink_count << " times" << endl;
	PDUSwitch sw(device_name);
	
	// Blink the output a few times
	for (int i = 0; i < blink_count * 2; ++i) {
		sw.SetState((SwitchState)(i % 2));
		COSMOS_SLEEP(1);
	}
}


int main(int argc, char ** argv) {
	
	
	switch ( argc ) {
		case 2:
			TestSwitch(argv[1]);
			break;
		case 3:
			TestSwitch(argv[1], atoi(argv[2]));
			break;
		default:
			printf("Usage: switch_test device_name [blink_count]\n");
			printf("Ex: switch_test heater 5\n");
			printf("\tdevice_name: the device name, one of:\n");
			for (int i = 0; i < SWITCH_COUNT; ++i) {
				printf("\t\t%s\n", PDUSwitch::GetSwitchName((SwitchID)i));
			}
			break;
	}
	
	
	//TestSwitch();
	
	
    return 0;
}

