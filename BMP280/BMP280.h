#ifndef _BMP280_H_
#define BMP280_H_

#include "stm32f1xx_hal.h"
#include <stdlib.h>
#include <string.h>
#include <main.h>

typedef struct BMP280 BMP280;

struct BMP280{
	//20 bytes for temperature and pressure ?
	uint32_t rawTemperature;
	uint32_t rawPressure;
	uint8_t buffer[3];

	I2C_HandleTypeDef* i2c_handler;
	uint16_t slaveAddress;
	uint8_t configReg;
	uint8_t ctrlMeasReg;


};

BMP280* BMP280_Create(I2C_HandleTypeDef * i2c_handler, uint8_t SDO_state);
void BMP280_Destroy(BMP280* const me);
void BMP280_Init(BMP280* const me,I2C_HandleTypeDef* i2c_handler, uint8_t SDO_state);

void BMP280_SensorInitialize(BMP280 * const me);
void BMP280_ReadTemperature(BMP280 * const me);
void BMP280_ReadPressure(BMP280 * const me);
void BMP280_ReadTemperatureAndPressure(BMP280 * const me);
void BMP280_ReadRegisters(BMP280 * const me, uint8_t address, uint8_t bytes);
void BMP280_WriteRegisters(BMP280 * const me, uint8_t address, uint8_t data); //pointer to table?

void BMP280_setConfigReg(BMP280 * const me);
void BMP280_setCtrlMeasReg(BMP280 * const me);

float BMP280_getTemperature(BMP280 * const me);
float BMP280_getPressure(BMP280 * const me);
uint8_t BMP280_getSensorID(BMP280 * const me);
uint8_t BMP280_getConfigReg(BMP280 * const me);
uint8_t BMP280_getCtrlMeasReg(BMP280 * const me);

void BMP280_ResetSensor(BMP280 * const me);










#endif
