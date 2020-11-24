

class IMU:

    def __init__(self):
        self._magnetic = (0, 0, 0)
        self._acceleration = (0, 0, 0)
        self._gyro = (0, 0, 0)
        self._utc = 0
        pass

    def load_json(self, data_json):
        """Loads the agent_raspi data JSON"""
        imu_data = data_json['output']['agent_pycubed']['imu']
        mag = imu_data['mag']
        accel = imu_data['accel']
        gyro = imu_data['gyro']
        
        self.magnetic = (mag[0], mag[1], mag[2])
        self.acceleration = (accel[0], accel[1], accel[2])
        self.gyro = (gyro[0], gyro[1], gyro[2])
    
    @property
    def utc(self):
        return self.utc

    @property
    def magnetic(self):
        return self._magnetic

    @magnetic.setter
    def magnetic(self, value):
        self._magnetic = value

    @property
    def acceleration(self):
        return self._acceleration

    @acceleration.setter
    def acceleration(self, value):
        self._acceleration = value

    @property
    def gyro(self):
        return self._gyro

    @gyro.setter
    def gyro(self, value):
        self._gyro = value


