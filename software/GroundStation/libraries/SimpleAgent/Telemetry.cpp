#include "Telemetry.h"

#include <fstream>



using namespace std;
using namespace cubesat;


TelemetryLog::TelemetryLog(const std::string &agent, const std::string &node) {
	
	// Create the log folder
	file = getenv("HOME") + ("/cosmos/nodes/" + node + "/telem");
	if ( mkdir(file.c_str(), 0777) == -1 ) {
		
		perror("Failed to make log folder");
		
		if ( errno != EEXIST )
			throw std::runtime_error("Unable to create log folder at " + file);
	}
	
	file += "/" + agent + ".json";
	
	// Try to create the file
	if ( !Create() )
		throw std::runtime_error("Unable to create log file at " + file);
}
TelemetryLog::~TelemetryLog() {
	WriteEntries();
}

bool TelemetryLog::Create() {
	if ( Exists() )
		return true;
	
	// Open the file
	ofstream out(file);
	if ( out.fail() )
		return false;
	
	// Start the file with an opening bracket
	out << "[" << endl;
	out.close();
	
	return true;
}

bool TelemetryLog::Exists() const {
	struct stat buffer;   
	return stat(file.c_str(), &buffer) == 0;
}

bool TelemetryLog::Purge() {
	
	// Remove the finalized state
	finalized = false;
	
	if ( remove(file.c_str()) == 0 ) {
		printf("Successfully purged log\n");
		finalized = false;
		return true;
	}
	else {
		printf("Failed to purge log\n");
		return false;
	}
}


bool TelemetryLog::WriteEntries() {
	
	// Purge the file if the log has been finalized
	if ( finalized )
		return false;
	
	
	// Open the output file in append mode
	ofstream out;
	out.open(file, ios::app);
	
	// Check if the file failed to open
	if ( out.fail() ) {
		printf("Failed to write to log file '%s'\n", file.c_str());
		return false;
	}
	
	// Write the properties into the file
	
	out << '{' << endl;
	
	for (int i = 0; i < devices.size(); ++i) {
		DeviceTelemWrapper &device = devices[i];
		
		
		out << '"' << device.name << "\": {" << endl;
		
		for (int j = 0; j < device.entries.size(); ++j) {
			DeviceTelemWrapper::Entry &entry = device.entries[j];
			
			out << '"' << entry.name << "\": " << entry.retriever(entry.property) << ',' << endl;
		}
		
		out << endl << "}," << endl;
	}
		
	out << "}," << endl;
	
	out.close();
	
	return true;
}

bool TelemetryLog::Finalize() {
	if ( finalized )
		return true;
	else if ( !Exists() ) {
		printf("Failed to finalize log: file does not exist\n");
		return false;
	}
	
	ofstream out(file, ios::app);
	if ( out.fail() ) {
		printf("Failed to finalize log file\n");
		return false;
	}
	
	out << "]" << endl;
	out.close();
	
	finalized = true;
	
	return true;
}






