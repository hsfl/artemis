

class Heater:

    def __init__(self, cubesat):
        self.cubesat = cubesat
        self._enabled = False
        self._utc = 0
        pass

    def load_json(self, data_json):
        """Loads the agent_raspi data JSON"""
        
        self._enabled = data_json['output']['agent_heater']['enabled']

    @property
    def utc(self):
        return self._utc

    @property
    def enabled(self):
        return self._enabled

    @enabled.setter
    def enabled(self, value):
        
        # Check if the heater should be enabled/disabled
        if value:
            
            self.cubesat.agent_heater.request("enable")
        else:
            self.cubesat.agent_heater.request("disable")
        
        self._enabled = value


