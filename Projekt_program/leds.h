#ifndef leds_h
#define leds_h

void ledsInitialize(void);

void ledsOff (void);
void ledsOn (void);
void ledGreenOff (void);
void ledGreenOn (void);

void startStopFSM(void);
void ledsService1ms(void);
void nextLedState(void);
void miganie(void);
void migocz_czer(void);
void migocz_ziel(void);
void rgbON(void);
void rgbOFF(void);

unsigned char phaseA(void);
unsigned char phaseB(void);
unsigned char phaseC(void);

void fastSlowFSM(void);

extern unsigned char slowFSM;


#endif
