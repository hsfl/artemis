
#ifndef CUBESAT_DEVICE_DETAIL
#define CUBESAT_DEVICE_DETAIL

#include "support/configCosmos.h"
#include "agent/agentclass.h"
#include "support/jsonlib.h"
#include "support/jsonclass.h"
#include "Types.h"

#include "StringTools.h"


//! Use this to add support for a new property
#define _RegisterProperty(simple_name_, device_struc, member)\
	template<> struct PropertyMeta<device_struc, offsetof(device_struc, member)> {\
		using ValueType = decltype(device_struc::member);\
		using MemberType = decltype(device_struc::member);\
		static constexpr const char *cosmos_name = #member;\
		static constexpr const char *simple_name = simple_name_;\
	}

//! Use this to add support for a new property that uses a different type than the one
//! defined in the given device struc
#define _RegisterPropertyWithType(type, simple_name_, device_struc, member)\
	template<> struct PropertyMeta<device_struc, offsetof(device_struc, member)> {\
		using ValueType = type;\
		using MemberType = decltype(device_struc::member);\
		static constexpr const char *cosmos_name = #member;\
		static constexpr const char *simple_name = simple_name_;\
	}

//! Use this to add a property to a device implementation
//! (it's just for convenience)
#define _AddProperty(name, member)\
	Property<__DeviceStruc, offsetof(__DeviceStruc, member)> name


namespace cubesat {
	
	/**
	 * @brief Holds information about a COSMOS property
	 * @tparam device_struc The COSMOS device struc this property belongs to
	 * @tparam offset The offset in bytes of the property variable to the beginning of the device_struc
	 */
	template <typename device_struc, size_t offset>
	struct PropertyMeta {};
	
	template <typename device_struc, size_t offset_>
	struct Property {
	public:
		//! The offset in bytes of the property variable to the beginning of the device_struc
		static constexpr size_t offset = offset_;
		//! The PropertyMeta type for this property
		using MetaData = PropertyMeta<device_struc, offset>;
		//! The actual member type used in the device_struc declaration
		using MemberType = typename PropertyMeta<device_struc, offset>::MemberType;
		//! The value type expected (may or may not be the same as the MemberType)
		using ValueType = typename PropertyMeta<device_struc, offset>::ValueType;
		
		
		Property(Agent *agent, int cindex) : agent(agent), cindex(cindex) {
			
		}
		
		//! Stores the given value in the COSMOS namespace
		inline Property& operator =(ValueType value) {
			// Retrieve the value pointer with its actual type
			MemberType *member_value = (MemberType*)((char*)&agent->cinfo->device[cindex] + offset);
			
			// Try to store a casted version of the type
			*member_value = (MemberType)value;
			
			return *this;
		}
		//! Retrieves the value in the COSMOS namespace
		inline operator ValueType() {
			// Retrieve the value with its actual type
			MemberType *member_value = (MemberType*)((char*)&agent->cinfo->device[cindex] + offset);
			
			// Return the value with a possibly casted type
			return (ValueType)*member_value;
		}
		
	private:
		//! The agent used to access the COSMOS namespace
		Agent *agent;
		//! The component index of the device this property belongs to
		int cindex;
	};
	
	
	
	
	
	
	//===============================================================
	//==================== PROPERTY DEFINITIONS =====================
	//===============================================================
	
	//============ Temperature Sensor ============
	_RegisterProperty("Temperature", tsenstruc, temp);
	_RegisterProperty("Enabled", tsenstruc, enabled);
	_RegisterProperty("Voltage", tsenstruc, volt);
	_RegisterProperty("Current", tsenstruc, amp);
	_RegisterProperty("Power", tsenstruc, power);
	_RegisterProperty("UTC", tsenstruc, utc);
	_RegisterProperty("Energy", tsenstruc, energy);
	
	//============ Heater ============
	_RegisterProperty("Temperature", htrstruc, temp);
	_RegisterProperty("Enabled", htrstruc, enabled);
	_RegisterProperty("Voltage", htrstruc, volt);
	_RegisterProperty("Current", htrstruc, amp);
	_RegisterProperty("Power", htrstruc, power);
	_RegisterProperty("UTC", htrstruc, utc);
	
	//============ Sun Sensor ============
	_RegisterProperty("Temperature", ssenstruc, temp);
	_RegisterProperty("Enabled", ssenstruc, enabled);
	_RegisterProperty("Voltage", ssenstruc, volt);
	_RegisterProperty("Current", ssenstruc, amp);
	_RegisterProperty("Power", ssenstruc, power);
	_RegisterProperty("UTC", ssenstruc, utc);
	
