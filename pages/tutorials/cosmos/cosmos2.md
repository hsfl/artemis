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
A SimpleAgent _device_ is a C++ object which can hold certain properties. In this tutorial, the devices aren't real. We make them up to understand how the concepts can be used for real devices and requested for any data we need to know about the satellite.

The types of properties a device can have depend on the type of device. For example, a `Battery` device has a `capacity` property, while a `TemperatureSensor` device has a `temperature` property.

{% include note.html content="A SimpleAgent device does not handle hardware directly, and only stores properties.
Any hardware interaction with a _physical_ device is up to you to code." %}

{% capture tip %}
For a complete listing of available devices and their properties, visit the
[Device documentation]({{site.folder_docs_utility}}/simpleagent-devices.html). These can be used in the agent, such as `TemperatureSensor`.
{% endcapture %}
{% include tip.html content=tip %}

## Using SimpleAgent
Now that we've gotten definitions out of the way, we can start by creating a SimpleAgent.

### Creating the SimpleAgent
First, you'll need to include the header file with all of the SimpleAgent definitions (make sure to always type in code exactly as it appears here):

```cpp
#include "SimpleAgent/SimpleAgent.h"
```

The above line should already be in your file. If not, add it to the very top. Next you'll see the following:

```cpp
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
```

The first two lines you see help the agent to be compatible with COSMOS. The line starting with `double` (and the two following it) is a function, which when called will perform the action in the comment. This will make sense when we test it out.

Next, you'll need to create a new `SimpleAgent` object under the corresponding comment.

{% include note.html content="Everything you have to add to the file will have a corresponding comment. Good practice is to have plenty of comments so your code is easily readable. Type in the code on the line below the comment." %}

This can go above the main function (or elsewhere, as long as you create it before you use it):

```cpp
SimpleAgent *agent;
```

Make sure you _never_ create more than one SimpleAgent per program, as this will raise an exception.

Now we can move into our `int main()` function. Ignore the `temperature sensor device` for now.

We have created our agent, but now we need to define it under `// Create the agent`:

```cpp
agent = new SimpleAgent("my_agent");
```

Now, `my_agent` can be used to run this agent. 

We can then set how often our agent will perform its tasks by using the `set_activity_period` function:

```cpp
agent->set_activity_period(1.5);
```

You can add this line right below the `agent = new SimpleAgent...` line. The line of code above will set our agent to run at 1.5 second intervals. It's okay if your agent takes longer than this time to perform its tasks. This only really matters if your agent takes less than this time: the agent will wait until the appropriate time has passed before starting the next loop iteration (repeating the task).

{% include note.html content ="Each task will be performed every loop period. When we call a request, we are asking for the current output of that request." %}


### Adding Devices
Now that the agent is created, we can start loading it up with devices. You want to add a device to your agent for the type of data that the agent will be monitoring. In this example below, we are monitoring temperature so we want to add a temperature sensor device to our agent. 
You can have as many devices as you'd like, but in the example below we'll just add one `devicestruc` device with the name `temp_sensor` (above the `main` function, right under `//! Our temperature sensor`):

```cpp
devicestruc *temp_sensor;
```

Back in our main function, we can define our temperature sensor device under `//! Add a temperature sensor device`:

```cpp
int32_t error = 0; 
temp_sensor = agent->add_device("temp_sensor", DeviceType::TSEN, error);
if(error < 0) {
    printf("Error adding device temp_sensor\n"); 
}
```
Here, `devicestruc` is a COSMOS device struct that we use and name `temp_sensor`.

We define an `error` value for error checking throughout the program and pass it by reference to `add_device()` as the third argument. After the function call we ensure the device was properly added by verifying the value of `error`. If `error` is not negative, then we know everything is running smoothly. 

The second argument to `add_device()` is the type of device we will be monitoring. Some of supported devices are: 

| Device Type | Description               |
|-------------|---------------------------|
| PLOAD       | Payload                   |
| SSEN        | Sun Sensor                |
| IMU         | Inertial Measurement Unit |
| CPU         | Processing Unit           |
| BATT        | Battery                   |
| HTR         | Heater                    |
| SWCH        | Switch                    |
| TSEN        | Temperature Sensor        |

For more documentation and supported device types, see COSMOS Docs. [insert link]

Next we can define properties we would like to post to the agent's state of health (SOH) messages. Adding properties to the SOH allows us to monitor the specified data the agent is monitoring. 
In the following example, we use the `append_soh_list()` to add our device properties to the SOH. Here, we want to add the temperature value and a timestamp (UTC) for this device to our SOH. 

```cpp
agent->append_soh_list("temp_sensor", {"utc","temp"}); 
```

The first argument to `append_soh_list` is name of the device, here it is `"temp_sensor"`.
The second argument takes a `vector<string>` which represents a list of device property names. All device types support the properties: `utc, volt, amp, power, temp`. Each specific `DeviceType` supports specific properties to that device. For more specific device properties, see COSMOS Docs. [insert link]

### Finalizing Properties
Once you are done adding devices and device properties you should _finalize_ the agent with `set_soh()`. This just means that any properties that are posted will get handled properly and added to your agent's SOH. You can still set, get, or add properties as usual, but you'll have to _finalize_ the agent again. Finalizing the agent is just a simple function call:

```cpp
// Let the agent know all the devices have been set up
agent->set_soh();
```

### Updating Properties 

Ok, we've added our devices, we've added our device properties to the SOH. Now I'll demonstrate how to set the value of these properties: 

```cpp
temp_sensor->utc = 0; 
temp_sensor->temp = 273.15;
```

Assigning values to your device automatically updates the agent's data that will show up in the SOH. We previously defined `temp_sensor` as a `devicestruc*` when we made the call to `add_device()` so the values are linked to the agent. 

### Setting Up the "while" Loop

Next, we'll write a loop that will perform our tasks repeatedly (every loop period) until we tell them to stop. Write the following line below `// Start Running the Agent`:

```cpp
while ( agent->StartLoop() ) {

}
```

Now, we can add in some repeating actions. Add in the three lines, the first above `while`, and the other lines __inside the curly brackets__:

```cpp
// A counter which holds a dummy value for the temperature
int i = 0;

...

// Timestamp the device
temp_sensor->utc = currentmjd();
temp_sensor->temp = i++;
```

Now, the sensor will keep track of the MJD time as the agent is running, and the temperature will just increase by 1 every loop period (`i++` = `i+1`).

Now, add a `delete agent;` and a `return 0;` after the `while` loop to end our main function. 

{% include important.html content="You should _never_ delete devices returned by the agent's
`NewDevice` function, as this will cause issues." %}

We delete the agent after we're done with it, but we can get it back anytime by running `my_agent`.

{% include important.html content="There should be a closing curly bracket right above `double Request_Double(double x)`. This indicates the end of the `main` function. Make sure your `return 0;` is above this." %}


## Using Requests

### Adding Requests

A request function can take on one of two signatures (i.e. the form of the function):

1. `string MyRequestWithNoArguments(int32_t &error)`
2. `string MyRequestWithArguments(vector<string> &arguments, int32_t &error)`

Notice both forms take in an argument that is a reference to an `error` value. Error checking is necessary to keep anyone from crashing your agent through a request. Both forms also return a string, which is the response of that request. 
The first request form is for a request that takes no arguments. The second request takes a vector of arguments. If you decide you need arguments in your request, for safety you should check that the number arguments and their types are correct.

For example, on line 15 there is a request in the form of number 2 above, with one argument. 

You can add either type of request to the agent with the same function `add_request`, and provide a usage string and detailed description of the request:

```cpp
agent->add_request("myrequest_1", MyRequestWithNoArguments, "", "A detailed description");
agent->add_request("myrequest_2", MyRequestWithArguments, "arg1 arg2", "Description of my request");
```

The `add_request()` function takes 4 arguments:
1. name of the request, how the request will be called 
2. the function that is run when the request is called 
3. a list of the argument format
4. a description of what the request does. 

The first line above adds the `MyRequestWithNoArguments` request using the name `myrequest_1`, and provides an empty string and detailed description of the request. The second line adds the `MyRequestWithArguments` request using the name `myrequest_2`, and provides usage showing two arguments, and a description. 

Here is a more detailed example of a request function with arguments. Say we have a request `request_add` that will take two arguments and return the sum of the two arguments. We define the request function as follows: 
```cpp
string request_add(vector<string> &args, int32_t &error) {
     if(args.size() < 2){
     	error = ErrorNumbers::COSMOS_GENERAL_ERROR_ARGS; 
	return "usage arg1 arg2"; 
     }
     int arg1 = stoi(args[0]); 
     int arg2 = stoi(args[1]); 
     int sum = arg1 + arg2;
     return to_string(sum); 
}
```
Notice at the beginning of the function we check that the correct arguments are passed. In this case, to indicate error, `error` must be set to a negative value. We must be careful to check the arguments before accessing them, to prevent a segmentation fault, which will end up crashing your whole agent program! More about Cosmos Error Numbers [Here](https://hsfl.github.io/cosmos-docs/pages/4-tutorials/concepts/errors.html)

Since the arguments come in as strings, we need to parse them as `int`, which can be done by using `stoi()` (which is just short for 'string to integer'). And the return value, we cast back to a string with the `to_string()` function. 

Adding our `request_add` request to our agent within the main() of the agent:

```cpp

agent->add_request("add", request_add, "num1 num2", "returns the sum of two numbers");

```

Notice the third argument `"num1 num2"` tells our user that the request will take in two numbers as arguments 

### Calling a Request From the Terminal

We are now ready to run the agent. First, build the project by clicking the hammer icon in the bottom left of QtCreator. It may take a minute to finish. When it does, go to the _Projects_ tab and find the build directory of the `simpleagent_template` project. Open a terminal, navigate to that directory, and run the command below:

```bash
$ my_agent
```


Once your agent is running, you can call a previously added request from a terminal. For example, if we've added a request called `my_request` to an agent called `my_agent` running on the node `cubesat`, we can run the following command to call this request (optionally providing arguments `argument1` and `argument2`, which get redirected to the request function):

```bash
$ agent cubesat my_agent add 3 9
```

This will call the request function and print the string or number returned from the request.

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

Type in the `agent cubesat my_agent` to see the available requests, including the ones we've added. To use the `gettemp` request, type the following command:

```bash
$ agent cubesat my_agent temp_sensor:gettemp 0
```

The `temp_sensor:gettemp` part is the syntax for a device request. If you remember how the function was defined, it asked for both the sensor name and an `int x`, and it adds this `x` to the temperature. The output will be the current temperature plus `x` (0 in this case). You can type in any integer, but remember to subtract it to get the actual value. 

Call that request a few more times, and you'll get different values as time passes.

Now you can try our other requests. Type in the following:

```bash
$ agent cubesat my_agent double 3.14
```

The output will be 2 times the number you enter, so try a few more numbers to see what `double` can do. Try to figure out how to use the `repeat` request on your own (hint: a string is any set of characters and spaces). 

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

## Putting it all together

### Example 1
Here is a working example of an agent program:



{% highlight cpp linenos %}

#include "SimpleAgent/SimpleAgent.h"

using namespace std;
using namespace cubesat;

//! An agent request which returns whatever argument the user gives it
string Request_Double(vector<string> &arguments, int32_t &error);

//! An agent request which returns whatever we put in. 
string Request_Repeat(vector<string> &arguments, int32_t &error);

//! A device request attached to a temperature sensor. Returns
//! the temperature plus a given number
string Request_GetTemperature(vector<string> &arguments, int32_t &error);



//! Our SimpleAgent object
SimpleAgent *agent;
//! Our temperature sensor device
devicestruc *temp_sensor;


int main() {
	
	// Create the agent
	agent = new SimpleAgent("my_agent");
	agent->SetLoopPeriod(1.5);
	
	// Add the Request_Repeat request using the name "repeat"
	agent->add_request("repeat", Request_Repeat, "arg1", "Returns whatever is inputted");
	
	// Add the "Request_Double" request using aliases "double" and "twice"
	agent->add_request({"double", "twice"}, Request_Double, "arg1", "Doubles a number");
	
	
	
	// Add a temperature sensor device
	int32_t error = 0; 
	temp_sensor = agent->add_device("temp_sensor", DeviceType::TSEN, error);
	if(error < 0) {
		printf("Error adding device temp_sensor\n"); 
	}

	
	// Set the utc and temperature properties to zero and post them
	agent->append_soh_list("temp_sensor", {"utc","temp"}); 
	agent->set_soh();
	temp_sensor->utc = 0; 
	temp_sensor->temp = 273.15;

	
	// Add the Request_GetTemperature request to the temperature sensor with
	// aliases "gettemp" and "temp"
	temp_sensor->add_request({"gettemp", "temp"}, Request_GetTemperature, "arg1 arg2", "Gets temperature reading from sensor");
	
	
	
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
		temp_sensor->temp = i++;
	}
	
	delete agent;
	return 0;
}



string Request_Double(vector<string> &args, int32_t &error) {
    if(args.size() < 1){
     	error = ErrorNumbers::COSMOS_GENERAL_ERROR_ARGS; 
	return "usage arg1"; 
     }
     int arg1 = stoi(args[0]); 
     int double = arg1 * 2;
     return to_string(double); 
}
string Request_GetTemperature(vector<string> &args, int32_t &error) {
    if(args.size() < 2){
     	error = ErrorNumbers::COSMOS_GENERAL_ERROR_ARGS; 
	return "usage arg1 arg2"; 
     }
     int arg2 = stoi(args[1]); 
     int sum = arg1->temperature + arg2;
     return to_string(sum); 
}
string Request_Repeat(vector<string> &args, int32_t &error) {
    if(args.size() < 1){
     	error = ErrorNumbers::COSMOS_GENERAL_ERROR_ARGS; 
	return "usage arg1"; 
     }
     int arg1 = stoi(args[0]); 
     return to_string(arg1); 
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



## Advanced 

### Custom Properties (Work-in-Progress)

You can also set custom properties if your device doesn't already have the properties you want, as shown in the example below. Unfortunately due to limitations of COSMOS, these custom properties cannot currently be posted.

```cpp
my_sensor->SetCustomProperty<bool>("is_initialized", true);
// ...
bool is_initialized = my_sensor->GetCustomProperty<bool>("is_initialized");
```

{% include important.html content="it is _very important_ that you retrieve the custom property
using the same type (`bool` in this case) you used to set it. If you don't do this,
then an exception _will_ be thrown." %}

### Custom Devices

If you find that a device you'd like to use isn't supported, you can always use the [CustomDevice]({{site.folder_docs_utility}}/simpleagent-devices.html#customdevice) device type. This device only supports a few post-able properties, but you can use as many custom properties as you wish.

### Setting Node Properties

For properties about the COSMOS node that don't fit into a device, you can use node properties:

```cpp
agent->SetNodeProperty<Node::UTC>(Time::Now());
Time utc = agent->GetNodeProperty<Node::UTC>();
```

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

Here's an example for connecting to `propagator_simple`, an orbital simulation that outputs time, position, velocity, and magnetic field of a satellite in orbit:

```cpp
    // other agents
    static RemoteAgent propagator_simple = agent->FindAgent("propagator_simple","cubesat1");
    if ( propagator_simple.Connect() ) {
        cout << "propagator_simple is connected!" << endl;
    }


	
	// Let the agent know all the devices have been set up
	agent->Finalize();
```

The node `cubesat1` is one used in COSMOS core. Now, save your file, build your project, and open 2 terminals. In the first, write the following command:

```bash
$ propagator_simple cubesat1 0
```

The program should boot up, and every second a new line will show up as the output. With this terminal running, start `my_agent` in the other terminal. If you see `"propagator_simple is connected!"` then you have successfully linked with another agent! Go ahead and explore this more, trying it with other agents as you like. 

For safety, you should place any code that depends on the other agent existing inside of the `if` block as shown above.

### Getting Properties from Another Agent
After connecting to another agent, you can get retrieve its properties. To do this, you will need to know the unique COSMOS name of the property (we're working on making this easier). You can get the COSMOS name using the agent's `DebugPrint` function or built-in `print` request. In the example below, we retrieve the properties with COSMOS names `device_batt_temp_000` and `device_imu_temp_000` from another agent:

```cpp
auto values = other_agent.GetCOSMOSValues({"device_batt_temp_000", "device_imu_temp_000"});
```

This function returns an `unordered_map<string, Json::Value>` object, but we don't really care about this, so we can use the `auto` keyword to let the compiler infer which datatype we're using. We can get the actual values from the `values` variable using the COSMOS names:

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

Then, you can request the value of `batt_temp` while the agents are running, and if you still get a 0 you'll know something went wrong.

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
    cout << "An error occured!" << endl;
}
else {
    // Do something with the response string
    cout << "Got a response from the other agent: " << response << endl;
}
```




## See Also
* [SimpleAgent Documentation]({{site.folder_docs_utility}}/simpleagent.html)
* [Device Documentation]({{site.folder_docs_utility}}/simpleagent-devices.html)
* [COSMOS Documentation]({{site.folder_docs_cosmos}}/cosmos.html)
