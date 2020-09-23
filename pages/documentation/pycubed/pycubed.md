---
title: PyCubed Software
permalink: /pages/documentation/pycubed/pycubed.html
layout: page
sidebar: home_sidebar

tags: [software]
keywords: software
---


## Overview

The PyCubed board conveniently bundles the functionality of several cubesat subsystems into one board. Furthermore,
scripts for the PyCubed are written with CircuitPython, an open-source software implementation of Python 3 meant to run 
on a microcontroller, making its use easy for beginners.

In the Artemis cubesat, the PyCubed board functions as a secondary OBC and ISC during periods of low power.

## Folder Structure

The main script is located in the root directory on the PyCubed, under a file called `main.py`.
The Artemis-specific script files are located in the `artemis` package, while the PyCubed default
libraries are located in the `pycubed` package.
The directories for both packages are located in the root are placed in the root directory of the PyCubed.


## Mu and the REPL

The [Mu editor](https://codewith.mu/) provides a convenient serial monitor which can be used to communicate
with the board for testing. The REPL (read-evaluate-print loop) interface allows users to enter Python
code which is immediately executed on the PyCubed processor.


## See Also
* [PyCubed Website](http://pycubed.org/)
* [PyCubed Communication Protocol]({{site.folder_docs_other}}/pycubed-communication.html)