	//============ IMU ============
	_RegisterProperty("Temperature", imustruc, temp);
	_RegisterProperty("Enabled", imustruc, enabled);
	_RegisterProperty("Voltage", imustruc, volt);
	_RegisterProperty("Current", imustruc, amp);
	_RegisterProperty("Power", imustruc, power);
	_RegisterProperty("UTC", imustruc, utc);
	_RegisterPropertyWithType(Vec3, "Magnetic Field", imustruc, mag);
	_RegisterPropertyWithType(Vec3, "Acceleration", imustruc, accel);
	_RegisterPropertyWithType(Vec3, "Angular Acceleration", imustruc, omega);
	
	//============ GPS ============
	_RegisterProperty("Temperature", gpsstruc, temp);
	_RegisterProperty("Enabled", gpsstruc, enabled);
	_RegisterProperty("Voltage", gpsstruc, volt);
	_RegisterProperty("Current", gpsstruc, amp);
	_RegisterProperty("Power", gpsstruc, power);
	_RegisterProperty("UTC", gpsstruc, utc);
	_RegisterProperty("Satellites Used", gpsstruc, sats_used);
	_RegisterPropertyWithType(Location, "Location", gpsstruc, geods);
	_RegisterPropertyWithType(Vec3, "Velocity", gpsstruc, geocv);
	
	//============ Battery ============
	_RegisterProperty("Temperature", battstruc, temp);
	_RegisterProperty("Enabled", battstruc, enabled);
	_RegisterProperty("Voltage", battstruc, volt);
	_RegisterProperty("Current", battstruc, amp);
	_RegisterProperty("Power", battstruc, power);
	_RegisterProperty("UTC", battstruc, utc);
	_RegisterProperty("Percent", battstruc, percentage);
	_RegisterProperty("Capacity", battstruc, capacity);
	_RegisterProperty("Charge", battstruc, charge);
	_RegisterProperty("Efficiency", battstruc, efficiency);
	_RegisterProperty("Time Remaining", battstruc, time_remaining);
	
	//============ Radio Transceiver ============
	_RegisterProperty("Temperature", tcvstruc, temp);
	_RegisterProperty("Enabled", tcvstruc, enabled);
	_RegisterProperty("Voltage", tcvstruc, volt);
	_RegisterProperty("Current", tcvstruc, amp);
	_RegisterProperty("Power", tcvstruc, power);
	_RegisterProperty("UTC", tcvstruc, utc);
	_RegisterProperty("Frequency", tcvstruc, freq);
	_RegisterProperty("Max Frequency", tcvstruc, maxfreq);
	_RegisterProperty("Min Frequency", tcvstruc, minfreq);
	_RegisterProperty("Power In", tcvstruc, powerin);
	_RegisterProperty("Power Out", tcvstruc, powerout);
	_RegisterProperty("Max Power", tcvstruc, maxpower);
	_RegisterProperty("Bandwidth", tcvstruc, band);
	//_RegisterProperty("Good Packet Count", tcvstruc, goodcnt);
	//_RegisterProperty("Bad Packet Count", tcvstruc, badcnt);
	
	//============ CPU ============
	_RegisterProperty("Temperature", cpustruc, temp);
	_RegisterProperty("Enabled", cpustruc, enabled);
	_RegisterProperty("Voltage", cpustruc, volt);
	_RegisterProperty("Current", cpustruc, amp);
	_RegisterProperty("Power", cpustruc, power);
	_RegisterProperty("UTC", cpustruc, utc);
	_RegisterProperty("Up Time", cpustruc, uptime);
	_RegisterProperty("Load", cpustruc, load);
	_RegisterProperty("Max Load", cpustruc, maxload);
	_RegisterProperty("Max Memory", cpustruc, maxgib);
	_RegisterProperty("Memory Use", cpustruc, gib);
	_RegisterProperty("Boot Count", cpustruc, boot_count);
	
	//============ Camera ============
	_RegisterProperty("Temperature", camstruc, temp);
	_RegisterProperty("Enabled", camstruc, enabled);
	_RegisterProperty("Voltage", camstruc, volt);
	_RegisterProperty("Current", camstruc, amp);
	_RegisterProperty("Power", camstruc, power);
	_RegisterProperty("UTC", camstruc, utc);
	_RegisterProperty("Pixel Width", camstruc, pwidth);
	_RegisterProperty("Pixel Height", camstruc, pheight);
	_RegisterProperty("Width", camstruc, width);
	_RegisterProperty("Height", camstruc, height);
	_RegisterProperty("Focal Length", camstruc, flength);
	
	//============ Switch ============
	_RegisterProperty("Temperature", swchstruc, temp);
	_RegisterProperty("Enabled", swchstruc, enabled);
	_RegisterProperty("Voltage", swchstruc, volt);
	_RegisterProperty("Current", swchstruc, amp);
	_RegisterProperty("Power", swchstruc, power);
	_RegisterProperty("UTC", swchstruc, utc);
	
