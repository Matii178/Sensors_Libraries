
#include "main.h"
#include "BMP280.h"

I2C_HandleTypeDef hi2c1;

int main(void)
{
  
  uint8_t val = 0;

  BMP280 * sensor;
  sensor = BMP280_Create(&hi2c1, SDO_STATE_GND);
  BMP280_SensorInitialize(sensor, FORCED_MODE, STB_125, OSRS_X2, OSRS_X2);

  val = BMP280_getSensorID(sensor);

  BMP280_ReadTemperatureAndPressure(sensor, 300); //my localization is placed 300 m above mean sea level

  val = BMP280_getTemperature(sensor);
  val = BMP280_getPressure(sensor);

  val = BMP280_getConfigReg(sensor);
  val = BMP280_getCtrlMeasReg(sensor);

  BMP280_setConfigReg(sensor, STB_1000 << 5); // sets value 10100000 to config register, standby mode equal to 1000ms
  BMP280_setCtrlMeasReg(sensor, OSRS_X1 << 5 | OSRS_X1 << 2 | FORCED_MODE); //value of osrs_t, osrs_p, mode value 00100101

  val = BMP280_getConfigReg(sensor);
  val = BMP280_getCtrlMeasReg(sensor);

  

  while (1)
  {

   
  }

}
