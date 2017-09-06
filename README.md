<<<<<<< HEAD
---
services: iot-hub
platforms: C
author: Ryan
---

# IoT Hub Raspberry Pi 3 Client application
[![Build Status](https://travis-ci.com/Azure-Samples/iot-hub-c-raspberrypi-client-app.svg?token=5ZpmkzKtuWLEXMPjmJ6P&branch=master)](https://travis-ci.com/Azure-Samples/iot-hub-c-raspberrypi-client-app)

> This repo contains the source code to help you get started with Azure IoT using the Microsoft IoT Pack for Raspberry Pi 3 Starter Kit. You will find the [full tutorial on Docs.microsoft.com](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-raspberry-pi-kit-c-get-started).

This repo contains an arduino application that runs on Raspberry Pi 3 with a CC2650 SensorTag temperature, humidity, barometer and luxometer sensor, and then sends these data to your IoT hub. 

## Set up your Pi
### Enable SSH on your Pi
Follow [this page](https://www.raspberrypi.org/documentation/remote-access/ssh/) to enable SSH on your Pi.

## Running this sample
### Install Azure IoT SDK
Install all packages by the following command:

```bash
grep -q -F 'deb http://ppa.launchpad.net/aziotsdklinux/ppa-azureiot/ubuntu vivid main' /etc/apt/sources.list || sudo sh -c "echo 'deb http://ppa.launchpad.net/aziotsdklinux/ppa-azureiot/ubuntu vivid main' >> /etc/apt/sources.list"
grep -q -F 'deb-src http://ppa.launchpad.net/aziotsdklinux/ppa-azureiot/ubuntu vivid main' /etc/apt/sources.list || sudo sh -c "echo 'deb-src http://ppa.launchpad.net/aziotsdklinux/ppa-azureiot/ubuntu vivid main' >> /etc/apt/sources.list"
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys FDA6A393E4C2257F
sudo apt-get update
sudo apt-get install -y azure-iot-sdk-c-dev cmake libcurl4-openssl-dev git-core
git clone git://git.drogon.net/wiringPi
cd ./wiringPi
./build
```
### Build the sample code
Build the sample code by the following command:

```bash
cmake . && make
```

### Run your client application
Run the client application with root priviledge, and you also need provide your Azure IoT hub device connection string, note your connection should be quoted in the command.

```bash
sudo ./app '<your Azure IoT hub device connection string>'
```

### Send Cloud-to-Device command
You can send a C2D message to your device. You can see the device prints out the message and blinks once receiving the message.

### Send Device Method command
You can send `start` or `stop` device method command to your Pi to start/stop sending message to your IoT hub.
=======
# iot-hub-client
receive data from bluetooth upload to cloud
>>>>>>> ca06968e288197af8072396202b2510a7ebec40e
