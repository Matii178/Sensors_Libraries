#include "am2320.h"

uint8_t AM2320_read(AM2320* const me, uint8_t startAdress, uint8_t bytes){
	uint8_t funCodes[] = {0x03,startAdress,bytes};

	HAL_Delay(100); // if it doesnt wait, then the error comes -> Sensor not being ready I guess ?

	HAL_I2C_Master_Transmit(me->I2Cinstance, AM2320_ADRESS, 0x00, 1, 800);

	HAL_Delay(1); //according to datasheet, there is a need to wait more than 800u and less than 3ms

	if(HAL_I2C_Master_Transmit(me->I2Cinstance, AM2320_ADRESS, funCodes, 3, 2000)) {
		return -1;
	}
	HAL_Delay(2);
	if(HAL_I2C_Master_Receive(me->I2Cinstance, AM2320_ADRESS, me->data, bytes + 4, 2000)) {
		return -1;
	}

	return 0;
}


void AM2320_readTemperature(AM2320* const me) {
		uint16_t result;
		float temperature;

		if(AM2320_read(me, 0x02, 0x02)){
			Error_Handler();
		}
		result = (me->data[2]) << 8 | (me->data[3]);
		temperature = result / 10.0;
		me->temperature = temperature;

}

void AM2320_readHumidity(AM2320* const me) {
	uint16_t result;
	float humidity;

	if(AM2320_read(me, 0x00, 0x02)){
		Error_Handler();
	}
	result = (me->data[2]) << 8 | (me->data[3]);
	humidity = result/10.0;
	me->humidity = humidity;

}

void AM2320_readTempAndHum(AM2320* const me) {
	uint16_t result;
	float humidity;
	float temperature;

	if(AM2320_read(me, 0x00, 0x04)){
		Error_Handler();
	}
	result = (me->data[2]) << 8 | (me->data[3]);
	humidity = result/10.0;
	result = (me->data[4]) << 8 | (me->data[5]);
	temperature = result/10.0;
	me->humidity = humidity;
	me->temperature = temperature;

}


float AM2320_getTemperature(AM2320* const me){
	return me->temperature;
}
float AM2320_getHumidity(AM2320* const me){
	return me->humidity;


}
uint16_t AM2320_getModel(AM2320* const me){
	return me->model;
}
uint8_t AM2320_getVersion(AM2320* const me){
	return me->versionNum;

}


void AM2320_Init(AM2320* const me,I2C_HandleTypeDef *hi2c){
	me->I2Cinstance = hi2c;
	me->humidity = 0;
	me->temperature = 0;
	memset(me->data,0,8);
//
	AM2320_read(me, 0x08, 0x02);
	me->model = (me->data[2] << 8) | (me->data[3]);
	HAL_Delay(100);
	AM2320_read(me, 0x0A, 0x01);
	me->versionNum = me->data[2];
}

AM2320 * AM2320_Create(I2C_HandleTypeDef* hi2c){
	AM2320* me = malloc(sizeof(AM2320));

	if(me != NULL) {
		AM2320_Init(me, hi2c);
	}
	return me;
}

void AM2320_Destroy(AM2320* const me){
	free(me);
}
