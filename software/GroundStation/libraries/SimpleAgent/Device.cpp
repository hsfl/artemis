
#include "Device.h"

#include "SimpleAgent.h"

using namespace std;
using namespace artemis;



int32_t artemis::DeviceRequestProxy(string &request_str, string &response, Agent *agent_) {
	
	// The request string is messed up for some reason, so we need to fix it:
	request_str.assign(request_str.c_str(), strlen(request_str.c_str()));
	
	cout << request_str << endl;
	
	// Split the request string into arguments
	std::vector<std::string> arguments;
	istringstream iss(request_str);
	string arg;
	
	while ( getline(iss, arg, ' ') )
		arguments.push_back(arg);
	
	// Get the request locator and remove it from the argument list
	std::string request_locator = arguments[0];
	arguments.erase(arguments.begin());
	
	// Get the device and request names from the request locator
	std::string device_name = request_locator.substr(0, request_locator.find(":"));
	std::string request_name = request_locator.substr(request_locator.find(":") + 1);
	
	// Find the device
	SimpleAgent *agent = SimpleAgent::GetInstance();
	Device *device = agent->GetDevice<Device>(device_name);
	
	// Check if the device exists
	if ( device == nullptr ) {
		return -1;
	}
	
	// Get the device request
	DeviceRequest *request = device->GetRequest(request_name);
	
	// Make sure the request exists
	if ( request == nullptr ) {
		return -1;
	}
	
	
	// Clear the request error
	agent->RaiseRequestError("");
	
	// Call the request
	std::string response_str;
	bool success = request->Invoke(device, arguments, response_str);
	
	// Check if the request callback raised an error
	const std::string& request_err = agent->GetLastRequestError();
	
	// Print the error if one was raised
	if ( !request_err.empty() ) {
		response = request_err.c_str();
		
		return -1;
	}
	else {
		// Print the response
		response = response_str.c_str();
		
		// Return the status of the operation
		return success;
	}
}



//===============================================================
//============================ OTHER ============================
//===============================================================
const char* artemis::GetDeviceTypeString(DeviceType type) {
	switch ( type ) {
		case DeviceType::PLOAD: return "payload";
		case DeviceType::SSEN: return "sun sensor";
		case DeviceType::TSEN: return "temperature sensor";
		case DeviceType::MTR: return "magnetic torque rod";
		case DeviceType::ANT: return "antenna";
		case DeviceType::CPU: return "CPU";
		case DeviceType::IMU: return "IMU";
		case DeviceType::GPS: return "GPS";
		case DeviceType::RW: return "reaction wheel";
		case DeviceType::RXR: return "radio receiver";
		case DeviceType::TXR: return "radio transmitter";
		case DeviceType::TCV: return "radio transceiver";
		case DeviceType::MOTR: return "motor";
		case DeviceType::THST: return "thruster";
		case DeviceType::PROP: return "propellant tank";
		case DeviceType::SWCH: return "switch";
		case DeviceType::ROT: return "rotor";
		case DeviceType::STT: return "star tracker";
		case DeviceType::MCC: return "motion capture camera";
		case DeviceType::TCU: return "torque rod control unit";
		case DeviceType::BUS: return "power bus";
		case DeviceType::PSEN: return "pressure sensor";
		case DeviceType::CAM: return "camera";
		case DeviceType::TELEM: return "telemetry";
		case DeviceType::DISK: return "disk drive";
		default: return "invalid";
	}
}

