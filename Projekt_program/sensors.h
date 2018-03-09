/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    sensors.h
 *      Purpose: Wheather Station - project
 *			Author: DarthSkipper & ArdeoDeo
 *			Date: 09-12-2017
 *----------------------------------------------------------------------------
 *      ^^^^^WHEATHER STATION^^^^^
 *---------------------------------------------------------------------------*/
 #ifndef sensors_h
 #define sensors_h
 #include "i2c.h"
 #include "inne.h"
 
 /* Temperature sensor's registers */
 #define STLM75_ADDR 0x90		
 #define STLM75_TEMP 0x00		
 /* Light sensor's registers */
 #define TSL25721_ADDR 0x72
 #define TSL25721_C0DATA 0x14
 #define TSL25721_C0DATA2 0x15
 #define TSL25721_C1DATA 0x16
 #define TSL25721_C1DATA2 0x17
 /* Humidity sensor's registers */
 #define HTS221_ADDR 0xBE		
 #define HTS221_HUMIDITY_OUT_L 0x28 
 #define HTS221_HUMIDITY_OUT_H 0x29	
 #define HTS221_H0_rH_x2 0x30
 #define HTS221_H1_rH_x2 0x31
 #define HTS221_H0_T0_OUT 0x36
 #define HTS221_H0_T0_OUT2 0x37
 #define HTS221_H1_T0_OUT 0x3A
 #define HTS221_H1_T0_OUT2 0x3B
 /* Pressure sensor's registers */
 #define LPS331_ADDR 0xBB	
 #define LPS331_PRESS_OUT_H 0x2A
 #define LPS331_PRESS_OUT_L 0x29 
 #define LPS331_PRESS_OUT_XL 0x28 
 
 /* Initializing of sensors */
 void turnOnSensors(void);
 
 /****************************************************************
  Functions reading Nucleo Weather 
	****************************************************************/
 /* Function returning temperature */
 float temperatureRead(void);
 /* Function returning pressure */
 uint32_t pressureRead(void);
 /* Function returning humidity */
 uint32_t humidityRead(void);
 /* Function returning light */
 float lightRead(void);
 
 #endif
