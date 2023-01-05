#ifndef _TEMP_SENSOR_CONFIG_H
#define _TEMP_SENSOR_CONFIG_H
#include "STD_TYPES.h"
#include "ADC_config.h"

 //////Functions prototypes//////
void LM35_sensor_init(void);
u8* LM35_SensorREAD(void);

#endif