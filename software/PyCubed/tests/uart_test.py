from artemis import beaglebone
import microcontroller
import time
import board
import busio
import digitalio

# Initialize a BeagleBone object on pins PB16/PB17
# for UART TX/RX respectively
tx_pin = microcontroller.pin.PB16
rx_pin = microcontroller.pin.PB17
uart = busio.UART(tx_pin, rx_pin)


while True:
		if uart.in_waiting: # check if there's anything in uart buffer
			data = uart.read(32) # read at most 32 bytes

			# data is a bytearray, we'll want to convert it to a string
			data_string = ''.join([chr(b) for b in data])
			print(data_string)
		time.sleep(0.1)
