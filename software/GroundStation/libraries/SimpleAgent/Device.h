
#ifndef CUBESAT_DEVICE
#define CUBESAT_DEVICE

#include "agent/agentclass.h"
#include "support/configCosmos.h"
#include "agent/agentclass.h"
#include "support/jsonlib.h"
#include "support/jsonclass.h"

#include "Exceptions.h"
#include "DeviceDetail.h"
#include "StringTools.h"
#include "DeviceRequest.h"

#include <unordered_map>


#pragma GCC diagnostic push
// Silence annoying warnings about pointer magic
#pragma GCC diagnostic ignored "-Wpointer-arith"


namespace artemis {
	
	/**
	 * @brief Used to redirect external requests to device request callbacks
	 * @param request The request string
	 * @param response The response string
	 * @param agent_ The calling agent
	 * @return A non-negative value upon success
	 */
	int32_t DeviceRequestProxy(std::string &request, std::string &response, Agent *agent_);
	
	
	/**
	 * @brief Holds information about a device, and allows
	 * for properties to be posted in an agent's state of health message
	 */
	class Device {
		//! Represents a property in the agent's state of health message
		struct PostedProperty {
			std::string readable_name;
			std::string cosmos_name;
		};
		
		//! Represents a custom property
		struct CustomProperty {
			void *value;
			PropertyID value_type;
			
			CustomProperty() : value(0), value_type(0) {
				
			}
			CustomProperty(const CustomProperty &other) = delete;
			~CustomProperty() {
				if ( value != 0 )
					free(value);
			}
			
			template <typename T>
			bool TypeMatches() {
				return value_type == GetPropertyID<T>();
			}
			
			template <typename T>
			void Load(const T &value_) {
				T *mem = new T();
				*mem = value_;
				value = mem;
				value_type = GetPropertyID<T>();
			}
			
			template <typename T>
			void Set(T value_) {
				if ( !TypeMatches<T>() )
					throw TypeMismatchException("Give type does not match stored type");
				else
					*(T*)value = value_;
			}
			
		};
		
	public:
		/**
		 * @brief Creates a new device
		 * @param agent The COSMOS agent this device belongs to
		 * @param cindex The COSMOS component index of this device
		 * @param dindex The COSMOS device index of this device
		 * @param cosmos_device_name The COSMOS name for this device
		 */
		Device(Agent *agent, int cindex, int dindex, const std::string &cosmos_device_name)
			: agent(agent), cindex(cindex), dindex(dindex),
			  cosmos_device_name(cosmos_device_name) {}
		virtual ~Device() {}
		
		
		/**
		 * @brief Retrieves a device request
		 * @param request_name The request name
		 * @return The device request
		 */
		DeviceRequest* GetRequest(const std::string &request_name) {
			auto it = requests.find(request_name);
			if ( it == requests.end() )
				return nullptr;
			else
				return it->second;
		}
		
		
		/**
		 * @brief Adds a request to this device
		 * @tparam T The device type used in the request callback
		 * @tparam R The return type of the request callback
		 * @tparam Args The other arguments used in the request callback
		 * @param request_name The name of the request
		 * @param synopsis The synopsis string
		 * @param description The description string
		 * @param crash_on_error If true, the program crashes if an error occurs
		 * @return True upon success
		 */
		template <typename T, typename R, typename... Args>
		bool AddRequest(const std::string &request_name, R(*request_callback)(T*, Args...),
						const std::string &synopsis = "", const std::string &description = "", bool crash_on_error = true) {
			
			// Create a "locator" in the format "device:request"
			std::string request_locator = device_name + ":" + request_name;
			
			// Check if	a request with the same name exists
			if ( requests.find(request_name) != requests.end() ) {
				printf("Failed to add request '%s': another request with this name already exists.\n", request_name.c_str());
				
				if ( crash_on_error )
					exit(1);
				
				return false;
			}
			
			
			// Add the request proxy to the instead, using the request locator
			int status = agent->add_request(request_locator, DeviceRequestProxy, synopsis, description);
			
			// Check for errors
			if ( status < 0 ) {
				printf("Failed to add request '%s': %s\n", request_locator.c_str(), cosmos_error_string(status).c_str());
				
				if ( crash_on_error )
					exit(status);
				
				return false;
			}
			
			
			// Store the request
			requests[request_name] = new DeviceRequest(request_callback);
			
			return true;
		}
		
