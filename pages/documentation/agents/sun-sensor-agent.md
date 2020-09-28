---
title: Sun Sensor Agent
permalink: /pages/documentation/agents/sun-sensor-agent.html
layout: agent

tags: [software, sunsensor]
keywords: software

agent_name: agent_sun
---


## Description
The sun sensor agent (aka `agent_sun`) is an agent that handles operations with the sun sensors. This includes initialization, configuration, and reading values from the sun sensors. Nothing is done with the values obtained from the sun sensors, but they are available for use elsewhere, such as in an ADCS agent (not included).

There are six sun sensors, with one located on each faces of the cubesat.

## Sensor Names
Below is a table showing which sensor names correspond to which physical devices.

| Sensor Name    | ID Number | Physical Device | PC104 Header Pin |
| -------------- | --------- | --------------- | ---------------- |
| `ss_plusx`     |     0     | +X Sun Sensor   |       TODO       |
| `ss_minusx`    |     1     | -X Sun Sensor   |       TODO       |
| `ss_plusy`     |     2     | +Y Sun Sensor   |       TODO       |
| `ss_minusy`    |     3     | -Y Sun Sensor   |       TODO       |
| `ss_plusz`     |     4     | +Z Sun Sensor   |       TODO       |
| `ss_minusz`    |     5     | -Z Sun Sensor   |       TODO       |

## Configuration

The JSON [configuration file](https://github.com/hsfl/artemis/blob/dev/software/BeagleBone/beaglebone/include/config/sun_sensors.json) provides a method of altering the behavior of the agent. This configuration file contains a list
of all sun sensors to be used and their properties, such as their names, I2C bus, device address, and physical
orientation. The default configuration is shown below:

```json
[
	{
		"name": "plus_x",
		"bus": 0,
		"address": 80,
		"orientation": [1,0,0]
	},
	{
		"name": "minus_x",
		"bus": 0,
		"address": 81,
		"orientation": [-1,0,0]
	},
	{
		"name": "plus_y",
		"bus": 0,
		"address": 82,
		"orientation": [0,1,0]
	},
	{
		"name": "minus_y",
		"bus": 0,
		"address": 83,
		"orientation": [0,-1,0]
	},
	{
		"name": "plus_z",
		"bus": 0,
		"address": 84,
		"orientation": [0,0,1]
	},
	{
		"name": "minus_z",
		"bus": 0,
		"address": 85,
		"orientation": [0,0,-1]
	}
]
```