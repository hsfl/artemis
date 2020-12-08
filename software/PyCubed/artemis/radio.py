

from pycubed import cubesat as pycubed_cubesat


class Radio:
	
	def __init__(self):
		self.radio = pycubed_cubesat.radio1
		self.radio.tx_power = 23
		self.radio.frequency_mhz = 431
        
        
	
	def send(self, data):
		"""Transmits the given data"""
		self.radio.send(data)
		
	def receive(self):
		return self.radio.receive()
	
	def kill(self):
		pass  # TODO


radio = Radio()


