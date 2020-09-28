---
title: PyCubed Main Script
permalink: /pages/documentation/pycubed/main-script.html
layout: page

keywords: software
---


## Overview

The [main script](https://github.com/hsfl/artemis/blob/master/software/PyCubed/main.py)
on the PyCubed is automatically executed when powering the board.
This script must have the name `main.py` and be located in the root directory of
the PyCubed in order to be run.

In the cubesat kit, this script performs all of the logic necessary for the
PyCubed to operate correctly.


## Initialization

When the main script first runs, it ensures that the BeagleBone is receiving power
and has booted successfully. Once the PyCubed receives a "startup signal" from the
BeagleBone, the main script enters _nominal mode_.


## Power Modes

As the PyCubed acts as an ISC during periods of low power, it is necessary for the
main script to control the entry and exit of _low power mode_. There are several
distinct states that the main script can be in at any given moment:


### 1. Nominal Mode
This is the mode the PyCubed will be in while the battery charge is sufficiently high.
Typical I/O is performed between the BeagleBone and PyCubed.


### 2. Entering Low Power
This mode is entered when the battery charge drops too low. A message is sent
to the BeagleBone to request that it shut down. Once confirmation is received,
power is cut off to the BeagleBone in order to reduce energy use.

### 3. Low Power Mode
In this mode, the PyCubed simply waits until the batteries have become sufficiently
charged by the solar cells. Once an adequate charge is reached, power is restored
to the BeagleBone, and low power mode is exited.

### 4. Exiting Low Power
In this mode, the PyCubed waits for a "startup confirmation" signal to be received
from the BeagleBone, indicating that it booted successfully. Once this signal is
received, the PyCubed returns to nominal mode.


## See Also
* [PyCubed Website](http://pycubed.org/)
* [PyCubed Communication Protocol](communication-protocol.html)