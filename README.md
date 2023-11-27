<div align="center">

![Locus Imperium](/media/LocusImperium.gif)

### A room controlling device that reads room data attributes such as temperature, humidity, loudness, and estimates how many people are in the room at any given moment.

</div>

# Table of Contents 

- [Links](#links)
- [Introduction](#introduction)
  - [Purpose & Benefits](#purpose-and-benefits)
  - [How the system works](#how-the-system-works)
  - [Tools used](#tools-used)
- [Installation](#installation)
  - [Prerequisites](#prerequisites)
  - [Installation steps](#installation-steps)
- [User Manual](#user-manual)
- [Developed by](#developed-by)

# Links

### [Wiki Page 📚](https://git.chalmers.se/courses/dit113/2023/group-6/group-6/-/wikis/home)

### [Showcase Video 📽️](https://www.youtube.com/watch?v=5KdoOFKNgRQ)

# Introduction

## Purpose and Benefits

The purpose of this project is to create a device that reads room data attributes such as temperature, humidity, loudness, and the amount of people in a room. 

This information allows the user to study the air quality and ensure that they and their peers are in a healthy environment. For example:

- Keeping track of the room temperature and being able to regulate it whenever it exceeds the set limit guarantees everybody's comfort.
- Monitoring the level of humidity in the room and making sure it does not surpass the recommended relative humidity indoors could prevent undesirable conditions such as dry skin, dampness, mold formation, etc.
- The user can further prevent everyone around them from being in an unpleasant environment by keeping an eye on the loudness level. Any loud noise over a prolonged period of time may damage one's hearing.

All this information could be useful to determine a relation between the amount of people in the room and the air quality.

## How the system works

 <details>
 <summary> Hardware Architecture </summary>
 
![Hardware Architecture](media/IMG_4191.png)
 </details>
 
 <details>
 <summary> Software Architecture </summary>
 
 ### MQTT Architecture
 ![Locus Imperium](/media/mqtt.png)

 ### Sequence Diagram
 ![Locus Imperium](/media/SequenceDiagram.jpg)

 </details>

## Tools used

- [Mosquitto](https://mosquitto.org/)

- [Arduino CLI](https://arduino.github.io/arduino-cli/0.32/)

- [Miro Boards](https://miro.com)

- [Adobe Express](https://www.adobe.com/express/)

- [Android Studio](https://developer.android.com/studio)

- [Seeed Studio Ecosystem & Grove Sensors](https://www.seeedstudio.com/)


<details>
<summary> Libraries used </summary>

- [Seeeduino SAMD Core (1.8.3)](https://www.seeedstudio.com/) by Seeed Studio
- [Grove Temperature And Humidity Sensor (2.0.1)](https://github.com/Seeed-Studio/Grove_Temperature_And_Humidity_Sensor) by Seeed Studio
- [Grove Ultrasonic Ranger (1.0.1)](https://github.com/Seeed-Studio/Seeed_Arduino_UltrasonicRanger) by Seeed Studio
- [PubSubClient (2.8.0)](https://github.com/knolleary/pubsubclient) by Nick O’Leary
- [FS (File System) (2.1.1)]() by Seeed Studio
- [rpcUnified (2.1.4)](https://github.com/Seeed-Studio/Seeed_Arduino_rpcUnified) by Seeed Studio
- [rpcWiFi (1.0.6)](https://github.com/Seeed-Studio/Seeed_Arduino_rpcWiFi) by Seeed Studio
- [SFUD (Serial Flash Universal Driver) (2.0.2)](https://github.com/Seeed-Studio/Seeed_Arduino_SFUD) by Seeed Studio
- [Mbed TLS (3.0.1)](https://github.com/Seeed-Studio/Seeed_Arduino_mbedtls) by Seeed Studio

</details>

# Installation

## Prerequisites

### System Requirements

- OS: Windows/Linux

- Internet Access: Required

**Note:** *We believe that the system should also work on Mac OS, however it has not been tested.*

### Hardware

 - [WIO Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
 - [Wio Terminal Chassis Battery](https://wiki.seeedstudio.com/Wio-Terminal-Battery-Chassis/)
 - [Grove Ultrasonic Sensor](https://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/) x 2
 - [Grove Temperature and Humidity Sensor](https://wiki.seeedstudio.com/Grove-TemperatureAndHumidity_Sensor/)
 - [Grove Buzzer](https://wiki.seeedstudio.com/Grove-Buzzer/)

### Software

  - [Git](https://git-scm.com/) installed.

  - [Java JDK](https://www.oracle.com/se/java/technologies/downloads/) properly installed.

  - [Arduino CLI](https://arduino.github.io/arduino-cli/0.32/) properly installed.

  **Note:** *'properly installed'* means that it is in System Environment Variables: Path for Windows or $PATH for Linux.  

If you desire to host your own broker, a WiFi connection that supports MQTT is required. Make sure to connect the WIO, app and broker device to the same network.

## Installation steps

> Before starting, ensure you have the following [prerequisites](#prerequisites).

### Installing **Locus Imperium** on the **WIO Terminal** and your **Android Device**

1. Open your terminal and clone the repository.
   ```
   git clone https://git.chalmers.se/courses/dit113/2023/group-6/group-6.git
   ```
2. Go to the installation repository.
    ```
    cd group-6
    ```
3. Connect the **WIO Terminal** and your **Android Device** to your computer with USB or USB Type C.
4. Run the install script adequate for your operating system and follow the instructions.
**Note:** the linux script *should* also work on Mac OS.

    In Linux:
    ```
    ./linux_install.sh
    ```

    In Windows:
    ```
    .\windows_install.bat
    ```
5. Follow the steps on the install script.
6. Done!

### (Optional) Installing **Mosquitto** on your dedicated broker machine

1. Download [Mosquitto](https://mosquitto.org/download/) and follow the installation.

2. Go to the mosquitto folder and open `mosquitto.config` file in your computer, below "General configuration" add:

    ```
    listener 1883 0.0.0.0
    allow_anonymous true
    ```
3. Open a terminal in the folder and enter the following script:

    In Windows and Linux:
    ```
    mosquitto -c mosquitto.conf -v
    ```
    In MacOS:
    ```
    brew services start mosquitto
    ```

4. Done! The broker is now online on the network your device is connected to!

<details>
<summary> How to find your IPv4: </summary>

1. Open a terminal and run:

    In Windows
    ```
    ipconfig
    ```
    In Linux
    ```
    ip addr show
    ```
    In MacOS:
    ```
    cat /sbin/ifconfig
    ```

2. Find and select: 
<br> `Wireless LAN adapter Wi-Fi: IPv4 Address`

</details>

**Note:** On Windows, if you receive "Error: Only one usage of each socket address", terminate the already running mosquitto process:
  - Open Task Manager (ctrl+shift+esc) and under processes kill `mosquitto.exe`.

# User Manual

## WIO Terminal

Make sure to look into the official [WIO Terminal User Manual](https://files.seeedstudio.com/wiki/Wio-Terminal/res/Wio-Terminal-User-Manual.pdf) by Seeed Studio!

### 1. Connecting all the sensors
- For more information, check out the [hardware architecture](#how-the-system-works).

### 2. Button functionality (*click the menu below*)

<details>
<summary> Click to expand </summary>

 - A - Decrease the number of people by 1.

 - B - Increase the number of people by 1.

 ![Buttons](/media/WIOButtons.jpg)
</details>

## Android Application

### 1. Home Tab

 - Displays all room data in the following order:

    1. Loudness level
    2. Number of people
    3. Temperature level
    4. Humidity level

 - The "plus" and "minus" buttons will respectively adjust the people counter in accordance with the number of button presses.

### 2. Connect Tab

- Allows the user to insert an IP address and pressing the "Connect" button to connect to the broker.

### 3. Settings Tab

- Allows the user to change alert thresholds by inserting values and hitting the “Save” button.

# Developed by

### William Andersson

- Implemented the mqtt connection and how each part of the different systems should communicate with each other. Also was a part of developing the GUI for the WIO and the automated build script. Furthermore, worked on alerts, bugfixes, and general things.

### Joshua Chiu Falck

- Created the the android application functionality with the initial design. Functionality such as save & load settings, alerts, connecting with a different IP, displaying data from the broker as well as manually updating the people counter. Also assisted in the mqtt connection through the two systems and contributed to the wiki
 

### Carlos Campos Herrera

- Mainly worked on the WIO Terminal and the pipeline. Contributed to the readme, the wiki and the android app.

### Marcelo Santibáñez

- Firstly worked on MQTT connection. Implemented functionalities on the WIO terminal, screens on the Android app and also GUI and unit tests for the Java code of the app. Edited all the videos of the project.

### Andrii Demchenko 

- Developed the people movement detection algorithm, loudness measurement, and redesigned the mobile app. Also worked on test coverage reporting and contributed to the documentation.

### Vasilena Karaivanova 

- Contributed to the functionality of some sensors. Worked on the WIO Terminal for the most part, in terms of GUI and alerts. Additionally, worked on documentation, readme & wiki-page.