from collections import namedtuple

import json
import signal
from .agent import Agent
from .sunsensor import SunSensor
from .gps import GPS
from .heater import Heater
from .imu import IMU
from .beaglebone import BeagleBone
from .tempsensor import TempSensor
from .log import log_file

# COSMOS Constants
COSMOS_NODE_NAME = 'cubesat'
COSMOS_AGENT_TEMPSENSOR_NAME = 'temp'
COSMOS_AGENT_SUNSENSOR_NAME = 'sunsensor'
COSMOS_AGENT_HEATER_NAME = 'heater'
COSMOS_AGENT_PYCUBED_NAME = 'pycubed'
COSMOS_AGENT_RASPI_NAME = 'raspi'
COSMOS_AGENT_SWITCH_NAME = 'switch'


_SunSensorTuple = namedtuple('_SunSensorTuple', ['plusx', 'minusx', 'plusy', 'minusy', 'plusz', 'minusz'])
_TempSensorTuple = namedtuple('_TempSensorTuple', ['eps', 'obc', 'payload', 'battery', 'pycubed'])

def _byteify(dictionary):
    """Used to convert the dictionary produced by json.loads() to ASCII instead of Unicode"""
    if isinstance(dictionary, dict):
        return {_byteify(key): _byteify(value)
                for key, value in dictionary.iteritems()}
    elif isinstance(dictionary, list):
        return [_byteify(element) for element in dictionary]
    elif isinstance(dictionary, unicode):
        return dictionary.encode('utf-8')
    else:
        return dictionary
    

def shutdown_hook(sig, frame):
    cubesat.__shutdown_signal()

