#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "..\..\include\heart_rate_sensor_config.h"

u8* HEARTRATE_Bpm(u8 digital_heartRate)
{
        u8 HeartRate[] = "000";
        if (digital_heartRate > 99){
           HeartRate[0]  = 1 + 48;              // Put 1 (for hundreds)
        }
        else{
          HeartRate[0]  = ' ';               // Put space
        }
        HeartRate[1]  = (digital_heartRate / 10) % 10  + 48;
        HeartRate[2]  = digital_heartRate % 10  + 48;

        return HeartRate;
}