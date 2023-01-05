#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "..\..\include\ADC_Config.h"

void ADC_Init(void)
{
    // Configure Port
    SET_BIT(ANSEL,ANS0);    // configure the pin as Analog
    SET_BIT(TRISA,TRISA0); // configure the pin as input

    // Configure the ADC module
    // A/D Conversion Clock Select bits (FOSC/2)
    CLR_BIT(ADCON0,ADCS0);
    CLR_BIT(ADCON0,ADCS1);

    // Analog Channel Select bits (AN0)
    CLR_BIT(ADCON0,CHS0);
    CLR_BIT(ADCON0,CHS1);
    CLR_BIT(ADCON0,CHS2);
    CLR_BIT(ADCON0,CHS3);


    SET_BIT(ADCON0,ADON); // ADC Enable bit

    // Select result format
    CLR_BIT(ADCON1,ADFM); // Left justified

    // Voltage Reference
    CLR_BIT(ADCON1,VCFG0); // VSS
    CLR_BIT(ADCON1,VCFG1); // VDD

    ADCON0.B1 = go;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
u16 ADC_GetResult(void)
{

    ADCON0.B1 = go;
    while (ADCON0.B1 == 1);

    return ADRESH;
}