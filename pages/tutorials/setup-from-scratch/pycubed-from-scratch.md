---
title: "Setting up the PyCubed Mainboard From Scratch"
layout: page
permalink: /pages/tutorials/setup-from-scratch/pycubed-from-scratch.html

tags: [software]
keywords: software
---

{% assign warning = "Before getting started, make sure to review the [safety procedures](" | append: 
site.baseurl | append: "/pages/safety-procedures.html#beaglebone) for working with the BeagleBone." %}
{% include important.html content=warning %}

## What You Will Need

* PyCubed Mainboard (populated)
* USB-C Cable
* Jumper Cables
* JTAG Programmer

# Setting up the PyCubed

## Flashing the Bootloader

On the PyCubed website, you'll find a [tutorial](https://www.notion.so/Programming-the-Bootloader-a5c2f6b50c3d459eaa0a4f00d8218365#11432bf53fb44763b39cc682d8e2ed8d) that will help you with initial firmware flashing on the PyCubed main board.

After completing the steps, you can move on to the next section.

## Prepping the Hardware

{% include note.html content="Please note, these steps can also be found on the PyCubed website found [here](https://www.notion.so/Hands-On-Quick-Start-d220f0ec88eb41c08ee855ff4f46d737)." width="50%" %}

Before powering the PyCubed board, you will most likely need to make sure the railswitches and footswitches are jumped. This can be done with jumper cables or wires or even paper clips (be sure not to touch them while the board is powered!).

In the images below, make sure the positive and negative terminals are connected for all three switches.

{% include image.html file="/resources/tutorials/from scratch/pycubed/rail_switch.jpg" width ="70%" %}

The rail switch is located on the top side of the board.

{% include image.html file="/resources/tutorials/from scratch/pycubed/foot_switch.jpg" width ="70%" %}

The foot switches are on the bottom of the board.

## Installing Mu

Mu is a graphical user interface that allows you to edit and run CircuitPython code on the PyCubed board. It can be installed on Mac, Windows, and Linux [here](https://codewith.mu/en/download) (Linux users, go to the link destination for the source code).

Follow the instructions to complete the install. Currently, the PyCubed board will not be recognized by Mu, so you will have to edit the `adafruit.py` file so that it will interface. This file can be found in the following folder(s):

        Windows:    C:\Users\USERNAME\AppData\Local\Mu\pkgs\mu\modes 
        Mac:        /Applications/mu-editor.app/Contents/Resources/app/mu/modes

Scroll to lines 64-66

```python
        (0x239A, 0x803C),  # future board
        (0x239A, 0x803E),  # future board
    ]
```

and add the following two lines between 65 and 66:

```python
        (0x239A, None),    # Any Adafruit Boards
        (0x04D8, None),    # PyCubed related boards
```

This should help the PyCubed to connect with the Mu application.

Now start up Mu, and you'll be prompted to select a mode.

{% include image.html file="/resources/tutorials/from scratch/pycubed/mu_startup.png" width="90%" %}

Select "CircuitPython", which allows you to access and edit files in the editor above, and run scripts in the console below. You may get an error if your PyCubed is not connected, but you can close the error and the PyCubed will automatically connect when it is plugged in to the computer.

{% include image.html file="/resources/tutorials/from scratch/pycubed/device_error.png" width="80%" %}

When your device is connected, you'll see this at the bottom of the window:

{% include image.html file="/resources/tutorials/from scratch/pycubed/new_device.png" width="60%" %}

## Running Sensor Test Scripts

The PyCubed main board will only run the file in the home directory called `main.py`. In order to run any script, the script has to be renamed or the contents have to be pasted into the main file. An easy way to approach this is to keep all of your scripts named in a descriptive way, to have the `main.py` file open, and to simply copy and paste the contents of the script you'd like to run into `main.py`.

In Mu, click on the "Serial" button.

{% include image.html file="/resources/tutorials/from scratch/pycubed/serial.png" width="80%" %}

In the console that appears below, click in the field and press <kbd>Ctrl</kbd>+<kbd>C</kbd>. This ends any currently running process. If nothing happens, there is nothing running (no `main.py` file). If there is a main script running, you will see some output indicating that the program has stopped.

Next, click on the "Load" button to select a file to open. The first folder you see is the home directory, where you should save the `main.py` file. Open the "tests" folder. Here you will find several scripts to test the functionality of the board. Try opening `led_test.py`. This script will cycle the LED on the board through a rainbow of colors.

Open the `main.py` file alongside the LED script if you have one. If not, create a new one and save it in the home directory. Copy and paste all the contents of `led_test.py` into the main script and make sure to remove any other code. Save the file, and the main script will run automatically.

{% include image.html file="/resources/tutorials/from scratch/pycubed/led.png" width="90%" %}

If everything is correct, you'll see the LED continuously cycle through the colors.

Next, you can test the IMU. Open the `imu_test.py` file and copy it into the main script.

{% include image.html file="/resources/tutorials/from scratch/pycubed/imu_test.png" width="100%" %}

You should see output like in the image above. Carefully pick up the PyCubed and rotate it and move it around slightly, and look for the response in the output of the sensor data. You can also place a finger on the IMU and look for a response in the temperature sensor. Be extra careful with this, making sure not to touch any of the electrical contacts on the board.

Repeat the process to test out any of the other sensors you would like.
