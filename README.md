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
- [Linear Potentiometer]()
- [Potentiometer Knob]()
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
1. Download and install the Arduino IDE ([click here to access the download link](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE))
2. Open the Arduino IDE and navigate to Settings/Preferences
3. Paste ```https://arduino.esp8266.com/stable/package_esp8266com_index.json``` into the Additional Boards Manager URLs box
#### Hardware Setup
1. Go to Tools > Board > Boards Manager
2. Search for espP8266 and install the package by ESP8266 Community
3. Connect your ESP8266 board to your computer using a micro-usb cable
4. Select the port connected to your board from the "Select Board" drop-down list (it should be a usbserial port)
5. In the pop-up window, select "NodeMCU 1.0 (ESP-12E Module)" under "BOARDS" and select the port connected to your board under "PORTS"
6. Press the left arrow "Upload" button
#### Test the ESP8266 
1. Go to File > Examples > ESP8266 > Blink
2. Click uplaod
3. Confirm on the ESP8266 is blinking
### Building the Circuit
<img width="1412" height="798" alt="circuit_diagram" src="https://github.com/user-attachments/assets/bb384898-dd90-49fa-8e3f-db55bf208ce1" />

1. Solder the ESP8266 to the breadboard
2. Solder the L9110H to the breadboard
> [!NOTE]
> To test the circuit at this stage, connect a toy motor to the jumper wires extending from the OA and OB pins of the L9110H H-bridge, with one wire connected to each motor terminal; then, upload the following code to the ESP8266. The motor should alternate between directions every 5 seconds, with a 2-second pause between rotations. 
> ```cpp
> void setup() {
>   pinMode(D1, OUTPUT);
>   pinMode(D2, OUTPUT);
>   digitalWrite(D1, LOW);
>   digitalWrite(D2, LOW);
> }
>
> void loop() {
>   digitalWrite(D1, HIGH);
>   delay(5000);
>   digitalWrite(D1, LOW);
>   delay(2000);
>
>   digitalWrite(D2, HIGH);
>   delay(5000);
>   digitalWrite(D2, LOW);
>   delay(2000);
> }
> ```

>void loop() {
>}
>```

### Assembling the Project Enclosure
<img width="1249" height="604" alt="Screenshot 2026-08-18 at 12 19 40 PM" src="https://github.com/user-attachments/assets/276b614d-1981-4c4e-97d0-465117b9645d" />

## Using the Controller
### Physical Interface
### Web Interface 
## Loading Samples onto the Holder
