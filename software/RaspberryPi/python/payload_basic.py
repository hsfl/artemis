from time import sleep
from picamera import PiCamera
from artemis import cubesat

camera = PiCamera() # Provides control of the camera
image_count = 0  # The number of images written

while True:
    cubesat.update() # Update the CubeSat (important!!!)

    # Pick the destination file on the Raspberry Pi
    image_file = '/home/pi/payload_files/image_%d.jpeg' % image_count
    image_count += 1
    
    # Capture the image
    camera.capture(image_file, 'jpeg')
    
    # Send the image file to the BeagleBone
    cubesat.beaglebone.copy_to(image_file)
    
    # Wait for a little
    sleep(5)




