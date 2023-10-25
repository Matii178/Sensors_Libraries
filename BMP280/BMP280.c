#include "BMP280.h"

BMP280* BMP280_Create(I2C_HandleTypeDef *i2c_handler, uint8_t SDO_state) {
	BMP280 *newObject = malloc(sizeof(BMP280));
	if(newObject != NULL) {
		BMP280_Init(newObject, i2c_handler, SDO_state);
	}
	return newObject;

}
void BMP280_Destroy( BMP280* const me) {
	free(me);
}
void BMP280_Init(BMP280* const me,I2C_HandleTypeDef* i2c_handler, uint8_t SDO_state){
	memset(me->buffer,0,3);
	me->i2c_handler = i2c_handler;
	me->rawPressure = 0;
	me->rawTemperature = 0;

	me->configReg = BMP280_getConfigReg(me);
	me->ctrlMeasReg = BMP280_getCtrlMeasReg(me);
}

void BMP280_SensorInitialize(BMP280 * const me);
void BMP280_ReadTemperature(BMP280 * const me) {

	//w zaleznosci od parametrow wewnetrznych...
	//BMP280_ReadRegisters(me, 0xFA, 3..2..1);

}
void BMP280_ReadPressure(BMP280 * const me);
void BMP280_ReadTemperatureAndPressure( BMP280 * const me);

void BMP280_ReadRegisters(BMP280* const me, uint8_t address, uint8_t bytes) {
	HAL_I2C_Master_Transmit(me->i2c_handler, me->slaveAddress, (uint8_t *) address, 1, HAL_MAX_DELAY); //not sure
	HAL_I2C_Master_Receive(me->i2c_handler, me->slaveAddress, me->buffer, bytes, HAL_MAX_DELAY); //bytes cannot be greater than 3;
}
void BMP280_WriteRegisters(BMP280 * const me, uint8_t address, uint8_t data); //pointer to table?

void BMP280_setConfigReg(BMP280 * const me);
void BMP280_setCtrlMeasReg(BMP280 * const me);

float BMP280_getTemperature(BMP280 * const me);
float BMP280_getPressure(BMP280 * const me);
uint8_t BMP280_getSensorID(BMP280 * const me);
uint8_t BMP280_getConfigReg(BMP280 * const me);
uint8_t BMP280_getCtrlMeasReg(BMP280 * const me);

void BMP280_ResetSensor(BMP280 * const me);