class CubeSat:
    """The main class for interacting with the CubeSat Kit"""
    def __init__(self):
        
        log_file.message('CubeSat', 'Initializing CubeSat module')
        
        # Set up components
        log_file.message('CubeSat', 'Adding components')
        self._beaglebone = BeagleBone()
        self._imu = IMU()
        self._gps = GPS()
        self._heater = Heater(self)
        self._sunsensor = _SunSensorTuple(plusx=SunSensor('ss_plusx'),
                                          minusx=SunSensor('ss_minusx'),
                                          plusy=SunSensor('ss_plusx'),
                                          minusy=SunSensor('ss_minusx'),
                                          plusz=SunSensor('ss_plusx'),
                                          minusz=SunSensor('ss_minusx'))
        self._tempsensor = _TempSensorTuple(eps=TempSensor('temp_eps'),
                                            obc=TempSensor('temp_obc'),
                                            payload=TempSensor('temp_raspi'),
                                            battery=TempSensor('temp_battery'),
                                            pycubed=TempSensor('temp_pycubed'))

        # Create Agent objects
        log_file.message('CubeSat', 'Adding agents')
        self.agent_temp = Agent(COSMOS_AGENT_TEMPSENSOR_NAME, COSMOS_NODE_NAME)
        self.agent_sunsensor = Agent(COSMOS_AGENT_SUNSENSOR_NAME, COSMOS_NODE_NAME)
        self.agent_heater = Agent(COSMOS_AGENT_HEATER_NAME, COSMOS_NODE_NAME)
        self.agent_pycubed = Agent(COSMOS_AGENT_PYCUBED_NAME, COSMOS_NODE_NAME)
        self.agent_raspi = Agent(COSMOS_AGENT_RASPI_NAME, COSMOS_NODE_NAME)
        self.agent_switch = Agent(COSMOS_AGENT_SWITCH_NAME, COSMOS_NODE_NAME)
        
        # Setup shutdown handlers
        log_file.message('CubeSat', 'Adding shutdown hook')
        self.__shutdown_callback = None
        signal.signal(signal.SIGTERM, shutdown_hook)
        
        log_file.message('CubeSat', 'Finished setting up CubeSat')
        
    def __shutdown_signal(self):
        # Call the shutdown callback function
        if self.__shutdown_callback:
            log_file.message('CubeSat', 'Received shutdown signal')
            self.__shutdown_callback()
        else:
            log_file.warning('CubeSat', 'Received shutdown signal, but no callback is set')
    
    def update(self):
        """Updates the CubeSat with the latest information"""
        
        log_file.message('CubeSat', 'Updating...')
        
        # Update the BeagleBone
        log_file.message('CubeSat', 'Updating the BeagleBone')
        self.beaglebone.update()
        
        # Get a JSON string from agent_raspi holding agent SOH info
        log_file.message('CubeSat', 'Fetching data from agent_raspi')
        data_str_pycubed = self.agent_pycubed.request('soh')
        data_str_sun = self.agent_sun.request('list')
        data_str_switch = self.agent_switch.request('list')
        data_str_temp = self.agent_temp.request('list')

        # Convert the JSON string into a dictionary        
        data_json_pycubed = []
        try:
            data_json_pycubed = _byteify(json.loads(data_str_pycubed))
        except ValueError as e:
            print('Could not parse JSON from agent_pycubed')
            log_file.error('CubeSat', 'Failed to parse data from agent_pycubed')
            return False
        
        data_json_sun = {}
        try:
            data_json_sun = _byteify(json.loads(data_str_sun))
        except ValueError as e:
            print('Could not parse JSON from agent_sun')
            log_file.error('CubeSat', 'Failed to parse data from agent_sun')
            return False
        
        data_json_switch = []
        try:
            data_json_switch = _byteify(json.loads(data_str_switch))
        except ValueError as e:
            print('Could not parse JSON from agent_switch')
            log_file.error('CubeSat', 'Failed to parse data from agent_switch')
            return False

        data_json_temp = []
        try:
            data_json_temp = _byteify(json.loads(data_str_temp))
        except ValueError as e:
            print('Could not parse JSON from agent_temp')
            log_file.error('CubeSat', 'Failed to parse data from agent_temp')
            return False

        # Check if the request was completed successfully
        if not ('status' in data_json_pycubed) or data_json_pycubed['status'] != 'OK':
            print('Data from agent_pycubed is invalid or corrupted')
            log_file.error('CubeSat', 'Data from agent_pycubed is invalid or corrupted')
            return False
        if not ('status' in data_json_sun) or data_json_sun['status'] != 'OK':
            print('Data from agent_sun is invalid or corrupted')
            log_file.error('CubeSat', 'Data from agent_sun is invalid or corrupted')
            return False
        if not ('status' in data_json_switch) or data_json_switch['status'] != 'OK':
            print('Data from agent_switch is invalid or corrupted')
            log_file.error('CubeSat', 'Data from agent_switch is invalid or corrupted')
            return False
        if not ('status' in data_json_temp) or data_json_temp['status'] != 'OK':
            print('Data from agent_temp is invalid or corrupted')
            log_file.error('CubeSat', 'Data from agent_temp is invalid or corrupted')
            return False


        # Update agent states
        log_file.message('CubeSat', 'Updating agent_temp')
        self.agent_temp.active = data_json_temp['output']['agent_temp']['active']

        log_file.message('CubeSat', 'Updating agent_pycubed')
        self.agent_pycubed.active = data_json_pycubed['output']['agent_pycubed']['active']

        log_file.message('CubeSat', 'Updating agent_sun')
        self.agent_sun.active = data_json_sun['output']['agent_sun']['active']

        log_file.message('CubeSat', 'Updating agent_switch')
        self.agent_switch.active = data_json_switch['output']['agent_switch']['active']
        
        # Update IMU
        log_file.message('CubeSat', 'Updating IMU values')
        self.imu.load_json(data_json_pycubed)
        
        # Update GPS
        log_file.message('CubeSat', 'Updating GPS values')
        self.gps.load_json(data_json_pycubed)
        
    
        # Update temperature sensors
        log_file.message('CubeSat', 'Updating temperature sensor values')
        self.tempsensor.eps.load_json(data_json_temp)
        self.tempsensor.obc.load_json(data_json_temp)
        self.tempsensor.payload.load_json(data_json_temp)
        self.tempsensor.battery.load_json(data_json_temp)
        self.tempsensor.pycubed.load_json(data_json_temp)
    
        # Update sun sensors
        log_file.message('CubeSat', 'Updating sun sensor values')
        self.sunsensor.plusx.load_json(data_json_sun)
        self.sunsensor.minusx.load_json(data_json_sun)
        self.sunsensor.plusy.load_json(data_json_sun)
        self.sunsensor.minusy.load_json(data_json_sun)
        self.sunsensor.plusz.load_json(data_json_sun)
        self.sunsensor.minusz.load_json(data_json_sun)
    
        # Update heater
        log_file.message('CubeSat', 'Updating heater values')
        self.heater.load_json(data_json_switch)

        log_file.message('CubeSat', 'Finished updating CubeSat')


        # Transmit files in the outgoing folder
        
        
    def transmit_file(self, source_file, outgoing_file_name = None):
        """Uses rsync to copy the given file to the BeagleBone, marking it for radio transmission.
                'outgoing_file_name' is the name ONLY of the destination file."""
        log_file.message('CubeSat', 'Transmitting file ' + source_file)
        return self.beaglebone.transmit_file(source_file, outgoing_file_name)
    
    def set_soh(self):
        """Sets the State of Health string for your payload"""
        log_file.message('CubeSat', 'Set SOH string')
        pass
    
    def set_shutdown_callback(self):
        """Adds a shutdown callback function. This function
        is called when the Raspberry Pi is shutting down"""
        log_file.message('CubeSat', 'Set shutdown callback')
        self.__shutdown_callback = self
    
    @property
    def beaglebone(self):
        return self._beaglebone

    @property
    def imu(self):
        return self._imu

    @property
    def gps(self):
        return self._gps

    @property
    def tempsensor(self):
        return self._tempsensor
    
    @property
    def sunsensor(self):
        return self._sunsensor
    
    @property
    def heater(self):
        return self._heater



cubesat = CubeSat()
