
#include "utility/files.h"

#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <algorithm>

using namespace std;
using namespace artemis;


void GetFiles(const string &folder, vector<string> &out) {
	out.clear();
	
	DIR *dir;
	struct dirent *ent;
	
	if ( (dir = opendir(folder.c_str())) != NULL ) {
		while ( (ent = readdir(dir)) != NULL ) {
			if ( strcmp(ent->d_name, ".") == 0 )
				continue;
			else if ( strcmp(ent->d_name, "..") == 0 )
				continue;
			
			out.push_back(ent->d_name);
		}
		closedir(dir);
	}
	else {
		throw std::runtime_error("Enable to read directory '" + folder + "'");
	}
}


OutgoingFolder::OutgoingFolder(const std::string &node) {
	
	// Create the log folder
	folder = getenv("HOME") + ("/cosmos/nodes/" + node + "/outgoing");
	if ( mkdir(folder.c_str(), 0777) == -1 ) {
		
		perror("Failed to make outgoing folder");
		
		if ( errno != EEXIST )
			throw std::runtime_error("Unable to create outgoing folder at " + folder);
	}
}

std::vector<std::string> IncomingFolder::GetOrdinaryFiles() const {
	vector<string> files;
	GetFiles(folder, files);
	
	for (auto it = files.begin(); it != files.end(); ++it) {
		// Remove command files
		if ( (*it).find("cmd") == 0 ) {
			files.erase(it);
		}
	}
	
	return files;
}

std::vector<std::string> OutgoingFolder::GetAllFiles() const {
	vector<string> files;
	GetFiles(folder, files);
	return files;
}

vector<string> OutgoingFolder::GetCommands() const {
	vector<string> files;
	GetFiles(folder, files);
	
	for (auto it = files.begin(); it != files.end(); ++it) {
		// Remove non-command files
		if ( (*it).find("cmd") != 0 ) {
			files.erase(it);
		}
	}
	
	return files;
}

vector<int> OutgoingFolder::GetCommandIDs() const {
	vector<string> files;
	vector<int> ids;
	GetFiles(folder, files);
	
	
	for (auto it = files.begin(); it != files.end(); ++it) {
		// Remove non-command files
		if ( (*it).find("cmd") == 0 ) {
			int id;
			sscanf(it->c_str(), "cmd%d", &id);
			ids.push_back(id);
		}
	}
	
	return ids;
}

int OutgoingFolder::GenerateCommandID() const {
	vector<int> waiting_command_ids = GetCommandIDs();
	
	
	// Find an unused command ID
	int id;
	do id = rand();
	while ( std::find(waiting_command_ids.begin(), waiting_command_ids.end(), id) != waiting_command_ids.end() || id == 0);
	
	return id;
}


void OutgoingFolder::WriteMessage(const OutgoingMessage &msg) {
	string filename = folder + "/";
	
	switch ( msg.type ) {
		case OutgoingMessageType::Command:
			filename += "cmd" + std::to_string(msg.contents.command.command_id);
			break;
		default:
			printf("OutgoingFolder: unsupported message type\n");
			return;
	}
	
	ofstream f(filename, ios::out | ios::binary);
	if ( !f.good() ) {
		printf("Failed to open file '%s'\n", filename.c_str());
		return;
	}
	
	f.write((char*)&msg, msg.length);
	f.close();
}
void OutgoingFolder::RemoveFile(const std::string &filename) {
	remove((folder + "/" + filename).c_str());
}
bool OutgoingFolder::ReadMessage(const std::string &filename, OutgoingMessage &msg) {
	
	ifstream f(folder + "/" + filename, ios::in | ios::ate);
	
	if ( !f.good() ) {
		printf("Failed to open file %s/%s\n", folder.c_str(), filename.c_str());
		return false;
	}
	
	std::streamsize size = f.tellg();
	f.seekg(0, std::ios::beg);
	
	std::vector<char> buffer(size);
	if ( f.read(buffer.data(), size) ) {
		memcpy(&msg, &buffer[0], buffer.size());
		remove((folder + "/" + filename).c_str());
		f.close();
		return true;
	}
	else {
		printf("Failed to read from file %s/%s", folder.c_str(), filename.c_str());
		f.close();
		return false;
	}
}

















IncomingFolder::IncomingFolder(const std::string &node) {
	// Create the log folder
	folder = getenv("HOME") + ("/cosmos/nodes/" + node + "/incoming");
	if ( mkdir(folder.c_str(), 0777) == -1 ) {
		
		perror("Failed to make outgoing folder");
		
		if ( errno != EEXIST )
			throw std::runtime_error("Unable to create outgoing folder at " + folder);
	}
}
std::vector<std::string> IncomingFolder::GetCommandResponses() const {
	vector<string> files;
	GetFiles(folder, files);
	
	for (auto it = files.begin(); it != files.end(); ++it) {
		// Remove non-command files
		if ( (*it).find("cmd") != 0 ) {
			files.erase(it);
		}
		else {
			(*it) = folder + "/" + *it;
		}
	}
	
	return files;
}
std::vector<int> IncomingFolder::GetCommandResponseIDs() const {
	vector<string> files;
	vector<int> ids;
	GetFiles(folder, files);
	
	
	for (auto it = files.begin(); it != files.end(); ++it) {
		// Remove non-command files
		if ( (*it).find("cmd") == 0 ) {
			int id;
			sscanf(it->c_str(), "cmd%d", &id);
			ids.push_back(id);
		}
	}
	
	return ids;
}

bool IncomingFolder::ReadMessage(const std::string &filename, IncomingMessage &msg) {
	
	ifstream f(folder + "/" + filename, ios::in | ios::ate);
	
	if ( !f.good() ) {
		printf("Failed to open file %s/%s\n", folder.c_str(), filename.c_str());
		return false;
	}
	
	std::streamsize size = f.tellg();
	f.seekg(0, std::ios::beg);
	
	std::vector<char> buffer(size);
	if ( f.read(buffer.data(), size) ) {
		memcpy(&msg, &buffer[0], buffer.size());
		remove((folder + "/" + filename).c_str());
		f.close();
	}
	else {
		printf("Failed to read from file %s/%s", folder.c_str(), filename.c_str());
		f.close();
		return false;
	}
	
	int checksum = (int)GetChecksum(msg);
	
	if ( checksum != (int)msg.checksum ) {
		printf("IncomingFolder: Checksum calculated (%d) does not match checksum provided (%d)\n",
			   checksum, (int)msg.checksum);
		return false;
	}
	else {
		return true;
	}
}


void IncomingFolder::WriteMessage(const IncomingMessage &msg) {
	string filename = folder + "/";
	
	switch ( msg.type ) {
		case IncomingMessageType::CommandResponse:
			filename += "cmd" + std::to_string(msg.contents.command_response.command_id);
			break;
		default:
			filename += "telem";
			break;
	}
	
	ofstream f(filename, ios::out | ios::binary);
	if ( !f.good() ) {
		printf("Failed to open file '%s'\n", filename.c_str());
		return;
	}
	
	f.write((char*)&msg, msg.length);
	f.close();
}


