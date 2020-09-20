---
title: "Setting up the Raspberry Pi From Scratch"
layout: page
permalink: /pages/tutorials/setup-from-scratch/raspi-from-scratch.html

tags: [software]
keywords: software
---

{% assign warning = "Before getting started, make sure to review the [safety procedures](" | append: 
site.baseurl | append: "/pages/safety-procedures.html#raspberry-pi) for working with the Raspberry Pi." %}
{% include important.html content=warning %}


*****************

> What you will need:
>
>   * Raspberry Pi Zero W
>
>   * Raspberry Pi Camera Module V2
>
>   * Pi Zero Camera Cable
>
>   * Micro USB Cable
>
>   * MicroSD Card and Adapter (8 GB or greater)
>
>   * WiFi connection

{% include image.html file="/resources/tutorials/raspi/components.png" width="75%" %}

******************

# About this Tutorial

If you follow these directions, you will have your Raspberry Pi camera setup working in no time! Some things for you to note: 
* a Pi __Zero__ __W__ is required for this setup (the __W__ indicates that this model has a WiFi module included on the board)
* It is _highly_ _recommended_ that you set up your Pi with a microSD card. It is possible to use the Pi without one, but is more complicated, especially for those with little/no experience
* if you are using a laptop to plug in your USB cable, do not leave it unattended. If your laptop goes into sleep mode, the Pi will lose power and your microSD may be corrupted
* a few downloads are required to complete the setup. They are all open-source, but read ahead and take a look at the links if you'd like

{% include note.html content="If you would like to connect to your Pi over SSH through USB (instead of over WiFi), try this [tutorial](https://desertbot.io/blog/ssh-into-pi-zero-over-usb)" %}

## Preparing the MicroSD

