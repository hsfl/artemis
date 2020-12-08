
#ifndef CUBESAT_DEVICE_REQUEST
#define CUBESAT_DEVICE_REQUEST

#include <functional>
#include <vector>

#include "RequestHelper.h"
#include "Exceptions.h"

namespace artemis {
	
	
	
	
	// Forward declaration
	class Device;
	
	
	
	
	class DeviceRequest {
	public:
		/**
		 * @brief Creates a new request
		 * @tparam D The device type
		 * @tparam R The return type
		 * @tparam Args The other arguments taken by the callback
		 * @param callback The callback function
		 */
		template <typename D, typename R, typename... Args>
		DeviceRequest(R (*callback_)(D*, Args...)) {
			callback = (void*)callback_;
			
			// Store a lambda function which can later be used to invoke the request.
			// This is used to avoid needing to know the function signature every time
			// we want to call the request
			invoker = +[](void *callback, Device *device_, const std::vector<std::string> &args, std::string &response) -> bool {
				
				// The number of arguments the callback takes
				constexpr int arg_count = sizeof...(Args);
				
				// Make sure the number of arguments supplied is correct
				if ( args.size() != arg_count ) {
					response = "Expected " + std::to_string(arg_count)
							+ (arg_count == 1 ? " argument but got " : " arguments but got ")
							+ std::to_string(args.size()) + " instead.";
					return false;
				}
				
				// Try to convert the string arguments to their respective types
				std::tuple<Args...> arg_tuple_no_device;
				if ( !detail::GetArgumentTuple<Args...>(args, arg_tuple_no_device) ) {
					response = "Failed to parse one or more arguments";
					return false;
				}
				
				// Downcast to the necessary type
				D *device = dynamic_cast<D*>(device_);
				if ( device == nullptr ) {
					response = "The request does not accept this type of device";
					return false;
				}
				
				// Insert the device into the tuple
				auto arg_tuple = std::tuple_cat(std::make_tuple(device), arg_tuple_no_device);
				
				// Invoke the callback function
				response = detail::InvokeAgentRequest((R(*)(D*, Args...))callback, arg_tuple);
				return true;
			};
			
			signature = detail::GetFunctionSignature<R, Args...>();
		}
		
		/**
		 * @brief Creates a new request
		 * @param callback The callback function
		 */
		template <typename D, typename R>
		DeviceRequest(R (*callback_)(Device *device_, CapturedInput)) {
			callback = (void*)callback_;
			
			// Store a lambda function which can later be used to invoke the request.
			// This is used to avoid needing to know the function signature every time
			// we want to call the request
			invoker = +[](void *callback, Device *device_, const std::vector<std::string> &args, std::string &response) -> bool {
				
				// Downcast to the necessary type
				D *device = dynamic_cast<D*>(device_);
				if ( device == nullptr ) {
					response = "The request does not accept this type of device";
					return false;
				}
				
				// Invoke the callback function
				R(*typed_callback)(D*, CapturedInput) = (R(*)(D*, CapturedInput))callback;
				
				response = ToString<R>(typed_callback(device, CapturedInput(args)));
				return true;
			};
			
			
			signature = detail::GetFunctionSignature<R, CapturedInput>();
		}
		
		/**
		 * @brief Invokes the request callback function with the given arguments
		 * @param args The argument strings
		 * @param response The response string output
		 * @return True if successful
		 */
		bool Invoke(Device *device, const std::vector<std::string> &args, std::string &response) {
			return invoker(callback, device, args, response);
		}
		
		/**
		 * @brief Returns a string representing the request callback signature
		 * @return The signature string
		 */
		inline const std::string& GetSignatureString() const {
			return signature;
		}
		
		
	private:
		//! A function pointer to the request callback
		void *callback;
		//! A function pointer to the invoker lambda function
		bool (*invoker)(void *callback, Device *device, const std::vector<std::string> &args, std::string &response);
		//! The function signature string
		std::string signature;
	};
	
}


#endif
