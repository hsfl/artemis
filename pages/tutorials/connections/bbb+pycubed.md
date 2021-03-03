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
>   * BeagleBone Black
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

Connect to your computer the BeagleBone using the mini USB and the PyCubed Main Board using the USB-C cable.  The BeagleBone and PyCubed will have three jumper cable connections between them.  The TX, RX, and ground.  Connect jump cables to PB16(TX), PB17(RX) and ground.  If using UART1 on the BeagleBone, connect PB16 to P9.26 PB17 to P9.27 and ground to P9.1.  

{% include image.html file="/resources/tutorials/board interfacing/pycubed+bbb.png" width="70%" %}

## Setup BeagleBone UART

SSH into your BeagleBone.  Check to if UART lines are open.  In ttyO*, it is the letter "O", not the number 0.

```bash
$ ls -l /dev/ttyO*
```

If the following results do not show up, then follow this [link.](https://sites.google.com/from scratch/bbb/usb_device.png

{% include image.html file="/resources/tutorials/board interfacing/testuart.png" width="70%" %}

Use the following commands to install the necessary tools.

```bash
$ Sudo apt-get update && apt-get instafrom scratch/bbb/usb_device.png
```bash
$ minicom -b 9600 -D /dev/ttyO1
```

Hit "CTRL-A" and then "E" to enter echo mode.  Now you can type in minicom.  If the BeagleBone and and PyCubed are set up correctly, then you will now be sending messages to the PyCubed.

## Testing BeagleBone UART

If you are having issues with the UART connection, one way to troubleshoot the issue is to test the BeagleBone UART.  To do this you will need to connect a jumper cable from P9.26 to P9.21 and P9.24 to P9.22.  

{% include image.html file="/resources/tutorials/board interfacing/bbbuart.png" width="70%" %}

This will connet UART1 to UART2.  Follow the installations to make sure everything needed is installed.

```bash
$ Sudo apt-get update && apt-get install python-pip python-setuptools python-smbus
$ Sudo apt-get install Adafruit_BBIO
$ Sudo apt-get install minicom
```

In two different terminals, open up minicom for UART1 and UART2.

```bash
$ minicom -b 9600 -D /dev/ttyO1
```

```bash
$ minicom -b 9600 -D /dev/ttyO2
```

Hit "CTRL-A" then "E" on both terminals to open echo mode.  You should be able to type in either terminal and it will appear in the other window.  If this is not working, then attempt to open UART1 and UART2 using python

```bash
$ python
>>> import Adafruit_BBIO.UART as UART
>>> UART.setup("UART1")
>>> UART.setup("UART2")
>>> exit()
```

Open minicom for UART1 and UART2.  Enable echo mode and attempt to communicate between the two UARTs.