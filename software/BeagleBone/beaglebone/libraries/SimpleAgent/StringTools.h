
#ifndef CUBESAT_STRING_TOOLS
#define CUBESAT_STRING_TOOLS

#include <string>
#include "math/vector.h"
#include "Types.h"


namespace cubesat {
	
	
	struct CapturedInput {
		std::string input;
		
		CapturedInput(const std::string &input) : input(input) {
			
		}
		CapturedInput(const std::vector<std::string> &input) {
			for (int i = 0; i < (int)input.size(); ++i) {
				this->input += input[i];
				if ( i != (int)input.size() - 1 )
					this->input += " ";
			}
		}
		
		inline operator std::string() {
			return input;
		}
	};
	
	
	
	namespace detail {
		
		template <typename T>
		struct StringConverter {
			using SupportFlag = bool;
		};
		
		template <>
		struct StringConverter<void> {
			inline static std::string ToString(bool &conversion_flag) {
				conversion_flag = true;
				return "";
			}
			inline static void FromString(const std::string &str, bool &conversion_flag) {
				conversion_flag = true;
			}
			inline static std::string TypeName() {
				return "void";
			}
		};
		
		template <>
		struct StringConverter<std::string> {
			inline static std::string ToString(const std::string &value, bool &conversion_flag) {
				conversion_flag = true;
				return value;
			}
			inline static std::string FromString(const std::string &str, bool &conversion_flag) {
				conversion_flag = true;
				return str;
			}
			inline static std::string TypeName() {
				return "std::string";
			}
		};
		
		template <>
		struct StringConverter<const char *> {
			inline static std::string ToString(const char *value, bool &conversion_flag) {
				conversion_flag = true;
				return value;
			}
			inline static const char* FromString(const std::string &str, bool &conversion_flag) {
				return str.c_str(); // Hmm...
			}
			inline static std::string TypeName() {
				return "const char*";
			}
		};
		
		template <>
		struct StringConverter<bool> {
			inline static std::string ToString(bool value, bool &conversion_flag) {
				conversion_flag = true;
				return value ? "true" : "false";
			}
			inline static bool FromString(const std::string &str, bool &conversion_flag) {
				if ( str == "true" || str == "1" ) {
					conversion_flag = true;
					return true;
				}
				else if ( str == "false" || str == "0" ) {
					conversion_flag = true;
					return false;
				}
				
				conversion_flag = false;
				return false;
			}
			inline static std::string TypeName() {
				return "bool";
			}
		};
		
		template <>
		struct StringConverter<char> {
			inline static std::string ToString(char value, bool &conversion_flag) {
				conversion_flag = true;
				return std::string(1, value);
			}
			inline static char FromString(const std::string &str, bool &conversion_flag) {
				if ( str.length() == 1) {
					conversion_flag = true;
					return str[0];
				}
				else {
					conversion_flag = false;
					return 0;
				}
			}
			inline static std::string TypeName() {
				return "char";
			}
		};
		
		template <>
		struct StringConverter<int> {
			inline static std::string ToString(int value, bool &conversion_flag) {
				conversion_flag = true;
				return std::to_string(value);
			}
			inline static int FromString(const std::string &str, bool &conversion_flag) {
				char *p;
				long value = strtol(str.c_str(), &p, 10);
				conversion_flag = (p != NULL);
				return value;
			}
			inline static std::string TypeName() {
				return "int";
			}
		};
		
		template <>
		struct StringConverter<unsigned int> {
			inline static std::string ToString(unsigned int value, bool &conversion_flag) {
				conversion_flag = true;
				return std::to_string(value);
			}
			inline static unsigned int FromString(const std::string &str, bool &conversion_flag) {
				char *p;
				long value = strtol(str.c_str(), &p, 10);
				conversion_flag = (p != NULL);
				return (unsigned int) value;
			}
			inline static std::string TypeName() {
				return "unsigned int";
			}
		};
		
