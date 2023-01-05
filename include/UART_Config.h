#ifndef _UART_CONFIG_H
#define _UART_CONFIG_H
#include "STD_TYPES.h"

/////////Function Prototypes/////////
void Serial_Init();
void UART_IO_Init();
void TX_Charachter(u8* character);
void TX_String(u8* string);
void TX_Number(float);

#endif