	//============ Custom Device ============
	_RegisterProperty("Temperature", ploadstruc, temp);
	_RegisterProperty("Enabled", ploadstruc, enabled);
	_RegisterProperty("Voltage", ploadstruc, volt);
	_RegisterProperty("Current", ploadstruc, amp);
	_RegisterProperty("Power", ploadstruc, power);
	_RegisterProperty("UTC", ploadstruc, utc);
	
	//===============================================================
	//====================== NODE PROPERTIES ========================
	//===============================================================
	
	template <typename T, size_t _offset>
	struct NodeProperty {
		//! The value type
		using ValueType = T;
		//! The byte offset to the property member
		static constexpr size_t offset = _offset;
	};
	
	//! A namespace holding all available node properties
	namespace Node {
		struct UTC : NodeProperty<double, offsetof(nodestruc, utc)> {
			static constexpr auto key = "node_utc";
			static constexpr const char *name = "UTC";
		};
		struct MomentOfInertia : NodeProperty<rvector, offsetof(nodestruc, moi)> {
			static constexpr auto key = "node_moi";
			static constexpr const char *name = "Moment of Inertia";
		};
		struct Mass : NodeProperty<float, offsetof(nodestruc, mass)> {
			static constexpr auto key = "node_mass";
			static constexpr const char *name = "Mass";
		};
		struct PowerGeneration : NodeProperty<float, offsetof(nodestruc, powgen)> {
			static constexpr auto key = "node_powgen";
			static constexpr const char *name = "Power Generation";
		};
		struct PowerUse : NodeProperty<float, offsetof(nodestruc, powuse)> {
			static constexpr auto key = "node_powuse";
			static constexpr const char *name = "Power Use";
		};
		struct BatteryCapacity : NodeProperty<float, offsetof(nodestruc, battcap)> {
			static constexpr auto key = "node_battcap";
			static constexpr const char *name = "Battery Capacity";
		};
		struct BatteryCharge : NodeProperty<float, offsetof(nodestruc, battlev)> {
			static constexpr auto key = "node_battlev";
			static constexpr const char *name = "Battery Charge";
		};
	}
	
	//===============================================================
	//==================== PROPERTIES UTILITIES =====================
	//===============================================================
	
	//! A unique ID corresponding to a particular property
	using PropertyID = intptr_t;
	
	
	/**
	 * @brief Returns a unique ID corresponding to a property
	 * @tparam T The property type (e.g. TemperatureSensor::Temperature or Node::UTC)
	 * @return The ID of the property
	 */
	template <typename T>
	PropertyID GetPropertyID() {
		// Use a dummy variable as the property key
		// A different variable will be created on each instance of this template
		static char key;
		
		// Return a casted version of the address of the variable,
		// since each address will be unique for each property
		return reinterpret_cast<PropertyID>(&key);
	}
	
	
	
	
//	enum class Devices : int {
//		Payload = (int):DeviceType::PLOAD,
//		SunSensor = (int)DeviceType::SSEN,
//		TempSensor = (int)DeviceType::TSEN,
//		TorqueRod = (int)DeviceType::MTR,
//		Antenna = (int)DeviceType::ANT,
//		CPU = (int)DeviceType::CPU,
//		IMU = (int)DeviceType::IMU,
//		GPS = (int)DeviceType::GPS,
//		ReactionWheel = (int)DeviceType::RW,
//		RadioReceiver = (int)DeviceType::RXR,
//		RadioTransmitter = (int)DeviceType::TXR,
//		RadioTransceiver = (int)DeviceType::TCV,
//		Motor = (int)DeviceType::MOTR,
//		Thruster = (int)DeviceType::THST,
//		PropellantTank = (int)DeviceType::PROP,
//		Switch = (int)DeviceType::SWCH,
//		Rotor = (int)DeviceType::ROT,
//		StarTracker = (int)DeviceType::STT,
//		MotionCaptureCamera = (int)DeviceType::MCC,
//		TorqueRodControlUnit = (int)DeviceType::TCU,
//		PowerBus = (int)DeviceType::BUS,
//		PressureSensor = (int)DeviceType::PSEN,
//		Camera = (int)DeviceType::CAM,
//		Telemetry = (int)DeviceType::TELEM,
//		DiskDrive = (int)DeviceType::DISK,
		
//	};
	
	const char* GetDeviceTypeString(DeviceType type);
	
	
	
	
	
	
	class SerializedProperty {
	public:
		SerializedProperty(const std::string &value) : value(value) {}
		
		template <typename T>
		T Get() const {
			return FromString<T>(value);
		}
		
		template <typename T>
		inline explicit operator T() const {
			return Get<T>();
		}
		
	private:
		std::string value;
	};
	
	
}

#endif