		/**
		 * @brief Adds a request to this device using alias names
		 * @param request_names The alias names of this request
		 * @param request_callback The callback function
		 * @param synopsis A brief description of the request
		 * @param description A detailed description of the request
		 * @param crash_on_error If true, the program will crash if an error occurs
		 * @return True if successful
		 */
		template <typename T, typename R, typename... Args>
		bool AddRequest(std::initializer_list<std::string> request_names, R(*request_callback)(T*, Args...),
						std::string synopsis = "", std::string description = "", bool crash_on_error = true) {
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
		 * @brief Posts a property to the state of health message
		 * @tparam _PropertyType The type of property, automatically inferred from the argument.
		 * @param property The property to post
		 */
		template <typename _PropertyType>
		void Post(const _PropertyType &property) {
			// Store the property metadata
			PostedProperty property_data;
			property_data.readable_name = _PropertyType::MetaData::simple_name;
			property_data.cosmos_name = _PropertyType::MetaData::cosmos_name;
			
			// Store the property
			cosmos_properties[GetPropertyID<_PropertyType>()] = property_data;
		}
		
		/**
		 * @brief Adds all posted properties to the given vector
		 * @param keys The vector of properties to add to
		 */
		void StorePostedProperties(std::vector<std::string> &keys) {
			for (auto property_pair : cosmos_properties) {
				keys.push_back(GetCOSMOSPropertyName(property_pair.second.cosmos_name));
			}
		}
		
		/**
		 * @brief Checks if a custom property with the given name exists.
		 * @param name The property name
		 * @return True if the property has been previous set
		 */
		bool CustomPropertyExists(const std::string &name) {
			return custom_properties.find(name) != custom_properties.end();
		}
		
		/**
		 * @brief Stores a custom property
		 * @tparam T The value type
		 * @param name The property name
		 * @param value The value to store
		 */
		template <typename T>
		void SetCustomProperty(const std::string &name, T value) {
			if ( CustomPropertyExists(name) )
				custom_properties[name].Set(value);
			else
				custom_properties[name].Load(value);
		}
		
		/**
		 * @brief Retrieves a custom property from this device
		 * @tparam T The value type. This MUST match the one supplied in Device::SetCustomProperty().
		 * @param name The property name
		 * @return The property.
		 */
		template <typename T>
		T& GetCustomProperty(const std::string &name) {
			// Make sure the property exists
			if ( !CustomPropertyExists(name) )
				throw NonExistentPropertyException(name);
			
			CustomProperty &property = custom_properties[name];
			
			// Make sure the type matches
			if ( property.TypeMatches<T>() )
				return *(T*)property.value;
			else
				throw TypeMismatchException("Incorrect type supplied when retrieving property '" + name + "'");
		}
		
		/**
		 * @brief Prints information about this device
		 */
		void DebugPrint() {
			printf("|\t|\t| Posted Properties\n");
			for (auto property_pair : cosmos_properties) {
				printf("|\t|\t|\t| %s (aka %s)\n",
					   property_pair.second.readable_name.c_str(),
					   GetCOSMOSPropertyName(property_pair.second.cosmos_name).c_str());
			}
			printf("|\t\t| Requests\n");
			for (auto request_pair : requests) {
				printf("\t|\t|\t| %s: %s\n", request_pair.first.c_str(), request_pair.second->GetSignatureString().c_str());
			}
		}
		
		/**
		 * @brief Prints information about this device to an std:stringstream
		 * @param ss The output stream
		 */
		void GetDebugString(std::stringstream &ss) {
			ss << "|\t|\t| Posted Properties\n";
			for (auto property_pair : cosmos_properties) {
				ss << "|\t|\t|\t| " << property_pair.second.readable_name.c_str()
				   << "(aka " << GetCOSMOSPropertyName(property_pair.second.cosmos_name).c_str() << ")\n";
			}
			ss << "|\t\t| Requests\n";
			for (auto request_pair : requests) {
				ss << "\t|\t|\t| '" << request_pair.first << "': " << request_pair.second->GetSignatureString() << std::endl;
			}
		}
		
		/**
		 * @brief Sets the name of this device
		 * @param device_name The name
		 */
		inline void SetName(const std::string &device_name) {
			this->device_name = device_name;
		}
		
		/**
		 * @brief Gets the name of this device
		 * @return The name
		 */
		inline const std::string& GetName() const {
			return device_name;
		}
		
	protected:
		//! The agent this device belongs to
		Agent *agent;
		//! The COSMOS component index of this device
		int cindex;
		//! The COSMOS device index of this device
		int dindex;
		//! The name of this device
		std::string device_name;
		//! The COSMOS name for this device type
		std::string cosmos_device_name;
		//! A table of posted COSMOS properties
		std::unordered_map<PropertyID, PostedProperty> cosmos_properties;
		//! A table of custom properties
		std::unordered_map<std::string, CustomProperty> custom_properties;
		//! A table of device requests
		std::unordered_map<std::string, DeviceRequest*> requests;
		
		/**
		 * @brief Gets the COSMOS name of a device property
		 * @param cosmos_property_name The name of the property
		 * @return The COSMOS name
		 */
		std::string GetCOSMOSPropertyName(const std::string & cosmos_property_name) {
			std::stringstream ss;
			ss << "device_" << cosmos_device_name << "_" << cosmos_property_name << "_" << std::setw(3) << std::setfill('0') << dindex;
			
			return ss.str();
		}
	};
	