		template <>
		struct StringConverter<long> {
			inline static std::string ToString(long value, bool &conversion_flag) {
				conversion_flag = true;
				return std::to_string(value);
			}
			inline static long FromString(const std::string &str, bool &conversion_flag) {
				char *p;
				long value = strtol(str.c_str(), &p, 10);
				conversion_flag = (p != NULL);
				return value;
			}
			inline static std::string TypeName() {
				return "long";
			}
		};
		
		template <>
		struct StringConverter<unsigned long> {
			inline static std::string ToString(unsigned long value, bool &conversion_flag) {
				conversion_flag = true;
				return std::to_string(value);
			}
			inline static unsigned long FromString(const std::string &str, bool &conversion_flag) {
				char *p;
				long value = strtol(str.c_str(), &p, 10);
				conversion_flag = (p != NULL);
				return (unsigned long)value;
			}
			inline static std::string TypeName() {
				return "unsigned long";
			}
		};
		
		template <>
		struct StringConverter<float> {
			inline static std::string ToString(float value, bool &conversion_flag) {
				conversion_flag = true;
				return std::to_string(value);
			}
			inline static float FromString(const std::string &str, bool &conversion_flag) {
				char *p;
				float value = (float)strtod(str.c_str(), &p);
				conversion_flag = (p != NULL);
				
				return value;
			}
			inline static std::string TypeName() {
				return "float";
			}
		};
		
		template <>
		struct StringConverter<double> {
			inline static std::string ToString(double value, bool &conversion_flag) {
				conversion_flag = true;
				return std::to_string(value);
			}
			inline static double FromString(const std::string &str, bool &conversion_flag) {
				char *p;
				double value = strtod(str.c_str(), &p);
				conversion_flag = (p != NULL);
				
				return value;
			}
			inline static std::string TypeName() {
				return "double";
			}
		};
		
		template <>
		struct StringConverter<rvector> {
			inline static std::string ToString(rvector value, bool &conversion_flag) {
				conversion_flag = true;
				return "[" + std::to_string(value.col[0]) + ","
						+ std::to_string(value.col[1]) + ","
						+ std::to_string(value.col[2]) + "]";
			}
			inline static rvector FromString(const std::string &str, bool &conversion_flag) {
				
				rvector vec;
				int s = sscanf(str.c_str(), "[%lf,%lf,%lf]", &vec.col[0], &vec.col[1], &vec.col[2]);
				conversion_flag = (s == 3);
				return vec;
			}
			inline static std::string TypeName() {
				return "rvector";
			}
		};
		
		template <>
		struct StringConverter<Vec3> {
			inline static std::string ToString(Vec3 value, bool &conversion_flag) {
				conversion_flag = true;
				return "[" + std::to_string(value.x) + ","
						+ std::to_string(value.y) + ","
						+ std::to_string(value.z) + "]";
			}
			inline static Vec3 FromString(const std::string &str, bool &conversion_flag) {
				Vec3 vec;
				int s = sscanf(str.c_str(), "[%lf,%lf,%lf]", &vec.x, &vec.y, &vec.z);
				conversion_flag = (s == 3);
				return vec;
			}
			inline static std::string TypeName() {
				return "Vec3";
			}
		};
		
		template <>
		struct StringConverter<gvector> {
			inline static std::string ToString(gvector value, bool &conversion_flag) {
				conversion_flag = true;
				return "[" + std::to_string(value.lat) + ","
						+ std::to_string(value.lon) + ","
						+ std::to_string(value.h) + "]";
			}
			inline static gvector FromString(const std::string &str, bool &conversion_flag) {
				gvector vec;
				int s = sscanf(str.c_str(), "[%lf,%lf,%lf]", &vec.lat, &vec.lon, &vec.h);
				conversion_flag = (s == 3);
				return vec;
			}
			inline static std::string TypeName() {
				return "gvector";
			}
		};
		
