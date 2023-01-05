#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "..\..\include\Timer1_config.h"

void TIMER1_voidInit(void)
{
     //Timer1 On bit
     #if timer == Enabled
     SET_BIT(T1CON,TMR1ON);  //  Timer1 Enable
     #elif timer == Disabled
     CLR_BIT(T1CON,TMR1ON);  //  Timer1 disable
     #endif

     //Timer1 Clock Source Select bit
     #if clock == external
     SET_BIT(T1CON,TMR1CS);  //External clock from T1CKI pin (on the rising edge)
     #elif clock == internal
     CLR_BIT(T1CON,TMR1CS);  //Internal clock (FOSC/4)
     #endif

     // Initialize 2 registers (16bit)
     TMR1H = 0; //Register for the MSB of the 16-bit TMR1 Register
     TMR1L = 0; //Register for the LSB of the 16-bit TMR1 Register

}