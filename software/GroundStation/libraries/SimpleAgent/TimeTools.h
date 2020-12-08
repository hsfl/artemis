
#ifndef CUBESAT_TIME_TOOLS
#define CUBESAT_TIME_TOOLS


#include "support/timelib.h"


namespace cubesat {
	
	class Time {
	public:
		
		Time() : utc_mjd(currentmjd()) {
			
		}
		Time(double utc_mjd) : utc_mjd(utc_mjd) {
			
		}
		
		inline static Time Now() {
			return Time();
		}
		
		/**
		 * @brief Converts this time to a year, month, and day
		 * @param year The year
		 * @param month The month of the year
		 * @param day The day of the month (fractional)
		 */
		inline void GetYMD(int32_t &year, int32_t &month, double &day) {
			mjd2ymd(utc_mjd, year, month, day);
		}
		
		//! Returns this time as an ISO 8601 formatted string
		inline std::string ToString() const {
			return mjd2iso8601(utc_mjd);
		}
		
		//! Converts this time to seconds
		inline double Seconds() const {
			return utc2unixseconds(utc_mjd);
		}
		//! Converts this time to minutes
		inline double Minutes() const {
			return Seconds() / 60.0;
		}
		//! Converts this time to hours
		inline double Hours() const {
			return Seconds() / 3600.0;
		}
		//! Converts this time to days
		inline double Days() const {
			return Seconds() / 86400.0;
		}
		
		//! Returns the modified Julian day (UTC)
		inline double GetModifiedJulianDay() const {
			return utc_mjd;
		}
		
		//! Returns the modified Julian date (UTC)
		inline operator double() const {
			return utc_mjd;
		}
		
		//! Returns this time as an ISO 8601 formatted string
		inline operator std::string() const {
			return ToString();
		}
		
		inline bool operator ==(const Time &other) const {
			return utc_mjd == other.utc_mjd;
		}
		
		inline bool operator >(const Time &other) const {
			return utc_mjd > other.utc_mjd;
		}
		inline bool operator >=(const Time &other) const {
			return utc_mjd >= other.utc_mjd;
		}
		
		inline bool operator <(const Time &other) const {
			return utc_mjd < other.utc_mjd;
		}
		inline bool operator <=(const Time &other) const {
			return utc_mjd <= other.utc_mjd;
		}
		
		
		inline static void Sleep(double seconds) {
			COSMOS_SLEEP(seconds);
		}
		
	private:
		double utc_mjd;
	};
	
	
	class Timer {
	public:
		//! Starts the timer
		inline void Start() {
			start_time = Time::Now();
		}
		
		//! Returns the duration between when Timer::Start() was called,
		//! and when this function was called
		inline double Seconds() {
			return Time::Now().Seconds() - start_time.Seconds();
		}
		
	private:
		Time start_time;
	};
	
	
}

#endif
