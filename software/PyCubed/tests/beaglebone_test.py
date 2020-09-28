from artemis import beaglebone
import microcontroller
import time

# Initialize a BeagleBone object on pins PB16/PB17
# for UART TX/RX respectively
tx_pin = microcontroller.pin.PB16
rx_pin = microcontroller.pin.PB17
bb = beaglebone.BeagleBone(tx_pin, rx_pin)


while True:
    bb.update()
    time.sleep(1)
    


    
    
    
    