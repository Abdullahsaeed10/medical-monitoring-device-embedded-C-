#ifndef _TIMER1_CONFIG_H_
#define _TIMER1_CONFIG_H_

// enable or disable  timer1
#define Enabled 1
#define Disabled 2
#define timer Enabled

// clock source internal or external
#define internal 1
#define external 2
#define clock external

void TIMER1_voidInit(void);

#endif