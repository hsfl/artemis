---
title: "Setting up the BeagleBone From Scratch"
layout: page
permalink: /pages/tutorials/setup-from-scratch/beaglebone-from-scratch.html

tags: [software]
keywords: software
---

{% assign warning = "Before getting started, make sure to review the [safety procedures](" | append: 
site.baseurl | append: "/pages/safety-procedures.html#beaglebone) for working with the BeagleBone." %}
{% include important.html content=warning %}

## What You'll Need
* BeagleBone Black
  * Micro SD Card (this will be overwritten)
* Desktop computer
  * Internet Connection
  * A way of writing to the Micro SD Card (built-in slot, external writer, SD card adapter, etc.)
* Ethernet Cable (optional, for updating)
* USB Type A to USB Mini-B cable

# Setting up the BeagleBone

## Getting Started
Let's begin with turning on the BeagleBone and making sure it works properly. Plug in your USB A-to-Mini-B cable into your computer and the BeagleBone. Use the Mini USB port on the underside of the board, near the ethernet port. 

{% include image.html file="/resources/tutorials/from scratch/bbb/bbb_ports.png" width="100%" %}

You will see a power LED flash on, and 4 other LEDs will blink on and off. This indicates the boot process of the device. After a minute or so, the BeagleBone should appear as a USB storage device, a network device, and a serial device. 

{% include image.html file="/resources/tutorials/from scratch/bbb/bbb_on.png" width="70%" file="/resources/tutorials/from scratch/bbb/serial_device.png" width="70%" %}

