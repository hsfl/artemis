
// Internal headers
#include "SimpleAgent/SimpleAgent.h"
#include "device/ADT7311.h"
#include "device/temp_sensors.h"

#include <iostream>
#include <fstream>

// The interval between iterations in the run_agent() function
#define SLEEP_TIME 1

using namespace std;
using namespace cubesat;

//! Allows for usage of COSMOS
SimpleAgent *agent;

//! The SimpleAgent temperature sensor devices
TemperatureSensor *temp_sensors[TEMPSENSOR_COUNT];

//! The ADT7311 device handlers
ADT7311 *handlers[TEMPSENSOR_COUNT];

//! The sensor configuration
ADT7311::Configuration default_sensor_config;
bool should_enable_sensors = true; // Whether or not the temperature sensors should be enabled
bool sensors_powered = false; // Whether or not the temperature sensors are actually enabled

struct DeviceAddress {
	uint8_t spi_bus;
	uint8_t dev_addr;
};
DeviceAddress device_addresses[TEMPSENSOR_COUNT] =  {
	{0x00, 0x00},
	{0x00, 0x00},
	{0x00, 0x00},
	{0x00, 0x00},
	{0x00, 0x00},
};

// |----------------------------------------------|
// |                  Prototypes                  |
// |----------------------------------------------|

//! Initializes the sensor devices
void InitSensors();

//! Attempts to connect a sensor
bool ConnectSensor(int index);

//! Wraps up communication with the sensor devices.
void DestroySensors();

//! Updates the temperature readings for a non-pycubed-connected sensor
void UpdateNormalTemperature(int index);

//! Grabs the latest readings from the sensor devices
void UpdateTemperatures();

//! Enables/disables power to sensors via agent_switch
void SetSensorPower(bool enabled);


//! Request for displaying temperatures
float Request_Sensor_Temperature(TemperatureSensor *sensor);

//! Request for listing sensors
string Request_List();


// |----------------------------------------------|
// |                 Main Function                |
// |----------------------------------------------|

int main(int argc, char** argv) {
	
	// Create the agent
	agent = new SimpleAgent(CUBESAT_AGENT_TEMP_NAME);
	agent->SetLoopPeriod(SLEEP_TIME);
	agent->AddRequest("list", Request_List, "Returns a list of sensors");
	
	// Add the temperature sensor devices
	temp_sensors[0] = agent->NewDevice<TemperatureSensor>(TEMPSENSOR_EPS_NAME);
	temp_sensors[1] = agent->NewDevice<TemperatureSensor>(TEMPSENSOR_OBC_NAME);
	temp_sensors[2] = agent->NewDevice<TemperatureSensor>(TEMPSENSOR_PAYLOAD_NAME);
	temp_sensors[3] = agent->NewDevice<TemperatureSensor>(TEMPSENSOR_BATT_NAME);
	temp_sensors[4] = agent->NewDevice<TemperatureSensor>(TEMPSENSOR_PYCUBED_NAME);
	
	// Initialize the temperature sensor devices
	for (int i = 0; i < TEMPSENSOR_COUNT; ++i) {
		temp_sensors[i]->Post(temp_sensors[i]->utc = Time::Now());
		temp_sensors[i]->Post(temp_sensors[i]->temperature = 273.15);
		temp_sensors[i]->Post(temp_sensors[i]->voltage = 0);
		temp_sensors[i]->SetCustomProperty<ADT7311*>("handler", nullptr);
		
//		temp_sensors[i]->AddRequest({"temp", "temperature"}, Request_Sensor_Temperature, "Returns the latest temperature reading");
	}
	InitSensors();
	
	
	// Finish up
	agent->Finalize();
	agent->DebugPrint();
	
	
	
	// Start executing the agent
	while ( agent->StartLoop() ) {
		
		// Ensure correct power mode
		SetSensorPower(should_enable_sensors);
		
		// Update sensor readings
		UpdateTemperatures();
	}
	
	
	
	// Free sensor devices
	DestroySensors();
	
	// Free the agent
	delete agent;
	
	return 0;
}

bool ConnectSensor(int index) {
	
	TemperatureSensor *sensor = temp_sensors[index];
	ADT7311 *handler = handlers[index];
	
	temp_sensors[index]->utc = Time::Now();
	temp_sensors[index]->voltage = handler->IsOpen() ? 3.3 : 0.0;
	temp_sensors[index]->power = handler->IsOpen() ? 3.3 : 0.0; // Set to some non-zero value if enabled
	
	
	// Check if the sensor is already connected
	if ( handler->IsOpen() )
		return true;
	
	// We compare against the manufacturer ID to see if the sensors are connected
	const int kManufacturerID = 0b11000;
	
	// Check if the device is open by actually reading a register we know the value of
	if ( handler->Open() >= 0 ) {
		
		// Read the sensor state
		handler->ReadState();
		
		// Check if the manufacturer register has the correct value
		if ( handler->GetManufacturerRegister().manufacturer_id != kManufacturerID ) {
			handler->Close(); // Close the device to prevent dangling file descriptors
			
			sensor->enabled = false;
			sensor->voltage = 0;
			sensor->power = 0;
			
			printf("Failed to open temperature sensor '%s' on SPI Bus %d at address %02x\n",
				   sensor->GetName().c_str(), handler->GetBus(), handler->GetDeviceAddr());
			
			return false;
		}
	}
	
	// Update the device properties
	sensor->enabled = true;
	sensor->voltage = 3.3;
	sensor->power = 3.3;
	
	printf("Successfully opened temperature sensor '%s'\n", sensor->GetName().c_str());
	
	return true;
}

