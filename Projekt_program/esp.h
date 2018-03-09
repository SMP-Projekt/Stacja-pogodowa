/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    esp.h
 *      Purpose: Wheather Station - project
 *			Author: DarthSkipper & ArdeoDeo
 *			Date: 09-12-2017
 *----------------------------------------------------------------------------
 *      ^^^^^WHEATHER STATION^^^^^
 *---------------------------------------------------------------------------*/
#ifndef _esp_h
#define _esp_h

#include "MKL46Z4.h" 
#include "inne.h" 
#include "uart.h" 
#include "leds.h" 
#include "sensors.h" 

/* initialize of esp module */
void esp_init(void);
/* check if connected with IP and send website */
void website_run(void);

#endif
