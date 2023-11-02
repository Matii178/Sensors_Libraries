# BMP280 STM32 Library

### Welcome to library created by me that covers BMP280 Bosch air pressure and temperature sensor. I used very similar board (HW-611) that had additional SDO and CSB pins, but they didn't need to be connected (SDO was connected to GND by manufacturer) thus on schematic I used similar sensor that contains only pins used by me.
<img src="https://github.com/Matii178/Sensors_Libraries/assets/62108776/acaa928f-16a5-4433-b36f-16053660e719" width="200" height="200">
<img src = "https://github.com/Matii178/Sensors_Libraries/assets/62108776/75bf8897-eeb5-4546-9ae4-63e7a53e6672" width = "200" height = "200">

## __Schematic__:  
<img src = "https://github.com/Matii178/Sensors_Libraries/assets/62108776/9a72a099-e3f8-4a79-ae0f-fdd9fbf3d86b" width = "520" height = "400"> 
  
3.3V -> Vin  
GND -> GND  
(It depends on which I2C you're using) PB9 -> SDA  
(It depends on which I2C you're using) PB8 -> SCL  

__Datasheet__:  
Here you can find all the information about registers, time settings etc.  
https://cdn-shop.adafruit.com/datasheets/BST-BMP280-DS001-11.pdf  

## Valuable information from the datasheet:  
* Never connect BMP280 to 5V, as its operational voltage is __1.71 - 3.6__ V _Page 7_
* BMP280 offers 3 working modes that can be controlled by 2 bits (LSB) in 0xF4 register: _Page 10 / 15_
  * Sleep mode - no measurments are conducted, sensor is idle.
  * Normal mode- measurments are conducted cylically.
  * Forced mode - only one measurment is done, after that sensor returns to Sleep mode.
* You can choose Oversampling wich will increase precission of measurement. Both to temperature and pressure, these could be managed via OSRS_T and OSRS_P bits in 0xF4 register. _Page 25_
* There is a possibility to manipulate time between each measurment by changing 3 bits (MSB) in 0xF5 register _Page 16 / 17_
  ![image](https://github.com/Matii178/Sensors_Libraries/assets/62108776/9ad6166e-7831-42e4-a217-ed063c6e783b)

* You can use IIR filter by managing bits in 0xF5 register _Page 13 / 14_
* There is a very useful memory map that contains every vital register _Page 24_
![image](https://github.com/Matii178/Sensors_Libraries/assets/62108776/d02f1f8b-dbb1-4863-998c-e3ec3c3dc9fb)


## BMP280.h
this file contains functions and definitions for the most important bit values to every parametr register, for example:  
* SDO_STATE_X - parameter depending on hardware SDO pin in sensor connected to GND or Vdd, Slave address depends on it.
* SLEEP_MODE, FORCED_MODE, NORMAL_MODE - modes for sensor to work in
* STB_X - standby times where X stands for time in ms.
* OSRS_X - values os oversampling for both temperature and pressure.
* functions are described in comments in BMP280.c file  

## BMP280.c
this file contains the bodies of every function, each one is commented, so every parameter should be described with 
* @brief - short description of function's purpouse.
* @param - description of parameters starting from the leftmost
* @retval - returning value

## example.c
this file contains an example of how every object (BMP280* sensor) needs to be created and then used via its methods. I contained there various changes of some important registers, initialization of a sensor, and what is the most important: reading temperature and pressure values from our environment.

I really hope it will be usefull to anyone, and if someone has anything to add or ask, then I encourage to contact with me :)

