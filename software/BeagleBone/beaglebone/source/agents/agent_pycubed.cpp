
#include "CubeSat.h"
#include "SimpleAgent/SimpleAgent.h"
#include "device/PyCubed.h"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <net/if.h>
#include <linux/if_tun.h>

// The interval between iterations in the run_agent() function
#define SLEEP_TIME 0.25

#define PYCUBED_UART 0
#define PYCUBED_BAUD 9600

#define MAXBUFFERSIZE 2560 // comm buffer for agents
#define TUN_BUF_SIZE 2000

using namespace std;
using namespace cubesat;


// The agent object which allows for communication with COSMOS
SimpleAgent *agent;
CPU *pycubed;
IMU *imu;
GPS *gps;
Battery *battery;
RadioTransceiver *radio;
Timer connection_timer;

PyCubed *handler = nullptr;

// Tunnel stuff
static queue<vector<uint8_t> > tun_fifo;
static queue<vector<uint8_t> > tcv_fifo;

static condition_variable tcv_fifo_check;
static condition_variable tun_fifo_check;

static int tun_fd;

static string rxr_devname;
static string txr_devname;
static uint16_t tunnel_mtu = 512;

int tun_out, tun_in, gl_in, gl_out = 0;


//! Sets up the PyCubed
void InitPyCubed();
//! Tries to connect to the PyCubed
bool ConnectPyCubed();
//! Handles operations with the PyCubed
void UpdatePyCubed();

/**
 * @brief Shutdown callback function
 */
void Shutdown();

string Request_IsUp();
string Request_SendMessage(string message);
string Request_GetIMUData();
string Request_GetGPSData();
string Request_GetPowerData();
string Request_GetTemperatureData();
string Request_KillRadio();


// Tunnel stuff
void StartTunnel(const std::string &tunnel_ip);
void tcv_read_loop();
void tcv_write_loop();
void tun_read_loop();
void tun_write_loop();

int32_t request_tunnel_queue_size(char *request, char *response, Agent *);
int32_t request_serial_queue_size(char *request, char *response, Agent *);

// ===========================================








int main(int argc, char** argv) {
	std::string tunnel_ip;
	vector<uint8_t> buffer;
	bool do_tunnel = true;
	
	switch ( argc ) {
		case 2: {
			// Get address for tunnel
			tunnel_ip = argv[1];
		} break;
		default:
			printf("To establish tunnel: agent_pycubed ip_address\n");
			do_tunnel = false;
			break;
	}
	
	// Initialize the Agent
	agent = new SimpleAgent(CUBESAT_AGENT_PYCUBED_NAME);
	agent->SetLoopPeriod(SLEEP_TIME);
	
	agent->AddNodeProperty<Node::PowerUse>(0);
	agent->AddNodeProperty<Node::PowerGeneration>(0);
	agent->AddNodeProperty<Node::BatteryCapacity>(3.5f * 4);
	agent->AddNodeProperty<Node::BatteryCharge>(0);
	
	// Initialize the PyCubed
	InitPyCubed();
	
	// Finish adding properties
	agent->Finalize();
	
	// Debug print
	agent->DebugPrint(true);
	
	// Initialize the network tunnel
	if ( do_tunnel ) {
		StartTunnel(tunnel_ip);
		
		// Start tunnel threads
		thread tun_read_thread(tun_read_loop);
		thread tun_write_thread(tun_write_loop);
	}
	
	
	// Run the main loop for this agent
	while ( agent->StartLoop() ) {
		
		// Try to connect to the PyCubed
		ConnectPyCubed();
		
		// Update the PyCubed
		UpdatePyCubed();
	}
	
	// Tidy up
	delete handler;
	delete agent;
	
	
	return 0;
}


