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
	//ledsInitialize();
	turnOnSensors();
	uint8_t next = 1;
	while(1) 
	{
		switch(next)
		{
			case 1:
				slcdDisplay(temperatureRead()*100, 10);
				dot(2);
				slcdSet(0x0C, 4);
				next++;
			delay_mc(500);
				break;
			case 2:
				slcdDisplay(pressureRead(), 10);
				next++;
				delay_mc(500);
				break;
			case 3:
			slcdDisplay(humidityRead(), 10);
				next++;
			delay_mc(500);
				break;
			case 4:
				slcdDisplay(lightRead()*10, 10);
				dot(3);
				next=1;
				delay_mc(500);
				break;
		}
	};

}
