#ifndef UTILITY_MESSAGE
#define UTILITY_MESSAGE

#include <string>


namespace artemis {
	
	
	
	enum class IncomingMessageType : unsigned char {
		CommandResponse,
		FilePacket,
		TemperatureTelemetry,
		PowerTelemetry,
		LuxTelemetry,
		IMUTelemetry,
		// ----------
		Invalid
	};
	
	struct IncomingMessage {
		unsigned int length;
		unsigned char checksum;
		IncomingMessageType type;
		double timestamp;
		union {
			struct {
				unsigned int command_id;
				char response[256];
			} command_response;
			struct {
				bool termination_flag;
				unsigned int packet_number;
				unsigned int length;
				char packet[256];
			} file_packet;
			struct {
				float eps_temperature;
				float obc_temperature;
				float raspi_temperature;
				float battery_temperature;
				float pycubed_temperature;
			} temperature_telem;
			struct {
				float system_voltage;
				float system_current;
				float battery_voltage;
				float battery_current;
			} power_telem;
			struct {
				float plusx_lux;
				float minusx_lux;
				float plusy_lux;
				float minusy_lux;
				float plusz_lux;
				float minusz_lux;
			} lux_telem;
			struct {
				float magnetic_field[3];
				float acceleration[3];
				float angular_velocity[3];
			} imu_telem;
			struct {
				float latitude;
				float longitude;
				float altitude;
				bool fix;
			} gps_telem;
		} contents;
	};
	
	
	enum class OutgoingMessageType : unsigned char {
		Command,
		
		// ----------
		Invalid
	};
	
	struct OutgoingMessage {
		unsigned int length;
		unsigned char checksum;
		OutgoingMessageType type;
		double timestamp;
		union {
			struct {
				unsigned int command_id;
				char command[256];
			} command;
			struct {
				bool termination_flag;
				unsigned int packet_number;
				unsigned int length;
				char packet[256];
			} file_packet;
		} contents;
	};
	
	
	unsigned char GetChecksum(const IncomingMessage &message);
	unsigned char GetChecksum(const OutgoingMessage &message);
	
	IncomingMessage BytesToIncomingMessage(char *bytes, unsigned int max_length);
	unsigned int OutgoingMessageToBytes(const OutgoingMessage &message, char *bytes, unsigned int max_length);
	bool PrepareOutgoingMessage(OutgoingMessage &message);
	
	
	
}



#endif
