/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    inne.c
 *      Purpose: Wheather Station - project
 *			Author: DarthSkipper & ArdeoDeo
 *			Date: 09-12-2017
 *----------------------------------------------------------------------------
 *      ^^^^^WHEATHER STATION^^^^^
 *---------------------------------------------------------------------------*/
#include "inne.h" 
/*************************************************************************
Function: delay_ms()
Purpose:  delay based on processor speed
Input:    time of waiting (ms)
Returns:  none          
**************************************************************************/
void delay_ms(int m)
{
	uint32_t i, j;
	for(j=0; j<m; j++)
	{
		for(i=0; i<SystemCoreClock /100000; i++) {}
	}	
}
/*************************************************************************
Function: string_dlugosc()
Purpose:  length of string
Input:    string
Returns:  length          
**************************************************************************/
int string_dlugosc(char *c)
{
	int dlugosc = 0;
	while((unsigned char)c[dlugosc] != 0x00) dlugosc++;
		
	return dlugosc;
}
/*************************************************************************
Function: int_na_char()
Purpose:  converts int on string (4 numbers max)
Input:    int
Returns:  string          
**************************************************************************/
char* int_na_char(int liczba)
{	
	static char tablica4[4];
	int i;
	
	for(i = 0; i<4; i++) tablica4[i] = 0;
	
	if(liczba > 999)
	{		
		for(i = 0; i<4; i++) tablica4[i] = 48;
		while (liczba > 999)
		{
			tablica4[0]++;
			liczba -= 1000;
		}
		while (liczba > 99)
		{
			tablica4[1]++;
			liczba -= 100;
		}
		while (liczba > 9)
		{
			tablica4[2]++;
			liczba -= 10;
		}
		while (liczba > 0)
		{
			tablica4[3]++;
			liczba -= 1;
		}
	}
	else if(liczba > 99)
	{
		for(i = 0; i<3; i++) tablica4[i] = 48;
		while (liczba > 99)
		{
			tablica4[0]++;
			liczba -= 100;
		}
		while (liczba > 9)
		{
			tablica4[1]++;
			liczba -= 10;
		}
		while (liczba > 0)
		{
			tablica4[2]++;
			liczba -= 1;
		}
	}
	else if(liczba > 9)
	{
		for(i = 0; i<2; i++) tablica4[i] = 48;
		while (liczba > 9)
		{
			tablica4[0]++;
			liczba -= 10;
		}
		while (liczba > 0)
		{
			tablica4[1]++;
			liczba -= 1;
		}
	}
	else
	{
		tablica4[0] = 48;
		while (liczba > 0)
		{
			tablica4[0]++;
			liczba -= 1;
		}		
	}
	
	return tablica4;
}
