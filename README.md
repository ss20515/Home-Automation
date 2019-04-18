# Home-Automation

Most good programmers do programming not because they expect to get paid or get adulation by the public, but because it is fun to program. - Linus Torvalds

## Introduction
This will be a web application used for the home automation system.

## Technologies
The technologies which will be used in developing this application are as follows:

Express
/*add more later*/
## Interfaces to be added
- An interface for the led which have a toggle option for the mode that is  (automatic/appcontrol)
 The user will select one of them. And it will have:
  <b>Automatic mode: </b>
  On selecting automatic mode display if the light is on or off and if some one is in the room or not.
  <b> Appcontrol mode: </b>
  On selecting app control this mode will display a button to control the led and it will show the person status inside the room.
  
 - [ ] Web app 
 - [ ] Android
 
 - A second interface to display temprature and humidity
 
 - [ ] Web app 
 - [ ] Android
 
 - An Interface for the AC in which there are two modes **Automatic** and **AppControl**
 
 **Automatic Mode:** 
 In this mode the AC will turn on automatically when the temprature rises above the mentioned threshold temperature.
 
 The mode is turned on by **fan_tempset** variable in firebase to 1.
 
 For this the AC can be controlled by **fan_cntrl** variable which is modifyable .
 
 The temp is set in the **fan_temp** variable.
 
 **AppControl Mode**
 
 Similar to that of the led's. Turn the AC on or off with a button using the **fan_cntrl** variable
 
 - [ ] Web app 
 - [ ] Android
 
  
## Firebase database reference
- **led_r1:** This is used to display the status of led in room 1. Values used are 0 or 1.*(Read only)*
- **led_r1cntrl:** This is used to control the led in room 1. *(Read and write)*
- **pir_r1:** This is used to display whether there is some one in room 1 or not. *(Read)*
- **led_r1mode:** Used to select mode. 0 for automatic. 1 for app control. *(Read and write)*

## Author & Contributor list

/*add respective names*/

