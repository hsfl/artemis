
#ifndef CUBESAT_DEVICEJSON
#define CUBESAT_DEVICEJSON

#include "Device.h"
#include "StringTools.h"
#include "DeviceRequest.h"

#include <unordered_map>
#include <sstream>


namespace cubesat {
	
	
	class DeviceSerializer {
	public:
		DeviceSerializer() {}
		
		
		template <typename T>
		void AddProperty(const std::string key, T &property) {
			properties[key] = ToJSONString(property.GetValue());
		}
		
		std::string GetJSON() {
			std::stringstream ss;
			ss << "{" << endl;
			
			int i = 0;
			for (auto pair : properties) {
				ss << '"' << pair.first << "\": " << pair.second;
				if ( ++i != properties.size() )
					ss << ", ";
			}
			
			ss << "}";
			
			return ss.str();
		}
		
		
	private:
		std::unordered_map<std::string, std::string> properties;
		
	};
	
	
}

#endif
