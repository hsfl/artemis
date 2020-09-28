---
title: Heater Agent
permalink: /pages/documentation/agents/heater-agent.html

tags: [software, heater]
keywords: software

agent_name: agent_heater
---


## Description
The heater agent (AKA `agent_heater`) is an agent that handles the heater device. Should any temperatures fall too low, the heater agent will enable the heater. Later when the temperatures readings are sufficient, the heater agent will disable the heater. For the specific temperatures different events occur at, see the [temperature events table](#temperature-events)

The physical heater device is controlled using requests issued to the [switch agent](switch-agent.html) which, in turn, enables or disables the switched line for the heater.

All temperature values are retrieved from the [temperature sensor agent](temperature-sensor-agent.html).

## Temperature Events
Below is a table showing the temperatures various events occur at.

| Temperature (°C) |     Event      |
| ---------------- | -------------- |
|     10           | Heater Enable  |
|     20           | Heater Disable |

## Configuration

The JSON [configuration file](https://github.com/hsfl/artemis/blob/dev/software/BeagleBone/beaglebone/include/config/heaters.json) provides a method of altering the behavior of the agent. A list of sensors and their enable/disable
temperatures can be used to determine when the heater is enabled or disabled.

The default configuration using only the battery temperature sensor is shown below. Note that the `source` field
corresponds to the COSMOS temperature property of the sensor in question.

```json
{
	"name": "heater",
	"switch": "sw1",
	"pulse_time": 5,
	"sensors": [
		{
			"name": "temp_batt",
			"source": "device_tsen_temp_004",
			"enable_temp": 10,
			"disable_temp": 20
		}
	]
}
```