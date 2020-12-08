
#ifndef CUBESAT_AGENT_REQUEST
#define CUBESAT_AGENT_REQUEST

#include <functional>
#include <cmath>
#include <vector>

#include "RequestHelper.h"
#include "Exceptions.h"
#include "StringTools.h"

namespace artemis {
	
	//! Holds the callback function for an agent request
	class AgentRequest {
	public:
		/**
		 * @brief Creates a new request
		 * @param callback The callback function
		 */
		template <typename R, typename... Args>
		AgentRequest(R (*callback_)(Args...)) {
			callback = (void*)callback_;
			
			// Store a lambda function which can later be used to invoke the request.
			// This is used to avoid needing to know the function signature every time
			// we want to call the request
			invoker = +[](void *callback, const std::vector<std::string> &args, std::string &response) -> bool {
				
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
				std::tuple<Args...> arg_tuple;
				if ( !detail::GetArgumentTuple<Args...>(args, arg_tuple) ) {
					response = "Failed to parse one or more arguments";
					return false;
				}
				
				// Invoke the callback function
				response = detail::InvokeAgentRequest((R(*)(Args...))callback, arg_tuple);
				return true;
			};
			
			
			signature = detail::GetFunctionSignature<R, Args...>();
		}
		
		/**
		 * @brief Creates a new request
		 * @param callback The callback function
		 */
		template <typename R>
		AgentRequest(R (*callback_)(CapturedInput)) {
			callback = (void*)callback_;
			
			// Store a lambda function which can later be used to invoke the request.
			// This is used to avoid needing to know the function signature every time
			// we want to call the request
			invoker = +[](void *callback, const std::vector<std::string> &args, std::string &response) -> bool {
				
				// Invoke the callback function
				R(*typed_callback)(CapturedInput) = (R(*)(CapturedInput))callback;
				
				response = ToString<R>(typed_callback(CapturedInput(args)));
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
		bool Invoke(const std::vector<std::string> &args, std::string &response) {
			return invoker(callback, args, response);
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
		bool (*invoker)(void *callback, const std::vector<std::string> &args, std::string &response);
		
		//! The function signature string
		std::string signature;
	};
	
}


#endif