void InitPyCubed() {
	
	// Create a new PyCubed device
	handler = new PyCubed(PYCUBED_UART, PYCUBED_BAUD);
	handler->SetShutdownCallback(Shutdown);
	
	// Add the PyCubed CPU device
	pycubed = agent->NewDevice<CPU>("pycubed");
	pycubed->Post(pycubed->utc = Time::Now());
	pycubed->Post(pycubed->memory_usage = 0);
	pycubed->Post(pycubed->max_memory = 0.0037252903); // MR25H40MDF RAM
	pycubed->Post(pycubed->voltage = 0);
	pycubed->Post(pycubed->current = 0);
	pycubed->Post(pycubed->up_time = 0);
	pycubed->Post(pycubed->temperature = 273.15);
	pycubed->SetCustomProperty<bool>("sent_startup_confirmation", false);
	pycubed->SetCustomProperty<PyCubed*>("handler", handler);
	
	// Add the battery pack
	battery = agent->NewDevice<Battery>("battery");
	battery->Post(battery->utc = Time::Now());
	battery->Post(battery->temperature = 273.15);
	battery->Post(battery->capacity = 3.5f * 4);
	battery->Post(battery->charge = 3.5f * 4);
	battery->Post(battery->efficiency = 0.85f);
	battery->Post(battery->percentage = 100);
	battery->Post(battery->voltage = 0);
	battery->Post(battery->current = 0);
	battery->AddRequest("charge", +[](Battery *battery) -> float { return battery->charge; }, "Returns the battery charge");
	
	
	// Add the IMU
	imu = agent->NewDevice<IMU>("imu");
	imu->Post(imu->utc = Time::Now());
	imu->Post(imu->temperature = 273.15);
	imu->Post(imu->acceleration = Vec3());
	imu->Post(imu->magnetic_field = Vec3());
	imu->Post(imu->angular_velocity	= Vec3());
	
	// Add the GPS
	gps = agent->NewDevice<GPS>("gps");
	gps->Post(gps->utc = Time::Now());
	gps->Post(gps->location = Location());
	gps->Post(gps->velocity = Vec3());
	gps->Post(gps->satellites_used = 0);
}

bool ConnectPyCubed() {
	
	// It's all good if we're already connected
	if ( handler->IsOpen() )
		return true;
	
	// Try to open the PyCubed device
	if ( handler->Open() >= 0 ) {
		
		// Mark the time the PyCubed was connected to
		connection_timer.Start();
		
		printf("Successfully opened PyCubed device at %s\n", handler->GetDevicePath().c_str());
		return true;
	}
	else {
		printf("Failed to open PyCubed device at %s\n", handler->GetDevicePath().c_str());
		
		// Close the device just in case
		handler->Close();
		return false;
	}
}

void UpdatePyCubed() {
	
	pycubed->enabled = handler->IsOpen();
	
	
	// Make sure the PyCubed is connected
	if ( !handler->IsOpen() ) {
		
		// Set the PyCubed connection status
		pycubed->enabled = false;
		pycubed->up_time = 0;
		
		// Update timestamps
		pycubed->utc = Time::Now();
		battery->utc = Time::Now();
		imu->utc = Time::Now();
		gps->utc = Time::Now();
		
		return;
	}
	
	// Send startup confirmation
	if ( !pycubed->GetCustomProperty<bool>("sent_startup_confirmation") ) {
		handler->StartupConfirmation();
		pycubed->SetCustomProperty<bool>("sent_startup_confirmation", true);
	}
	
	// Receive messages from pycubed
	handler->ReceiveMessages();
	
	// Get the latest device information
	PyCubedIMUInfo imu_info = handler->GetIMUInfo();
	PyCubedGPSInfo gps_info = handler->GetGPSInfo();
	PyCubedPowerInfo power_info = handler->GetPowerInfo();
	PyCubedTempInfo temp_info = handler->GetTempInfo();
	
	// Store CPU info
	pycubed->utc = Time::Now();
	pycubed->voltage = power_info.sys_voltage;
	pycubed->current = power_info.sys_current;
	pycubed->temperature = temp_info.cpu_temp;
	pycubed->up_time = (int)connection_timer.Seconds();
	
	// Store battery info
	battery->utc = Time::Now();
	battery->voltage = power_info.batt_voltage;
	battery->current = power_info.batt_current;
	battery->temperature = temp_info.batt_temp;
	
	// Store IMU info
	imu->utc = Time::Now();
	imu->temperature = temp_info.cpu_temp;
	imu->magnetic_field = imu_info.magnetometer;
	imu->acceleration = imu_info.acceleration;
	imu->angular_velocity = imu_info.gyroscope;
	
	// Store GPS info
	gps->utc = Time::Now();
	gps->location = Location(gps_info.latitude, gps_info.longitude, gps_info.altitude);
	gps->velocity = Vec3(gps_info.speed, 0, 0);
	gps->satellites_used = gps_info.sats_used;
	
	// Store node info
	agent->SetNodeProperty<Node::PowerUse>(power_info.batt_current * power_info.batt_voltage);
	agent->SetNodeProperty<Node::BatteryCharge>(0); // ?
}


