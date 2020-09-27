
#ifndef CUBESAT_DEVICE_PYCUBED
#define CUBESAT_DEVICE_PYCUBED

#include "device/UARTDevice.h"
#include "device/PyCubedMessage.h"
#include "support/datalib.h"
#include "SimpleAgent/DeviceDetail.h"
#include <unordered_map>

namespace cubesat {
	
	class PyCubed;
	
	typedef void (*PyCubedShutdownCallback)();
	typedef void (*PyCubedReceiveFileCallback)(const std::string &file_name);
	
	//! Callback function for handling non-binary messages. Message arguments are supplied
	//! in the argument vector, and do not include the message type or checksum
	typedef bool (*PyCubedMessageHandlerCallback)(std::vector<std::string> args, PyCubed &pycubed);
	//! Callback function for parsing (potentially) binary messages. At the point
	//! this function is called, the message type and first comma have been read in
	//! from the UART device. Checksum handling is your responsibility!
	typedef bool (*PyCubedMessageParserCallback)(UARTDevice &uart, PyCubed &pycubed);
	
	
	typedef std::vector<std::string> (*PyCubedMessageSender)(std::vector<std::string> arg_strs);
	
	/**
	 * @brief Provides access to the PyCubed mainboard
	 */
	class PyCubed : protected UARTDevice {
		struct MessageHandler {
			PyCubedMessageHandlerCallback callback;
			unsigned int num_args;
		};
		struct MessageParser {
			PyCubedMessageParserCallback callback;
		};
		struct MessageSender {
			PyCubedMessageSender callback;
		};
		
		
	public:
		using UARTDevice::GetDevicePath;
		using UARTDevice::GetDeviceNumber;
		using UARTDevice::IsOpen;
		using UARTDevice::Open;
		using UARTDevice::Close;
		
		/**
		 * @brief Constructs a PyCubed object using the given bus and device numbers
		 * @param bus The UART bus number to use
		 * @param device The device number to use
		 */
		PyCubed(uint8_t bus, unsigned int baud);
		/**
		 * @brief Destructor
		 */
		virtual ~PyCubed();
		
		/**
		 * @brief Sends a typical (non-binary) message to the PyCubed
		 * @param message_type_str The message type string
		 * @param args The string arguments to write
		 * @return True upon success
		 */
		bool SendMessage(const std::string &message_type_str, const std::vector<std::string> &args);
		
		
		/**
		 * @brief Adds a message handler
		 * @param message_type_str The message type string to add support for
		 * @param callback The function to call when this message type is received
		 * @param num_args The number of arguments expected
		 */
		void AddMessageHandler(const std::string &message_type_str, PyCubedMessageHandlerCallback callback, int num_args) {
			MessageHandler handler;
			handler.callback = callback;
			handler.num_args = num_args;
			handlers[message_type_str] = handler;
		}
		/**
		 * @brief Adds a message parser
		 * @param message_type_str The message type string to add support for
		 * @param callback The function to call when this message type is received
		 */
		void AddMessageParser(const std::string &message_type_str, PyCubedMessageParserCallback callback) {
			MessageParser parser;
			parser.callback = callback;
			parsers[message_type_str] = parser;
		}
		
		/**
		 * @brief Sends a message that startup was successful
		 * @return The status of the operation
		 */
		inline bool StartupConfirmation() {
			return SendMessage(PYCUBED_BEAGLEBONE_STATUS_MSGTYPE,
			{"y", "n", "n"});
		}
		
		/**
		 * @brief Sends a handoff confirmation message
		 * @return The status of the operation
		 */
		inline bool Handoff() {
			return SendMessage(PYCUBED_BEAGLEBONE_STATUS_MSGTYPE,
			{"n", "y", "n"});
		}
		/**
		 * @brief Sends a message to kill the radio
		 * @return The status of the operation
		 */
		inline bool KillRadio() {
			return SendMessage(PYCUBED_BEAGLEBONE_STATUS_MSGTYPE,
			{"n", "n", "y"});
		}
		
		/**
		 * @brief Sets the callback function for when shutdown is requested
		 * @param callback The function to call
		 */
		inline void SetShutdownCallback(PyCubedShutdownCallback callback) {
			this->shutdown_callback = callback;
		}
		
		/**
		 * @brief Returns the latest IMU information received
		 * @return The IMU information
		 */
		inline PyCubedIMUInfo GetIMUInfo() const {
			return imu_info;
		}
		
		/**
		 * @brief Returns the latest GPS information received
		 * @return The GPS information
		 */
		inline PyCubedGPSInfo GetGPSInfo() const {
			return gps_info;
		}
		
		/**
		 * @brief Returns the latest temperature information received
		 * @return The temperature information
		 */
		inline PyCubedTempInfo GetTempInfo() const {
			return temp_info;
		}
		
		/**
		 * @brief Returns the latest power information received
		 * @return The power information
		 */
		inline PyCubedPowerInfo GetPowerInfo() const {
			return power_info;
		}
		
		
		/**
		 * @brief Pops the newest radio packet from the incoming queue.
		 * @param packet The output variable for the packet
		 * @return The packet size
		 */
		int PopIncomingPacket(PyCubedPacket &packet);
		
		/**
		 * @brief Sends a packet to the radio
		 * @param packet The packet
		 * @return The number of bytes written
		 */
		int TelecommandOutboundPacket(PyCubedDataPacket packet);
		
		
		/**
		 * @brief Polls the PyCubed device for received messages
		 * @return The number of messages received
		 */
		int ReceiveMessages();
		
		/**
		 * @brief Receives the next message available.
		 * @return True if the message was read successfully
		 */
		bool ReceiveNextMessage();
		
	private:
		//! The shutdown callback function
		PyCubedShutdownCallback shutdown_callback;
		//! The file receive callback
		PyCubedReceiveFileCallback receive_file_callback;
		
		//! Holds the last received IMU information
		PyCubedIMUInfo imu_info;
		//! Holds the last received GPS information
		PyCubedGPSInfo gps_info;
		//! Holds the last received temperature information
		PyCubedTempInfo temp_info;
		//! Holds the last received power information
		PyCubedPowerInfo power_info;
		
		//! Holds the incoming radio packets
		std::queue<PyCubedPacket> incoming_packets;
		
		//! The added message parsers
		std::unordered_map<std::string, MessageParser> parsers;
		//! The added message handlers
		std::unordered_map<std::string, MessageHandler> handlers;
		
		
		
		
		
		//! Radio packet parser
		static bool Parser_PKT(UARTDevice &uart, PyCubed &pycubed);
		
		//! PyCubed status handler
		static bool Handler_PST(std::vector<std::string> args, PyCubed &pycubed);
		//! IMU handler
		static bool Handler_IMU(std::vector<std::string> args, PyCubed &pycubed);
		//! GPS handler
		static bool Handler_GPS(std::vector<std::string> args, PyCubed &pycubed);
		//! Temperature handler
		static bool Handler_TMP(std::vector<std::string> args, PyCubed &pycubed);
		//! Power handler
		static bool Handler_PWR(std::vector<std::string> args, PyCubed &pycubed);
		
	};
	
}


#endif
