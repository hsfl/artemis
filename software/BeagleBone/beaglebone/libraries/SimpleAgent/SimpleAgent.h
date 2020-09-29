
#ifndef CUBESAT_SIMPLEAGENT
#define CUBESAT_SIMPLEAGENT


//! If true, the program will operate in "strict mode," and will
//! crash upon various failures. By default this is set to
//! true. Define this before including the file SimpleAgent.h
//! if you want to change it
#ifndef SIMPLEAGENT_STRICT_MODE
#define SIMPLEAGENT_STRICT_MODE true
#endif

//! If true, case will be ignored in request names. Ignoring
//! case will slow down lookup times. By default
//! this is set to true. Define this before including
//! the file SimpleAgent.h if you want to change it
#ifndef SIMPLEAGENT_IGNORE_CASE
#define SIMPLEAGENT_IGNORE_CASE true
#endif



#include "agent/agentclass.h"
#include "support/configCosmos.h"
#include "agent/agentclass.h"
#include "support/jsonlib.h"
#include "support/jsonclass.h"

#include "cubesat_defs.h"
#include "Exceptions.h"
#include "RemoteAgent.h"
#include "Device.h"
#include "StringTools.h"
#include "TimeTools.h"
#include "AgentRequest.h"
#include "DeviceRequest.h"

#include <functional>
#include <unordered_map>

#pragma GCC diagnostic push
// Silence annoying warnings about pointer magic
#pragma GCC diagnostic ignored "-Wpointer-arith"


namespace cubesat {
	
	//===============================================================
	//=========================== SUPPORT ===========================
	//===============================================================
	
	/**
	 * @brief A request which redirects itself to requests added to a SimpleAgent
	 * @param request The request string. This begins with the request name, so we can look up the callback
	 * @param response The output response string
	 * @param agent_ The (complex) agent calling this request
	 * @return 0 upon success, or a negative value on failure
	 */
	int32_t RequestProxy(std::string &request, std::string &response, Agent *agent_);
	
	
	
	//! A SimpleAgent request (added by default) which prints device properties
	std::string _Request_DebugPrint();
	
	
	//! You guessed it -- it's a simple agent
	class SimpleAgent : protected Agent {
	protected:
		
		//! Represents a COSMOS node property
		struct NodeProperty {
			//! The COSMOS name of the property (e.g. node_battcap)
			std::string cosmos_name;
			//! The readable name of the property (e.g. Battery Capacity)
			std::string readable_name;
			//! The value of the property represented as a string
			std::string value_string;
			//! Whether or not the property should be posted in the state of health string
			bool post;
			
			//! A default constructor is required for std::unordered_map
			NodeProperty() {}
			NodeProperty(const std::string &value_string, const std::string &cosmos_name, const std::string &readable_name, bool post)
				: cosmos_name(cosmos_name), readable_name(readable_name), value_string(value_string), post(post) {}
		};
		
	public:
		
		/**
		 * @brief Creates a new simple agent with the given name. Don't create multiple instances in one program!
		 * @param name The agent name
		 * @param node The node name, defaults to 'cubesat'
		 * @param crash_if_not_open If true, the program will crash on failure to start the agent
		 */
		SimpleAgent(const std::string &name, std::string node = CUBESAT_NODE_NAME,
					bool crash_if_not_open = SIMPLEAGENT_STRICT_MODE);
		
		//! Disallow copy construction for safety
		SimpleAgent(const SimpleAgent&) = delete;
		
		virtual ~SimpleAgent() {
			
			// Delete devices
			for (auto device_pair : devices)
				delete device_pair.second;
			
			devices.clear();
		}
		
		
		//===============================================================
		//======================== MISCELLANEOUS ========================
		//===============================================================
		
		
		/**
		 * @brief Returns the original (more complex) version of this agent
		 * @return The original version of this agent
		 */
		inline Agent* GetComplexAgent() {
			// Just	upcast to the base class
			return (Agent*)this;
		}
		
		/**
		 * @brief Returns the original (more complex) version of this agent
		 * @return The original version of this agent
		 */
		inline const Agent* GetComplexAgent() const {
			// Just	upcast to the base class
			return (const Agent*)this;
		}
		
