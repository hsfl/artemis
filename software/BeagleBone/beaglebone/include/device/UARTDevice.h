
#ifndef CUBESAT_DEVICE_UARTDEVICE
#define CUBESAT_DEVICE_UARTDEVICE

#include <string>
#include <queue>
#include <stdint.h>
#include <termios.h>



namespace artemis {
	
	/**
	 * @brief Utility class for communicating with serial UART devices
	 */
	class UARTDevice {
		
		//! Holds data for spoofed input
		struct SpoofedInput {
			//! The input data
			uint8_t input[256];
			//! The length of the input data
			unsigned int length;
			//! Points to the last byte read in
			unsigned int index = 0;
		};
		
	public:
		/**
		 * @brief Constructs a new UARTDevice
		 * @param device The UART device number
		 * @param baud_rate The baud rate (bits per second)
		 */
		UARTDevice(unsigned int device, unsigned int baud_rate);
		/**
		 * @brief Destructor. Closes the UART device, if still open
		 */
		virtual ~UARTDevice();
		
		/**
		 * @brief Attempts to open the UART device
		 * @return True if the device was opened successfully
		 */
		virtual bool Open();
		/**
		 * @brief Closes the UART device, if still open
		 */
		virtual void Close();
		
		/**
		 * @brief Checks whether the device is open
		 * @return True if the device is open
		 */
		inline bool IsOpen() const {
			return file >= 0;
		}
		/**
		 * @brief Returns the device number of this UART
		 * @return The device number
		 */
		inline unsigned int GetDeviceNumber() const {
			return device;
		}
		/**
		 * @brief Returns the UART device file path
		 * @return The file path
		 */
		inline std::string GetDevicePath() const {
			return "/dev/ttyO" + std::to_string(device);
		}
		/**
		 * @brief Returns the number of bytes available to read in
		 * @return The number of bytes available, or zero if the UART is not open.
		 */
		virtual size_t InWaiting() const;
		
		/**
		 * @brief Writes a single byte
		 * @param byte The byte
		 * @return True if successful
		 */
		virtual bool WriteByte(uint8_t byte);
		/**
		 * @brief Writes an array of bytes
		 * @param bytes The byte array
		 * @param len The number of bytes to write
		 * @return True if successful
		 */
		virtual bool Write(uint8_t bytes[], unsigned int len);
		/**
		 * @brief Reads a number of bytes
		 * @param out The byte array to read to
		 * @param len The maximum number of bytes to read
		 * @return The actual number of bytes read
		 */
		virtual size_t Read(uint8_t out[], size_t len);
		/**
		 * @brief Reads until a newline character is reached
		 * @param out The byte array to read to
		 * @param len The maximum number of bytes to read
		 * @return The actual number of bytes read
		 */
		virtual size_t ReadLine(uint8_t out[], size_t len);
		
		/**
		 * @brief Blocks output until all data is transmitted
		 */
		virtual void Drain();
		
		/**
		 * @brief Spoofs input to the device. Used mainly for debugging purposes.
		 * Disable at compile time by using defining the CUBESAT_DISABLE_UART_SPOOFING macro
		 * @param input The input string to spoof
		 * @param len The length of the input string
		 */
		void SpoofInput(uint8_t input[], unsigned int len);
		
		
		
	private:
		//! The name of the UART device file
		std::string filename;
		//! The UART device number
		unsigned int device;
		//! The serial baud rate
		unsigned int baud_rate;
		//! The	file handle
		int file;
		//! Used to set the UART attributes
		struct termios uartTermios, oldDescriptor;
		
		//! A vector of spoofed inputs
		std::vector<SpoofedInput> spoofed_input;
	};

}

#endif
