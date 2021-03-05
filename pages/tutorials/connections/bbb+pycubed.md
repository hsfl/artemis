---
title: "Interfacing the BeagleBone and PyCubed Mainboard"
layout: page
permalink: /pages/tutorials/connections/bbb+pycubed.html

tags: [software]
keywords: software
---

*****************

> What you will need:
>
>   * BeagleBone Black Industrial
>
>   * PyCubed Main Board
>
>   * USB-C cable
>
>   * Mini USB cable
>
>   * 3 Jumper Cables

*****************

## Hardware Setup

Connect to your computer the BeagleBone using the mini USB and the PyCubed Main Board using the USB-C cable.  The BeagleBone and PyCubed will have three jumper cable connections between them: TX, RX, and ground. 

{% include image.html file="/resources/tutorials/board interfacing/pycubed+bbb.png" width="70%" %}

This is how the setup will look when you are testing communication.

## Set up BeagleBone UART and Test

If you are having issues with the UART connection, one way to troubleshoot the issue is to test the BeagleBone UART.  To do this you will need to connect a jumper cable from P9.26 to P9.21 and P9.24 to P9.22 on the BeagleBone.

{% include image.html file="/resources/tutorials/board interfacing/beaglebone_pins.jpg" width="70%" %}
{% include image.html file="/resources/tutorials/board interfacing/bbbuart.png" width="70%" %}

This will connet UART1 to UART2.  Follow the installations to make sure everything needed is installed.

```bash
$ Sudo apt-get update && apt-get install python-pip python-setuptools python-smbus
$ Sudo apt-get install Adafruit_BBIO
$ Sudo apt-get install minicom
```

Now, we need to configure the UART lines. Type the commands below to setup UART1 and UART2.

```bash
$ python
>>> import Adafruit_BBIO.UART as UART
>>> UART.setup("UART1")
>>> UART.setup("UART2")
>>> exit()
```
SSH into your BeagleBone.  Check to if UART lines are open.  In ttyO*, it is the letter "O", not the number 0.

```bash
$ ls -l /dev/ttyO*
```

You should see the five UART lines, UART0-UART4. If not, you may need to go back to installing and setting up `Adafruit_BBIO`.

{% include image.html file="/resources/tutorials/board interfacing/testuart.png" width="70%" %}

In two different terminals, log in to the BeagleBone open up minicom for both UART lines.

```bash
$ minicom -b 9600 -D /dev/ttyO1
$ minicom -b 9600 -D /dev/ttyO2
```

Enable echo mode by entering <kbd>Ctrl</kbd> + <kbd>A</kbd> and then <kbd>Z</kbd> and choose <kbd>E</kbd> in the menu in both terminals. Attempt to communicate between the two.  You should be able to type in either terminal and it will appear in the other window. 

Once you confirm UART communication on your BeagleBone, you are ready to move on to the Pycubed.

## Setup PyCubed for UART

For this tutorial, you should be using a PyCubed mainboard that has already been flashed with the required software. 

