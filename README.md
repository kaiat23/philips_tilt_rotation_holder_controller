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
