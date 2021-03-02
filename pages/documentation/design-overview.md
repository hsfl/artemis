---
title: Design Overview
permalink: /pages/documentation/design-overview.html
layout: page

tags: [software]
keywords: software
---


## Introduction

The design of a cubesat is broken down into several subsystems, each corresponding to a major
grouping of necessary functionality. The subsystems in this kit are briefly explained below.


## Thermal Control System (TCS)

The purpose of the TCS is to regulate temperatures inside of the satellite. This subsystem is critical,
as virtually all of the electrical components can only operate within a certain range of temperatures.

In this kit the limiting temperature range is that of the battery pack, which has a minimum charging
temperature of 0&deg;C and a maximum charging temperature of about 45&deg;C.

In this kit, the TCS uses five temperature sensors ([TMP36GZ](http://www.us.diigiit.com/tmp36gz-temperature-sensor) / [BMX160](https://www.digikey.com/product-detail/en/bosch-sensortec/BMX160/828-1087-1-ND/?utm_adgroup=Sensors%20%26%20Transducers&utm_source=google&utm_medium=cpc&utm_campaign=Dynamic%20Search_EN_Product&utm_term=&utm_content=Sensors%20%26%20Transducers&gclid=Cj0KCQiAvvKBBhCXARIsACTePW-6egaa0lNaTEWvnBmjjd_bKXjcJ0FRFKbaYU3OE2iOX3ekU0w9c2oaAkuzEALw_wcB)) on each board to determine when it is
appropriate to activate the heater, located on the battery pack.


## Attitude Determination and Control System (ADCS)

The purpose of the ADCS is to determine attitude and location, and adjust the orientation of the satellite
accordingly by means of actuators (magnetic torque rods, reaction wheels, etc.). In this kit there
are no built-in actuators.

The ADCS in this kit is comprised of an IMU (BMX160), coarse sun sensors ([OPT3001](https://www.ti.com/product/OPT3001?utm_source=google&utm_medium=cpc&utm_campaign=asc-null-null-GPN_EN-cpc-pf-google-wwe&utm_content=OPT3001&ds_k=OPT3001&DCM=yes&gclid=Cj0KCQiAvvKBBhCXARIsACTePW80NzFlXbPtyuDWsTLq19sVP7OgQZ_GNI2wUaA2XgECfX4F9WNREn8aAgKdEALw_wcB&gclsrc=aw.ds)), and a GPS module([Venus838FLPx-L](http://navspark.mybigcommerce.com/content/Venus838FLPx_DS_v7.pdf)).

The GPS module is used to determine the geographic coordinates, altitude, and velocity of the satellite.
Although there is no attitude determination performed by default, the sun sensors and IMU may be used
in user-written software for this purpose.


## Communications Subsystem (COMMS)

The purpose of the COMMS is to transmit and receive information remotely once the the satellite
is in orbit. Without a working COMMS subsystem, the satellite cannot meaningfully perform its
tasks once out of the reach of engineers.

The COMMS subsystem in this kit is comprised of a longe-range radio transceiver ([RFM98PW](https://www.hoperf.com/modules/lora/RFM98P.html)) and
an antenna.


## Electrical Power System (EPS)

The purpose of the EPS is to manage the storage and distribution of power throughout the satellite.

The collection of electrical components handling power distribution is known as
a _Power Distribution Unit_, or PDU. The circuit board holding the PDU is known simply as the PDU board.
The PDU board used in this kit is designed by Hawaii Space Flight Laboratory.

In this kit, the EPS subsystem is the generates power through solar cells, and stores them in a
battery pack ([LG MJ1 18650](https://www.batteryjunction.com/lg-mj1-inr-18650-batteries-4pack.html)). The board containing the batteries is known as the battery board,
which is designed by PyCubed in this kit.

## Onboard Computer System (OBCS)

The purpose of the OBCS is to process information supplied by the other subsystems and determine
appropriate actions through the flight software. In this kit there are three onboard computers:

The [BeagleBone Black Industrial](https://beagleboard.org/black-industrial) (BeagleBone for short) is the primary OBC running flight software
designed using COSMOS.

The [Raspberry Pi Zero W](https://www.raspberrypi.org/products/raspberry-pi-zero-w/) (Raspberry Pi or Raspi for short) is the payload OBC used as an
interface for various user-defined payloads. Scripts written for the Raspberry Pi handle
interaction with the payload and refer necessary information to the BeagleBone. Communication is
performed over a USB/SSH connection between the two OBCs.

The [PyCubed](https://www.notion.so/PyCubed-4cbfac7e9b684852a2ab2193bd485c4d) mainboard controller (PyCubed for short) is the OBC used to interface with the components
on the PyCubed mainboard (e.g. IMU, GPS, radio transceiver, etc.). Scripts written for the PyCubed
handle interaction with the various components. Information such as radio packets and sensor data
is relayed between the BeagleBone and PyCubed over a serial connection.

## Flight Software

In a satellite, flight software refers to the software written for an OBC. The flight software in this kit
is broken into three major parts corresponding to the three OBCs.

The BeagleBone flight software is comprised of several COSMOS agents, each of which handle
interaction with a hardware component connected to the BeagleBone.

The Raspberry Pi flight software is comprised of a Python package (known here as the Artemis Raspberry Pi
or ARP library) used to gather information from hardware components, and one or more payload script using this package.

The PyCubed flight software is comprised of a Python package (known here as the Artemis PyCubed or APC library)
used to communicate with the BeagleBone, and the main script using this package.

## Structure and Mechanisms

The structure subsystem involves the physical assembly of the satellite, while the mechanisms subsystem
involves the mechanical mechanisms built into the structure (e.g. antenna deployment and deployment switches).

The structure and mechanisms must adhere to strict requirements in order to be accepted by a launch provider.
The structure and mechanisms of this kit are designed to follow Nanoracks and Cubesat Launch Initiative (CSLI)
requirements.

## Payload

A payload is the device included in a satellite which performs its primary task. This is often chosen to collect data
in response to a research question, and may be defined by stakeholders of the mission.

The payload device included in this kit is the [Raspberry Pi Camera Module V2](https://www.raspberrypi.org/products/camera-module-v2/), an optical and infrared imaging
camera. While this payload may be switched out with another at the user's discretion, there is no additional
software provided with this kit meant to control other payloads. Any additional software functionality required
is up to the user to implement.
