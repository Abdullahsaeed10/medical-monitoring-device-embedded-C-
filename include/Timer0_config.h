#ifndef _TIMER0_CONFIG_H_
#define _TIMER0_CONFIG_H_

// TMR0 Clock Source Select bit
#define Timer 0
#define Counter 1
#define mode Timer

// interrupt enable or disable
#define Enabled 1
#define Disabled 2
#define interrupt Enabled

void TIMER0_voidInit(void);



#endif