void Shutdown() {
	
	// 1. Shut down agents (not agent_switch)
	system("agent " CUBESAT_NODE_NAME " " CUBESAT_AGENT_TEMP_NAME " shutdown");
	system("agent " CUBESAT_NODE_NAME " " CUBESAT_AGENT_SUNSENSOR_NAME " shutdown");
	system("agent " CUBESAT_NODE_NAME " " CUBESAT_AGENT_HEATER_NAME " shutdown");
	system("agent " CUBESAT_NODE_NAME " " CUBESAT_AGENT_RASPI_NAME " shutdown");
	
	// 2. Turn off hardware components (agent_switch)
	system("agent " CUBESAT_NODE_NAME " " CUBESAT_AGENT_SWITCH_NAME " disable all");
	
	// 3. Give PyCubed permission to take over
	handler->Handoff();
	agent->Shutdown();
	
	// 4. Shut down the BeagleBone
	system("shutdown -h now");
	
	exit(0);
}

//===============================================================
//=========================== TUNNEL ============================
//===============================================================


void StartTunnel(const std::string &tunnel_ip) {
	// Initialize Gamalink
	//	gamalink = new GamaLink();
	//	gamalink->set_debug_level(GamaLink::debugLevel::OFF);
	//	iretn = gamalink->init(dev);
	//	if(iretn < 0 ){
	//		printf("Could not intialize \n");
	//		exit(-1);
	//	}
	
	// Start serial threads
	thread tcv_read_thread(tcv_read_loop);
	thread tcv_write_thread(tcv_write_loop);
	
	// Open tunnel device
	int tunnel_sock;
	struct ifreq ifr1, ifr2;
	struct sockaddr_in *addr = (struct sockaddr_in *)&ifr2.ifr_addr;
	
	if ((tun_fd=open("/dev/net/tun", O_RDWR)) < 0)
	{
		perror("Error opening tunnel device");
		exit (-1);
	}
	
	memset(&ifr1, 0, sizeof(ifr1));
	ifr1.ifr_flags = IFF_TUN | IFF_NO_PI;
	strncpy(ifr1.ifr_name, agent->GetComplexAgent()->cinfo->agent[0].beat.proc, IFNAMSIZ);
	if (ioctl(tun_fd, TUNSETIFF, static_cast<void *>(&ifr1)) < 0)
	{
		perror("Error setting tunnel interface");
		exit (-1);
	}
	
	if((tunnel_sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_IP)) < 0)
	{
		perror("Error opening tunnel socket");
		exit (-1);
	}
	
	// Get ready to set things
	strncpy(ifr2.ifr_name, agent->GetComplexAgent()->cinfo->agent[0].beat.proc, IFNAMSIZ);
	ifr2.ifr_addr.sa_family = AF_INET;
	
	// Set interface address
	
	inet_pton(AF_INET, tunnel_ip.c_str(), &addr->sin_addr);
	if (ioctl(tunnel_sock, SIOCSIFADDR, &ifr2) < 0 )
	{
		perror("Error setting tunnel address");
		exit (-1);
	}
	
	// Set interface netmask
	inet_pton(AF_INET, static_cast<const char *>("255.255.255.0"), &addr->sin_addr);
	if (ioctl(tunnel_sock, SIOCSIFNETMASK, &ifr2) < 0 )
	{
		perror("Error setting tunnel netmask");
		exit (-1);
	}
	
	if (ioctl(tunnel_sock, SIOCGIFFLAGS, &ifr2) < 0 )
	{
		perror("Error getting tunnel interface flags");
		exit (-1);
	}
	
	// Bring interface up
	ifr2.ifr_flags |= (IFF_UP | IFF_RUNNING);
	if (ioctl(tunnel_sock, SIOCSIFFLAGS, &ifr2) < 0 )
	{
		perror("Error setting tunnel interfa ce flags");
		exit (-1);
	}
	
	// Set interface MTU
	ifr2.ifr_mtu = tunnel_mtu;
	if (ioctl(tunnel_sock, SIOCSIFMTU, &ifr2) < 0 )
	{
		perror("Error setting tunnel interface MTU");
		exit (-1);
	}
	
	
	close(tunnel_sock);
}

