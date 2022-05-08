# Home-Automation
This will be used as the site for the home automation system


## Introduction

The objective of this project is to implement a low cost, reliable and scalable home automation 
system that can be used to remotely control different aspects of the house. The different aspects 
include controlling appliances, intruder alarm system, fire alarm system, temperature control, 
garage shutter control etc.
To interact with this system remotely we provide android app for smartphone users and a 
website for other platform users. 

## Technologies

Hardware Components Specifications 
1. Arduino Uno 22 pins, operating voltage 6-20 v 
2. NodeMCU: Esp8266 CPU 
3. LED’S: 5V 
4. LCD: 16 X 2 Display 
5. PIR Sensor: Voltage DC 3-5 v, Range 2-30 cm 
6. Step up Motor:  24BYJ48 Stepper Motor 
7. Infrared Flame Detection Sensor:  3 Pins ; 5 v 
8. Buzzer: 5 v 
9. Jump Wire: M-M, M-, F-F 
10. Breadboard: Standard 

Web app reuqirements
1. Nodejs
2. Express
3. Html
4. CSS
5. Javascript
6. VS Code

Cloud technologies used
1. Firebase cloud
2. Firebase atuhentication
3. FIrebase Realtime DB
4. Firebase functions

## Firebase realtime DB 

The data for every sensor & component in the house is stored in JSON format in the NO SQL Realtime DB. This JSON data is being used by the Arduino and as well as our web application for reading & writing the chnages taking place in the system. Below is the format that is being used.

{
  "b": 255,
  "fan": 1,
  "fan_cntrl": 0,
  "fan_temp": 22,
  "fan_tempset": 1,
  "fire_alarm": 0,
  "g": 0,
  "garage": 1,
  "humidity": 41,
  "intrusion_alarm": 0,
  "intrusion_set": 0,
  "led_g": 0,
  "led_h": 1,
  "led_k": 0,
  "led_r1": 0,
  "led_r1cntrl": 1,
  "led_r1mode": 1,
  "led_r2": 0,
  "led_r2cntrl": 0,
  "led_r2mode": 0,
  "light": 283,
  "lock": 0,
  "pir_r1": 1,
  "pir_r2": 1,
  "pir_r2mode": 1,
  "r": 255,
  "temp": 30
}

## System diagram
![image](https://user-images.githubusercontent.com/21179880/167303645-b088e14c-3a25-4149-ac17-e48a9e3db3d0.png)

## Adding firebase to your javascript project

Below link provides detials of connecting your javascript project to firebase & making use of the services offered by firebase. The api keys & configuration of firebase is mostly intialized in a firebase.js file.
https://firebase.google.com/docs/web/setup?msclkid=cd73418bcee411ec874efb1951927f1a 

