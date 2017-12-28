/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    i2c.c
 *      Purpose: Wheather Station - project
 *			Author: Michal Mrowiec & Marek Krupa
 *			Date: 09-12-2017
 *----------------------------------------------------------------------------
 *      ^^^^^WHEATHER STATION^^^^^
 *---------------------------------------------------------------------------*/
 #include "i2c.h"
 #include "extra.h" 

 /*----------------------------------------------------------------------------
	Function initializing I2C (see page 740 Reference Manual)
*----------------------------------------------------------------------------*/
void initI2C(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;	/* Enable clock for PORTC */
	SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;	/* Enable clock for I2C1 */
	
	PORTE->PCR[PORTE_SCL] = PORT_PCR_MUX(6);		/* PORTE 1 as I2C_SCL */
	PORTE->PCR[PORTE_SDA] = PORT_PCR_MUX(6);		/* PORTE 0 as I2C_SDA */
	
	I2C1->F = 0x14;		/* SDA hold time = 2.125us, SCL start hold time = 4.25us, SCL stop hold time = 5.125us */	
	I2C1->C1 |= I2C_C1_IICEN_MASK | I2C_C1_IICIE_MASK; /* I2C enable with interrupts */
	
}
/*----------------------------------------------------------------------------
	Enable ACK
*----------------------------------------------------------------------------*/
void I2C_enableAck(void)
{
	I2C1->C1 &= ~I2C_C1_TXAK_MASK;
}
/*----------------------------------------------------------------------------
	Disable ACK
*----------------------------------------------------------------------------*/
void I2C_disableAck(void)
{
	I2C1->C1 |= I2C_C1_TXAK_MASK;
}
/*----------------------------------------------------------------------------
	Repeat START
*----------------------------------------------------------------------------*/
void I2C_repeatedStart(void)
{
	I2C1->C1 |= I2C_C1_RSTA_MASK;
}
/*----------------------------------------------------------------------------
	Enable transmission and master mode
*----------------------------------------------------------------------------*/
void I2C_start(void)
{
	I2C1->C1 |= I2C_C1_TX_MASK | I2C_C1_MST_MASK;
}
/*----------------------------------------------------------------------------
	Disable transmission and master mode
*----------------------------------------------------------------------------*/
void I2C_stop(void)
{
	I2C1->C1 &= ~I2C_C1_MST_MASK;
  I2C1->C1 &= ~I2C_C1_TX_MASK;
}
/*----------------------------------------------------------------------------
	Enter Rx mode
*----------------------------------------------------------------------------*/
void I2C_enterRxMode(void)
{
	I2C1->C1 &= ~I2C_C1_TX_MASK;		/* RECEIVE MODE */
}
/*----------------------------------------------------------------------------
	Write to I2C
*----------------------------------------------------------------------------*/
void I2C_writeByte(uint32_t data)
{
	I2C1->D = data;
}
/*----------------------------------------------------------------------------
	Read I2C
*----------------------------------------------------------------------------*/
char I2C_readByte(void)
{
	return I2C1->D;
}
/*----------------------------------------------------------------------------
	Wait until 8 bits has been transmitted or received
*----------------------------------------------------------------------------*/
void I2C_wait(void) 
{    
  while((I2C1->S & I2C_S_IICIF_MASK)==0) {}  		
	I2C1->S |= I2C_S_IICIF_MASK; 		/* Clear the interrupt flag */   
}
/*----------------------------------------------------------------------------
	Write 8 bits of data to device register 
*----------------------------------------------------------------------------*/
void I2C_writeRegister(uint8_t u8SlaveAddress, uint8_t u8RegisterAddress, uint8_t u8Data)
{
	I2C_start();	          
	I2C_writeByte(u8SlaveAddress & 0xFE);									/* Send I2C device address with W/R bit = 0 */
	I2C_wait();

	I2C_writeByte(u8RegisterAddress);										/* Send register address */
	I2C_wait();

	I2C_writeByte(u8Data);												/* Send the data */
	I2C_wait();

	I2C_stop();

  delay_mc(50);
}
/*----------------------------------------------------------------------------
	Read 8 bits of data from device register and return it
*----------------------------------------------------------------------------*/
uint8_t I2C_ReadRegister(uint8_t u8SlaveAddress, uint8_t u8RegisterAddress)
{
	uint8_t result;
	  
	I2C_start();	          
	I2C_writeByte(u8SlaveAddress & 0xFE);							/* Send I2C device address with W/R bit = 0 */
	I2C_wait();										
	
	I2C_writeByte(u8RegisterAddress);								/* Send register address */
	I2C_wait();

	I2C_repeatedStart();
	
	I2C_writeByte(u8SlaveAddress | 0x01);		/* Send I2C device address this time with W/R bit = 1 */ 
	I2C_wait();	

	I2C_enterRxMode();
	I2C_disableAck();

	result = I2C_readByte();												
	I2C_wait();
	I2C_stop();  
	result = I2C_readByte();
	delay_mc(50);
	return result;
} 
/*----------------------------------------------------------------------------
	Read 8 bits of data from device register and put it in pointer's variable
*----------------------------------------------------------------------------*/
void I2C_ReadMultiRegisters(uint8_t u8SlaveAddress, uint8_t u8RegisterAddress, uint8_t n, uint8_t *data)
{
	char i;
	
	I2C_start();	
	I2C_writeByte(u8SlaveAddress & 0xFE);										/* Send I2C device address with W/R bit = 0 */
	I2C_wait();	
	
	I2C_writeByte(u8RegisterAddress);										/* Send register address */
	I2C_wait();

	I2C_repeatedStart();
		
	I2C_writeByte(u8SlaveAddress | 0x01);							/* Send I2C device address this time with W/R bit = 1 */ 
	I2C_wait();	

	I2C_enterRxMode();
	I2C_enableAck();
	
	i = I2C_readByte();
	I2C_wait();
	
	for(i=0; i<n-2; i++) 
	{
	    *data = I2C_readByte();
	    data++;
	    I2C_wait();
	}
	
	I2C_disableAck();
	*data = I2C_readByte();
	data++;
	I2C_wait();
	I2C_stop();
	*data = I2C_readByte(); 
	delay_mc(50);		
}
