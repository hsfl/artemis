import time

from pycubed import cubesat
import adafruit_gps, time
import time,board, digitalio, busio

if not cubesat.hardware['IMU']:
	print('[Error] No IMU found onboard')
	exit(1)


# Test resolution (samples per second)
resolution = 10

# Where to store the output file
output_file = '/sd/adcs_test.csv'

# Start time of the test
start_time = time.monotonic()

print('=' * 40)
print('Testing GPS & IMU with ' + str(resolution) + ' samples per second')
print('Writing output to file ' + output_file)
print('Columns: ', end='', flush=True)

print('timestamp')
print('accel-x')
print('accel-y')
print('accel-z')
print('mag-x')
print('mag-y')
print('mag-z')
print('gyro-x')
print('gyro-y')
print('gyro-z')


print('utc-month')
print('utc-day_of_month')
print('utc-year')
print('utc-hour')
print('utc-min')
print('utc-sec')
print('latitude')
print('longitude')
print('fix_quality')

if gps.satellites is not None:
	print('satellite-count')
if gps.altitude_m is not None:
	print('altitude')
if gps.speed_knots is not None:
	print('speed')
if gps.track_angle_deg is not None:
	print('track_angle')
if gps.horizontal_dilution is not None:
	print('horizontal_dilution')
if gps.height_geoid is not None:
	print('height_geoid')



	

print('=' * 40)
print('Power to GPS on')
cubesat.en_gps.value = True
time.sleep(2)
print('Booting GPS')

# Create a GPS module instance.
gps = adafruit_gps.GPS(cubesat.uart, debug=False) # Enable debugging to see raw GPS output

print('=' * 40)
print('IMU Configuration')
print('Sensor resolution: ' + str(cubesat.IMU.sensortime))
print('Gyro range: ' + str(cubesat.IMU.gyro_range))
print('Gyro ODR: ' + str(cubesat.IMU.gyro_odr))
print('Gyro power mode: ' + str(cubesat.IMU.gyro_powermode))
print('Accelerometer range: ' + str(cubesat.IMU.accel_range))
print('Accelerometer ODR: ' + str(cubesat.IMU.accel_odr))
print('Accelerometer power mode: ' + str(cubesat.IMU.accel_powermode))
print('=' * 40)


for i in range(10):
	
	# Get readings
	temp = imu.GetTemp()
	accel = imu.GetAccel()
	mag = imu.GetMag()
	omega = imu.GetOmega()
	
	
	
	
	# Print readings
	print('=' * 40)
	print('Temperature: {0: .6f} C'.format(temp))
	print('Acceleration: ({0: .6f}, {1: .6f}, {2: .6f})'.format(accel[0], accel[1], accel[2]))
	print('Magnetic Field: ({0: .6f}, {1: .6f}, {2: .6f})'.format(mag[0], mag[1], mag[2]))
	print('Angular Velocity: ({0: .6f}, {1: .6f}, {2: .6f})'.format(omega[0], omega[1], omega[2]))
	
	
	# Write output to file
	with open(output_file, "a") as f:
		
		# Sample timestamp (seconds)
		f.write(str(time.monotonic() - start_time) + ',');
		
		# Acceleration
		f.write(str(accel[0]) + ',')
		f.write(str(accel[1]) + ',')
		f.write(str(accel[2]) + ',')
		
		# Magnetic Field
		f.write(str(mag[0]) + ',')
		f.write(str(mag[1]) + ',')
		f.write(str(mag[2]) + ',')
		
		# Gyroscope
		f.write(str(omega[0]) + ',')
		f.write(str(omega[1]) + ',')
		f.write(str(omega[2]) + ',')
		
		# GPS fix timestamp
		f.write('{},{},{},{:02},{:02},{:02},'.format(
			gps.timestamp_utc.tm_mon,   # Grab parts of the time from the
            gps.timestamp_utc.tm_mday,  # struct_time object that holds
            gps.timestamp_utc.tm_year,  # the fix time.  Note you might
            gps.timestamp_utc.tm_hour,  # not get all data like year, day,
            gps.timestamp_utc.tm_min,   # month!
            gps.timestamp_utc.tm_sec))
		
		# GPS Latitude
		f.write(str(gps.latitude) + ',')
		
		# GPS Longitude
		f.write(str(gps.longitude) + ',')
		
		# Fix quality
		f.write(str(gps.fix_quality))
		
		# Other GPS info
		if gps.satellites is not None:
            f.write(',' + str(gps.satellites))
        if gps.altitude_m is not None:
            f.write(',' + str(gps.altitude_m))
        if gps.speed_knots is not None:
            f.write(',' + str(gps.speed_knots))
        if gps.track_angle_deg is not None:
            f.write(',' + str(gps.track_angle_deg))
        if gps.horizontal_dilution is not None:
            f.write(',' + str(gps.horizontal_dilution))
        if gps.height_geoid is not None:
            f.write(',' + str(gps.height_geoid))
			
		f.write('\n')
	
	# Sleep for a bit
	time.sleep(1 / resolution)

print('=' * 40)
print('Test finished')