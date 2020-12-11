
#ifndef CUBESAT_UTILITY_CONFIGURATION
#define CUBESAT_UTILITY_CONFIGURATION

#include <string>
#include "rapidjson/document.h"
#include <fstream>
#include <streambuf>


namespace artemis {
	
	
	
	inline std::string GetConfigFile(const std::string &config_name) {
		return getenv("HOME") + ("/agents/config/" + config_name + ".json");
	}
	
	
	inline bool GetConfigString(const std::string &config_name, std::string &out) {
		std::string filename = GetConfigFile(config_name);
		
		// Open the file
		std::ifstream f(filename);
		if ( !f.good() ) {
			printf("Configuration file '%s' does not exist!\n", filename.c_str());
			return false;
		}
		
		// Read the file into a string
		std::string json((std::istreambuf_iterator<char>(f)),
						 std::istreambuf_iterator<char>());
		out = json;
		
		// Close the file
		f.close();
		
		return true;
	}
	
	inline bool GetConfigDocument(const std::string &config_name, rapidjson::Document &doc_out) {
		std::string json;
		if ( !GetConfigString(config_name, json) )
			return false;
		
		// Parse the JSON
		doc_out.Parse(json.c_str());
		
		return true;
	}
	
	
}



#endif
