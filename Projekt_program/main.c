/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    main.c
 *      Purpose: Wheather Station - project
 *			Author: DarthSkipper & ArdeoDeo
 *			Date: 09-12-2017
 *----------------------------------------------------------------------------
 *      ^^^^^WHEATHER STATION^^^^^
 *---------------------------------------------------------------------------*/
#include "MKL46Z4.h" 
#include "leds.h" 
#include "esp.h" 
#include "sensors.h" 
#include "sleep.h" 

int main(void)
{
	ledsInitialize();
	uart_init();
	esp_init();
	initI2C();
	turnOnSensors();
	
	RedOn();
	
	while(1)
	{		 
		website_run();
		RedOn();
		sleep();	
	}
}
