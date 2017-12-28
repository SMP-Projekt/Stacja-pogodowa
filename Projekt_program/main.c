/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    main.c
 *      Purpose: Wheather Station - project
 *			Author: Michal Mrowiec & Marek Krupa
 *			Date: 09-12-2017
 *----------------------------------------------------------------------------
 *      ^^^^^WHEATHER STATION^^^^^
 *---------------------------------------------------------------------------*/
#include "MKL46Z4.h"	/* Device header */
#include "sensors.h"
#include "slcd.h"
#include "leds.h"
 /*----------------------------------------------------------------------------
	Main function body
*----------------------------------------------------------------------------*/
int main(void)
{
	initI2C();
	slcdInitialize();
	ledsInitialize();
	turnOnSensors();
	//rgbON();
	uint8_t next = 1;
	while(1) 
	{
//		switch(next)
//		{
//			case 1:
//				slcdDisplay(temperatureRead()*100, 10);
//				dot(2);
//				slcdSet(0x0C, 4);
//				next++;
//				FPTC->PCOR = (1UL<<8);
//			delay_mc(500);
//				break;
//			case 2:
//				slcdDisplay(pressureRead(), 10);
//				next++;
//				FPTB->PCOR = (1UL<<18);
//			  FPTD->PCOR = (1UL<<3);
//				delay_mc(500);
//				break;
//			case 3:
//				slcdDisplay(humidityRead(), 10);
//				dot(3);
//				next++;
//				FPTD->PCOR = (1UL<<3);
//				delay_mc(500);
//				break;
//			case 4:
				slcdDisplay(lightRead(), 10);
//				dot(3);
//				next=1;
//				FPTD->PCOR = (1UL<<3);
//				FPTC->PCOR = (1UL<<8);
//				delay_mc(500);
//				break;
//		}
//		rgbOFF();
	};

}