As you may already know, the `main.py` script is the only one that is set up to run on the PyCubed. Any time you would like to run a test script or the true main script, you will need to create a permanent name and only name the current script as `main.py` temporarily. An easy way to do this in [Mu](https://codewith.mu/en/download) is to have all of your scripts open at once and one script called `main.py`, and simply copy and paste your code into the main script file. This way, there is no confusion as to which script is currently main.

To test UART communication, find a script called `uart_test.py`. Find the lines that define the TX and RX pins on the PyCubed, they look like this:

```python
tx_pin = microcontroller.pin.PB16
rx_pin = microcontroller.pin.PB17
bb = beaglebone.BeagleBone(tx_pin, rx_pin)
```

These lines define which pins (PB16 and PB17) you will use for the UART line. You can see below where they are located on the board.

{% include image.html file="/resources/tutorials/board interfacing/pycubed_pins.jpg" width="70%" %}

There are alternate UART pins that are available if there are issues with the other pins, named PA12(MOSI) and PA13(SCK). Try PB16 and 17 first, and if issues arise, the alternates may be an option. The GND pin is also indicated, but doesn't need to be setup with any software.

## Testing the UART Connection

Make sure to insert jumper cables while the devices are powered off. Double check that RX on one device is connected to TX on the other device. The PyCubed GND pin can be connected to any ground pin on the BeagleBone.

{% include image.html file="/resources/tutorials/board interfacing/bbb_to_pycubed.jpg" width="70%" %}

The pin pairs from the image can be found below in the table.

| BeagleBone | PyCubed |
| :-----: | :----: |
| P9.24 | PB17 |
| P9.26 | PB16 |
| P9.1  | GND  |

Make sure the pins are safely touching the contacts on each device (you can solder after performing initial tests) and apply power to both. If you have already completed the [BeagleBone from Scratch](https://hsfl.github.io/artemis/pages/tutorials/setup-from-scratch/beaglebone-from-scratch.html) tutorial, the UART lines will be configured on startup from the python script. If not, go back to __Preparing BBIO Pins for Serial Communication__ section of that tutorial.

The pins used in the image above are for UART1 on the BeagleBone, so open Minicom for UART1:

```bash
$ minicom -b 9600 -D /dev/ttyO1
```

And activate echo mode.

On the PyCubed, save the `uart_test.py` file as `main.py` so that it runs. If you don't get any errors in Mu from the PyCubed, then the UART line should be open. Type something in the BeagleBone `minicom` window and hit <kbd>Enter</kbd>, and you should see the same text appear in the Mu output. If you do, you have successfully communicated over UART!

### Using Alternate Pins

If the previous steps did not work for you, there are two alternate pins that you can try. This may work if you got a "Invalid Pins" error.

{% include important.html content="Power down devices before moving jumper cables!" %}

In the `main.py` file, edit the `tx_pin` and `rx_pin` lines to use PA12 and PA13 (you may have to use the names MOSI and SCK, respectively, if another error gets thrown). Make sure to match the correct pins together to ensure that communication will work.

Before running the main script, load `pycubed.py`. You will have to comment out line 56 containing the following:

```python
self.spi  = busio.SPI(board.SCK,MOSI=board.MOSI,MISO=board.MISO)
```

so that these pins will be available. This is a temporary fix, as we do not need any pins for a SPI connection now but we may in the future.

Now, run the main script by hitting <kbd>Ctrl</kbd>+<kbd>D</kbd> and open Minicom on the BeagleBone. Try communicating again, and you should be able to see text from the Minicom window in the Mu console.

## Using Agents and Reading Sensor Data

After successfully confirming UART communication between devices, we can try communication using `agent_pycubed` and capturing sensor data from the BeagleBone. This time, instead of using the `uart_test.py` script we'll use `beaglebone_test.py`. This includes the function `update()` which sends all sensor data from the PyCubed to the IMU. This script is part of a larger `main.py` script that will be run in the deployed satellite, but we do not need all of the functionality for this test.

Save `beaglebone_test.py` as the main script and adjust the pin assignments if needed. 

On the BeagleBone, `agent_pycubed` should run on UART1 automatically.

```bash
$ agents/agent_pycubed
$ agents/agent_pycubed 1    # to specify UART line
```

Make sure to have the `beaglebone_test.py` before `agent_pycubed` so that you can confirm the message automatically sent to the PyCubed by the agent. You should see the following as a test message in the Mu console output:

```
Message type: BST
n
Message contents: BST,y,n,n
```

If you see this message, you have successfully communicated between the BeagleBone and PyCubed!

{% include image.html file="/resources/tutorials/board interfacing/communication_output_2.png" width="50%" %}

Turn to the BeagleBone terminal and look for messages coming in. The PyCubed should automatically send update messages from all of the sensors and print them to the `agent_pycubed` output. Here is an example of an IMU message:

```bash
PyCubed: got message `$IMU,0,-0.292093,0.0981622,0.97185,-5.4375,-35.9375,-1.3125,-0.518799,0.350952,-0.5054,7f`
```

If all of your PyCubed sensors are working properly, the BeagleBone should receive messages for the IMU, GPS, temperature, and power.

{% include image.html file="/resources/tutorials/board interfacing/communication_output_1.png" width="70%" %}

The output in the image above is from a PyCubed with only a working IMU. As you can see, new messages appear repeatedly according to the `sleep.time()` you see in the `beaglebone_test.py` file.