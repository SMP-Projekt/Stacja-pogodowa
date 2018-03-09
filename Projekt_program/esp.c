/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    esp.c
 *      Purpose: Wheather Station - project
 *			Author: DarthSkipper & ArdeoDeo
 *			Date: 09-12-2017
 *----------------------------------------------------------------------------
 *      ^^^^^WHEATHER STATION^^^^^
 *---------------------------------------------------------------------------*/
#include "esp.h" 

int iteracja = 0;
char *strona0 = "<!DOCTYPE html><html lang=\"pl\"><head><meta charset=\"utf-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge,chrome=1\" /><title>Nucleo Wheather</title><meta http-equiv=\"Refresh\" content=\"8\" /><style type=\"text/css\">.wy{font-size: 50px;}</style></head><body style=\"background-color: #8fd5d9; margin: 20px;text-align:center;\"><header><h1 style=\"color: #3280ed; font-size: 80px;\">Stacja pogodowa Nucleo Wheather</h1></header><div style=\"color: #303030; font-size: 30px;\">By Marek Krupa & Michal Mrowiec</div><br /><br /><div class=\"wy\"><div>Pomiar nr: <span>";
char *strona1 = "</span></div><p></p><div>Temperatura: <span style=\"color: red; margin-left:20px;\">";
char *strona2 = "</span><span> st.C</span></div><div>Cisnienie: <span style=\"color: blue; margin-left:40px;\">";
char *strona3 = "</span><span> hPa</span></div><div>Wilgotnosc: <span style=\"color: green; margin-left:27px;\">";
char *strona4 = "</span><span> %rH</span></div><div>Naswietlenie: <span style=\"color: yellow; margin-left:17px;\">";		
char *strona5 = "</span><span> lux</span></div></div></body></html>   ";
/*************************************************************************
Function: esp_send_and_wait()
Purpose:  send commend to esp module and wait for answer
Input:    commend; time for waiting; what answer we want; stop enable condition
Returns:  0 if fail and error=0, 1 if success          
**************************************************************************/
int esp_send_and_wait(char*c, int czas, char *odp, int error)  //zabepieczenie na >1024
{
	int odliczanie = 0;
	uart_send_string(c);
	while(odliczanie < czas)
	{
		if(uart_find(odp, 0) == 1) return 1;
				
		delay_ms(1);
		odliczanie++;		
	}	
	
	while(error)
	{
		RedTogle();
		delay_ms(100);
	}
	return 0;	
}
/*************************************************************************
Function: esp_init()
Purpose:  initialize of esp module
Input:    none
Returns:  none          
**************************************************************************/
void esp_init()
{
	int i;
	for(i=0; i<informacja_dl; i++) informacja[i] = 0;
	
	esp_send_and_wait("AT+CWMODE=2\r\n", 1000, "OK", 1);
	esp_send_and_wait("AT+CWQAP\r\n", 1000, "OK", 1); //rozlacz z siecia
	esp_send_and_wait("AT+RST\r\n", 3000, "ready", 1);	
	esp_send_and_wait("AT+CIPMUX=1\r\n", 1000, "OK", 1);
	esp_send_and_wait("AT+CIPSERVER=1,80\r\n", 1000, "OK", 1);
	
	RX_clear();
}
/*************************************************************************
Function: esp_send_start()
Purpose:  first step of sending a data
Input:    count of bits which we want to send
Returns:  0 if fail, 1 if success          
**************************************************************************/
int esp_send_start(int dlugosc)
{	
	uart_send_string("AT+CIPSEND=0,");
	uart_send_string(int_na_char(dlugosc));
	return esp_send_and_wait("\r\n", 2000, "> ", 1);
}
/*************************************************************************
Function: esp_send_web()
Purpose:  send data necesery to build a website 
Input:    none
Returns:  0 if fail, 1 if success          
**************************************************************************/
int esp_send_web()
{
	uart_send_string(strona0);
	uart_send_string(int_na_char(iteracja));
	uart_send_string(strona1);
	uart_send_string(int_na_char((int)temperatureRead()));
	uart_send_string(strona2);
	uart_send_string(int_na_char(pressureRead()));
	uart_send_string(strona3);
	uart_send_string(int_na_char(humidityRead()));
	uart_send_string(strona4);
	uart_send_string(int_na_char((int)lightRead()));
	return esp_send_and_wait(strona5, 2000, "OK", 0);		
}
/*************************************************************************
Function: esp_send_end()
Purpose:  close connection after sending data
Input:    none
Returns:  1 if success, 0 if fail          
**************************************************************************/
int esp_send_end()
{	
	uart_send_string("AT+CIPCLOSE=0");
	return esp_send_and_wait("\r\n", 2000, "0,CLOSED", 0);	
}
/*************************************************************************
Function: website_run()
Purpose:  check if connected with IP and send website
Input:    none
Returns:  none          
**************************************************************************/
void website_run()
{	
	if(uart_find("0,CONNECT", 0))
	{
		RedOff();
		int stan = 0;
		stan = esp_send_start(string_dlugosc(strona0) + string_dlugosc(strona1) + string_dlugosc(strona2) + string_dlugosc(strona3) + string_dlugosc(strona4) + string_dlugosc(strona5) + string_dlugosc(int_na_char(iteracja)) + string_dlugosc(int_na_char((int)temperatureRead())) + string_dlugosc(int_na_char(pressureRead()) + string_dlugosc(int_na_char(humidityRead())) + string_dlugosc(int_na_char((int)lightRead()))));
		if(stan) stan = esp_send_web();	
		if(stan) esp_send_end();		
		iteracja++;
	}		
}

