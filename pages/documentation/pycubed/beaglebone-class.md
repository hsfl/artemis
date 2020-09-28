---
title: BeagleBone Class (PyCubed)
permalink: /pages/documentation/pycubed/beaglebone-class.html
layout: class

tags: [software]
keywords: software

obc: pycubed
class_name: beaglebone
---


## Overview

The BeagleBone class is used by the PyCubed flight software to communicate
with the BeagleBone OBC. It provides message parsers to implement one half
of the [PyCubed Communication Protocol](communication-protocol). Custom
messages can be implemented by adding message handlers or parsers.

## Message Parsers and Handlers


### Parsers
A _message parser_ in this class refers to a function that deals directly with
the CircuitPython UART object to read information from the BeagleBone.
This is useful for cases where it is necessary to send and receive binary data.
The expected signature of a message parser is shown below:

```python
def my_parser(uart, beaglebone)
```

Where `uart` is the CircuitPython UART object, and `beaglebone` is the BeagleBone
object calling the parser.

### Handlers

A _message handler_ in this class refers to a function that receives an array of
string arguments parsed from a typical message. The expected signature of a
message handler is shown below:

```python
def my_parser(args, beaglebone)
```

Where `args` an array containing the automatically-parsed message arguments,
and `beaglebone` is the BeagleBone object calling the parser.