		/**
		 * @brief Returns the singleton instance of the SimpleAgent
		 * @return The SimpleAgent
		 */
		inline static SimpleAgent* GetInstance() {
			return SimpleAgent::instance;
		}
		
		/**
		 * @brief Checks if the agent has started successfully
		 * @return True if the agent started successfully
		 */
		inline bool IsOpen() {
			// Check if the agent is running
			return this->cinfo != nullptr && this->running() && this->wait() >= 0;
		}
		
		/**
		 * @brief Checks if the agent has started successfully
		 * @return True if the agent started successfully
		 */
		inline bool IsOpen() const {
			// Need to const_cast since Agent::running() and Agent::wait()
			// should be marked as const, but aren't
			Agent *agent = (Agent*)(const_cast<SimpleAgent*>(this));
			
			// Check if the agent is running
			return agent->cinfo != nullptr && agent->running() && agent->wait() >= 0;
		}
		
		/**
		 * @brief Shuts down the agent. Calls to SimpleAgent::StartLoop() will then return false
		 */
		inline void Shutdown() {
			this->shutdown();
		}
		
		/**
		 * @brief Crashes the program if the agent did not start successfully
		 */
		void CrashIfNotOpen();
		
		/**
		 * @brief Sets how long the agent should wait between iterations of the main loop (the period).
		 * If this method is not called, the period defaults to 1 second.
		 * @param period The period in seconds
		 */
		inline void SetLoopPeriod(double period) {
			this->cinfo->agent[0].aprd = period;
		}
		
		/**
		 * @brief Signals the beginning of an iteration of the main loop.
		 * @return True if the agent is running
		 */
		bool StartLoop();
		
		
		/**
		 * @brief Checks if the agent is currently running
		 * @return True if the agent is running
		 */
		bool IsRunning() {
			return this->running();
		}
		
		/**
		 * @brief Updates this agent's state of health message using
		 * the list of posted properties. Call this once you are done
		 * adding devices and properties
		 */
		void Finalize();
		
		//===============================================================
		//======================== REMOTE AGENTS ========================
		//===============================================================
		
		/**
		 * @brief Attempts to connect to an agent running in a different process
		 * @param name The name of the agent
		 * @param node The node the agent is running on. Defaults to the same one as this agent
		 * @param wait_sec The timeout duration in seconds
		 * @param crash_if_failed If true, the program will crash if the agent cannot be found
		 * @return A cubesat::RemoteAgent object corresponding to the remote agent
		 */
		RemoteAgent FindAgent(const std::string &name, const std::string &node, float wait_sec = 2.0f, bool crash_if_failed = false);
		
		/**
		 * @brief Attempts to connect to an agent running in a different process on the same node
		 * @param name The name of the agent
		 * @param wait_sec The timeout duration in seconds
		 * @param crash_if_failed If true, the program will crash if the agent cannot be found
		 * @return A cubesat::RemoteAgent object corresponding to the remote agent
		 */
		inline RemoteAgent FindAgent(const std::string &name, float wait_sec = 2.0f, bool crash_if_failed = false) {
			return FindAgent(name, this->nodeName, wait_sec, crash_if_failed);
		}
		
		//===============================================================
		//========================== REQUESTS ===========================
		//===============================================================
		/**
		 * @brief Adds a request to this agent.
		 * @param request_name The name of the request
		 * @param request_callback The callback function
		 * @param synopsis A brief description of the request
		 * @param description A detailed description of the request
		 * @param crash_on_error If true, the program will crash if an error occurs
		 * @return True if successful
		 */
		template <typename R, typename... Args>
		bool AddRequest(const std::string &request_name, R(*request_callback)(Args...),
						std::string synopsis = "", std::string description = "", bool crash_on_error = SIMPLEAGENT_STRICT_MODE) {
			
			// Check if a request with the same name was already added
			if ( requests.find(request_name) != requests.end() ) {
				printf("Failed to add request '%s': another request with this name already exists.\n", request_name.c_str());
				
				if ( crash_on_error )
					exit(1);
				
				return false;
			}
			
			
			// Add the request proxy to the agent instead, using the given request name
			int status = this->add_request(request_name, RequestProxy, synopsis, description);
			
			// Check for errors
			if ( status < 0 ) {
				printf("Failed to add request '%s': %s\n", request_name.c_str(), cosmos_error_string(status).c_str());
				
				if ( crash_on_error )
					exit(status);
				
				return false;
			}
			else {
				// Store the request
				requests[request_name] = new AgentRequest(request_callback);
				
				return true;
			}
		}
		