	template<typename DeviceStrucType, DeviceType type_>
	struct DeviceImplBase {
		using __DeviceStruc = DeviceStrucType;
		static constexpr DeviceType type = type_;
	};
	
	
	
	
	
	//===============================================================
	//=================== Device Implementations ====================
	//===============================================================
	
	
	class TemperatureSensor : public Device, public DeviceImplBase<tsenstruc, DeviceType::TSEN> {
	public:
		TemperatureSensor(Agent *agent, int cindex, int dindex) :
			Device(agent, cindex, dindex, "tsen"),
			temperature(agent, cindex),
			utc(agent, cindex),
			voltage(agent, cindex),
			current(agent, cindex),
			power(agent, cindex),
			enabled(agent, cindex)
		{}
		virtual ~TemperatureSensor() {}
		
		_AddProperty(temperature, temp);
		_AddProperty(utc, utc);
		_AddProperty(voltage, volt);
		_AddProperty(current, amp);
		_AddProperty(power, power);
		_AddProperty(enabled, enabled);
	};
	
	class Heater : public Device, public DeviceImplBase<htrstruc, DeviceType::HTR> {
	public:
		Heater(Agent *agent, int cindex, int dindex) :
			Device(agent, cindex, dindex, "htr"),
			utc(agent, cindex),
			voltage(agent, cindex),
			current(agent, cindex),
			power(agent, cindex),
			enabled(agent, cindex)
		{}
		virtual ~Heater() {}
		
		//! The timestamp for this device
		_AddProperty(utc, utc);
		_AddProperty(voltage, volt);
		_AddProperty(current, amp);
		_AddProperty(power, power);
		_AddProperty(enabled, enabled);
	};
	
	
	class SunSensor : public Device, public DeviceImplBase<ssenstruc, DeviceType::SSEN> {
	public:
		SunSensor(Agent *agent, int cindex, int dindex) :
			Device(agent, cindex, dindex, "ssen"),
			temperature(agent, cindex),
			utc(agent, cindex),
			voltage(agent, cindex),
			current(agent, cindex),
			power(agent, cindex),
			enabled(agent, cindex)
		{}
		virtual ~SunSensor() {}
		
		_AddProperty(temperature, temp);
		_AddProperty(utc, utc);
		_AddProperty(voltage, volt);
		_AddProperty(current, amp);
		_AddProperty(power, power);
		_AddProperty(enabled, enabled);
	};
	
