---
title: PyCubed Communication Protocol
permalink: /pages/documentation/pycubed/communication-protocol.html
layout: page

keywords: software
---


## Overview
A special serial communication protocol is used to communicate from software between the BeagleBone and PyCubed. Here, a packet of information is referred to as a _message_, and the format is as follows:

1. Each message starts with a syncword consisting of the character '$'. This is done to allow easier message synchronization for each receiver.
2. Following the syncword is a three-character identifier of the message type, followed by a comma.
3. Following the message type is a list of data elements, delimited by comma characters.
4. The last element is a checksum for the message, not including the preamble. The checksum takes up two regular hexadecimal digits.
5. Terminating the message is a newline character.

An example message (`CC` indicates the checksum):

```
$BST,y,n,n,CC
```

## Checksums and Loss Prevention
The two-byte checksum is a hexadecimal representation calculated from the transmitted message (not including the syncword, the three-character message type string, or the first comma). The checksum is used to validate the integrity of the message received. If the checksum received does not equal the one which appears in the message, the entire message is discarded, and the receiver waits until another syncword is read. Additionally, any message not precisely following the format in the table below is discarded.



## Types of Messages

Below are the default messages used. Note that the `CC` following each message corresponds to the two-byte checksum
field.

<br>

<table width="100%" align="center">
    <thead>
        <tr>
            <th>Type / Direction</th>
            <th>Format</th>
            <th>Arguments</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>BeagleBone Status<br>BB &rarr; PC</td>
            <td><code>$BST,x,x,x,CC</code></td>
            <td>
                <ol>
                    <li>[y/n] Successful startup</li>
                    <li>[y/n] Ready for power loss</li>
                    <li>[y/n] Kill radio transmission</li>
                </ol>
            </td>
        </tr>
        <tr>
            <td>PyCubed Status<br>PC &rarr; BB</td>
            <td><code>$PST,x,CC</code></td>
            <td>
                <ol>
                    <li>[y/n] BeagleBone shutdown requested</li>
                </ol>
            </td>
        </tr>
        <tr>
            <td>Radio Packet<br>PC &harr; BB</td>
            <td><code>$PKT,l,D,CC</code></td>
            <td>
                <ol>
                    <li>Packet length in bytes</li>
                    <li>Binary packet contents</li>
                </ol>
            </td>
        </tr>
        <tr>
            <td>IMU Data<br>PC &rarr; BB</td>
            <td><code>$IMU,yyyyMMddhhmmss,x,x,x,<br>x,x,x,x,x,x,x,x,x,CC</code></td>
            <td>
                <ol>
                    <li>Timestamp of reading</li>
                    <li>Acceleration x coordinate</li>
                    <li>Acceleration y coordinate</li>
                    <li>Acceleration z coordinate</li>
                    <li>Magnetic field x coordinate</li>
                    <li>Magnetic field y coordinate</li>
                    <li>Magnetic field z coordinate</li>
                    <li>Angular velocity  x coordinate</li>
                    <li>Angular velocity  y coordinate</li>
                    <li>Angular velocity  z coordinate</li>
                </ol>
            </td>
        </tr>
        <tr>
            <td>GPS Data<br>PC &rarr; BB</td>
            <td><code>$GPS,yyyyMMddhhmmss,x,x,x,x,<br>x,x,x,x,CC</code></td>
            <td>
                <ol>
                    <li>Timestamp of reading</li>
                    <li>[y/n] Indicates whether the GPS has a fix. No fix means the following data is discarded</li>
                    <li>Latitude in degrees</li>
                    <li>Longitude in degrees</li>
                    <li>Fix quality (0, 1, or 2)</li>
                    <li>Number of satellites used</li>
                    <li>Altitude in meters</li>
                    <li>Speed in meters per second</li>
                    <li>Azimuth in degrees</li>
                    <li>Horizontal dilution</li>
                </ol>
            </td>
        </tr>
        <tr>
            <td>Temperature Data<br>PC &rarr; BB</td>
            <td><code>$TMP,yyyyMMddhhmmss,x,x,CC</code></td>
            <td>
                <ol>
                    <li>Timestamp of reading</li>
                    <li>The CPU temperature in celsius</li>
                    <li>The battery temperature in celsius</li>
                </ol>
            </td>
        </tr>
        <tr>
            <td>Power Data<br>PC &rarr; BB</td>
            <td><code>$PWR,yyyyMMddhhmmss,x,x,x,x,CC</code></td>
            <td>
                <ol>
                    <li>Timestamp of reading</li>
                    <li>Battery voltage</li>
                    <li>Charge current in milliamps</li>
                    <li>System voltage</li>
                    <li>System current draw in milliamps</li>
                </ol>
            </td>
        </tr>
    </tbody>
</table>