		/**
		 * @brief Adds a request to this agent using alias names
		 * @param request_names The alias names of this request
		 * @param request_callback The callback function
		 * @param synopsis A brief description of the request
		 * @param description A detailed description of the request
		 * @param crash_on_error If true, the program will crash if an error occurs
		 * @return True if successful
		 */
		template <typename R, typename... Args>
		bool AddRequest(std::initializer_list<std::string> request_names, R(*request_callback)(Args...),
						std::string synopsis = "", std::string description = "", bool crash_on_error = SIMPLEAGENT_STRICT_MODE) {
			// Add aliases for the request
			bool success = true;
			
			// Add the requests
			// Agh why doesn't std::initializer_list have a subscript operator??
			int i = 0;
			std::string first_name;
			for (const std::string &name : request_names) {
				// After the first request, set the synopsis as 'Alias of ...'
				if ( i == 0 ) {
					success = success && AddRequest(name, request_callback, synopsis, description, crash_on_error);
					first_name = name;
				}
				else
					success = success && AddRequest(name, request_callback, "Alias of " + first_name, "", crash_on_error);
				
				++i;
			}
			
			return success;
		}
		
		/**
		 * @brief Retrieves a previously-added request
		 * @param request_name The name of the request
		 * @return The AgentRequest object, or nullptr if it does not exist
		 */
		inline AgentRequest* GetRequest(const std::string &request_name) {
			auto it = requests.find(request_name);
			
			if ( it == requests.end() )
				return nullptr;
			else
				return requests[request_name];
		}
		
		/**
		 * @brief Checks if a request with the given name already exists
		 * @param request_name The request name
		 * @return True if the request already exists
		 */
		inline bool RequestExists(const std::string &request_name) const {
			return requests.find(request_name) != requests.end();
		}
		
		
		
		//===============================================================
		//=========================== DEVICES ===========================
		//===============================================================
		/**
		 * @brief Adds a new device to this SimpleAgent
		 * @tparam _DeviceType The type of device to create (e.g. TemperatureSensor)
		 * @param name The name of the device
		 * @param crash_on_error If true, the program will crash if an error occurs
		 * @return The new device. Don't delete this! Do you want undefined behavior? Because that's how you get undefined behavior
		 */
		template <typename DeviceType>
		DeviceType* NewDevice(const std::string &name, bool crash_on_error = SIMPLEAGENT_STRICT_MODE) {
			
			// Check if a device with the given name already exists
			if ( DeviceExists(name) ) {
				printf("The device '%s' already exists\n", name.c_str());
				throw DeviceAlreadyExistsException(name);
			}
			else {
				
				// Create the piece
				int pindex = json_createpiece(this->cinfo, name, DeviceType::type);
				
				// Check if the piece was succesfully created
				if ( pindex < 0 ) {
					
					printf("Failed to add %s device named '%s': %s\n", GetDeviceTypeString(DeviceType::type),
						   name.c_str(), cosmos_error_string(pindex).c_str());
					if ( crash_on_error )
						exit(pindex);
					
					return nullptr;
				}
				
				// Get COSMOS indices
				int cindex = this->cinfo->pieces[pindex].cidx;
				int dindex = this->cinfo->device[cindex].all.didx;
				
				// Create the new device
				DeviceType *device = new DeviceType(GetComplexAgent(), cindex, dindex);
				device->SetName(name);
				devices[name] = device;
				
				return device;
			}
		}
		
		
		/**
		 * @brief Checks if a device with the given name exists
		 * @param name The device name
		 * @return True if the device already exists
		 */
		inline bool DeviceExists(const std::string &name) const {
			return devices.find(name) != devices.end();
		}
		
		template <typename DeviceType>
		inline DeviceType* GetDevice(const std::string &name) {
			for (auto device_pair : devices) {
				if ( name == device_pair.first )
					return dynamic_cast<DeviceType*>(device_pair.second);
			}
			return nullptr;
		}
		
