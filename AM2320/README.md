AM2320 STM32 Library.
Equipment used: STM32f103RB dev board, 2x 4.7k Ohm resistors, AM2320 sensor.

Schematic:
coming soon

AM2320 Class description:

AM2320_ADRESS            slave adress of sensor equal to 0xB8

float humidity
float temperature;
uint16_t model;
uint8_t versionNum;
uint8_t data[8];
I2C_HandleTypeDef *I2Cinstance;

void AM2320_readTemperature(AM2320* const me);
void AM2320_readHumidity(AM2320* const me);
void AM2320_readTempAndHum(AM2320* const me);
uint8_t AM2320_read(AM2320* const me, uint8_t startAdress, uint8_t bytes);

float AM2320_getTemperature(AM2320* const me);
float AM2320_getHumidity(AM2320* const me);
uint16_t AM2320_getModel(AM2320* const me);
uint8_t AM2320_getVersion(AM2320* const me);


void AM2320_Init(AM2320* const me, I2C_HandleTypeDef * I2Cinstance);
AM2320 * AM2320_Create(I2C_HandleTypeDef* hi2c);
void AM2320_Destroy(AM2320* const me);



Additional info:
After few hours of solving bug that was crashing main program, it turned out that there cannot be 2 reads (transmission and sensor response) within less than 2 seconds.
