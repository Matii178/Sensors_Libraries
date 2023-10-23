![AM2320](https://github.com/Matii178/Sensors_Libraries/assets/62108776/92502f03-2c86-48d1-886e-5da0915304c4)


**AM2320 STM32 Library**.<br>
Equipment used: STM32f103RB dev board, 2x 4.7k Ohm resistors, AM2320 sensor.<br>

Schematic:coming soon

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



Additional info:<br>
Function AM2320_read(...) inserts HAL_DELAY(100), due to errors connected to sensor being read too often. I tried more elegant way using HAL_I2C_isDeviceReady(..) but it could resolve the problem.
