 #include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "..\..\include\LM35_Config.h"
#include "..\..\include\adc_config.h"

void LM35_sensor_init(void)
{
 PORTA=0x00;
 SET_BIT(TRISA,RA0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
u8* LM35_SensorREAD(void)
{
 // variables init
    u16 digital_temperarure;
    u8 Temperature[] = " 00.0 C";
    u16 reading_value;
    
   // reading the output from the ADC
   reading_value = ADC_GetResult() ;
   
    // Fixed Ratio = 0.488 to convert voltge value to degrees
   digital_temperarure = reading_value * (500.0/255.0); //500 --> 50mV/Celisus scaling factor
                                                        //255 --> because we return 8-bit

    if (digital_temperarure > 99)
      Temperature[0]  = 1 + 48;              // Put 1 (for hundreds)
    else
      Temperature[0]  = ' ';               // Put space

    Temperature[1]  = (digital_temperarure / 10) % 10  + 48;
    Temperature[2]  =  digital_temperarure % 10  + 48;
    Temperature[5] = 223;               // Print degree symbol ( � )

    return Temperature;
}