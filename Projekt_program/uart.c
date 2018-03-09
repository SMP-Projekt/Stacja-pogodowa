/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    uart.c
 *      Purpose: Wheather Station - project
 *			Author: DarthSkipper & ArdeoDeo
 *			Date: 09-12-2017
 *----------------------------------------------------------------------------
 *      ^^^^^WHEATHER STATION^^^^^
 *---------------------------------------------------------------------------*/
#include "uart.h" 

/*************************************************************************
Structure: Q_T()
Purpose:  stores information about read information from UART      
**************************************************************************/
typedef struct 
{
	unsigned char Data[Q_SIZE];
	unsigned int Head; //points to oldest data element
	unsigned int Tail; //points to next free space
	unsigned int Size; //quantity of elements in queue
} Q_T;

/*************************************************************************
Function: Q_Init()
Purpose:  initialize storage for incoming informations
Input:    storage address
Returns:  none          
**************************************************************************/
Q_T TxQ, RxQ;
void Q_Init(Q_T * q) 
{
	unsigned int i;
	for (i=0; i<Q_SIZE; i++) q->Data[i] = 0;
	q->Head = 0;
	q->Tail = 0;
	q->Size = 0;
}

/*************************************************************************
Function: Q_Enqueue()
Purpose:  add char to the storage
Input:    storage address; char to be stored
Returns:  0 if failure, 1 when success          
**************************************************************************/
int Q_Enqueue(Q_T * q, unsigned char d) 
{
	if (!(q->Size == Q_SIZE))
	{ 		
		q->Data[q->Tail++] = d;
		q->Tail %= Q_SIZE; //Must wrap circular buffer
		q->Size++;
		return 1;
	} 
	else return 0;
}

/*************************************************************************
Function: Q_Dequeue()
Purpose:  returns char from the storage
Input:    storage address
Returns:  stored char       
**************************************************************************/
unsigned char Q_Dequeue(Q_T * q) 
{
	unsigned char c = 0;
	if (!(q->Size == 0))
	{ 		
		c = q->Data[q->Head];
		q->Data[q->Head++] = 0;
		q->Head %= Q_SIZE; //Wrap circular buffer
		q->Size--;
	}
	return c;
}

/*************************************************************************
Function: RX_clear()
Purpose:  clear storage
Input:    none
Returns:  none      
**************************************************************************/
void RX_clear()
{
	Q_Init(&RxQ);
}

/*************************************************************************
Function: uart_init()
Purpose:  initialize UART2 module
Input:    none
Returns:  none          
**************************************************************************/
void uart_init()
{
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK; //syg taktujacy do uart2
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK; //syg taktujacy do portu E
	
	PORTD->PCR[4] = PORT_PCR_MUX(3); //PTD4 uart2_RX
	PORTD->PCR[5] = PORT_PCR_MUX(3); //PTD5 uart2_TX
		
	UART2->C2 |= !UART_C2_RE_MASK | !UART_C2_TE_MASK; //zablokowany nadajnik i odbiornik

	UART2->BDH = UART_BDH_SBR(0x00); //bus = 24M, BR = 9600, SBR = 156 = 0x9C
	UART2->BDL = UART_BDL_SBR(0x9C);
	
	UART2->BDH |= !UART_BDH_SBNS_MASK; //jeden bit stopu	
	UART2->C1 |= !UART_C1_M_MASK | !UART_C1_PE_MASK; //dlugosc danej: 8-bit, brak sprawdzania parzystosci

	UART2->C2 |= UART_C2_TIE_MASK |	UART_C2_RIE_MASK; //przerwania on
	
	UART2->C2 |= UART_C2_RE_MASK | UART_C2_TE_MASK; //odblokowany nadajnik i odbiornik


	NVIC_SetPriority(UART2_IRQn, 128);
	NVIC_ClearPendingIRQ(UART2_IRQn);
	NVIC_EnableIRQ(UART2_IRQn);
		
	Q_Init(&TxQ);
	Q_Init(&RxQ);
}

/*************************************************************************
Function: UART2_IRQHandler()
Purpose:  handle UART2 interrupt
Input:    none
Returns:  none          
**************************************************************************/
void UART2_IRQHandler() 
{
	NVIC_ClearPendingIRQ(UART2_IRQn);
	
	if (UART2->S1 & UART_S1_TDRE_MASK) 
	{		
		if (!(TxQ.Size == 0)) UART2->D = Q_Dequeue(&TxQ); //can send another character
		else UART2->C2 &= ~UART_C2_TIE_MASK; //queue is empty so disable tx
	}
	
	if (UART2->S1 & UART_S1_RDRF_MASK) 
	{
		if (!(RxQ.Size == Q_SIZE)) Q_Enqueue(&RxQ, UART2->D);
		else while (1); //error - queue full
	}
	
	if (UART2->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK | UART_S1_FE_MASK | UART_S1_PF_MASK)) {}; //handle the error, clear the flag
}

/*************************************************************************
Function: uart_send_char()
Purpose:  send char by UART2
Input:    char to be transmitted
Returns:  none          
**************************************************************************/
void uart_send_char(unsigned char z)
{
	while(!(UART2->S1 & UART_S1_TDRE_MASK));

	UART2->D = z;		
}

/*************************************************************************
Function: uart_send_string()
Purpose:  send string by UART2
Input:    string to be transmitted
Returns:  none          
**************************************************************************/
void uart_send_string(char *s)
{
	while((unsigned char)*s != 0) uart_send_char((unsigned char)*s++);
	delay_ms(100);
}

/*************************************************************************
Function: uart_read_char()
Purpose:  read incoming char from UART2
Input:    none
Returns:  readed char          
**************************************************************************/
unsigned char uart_read_char()
{
	while(!(UART2->S1 & UART_S1_RDRF_MASK));
		
	return UART2->D;	
}


/*
Additional functions
*/

/*************************************************************************
Function: echo()
Purpose:  immediately send read char
Input:    none
Returns:  none         
**************************************************************************/
void echo()
{
	if(!(RxQ.Size == 0))
	{	
		int t;
		for(t=0; t<RxQ.Size; t++) uart_send_char(Q_Dequeue(&RxQ));		
	}			
}

/*************************************************************************
Function: uart_find()
Purpose:  find string in recived information and read some chars after it
Input:    string that you want to find; how many chars you want to read after, 
					if varable is < 1 then function will return only 0 or 1
Returns:  0 if couldn't find string, 1 when find string, 2 when all bits had been reading     
**************************************************************************/
unsigned char informacja[informacja_dl];
int znaleziony = 0, w = 0, k = 0;
int uart_find(char *c, int ilosc)
{	
	if(!(RxQ.Size == 0))
	{
		unsigned char znak = Q_Dequeue(&RxQ);
		if(znaleziony) //znalazlem slowo
		{			
			informacja[w] = znak;
			w++;
			
			if(w == ilosc) //informacja odebrana
			{				
				w = 0;
				znaleziony = 0;
				
				RX_clear();
				return 2;
			}			
		}				
		else if(znak == (unsigned char)c[k]) //szukam slowa
		{
			k++;
			if(k == string_dlugosc(c))
			{				
				k = 0;
				if(ilosc > 0) znaleziony = 1;
				else RX_clear();
				
				return 1;
			}			
		}
		else k = 0;
	}
	
	return 0;
}
