# Philips Tilt Rotation Controller for Modern TEMs

## About the Project

<img alt="Holder attached to controller in microscope" src="https://github.com/user-attachments/assets/6be63995-dee0-46c2-89e9-a63494352e9c" />

While legacy Philips side-entry holders are vacuum compatible with modern Thermo Fisher Scientific and FEI TEM goniometers, an external controller is needed to operate the in-plane rotation mechanism of the Philips 6594/00 tilt-rotation holder. We built an open-hardware controller to drive the holder’s motor and control the speed and direction of specimen rotation. The holder provides 360° of in-plane rotation, which can be combined with the microscope’s α-tilt to access a wide range orientations. [Click here to watch a video demo.](https://youtu.be/6G2ZNpXVkjs)

## Parts List

### Components
- [Linear potentiometer](https://a.co/d/02KlyO1r)
- [Potentiometer knob](https://www.adafruit.com/product/5529)
- [L9110H motor driver](https://www.adafruit.com/product/4489)
- [ESP8266 NodeMCU board](https://a.co/d/0iqh8LNQ)
- [Jumper wires](https://a.co/d/0hTiEMZ9)
- [Solid-core wire](https://a.co/d/089FC4C2)
- [Two banana jack binding posts](https://a.co/d/0c96mdkv)
- [Two momentary pushbuttons](https://a.co/d/02dmAwGY)
- [Adafruit Perma-Proto board](https://www.adafruit.com/product/1609)
- [USB-C to USB Micro-B cable](https://www.adafruit.com/product/3878)
- [USB Micro-B round panel-mount extension cable](https://www.adafruit.com/product/4217)
- Four M2.5 × 30 mm screws
- Electrical tape
- Two banana plugs
- Hook-up wire

### Required Tools
- Wire cutters
- Wire strippers
- Small flathead screwdriver
- 2 mm hex key
- 2.5 mm hex key
- 10 mm wrench
- Soldering iron
- Solder
- M2.5 hand tap
- Tap wrench

### Recommended Tools and Equipment
- 3D printer (for fabricating the project box)
- [Toy motor (for testing and troubleshooting)](https://a.co/d/04hegbpR)

## Building the Controller

The [project wiki](https://github.com/kaiat23/philips_tilt_rotation_holder_controller/wiki) provides step-by-step instructions for adapting the holder and building the controller.

1. [Adapting the Holder for Controller](https://github.com/kaiat23/philips_tilt_rotation_holder_controller/wiki/Adapting-the-Holder-for-Controller): Connect wires to the holder’s motor terminals so the motor can be driven by the external controller. 
2. [Circuit Instructions](https://github.com/kaiat23/philips_tilt_rotation_holder_controller/wiki/Circuit-Instructions): Set up the ESP8266, solder the circuit, and wire the binding posts, potentiometer, and pushbuttons. <img alt="circuit_diagram" src="https://github.com/user-attachments/assets/0cb3d755-3559-4a71-ab2c-66a7db6fddc8" />
3. [Project Box Assembly](https://github.com/kaiat23/philips_tilt_rotation_holder_controller/wiki/Project-Box-Assembly): Print the project box, tap screw holes, mount the components, and screw the box together. <img alt="Exploded view of Assembly" src="https://github.com/user-attachments/assets/d79812bd-f72d-4477-a616-241b2b7760ac" />

## Using the Controller

The external controller controls the direction and speed of in-plane specimen rotation. The α-tilt of the holder can still be controlled through the microscope's goniometer as usual.
> [!WARNING]
> The holder offers a full 360° range of rotation but cannot rotate continuously. Upon reaching the 0° or 360° limit, the holder can only be rotated in the opposite direction. Avoid driving the motor against these limits, as prolonged stalling may damage the motor. If rotation stops unexpectedly, stop driving the motor and check the rotation gauge before continuing.

### Connecting the Controller

1. Connect the banana plugs extending from the holder to the corresponding binding posts on the controller.
2. Plug a Micro-USB cable into the panel-mounted USB extension cable and connect the other end to a power source, such as a power bank or USB wall adapter.

### Manual Control

- **Direction:** Press and hold either pushbutton to rotate the specimen. One pushbutton rotates the specimen clockwise (CW), while the other rotates it counterclockwise (CCW).

- **Speed:** Turn the potentiometer knob to adjust the speed setting between 15% and 100%.
- **Stop:** Release the pushbutton to stop rotation. Pressing both pushbuttons simultaneously also stops rotation.

The speed setting corresponds to the pulse-width modulation (PWM) duty cycle, which is limited to a minimum of 15% to reduce the risk of motor stalling.

### Wi-Fi Control

If you uploaded the Wi-Fi-enabled sketch (`InPlaneRotationControl.ino`), the controller can also be operated through a web interface.

#### Connecting to the web interface

1. Open the Wi-Fi settings on your computer, phone, or tablet.
2. Connect to the controller's Wi-Fi network using the following credentials:
   - **Network name:** `InPlaneRotationController`
   - **Password:** `microscopy123`
3. Open a web browser and navigate to [http://192.168.4.1](http://192.168.4.1).

> [!TIP]
> The ESP8266 has a reported Wi-Fi range of up to 100 m under unobstructed conditions. However, the effective range may, especially indoors, due to obstructions and interference.

#### Operating the web interface
<img alt="web interface" src="https://github.com/user-attachments/assets/21bea394-d255-4ebd-9463-b318431fc364" />

Toggle the **Web control** switch to ON to enable the web interface controls.
>[!NOTE]
>The controller defaults to manual control each time it is powered on.

- **Direction:** Select **CW** or **CCW** to initiate rotation in the corresponding direction. The selected button will be highlighted in green. Selecting the opposite direction automatically deselects the previously selected button and reverses rotation.
- **Speed:** Adjust the slider to select a speed setting between 15% and 100%.
- **Stop:** Click the currently selected direction button again to stop rotation.
- **Return to manual control:** Toggle the **Web control** switch to OFF.

The status displayed below the controls indicates the current commanded direction and applied PWM duty cycle.

> [!NOTE]
> When web control is enabled, the physical potentiometer and individual pushbuttons are disabled to prevent conflicting inputs. However, pressing both physical pushbuttons simultaneously will stop rotation and deselect the active direction in the web interface. Rotation also stops when switching between manual and web control.
>
> Closing the webpage or losing the Wi-Fi connection will not stop ongoing rotation. In either case, rotation can still be stopped by pressing both physical pushbuttons simultaneously or disconnecting the controller from its USB power source.
