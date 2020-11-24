---
title: Raspberry Pi Library
permalink: /pages/documentation/raspi-library/index.html
layout: page

keywords: python, library
---

> **_Note:_** this page serves as documentation for the Raspberry Pi Library. For a tutorial on writing payload scripts using this library, visit [Payload Script Tutorial Series]({{site.folder_tutorials_scripts}}/scripts1.html).

## Description
The Raspberry Pi Library is a Python package which provides access to the cubesat from the Raspberry Pi Zero onboard computer.


## Directory Structure

The Artemis library for the Raspberry Pi expects a particular directory structure, shown below. Note that the tilde (`~`)
character denotes the user's home folder.

```
~
├── logs
├── payload
├── python
│   └── ...
└── scripts
    └── ...
```

## Usage
To use the package, you only need one import line:

```python
from artemis import cubesat
```

## Classes
Below are the important modules included in this package.

* [CubeSat Class](cubesat-class.html)
* [BeagleBone Class](beaglebone-class.html)
* [Agent Class](agent-class.html)
