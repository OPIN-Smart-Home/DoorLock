# OPIN Door Lock

[![License](https://img.shields.io/badge/license-Apache%202-blue.svg)](https://www.apache.org/licenses/LICENSE-2.0)

![Door Lock](https://github.com/OPIN-Smart-Home/DoorLock/blob/main/asset/DoorLock.png)

## Table of Contents
For User
- [Introduction](#introduction)
- [Features](#features)
- [Components and Interface](#components-and-interface)
- [User Guide](#user-guide)

For Developer
- [Installation](#installation)
- [MQTT Topics](#mqtt-topics)
- [Limitations](#limitations)
- [Future Development](#future-development)

Additional Information
- [OPIN Smart Home Devices](#opin-smart-home-devices)
- [Acknowledgments](#acknowledgments)
- [Further Information](#further-information)

 ---
 ---

# For User
## Introduction
The OPIN Door Lock is a smart security solution designed to enhance the safety and convenience of your home or office. By integrating with the [OPIN Gateway](https://github.com/OPIN-Smart-Home/OPIN-JetsonNano-public), this device allows users to remotely monitor and unlock their door via the OPIN mobile app. The door lock features an automatic locking mechanism, which automatically locks the door when it is closed, ensuring security without requiring manual intervention. 

Unlike other smart locks, the OPIN Door Lock only provides remote unlocking functionality since the locking occurs automatically. There are no automation options available for the lock/unlock mechanism, offering a straightforward and reliable security solution. 

The OPIN Door Lock can be easily integrated into existing smart home systems, providing real-time status updates and seamless interaction with other smart devices such as security cameras and alarms. The device is designed for modern smart homes, offering essential security features that ensure peace of mind for users.

For developers, the OPIN Door Lock uses MQTT protocol for communication, allowing for easy integration within the OPIN system. The device supports flexible API integration for custom use cases, while also ensuring simple installation and setup.

## Features
1. **Remote Unlocking**  
   The door lock can be unlocked remotely via the OPIN mobile app, providing flexibility and convenience. This feature is ideal for granting access to family members, visitors, or service personnel when you are away from home.
2. **Auto-Lock Mechanism**  
   The lock automatically engages when the door is closed, ensuring that your home is always secure without needing manual intervention. There is no remote locking feature as the lock is designed to automatically secure the door.
3. **Real-Time Status Updates**  
   Receive instant notifications on the lock's status through the OPIN mobile app. Know immediately when the door is unlocked or locked, giving you peace of mind.
4. **Manual Override**  
   In case of emergency or loss of connectivity, the OPIN Door Lock can still be operated manually, ensuring you’re never locked out of your home.
5. **Integration with OPIN Gateway**  
   Seamlessly integrates with the OPIN Gateway, allowing the OPIN Door Lock to be a part of your larger smart home ecosystem. While automation options are not available, users can still monitor the lock's status along with other smart home devices through the app.

## Components and Interface
The following components are used in the OPIN Door Lock. The numbers correspond to the labels in the [cover image](#opin-door-lock).

1. [**Electric Rim Door Lock**](https://www.yalehome.com/it/en/products/mechanical/locks-for-wooden-doors/electric-rim-lock/678-electric-rim-lock)  
   The physical lock mechanism that automatically locks when the door is closed. It can be unlocked via the OPIN mobile app or manually with a key. This lock is powered by the system and is designed for robust security. [Learn more about how Electric Rim Door Locks work](https://youtu.be/RPEi3pzziEc?si=CRzAZSvBFVsrrlkn).
2. **AC Power Cable**  
   This cable connects the system to the 12V Power Adapter (Trafo 12V 5A), supplying the necessary power to the door lock and its components.
3. **12V Power Adapter (Trafo 12V 5A)**  
   A transformer that supplies 12V DC power with a 5A current to the door lock system. It powers the door lock and other internal components.
4. **ESP32 Devkit V1**  
   The microcontroller responsible for managing the device's operations, Wi-Fi connection, and communication via MQTT.
5. **LED**  
   The device features an LED that indicates the WiFi connection status, helping users verify whether the device is connected to the network.
6. **Button**  
   A button is provided for initiating the WiFi configuration process, allowing users to connect the device to their network. This button can also be used to reset the WiFi connection.
7. **LM2596 Step Down**  
   A buck converter that steps down the 12V input to 5V for components like the ESP32, ensuring the correct power levels for stable operation.
8. **5V Relay Module with Optocoupler**  
   Controls the door's locking mechanism. It switches the circuit to unlock the door based on commands received from the OPIN mobile app, offering reliable control over the electric rim door lock.

## User Guide
This user guide provides step-by-step instructions for setting up, using, and troubleshooting the OPIN Door Lock. Follow these guidelines to ensure optimal performance and security.
### 1. Installation
1. **Required Tools**
    - Screwdriver
    - Drill (if necessary for mounting)
    - AC power source
2. **Mount the Electric Rim Door Lock**
   - Follow the manufacturer's instructions for mounting the electric rim door lock securely on your door.
   - Ensure that the lock aligns properly with the door frame for effective locking.
   - For a visual guide, you can watch the [installation tutorial](https://youtu.be/RLX9Dwu2r2o?si=dn9RHIza_dEbm8V_).
3. **Connect the Plug in the OPIN Door Lock**
    - Plug the adapter into a suitable power outlet to provide power to the lock.

### 2. LED Indicator
1. **Solid**: The device is connected to the network.
2. **Blinking continuously**: The device is not connected to a network or in the process of connecting.
3. **Off**: The device is either not powered or in WiFi configuration mode.

### 3. WiFi Configuration
#### Add WiFi Configuration
1. **Initiate WiFi Configuration**  
   - Press the button once to enter WiFi configuration mode. The LED will blink twice, indicating that the device is ready to connect to a network.  
   ![Button1](https://github.com/OPIN-Smart-Home/DoorLock/blob/main/asset/button1.gif)

2. **Connect to the Network**  
   - Open the WiFi settings on your mobile, laptop, or PC.
   - Connect to the Door Lock SSID `OPIN-DoorLock-[device_id]`. Your device should automatically redirect you to the WiFi configuration interface (captive portal).
      > **Tips**: If you're not redirected to the captive portal automatically, try the following:  
      (1) Look for a notification asking you to `log in to the network`,  
      (2) Go to [WiFi settings](<https://media.techietech.tech/2020/06/Forget-Network.jpg.webp>) and select something like `Manage network settings`,  
      (3) Manually access the captive portal by opening `192.168.4.1` in your browser.
   - Once inside the configuration interface, select `Configure WiFi`. Choose your home WiFi SSID from the list, enter the password, and click `Save`. (Refer to the provided images for detailed guidance.)  
   ![Configure WiFi](https://github.com/OPIN-Smart-Home/DoorLock/blob/main/asset/configure_wifi.png)

3. **Confirm Connection**  
   - After the connection is established, the LED will turn solid, indicating that the Door Lock is successfully connected to your WiFi network.

#### Reset WiFi Configuration
1. **Initiate Reset**  
   - Press and hold the button for at least two seconds. The LED will blink three times (indicating reset) followed by two blinks (entering WiFi configuration mode), signaling that the WiFi settings have been reset. This action will erase all previously saved WiFi configurations.  
   ![Button2](https://github.com/OPIN-Smart-Home/DoorLock/blob/main/asset/button2.gif)

2. **Reconnect to the Network**  
   - After resetting the WiFi, follow step [2 "Connect to the Network"](#add-WiFi-configuration) from the **Add WiFi Configuration** section to reconnect the Door Lock to your WiFi.

#### Check IP Address of the Door Lock
1. **Initiate WiFi Configuration**  
   - Press the button once to enter WiFi configuration mode. The LED will blink twice, indicating that the device is ready for network configuration.  
   ![Button1](https://github.com/OPIN-Smart-Home/DoorLock/blob/main/asset/button1.gif)

2. **Connect to the Network**  
   - Open the WiFi settings on your mobile, laptop, or PC.
   - Connect to the Door Lock SSID `OPIN-DoorLock-[device_id]`, and your device will be redirected to the WiFi configuration interface (captive portal).  
      > **Tip**: If you're not redirected to the captive portal automatically, try the following:  
      (1) Look for a notification asking you to `log in to the network`,  
      (2) Go to [WiFi settings](<https://media.techietech.tech/2020/06/Forget-Network.jpg.webp>) and select `Manage network settings`,  
      (3) Manually access the captive portal by opening `192.168.4.1` in your browser.
   - The IP address of the Door Lock will be shown in the connected WiFi details box. (Refer to the provided image for reference.)  
   ![Check IP](https://github.com/OPIN-Smart-Home/DoorLock/blob/main/asset/check_ip.jpeg)

3. **Exit Configuration Mode**  
   - After checking the IP address, select `Exit` to complete the configuration process. The LED will turn solid, indicating that the Door Lock is successfully connected to your WiFi network.

### 4. Connect Door Lock to OPIN Mobile App
1. **Add New Device**  
   - Open the OPIN mobile app and click the `Add New Device` option.  
   - Select `Door Lock` from the list of devices.  
   - Enter the `Device ID` and `IP Address` of the Door Lock.  
   - Click `Submit`.  
   > **Note**: Ensure that the `Device ID` and `IP Address` are accurate to avoid issues during the device setup.

2. **Unlocking the Door**
    - Use the OPIN mobile app to unlock the door remotely. 
    - Alternatively, unlock the door manually using the key provided with the electric rim lock.

### 5. Troubleshooting
1. **Device Not Connecting to Wi-Fi**
   - **Check Wi-Fi Credentials**: Ensure that the correct Wi-Fi credentials (SSID and password) are entered during the setup.
   - **Proximity to Router**: Make sure the Door Lock is within the range of your Wi-Fi router. Try moving it closer to the router for better signal strength.
   - **Reboot the Device**: Unplug the Door Lock from the power outlet and plug it back in to restart the device.

2. **Safety Information**
    - Ensure that the power supply is adequate for the electric rim door lock.
    - Keep the device away from moisture and extreme temperatures to prevent damage.

---
---

# For Developer
This section provides guidelines for developers looking to contribute to the OPIN Smart Home system. It's recommended to pay attention on [For User](#for-user) section.
## Installation
### Prerequisites
Before you begin, ensure you have the following installed on your development environment:
- **Arduino IDE** for uploading the firmware to the ESP32.
- **ESP32 Board Package** for Arduino IDE. For Arduino IDE, you can install it by going to **File > Preferences > Additional Board Manager URLs** and adding `https://dl.espressif.com/dl/package_esp32_index.json`. Then, navigate to **Tools > Board > Board Manager** and search for "ESP32".
- **Required Libraries**:
  - **WiFi**: For WiFi connectivity.
  - [**PicoMQTT** by Michał Leśniewski](<https://github.com/mlesniew/PicoMQTT>) version `0.3.8` : To enable the ESP32 to function as an MQTT broker/server.
  - [**WiFiManager** by tzapu](<https://github.com/tzapu/WiFiManager>) version `2.0.17`: For handling WiFi connections and configurations.

### Clone the Repository
To get started with the project, clone the repository to your local machine:
```bash
git clone https://github.com/OPIN-Smart-Home/DoorLock.git
```

## MQTT Topics
The following MQTT topics are utilized for communication between the OPIN Door Lock and the OPIN gateway:
- **User to Device (u2d)**:  
  `opin/DoorLock_[device_id]/u2d`  
  This topic is utilized for commands from the user to the OPIN Door Lock. Its sole function is to unlock the door.
- **Acknowledgment (ack)**:  
  `opin/DoorLock_[device_id]/ack`  
  This topic is used for sending acknowledgment messages, which include the current state of the door, as the door automatically locks itself when closed.
- **Device SSID**:  
  `OPIN-DoorLock-[device_id]`  
  This SSID is employed for connecting the OPIN Door Lock to WiFi during the initial configuration process.
> **Note**: The gateway will not accept the same `device_id` for multiple OPIN Door Locks. Developers must ensure that each OPIN Door Lock has a unique `device_id` to avoid communication conflicts within the system.

## Limitations
While the OPIN Door Lock provides several advantages for smart home security, there are some limitations to consider:
1. **Single Functionality**:  
   The OPIN Door Lock is designed solely for unlocking the door, as the locking mechanism is automatic when the door is closed. This limits its functionality compared to other smart locks that may offer additional features like remote locking.
2. **Dependence on Wi-Fi Connectivity**:  
   The functionality of the OPIN Door Lock relies heavily on a stable Wi-Fi connection. In the event of network issues, users may experience difficulties in accessing the lock remotely.
3. **Power Dependency**:  
   The device requires a continuous power supply to function. Any power outages or interruptions may render the lock inoperable until power is restored.
4. **Compatibility Issues**:  
   The OPIN Door Lock may not be compatible with all existing door frames and locking mechanisms. Proper installation may require additional adjustments or modifications.

## Future Development
The OPIN Door Lock team is committed to enhancing the product's functionality and user experience. The following features and improvements are planned for future development:
1. **Remote Locking Feature**:  
   Future updates may include the ability to remotely lock the door, providing users with greater control over their home security.
2. **Integration with Smart Home Ecosystems**:  
   Expanding compatibility with other smart home devices and platforms (such as Amazon Alexa, Google Assistant, or Apple HomeKit) will enable more seamless automation and control.
3. **Mobile Notifications**:  
   Implementing real-time notifications to inform users of the door’s status (locked/unlocked) will enhance security and user awareness.
4. **Advanced Analytics**:  
   Future versions may include analytics features, providing users with insights into their door usage patterns and notifications for unusual activity.

---
---

# Additional Information
## OPIN Smart Home Devices
Other devices:
- [OPIN Smart Gateway](<https://github.com/OPIN-Smart-Home/OPIN-JetsonNano-public>)
- [OPIN Smart Lamp](<https://github.com/OPIN-Smart-Home/SmartLamp>)
- [OPIN Smart kWh Meter](<https://github.com/OPIN-Smart-Home/kWhMeter>)
- [OPIN Smart AC Control](<https://github.com/OPIN-Smart-Home/ACControl>)

## Acknowledgments
This project makes use of:  
- [PicoMQTT](<https://github.com/mlesniew/PicoMQTT>) by [mlesniew](<https://github.com/mlesniew>) (Michał Leśniewski), under [LGPL-3.0 license](<https://github.com/mlesniew/PicoMQTT/blob/master/LICENSE>).
- [WiFiManager](<https://github.com/tzapu/WiFiManager>) by [tzapu](<https://github.com/tzapu>), under [MIT license](<https://github.com/tzapu/WiFiManager/blob/master/LICENSE>).

We appreciate their efforts and contributions, which have been instrumental in the development of this project.

## Further Information
For further information, please feel free to contact me at:
- **Email**: [anisahfarah28@gmail.com](mailto:anisahfarah28@gmail.com)
- **LinkedIn**: [Anisah Farah Fadhilah](https://www.linkedin.com/in/anisahfarahfadhilah)
