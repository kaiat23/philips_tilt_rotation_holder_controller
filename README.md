# Philips Tilt Rotation Controller for Modern TEMs

## About the Project

<img alt="Holder attached to controller in microscope" src="https://github.com/user-attachments/assets/6be63995-dee0-46c2-89e9-a63494352e9c" />

While legacy Philips side-entry holders are vacuum compatible with modern Thermo Fisher Scientific (TFS) and FEI TEM goniometers, an external controller is needed to operate the in-plane rotation mechanism of the Philips 6594/00 tilt-rotation holder. We built an open-hardware controller to drive the holder’s motor and control the speed and direction of specimen rotation. The holder provides 360° of in-plane rotation, which can be combined with the microscope’s α-tilt to access a wide range orientations. [Click here to watch a video demo.](https://youtu.be/6G2ZNpXVkjs)

## Parts List
### Components
- [Linear potentiometer](https://a.co/d/02KlyO1r)
- [Potentiometer knob](https://www.adafruit.com/product/5529)
- [L9110H Motor Driver](https://www.adafruit.com/product/4489)
- [ESP8266 NodeMCU board](https://a.co/d/0iqh8LNQ)
- [Jumper wire](https://a.co/d/0hTiEMZ9)
- [Solid core wire](https://a.co/d/089FC4C2)
- [Banana Jack binding posts](https://a.co/d/0c96mdkv)
- [Momentary pushbutton](https://a.co/d/02dmAwGY)
- [Adafruit permaproto board](https://www.adafruit.com/product/1609)
- [USB C to Micro B cable](https://www.adafruit.com/product/3878)
- [Micro B Round Panel Mount Extension Cable](https://www.adafruit.com/product/4217)
- Four m2.5 x 30 mm screws
- Electrical tape
- Banana plug
- Hook up wire 
### Required Tools
- Small flathead screwdriver
- 2mm allen wrench
- 2.5mm allen wrench
- Soldering iron
- Solder wire
- 2.5mm hand tap
- Tap holder
### Recommended Tools
- 3D printer (for project box, alternatively machine the box)
- [Toy motor (for troubleshooting)](https://a.co/d/04hegbpR)
- Helping hands (to make soldering easier)

## Building the Controller

The [project wiki](https://github.com/kaiat23/philips_tilt_rotation_holder_controller/wiki) provides step-by-step instructions for adapting the holder and building the controller.

1. [Adapting the Holder for Controller](https://github.com/kaiat23/philips_tilt_rotation_holder_controller/wiki/Adapting-the-Holder-for-Controller): Connect wires to the holder’s motor terminals so the motor can be driven by the external controller. 
2. [Circuit Instructions](https://github.com/kaiat23/philips_tilt_rotation_holder_controller/wiki/Circuit-Instructions): Set up the ESP8266, solder the circuit, and wire the binding posts, potentiometer, and pushbuttons. <img alt="circuit_diagram" src="https://github.com/user-attachments/assets/0cb3d755-3559-4a71-ab2c-66a7db6fddc8" />
3. [Project Box Assembly](https://github.com/kaiat23/philips_tilt_rotation_holder_controller/wiki/Project-Box-Assembly): Print the project box, tap screw holes, mount the components to the top and side panels, screw the box together. <img alt="Exploded view of Assembly" src="https://github.com/user-attachments/assets/d79812bd-f72d-4477-a616-241b2b7760ac" />