	class IMU : public Device, public DeviceImplBase<imustruc, DeviceType::IMU> {
	public:
		IMU(Agent *agent, int cindex, int dindex) :
			Device(agent, cindex, dindex, "imu"),
			temperature(agent, cindex),
			utc(agent, cindex),
			voltage(agent, cindex),
			current(agent, cindex),
			power(agent, cindex),
			enabled(agent, cindex),
			
			magnetic_field(agent, cindex),
			acceleration(agent, cindex),
			angular_velocity(agent, cindex)
		{}
		virtual ~IMU() {}
		
		_AddProperty(temperature, temp);
		_AddProperty(utc, utc);
		_AddProperty(voltage, volt);
		_AddProperty(current, amp);
		_AddProperty(power, power);
		_AddProperty(enabled, enabled);
		
		_AddProperty(magnetic_field, mag);
		_AddProperty(acceleration, accel);
		_AddProperty(angular_velocity, omega);
	};
	
	class GPS : public Device, public DeviceImplBase<gpsstruc, DeviceType::GPS> {
	public:
		GPS(Agent *agent, int cindex, int dindex) :
			Device(agent, cindex, dindex, "gps"),
			temperature(agent, cindex),
			utc(agent, cindex),
			voltage(agent, cindex),
			current(agent, cindex),
			power(agent, cindex),
			enabled(agent, cindex),
			
			satellites_used(agent, cindex),
			location(agent, cindex),
			velocity(agent, cindex)
		{}
		virtual ~GPS() {}
		
		_AddProperty(temperature, temp);
		_AddProperty(utc, utc);
		_AddProperty(voltage, volt);
		_AddProperty(current, amp);
		_AddProperty(power, power);
		_AddProperty(enabled, enabled);
		
		_AddProperty(satellites_used, sats_used);
		_AddProperty(location, geods);
		_AddProperty(velocity, geocv);
	};
	
	
	class Battery : public Device, public DeviceImplBase<battstruc, DeviceType::BATT> {
	public:
		Battery(Agent *agent, int cindex, int dindex) :
			Device(agent, cindex, dindex, "batt"),
			temperature(agent, cindex),
			utc(agent, cindex),
			voltage(agent, cindex),
			current(agent, cindex),
			power(agent, cindex),
			enabled(agent, cindex),
			
			percentage(agent, cindex),
			capacity(agent, cindex),
			charge(agent, cindex),
			efficiency(agent, cindex),
			time_remaining(agent, cindex)
		{}
		virtual ~Battery() {}
		
		_AddProperty(temperature, temp);
		_AddProperty(utc, utc);
		_AddProperty(voltage, volt);
		_AddProperty(current, amp);
		_AddProperty(power, power);
		_AddProperty(enabled, enabled);
		
		_AddProperty(percentage, percentage);
		_AddProperty(capacity, capacity);
		_AddProperty(charge, charge);
		_AddProperty(efficiency, efficiency);
		_AddProperty(time_remaining, time_remaining);
	};
	
	class RadioTransceiver : public Device, public DeviceImplBase<tcvstruc, DeviceType::TCV> {
	public:
		RadioTransceiver(Agent *agent, int cindex, int dindex) :
			Device(agent, cindex, dindex, "tcv"),
			temperature(agent, cindex),
			utc(agent, cindex),
			voltage(agent, cindex),
			current(agent, cindex),
			power(agent, cindex),
			enabled(agent, cindex),
			
			frequency(agent, cindex),
			max_frequency(agent, cindex),
			min_frequency(agent, cindex),
			power_in(agent, cindex),
			power_out(agent, cindex),
			max_power(agent, cindex),
			bandwidth(agent, cindex)
			//good_packet_count(agent, cindex),
			//bad_packet_count(agent, cindex)
		{}
		virtual ~RadioTransceiver() {}
		
		_AddProperty(temperature, temp);
		_AddProperty(utc, utc);
		_AddProperty(voltage, volt);
		_AddProperty(current, amp);
		_AddProperty(power, power);
		_AddProperty(enabled, enabled);
		
