/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    LEDS.C
 *      Purpose: Microprocessors Laboratory
 *----------------------------------------------------------------------------
 *      
 *      Author: Pawel Russek AGH University of Science and Technology
 *---------------------------------------------------------------------------*/

#include "MKL46Z4.h"                    //Device header
#include "leds.h"												//Declarations

const uint32_t red_mask= 1UL<<5;				//Red led is Port D bit 5
const uint32_t green_mask= 1UL<<29;			//Green led is Port C bit 5/


const unsigned int PHASE_DELAY_MS=400;		//FSM delay 
const unsigned char PHASE_A=0;						//FSM state Red=on Green=off
const unsigned char PHASE_B=1;						//FSM state Red=off Green=on
const unsigned char PHASE_C=2;						//FSM state Red=off Green=off

unsigned char slowFSM =1;									//FSM speed control flag. Initialize to 1: fast
unsigned char skipPhase = 0;							//Auxiliary variable to allow FSM slow mode					

unsigned char startFSM;										//FSM go control
unsigned char phase;											//FSM current state
unsigned int nextStateDelay;							//FSM delay counter


unsigned int migotac_czer = 0;
unsigned int migotac_ziel = 0;


/*----------------------------------------------------------------------------
  Function that initializes LEDs
 *----------------------------------------------------------------------------*/
void ledsInitialize(void) {
volatile int delay;
	uint8_t i;
	
//Initialize registers	
  SIM->SCGC5 |=  (SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK | SIM_SCGC5_PORTA_MASK);      /* Enable Clock to Port D & E */ 
  PORTD->PCR[5] = PORT_PCR_MUX(1);                       /* Pin PTD5 is GPIO */
  PORTE->PCR[29] = PORT_PCR_MUX(1);                      /* Pin PTE29 is GPIO */
  PORTC->PCR[8] = PORT_PCR_MUX(1);
	PORTD->PCR[3] = PORT_PCR_MUX(1);
	PORTB->PCR[18] = PORT_PCR_MUX(1);
	
	FPTD->PSOR = red_mask;          /* switch Red LED off */
	FPTE->PSOR = green_mask	;        /* switch Green LED off */
  FPTD->PDDR = red_mask | (1UL<<3);          /* enable PTB18/19 as Output */
	FPTE->PDDR = green_mask	;        /* enable PTB18/19 as Output */
	FPTC->PDDR = (1UL<<8);
	FPTB->PDDR = (1UL<<18);
	
	nextStateDelay=0;
	phase=PHASE_A;
	startFSM=1;
	
	FPTC->PSOR = (1UL<<8);
	FPTD->PSOR = (1UL<<3);
	FPTB->PSOR = (1UL<<18);
//Welcome sequence

		FPTD->PSOR=red_mask;          /* switch Red LED off  */
	  FPTE->PSOR=green_mask;        /* switch Green LED off  */
}

/*----------------------------------------------------------------------------
  Function that turns on RGB LED
 *----------------------------------------------------------------------------*/
void rgbON(void)
{
	FPTC->PCOR = (1UL<<8);
	FPTD->PCOR = (1UL<<3);
	FPTB->PCOR = (1UL<<18);
	
}
/*----------------------------------------------------------------------------
  Function that turns off RGB LED
 *----------------------------------------------------------------------------*/
void rgbOFF(void)
{
	FPTC->PSOR = (1UL<<8);
	FPTD->PSOR = (1UL<<3);
	FPTB->PSOR = (1UL<<18);
	
}
/*----------------------------------------------------------------------------
  Function that turns on Red LED
 *----------------------------------------------------------------------------*/
void ledRedOn (void) {
	FPTD->PCOR=red_mask;          	/* switch Red LED on */
	FPTE->PSOR=green_mask;          /* switch Green LED off */
}

/*----------------------------------------------------------------------------
  Function that turns on Green LED
 *----------------------------------------------------------------------------*/
