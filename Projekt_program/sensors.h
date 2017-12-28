/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    sensors.h
 *      Purpose: Wheather Station - project
 *			Author: Michal Mrowiec & Marek Krupa
 *			Date: 09-12-2017
 *----------------------------------------------------------------------------
 *      ^^^^^WHEATHER STATION^^^^^
 *---------------------------------------------------------------------------*/
 #ifndef sensors_h
 #define sensors_h
 #include "i2c.h"
 
 #define STLM75_ADDR 0x90		//temperature sensor address
 #define STLM75_TEMP 0x00		//register of temperature
 #define TSL25721_ADDR 0x72	// light sensor address
 #define TSL25721_C0DATA 0x14
 #define TSL25721_C1DATA 0x16
 #define TSL25721_ENABLE 0x00
 #define HTS221_ADDR 0xBF		// humidity sensor address
 #define HTS221_HUMIDITY_OUT_L 0x28 //reg_L of humidity
 #define HTS221_HUMIDITY_OUT_H 0x29	//reg_H of humidity
 #define HTS221_H0_rH_x2 0x30
 #define HTS221_H1_rH_x2 0x31
 #define HTS221_H0_T0_OUT 0x36
 #define HTS221_H1_T0_OUT 0x38
 #define LPS331_ADDR 0xBB		// pressure sensor address
 #define LPS331_PRESS_OUT_H 0x2A //reg_H of pressure
 #define LPS331_PRESS_OUT_L 0x29 //reg_L of pressure
 #define LPS331_PRESS_OUT_XL 0x28 //reg_XL of pressure
 
 void turnOnSensors(void);
 
 float temperatureRead(void);
 uint32_t pressureRead(void);
 uint32_t humidityRead(void);
 float lightRead(void);
 
 #endif