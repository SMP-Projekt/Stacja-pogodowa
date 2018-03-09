/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    sleep.h
 *      Purpose: Wheather Station - project
 *			Author: DarthSkipper & ArdeoDeo
 *			Date: 09-12-2017
 *----------------------------------------------------------------------------
 *      ^^^^^WHEATHER STATION^^^^^
 *---------------------------------------------------------------------------*/
#ifndef _sleep_h
#define _sleep_h

#include "MKL46Z4.h" 

/* Normal wait mode */
void sleep(void);
/* Very low-power stop mode */
void deepsleep(void);

#endif
