# Philips Tilt Rotation Controller for Modern TEMs
## Table of Contents
- [About the Project](#About-the-Project)
- [Parts List](#Parts-List)
- [Building the Controller](#Building-the-Controller)
  - [Connecting to the Motor Terminals](#Connecting-to-the-Motor-Terminals)
  - [Getting Started with the ESP8266](#Getting-Started-with-the-ESP8266)
  - [Building the Circuit](#Building-the-Circuit)
  - [Assembling the Project Enclosure](#Assembling-the-Project-Enclosure)
- [Using the Controller](#Using-the-Controller)
  - [Physical Interface](#Physical-Interface)
  - [Web Interface](#Web-Interface)
- [Loading Samples onto the Holder](#Loading-Samples-onto-the-Holder)

## About the Project
<p align="center">
  <a href="https://youtu.be/6G2ZNpXVkjs">
    <img src="https://youtube.com" alt="Watch the video" width="70%">
  </a>
</p>

## Parts List
- [L9110H H-Bridge](https://www.adafruit.com/product/4489)
- [ESP8266 NodeMCU Microcontroller](https://a.co/d/0bHyaaFW)
- [Breadboard](https://www.adafruit.com/product/1609)
- [Solid Core Wire](https://www.amazon.com/gp/product/B084DM42JS/ref=sw_img_1?smid=A1P2Y1BEUUWGO2&th=1)
- [Jumper Wire](https://a.co/d/01qo7M4T)
- [(2) Buttons]()
- [(2) Buttons]()
- [(2) Banana Plugs]()
- [(2) Banana Binding Posts]()
- [Potentiometer]()
- [USB Micro B Round Panel Mount Extension Cable]()
- [USB Micro B Cable]()

Access to soldering equipment and supplies is required for assembly of the electronics.

Access 3D printer is needed to print the project enclosure files included in this repository, but a similar box could also be machined.
## Building the Controller
### Connecting to the Motor Terminals
FIGURE 1
1. Using a flathead screwdriver, remove the screw on the body of the holder that is circled in Figure 1a.
2. Solder one wire onto each of the terminals circled in Figure 1b. Note: the length of this wire will constrain the maximum distance between the holder and the controller.
3. Solder banana plugs connectors onto the wires.
### Getting Started with the ESP8266
#### Software Setup
1. Download and install the Arduino IDE
2. Open the Arduino IDE and navigate to Settings/Preferences
3. Paste http://esp8266.com into the Additional Boards Manager URLs box
#### Hardware Setup
1. Go to Tools > Board > Boards Manager
2. Search for ESP8266 and install the package by ESP8266 Community
3. Connect your ESP8266 board to your computer using a micro-usb cable
4. Select your board from the drop down lis
#### Test the ESP8266 
1. Go to File > Examples > ESP8266 > Blink
2. Click uplaod
3. Confirm on the ESP8266 is blinking
### Building the Circuit
<img width="1890" height="1845" alt="Asset 1@2x" src="https://github.com/user-attachments/assets/b320ae67-5440-428a-b69e-8db7fd1ec743" />
1. Solder the ESP8266 to the breadboard
### Assembling the Project Enclosure
<img width="1249" height="604" alt="Screenshot 2026-08-18 at 12 19 40 PM" src="https://github.com/user-attachments/assets/276b614d-1981-4c4e-97d0-465117b9645d" />

## Using the Controller
### Physical Interface
### Web Interface 
## Loading Samples onto the Holder