void InitSensor(int index) {
	DeviceAddress config = device_addresses[index];
	
	// Create and store the device handler
	ADT7311 *device = new ADT7311(config.spi_bus, config.dev_addr);
	
	temp_sensors[index]->SetCustomProperty<ADT7311*>("handler", device);
	handlers[index]	= device;
}

void InitSensors() {
	// Set a default configuration for the normal temperature sensors
	default_sensor_config.fault_queue = 0;
	default_sensor_config.ct_pin_polarity = 0;
	default_sensor_config.int_pin_polarity = 0;
	default_sensor_config.int_ct_mode = 0;
	default_sensor_config.operation_mode = 0;
	default_sensor_config.resolution = 0;
	
	for (int i = 0; i < TEMPSENSOR_REGULAR_COUNT; ++i) {
		InitSensor(i);
	}
}

void DestroySensors() {
	// Delete pointers to device handlers
	for (int i = 0; i < TEMPSENSOR_REGULAR_COUNT; ++i) {
		delete handlers[i];
		handlers[i] = nullptr;
	}
}


void UpdateTemperatures() {
	
	for (int i = 0; i < TEMPSENSOR_REGULAR_COUNT; ++i) {
		// Reconnect to the sensor
		ConnectSensor(i);
		
		// Get the device handler
		ADT7311 *handler = handlers[i];
		TemperatureSensor *sensor = temp_sensors[i];
		
		// Update readings if the device is open
		if ( handler->IsOpen() ) {
			
			// Update readings from the device
			handler->ReadState();
			
			// Update the temperature reading
			sensor->utc = Time::Now();
			sensor->temperature = handler->GetTemperature();
		}
	}
	
	static RemoteAgent agent_pycubed = agent->FindAgent(CUBESAT_AGENT_PYCUBED_NAME);
	
	if ( agent_pycubed.Connect() ) {
		
		auto values = agent_pycubed.GetCOSMOSValues({"device_batt_temp_000", "device_imu_temp_000"});
		
		// Check if the request failed
		if ( values.empty() )
			return;
		
		temp_sensors[TEMPSENSOR_BATT_ID]->utc = Time::Now();
		temp_sensors[TEMPSENSOR_BATT_ID]->temperature = values["device_batt_temp_000"].nvalue;
		
		temp_sensors[TEMPSENSOR_PYCUBED_ID]->utc = Time::Now();
		temp_sensors[TEMPSENSOR_PYCUBED_ID]->temperature = values["device_imu_temp_000"].nvalue;
		
	}

}

void SetSensorPower(bool enable) {
	should_enable_sensors = enable;
	
	static RemoteAgent agent_switch = agent->FindAgent(CUBESAT_AGENT_SWITCH_NAME);
	
	if ( agent_switch.Connect() ) {
		// Request to enable/disable power to temperature sensor switch
		string response = agent_switch.SendRequest("enable", "sw_temp");
		
		// Check if the request was successful
		if ( response.find("NOK") == string::npos )
			sensors_powered = enable;
		
		// If they are disabled, make sure the sensors are closed
		if ( !sensors_powered ) {
			for (int i = 0; i < TEMPSENSOR_REGULAR_COUNT; ++i)
				handlers[i]->Close();
		}
	}
}

float Request_Sensor_Temperature(TemperatureSensor *sensor) {
	return sensor->temperature;
}

string Request_List() {
	
	stringstream ss;
	
	// Use a convenient lambda function to add sensor information
	auto add_sensor_info = [&ss](TemperatureSensor *sensor) {
		ADT7311 *device = sensor->GetCustomProperty<ADT7311*>("handler");
		
		ss <<	"\"" << sensor->GetName() << "\": {";
		ss <<		"\"utc\": " << sensor->utc << ", ";
		ss <<		"\"temp\": " << sensor->temperature << ",";
		ss <<		"\"spi_bus\": " << (device != nullptr ? std::to_string(device->GetBus()) : "N/A") << ", ";
		ss <<		"\"address\": " << (device != nullptr ? std::to_string(device->GetDeviceAddr()) : "N/A") << ", ";
		ss <<		"\"enabled\": " << (device != nullptr ? std::to_string(device->IsOpen()) : "true");
		
		ss <<	"},";
	};
	
	ss << "{";
	for (int i = 0; i < TEMPSENSOR_COUNT; ++i)
		add_sensor_info(temp_sensors[i]);
	ss << "}";
	
	return ss.str();
}
