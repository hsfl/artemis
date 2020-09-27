
#ifndef CUBESAT_EXCEPTIONS
#define CUBESAT_EXCEPTIONS


#include <exception>
#include <string>
#include <stdexcept>



namespace cubesat {
	
	//! Thrown if the user attempts to create a device with
	//! a name that is already taken
	class DeviceAlreadyExistsException : public std::exception {
	public:
		DeviceAlreadyExistsException(const std::string &device_name) {
			error_msg = "The device '" + device_name + "' already exists.";
		}
		
	  virtual const char* what() const throw() {
		return error_msg.c_str();
	  }
		
	private:
		std::string error_msg;
	};
	
	//! Thrown if the user attempts to create a second SimpleAgent in the same process
	class MultipleSimpleAgentException : public std::exception {
	public:
		MultipleSimpleAgentException(const std::string &msg) : error_msg(msg) {}
		
	  virtual const char* what() const throw() {
		return error_msg.c_str();
	  }
		
	private:
		std::string error_msg;
	};
	
	
	
	//! Thrown if a non-existent property is accessed
	class NonExistentPropertyException : public std::exception {
	public:
		NonExistentPropertyException(const std::string &prop_name) {
			error_msg = "Attempted to access nonexistent property '" + prop_name + "'";
		}
		
	  virtual const char* what() const throw() {
		return error_msg.c_str();
	  }
		
	private:
		std::string error_msg;
	};
	
	//! Thrown if a non-existent property is accessed
	class TypeMismatchException : public std::exception {
	public:
		TypeMismatchException(const std::string &msg) : error_msg(msg) {}
		
	  virtual const char* what() const throw() {
		return error_msg.c_str();
	  }
		
	private:
		std::string error_msg;
	};
	
	
	class ArgumentMismatchException : public std::runtime_error {
		public:
			ArgumentMismatchException(std::string const& msg) : std::runtime_error(msg) {}
	};
	
	class CallbackNotSetException : public std::runtime_error {
		public:
			CallbackNotSetException(std::string const& msg): std::runtime_error(msg) {}
	};
	
	class NonexistentRequestException : public std::runtime_error {
		public:
			NonexistentRequestException(std::string const& msg): std::runtime_error(msg) {}
	};

	
}

#endif
