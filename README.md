# Ikea Fridans Hack with Arduino (Apple Homekit)

[![Youtube Demo](http://img.youtube.com/vi/XIoDY6GLLso/0.jpg)](http://www.youtube.com/watch?v=XIoDY6GLLso)

The reason why I created this project is to be able to control my Ikea Fridans Blinds using my iPhone and Siri. Please excuse my wiring diagrams and mechanical designs because I'm not an Electrical nor a Mechanical Engineer. I spent about a month researching on how to connect these things through Google and Youtube videos. Please help correct my mistakes if you find any by submitting pull requests. Thank you.

## Credits
Special thanks to my wife who have helped me with this project. My daughter, Ayesha for helping me out with the Math calculations and code debugging. My friends, Van Chiang & Ezni, for helping me print the 3D pulley and contributing to this project.

## Introduction
This guide is specifically meant for ARDUINO UNO R3 ATMEGA328P ESP8266. It is a dual core Arduino with build in Wifi. The ATMEGA328P core will be used to control the stepper motors, while the ESP8266 core will be used to handle Wifi communication and Apple Homekit. Both of these cores communicates with each other using the onboard Serial.

## Software Requirement
1. Arduino IDE (https://www.arduino.cc/en/software)
2. Arduino-HomeKit-ESP8266 (https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266)
3. AccelStepper (https://www.arduino.cc/reference/en/libraries/accelstepper/)

## Hardware Requirements
If you wish to purchase the same hardware as I am, just copy paste the item name and find it at your nearest online store.
1. ARDUINO UNO R3 ATMEGA328P+ESP8266
2. CNC Shield V3
3. A4988 Stepper Motor Driver Module (x2)
4. NEMA 17HS4401 Bipolar Stepper Motor (x2)
5. Custom V-Pulley
    - stepper-v3.stl
    - fridans-v3.stl
6. 3mm Polyurethane Round Belt 
7. AC-DC Adapter 12V 2A
8. LED
9. Nema 17 stepper motor bracket 42 L Mounting Bracket Mount
10. Ikea Fridans Block-out roller blind
 
## Software Installation
Explain about Arduino dip switches. (todo) 

### FRIDANS_UNO
- Load FRIDANS_UNO.ino using Arduino IDE.
- Select model Arduino UNO.
- Set dip switch pin to ON 3,4.
- Load AccelStepper library.
- The stepper motor needs 200 pulses to complete make a complete rotation. My windows blinds needs 11 rotation to open and close, therefore, I need 2200 pulses to open or close my window blinds.
- Upload

### FRIDANS_ESP8266
- Load FRIDANS_ESP8266.ino using Arduino IDE.
- Select model Generic ESP8266 module.
- Set dip switch pin to ON 5,6,7.
- Load Arduino-HomeKit-ESP8266 library.
- Set home wifi password in wifi.h
- Upload

Once uploaded set 1,2 ON to enable serial communication between the 2 cores.

## Hardware Installation
(todo)
