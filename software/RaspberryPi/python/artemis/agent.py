import subprocess
import json
from .log import log_file

BEAGLEBONE_HOST_NAME = 'debian@192.168.6.2'


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


class Agent:

    def __init__(self, name, node='cubesat'):
        self._name = name
        self._node = node
        self._active = False
        self._soh_str = "{}"
        self._soh_dict = {}

    def request(self, request_str):
        """Sends an agent request to the BeagleBone and returns the result string."""
        log_file.message('Agent', 'Sending request to agent_' + self.name + ': ' + request_str + '...')
        output = subprocess.check_output("ssh %s /home/debian/cosmos/bin/agent %s %s %s" % (BEAGLEBONE_HOST_NAME, self.node, self.name, request_str), shell=True)
        log_file.message('Agent', 'Got response: ' + output)
        return output
    
    def _set_soh_string(self, soh_str):

        data_json = None
        try:
            data_json = _byteify(json.loads(soh_str))
        except ValueError as e:
            print('Could not parse JSON from agent_raspi')
            return False

        # Check if the request was completed successfully
        if data_json['status'] != 'OK':
            return False
        else:
            self._soh_str = soh_str
            self._soh_dict = data_json['output']
            return True
        
        
        
    @property
    def soh(self):
        """Returns the latest SOH as a dictionary for the given agent"""
        return self._soh_dict
    
    @property
    def name(self):
        return self._name
    
    @property
    def node(self):
        return self._node

    @property
    def active(self):
        return self._active
    
    @active.setter
    def active(self, value):
        self._active = value
