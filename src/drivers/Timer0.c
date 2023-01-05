#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "..\..\include\Timer0_config.h"

void TIMER0_voidInit(void)
{
     //TMR0 Clock Source Select bit
     #if mode == Timer
     CLR_BIT(OPTION_REG,T0CS);   // Timer mode
     #elif mode == Counter
     SET_BIT(OPTION_REG,T0CS);   // Counter mode
     #endif

     //TMR0 Source Edge Select bit
     CLR_BIT(OPTION_REG,T0SE); // Increment on Rising Edge

     //PSA: Prescaler Assignment bit
     CLR_BIT(OPTION_REG,PSA); // Prescaler is assigned to the Timer0 module

     //PS<2:0>: Prescaler Rate Select bits
     SET_BIT(OPTION_REG,PS2);
     SET_BIT(OPTION_REG,PS1);
     SET_BIT(OPTION_REG,PS0); // TMR0 RATE  1 : 256

     #if interrupt == Enabled
      SET_BIT(INTCON,GIE); // global interrupt enable
      SET_BIT(INTCON,PEIE);  // periferal interrupt  enable
      SET_BIT(INTCON,T0IE);   // Timer0 interrupt enable
      #elif interrupt == Disabled
      CLR_BIT(INTCON,GIE); // global interrupt Disabled
      CLR_BIT(INTCON,PEIE);  // periferal interrupt  Disabled
      CLR_BIT(INTCON,T0IE);   // Timer0 interrupt Disabled
      #endif

}