---
title: "Getting Started Part 2 - Development Environment"
layout: series
permalink: /pages/tutorials/setup/setup2.html

tags: [software]
keywords: software
sidebar: home_sidebar
toc: false


series:
  prev: /pages/tutorials/setup/setup1.html
  next: /pages/tutorials/setup/setup3.html
---

## Introduction

The Artemis Development Environment is provided as an Ubuntu 18.04.4 Vagrant box with necessary tools preinstalled.

VirtualBox and Vagrant are used to ensure the development environment is cross-platform. VirtualBox is used for
virtualization of operating systems, and Vagrant is used to set up the virtual machine in a (mostly)
platform-independent manner.

### Why Linux?

Linux makes working with the kit software much easier, as the operating system as a whole is designed for developers.
Our image is also fairly lightweight, meaning that unnecessary software is stripped out so that the download size is
minimal.

### Supported Operating Systems

The supported operating systems are essentially those that VirtualBox and Vagrant support:

* Windows
* macOS
* Linux


## 1. Install Dependencies

### 1.1 VirtualBox
VirtualBox is used to run the virtual machine used as the development environment. Get it [here](https://www.virtualbox.org/wiki/Downloads). The install wizard will help you.


### 1.2 Install Vagrant

Vagrant is used to set up the virtual machine used as the development environment. Get it [here](https://www.vagrantup.com/downloads). The install wizard will help you.

### 1.3 Install the Guest Additions Plugin

The Vagrant guest additions plugin automatically installs VirtualBox guest additions into the virtual machine. 
Install it by opening up a command prompt (Windows) or a terminal (Linux/Mac) and running the following:

```bash
$ vagrant plugin install vagrant-vbguest
```

{% include image.html file="/resources/tutorials/setup/part2/cmd.png" width="100%" %}

{% include important.html content="Do not copy the `$` character or the following space when entering commands.
This notation is used to indicate the input to a terminal." %}

## 2. Set up the Artemis Box

Some of the commands you will need:
- __cd__: changes directories. Use the command `cd {insert folder name here}` to move in to that folder. The command `cd ..` moves up one folder.
- __dir__: shows what is in the current directory. Use this to check what folders/files are in your current directory to ensure everything is done properly.

### 2.1 Add the Box


Download the Artemis box from
[here](https://drive.google.com/file/d/14slc_5AHery2TkT4guIsQOVaNav0zdbC/view?usp=sharing). An example location of the file on Windows is
`C:\Users\YOUR_USERNAME\Documents\Vagrant\artemis`. 



{% include important.html content="You must be in the correct folder for the commands to work. The file may be in your Downloads folder if the download does not prompt a window for a save location. Below is an example Command window in the correct folder after the file has been moved to another location." %} {% include image.html file="/resources/tutorials/setup/part2/command_line2.png" width="100%" %}



Once in the Command prompt is in the correct folder, Run the following commands.

```bash
$ cd "PATH/TO/VAGRANT/BOX"
$ vagrant box add artemis artemis.box
```

You can now delete the `artemis.box` file you downloaded if you wish.

### 2.2 Create the Virtual Machine

Once the install is finished, you can move on to the next step

Enter the following command:

```bash
$ vagrant init artemis
```

Download the "Vagrantfile" file from [here](https://drive.google.com/file/d/1YqGf7kaUyD1uRo8xKAWAwQrHmqKQplRl/view?usp=sharing). You will have to find the folder where the files have been installed and copy the "Vagrantfile" to the folder you previously chose, overwriting the existing "Vagrantfile" file. It will likely be the same folder your Command prompt was in at the time of the `vagrant init artemis` command.

The new Vagrantfile will set up the virtual machine with necessary virtualization settings.

### 2.3 Start the Virtual Machine

Next run the command:

```bash
$ vagrant up
```

#### Network Selection

If you are prompted to select a network option, just type in a number to select an option. Look for keywords such as _Wireless_ or _Ethernet_ for the appropriate selection, depending on your host computer's network connection. (If a list of options is not printed in the terminal, you may have an old and incompatible version of VirtualBox. Try checking if you need an update.)

After a minute or so should see the virtual machine boot. Login with the password below:

    username: vagrant
    password: vagrant



{% include image.html file="/resources/tutorials/setup/part2/vagrant_login.png" width="100%" %}

Open a terminal inside the virtual machine (<kbd>Control</kbd> + <kbd>Alt</kbd> + <kbd>T</kbd> or the
black box icon on the left-hand dock) and enter the following command:

```bash
$ sudo apt install virtualbox-guest-dkms virtualbox-guest-utils virtualbox-guest-x11
```

{% include important.html content="Copying and pasting will not work until after this step, so make sure
you type this command exactly as it appears!" %}

### 2.4 Reboot the Virtual Machine

Reboot the machine by returning to your host terminal and entering:

```bash
$ vagrant halt
$ vagrant up
```

In the future you should be able to start the virtual machine directly from the VirtualBox GUI, or you can continue
running `vagrant up` in the virtual machine folder.





### 2.5 Enable Useful Features
Once you have logged into the `vagrant` user again (default password is `vagrant`), you can enable some useful tools:

#### Automatic Display Resizing

This feature will resize the guest display when you adjust the size of the container window.

Click on the _View_ menu at the top of the virtual machine and click on `Auto-resize Guest Display`. If it is already
selected, then you should click on it again.

#### Shared Clipboard

This feature will allow you to copy and paste between the host and guest machines.

Click on the _Devices_ menu at the top of the virtual machine and click on _Shared Clipboard_ > _Bidirectional_.

{% include note.html content="When you paste text into a terminal you must use the
<kbd>Control</kbd> + <kbd>Shift</kbd> + <kbd>V</kbd> shortcut, and when you copy text from a terminal you must
use the <kbd>Control</kbd> + <kbd>Shift</kbd> + <kbd>C</kbd> shortcut." %}

#### Enabling USB in Virtual Machine

This section will allow you to use USB devices that are attached to your physical machine from the development environment. First, download the VirtualBox extension pack [here](https://download.virtualbox.org/virtualbox/6.1.18/Oracle_VM_VirtualBox_Extension_Pack-6.1.18.vbox-extpack).

When your download is complete, find the file and open it. This should give you a prompt in the VirtualBox program, so just follow the steps to install the extension.

{% include image.html file="/resources/tutorials/setup/part2/usb.png" width="40%" %}

After the install is complete, highlight the Development Environment and open the Settings menu. Select USB, click the box to _Enable USB Controller_, and select _USB 3.0_. If only _USB 1.0_ is available, the Extension Pack is not properly installed, so repeat this section.

Start the machine with your chosen USB device plugged in. After logging in and seeing the desktop, select _Devices/USB_ at the top of the window, and select the device you would like to access in the virtual environment (the device will not be accessible in your physical host machine after this step).

If you'd like to dismount the USB device from your VM, select the device in the _Devices_ menu again.

## 3. Update Software

From the virtual machine, open a new terminal (<kbd>Control</kbd> + <kbd>Alt</kbd> + <kbd>T</kbd>) and run the following command:


```bash
$ ./update
```

You will be prompted whether or not you want to update various components. Entering `y` will overwrite the existing
installations, if present.



## Further Reading
* [Artemis Development Environment]({{site.folder_docs_other}}/development-environment.html)
