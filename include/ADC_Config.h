#ifndef _ADC_CONFIG_H
#define _ADC_CONFIG_H
#include "STD_TYPES.h"

 //////Macros//////
#define go 1
#define done 0
 //////Functions prototypes//////
void ADC_Init(void);
u16 ADC_GetResult(void);


#endif