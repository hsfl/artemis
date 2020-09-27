---
title: COSMOS Tutorial Part 2 - Writing Agents
permalink: /pages/tutorials/cosmos/cosmos2.html
layout: series

tags: [software]
keywords: software
sidebar: home_sidebar
toc: false

series:
    language: "C++"
    prev: /pages/tutorials/cosmos/cosmos1.html
    next: /pages/tutorials/cosmos/cosmos3.html
---

{% capture tip %}Before you start this tutorial, you should check out the
[COSMOS documentation]({{site.folder_docs_cosmos}}/cosmos.html) for an explanation on the 
concepts used here.
{% endcapture %}
{% include tip.html content=tip %}


## Introduction

SimpleAgent is a class that encapsulates the regular [COSMOS agents]({{site.folder_docs_cosmos}}/cosmos.html#agents). While COSMOS agents can be difficult to use, SimpleAgent is designed with the user in mind. Here we'll be referring to SimpleAgent as an agent -- a SimpleAgent really is just a COSMOS agent; only the way you use it changes.


### SimpleAgent Devices
A SimpleAgent _device_ is a C++ object which can hold certain properties. The types of properties a device can have depend on the type of device. For example, a `Battery` device has a `capacity` property, but you can bet a `TemperatureSensor` device doesn't have a `capacity` property.

{% include note.html content="A SimpleAgent device does not handle hardware directly, and only stores properties.
Any hardware interaction with a _physical_ device is up to you to code." %}

{% capture tip %}
For a complete listing of available devices and their properties, visit the
[Device documentation]({{site.folder_docs_utility}}/simpleagent-devices.html).
{% endcapture %}
{% include tip.html content=tip %}

## Using SimpleAgent
Now that we've gotten definitions out of the way, we can start by creating a SimpleAgent.

### Creating the SimpleAgent
First, you'll need to include the header file with all of the SimpleAgent definitions:

```cpp
#include "SimpleAgent/SimpleAgent.h"
```

Next, you'll need to create a new `SimpleAgent` object in the main function (or elsewhere, as long as you create it before you use it):

```cpp
SimpleAgent *agent = new SimpleAgent("my_agent");
```

Here, we've created a new agent with the name `my_agent`. Make sure you _never_ create more than one SimpleAgent per program, as this will raise an exception.

We can then set how often our agent will perform its tasks by using the `SetLoopPeriod` function:

```cpp
agent->SetLoopPeriod(1.5)
```

The line of code above will set our agent to run at 1.5 second intervals. It's okay if your agent takes longer than this time to perform its tasks. This only really matters if your agent takes less than this time: the agent will wait until the appropriate time has passed before starting the next loop iteration.


### Adding Devices
Now that the agent is created, we can start loading it up with devices. You can have as many devices as you'd like, but in the example below we'll just add one `TemperatureSensor` device with the name `my_sensor`:

```cpp
TemperatureSensor *my_sensor = agent->NewDevice<TemperatureSensor>("my_sensor");
```

Next we can define properties we would like to post. You don't actually need to post any properties unless you want to access them externally.

```cpp
mysensor->Post(my_sensor->utc = Time::Now());
mysensor->Post(my_sensor->temperature);
```

The first line above assigns the current time to the sensor's `utc` property and posts it all in one go. You don't need to assign the value of a property immediately (although setting an initial value is recommended). The second line above demonstrates this by posting an uninitialized `temperature` property.

You can also set custom properties if your device doesn't already have the properties you want, as shown in the example below. Unfortunately due to limitations of COSMOS, these custom properties cannot currently be posted 😢.

```cpp
my_sensor->SetCustomProperty<bool>("is_initialized", true);
// ...
bool is_initialized = my_sensor->GetCustomProperty<bool>("is_initialized");
```

{% include important.html content="it is _very important_ that you retrieve the custom property
using the same type (`bool` in this case) you used to set it. If you don't do this,
then an exception _will_ be thrown." %}

If you find that a device you'd like to use isn't supported, you can always use the [CustomDevice]({{site.folder_docs_utility}}/simpleagent-devices.html#customdevice) device type. This device only supports a few post-able properties, but you can use as many custom properties as you wish.

### Setting Node Properties
For properties about the COSMOS node that don't fit into a device, you can use node properties:

```cpp
agent->SetNodeProperty<Node::UTC>(Time::Now());
Time utc = agent->GetNodeProperty<Node::UTC>();
```

### Finalizing Properties
Once you are done adding devices, device properties, and node properties, you should _finalize_ the agent. This just means that any properties that are posted will get handled properly. You can still set, get, or add properties as usual, but posting any new properties won't be handled properly unless you finalize the agent again. Finalizing the agent is just a simple function call:

```cpp
agent->Finalize();
```

### Viewing COSMOS Names
The names used internally by COSMOS are required for certain operations, such as for displaying properties in COSMOS Web or for making requests to other agents. You can see all of the names COSMOS uses (as well as previously-added requests) in SimpleAgent's convenient `DebugPrint` function:

```cpp
agent->DebugPrint()
```

### The Main Loop
The main loop of an agent is where all the agent's tasks are performed. The example below shows how the main loop should look:

```cpp
while ( agent->StartLoop() ) {
    // Perform tasks here...
}
```

The `StartLoop` function handles any waiting that may be necessary (e.g. if your agent performs its tasks faster than the time set by `SetLoopPeriod`), and whether or not the agent needs to shut down. After this loop you should probably wrap up any necessary hardware interaction, and also delete the SimpleAgent you've created:

```cpp
delete agent;
```


{% include important.html content="You should _never_ delete devices returned by the agent's
`NewDevice` function, as this will cause issues." %}

## Using Requests

### Adding Requests
A request function can take on one of two signatures (i.e. the form of the function):

1. `string MyRequestWithNoArguments()`
2. `string MyRequestWithArguments(vector<string> arguments)`

The first request takes no arguments, and returns a string indicating the response. The second request takes a vector of arguments and returns a string indicating the response. If you decide you need arguments in your request, for safety you should check that the number arguments and their types are correct.

You can add either type of request to the agent with the same function, and (optionally) provide a synopsis and detailed description of the request:

```cpp
agent->AddRequest("myrequest_1", MyRequestWithNoArguments, "A synopsis", "A detailed description");
agent->AddRequest("myrequest_2", MyRequestWithArguments);
```

The first line above adds the `MyRequestWithNoArguments` request using the name `myrequest_1`, and provides a synopsis and detailed description of the request. The second line adds the `MyRequestWithArguments` request using the name `myrequest_2`, and provides no synopsis or detailed description. Although providing the synopsis and detailed description strings is optional, it is good practice to use these.

You can add the same request under a variety of names (called request _aliases_) as long as one of these names isn't already taken by another request. There's actually a shorthand for this:

```cpp
agent->AddRequest({"alias_1", "alias_2", "alias_3"}, MyRequestWithArguments, "A synopsis", "A detailed description");
```

This will add our request function with the aliases `alias_1`, `alias_2`, and `alias_3`. You can add as many aliases as you wish and, as before, you can choose to omit the synopsis and detailed description strings.


{% include important.html content="The string returned from a request function should never be empty.
An empty response string is interpreted as failure to call the request. If you don't care about the value returned,
you can always just return a space character, or any other random non-empty string." %}

### Device Requests

You can also add requests to specific devices! For example, let's say we previously created a heater device named `heater`, and we want to add a request to it that either enables or disables the heater. The code for the request
might look like this:

```cpp
void DRequest_EnableHeater(Heater *some_heater, bool enabled) {
    if ( enabled ) {
        // Enable the heater here...
    }
    else {
        // Disable the heater here...
    }
}
```

Notice that device requests _must_ have the first argument as a pointer to the device they are acting on. This helps
makes your code flexible, especially if you are adding the same device request to many different devices.

To actually add the device request to the `heater` device, we can call the `heater` device's `AddRequest` function
inside of the main function:

```cpp

int main() {

    // ...

    // Create the heater device
    Heater *heater = agent->NewDevice<Heater>("my_heater");

    // Add our device request to the heater using the name "set_state"
    heater->AddRequest("set_state", DRequest_EnableHeater, "Sets the state of the heater");

    // ...
}
```


Now if we wanted to call this device request from a terminal (once the program is running), we could issue
the following command to enable the heater:

```bash
agent cubesat my_agent my_heater:set_state true
```

Notice that the format for calling a device request is `device_name:request_name <arguments>`.


### Calling a Request From the Terminal
Once your agent is running, you can call a previously-added request from a terminal. For example, if we've added a request called `my_request` to an agent called `my_agent` running on the node `cubesat`, we can run the following command to call this request (optionally providing arguments `argument1` and `argument2`, which get redirected to the request function):

```bash
$ agent cubesat my_agent my_request argument1 argument2
```

This will call the request function and print the string returned from the request.

To view a listing of all the requests available for the agent, you can run the following command:

```bash
$ agent cubesat my_agent
```

This will display all available requests in a nicely formatted table, along with their synopses and detailed descriptions if provided. Here is an example of the output from `agent_cpu`, a built-in agent:

```
    help 
            list of available requests for this agent

    help_json 
            list of available requests for this agent (but in json)

    shutdown 
            request to shutdown this agent

    idle 
            request to transition this agent to idle state

    init 
            request to transition this agent to init state

    monitor 
            request to transition this agent to monitor state

    run 
            request to transition this agent to run state

    status 
            request the status of this agent

    (clipped)
```

{% include note.html content="There are several requests used by COSMOS and SimpleAgent which are added by default.
Any requests that you add will be listed at the _bottom_ of this table." %}

## Communicating With Other Agents
When working with many agents, you will often need to send requests back and forth between agents running in separate programs. SimpleAgent provides a friendly way of doing this using the class `RemoteAgent`.

To find another agent you can use SimpleAgent's `FindAgent` function:

```cpp
static RemoteAgent other_agent = agent->FindAgent("other_agent", "cubesat")
```

In the code above, we attempt to find the agent named `other_agent` running on the node `cubesat`. You don't need to provide the node name; if the node name is omitted, then the node that our `agent` is running on will be used by default.

{% include note.html content="The `static` keyword is used here. This means that the variable `other_agent`
will be initialized _only once_ when the function containing this variable is called. If this keyword was not
included, the `FindAgent` function would be executed every time this code runs, and could possibly hang up your
program (the default timeout is 2 seconds). Unless you know what you're doing, the `static` keyword should
probably be used." %}


After calling the `FindAgent` function, you should check whether or not the remote agent was found:

```cpp
if ( other_agent.Connect() ) {
  // Do something here that depends on the other agent...
}
```

For safety, you should place any code that depends on the other agent existing inside of the `if` block as shown above.

### Getting Properties from Another Agent
After connecting to another agent, you can get retrieve its properties. To do this, you will need to know the unique COSMOS name of the property (we're working on making this easier). You can get the COSMOS name using the agent's `DebugPrint` function or built-in `print` request. In the example below, we retrieve the properties with COSMOS names `device_batt_temp_000` and `device_imu_temp_000` from another agent:

```cpp
auto values = other_agent.GetCOSMOSValues({"device_batt_temp_000", "device_imu_temp_000"});
```

This function returns an `unordered_map<string, Json::Value>` object, but we don't really care about this, so we can use the `auto` keyword to let the compiler infer which type we're using. We can get the actual values from the `values` variable using the COSMOS names:

```cpp
float batt_temp = values["device_batt_temp_000"].nvalue;
float imu_temp = values["device_imu_temp_000"].nvalue;
```

The `nvalue` member stands for _number value_, which is actually a `double` type. You can also use the `svalue` member for string values.

It's also a good idea to check whether the properties you want were actually returned by the `GetCOSMOSValues` function:

```cpp
float batt_temp = 0; // Set a fallback value in case the property isn't present
if ( values.find("device_batt_temp_000") != values.end() )
    batt_temp = values["device_batt_temp_000"].nvalue;

// Do something with batt_temp...
```

### Sending Requests
After connecting to another agent, you can also send requests to it. Besides being able to call SimpleAgent requests, you can also call the default COSMOS requests. In the example below we send a request to another agent:

```cpp
string response = other_agent.SendRequest("request_name", "argument_1", "argument_2");
```

The code above asks `other_agent` to execute a request with the name `request_name`, providing it with arguments `argument_1` and `argument_2`. The response of the request is stored into the variable `response`. You can provide as many arguments as you'd like, but you should make sure that they are string values (we're working on adding support for more types).

After calling a request, you should check whether the request was performed successfully by checking if the response string is empty:

```cpp
// Check if an error occurred
if ( response.empty() ) {
    // Handle the error
}
else {
    // Do something with the response string
    cout << "Got a response from the other agent: " << response << endl;
}
```

## Putting it all together

### Example 1
Here is a working example of an agent program:



{% highlight cpp linenos %}

#include "SimpleAgent/SimpleAgent.h"

using namespace std;
using namespace cubesat;

//! An agent request which returns whatever argument the user gives it
double Request_Double(double arg);

//! An agent request which returns whatever we put in. The "CapturedInput"
//! type allows the user to put in any string they wish (including spaces)
std::string Request_Repeat(CapturedInput input);

//! A device request attached to a temperature sensor. Returns
//! the temperature plus a given number
float Request_GetTemperature(TemperatureSensor *sensor, int x);



//! Our SimpleAgent object
SimpleAgent *agent;
//! Our temperature sensor device
TemperatureSensor *temp_sensor;


int main() {
	
	// Create the agent
	agent = new SimpleAgent("my_agent");
	
	// Add the Request_Repeat request using the name "repeat"
	agent->AddRequest("repeat", Request_Repeat);
	
	// Add the "Request_Double" request using aliases "double" and "twice"
	agent->AddRequest({"double", "twice"}, Request_Double, "Doubles a number");
	
	
	
	// Add a temperature sensor device
	temp_sensor = agent->NewDevice<TemperatureSensor>("temp_sensor");
	
	// Set the utc and temperature properties to zero and post them
	temp_sensor->Post(temp_sensor->utc = 0);
	temp_sensor->Post(temp_sensor->temperature = 0);
	
	// Add the Request_GetTemperature request to the temperature sensor with
	// aliases "gettemp" and "temp"
	temp_sensor->AddRequest({"gettemp", "temp"}, Request_GetTemperature);
	
	
	
	// Let the agent know all the devices have been set up
	agent->Finalize();
	
	// Show all of the properties and requests added
	agent->DebugPrint();
	
	// A counter which holds a dummy value for the temperature
	int i = 0;
	
	// Start running the agent
	while ( agent->StartLoop() ) {
		
		// Timestamp the device
		temp_sensor->utc = currentmjd();
		temp_sensor->temperature = i++;
	}
	
	return 0;
}



double Request_Double(double x) {
	return x * 2;
}
float Request_GetTemperature(TemperatureSensor *sensor, int x) {
	return sensor->temperature + x;
}
std::string Request_Repeat(CapturedInput input) {
	return input.input;
}

{% endhighlight %}

<br>

Here is the initial output of the agent program above:

```
------------------------------------------------------
COSMOS AGENT 'my_agent' on node 'cubesat'
Version 0.0 built on Sep 27 2020 20:58:16
Agent started at 2020-09-27 21:26:18
Debug level 1
------------------------------------------------------
Devices
|	| Device 'temp_sensor'
|	|	| Posted Properties
|	|	|	| Temperature (aka device_tsen_temp_000)
|	|	|	| UTC (aka device_tsen_utc_000)
|		| Requests
	|	|	| temp: (int) -> float
	|	|	| gettemp: (int) -> float
Requests
|	| Request 'twice': (double) -> double
|	| Request 'double': (double) -> double
|	| Request 'print': () -> std::string
|	| Request 'repeat': (CapturedInput) -> std::string
Node Properties

```


This output is all due to calling the `DebugPrint` function. All of the available COSMOS names are listed next to the property names (for example, `device_tsen_temp_000`). The `say_hi` request is also listed in this tree.

{% include note.html content="There are a couple requests, `getproperty` and `print`, that are added by default." %}

We can call the `say_hi` request externally from a terminal window by running:

```bash
$ agent cubesat my_agent say_hi
```

After running this command, the SimpleAgent will output `Hey there! (inside agent)`, and the output from the terminal window is

```bash
{"output": "Hey there! (outside agent)","status": "OK"}
```

This is a JSON-formatted string, and the actual output from the request is located under the `"output"` field.


## See Also
* [SimpleAgent Documentation]({{site.folder_docs_utility}}/simpleagent.html)
* [Device Documentation]({{site.folder_docs_utility}}/simpleagent-devices.html)
* [COSMOS Documentation]({{site.folder_docs_cosmos}}/cosmos.html)