
#ifndef CUBESAT_REQUEST_HELPER
#define CUBESAT_REQUEST_HELPER

#include <functional>
#include <cmath>
#include <vector>
#include <type_traits>

#include "StringTools.h"
#include "Exceptions.h"

namespace artemis {
	
	namespace detail {
		
		// C++11 implementation of the C++14 std::index_sequence type
		template <std::size_t ...>
		struct IndexSequence
		 { };
		
		template <std::size_t N, std::size_t ... Next>
		struct IndexSequenceHelper : public IndexSequenceHelper<N-1U, N-1U, Next...>
		 { };
		
		template <std::size_t ... Next>
		struct IndexSequenceHelper<0U, Next ... >
		 { using type = IndexSequence<Next ... >; };
		
		template <std::size_t N>
		using MakeIndexSequence = typename IndexSequenceHelper<N>::type;
		
		
		
		template <typename T>
		inline static T ConvertArgument(const std::string &string, bool &success_flag) {
			bool success_flag_temp;
			T result = FromString<T>(string, success_flag_temp);
			success_flag = success_flag & success_flag_temp;
			
			return result;
		}
		
		// Helper function
		template<typename... Args, std::size_t... S>
		inline static bool GetArgumentTuple(const std::vector<std::string>& args, std::tuple<Args...> &out, IndexSequence<S...>) {
			bool success = true;
			out = std::make_tuple(ConvertArgument<Args>(args[S], success)...);
			return success;
		}
		
		/**
		 * @brief Converts a vector of argument strings into a tuple of values
		 * @tparam Args The types to convert to
		 * @param args The string arguments
		 * @param out The tuple output
		 * @return True if all arguments were converted successfully
		 */
		template<typename... Args>
		inline static bool GetArgumentTuple(const std::vector<std::string> &args, std::tuple<Args...> &out) {
			return GetArgumentTuple(args, out, MakeIndexSequence<sizeof...(Args)>());
		}
		
		enum class enabler_t {};
		
		template<typename T>
		using EnableIf = typename std::enable_if<T::value, enabler_t>::type;
		
		
		// Helper function
		template<typename R, typename...Args, typename Tuple, std::size_t... S,
				 typename std::enable_if<!std::is_same<R, void>::value, int>::type = 0>
		inline static std::string InvokeAgentRequest(R(*func)(Args...), Tuple args, IndexSequence<S...>) {
			return ToString(func(std::get<S>(args)...));
		}
		
		
		// Helper function
		template<typename R, typename...Args, typename Tuple, std::size_t... S,
				 typename std::enable_if<std::is_same<R, void>::value, int>::type = 0>
		inline static std::string InvokeAgentRequest(R(*func)(Args...), Tuple args, IndexSequence<S...>) {
			func(std::get<S>(args)...);
			return "";
		}
		
		
		/**
		 * @brief Invoke Invokes a function using the given tuple as arguments
		 * @param func The function to invoke
		 * @param args The arguments to pass, stored in a tuple
		 * @return The response string
		 */
		template<typename Function, typename Tuple>
		inline static std::string InvokeAgentRequest(Function func, Tuple args) {
			static constexpr auto size = std::tuple_size<Tuple>::value;
			return InvokeAgentRequest(func, args, MakeIndexSequence<size>());
		}
		
		
		
		template <typename T>
		void AppendArgumentType(std::string &signature_str, bool is_last) {
			signature_str += TypeName<T>();
			if ( !is_last )
				signature_str += ", ";
		}
		
		
		// Helper function
		template<typename R, typename... Args, std::size_t... S>
		inline static std::string GetFunctionSignature(IndexSequence<S...>) {
			std::string signature_str = "(";
			
			using dummy = int[];
			(void)dummy {0, (AppendArgumentType<Args>(signature_str, S == sizeof...(Args) - 1), 0)...};
			signature_str += ") -> " + TypeName<R>();
			
			return signature_str;
		}
		
		/**
		 * @brief Returns a string representing the function signature
		 * @tparam R The return type
		 * @tparam Args The arguments
		 * @return The function signature string
		 */
		template<typename R, typename... Args>
		inline static std::string GetFunctionSignature() {
			std::string signature;
			return GetFunctionSignature<R, Args...>(MakeIndexSequence<sizeof...(Args)>());
		}
	}
	
}


#endif
