#ifndef _SPI_CONFIG_H
#define _SPI_CONFIG_H
#include "STD_TYPES.h"
#include "BIT_MATH.h"

 //////Macros//////
 #define RCK PORTE.RE0

 //////Functions prototypes//////
 void SPI_MasterInit(void);
 u8 SPI_Transmit_Data ( u8 _data );
 void SPI_IO_Init(void);
 void SPI_to_74HC595(void);

 #endif