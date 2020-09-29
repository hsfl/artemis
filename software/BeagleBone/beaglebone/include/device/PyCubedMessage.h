
#ifndef CUBESAT_DEVICE_PYCUBEDMESSAGE
#define CUBESAT_DEVICE_PYCUBEDMESSAGE

#include <cstdint>
#include <cstdlib>
#include <string>
#include <cstring>
#include "support/datalib.h"
#include "SimpleAgent/Types.h"

#define PYCUBED_BEAGLEBONE_STATUS_MSGTYPE "BST"
#define PYCUBED_PYCUBED_STATUS_MSGTYPE "PST"
#define PYCUBED_FILE_TRANSFER_MSGTYPE "FTR"
#define PYCUBED_IMU_DATA_MSGTYPE "IMU"
#define PYCUBED_GPS_DATA_MSGTYPE "GPS"
#define PYCUBED_TEMP_DATA_MSGTYPE "TMP"
#define PYCUBED_POWER_DATA_MSGTYPE "PWR"
#define PYCUBED_PACKET_MSGTYPE "PKT"

namespace cubesat {
	
	struct PyCubedPacketHeader {
		uint8_t bytes[6];
		struct {
			unsigned packet_version_number : 3;
			unsigned packet_type : 1;
			unsigned secondary_header_flag : 1;
			unsigned apid : 11;
			unsigned sequence_flags : 2;
			unsigned sequence_count : 14;
			unsigned packet_data_length : 16;
		} fields;
	};
	
	struct PyCubedPacketData
	{
		union {
			uint8_t id_bytes[2];
			uint16_t message_type_id;
		};
		vector<uint8_t> data;
	};
	
	struct PyCubedPacket {
		PyCubedPacketHeader header;
		PyCubedPacketData content;
	};
	
	struct PyCubedDataPacket {
		uint32_t addr;
		uint16_t length;
		vector<uint8_t> data;
		bool corrupted;
	};
	
	
	
	
	//! Holds IMU information
	struct PyCubedIMUInfo {
		double utc;
		Vec3 magnetometer;
		Vec3 acceleration;
		Vec3 gyroscope;
	};
	
	//! Holds GPS information
	struct PyCubedGPSInfo {
		double utc;
		bool has_fix;
		float latitude;
		float longitude;
		int fix_quality;
		int sats_used;
		float altitude;
		float speed;
		float azimuth;
		float horizontal_dilution;
	};
	
	//! Holds temperature information
	struct PyCubedTempInfo {
		double utc;
		float cpu_temp;
		float batt_temp;
	};
	
	//! Holds power information
	struct PyCubedPowerInfo {
		double utc;
		float batt_voltage;
		float batt_current;
		float sys_voltage;
		float sys_current;
	};
}


#endif
