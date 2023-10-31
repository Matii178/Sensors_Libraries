#ifndef _BMP280_H_
#define BMP280_H_

#include "stm32f1xx_hal.h"
#include <stdlib.h>
#include <string.h>
#include <main.h>

#define SDO_STATE_GND 0
#define SDO_STATE_VDD 1

//modes
#define SLEEP_MODE 	0b00
#define FORCED_MODE 0b01
#define NORMAL_MODE 0b11

//standby times
#define STB_0_5 	0b000
#define STB_0_62	0b001
#define STB_125		0b010
#define STB_250		0b011
#define STB_500		0b100
#define STB_1000	0b101
#define STB_2000	0b110
#define STB_4000	0b111

//osrs_t & p
#define OSRS_RESET 	0b000
#define OSRS_X1 	0b001
#define OSRS_X2 	0b010
#define OSRS_X4 	0b011
#define OSRS_X8 	0b100
#define OSRS_X16 	0b111



typedef struct BMP280 BMP280;

struct BMP280{
	//20 bytes for temperature and pressure ?
	uint32_t rawTemperature;
	uint32_t rawPressure;
	uint8_t buffer[24];

	I2C_HandleTypeDef* i2c_handler;
	uint8_t slaveAddress;
	uint8_t configReg;
	uint8_t ctrlMeasReg;
	uint8_t id;

	uint16_t calibT[3];
	uint16_t calibP[9];

};

BMP280* BMP280_Create(I2C_HandleTypeDef * i2c_handler, uint8_t SDO_state);
void BMP280_Destroy(BMP280* const me);
void BMP280_Init(BMP280* const me,I2C_HandleTypeDef* i2c_handler, uint8_t SDO_state);

void BMP280_SensorInitialize(BMP280 * const me, uint8_t mode, uint16_t standbyTime, uint16_t osrs_t, uint16_t osrs_p);
void BMP280_ReadTemperature(BMP280 * const me);
void BMP280_ReadPressure(BMP280 * const me);
void BMP280_ReadTemperatureAndPressure(BMP280 * const me);
void BMP280_ReadRegisters(BMP280 * const me, uint8_t address, uint8_t bytes);

/*
 * Function to write multiple bytes to multiple registers
 */
void BMP280_WriteRegisters(BMP280 * const me, uint8_t* addresses, uint8_t*  data, uint8_t bytes);

void BMP280_setConfigReg(BMP280 * const me, uint8_t reg);
void BMP280_setCtrlMeasReg(BMP280 * const me, uint8_t reg);

float BMP280_getTemperature(BMP280 * const me);
float BMP280_getPressure(BMP280 * const me);
uint8_t BMP280_getSensorID(BMP280 * const me);
uint8_t BMP280_getConfigReg(BMP280 * const me);
uint8_t BMP280_getCtrlMeasReg(BMP280 * const me);

void BMP280_ResetSensor(BMP280 * const me);



#endif
