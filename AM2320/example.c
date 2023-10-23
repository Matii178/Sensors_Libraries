#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "am2320.h"

int main(void)
{
  float temperature = 1, humidity = 1;
  uint16_t model = 1, version = 1;

  AM2320* tempSensor = AM2320_Create(&hi2c1);
  AM2320_readTempAndHum(tempSensor);
  temperature = AM2320_getTemperature(tempSensor);
  humidity = AM2320_getHumidity(tempSensor);

  while (1)
  {
	  AM2320_readTemperature(tempSensor);
	  temperature = tempSensor->temperature;
	  AM2320_readHumidity(tempSensor);
	  humidity = tempSensor ->humidity;
	  model = AM2320_getModel(tempSensor);
	  version = AM2320_getVersion(tempSensor);
    
  }
  
}


