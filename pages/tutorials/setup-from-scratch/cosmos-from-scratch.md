---
title: Installing COSMOS From Scratch
permalink: /pages/tutorials/setup-from-scratch/cosmos-from-scratch.html
layout: page

tags: [software]
keywords: software

---


# Introduction

If you want to install COSMOS without using the [development environment](https://hsfl.github.io/artemis/pages/tutorials/setup/setup2.html), you can always install COSMOS from scratch. This allows you to build your own virtual machine and use it as you choose, without the preconfigured settings included in the Vagrant box. If you are running a Linux machine, you can skip the steps below for "Creating the Virtual Machine". If you are on Windows or MacOS, it is recommended that you follow all the steps for ease of compatibility with COSMOS and your machine. In this case, your computer will be the __host__, and the virtual machine will be the __guest__.

## Creating the Virtual Machine

The first step to installing COSMOS on your own (without the prebuilt Vagrant box) is to create your own VirtualBox machine. A virtual machine is essentially an operating system within your computer's local host OS that allows you to perform software tasks on a guest machine separate from your own. To do this, there are a few dependencies to download:

  1. [Oracle VirtualBox](https://www.virtualbox.org/)
  2. [7-Zip](https://www.7-zip.org/)
  3. [Ubuntu 18.04.3](https://www.osboxes.org/ubuntu/)

{% include image.html file="/resources/tutorials/from scratch/cosmos from scratch/bionic_beaver.png" width="60%" %}

> Be sure to choose the correct OS for downloads 2 and 3 above (host computer). VirtualBox and 7Zip include install wizards to make things easy, just follow the steps and the wizard will do all the hard work for you. Make sure you have all 3 downloaded before moving on!

Now that you have your dependencies, you can unzip the Ubuntu disk image. Open your file explorer and find the Ubuntu file you just downloaded (probably in __Downloads__). Right-click on the file and click __7-Zip -> Extract files...__ and choose a location you will remember. It isn't of particular importance where you decide to save it, but once it is saved, you won't be able to move it without changing the filepath later.

{% include image.html file="/resources/tutorials/from scratch/cosmos from scratch/extract.png" width="50%" %}

Once the file is done extracting, you are ready to build the virtual machine. Start the Oracle VirtualBox program and click the blue "New" icon. This will bring up a new window where you can name your VM and define the OS type you are using. You can name the VM whatever you want, but use the picture below as a guide.

{% include image.html file="/resources/tutorials/from scratch/cosmos from scratch/machine_setup1.png" width="75%" %}
{% include image.html file="/resources/tutorials/from scratch/cosmos from scratch/machine_setup2.png" width="75%" %}

Make sure you select __Ubuntu (64bit)__, or you will have errors with compatibility. After clicking next, you will have to select a "virtual hard disk". This is the file you extracted in the previous step. Select _Use an existing virtual hard disk file_ and click on the little folder icon. Find the file you extracted (wherever you extracted it to), and double click. The next page asks you to choose how much memory will be used by the VM. You can select any number within the green area, but it is recommended to use at least 2000 Mb. Click __Next__, and you have just created the virtual machine!

Before booting the VM, some settings need to be changed.

{% include image.html file="/resources/tutorials/from scratch/cosmos from scratch/VB_machines.png" width="75%" %}

Click the __Settings__ icon to reconfigure the VM. First, in the __General__ tab, click __Advanced__, and for both __Shared Clipboard__ and __Drag'n'Drop__ select __Bidirectional__.

In the __Display__ tab, slide the __Video Memory__ indicator all the way to the right. 

Finally, in the __Storage__ tab, make sure there is a small CD icon with __Empty__ next to it. If it says anything else next to the CD icon, right-click and remove it, then click the small CD icon with a green plus sign and select __Leave Empty__. This is important for the next section. 

{% include image.html file="/resources/tutorials/from scratch/cosmos from scratch/VB_guestadditions.png" width="75%" %}

After making all of the changes, you can close the __Settings__ window and start your machine using the green arrow icon.

## Booting up the VM

When the VM is starting up, you will see something like this:

{% include image.html file="/resources/tutorials/from scratch/cosmos from scratch/machine_startup.png" width="75%" %}

It will take a few minutes the first time. You will see a screen like this:

{% include image.html file="/resources/tutorials/from scratch/cosmos from scratch/login_screen.png" width="75%" %}

You will need to log in to the machine as if you were starting up your host computer. The default password is shown below.

    username: osboxes.org
    password: osboxes.org

After logging in and a couple more minutes, you will see a desktop screen with icons on the left toolbar. Press <kbd>Ctrl</kbd> + <kbd>Alt</kbd> + <kbd>T</kbd> to open up a new terminal.

{% include note.html content="Try not to have too many windows open or switch between the VM window and other windows on your host computer while the VM is running. The VM can, at times, use as much RAM as your host computer on its own, and it may not handle multiple processes well." %}

In the terminal, type in the following command to ensure some vital extensions are included in your guest machine's OS:

```bash
$ sudo apt install dkms build-essential linux-generic-headers
```

Give your machine a minute to install these files. When it is finished, you can set up Guest Additions, which is important for everything that we will do in the virtual machine. 

To start the process, click __Devices__ in the top toolbar and select _Insert Guest Additions CD Image_. You will be prompted to reenter the password, and after doing so a terminal will open. A few processes will run, and then the terminal will ask if you would like to continue. Type `yes` and hit enter, and the installation will continue. When it is finished, the last line in the terminal will say "Press Return to close the window".

The virtual machine is now ready for working on software.

## Installing the Development Tools

Next, a few tools are needed to develop with COSMOS agents. Most of them will be installed using the terminal.

The first tool we will add is called __git__. This tool allows you to easily clone repositories from Github and to manage different updates and versions of the code. Type in the command below:

```bash
$ sudo apt install git
```

The install make take a couple minutes, and watch out for prompts to continue. These statements will appear in the terminal, ending in a parenthesis statement `(y/n)`. Be sure to type `y` and hit enter, including for any of the following terminal installs in this tutorial. After the process is finished, try typing in `git`. You should see an output like below.

    usage: git [--version] [--help] [-C <path>] [-c <name>=<value>]
           [--exec-path[=<path>]] [--html-path] [--man-path] [--info-path]
           [-p | --paginate | --no-pager] [--no-replace-objects] [--bare]
           [--git-dir=<path>] [--work-tree=<path>] [--namespace=<name>]
           <command> [<args>]

    These are common Git commands used in various situations:

    start a working area (see also: git help tutorial)
      clone      Clone a repository into a new directory
      init       Create an empty Git repository or reinitialize an existing one

    work on the current change (see also: git help everyday)
      add        Add file contents to the index
      mv         Move or rename a file, a directory, or a symlink
      reset      Reset current HEAD to the specified state
      rm         Remove files from the working tree and from the index

    examine the history and state (see also: git help revisions)
      bisect     Use binary search to find the commit that introduced a bug
      grep       Print lines matching a pattern
      log        Show commit logs
      show       Show various types of objects
      status     Show the working tree status

    grow, mark and tweak your common history
      branch     List, create, or delete branches
      checkout   Switch branches or restore working tree files
      commit     Record changes to the repository
      diff       Show changes between commits, commit and working tree, etc
      merge      Join two or more development histories together
      rebase     Reapply commits on top of another base tip
      tag        Create, list, delete or verify a tag object signed with GPG

    collaborate (see also: git help workflows)
      fetch      Download objects and refs from another repository
      pull       Fetch from and integrate with another repository or a local branch
      push       Update remote refs along with associated objects

    'git help -a' and 'git help -g' list available subcommands and some
    concept guides. See 'git help <command>' or 'git help <concept>'
    to read about a specific subcommand or concept.

If you see this, git has installed successfully.

Next, we will install Qt Creator. This is a program that allows for easy viewing and editing of code, and for compiling the COSMOS projet as well. Type in the command below to install Qt Creator.

```bash
$ sudo apt install qtcreator
```

Before moving on, let's make sure the Qt program boots up. In the terminal, enter `qtcreator` and wait for the window to pop up. Once it opens, go ahead and close it again. Our next tool is called CMake. This tool is used by Qt to compile the flight software project. This program can actually be installed in the Ubuntu software store.

{% include important.html content="Be careful of installing CMake from the terminal! In the past, older versions of CMake have been installed, which can cause issues with Qt Creator. It is recommended (and much easier) to install from the Software Shop, which automatically chooses the newest released version." %}

On the toolbar, you should have an orange icon called __Ubuntu Software__. Open that, and search for CMake. the correct choice will be the first on the list. Go ahead and hit install, and when it is finished you can close the window. 

{% include image.html file="/resources/tutorials/from scratch/cosmos from scratch/cmake.png" width="100%" %}

Qt Creator will now be able to build our project software, so it can be installed. 

## Cloning COSMOS Software

First, we can clone the COSMOS core repository. This repo is the basis for the Artemis flight software, but Artemis has a different set of agents. COSMOS core can be used to understand how agents work. Enter the command below in a terminal to download the installer.

```bash
$ git clone https://github.com/hsfl/cosmos-installer.git ~/cosmos
```

This will save the downloaded files to a folder called "cosmos". You will need to move into that folder to run the installer script, which will give you access to all the files in the COSMOS core repository. If you type `ls`, you should see the "cosmos" folder listed. If you see it, you can run the installer script:

```bash
$ cd ~/cosmos
$ ./cosmos-install.sh
```

After a couple minutes, the install should be finished. Check the file explorer for a folder called "bin" inside the "cosmos" folder. If you don't see this folder, there may be an issue with CMake. Try removing the files, reinstalling CMake, and following the steps above again. 

Now we can add the Artemis repo. This contains all the COSMOS agents that will be used for this specific cubesatellite.

```bash
$ cd
$ git clone https://github.com/hsfl/artemis.git artemis
```

There is no installer for the Artemis repo, so you are already set up! We have installed quite a few different tools and files, so it is a good idea to reboot the machine. Hit the red X at the top right of the window, and select _Power off the machine_.

Start up the virtual machine again and login. Open a terminal and move into the "cosmos" folder with `cd cosmos`. Type in `agent`, and you should see an output like below:

    Usage: agent [ list | dump [soh, beat, ###] | node_name agent_name "request [ arguments ]" ]

This means that COSMOS is installed correctly! Go ahead and try the same in the "artemis" folder, and you should get the same result.

## Compiling COSMOS Locally

In Qt Creator, click on _File > Open File or Project..._, and open up the file `~/cosmos/source/core/CMakeLists.txt`.

Once the project is finished loading, click the __Projects__ button on the left side of the window, and then click
on __Desktop__, and then click on __Build__ under it.

Make sure the build directory looks something like:

```
/home/cosmos/source/core/build-core-Desktop-Debug
or
/home/artemis/software/BeagleBone/build-beaglebone-Desktop_Qt_5_15_0_GCC_64bit-Debug
```

{% include image.html file="/resources/tutorials/from scratch/cosmos from scratch/qt_project.png" width="100%" %}

Now you can press <kbd>Control</kbd> + <kbd>B</kbd> (or the hammer icon at the bottom left) to build the project.
This can take a while.

All of the executables (files that can be run) are now located in the build directory from above. They are nested in a bunch of different folders,
but we need to put them together all in the same folder. To do so, run the following command in a terminal:

```bash
$ cd /home/cosmos/source/core/build-core-Desktop-Debug
$ mkdir bin
$ find ./ -perm /a+x -exec cp {} bin \;
```

You can also replace the first command with the filepath for the Artemis project. It is easiest to copy the path in the __Project__ tab of Qt and paste it in for this command.

Now you can copy the contents of the `/home/cosmos/source/core/build-core-Desktop-Debug/bin` folder to the `/home/cosmos/bin` folder in a file explorer. There will be a bunch of files already in the destination folder, but you can remove the old ones.