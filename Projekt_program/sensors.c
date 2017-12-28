/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    sensors.c
 *      Purpose: Wheather Station - project
 *			Author: Michal Mrowiec & Marek Krupa
 *			Date: 09-12-2017
 *----------------------------------------------------------------------------
 *      ^^^^^WHEATHER STATION^^^^^
 *---------------------------------------------------------------------------*/
 #include "sensors.h"
 /*----------------------------------------------------------------------------
	Function setting registeres of sensors
*----------------------------------------------------------------------------*/
 void turnOnSensors(void)
 {
	I2C_writeRegister(LPS331_ADDR, 0x20, 0x10);		/* Set measure pressure in 1 Hz speed */
	I2C_writeRegister(LPS331_ADDR, 0x20, 0x90);		/* Turn on pressure sensor */
	I2C_writeRegister(HTS221_ADDR, 0x20, 0x81);		/* Turn on humidity and set 1 Hz measure */
	I2C_writeRegister(TSL25721_ADDR, 0x01, 0xED);	/* 51.87 ms */
	I2C_writeRegister(TSL25721_ADDR, 0x0F, 0x02);	/* Set gain */
	I2C_writeRegister(TSL25721_ADDR, 0x00, 0x03);	/* Turn on light sensor */
	I2C_writeRegister(TSL25721_ADDR, 0x0D, 0x04);	/* Scale gain by 0.16 */
	 
	 
 }
/*----------------------------------------------------------------------------
	Function returning temperature
*----------------------------------------------------------------------------*/
float temperatureRead(void)
{
	float result;
	uint8_t STLM75Data[2];
	uint16_t temp;
	
	I2C_ReadMultiRegisters(STLM75_ADDR, STLM75_TEMP, 2, STLM75Data);
	/* Add 2 bytes in one (16) */
	temp = STLM75Data[1] | (STLM75Data[0] << 8); 
 
	if(temp && (uint16_t)(1 << 8) == 1) /* Temperature on minus */
		result = -(float)(temp >> 7)*0.5;
	else
		result = (float)(temp >> 7)*0.5;
	
	return result;
}
/*----------------------------------------------------------------------------
	Function returning pressure
*----------------------------------------------------------------------------*/
uint32_t pressureRead(void)
{
	uint8_t LPS331Data[3];
	uint32_t press;
	
	/* Read pressure registers (3 x 8bit) and merge them */
	LPS331Data[0] = I2C_ReadRegister(LPS331_ADDR, LPS331_PRESS_OUT_XL);
	LPS331Data[1] = I2C_ReadRegister(LPS331_ADDR, LPS331_PRESS_OUT_L);
	LPS331Data[2] = I2C_ReadRegister(LPS331_ADDR, LPS331_PRESS_OUT_H);
	
	press = ((uint32_t)(LPS331Data[2]<<16)) | ((uint16_t)(LPS331Data[1]<<8)) | LPS331Data[0];
	press /= 4096;
	
	return press;
}
/*----------------------------------------------------------------------------
	Function returning humidity
*----------------------------------------------------------------------------*/
uint32_t humidityRead(void)
{
	int16_t H0_T0_out, H1_T0_out, H_T_out;
	int16_t H0_rh, H1_rh;
	uint8_t HTS221Data[2];
	uint32_t tmp, humi;
	
	/* Read H0_rH and H1_rH coefficients */
	I2C_ReadMultiRegisters(HTS221_ADDR, HTS221_H0_rH_x2, 2, HTS221Data);
	H0_rh = HTS221Data[0]>>1;
	H1_rh = HTS221Data[1]>>1;
	/* Read H0_T0_OUT */
	I2C_ReadMultiRegisters(HTS221_ADDR, HTS221_H0_T0_OUT, 2, HTS221Data);
	H0_T0_out = ((uint16_t)(HTS221Data[1]<<8)) | (uint16_t)HTS221Data[0];
	/* Read H1_T0_OUT */
	I2C_ReadMultiRegisters(HTS221_ADDR, HTS221_H1_T0_OUT, 2, HTS221Data);
	H1_T0_out = ((uint16_t)(HTS221Data[1]<<8)) | (uint16_t)HTS221Data[0];
	/* ReadH_T_OUT */
	I2C_ReadMultiRegisters(HTS221_ADDR, HTS221_HUMIDITY_OUT_L, 2, HTS221Data);
	H_T_out = ((uint16_t)(HTS221Data[1]<<8)) | (uint16_t)HTS221Data[0];
	/* Compute the RH [%] value by linear interpolation */
	tmp = ((uint32_t)(H_T_out - H0_T0_out)) * ((uint32_t)((H1_rh - H0_rh)*10));
	humi = tmp/((uint32_t)(H1_T0_out - H0_T0_out)) + (((uint32_t)H0_rh)*10);

	return humi;
}
/*----------------------------------------------------------------------------
	Function returning light
*----------------------------------------------------------------------------*/
float lightRead(void)
{
	float lux1;
	float lux2;
	float CPL = 1.729; //0.455	//(ATIME_ms(51.87)*AGAINx(2.0))/(GA(1)*60)
	CPL /=6;
	int16_t C0Data, C1Data;
	uint8_t TSL25721_Data[2];
	
	/* Read C0DATA coefficients */
	I2C_ReadMultiRegisters(TSL25721_ADDR, TSL25721_C0DATA, 2, TSL25721_Data);
	C0Data = (int16_t)(TSL25721_Data[1]<<8) | (int16_t)TSL25721_Data[0];
	/* Read C1DATA coefficients */
	I2C_ReadMultiRegisters(TSL25721_ADDR, TSL25721_C1DATA, 2, TSL25721_Data);
	C1Data = (int16_t)(TSL25721_Data[1]<<8) | (int16_t)TSL25721_Data[0];
	/* Calculate lux */
	lux1 = ((float)C0Data - 1.87 * (float)C1Data)/CPL;
	lux2 = (0.63 * (float)C0Data - (float)C1Data)/CPL;
	
	/* Final light is max of light1, light2 or 0 */
	if (lux1>lux2) return lux1;
	else if (lux1 < 0 && lux2 < 0) return 0;
	else return lux2;
}