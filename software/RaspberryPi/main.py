# System modules
import json
import os
from time import sleep

# Payload control modules
from picamera import PiCamera

# CubeSat module
from artemis import cubesat

# ====================== SETTINGS ======================
OUTPUT_DIRECTORY = '/home/pi/payload_files'  # Where to save the images before sending them to the BeagleBone

camera = None
image_count = 0  # The number of images that have been written since the script starteds
debug_mode = True  # Set to True to display debug messages

# Camera settings
power_saving = False  # Whether or not to conserve power by disabling the camera after captures
resolution = (1024, 768)  # Image resolution
iso = 800  # Can be one of: 100, 200, 320, 400, 500, 640, 800

capture_interval = 5  # The time to wait between captures
warm_up_time = 2  # The time to wait after enabling the camera before capturing images


# Set up the SOH as a dictionary
soh_dict = {
    "camera": {
        "enabled": False,
        "resolution_w": resolution[0],
        "resolution_h": resolution[1],
        "iso": iso,
        "image_count": image_count,
        "last_utc": 0  # TODO
    }
}
# ======================================================


def UpdateSOH():
    'Sets the state of health string for the payload via artemis.SetSOHString(...)'
    global soh_dict, camera, resolution, iso, image_count, debug_mode

    soh_dict["camera"]["enabled"] = camera is None
    soh_dict["camera"]["resolution_w"] = resolution[0]
    soh_dict["camera"]["resolution_h"] = resolution[1]
    soh_dict["camera"]["iso"] = iso
    soh_dict["camera"]["image_count"] = image_count
    soh_dict["camera"]["last_utc"] = 0  # TODO

    # Convert the SOH dictionary to a JSON string
    # soh_json = json.dumps(soh_dict, separators=(',',':'))
    soh_json = json.dumps(soh_dict, sort_keys=False, indent=4, separators=(',', ': '))

    # Set the SOH string
    # (TODO) artemis.SetSOHString(soh)
    if debug_mode:
        print('Current SOH:')
        print(soh_json)


def EnableCamera(warm_up=False):
    'Enables the camera if not already enabled. If warm_up is true, then there is a delay after enabling.'

    global camera, resolution, iso, warm_up_time, debug_mode

    # Check if the camera is already enabled
    if camera is None:

        if debug_mode:
            print('Enabling the camera with resolution %dx%d and ISO %d' % (resolution[0], resolution[1], iso))

        # Initialize and configure the camera
        camera = PiCamera()
        camera.resolution = resolution
        camera.iso = iso

        # Sleep if a warm up is requested
        if warm_up:
            sleep(warm_up_time)


def DisableCamera():
    'Disables the camera if it is enabled. This frees resources used by the camera device.'

    global camera, debug_mode

    # Check if the camera is already disabled
    if camera is not None:
        if debug_mode:
            print('Disabling the camera')

        camera.close()
        camera = None


def SingleCapture():
    'Captures an image and saves it to a file. Returns the name of the file.'

    global camera, image_count, OUTPUT_DIRECTORY, debug_mode

    # Make sure the camera is enabled
    EnableCamera()

    # Capture the image
    dest_file = OUTPUT_DIRECTORY + '/image_%d.jpeg' % image_count
    camera.capture(dest_file, 'jpeg')

    image_count += 1

    if debug_mode:
        print('Captured image to ' + dest_file)

    # Disable the camera if in power-saving mode
    if power_saving:
        DisableCamera()

    # Return the path of the output file
    return dest_file


# Main loop
while True:
    # Update the CubeSat
    cubesat.update()

    # Capture an image
    image_file = SingleCapture()

    # Transmit the file to the BeagleBone
    if debug_mode:
        print('Attempting to transmit file to BeagleBone...')

    status = cubesat.beaglebone.copy_to(image_file)

    # TODO Check if an error occurred
    
    # Update the SOH
    UpdateSOH()

    # Sleep for a little
    sleep(capture_interval)




