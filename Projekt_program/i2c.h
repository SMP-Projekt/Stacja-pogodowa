/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    i2c.h
 *      Purpose: Wheather Station - project
 *			Author: Michal Mrowiec & Marek Krupa
 *			Date: 09-12-2017
 *----------------------------------------------------------------------------
 *      ^^^^^WHEATHER STATION^^^^^
 *---------------------------------------------------------------------------*/
 #ifndef i2c_h
 #define i2c_h
 #include "MKL46Z4.h"	/* Device header */	
 
 #define I2C1_Interrupt (IRQn_Type) 9
 #define PORTE_SCL 1
 #define PORTE_SDA 0
 
 void initI2C(void);
 void I2C_enableACK(void);
 void I2C_disableACK(void);
 void I2C_repeatedStart(void);
 void I2C_start(void);
 void I2C_stop(void);
 void I2C_enterRxMode(void);
 void I2C_writeByte(uint32_t data);
 char I2C_read_byte(void);
 void I2C_wait(void);
 
 void I2C_writeRegister(uint8_t u8SlaveAddress, uint8_t u8RegisterAddress, uint8_t u8Data);
 unsigned char I2C_ReadRegister(uint8_t u8SlaveAddress, uint8_t u8RegisterAddress);
 void I2C_ReadMultiRegisters(uint8_t u8SlaveAddress, uint8_t u8RegisterAddress, uint8_t n, uint8_t *data);


 #endif