
#include "SimpleAgent/SimpleAgent.h"
#include "device/PyCubed.h"

#include <iostream>
#include <fstream>
#include  <iomanip>



 
 
using namespace std;
using namespace artemis;

SimpleAgent *agent;

PyCubed *pycubed;
PyCubed *handler = nullptr;
bool shutdown_received = false;

void Shutdown();

// Request to send a message to the PyCubed
string SendMessage(vector<string> &args, int32_t &error);


int main(int argc, char ** argv) {
	
	int uart_device, baud_rate;
	
	switch ( argc ) {
		case 3:
			uart_device = atoi(argv[1]);
			baud_rate = atoi(argv[2]);
			break;
		default:
			printf("Usage: pycubed_test uart_num baud_rate\n");
			printf("Defaulting to uart=1 and baud_rate=9600");
			uart_device = 1;
			baud_rate = 9600;
	}
	
	// Set up the agent
	agent = new SimpleAgent("pycubed");
	agent->set_activity_period(0.5);
    agent->add_request("send", SendMessage, "<message type> <arg1> <arg2...>", "Send a message to the PyCubed");
    agent->set_soh();
	
	// Connect to the PyCubed
	pycubed = new PyCubed(uart_device, baud_rate);
	pycubed->SetShutdownCallback(Shutdown);
	
	printf("Attempting to connect to PyCubed on UART%d with baud %d\n", uart_device, baud_rate);
	
	
	
	// Attempt to connect to the PyCubed
	const int kConnectAttempts = 5;
	for (int i = 0; i < kConnectAttempts; ++i) {
		
		// Check if the device can be opened
		if ( pycubed->Open() < 0 ) {
			printf("Failed to connect to PyCubed. Trying again...\n");
			pycubed->Close();
			Time::Sleep(1);
		}
		else {
			printf("Successfully connected to PyCubed\n");
			break;
		}
	}
	
	
	// Exit if the PyCubed is not open
	if ( !pycubed->IsOpen() ) {
		
		// Exit upon failure to connect
		printf("Fatal: could not connect to PyCubed\n");
		delete pycubed;
		agent->Shutdown();
		delete agent;
		exit(1);
	}
	
	
	
	
	
	
	
	PyCubedIMUInfo imu;
	PyCubedGPSInfo gps;
	PyCubedPowerInfo power;
	PyCubedTempInfo temp;
	
	
	printf("======================================\n");
	
	
	while ( agent->StartLoop() ) {
		printf("Polling messages from PyCubed\n");
		
		// Receive messages from the PyCubed
		int messages_received = 0;
		while ( pycubed->ReceiveMessages() ) {
			++messages_received;
		}
		
		if ( messages_received == 0 ) {
			continue;
		}
		
		// Retrieve device info
		imu = pycubed->GetIMUInfo();
		gps = pycubed->GetGPSInfo();
		power = pycubed->GetPowerInfo();
		temp = pycubed->GetTempInfo();
		
		printf("======================================\n");
		printf("IMU Data: \n");
		printf("\tTimestamp: %f\n", imu.utc);
		printf("\tAccel:    (%.2f, %.2f, %.2f)\n", imu.acceleration.x, imu.acceleration.y, imu.acceleration.z);
		printf("\tMagnetic: (%.2f, %.2f, %.2f)\n", imu.magnetometer.x, imu.magnetometer.y, imu.magnetometer.z);
		printf("\tGyro:     (%.2f, %.2f, %.2f)\n", imu.gyroscope.x, imu.gyroscope.y, imu.gyroscope.z);
		printf("\n");
		
		printf("GPS Data: \n");
		printf("\tTimestamp: %f\n", gps.utc);
		printf("\tHas Fix: %s\n", gps.has_fix ? "true" : "false");
		printf("\tLatitude: %.4f degrees\n", gps.latitude);
		printf("\tLongitude: %.4f degrees\n", gps.longitude);
		printf("\tAltitude: %.2f m\n", gps.altitude);
		printf("\tSpeed: %.2f m/s\n", gps.speed);
		printf("\tFix Quality: %d\n", gps.fix_quality);
		printf("\tSatellites Used: %d\n", gps.sats_used);
		printf("\tAzimuth: %.2f degrees\n", gps.azimuth);
		printf("\tHoriz. Dilution: %.2f\n", gps.horizontal_dilution);
		printf("\n");
		
		printf("Temperature Data: \n");
		printf("\tTimestamp: %f\n", temp.utc);
		printf("\tCPU Temp: %.2f\n", temp.cpu_temp);
		printf("\tBattery Temp: %.2f\n", temp.batt_temp);
		printf("\n");
		
		printf("Power Data: \n");
		printf("\tTimestamp: %f\n", power.utc);
		printf("\tBattery Voltage: %.2f V\n", power.batt_voltage);
		printf("\tBattery Current: %.2f mA\n", power.batt_current);
		printf("\tSystem Voltage: %.2f V\n", power.sys_voltage);
		printf("\tSystem Current: %.2f mA\n", power.sys_current);
		printf("======================================\n");
		
		Time::Sleep(2);
	}
	
	// Test startup confirmation signal
	printf("Sending startup confirmation signal\n\n");
	pycubed->StartupConfirmation();
	
	Time::Sleep(1);
	
	// Test kill radio signal
	printf("Sending 'kill radio' signal\n\n");
	pycubed->KillRadio();
	
	Time::Sleep(1);
	
	// Test shutdown signal
	printf("Waiting for shutdown signal...\n");
	const int kShutdownWait = 10;
	
	for (int i = 0; i < kShutdownWait && !shutdown_received; ++i) {
		
		// Poll messages
		pycubed->ReceiveMessages();
		
		if ( !shutdown_received )
			printf("No shutdown signal received\n");
		
		Time::Sleep(1);
	}
	
	if ( !shutdown_received ) {
		printf("Did not receive shutdown signal: timed out\n");
	}
	
	
	printf("Test complete. Exiting now.\n");
    handler->Close();

    delete pycubed;
    delete handler;
	delete agent;
	
	
	return 0;
}

void Shutdown() {
	shutdown_received = true;
	
	printf("Shutdown signal received.\n");
	printf("Sending 'handoff' signal.\n");
	
	// Send the handoff signal
	pycubed->Handoff();
	
	COSMOS_SLEEP(2);
}

string SendMessage(vector<string> &args, int32_t &error) {

    // Make sure the PyCubed is connected first
    if ( !handler->IsOpen() )
        return "false";

    // Parse the string into a vector of arguments
    if(args.size() == 0) {
        error = ErrorNumbers::COSMOS_GENERAL_ERROR_EMPTY;
        return "incorrect usage";
    }
    string message_type = args[0];
    args.erase(args.begin());

    // Send the message
    return handler->SendMessage(message_type, args) ? "true" : "false";
}