		_AddProperty(frequency, freq);
		_AddProperty(max_frequency, maxfreq);
		_AddProperty(min_frequency, minfreq);
		_AddProperty(power_in, powerin);
		_AddProperty(power_out, powerout);
		_AddProperty(max_power, maxpower);
		_AddProperty(bandwidth, band);
		//_AddProperty(good_packet_count, goodcnt);
		//_AddProperty(bad_packet_count, badcnt);
	};
	
	class CPU : public Device, public DeviceImplBase<cpustruc, DeviceType::CPU> {
	public:
		CPU(Agent *agent, int cindex, int dindex) :
			Device(agent, cindex, dindex, "cpu"),
			temperature(agent, cindex),
			utc(agent, cindex),
			voltage(agent, cindex),
			current(agent, cindex),
			power(agent, cindex),
			enabled(agent, cindex),
			
			up_time(agent, cindex),
			load(agent, cindex),
			max_load(agent, cindex),
			max_memory(agent, cindex),
			memory_usage(agent, cindex),
			boot_count(agent, cindex)
		{}
		virtual ~CPU() {}
		
		_AddProperty(temperature, temp);
		_AddProperty(utc, utc);
		_AddProperty(voltage, volt);
		_AddProperty(current, amp);
		_AddProperty(power, power);
		_AddProperty(enabled, enabled);
		
		_AddProperty(up_time, uptime);
		_AddProperty(load, load);
		_AddProperty(max_load, maxload);
		_AddProperty(max_memory, maxgib);
		_AddProperty(memory_usage, gib);
		_AddProperty(boot_count, boot_count);
	};
	
	class Camera : public Device, public DeviceImplBase<camstruc, DeviceType::CAM> {
	public:
		Camera(Agent *agent, int cindex, int dindex) :
			Device(agent, cindex, dindex, "cam"),
			temperature(agent, cindex),
			utc(agent, cindex),
			voltage(agent, cindex),
			current(agent, cindex),
			power(agent, cindex),
			enabled(agent, cindex),
			
			pixel_width(agent, cindex),
			pixel_height(agent, cindex),
			width(agent, cindex),
			height(agent, cindex),
			focal_length(agent, cindex)
		{}
		virtual ~Camera() {}
		
		_AddProperty(temperature, temp);
		_AddProperty(utc, utc);
		_AddProperty(voltage, volt);
		_AddProperty(current, amp);
		_AddProperty(power, power);
		_AddProperty(enabled, enabled);
		_AddProperty(pixel_width, pwidth);
		_AddProperty(pixel_height, pheight);
		_AddProperty(width, width);
		_AddProperty(height, height);
		_AddProperty(focal_length, flength);
	};
	
	class Switch : public Device, public DeviceImplBase<swchstruc, DeviceType::SWCH> {
	public:
		Switch(Agent *agent, int cindex, int dindex) :
			Device(agent, cindex, dindex, "swch"),
			temperature(agent, cindex),
			utc(agent, cindex),
			voltage(agent, cindex),
			current(agent, cindex),
			power(agent, cindex),
			enabled(agent, cindex)
		{}
		virtual ~Switch() {}
		
		_AddProperty(temperature, temp);
		_AddProperty(utc, utc);
		_AddProperty(voltage, volt);
		_AddProperty(current, amp);
		_AddProperty(power, power);
		_AddProperty(enabled, enabled);
	};
	
	
	class CustomDevice : public Device, public DeviceImplBase<ploadstruc, DeviceType::PLOAD> {
	public:
		CustomDevice(Agent *agent, int cindex, int dindex) :
			Device(agent, cindex, dindex, "pload"),
			temperature(agent, cindex),
			utc(agent, cindex),
			voltage(agent, cindex),
			current(agent, cindex),
			power(agent, cindex),
			enabled(agent, cindex)
		{}
		virtual ~CustomDevice() {}
		
		_AddProperty(temperature, temp);
		_AddProperty(utc, utc);
		_AddProperty(voltage, volt);
		_AddProperty(current, amp);
		_AddProperty(power, power);
		_AddProperty(enabled, enabled);
	};
	
}

#pragma GCC diagnostic pop

#endif
