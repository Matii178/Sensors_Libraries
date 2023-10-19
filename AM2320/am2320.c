#include "am2320.h"

uint8_t AM2320_read(AM2320* const me, uint8_t startAdress, uint8_t bytes){

	uint8_t funCodes[] = {0x03,startAdress,bytes};

	HAL_I2C_Master_Transmit(me->I2Cinstance, AM2320_ADRESS, 0x00, 0, HAL_MAX_DELAY);
	HAL_Delay(3);
	if(HAL_I2C_Master_Transmit(me->I2Cinstance, AM2320_ADRESS, funCodes, 3, HAL_MAX_DELAY) != HAL_OK) {
		return -1;
	}
	HAL_Delay(3);
	if(HAL_I2C_Master_Receive(me->I2Cinstance, AM2320_ADRESS, me->data, bytes + 4, HAL_MAX_DELAY)) {
		return -2;
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

	if(AM2320_read(me, 0x00, 0x02)){
		Error_Handler();
	}
	result = (me->data[2]) << 8 | (me->data[3]);
	result /= 10;
	me->temperature = (float) result;

}
uint32_t AM2320_introduceSelf(AM2320* const me){
	return 1;
}

float AM2320_getTemperature(const AM2320* const me){
	return me->temperature;
}
float AM2320_getHumidity(AM2320* const me){
	return me->humidity;


}
uint16_t AM2320_getModel(AM2320* const me){
	return 1;
}
uint8_t AM2320_getVersion(AM2320* const me){
	return 1;

}


void AM2320_Init(AM2320* const me,I2C_HandleTypeDef *hi2c){
	me->I2Cinstance = hi2c;
	me->humidity = 0;
	me->temperature = 0;
	me->model = 0;
	me->versionNum = 0;
	memset(me->data,0,8);
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
