/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    uart.h
 *      Purpose: Wheather Station - project
 *			Author: DarthSkipper & ArdeoDeo
 *			Date: 09-12-2017
 *----------------------------------------------------------------------------
 *      ^^^^^WHEATHER STATION^^^^^
 *---------------------------------------------------------------------------*/
#ifndef _uart_h
#define _uart_h

#include "MKL46Z4.h" 
#include "inne.h"

#define Q_SIZE (1024) //length of array that storage received informations
#define informacja_dl 1024 //length of array used in uart_find() that saves bits after string
extern unsigned char informacja[informacja_dl];

/* clear storage */
void RX_clear(void);
/* initialize UART2 module */
void uart_init(void);
/* send char by UART2 */
void uart_send_char(unsigned char z);
/* send string by UART2 */
void uart_send_string(char *s);
/* read incoming char from UART2 */
unsigned char uart_read_char(void);

/** Additional functions **/

/* immediately send read char */
void echo(void);
/* find string in recived information and read some chars after it */
int uart_find(char *c, int ilosc);

#endif
