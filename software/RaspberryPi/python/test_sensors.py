
from artemis import cubesat
from time import sleep

# Main loop
while True:
    # Update the artemis
    cubesat.update()
    
    print('=' * 40)
    
    # Print IMU info
    magnetic = cubesat.imu.magnetic
    acceleration = cubesat.imu.acceleration
    gyro = cubesat.imu.gyro
    utc = cubesat.imu.utc

    print('IMU')
    print('\t| Timestamp: %d' % utc)
    print('\t| Magnetic: (%d, %d, %d)' % (magnetic[0], magnetic[1], magnetic[2]))
    print('\t| Acceleration: (%d, %d, %d)' % (acceleration[0], acceleration[1], acceleration[2]))
    print('\t| Gyro: (%d, %d, %d)' % (gyro[0], gyro[1], gyro[2]))
    
    # Print temperature sensor info
    print('Temperature')
    for tempsensor in cubesat.tempsensor:
        print('\t| Sensor "%s"' % tempsensor.name)
        print('\t|\t| Timestamp: %d' % tempsensor.utc)
        print('\t|\t| Temperature: %d' % tempsensor.temp)
        
    # Print sun sensor info
    print('Illumination')
    for sunsensor in cubesat.sunsensor:
        print('\t| Sensor "%s"' % sunsensor.name)
        print('\t|\t| Timestamp: %d' % sunsensor.utc)
        print('\t|\t| Lux: %d' % sunsensor.lux)
    
    # Print heater info
    print('Heater')
    print('\t| Timestamp: %d' % cubesat.heater.utc)
    print('\t| Enabled: %r' % cubesat.heater.enabled)
    
    # Wait for a few seconds
    sleep(3)







