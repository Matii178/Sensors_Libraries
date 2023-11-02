# AM2320 STM32 Library

### Welcome to library created by me that covers AM2320 humidity and temperature sensor. 
<img src= "https://github.com/Matii178/Sensors_Libraries/assets/62108776/92502f03-2c86-48d1-886e-5da0915304c4" width = "400" height = "400">

## Schematic:  
Equipment used: STM32f103RB dev board, 2x 4.7k Ohm resistors, AM2320 sensor.<br>

<img src= "https://github.com/Matii178/Sensors_Libraries/assets/62108776/ac063cc5-ecf4-4f05-b5a7-2a6bb50482f3" width = "400" height = "400">  
  
3.3V -> Vdd  
GND -> GND  
(It depends on which I2C you're using) PB9 -> SDA  
(It depends on which I2C you're using) PB8 -> SCL  
SDA and SCL lines are pulled to Vdd via 4.7kΩ resistors

__Datasheet__:  
Here you can find all the information about registers etc. Unfortunatelly it was written using very poor english and sometimes it is really hard to understand.  
https://cdn-shop.adafruit.com/product-files/3721/AM2320.pdf

## Valuable information from the datasheet:  
* Pullup resistors used for SDA & SCL need to be within range from 3 up to 10 kΩ _page 5_
* Unfortunatelly, all AM2320 sensors have the same slave adress (0xB8) which means that there can be only one sensor of its' kind connected to I2C bus. _page 11_
* Function codes are "requests" that can be used to get data from AM2320. There are 2 codes: _page 11 / 12_ </br>
  __0x03__ read register data </br>(for example. sending Frame containing data:[0x03,0x00,0x04] means -> read 0x04 bytes starting from register with adress 0x00</br>
  __0x10__ write data to registers
* Registers being used to hold Sensors Data, which can be used by user are:</br>
  ![image](https://github.com/Matii178/Sensors_Libraries/assets/62108776/4f033506-6b71-4134-ad0a-e2d58f7e01a5)
</br>whereas DeviceID starts at 0x0B and is 32bit value, thus ends at 0x0E.
* The routine of acquiring data from sensor contains: _page 15/16/17_
  * Waking Up the sensor -> sending just the slave adress with no data, it ends with **NOT** acknowledging </br>
![image](https://github.com/Matii178/Sensors_Libraries/assets/62108776/20444505-dca9-457d-8ff0-fcbed87cca84) </br>
  * After that Function Codes can be normally sent to sensor
  * After 1.5ms Sensor responds
  * **Duration of whole operation cannot last longer than 3S** after that time sensor becomes dormant
* Values of temperature and humidity read from registers need to be divided by 10 _page 17_
* Sensor measures environmental conditions every 2seconds, so there is no need to read it more often. _page 17_

## AM2320.h
This file contains declaration of every AM2320 function and definition of slave address

## AM2320.c
this file contains body of every function that is commented in a following way to make it easier to understand:
* @brief - short description of function's purpose
* @param - described parameters, starting from the leftmost
* @retval - returning value

## example.c
this file contains example of creation the AM2320 object and how data from it is read and extracted.

### Additional info:
Function AM2320_read(..) inserts HAL_DELAY(100), due to errors connected to sensor being read too often. I tried more elegant way using HAL_I2C_isDeviceReady(..) but it could not resolve the problem. Implementation of these HAL_DELAYs' ensures that user will not read sensor too often making it crash.


I really hope it will be usefull to anyone, and if someone has anything to add or ask, then I encourage them to contact with me :)



