


class TempSensor:

    def __init__(self, sensor_name):
        self._sensor_name = sensor_name
        self._temp = 0
        self._utc = 0
        pass
    
    def load_json(self, data_json):
        """Loads the agent_raspi data JSON"""
        
        self.temp = data_json['output']['agent_temp'][self.name]
    
    @property
    def name(self):
        return self._sensor_name
    
    @property
    def utc(self):
        return self._utc
        
    @property
    def temp(self):
        return self._temp

    @temp.setter
    def temp(self, value):
        self._temp = value