		//===============================================================
		//======================= NODE PROPERTIES =======================
		//===============================================================
		
		/**
		 * @brief Adds and posts a node property. Equivalent to SimpleAgent::SetNodeProperty(..., true)
		 * @tparam _NodeProperty The node property to set (e.g. Node::BatteryCapacity)
		 * @param value The value to store. If not supplied, a default-constructed value is used
		 */
		template <typename _NodeProperty>
		void AddNodeProperty(typename _NodeProperty::ValueType value = _NodeProperty::ValueType()) {
			SetNodeProperty<_NodeProperty>(value, true);
		}
		
		/**
		 * @brief Sets a node property
		 * @tparam _NodeProperty The node property to set (e.g. Node::BatteryCapacity)
		 * @param value The value to store. If not supplied, a default-constructed value is used
		 * @param post If true, this property will be posted in the state of health message. If set to true, subsequent calls will not 'un-post' the property
		 */
		template <typename _NodeProperty>
		void SetNodeProperty(typename _NodeProperty::ValueType value, bool post = false) {
			
			// Check if there's an old value set, and if so, steal its 'post' value
			if ( node_properties.find(GetPropertyID<_NodeProperty>()) != node_properties.end() ) {
				post = node_properties[GetPropertyID<_NodeProperty>()].post;
			}
			
			// Create the property
			NodeProperty new_property(ToString<typename _NodeProperty::ValueType>(value), _NodeProperty::key, _NodeProperty::name, post);
			
			// Store the device property
			node_properties[GetPropertyID<_NodeProperty>()] = new_property;
			
			// Set the property value using the NodeProperty offset
			// Beware: pointer magic ahead!
			*(typename _NodeProperty::ValueType*)((void*)&this->cinfo->node + _NodeProperty::offset) = value;
		}
		
		/**
		 * @brief Retrieves the value of a node property
		 * @param _NodeProperty The node property to set (e.g. Node::BatteryCapacity)
		 * @return The value of the property, or a default-construct value if the property was not set
		 */
		template <typename _NodeProperty>
		typename _NodeProperty::ValueType GetNodeProperty() {
			
			if ( node_properties.find(GetPropertyID<_NodeProperty>()) == node_properties.end() ) {
				printf("Attempted to retrieve nonexistent node property '%s'\n", _NodeProperty::name);
				return _NodeProperty::ValueType();
			}
			
			// Get the property value using the NodeProperty offset
			// Beware: pointer magic ahead!
			return *(typename _NodeProperty::ValueType*)((void*)&this->cinfo->node + _NodeProperty::offset);
		}
		
		//===============================================================
		//============================ DEBUG ============================
		//===============================================================
		
		/**
		 * @brief DebugPrint Prints the requests and posted device and node properties for this SimpleAgent
		 * @param print_all If true, even non-posted properties are printed
		 */
		void DebugPrint(bool print_all = false) const;
		
		/**
		 * @brief DebugPrint Gets the requests and posted device and node properties for this SimpleAgent
		 * as a formatted string
		 * @param print_all If true, even non-posted properties are printed
		 * @return The formatted string
		 */
		std::string GetDebugString(bool print_all = false) const;
		
		
		/**
		 * @brief Used to signal an error from inside a request
		 * @param message The error message
		 */
		inline void RaiseRequestError(const std::string &message) {
			last_request_error = message;
		}
		/**
		 * @brief Retrieves the last error message raised by a request
		 * @return The error message
		 */
		inline const std::string& GetLastRequestError() {
			return last_request_error;
		}
		
	protected:
		//! A table of user-defined request callbacks (those with vector arguments)
		std::unordered_map<std::string, AgentRequest*> requests;
		
		std::unordered_map<std::string, DeviceRequest*> device_requests;
		//! A table of user-defined devices
		std::unordered_map<std::string, Device*> devices;
		//! A table of user-defined node properties
		std::unordered_map<PropertyID, NodeProperty> node_properties;
		//! Indicates whether the first iteration of the main loop has occurred
		bool loop_started;
		
		
		std::string last_request_error;
		
		//! The singleton instance of the SimpleAgent class
		static SimpleAgent *instance;
		
	};
	
	
	
	
	
	
	
	
	
}


#pragma GCC diagnostic pop

#endif
