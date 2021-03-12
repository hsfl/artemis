---
title: "Testing the Temperature Sensor"
layout: page
permalink: /pages/tutorials/testing/temp_sensor_test.html

tags: [software]
keywords: software
---

*****************

> What you will need:
>
>   * BeagleBone Black
>
>   * TMP36
>
>   * Breadboard
>
>   * Three Male to Male Jumper Cables

*****************

## Hardware Setup

The TMP36 is an analog temperature sensor that provides a voltage output directly proportionate to the temperature in Celsius. Since no external calibration is needed, we can connect the sensor to the BBB just through wires. It is good practice to setup wiring while the BBB is off. Using the breadboard, connect the temp sensor's source voltage pin to the 3.3V output (P9.3) on the BBB, the sensor's ground pin to the GNDA_ADC (P9.34) on the BBB and the sensor's output voltage pin to AIN1 (P9.40) on the BBB. The AIN pins on the BBB are analog to digital converters (ADC) that allow us to access the analog outputs from the sensor. Click this [link](https://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf) for the TMP36 datasheet. 

{% include image.html file="/resources/tutorials/sensor/File_001.png" width="70%" %}

In the image above, the teal wire connects the 3.3V voltage source, the blue wire corresponds to the ADC connection, and the orange wire connects the ground.

## Getting the Raw Voltage

To get the raw voltage outputted by the temp sensor, use the following commands:
```bash
$ cd /sys/bus/iio/devices/iio:device0
$ cat in_voltage1_raw
```
This code helps you navigate to the correct directory and display the contents of the ADC pin that is receiving data from the temp sensor. You should get a value that is around 1500.

## Writing the Program

The program used to get temperature readings will be in C++. Create a new file called tmp36.cpp.

```bash
$ sudo nano tmp36.cpp
```

Paste the following code into your tmp36.cpp file:

```bash
#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>

#define ADC_PATH "/sys/bus/iio/devices/iio:device0/in_voltage"
#define ADC 1

float getTemp(int adc_value) {
        float voltage = adc_value * (1.80/4096.0);
        float diff_degreesC = (voltage-0.75)/0.01;
        return (25.0 + diff_degreesC);
}

int readAnalog(int num) {
        stringstream ss;
        ss << ADC_PATH << num << "_raw";
        fstream fs;
        fs.open(ss.str().c_str(), fstream::in);
        fs >> num;
        fs.close();
        return num;
}

int main() {
        while(1){
                float temp = getTemp(readAnalog(ADC));
                float fahr = 32 + ((temp * 9)/5);
                cout << "C = " << temp << "\tF = " << fahr << endl;
                sleep(1);
        }
}
```
The getTemp() function accepts the raw voltage inputted on the ADC pin and returns the corresponding temperature in Celsius. The readAnalog() function accepts the ADC pin number (we are using AIN1 so the ADC pin number is 1) and returns the raw voltage inputted on that ADC pin. In the main() function we are continuously printing the current temperature in Celsuis and Fahrenheit with a one second wait in between each reading. 

The temperatures being printed should reflect any change in temperature. If you put your hand around the temp sensor to warm it up, the temperatures should also go up. When you remove your hand, you should see the temperatures go back down and eventually return to the room temp.

## Using Multiple Temp Sensors

When using more than one temperature sensor, you can use the same pins to power and ground all of the sensors, but each sensor must have their own ADC pin. 

In this part we will be setting up two temperature sensors on the BBB. Connect the source voltage pins on both temp sensors to the same BBB 3.3V pin (P9.3) and the same GNDA_ADC (P9.34). Keep one sensor connected to AIN1 (P9.40) and connect the second sensor to AIN2 (P9.37).

{% include image.html file="/resources/tutorials/sensor/File_000.png" width="70%" %}

In the picture above, the teal, blue, and orange wires are connected to the same things as before while the yellow wire corresponds to the second ADC connection.

To allow a user to choose which temp sensor they'd like to receive a reading from, we have to redefine the ADC variable based on what the user wants. 

Delete this line of code:

```bash
#define ADC 1
```

Inside the main function, declare ADC as an int.

```bash
int ADC;
```

Inside the while loop, add a request for user input and assign the input to the ADC variable.

```bash
cout << "Temp sensor #: ";
cin >> ADC;
```
Save and exit the file, then run the code. The program should request a temp sensor number and when 1 is inputted should display the temperature from the sensor connected to AIN1. When 2 is inputted as the temp sensor number, the program should output the reading from the sensor connected to AIN2.