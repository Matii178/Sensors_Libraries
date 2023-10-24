# AM2320 STM32 Library:

![AM2320](https://github.com/Matii178/Sensors_Libraries/assets/62108776/92502f03-2c86-48d1-886e-5da0915304c4)

Equipment used: STM32f103RB dev board, 2x 4.7k Ohm resistors, AM2320 sensor.<br>

Schematic:</br>
![image](https://github.com/Matii178/Sensors_Libraries/assets/62108776/8434ce9e-c41e-4a03-91da-8fcf5dfef0a4)

## AM2320 Class description:

**AM2320_ADRESS** slave adress of sensor equal to 0xB8

**float humidity** value of humidity<br>
**float temperature** value of temperature<br>
**uint16_t model** model<br>
**uint8_t versionNum** number of version<br>
**uint8_t data[8]** buffer to hold read data<br>
**I2C_HandleTypeDef *I2Cinstance***; I2C instance<br>

__void AM2320_readTemperature(AM2320* const me)__ function to read temperature value and store its value inside 'float temperature'<br>
___void AM2320_readHumidity(AM2320* const me)__ function to read humidity value and store its value inside 'float humidity'<br>
__void AM2320_readTempAndHum(AM2320* const me)__ function to read both humidity and temperature and store them in 'float humidity' and 'float temperature'<br>  
__uint8_t AM2320_read(AM2320* const me, uint8_t startAdress, uint8_t bytes)__  subfunction used to read 'uint8_t bytes' starting from adress value: 'uint8_t startAdress'<br>  

__float AM2320_getTemperature(AM2320* const me)__ returns value stored in 'float temperature' <br> 
__float AM2320_getHumidity(AM2320* const me)__ returns value stored in 'float humidity' <br> 
__uint16_t AM2320_getModel(AM2320* const me)__ returns value stored in 'uint16_t model' <br> 
__uint8_t AM2320_getVersion(AM2320* const me)__ returns value stored in 'uint8_t versionNum'<br>  


__void AM2320_Init(AM2320* const me, I2C_HandleTypeDef * I2Cinstance)__ initialization of an object<br>
__AM2320 * AM2320_Create(I2C_HandleTypeDef* hi2c)__ creation of an object<br>
__void AM2320_Destroy(AM2320* const me)__ destruction of an object<br>



#### Additional info:
Function AM2320_read(..) inserts HAL_DELAY(100), due to errors connected to sensor being read too often. I tried more elegant way using HAL_I2C_isDeviceReady(..) but it could not resolve the problem.

Unfortunatelly the datasheet to this sensor was very poorly written thus its barely understandable. Link here: 
https://cdn-shop.adafruit.com/product-files/3721/AM2320.pdf

### Here are some tips and clarifications I used from there:  
* Pullup resistors used for SDA & SCL need to be within range from 3 up to 10 kΩ _page 5_
* Unfortunatelly, all AM2320 sensors have the same slave adress (0xB8) which means that there can be only one sensor of its' kind connected to I2C bus. _page 11_
* Function codes are "requests" that can be used to get data from AM2320. There are 2 codes: _page 11 / 12_ </br>
  __0x03__ read register data </br>(for example. sending Frame containing data:[0x03,0x00,0x04] means -> read 0x04 bytes starting from register with adress 0x00</br>
  __0x10__ write data to registers
* Registers being used to hold Sensors Data that can be used by user are:</br>
  ![image](https://github.com/Matii178/Sensors_Libraries/assets/62108776/4f033506-6b71-4134-ad0a-e2d58f7e01a5)
</br>wheheras DeviceID starts at 0x0B and is 32bit value, thus ends at 0x0E.
* The routine of acquiring data from sensor contains: _page 15/16/17_
  * Waking Up the sensor -> sending just the slave adress with no data, it ends with **NOT** acknowledging </br>
![image](https://github.com/Matii178/Sensors_Libraries/assets/62108776/20444505-dca9-457d-8ff0-fcbed87cca84) </br>
  * After that Function Codes can be normally sent to sensor
  * After 1.5ms Sensor responds
  * **Duration of whole operation cannot last longer than 3S** after that time sensor becomes dormant
* Values of temperature and humidity read from registers need to be divided by 10 _page 17_
* Sensor measures environmental conditions every 2seconds, so there is no need to read it more often. _page 17_




