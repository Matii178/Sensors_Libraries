#include "BMP280.h"

/*
 * Creation of an object
 */
BMP280* BMP280_Create(I2C_HandleTypeDef *i2c_handler, uint8_t SDO_state) {
	BMP280 *newObject = malloc(sizeof(BMP280));
	if(newObject != NULL) {
		BMP280_Init(newObject, i2c_handler, SDO_state);
	}
	return newObject;

/*
 * Destruction of an object
 */
}
void BMP280_Destroy( BMP280* const me) {
	free(me);
}

/*
 * First initialization of parameters
 */
void BMP280_Init(BMP280* const me,I2C_HandleTypeDef* i2c_handler, uint8_t SDO_state){
	memset(me->buffer,0,20);
	if(SDO_state){
		me->slaveAddress = 0x77 << 1;
	} else {
		me->slaveAddress = 0x76 << 1;
	}
	me->i2c_handler = i2c_handler;
	me->rawPressure = 0;
	me->rawTemperature = 0;

	BMP280_ReadRegisters(me, 0xD0, 1);
	me->id = me->buffer[0];

	me->configReg = BMP280_getConfigReg(me);
	me->ctrlMeasReg = BMP280_getCtrlMeasReg(me);

	BMP280_ReadRegisters(me, 0x88, 24);

	for(int i = 0; i < 3; i ++) {
		me->calibT[i] = me->buffer[2*i + 1] << 8 | me->buffer[2*i];
	}
	for(int i = 0; i < 9; i ++) {
		me->calibP[i] = me->buffer[6 + 2*i + 1] << 8 | me->buffer[6 + 2*i];
	}
}

/*
 * Initialization of sensor with given settings
 */
void BMP280_SensorInitialize(BMP280 * const me, uint8_t mode, uint16_t standbyTime, uint16_t osrs_t, uint16_t osrs_p) {

	uint8_t settings[2] = {0};
	settings[0] = (osrs_t << 5) | (osrs_p << 2) | mode;
	settings[1] = (standbyTime << 5) | 0b00000; // filters to zero, maybe ill later change that

	HAL_I2C_Mem_Write(me->i2c_handler, me->slaveAddress, 0xF4, 1, settings, 1, HAL_MAX_DELAY); //??? tutaj nie dziala nawet jak sie chce 2B wpisac
	HAL_I2C_Mem_Write(me->i2c_handler, me->slaveAddress, 0xF5, 1, &settings[1], 1, HAL_MAX_DELAY);


}
void BMP280_ReadTemperature(BMP280 * const me) {

	//w zaleznosci od parametrow wewnetrznych...
	//BMP280_ReadRegisters(me, 0xFA, 3..2..1);


}
void BMP280_ReadPressure(BMP280 * const me);
void BMP280_ReadTemperatureAndPressure( BMP280 * const me);

void BMP280_ReadRegisters(BMP280* const me, uint8_t address, uint8_t bytes) {
	uint8_t ret[2];
	ret[0] = HAL_I2C_Master_Transmit(me->i2c_handler, me->slaveAddress | 0, &address, 1, HAL_MAX_DELAY); //not sure
	ret[1] = HAL_I2C_Master_Receive(me->i2c_handler, me->slaveAddress | 1, me->buffer, bytes, HAL_MAX_DELAY); //bytes cannot be greater than 24;

	ret[0] = 0;
}

void BMP280_WriteRegisters(BMP280 * const me, uint8_t* addresses, uint8_t*  data, uint8_t bytes) {
	//2 bytes of data => 4 bytes overall (2data+2add)

	uint8_t dataToWrite[bytes*2]; // add + data

	int counter = 0;
	for (int i = 0; i < bytes * 2; i+=2) {
		dataToWrite[i] = *(addresses + counter);
		dataToWrite[i+1] = *(data + counter);
		counter++;
	}
	//creating a table that contains addresses interspersed with data [add,data,add2,data2...]
	HAL_I2C_Master_Transmit(me->i2c_handler, me->slaveAddress, dataToWrite, bytes*2, HAL_MAX_DELAY);
}

void BMP280_setConfigReg(BMP280 * const me, uint8_t reg) {
	uint8_t add = 0xF5;
	if(reg & 1 == 1) Error_Handler(); // otherwise SPI would turn on
	BMP280_WriteRegisters(me, &add, reg, 1);
	me->configReg = reg;
}
void BMP280_setCtrlMeasReg(BMP280 * const me, uint8_t reg){
	uint8_t add = 0xF4; //CHECK THIS ONE
	BMP280_WriteRegisters(me, &add, reg, 1);
	me->ctrlMeasReg = reg;
}
float BMP280_getTemperature(BMP280 * const me){
	return 1;
}
float BMP280_getPressure(BMP280 * const me) {
	return 1;
}
uint8_t BMP280_getSensorID(BMP280 * const me){
	return me->id;
}
uint8_t BMP280_getConfigReg(BMP280 * const me) {
	return me->configReg;
}
uint8_t BMP280_getCtrlMeasReg(BMP280 * const me){
	return me->ctrlMeasReg;
}

void BMP280_ResetSensor(BMP280 * const me){
	uint8_t add = 0xE0;
	uint8_t reg = 0xB6;
	BMP280_WriteRegisters(me, &add, &reg, 1);
}
