
#ifndef CUBESAT_REMOTEAGENT
#define CUBESAT_REMOTEAGENT

#include "agent/agentclass.h"
#include "support/configCosmos.h"
#include "agent/agentclass.h"
#include "support/jsonlib.h"
#include "support/jsonclass.h"

#include "DeviceDetail.h"
#include "StringTools.h"

#include <unordered_map>
#include <sstream>

namespace cubesat {
	
	struct RemoteDeviceProperty {
		std::string device_name;
		size_t mem_offset;
		
		template <typename PropertyType>
		RemoteDeviceProperty(const std::string &device_name, PropertyType)
			: device_name(device_name), mem_offset(PropertyType::offset) {}
	};
	
	template <typename... PropertyTypes>
	struct RemoteDevicePropertyList {
		
		
		std::tuple<typename PropertyTypes::ValueType...> values;
		
	};
	
	
	/**
	 * @brief A utility class for communicating with agents on seperate processes
	 */
	class RemoteAgent {
	public:
		RemoteAgent() {
			beat.utc = 0.;
			beat.exists = false;
		}
		RemoteAgent(const std::string &node_name, const std::string &agent_name, Agent *agent, beatstruc beat) : agent(agent), beat(beat), node_name(node_name), agent_name(agent_name) {
			
		}
		
		/**
		 * @brief Checks if this agent was connected to successfully.
		 * @return True if connected
		 */
		inline bool IsOpen() const {
			return beat.utc != 0. && beat.exists;
		}
		
		/**
		 * @brief Attempts to connect to the remote agent
		 * @param wait_sec The maximum duration in seconds to wait
		 * @param crash_if_failed If true, the program will crash if the agent is not found
		 * @return True if the agent connected successfully
		 */
		bool Connect(float wait_sec = 2.0f, bool crash_if_failed = false);
		
		/**
		 * @brief Gets a list of state of health values from a remote agent
		 * @param keys A vector of COSMOS namespace names to retrieve
		 * @return A table of values, indexed by the given keys
		 */
		std::unordered_map<std::string, Json::Value> GetCOSMOSValues(std::vector<std::string> keys);
		
		template <typename... Properties, typename... Args>
		std::unordered_map<std::string, std::string> GetProperties(Args... device_names_) {
			static_assert(sizeof...(Properties) == sizeof...(Args), "The number of property types and device names does not match");
			std::vector<std::string> device_names = {device_names_...};
			std::vector<std::string> property_names = {Properties::key...};
			
			std::stringstream request;
			
			// Add the device and property keys to the request
			for (int i = 0; i < device_names.size(); ++i) {
				request << device_names[i] << ":" << property_names[i] << " ";
			}
			
			// Send the request
			std::string response = SendRequest("getproperty", request.str());
			std::unordered_map<std::string, std::string> values;
			
			// Check if the request failed
			if ( response.empty() )
				return values;
			
			// Parse the JSON response
			Json jresult;
			int status = jresult.extract_object(response);
			
			// Check if an error occurred
			if ( status > 0 ) {
				
				// Populate the table
				for (Json::Member member : jresult.Members) {
					values[member.value.name] = member.value.svalue;
				}
			}
			
			return values;
		}
		
		
		
		/**
		 * @brief Sends a request to the remote agent
		 * @param request_name The name of the request
		 * @param args The arguments to the request
		 * @return The response, or an empty string on failure
		 */
		template <typename... Args>
		std::string SendRequest(std::string request_name, Args... args) {
			
			// Return default values if the agent isn't connected
			if ( !IsOpen() ) {
				return "";
			}
			
			// Generate the request string
			std::stringstream request;
			request << request_name;
			
			
			using dummy = int[];
			(void)dummy {0, (request << " " << ToString<Args>(args), 0)...};
			
			// Call the request
			std::string output;
			int status = agent->send_request(beat, request.str(), output, wait_time);
			
			// Check if an error occurred
			if ( status < 0 ) {
				beat.utc = 0.;
				beat.exists = false;
				printf("Error sending request to [%s:%s]: %s\n", node_name.c_str(), agent_name.c_str(), cosmos_error_string(status).c_str());
				return "";
			}
			
			return output;
		}
		
		template <typename... Args>
		std::string SendDeviceRequest(const std::string &device_name, const std::string request_name, Args... args) {
			return SendRequest(device_name + ":" + request_name, args...);
		}
		
	protected:
		//! The non-remote agent
		Agent *agent;
		//! The heartbeat of the remote agent
		beatstruc beat;
		//! The timeout for requests
		float wait_time = 5.0f;
		//! The name of the node the remote agent is on
		std::string node_name;
		//! The name of the remote agent
		std::string agent_name;
		
	};
	
}

#endif