		template <>
		struct StringConverter<Location> {
			inline static std::string ToString(Location value, bool &conversion_flag) {
				conversion_flag = true;
				return "[" + std::to_string(value.latitude) + ","
						+ std::to_string(value.longitude) + ","
						+ std::to_string(value.altitude) + "]";
			}
			inline static Location FromString(const std::string &str, bool &conversion_flag) {
				Location vec;
				int s = sscanf(str.c_str(), "[%lf,%lf,%lf]",
					   &vec.latitude, &vec.longitude, &vec.altitude);
				conversion_flag = (s == 3);
				return vec;
			}
			inline static std::string TypeName() {
				return "Vec3";
			}
		};
		
		template <>
		struct StringConverter<CapturedInput> {
			inline static std::string ToString(const CapturedInput &value, bool &conversion_flag) {
				conversion_flag = true;
				return value.input;
			}
			inline static CapturedInput FromString(const std::string &str, bool &conversion_flag) {
				conversion_flag = true;
				return str;
			}
			inline static std::string TypeName() {
				return "CapturedInput";
			}
		};
		
		
		
		template <typename T>
		class StringConversionSupported {
		private:
			typedef char YesType[1];
			typedef char NoType[2];
		
			template <typename C> static YesType& test( decltype(&StringConverter<C>::ToString) ) ;
			template <typename C> static NoType& test(...);
			
		public:
			enum { value = sizeof(test<T>(0)) == sizeof(YesType) };
		};
		
	}
	
	template <typename T>
	inline std::string ToString(T value) {
		static_assert(detail::StringConversionSupported<T>::value,
				"String conversion to this type is not supported");
		
		bool conversion_flag;
		return detail::StringConverter<T>::ToString(value, conversion_flag);
	}
	
	template <typename T>
	inline std::string ToString(T value, bool &conversion_flag) {
		static_assert(detail::StringConversionSupported<T>::value,
				"String conversion to this type is not supported");
		
		return detail::StringConverter<T>::ToString(value, conversion_flag);
	}
	
	template <typename T>
	inline T FromString(const std::string &str) {
		static_assert(detail::StringConversionSupported<T>::value,
				"String conversion from this type is not supported");
		
		bool conversion_flag;
		return detail::StringConverter<T>::FromString(str, conversion_flag);
	}
	
	
	template <typename T>
	inline T FromString(const std::string &str, bool &conversion_flag) {
		static_assert(detail::StringConversionSupported<T>::value,
				"String conversion from this type is not supported");
		
		return detail::StringConverter<T>::FromString(str, conversion_flag);
	}
	
	template <typename T>
	inline std::string TypeName() {
		return detail::StringConverter<T>::TypeName();
	}
	
	
	
	
	
	
	inline std::string ToLowercase(std::string input) {
		for (size_t i = 0; i < input.length(); ++i)
			input[i] = tolower(input[i]);
		
		return input;
	}
	inline std::string ToUppercase(std::string input) {
		for (size_t i = 0; i < input.length(); ++i)
			input[i] = toupper(input[i]);
		
		return input;
	}
	inline std::string& ToLowercaseInPlace(std::string &input) {
		for (size_t i = 0; i < input.length(); ++i)
			input[i] = tolower(input[i]);
		
		return input;
	}
	inline std::string& ToUppercaseInPlace(std::string &input) {
		for (size_t i = 0; i < input.length(); ++i)
			input[i] = toupper(input[i]);
		
		return input;
	}
	inline bool CompareAndIgnoreCase(const std::string &first, const std::string &second) {
		// First compare their lengths
		if ( first.length() != second.length() )
			return false;
		
		// Check each character and ignore case
		for (size_t i = 0; i < first.length(); ++i) {
			if ( tolower(first[i]) != tolower(second[i]) )
				return false;
		}
		
		// Yup, they're the same
		return true;
	}
	
	
	
}

#endif
