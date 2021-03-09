---
title: "Interfacing the BeagleBone and Raspberry Pi"
layout: page
permalink: /pages/tutorials/connections/bbb+raspi.html

tags: [software]
keywords: software
---

*****************

## What you will need:

   * Raspberry Pi Zero W

   * Micro USB Cable

   * BeagleBone Black

   * Micro SD card

   * Micro SD card adapter


******************

## Preparing the MicroSD

Follow the [Raspberry Pi From Scratch](https://hsfl.github.io/artemis/pages/tutorials/setup-from-scratch/raspi-from-scratch.html) tutorial.  Enter these two commands.

```bash
$ cd /etc/wpa_supplicant/
$ vi wpa_supplicant.conf
```

Edit the file to look like the following.

```bash
country=US
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
```

This will disable the wifi and enable the Raspberrypi to connect to the BeagleBone Black over the USB cable.  Attach the USB host to the BeagleBone and the micro USB to the Raspberrypi.  Connect the BeagleBone Black to the computer and SSH into the BeagleBone by using putty or the following command from the command prompt.

```bash
$ ssh debian@beaglebone.local
```

Now ssh into the Raspberrypi.

```bash
$ ssh pi@raspberrypi.local
```

If properly connected, you will now be able to controll the Raspberrypi through the BeagleBone Black.

## Adding Files to RaspberryPi through the BeagleBone

For this procedure we will need to transfer the files onto the BeagleBone and then transfer them onto the Raspberrypi.  Place the designated file or folder onto your computer desktop.  We will be transfering the folder "python".  In the command prompt enter the following commands.

```bash
$ rsync -auv ./python debian@beaglebone.local:/debian/home
$ ssh debian@beaglebone.local
$ ls
```

Now you should be in the BeagleBone and the "python" folder should appear on the BeagleBone.  Now we are going to transfer the file from the BeagleBone to the Raspberrypi.

```bash
$ rsync -auv ./python pi@raspberrypi.local:/pi/home
$ ssh pi@raspberrypi.local
$ ls
```

You should now be in the Raspberrypi and the "python" folder should appear inside.