void tun_read_loop() {
	vector<uint8_t> buffer;
	ssize_t nbytes;
	
	while ( agent->IsRunning() ) {
		
		buffer.resize(TUN_BUF_SIZE);
		nbytes = read(tun_fd, &buffer[0], TUN_BUF_SIZE);
		if (nbytes > 0)
		{	// Start of mutex for tcv fifo
			tun_in ++;
			
			buffer.resize(static_cast<size_t>(nbytes));
			tcv_fifo.push(buffer);
			tcv_fifo_check.notify_one();
		}	// End of mutex for tcv fifo
	}
}

void tun_write_loop() {
	vector<uint8_t> buffer;
	ssize_t nbytes;
	std::mutex tun_fifo_lock;
	std::unique_lock<std::mutex> locker(tun_fifo_lock);
	
	while ( agent->IsRunning() ) {
		
		tun_fifo_check.wait(locker);
		// End of mutex for tun fifo
		
		while (!tun_fifo.empty())
		{
			buffer = tun_fifo.front();
			nbytes = write(tun_fd, &buffer[0], buffer.size());
			if (nbytes > 0)
			{
				tun_fifo.pop();
				tun_out ++;
			}
		}
	}
}

void tcv_read_loop() { // reading from gamalink packet buffer (incoming)
	vector<uint8_t> buffer;
	ssize_t nbytes;
	PyCubedPacket packet;
	PyCubed *handler = nullptr;
	
	
	while ( agent->IsRunning() ) {
		
		if ( handler == nullptr )
			handler = pycubed->GetCustomProperty<PyCubed*>("handler");
		
		// Read data from receiver port
		buffer.resize(TUN_BUF_SIZE);
		
		if ( handler == nullptr )
			nbytes = 0;
		else
			nbytes = handler->IsOpen() ? handler->PopIncomingPacket(packet) : 0;
		
		if ( nbytes > 0 ) { // Start of mutex for tun FIFO
			gl_in ++;
			buffer.resize(0);
			
			for(uint16_t i = 0; i < nbytes; i++){
				buffer.push_back(packet.content.data[i+6]);
			}
			
			tun_fifo.push(buffer);
			tun_fifo_check.notify_one();
			
		} // End of mutex for tun FIFO
	}
}

void tcv_write_loop() { // telecommand send gamalink packet (outgoing)
	std::mutex tcv_fifo_lock;
	std::unique_lock<std::mutex> locker(tcv_fifo_lock);
	vector<uint8_t> buffer;
	PyCubed *handler;
	
	PyCubedDataPacket out_packet;
	while ( agent->IsRunning()) {
		tcv_fifo_check.wait(locker);
		
		if ( handler == nullptr )
			handler = pycubed->GetCustomProperty<PyCubed*>("handler");
		
		while ( !tcv_fifo.empty() ) {
			// Get next packet from transceiver FIFO
			buffer = tcv_fifo.front();
			tcv_fifo.pop();
			gl_out ++;
			// Write data to transmitter port
			out_packet.length = buffer.size();
			out_packet.addr = 255;
			out_packet.data = buffer;
			
			if ( handler != nullptr && handler->IsOpen() )
				handler->TelecommandOutboundPacket(out_packet);
			else
				printf("Attempted to send packets, but PyCubed device is not open.\n");
			//gamalink->telecommand_outbound_packet(out_packet);
		}
	}
}

