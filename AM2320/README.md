
![image](https://github.com/Matii178/Sensors_Libraries/assets/62108776/e221179e-9432-43fe-91ec-fd9187a481f1)

AM2320 STM32 Library.
Equipment used: STM32f103RB dev board, 2x 4.7k Ohm resistors, AM2320 sensor.

Schematic:
coming soon

AM2320 Class description:

AM2320_ADRESS                   slave adress of sensor equal to 0xB8

float humidity                  value of humidity
float temperature;              value of temperature
uint16_t model;                 model
uint8_t versionNum;             number of version
uint8_t data[8];                buffer to hold read data
I2C_HandleTypeDef *I2Cinstance; I2C instance

void AM2320_readTemperature(AM2320* const me);  function to read temperature value and store its value inside 'float temperature'
void AM2320_readHumidity(AM2320* const me);     function to read humidity value and store its value inside 'float humidity'
void AM2320_readTempAndHum(AM2320* const me);   function to read both humidity and temperature and store them in 'float humidity' and 'float temperature'
uint8_t AM2320_read(AM2320* const me, uint8_t startAdress, uint8_t bytes);  subfunction used to read 'uint8_t bytes' starting from adress value: 'uint8_t startAdress'

float AM2320_getTemperature(AM2320* const me); returns value stored in 'float temperature'
float AM2320_getHumidity(AM2320* const me); returns value stored in 'float humidity'
uint16_t AM2320_getModel(AM2320* const me); returns value stored in 'uint16_t model'
uint8_t AM2320_getVersion(AM2320* const me); returns value stored in 'uint8_t versionNum'


void AM2320_Init(AM2320* const me, I2C_HandleTypeDef * I2Cinstance);  initialization of an object
AM2320 * AM2320_Create(I2C_HandleTypeDef* hi2c);    creation of an object
void AM2320_Destroy(AM2320* const me);              destruction of an object



Additional info:
After few hours of solving bug that was crashing main program, it turned out that there cannot be 2 reads (transmission and sensor response) within less than 2 seconds.
