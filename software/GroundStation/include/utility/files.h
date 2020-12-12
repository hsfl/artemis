#ifndef UTILITY_FILES
#define UTILITY_FILES

#include <string>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include "utility/message.h"

namespace artemis {
	
	
	
	class OutgoingFolder {
	public:
		OutgoingFolder(const std::string &node);
		
		
		std::vector<std::string> GetAllFiles() const;
		std::vector<std::string> GetCommands() const;
		std::vector<int> GetCommandIDs() const;
		
		int GenerateCommandID() const;
		
		void WriteMessage(const OutgoingMessage &msg);
		void RemoveFile(const std::string &filename);
		bool ReadMessage(const std::string &filename, OutgoingMessage &msg);
		
	private:
		std::string folder;
	};
	
	
	class IncomingFolder {
	public:
		IncomingFolder(const std::string &node);
		
		std::vector<std::string> GetOrdinaryFiles() const;
		std::vector<std::string> GetCommandResponses() const;
		std::vector<int> GetCommandResponseIDs() const;
		
		bool ReadMessage(const std::string &filename, IncomingMessage &msg);
		void WriteMessage(const IncomingMessage &msg);
		
	private:
		std::string folder;
	};
	
	
	
}



#endif