The first step for the microSD is to format it. An [SD card formatter](https://www.sdcard.org/downloads/formatter/) will make this easier (be sure to select the correct version for you OS). Formatting will clear the card of any data so that it can be loaded with the operating system for your Pi.

{% include image.html file="/resources/tutorials/raspi/card_form.png" width="50%" %}

Connect your microSD card adapter and open the formatter. It should select your microSD automatically, but if not, the card should have a drive tag of "D:". Select Quick format and click "Format".

After receiving confirmation, close the formatter.

Next, the OS must be installed on the memory card. Download a Raspberry Pi Imager [here](https://www.raspberrypi.org/downloads/). Open the imager, and for select "Raspberry Pi OS Lite" under "Raspberry Pi OS (Other)". This version uses less data because it does not have to support peripherals like its own monitor, keyboard, and mouse. Select your microSD card and click "Write".

{% include image.html file="/resources/tutorials/raspi/imager.png" width="70%" %}

After the setup is complete, your adapter may disconnect. Check your file explorer for a drive called "D:" or "D:boot" or "SDHC (D:)". If it is missing or you cannot access it, just unplug your adapter and plug it back in. 

When you are able to open up your microSD's drive, you should see various files inside. There are a couple more files that you will need to download and include so that you can access your Pi. An [ssh](https://drive.google.com/file/d/1DUJifUyqbFnxzawpOPD8wK9qO9SceDlm/view?usp=sharing) file will allow you to control the Pi securely from your computer. It is a _blank_ _file_ (may have a single space), and just having it on your memory card enables ssh access. Another file called [wpa_supplicant.conf](https://drive.google.com/file/d/16kqigwpuCYL6QoGRqliyvyxbc_CHEY0w/view?usp=sharing) connects your Pi to WiFi. Open the file in a text editor such as Notepad++ or Visual Studio Code (not Notepad, it may have formatting issues) and add your WiFi name and password inside the double quotes. Keep in mind that the Pi Zero is not yet compatible with 5G networks, so a WiFi connection at about 2.4 GHz is preferable.

{% include image.html file="/resources/tutorials/raspi/folder.png" width="90%" %}

Copy these two files to your microSD.

Make sure they are in the drive folder, and then you can remove the adapter.

{% include important.html content="Make sure to remove the drive safely! The microSD card may be corrupted if you don't and you will have to repeat this section." %}

## Access Your Raspberry Pi By SSH

Start by gathering your formatted microSD card, Pi Zero W, and micro USB cable. Insert your microSD into the port on the Pi. Make sure it is all the way in and secured. Plug in your micro USB into the power port (the one further from the microSD). The other port is for transferring data, which we will do over WiFi.

{% include image.html file="/resources/tutorials/raspi/ports.png" width="50%" %}

You may now plug in the USB end of the cable into power. The green LED should light up, blink on and off for about a minute, then remain on. Give your Pi about 1-2 minutes to boot up. If you hae followed the directions correctly, it will connect to your WiFi automatically. The next step is to make sure the Pi did connect successfully. This can be done by "pinging" the Pi. Open a Command prompt, Terminal, or other command line app and enter the command below

```bash
$ ping raspberrypi
```

and you should get something like this.

{% include image.html file="/resources/tutorials/raspi/ping.png" width="75%" %}

The `bytes from raspberry pi` show that your Raspberry Pi has connect to WiFi and is returning its state of health. If you get an error message like "Ping request could not find host raspberrypi. Please check the name and try again.", then the Pi did not connect to WiFi. Try repeating the steps from __Preparing the MicroSD__. This process can be frustrating and may take a few tries, but don't give up!

Now we can try to log into it with `ssh`.

```bash
$ ssh pi@raspberrypi
```

You will then be prompted to enter a password. The default can be seen below:

        password: raspberry

If you have logged in successfully, you will see somthing like the picture below.

{% include image.html file="/resources/tutorials/raspi/login.png" width="80%" %}

The `pi@raspberrypi` to the left of the `$` sign indicates that you are logged in to the Raspberry Pi as the user `pi`! All commands will be executed in this window. If you accidentally close it, don't worry, just open another terminal window and log back in.

We are now able to see the files stored on the Pi and start to change some settings. First, we must install the camera module so that the Pi knows how to interact with it.

```
$ sudo apt-get update
$ sudo apt-get install python-picamera python3-picamera
```

The install will take a minute, then we can move on to the Raspberry Pi's settings menu. To do this type in the command below:

```
$ sudo raspi-config
```

Once the settings display is open, you can navigate through the options with your arrow keys and the enter key. First, if you would like to change the password for your Pi, you can do so. This will prevent unwanted logins to your Pi, which is particularly easy with the same default password for all Raspberry Pi's. In order to use the camera with your Pi, you will need to enable the camera port.

{% include image.html file="/resources/tutorials/raspi/port.png" width="90%" %}

Scroll to `5 Interfacing Options` and hit enter. Select the camera port option and enable it. The Pi is now ready to interface with the camera. 

{% include important.html content="Do not plug in or remove the camera while the Raspberry Pi is running! Issues have occurred in the past and components may short circuit and be rendered unusable." %}

Before we plug in and test out the camera, we need to safely shutdown the Pi. Type in the command below.

```
$ sudo shutdown -h now
```

The green LED will flash 10 times to indicate shutdown, and then it will turn off. The USB can now be safely removed. 

## Setting Up the Camera

Next we can plug in the camera. Setup your parts in the configuration below.

{% include image.html file="/resources/tutorials/raspi/cable.png" width="75%" %}

The Pi should be face up, the metallic pins on the cable face down, and the camera face down. Now that you know how to correctly insert the cable to each component, carefully pull back the black cable lock on each part. Try to be gentle with these pieces, but if they come completely loose, just put them back where they were. Insert the cable on each side, then secure the lock back in place. 

{% include image.html file="/resources/tutorials/raspi/setup.png" width="75%" %}

Plug in your USB and follow the login steps again. Next we will take a sample picture!

Position your camera at the desired target and execute the following command.

```
$ raspistill -o image.jpeg
```

You can use any name for your picture, but we'll just use `image.jpeg`. The filetype must be `jpeg` or `jpg`. The camera will open its shutter to examine the ambient light for about 5 seconds, then take a picture and turn off. When it is finished, type in `ls` (lowercase L) and you should see `image.jpeg` in the directory!

Because we are using a "headless" boot, where the Pi does not have its own monitor, the picture cannot be viewed directly. We can easily circumvent this issue by secure copying the file to the local machine (your computer or the virtual machine you are using to access the Pi). Open a new terminal window and navigate to the Desktop to make things easy. A simple `$ cd Desktop` should work in a new terminal. Copy and paste the following command:

```bash
$ scp pi@raspberrypi:~/image.jpeg image.jpeg
```

The first `image.jpeg` is the file being copied from the Pi, and the second is what the file is called in the place it is copied to. Now minimize all your windows and find the file and take a look. You should see the file on your desktop and be able to view the jpeg. You have now officially set up your Raspberry Pi camera device!

{% include note.html content="The secure copy command above requires a filepath to the file being copied. In the above example, the file is in the home directory (\~), so all that is required for the filepath is '~/'. If your file is in another directory, just add the filepath like this: ~/folder1/folder2/.../folder17/image.jpeg." %}

If you would like to take a video, try the following command.

```
$ rapsivid -o video.h264
```

H264 is the only video filetype available with the Rapsberry Pi. After copying to your local machine, you will need a way to view this file. It is not easily viewable on most PCs because of its relative high quality. The easiest method is to convert the file to MP4, which can be done in an internet browser [here](https://anyconv.com/h264-to-mp4-converter/). There are methods to view the original files, which can be [explored](https://reolink.com/how-to-play-h264-files-in-vlc/) if you wish.

## Navigating the Rapsberry Pi

Two commands are the most commonly used when navigating through command line.
1. `cd`: change directory. This alone will move you to the home directory. This followed by a folder or path (`cd folder` or `cd folder1/folder2/folder3`) will move to that directory. `cd ..` will move you up one directory. For Raspberry Pi, start with `cd /` to see the pre-installed files.
2. `ls`: list directory items. This lists everything within the current directory. Add a -F like this `ls -F` to distingush files from folders/directories.

Anytime you see `$`, what you type goes afterward.

It is a good idea to create a directory for your picture and video files and eventually for Python scripts that you may use in the future. This directory can be place anywhere, but let's put it in the home directory for simplicity. The command below will create a directory called `picamera` in the home directory.

```
pi@raspberrypi:~ $ mkdir picamera
```

Type `ls` and you should see `picamera` in the directory. Enter this directory and run your `raspistill` and `raspivid` commands to save the files here. 