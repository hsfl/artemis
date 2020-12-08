
#ifndef CUBESAT_DEVICE_RASPBERRYPI
#define CUBESAT_DEVICE_RASPBERRYPI

#include <string>

#define RASPI_INCOMING_FOLDER "/home/pi/outgoing"
#define RASPI_OUTGOING_FOLDER "/home/pi/incoming"
#define BEAGLEBONE_INCOMING_FOLDER "/home/debian/raspi/incoming"
#define BEAGLEBONE_OUTCOMING_FOLDER "/home/debian/raspi/outgoing"

namespace artemis {
	
	
	
	class RaspberryPi {
	public:
		
		
		/**
		 * @brief Uses rsync to synchronize source file with destination file
		 * @param src The source file
		 * @param dest The destination file
		 */
		void SendFile(const std::string &src, const std::string &dest);
	};
	
	
}


#endif
