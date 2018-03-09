/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    inne.h
 *      Purpose: Wheather Station - project
 *			Author: DarthSkipper & ArdeoDeo
 *			Date: 09-12-2017
 *----------------------------------------------------------------------------
 *      ^^^^^WHEATHER STATION^^^^^
 *---------------------------------------------------------------------------*/
#ifndef _inne_h
#define _inne_h

#include "MKL46Z4.h" 

/* delay based on processor speed */
void delay_ms(int m);
/* length of string */
int string_dlugosc(char *c);
/* converts int on string (4 numbers max) */
char* int_na_char(int liczba2);

#endif
