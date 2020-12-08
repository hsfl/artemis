
#ifndef CUBESAT_TYPES
#define CUBESAT_TYPES

#include "agent/agentclass.h"
#include "support/configCosmos.h"
#include "agent/agentclass.h"
#include "support/jsonlib.h"
#include "support/jsonclass.h"

#include <unordered_map>
#include <cmath>

namespace cubesat {
	
	
	
	
	
	struct Vec3 {
		double x, y, z;
		
		Vec3() : x(0), y(0), z(0) {}
		Vec3(double x, double y, double z) : x(x), y(y), z(z) {}
		Vec3(const rvector &vec) : x(vec.col[0]), y(vec.col[1]), z(vec.col[2]) {}
		
		inline double Dot(const Vec3 &other) const {
			return x * other.x + y * other.y + z * other.z;
		}
		//! Vector cross product
		inline Vec3 Cross(const Vec3 &other) {
			return Vec3(y * other.z - z * other.y,
						z * other.x - x * other.z,
						x * other.y - y * other.x);
		}
		//! Vector magnitude
		inline double Length() const {
			return Magnitude();
		}
		//! Vector magnitude
		inline double Magnitude() const {
			return sqrt(x * x + y * y + z * z);
		}
		
		//! Conversion to string
		inline std::string ToString() const {
			return "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "]";
		}
		
		//! Conversion operator for rvector
		inline operator rvector() const {
			rvector value;
			value.col[0] = x;
			value.col[1] = y;
			value.col[2] = z;
			return value;
		}
		
		//! Conversion operator to string
		inline operator std::string() const {
			return ToString();
		}
		
		//! Vector addition operator
		inline Vec3 operator +(const Vec3 &other) const {
			return Vec3(x + other.x, y + other.y, z + other.z);
		}
		//! Vector subtraction operator
		inline Vec3 operator -(const Vec3 &other) const {
			return Vec3(x - other.x, y - other.y, z - other.z);
		}
		//! Scalar multiplication operator
		inline Vec3 operator *(double scalar) const {
			return Vec3(x * scalar, y * scalar, z * scalar);
		}
		//! Scalar division operator
		inline Vec3 operator /(double scalar) const {
			if ( scalar == 0.0 )
				return Vec3();
			else
				return Vec3(x / scalar, y / scalar, z / scalar);
		}
		//! Vector addition assignment operator
		inline Vec3& operator +=(const Vec3 &other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		//! Vector subtraction assignment operator
		inline Vec3& operator -(const Vec3 &other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		//! Scalar multiplication assignment operator
		inline Vec3& operator *=(double scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}
		//! Scalar division assignment operator
		inline Vec3& operator /=(double scalar) {
			if ( scalar == 0.0 ) {
				x = y = z = 0.0;
			}
			else {
				x /= scalar;
				y /= scalar;
				z /= scalar;
			}
			
			return *this;
		}
		//! Vector dot product operator
		inline double operator *(const Vec3 &other) const {
			return Dot(other);
		}
		//! Vector magnitude operator
		inline double operator ~() const {
			return Magnitude();
		}
		
		inline bool operator ==(const Vec3 &other) const {
			return x == other.x && y == other.y && z == other.z;
		}
		inline bool operator !=(const Vec3 &other) const {
			return x != other.x || y != other.y || z != other.z;
		}
		inline double operator [](size_t index) const {
			switch ( index ) {
				case 0:
					return x;
				case 1:
					return y;
				case 2:
					return z;
				default:
					throw std::out_of_range("Index " + std::to_string(index) + " is out of range");
			}
		}
	};
	
	struct Location {
		double latitude;
		double longitude;
		double altitude;
		
		Location() : latitude(0), longitude(0), altitude(0) {}
		Location(double latitude, double longitude, double altitude)
			: latitude(latitude), longitude(longitude), altitude(altitude) {}
		Location(const gvector &vec) : latitude(vec.lat), longitude(vec.lon), altitude(vec.h) {}
		
		operator gvector() const {
			gvector value;
			value.lat = latitude;
			value.lon = longitude;
			value.h = altitude;
			return value;
		}
		
		//! Conversion to string
		inline std::string ToString() const {
			return "[" + std::to_string(latitude) + "," + std::to_string(longitude) + "," + std::to_string(altitude) + "]";
		}
		
		inline operator std::string() const {
			return ToString();
		}
	};
	
}


#endif