Open up a file explorer and select the USB storage device folder, which should appear as the __D:__ drive. Open the file _START.html_ in a browser to view the BeagleBone "Getting Started" page (you can also find it [here](https://beagleboard.org/getting-started)). There you will find plenty of useful advice in working with your BeagleBone. It is a good idea to follow the steps for "Updating board with latest software".

{% include image.html file="/resources/tutorials/from scratch/bbb/usb_device.png" width="70%" %}

There may be issues with booting your BeagleBone from the image on the SD card. Follow the link [here](https://stackoverflow.com/questions/31725206/unable-to-flash-emmc-from-sd-card-beaglebone-black) for help with this.

{% include note.html content="You will know the correct image has booted when you see a correct date for the new image in the terminal when you log in (the factory operating system will be signified by 'BeagleBoard.org Debian Image 2016-01-24')." %}

This site will tell you to open up `http://192.168.7.2/ ` or `http://192.168.6.2 ` for Linux/MacOS. This leads to the Cloud9 Integrated Development Environment, a graphical interface which makes developing with the BeagleBone easier. Go ahead and open the link. If it works, then you can skip the next section! The Cloud9 IDE has been known to malfunction in some cases upon the first startup, and in this case, follow the steps in the next subsection.

### Establishing a Serial Connection

Connecting to devices is pretty simple using a serial port. A good application for this is [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html), but the Arduino IDE and others will also work. In this tutorial we'll use PuTTY, but these steps can be used in other programs as well.

Go to your device manager, and find the BeagleBone in the list. In Windows, it should appear under _Ports (COM & LPT)_ as _USB Serial Device (COM4)_. The number next to _COM_ may be different. In Linux or MacOS, the device will appear in your `/dev/` folder as something like `ttys004` or `ttyACM4`. You will need the name of the device on your machine for the next step.

{% include important.html content="It is not recommended to work with any physical connections from a virtual machine. It can be difficult to enable peripheral interfaces, and they can cause problems with the virtual machine itself as well." %}

Open PuTTY once it is installed. Switch to "Serial" and enter the device name you found before under "Serial Line". Enter "115200" under speed. This is known as the "baud rate", or the data transfer rate through this connection. Click "Open", and a terminal will appear.

{% include image.html file="/resources/tutorials/from scratch/bbb/putty.png" width="70%" %}
{% include image.html file="/resources/tutorials/from scratch/bbb/console.png" width="100%" %}

Like you can see in the printed lines in the terminal, the default login is as follows:

	  username: debian
	  password: temppwd

Using the commands `cd` and `ls`, you can navigate the device easily. Your BeagleBone is up and running! One more thing to do is change the password on your BeagleBone for security reasons before connecting it to your network.

This can be done with the command below:

```bash
$ passwd
```

And just follow the steps with the new password of your choice! Remember that you will have to use this password every time you access the BeagleBone in the future, so be sure to choose something you can remember.

## Remote Access to the BeagleBone

For this section, you can continue to provide power to your board using the USB cable. It is, however, good practice to set up a remote connection between your systems while providing power to the BeagleBone with a 5V power supply like [this one](https://www.trcelectronics.com/View/Mean-Well/GSM12U05-P1J.shtml). This is for safety purposes, as you can plug in your board to power and your network away from your workspace and avoid any accidental damage to the board or its sensitive components.

Whatever method of power you choose, plug in an ethernet cable into your board, and apply power. The BeagleBone should come with SSH (method of remote access) and ethernet access enabled already. Give the board a minute to boot up, and the next step is to find the IP address of your BeagleBone.

If you know the IP address of your home network (likely an internet router), just type it in the search bar of your browser. If you don't, type in the following command in a terminal or command prompt:

```bash
$ ipconfig
```

In Linux or MacOS, use the command `ifconfig` or `ip a`.

Look through the output. If you are using WiFi, look for "Wireless LAN adapter Wi-Fi" (Windows). With ethernet, the process should be similar. There should be a line that says "Default Gateway", and the IP address on that line will be the IP of your network router.

{% include image.html file="/resources/tutorials/from scratch/bbb/ipconfig.png" width="90%" %}

Go ahead and put that IP in your browser's search bar.

You should see information about your network, including any devices that are connected. Look through the list, and find "beaglebone" with connection type "Ethernet LAN-4". There should be an IP address as well that looks like "192.168.1.xxx".

{% include note.html content="If you don't see 'beaglebone' on your network device list, it may not be properly connected to the network. Make sure the ethernet cable is connected properly at both ends and the network is active." %}

Once you find it, write it down or commit it to memory for the next step. With your host computer (laptop or desktop) connected to the same network (WiFi or ethernet), open PuTTY again and select "SSH" this time. This is short for secure shell, or a secure way to remotely access another device. Type in the IP address of the __BeagleBone__ and open it. A terminal should appear the same way as with the serial connection method.

Alternatively, you can access the device from a terminal or command prompt. Just use the following command:

```bash
$ ssh debian@192.168.1.xxx
```

## Cloud9 Integrated Development Environment

Try opening up the Cloud9 IDE again with the IP addresses above. If you are using a Windows host machine, you may need to eject this device before proceeding.

Open up a web browser and navigate to:

* **Windows:** http://192.168.7.2/
* **Linux/Mac:** http://192.168.6.2/

 You may need to wait a minute if the BeagleBone is still booting. Eventually you should see the Cloud9 IDE.

If you are still having issues, go back to the remote access section using ethernet and boot the BeagleBone. Instead of accessing the board with SSH, enter the BeagleBone's IP in the search bar of your browser. You should see BeagleBoard site appear with a green box that says "Your board is connected!". Scroll down and click on __Cloud9 IDE__.

{% include image.html file="/resources/tutorials/from scratch/bbb/bone101.png" width="100%" %}

In the new tab, you should see a few different boxes. Play around with this interface and familiarize yourself with how it works. This is similar to working with Qt Creator, if you have already completed the "Development Environment" or "COSMOS from Scratch" tutorials. 


If you haven't completed one of those tutorials yet, go back and finish at least one of them before moving on.

## Set up COSMOS on the BeagleBone
To install COSMOS on the BeagleBone, you will have to _cross compile_ the code, or compile the code on a host system for a target system. In this case, the host is your virtual machine, and the target is the BeagleBone.

Open up your virtual machine containing COSMOS software. Log in and open up Qt Creator. You don't need to have any projects open yet. Follow this [tutorial](https://hsfl.github.io/cosmos-docs/pages/4-tutorials/build/cross-compile.html) on cross-compiling. Do your best to follow the steps.


> Tips for Cross-Compiling Tutorial
>
> 1. All commands beginning with `$` should be executed in a terminal
>
> 2. The BeagleBone must be accessed _inside_ the machine you are using to cross-compile while you are going through the tutorial, or you won't be able to add the device (use SSH from a terminal)
>
> 3. If running the `rsync` command results in errors, you can try a couple of different things. First make sure the ip address of the BeagleBone is correct, then try manually creating the cosmos folder in the BeagleBone by running `mkdir cosmos`, finally double check that the folders you are sending and receiving from are correct.
>
> 4. If the steps under __Add COSMOS to Path__ don't work, start by rebooting the BeagleBone with a `$ sudo shutdown -h now`, and then type `$ agent`. If that doesn't work, try tip 4
>
> 5. Try `$ ./agent`. If this works, you will need to use `./` at the beginning of each agent you run. If that doesn't work, try tip 5
>
> 6. Look for a folder named `bin`. It should be the location you chose in the `rsync` command, and an `ls` will show all the necessary agent (green text in Ubuntu). Try `$ ./agent` again. If it still does not work, the executable files may not have been correctly transferred
>
> 7. Follow the same steps for the Artemis software project. It is recommended to have COSMOS core agents and Artemis agents loaded on your BeagleBone.

## Preparing BBIO Pins for Serial Communication

After looking through the Artemis agent programs, you may notice that some of the devices require serial communication to keep track of data. For testing, the BeagelBone must be prepared for these UART, SPI, and I2C connections. 

These steps will help you set up UART on the BeagelBone. 

First, you will need to install the __Adafruit-BBIO__ module. (It is good practice to always run `sudo apt update`, and `sudo apt upgrade` if necessary, before installing new modules.)

In the BeagleBone terminal (PuTTY), type in the commands:

```bash
$ sudo apt install python-dev python3-pip -y
$ sudo pip3 install Adafruit_BBIO
```

This will install the BeagleBone pin library to your device. After this step, each UART line must be configured before it can be used.

```bash
$ python
>>> import Adafruit_BBIO.UART as UART
>>> UART.setup("UART1")
>>> quit()
```

Now UART1 on the BeagleBone is ready for communication. You can test this out with a program called __minicom__.

```bash
$ sudo apt install minicom
```

Once this is installed, run the `python` and `UART.setup` commands again, but this time, with "UART2".

For communication to occur, there must be a physical connection. Turn off your BeagleBone and use jumper cables to connect UART1 to UART2 on the BeagleBone, following the picture below.

{% include image.html file="/resources/tutorials/cosmos/part2/beaglebone_rx_tx_feedback.png" width="100%" %}

Note that for each cable, __TX__ is connected to __RX__ and vice versa. The pin connections are P9_22<===>P9_24 and P9_21<===>P9_26.

Now boot your device back up and open two terminals. Log in on both and type in the following commands:

```bash
# first terminal
$ minicom -b 9600 -D /dev/ttyO1

# second terminal
$ minicom -b 9600 -D /dev/ttyO2
```

In both terminals, type in <kbd>Ctrl</kbd> + <kbd>A</kbd> and then <kbd>Z</kbd>, and when the menu pops up, type in <kbd>E</kbd>. This will activate the `echo` setting, which will print anything that is received by the given UART line. Type in one of the windows, and you should see the same text appear in the other window. Then try the reverse. If the text appears in each window, then you have successfully configured UART! 

For a normal connection, you will only need one UART line on the BeagleBone, and the other will be on the peripheral device you are connecting. For example, The PyCubed board is connected to UART1 on the BeagleBone.

An issue that may occur with the BeagleBone is that the UART line will have to be reconfigured every time the BeagleBone is turned off and on. To make the configuration easier, we can write a script that reduces the commands needed to one. The lines below are an example of a script that would do this for us. to create a new file, type in `nano init_uart.py` or whatever name you would like for the file, and add the lines.

```python
import Adafruit_BBIO.UART as UART

UART.setup("UART1")
UART.setup("UART2")
UART.setup("UART3")
UART.setup("UART4")
```

Hit <kbd>Ctrl</kbd> + <kbd>S</kbd> to save and <kbd>Ctrl</kbd> + <kbd>X</kbd> to exit. Reboot the BeagleBone and run the script with `python init_uart.py`, and the UART lines should be configured and ready to communicate.

To have this script run on its own each time the BeagleBone is powered, run the command below.

```bash
$ sudo cp -i {insert path}/init_uart.py /bin
```

Now that the script is in the `bin` folder, run the command:

```bash
$ sudo crontab -e
```

and select `nano` if prompted. Scroll all the way to the bottom of the file and add the line below:

```
@reboot python /bin/init_uart.py &
```

Save and exit the file. Now, reboot your BeagleBone, and UART should be configured automatically!
