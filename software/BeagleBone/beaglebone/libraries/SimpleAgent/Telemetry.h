
#ifndef CUBESAT_TELEMETRY
#define CUBESAT_TELEMETRY

#include "Device.h"
#include "support/timelib.h"

namespace cubesat {
	
	
	
	class TelemetryLog {
		
		struct DeviceTelemWrapper {
			using PropertyRetriever = std::string (*)(void* property);
			
			struct Entry {
				std::string name;
				PropertyRetriever retriever;
				void *property;
			};
			
			Device *device;
			std::string name;
			std::vector<Entry> entries;
			
			
			DeviceTelemWrapper(const std::string &name, Device *device) : name(name), device(device) {}
			
			
			template <typename Property>
			DeviceTelemWrapper& RegisterProperty(const std::string &key, Property &property) {
				
				// Create a lambda function to help us retrieve a JSON-formatted
				// string for the property, regardless of its type
				PropertyRetriever retriever = +[](void *prop) -> std::string {
					return ToJSONString(static_cast<Property*>(prop)->GetValue());
				};
				
				// Store the entry
				Entry e;
				e.name = key;
				e.property = &property;
				e.retriever = retriever;
				entries.push_back(e);
				
				return *this;
			}
		};
		
		/**
		 * @brief Creates a new log file
		 * @return True if successful, or the log file already exists
		 */
		bool Create();
		
	public:
		TelemetryLog(const std::string &agent, const std::string &node);
		TelemetryLog(const TelemetryLog &other) = delete;
		~TelemetryLog();
		
		/**
		 * @brief Returns the path to the log file being used
		 * @return The path to the file
		 */
		inline const std::string& GetLogFile() const {
			return file;
		}
		
		/**
		 * @brief Checks if the log file exists
		 * @return True if the file exists
		 */
		bool Exists() const;
		
		/**
		 * @brief Used to register a device for automatic telemetry logging
		 * @param key The name of the device
		 * @param device The device
		 * @return A wrapper object used to register properties with this device
		 */
		inline DeviceTelemWrapper& RegisterDevice(const std::string &key, Device *device) {
			devices.emplace_back(key, device);
			return devices.back();
		}
		
		/**
		 * @brief Clears all entries in the log file
		 * @param clear_buffer If true, all entries waiting to be written will be removed as well
		 */
		bool Purge();
		
		/**
		 * @brief Writes all properties in the buffer to the log file
		 * @return True if successful
		 */
		bool WriteEntries();
		
		/**
		 * @brief Finalizes all entries currently written to the log file. No further changes may be
		 * flushed before purging the contents.
		 * @return True if successful
		 */
		bool Finalize();
		
		
	private:
		bool finalized = false;
		std::string file;
		std::vector<DeviceTelemWrapper> devices;
		
	};
	
	
	
	
	
}

#endif