void ledGreenOn (void) {
	FPTE->PCOR=green_mask;       		/* switch Green LED on */
	FPTD->PSOR=red_mask;          	/* switch Red LED off  */
}

/*----------------------------------------------------------------------------
  Function that turns all LEDs off
 *----------------------------------------------------------------------------*/
void ledsOff (void) {
		FPTD->PSOR=red_mask;          /* switch Red LED off  */
	  FPTE->PSOR=green_mask;        /* switch Green LED off  */
}

/*----------------------------------------------------------------------------
  Function that turns all LEDs on
 *----------------------------------------------------------------------------*/
void ledsOn (void) {
		FPTD->PCOR=red_mask;      	/* switch Red LED on  */
	  FPTE->PCOR=green_mask;     	/* switch Green LED on */
}

/*----------------------------------------------------------------------------
 Function that moves FSM to phase A 
 *----------------------------------------------------------------------------*/
unsigned char phaseA(void){
	ledsOff();
	ledRedOn();
	return PHASE_B;								/*Return next state of FSM*/
}

/*----------------------------------------------------------------------------
 Function that moves FSM to phase B   
 *----------------------------------------------------------------------------*/
unsigned char phaseB(void){
	ledsOff();
	ledGreenOn();
	return PHASE_C;								/*Return next state of FSM*/				
}

/*----------------------------------------------------------------------------
 Function that moves FSM to phase C     
 *----------------------------------------------------------------------------*/
unsigned char phaseC(void){
	ledsOff();
	return PHASE_A;								/*Return next state of FSM*/
}

/*----------------------------------------------------------------------------
 Function that stops FSM transitions     
 *----------------------------------------------------------------------------*/
void startStopFSM(void){
	startFSM^=1;
}

/*----------------------------------------------------------------------------
 Every 1 ms function that makes FSM run    
 *----------------------------------------------------------------------------*/
void ledsService1ms (void) {	
	miganie();	
	
	if(nextStateDelay!=PHASE_DELAY_MS){
		nextStateDelay+=startFSM;
		return;
	}	
	
	nextStateDelay=0;
	
	nextLedState();
}

/*----------------------------------------------------------------------------
 Function that makes FSM transition to the next state  
 *----------------------------------------------------------------------------*/

void nextLedState (void) {	
 
	/** Allow slower FSM transition */
	if (slowFSM==0) {
			skipPhase+=1;
			if( (skipPhase%3) != 0 ) return;		/* Every third call passes  to switch clause*/
	}
	/**/
	
	switch(phase){
		case PHASE_A:
			phase=phaseA();
			break;
		case PHASE_B:
			phase=phaseB();
		  break;
		default:
			phase=phaseC();
		  break;
	}
}

/*----------------------------------------------------------------------------
 Function controls transition speed of the FSM  
 *----------------------------------------------------------------------------*/
void fastSlowFSM(void){	
	slowFSM^=1;				/* Toggle speed mode */
}

/* Initialize of red toggle */
void migocz_czer(void)
{
	migotac_czer = 1;
}
/* Initialize of green toggle */
void migocz_ziel(void)
{
	migotac_ziel = 1;
}
/* Function for interrupts of buttons */
void miganie(void)
{	
	volatile int delay;
	uint8_t i;	//loop's repeat
	
	/* If interrupt from SW3 */
	if(migotac_czer)
	{
		migotac_czer = 0;
		for(i=30; i>1; i--)
		{
			if(migotac_ziel || migotac_czer) break;	/* If appear interupt from any button, break */
			FPTE->PTOR = 1UL<<29;		/* Toggle red diod */
			for(delay=0; delay<8000*i; delay++);
		}			
	}	
	/* If interrupt from SW1 */
	if(migotac_ziel)
	{
		migotac_ziel = 0;
		for(i=30; i>1; i--)
		{
			if(migotac_czer || migotac_ziel) break;	/* If appear interupt from any button, break */
			FPTD->PTOR = 1UL<<5;		/* Toggle green diod */
			for(delay=0; delay<8000*i; delay++);
		}		
	}
}
