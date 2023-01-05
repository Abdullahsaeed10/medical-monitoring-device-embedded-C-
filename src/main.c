#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "..\..\include\ADC_config.h"
#include "..\..\include\SPI_Config.h"
#include "..\..\include\LCD_Config.h"
#include "..\..\include\LM35_Config.h"
#include "..\..\include\UART_Config.h"
#include "..\..\include\Timer0_config.h"
#include "..\..\include\Timer1_config.h"
#include "..\..\include\heart_rate_sensor_config.h"




///// global variables /////
u8 timerCounter = 0;
u8 pulses = 0;
u8 counter = 0;

u8 lcd_conuter = 0;
u8 lcd_update = 1;

u8 uart_counter=0;
u8 uart_update =0;

u8 digital_heartRate;
u8 HeartRate[] = "000";
u8 counter_mode =0;


 void on_off_toggle(void)
 {
    // if switch is OPEN
   if(PORTD.B2 == 0)
    {
    // Turn on LED
    PORTD.B3=1;
    // Darlington Configuration LOW (to stop the heart rate buzzer and led )
    PORTD.B4=0;
    
    LCD_Home(); // clear LCD
    
    while(PORTD.B2 == 0);
    
    // Turn off LED
    PORTD.B3=0;

    }
 }
 void modes(void)
 {
  if (PORTD.B0 ==1)
    {
     // Turn on LED
     PORTD.B1=1;
      // increment counter mode
      counter_mode ++;
      // if the modes exceeded the number of modes make count = 0
      if (counter_mode == 3)
      {
          counter_mode=0;
      }
    }
 }

 void checker(void)
 {
       modes();
       on_off_toggle();
 }
void Interrupt()
{
     if(INTCON.T0IF==1) // Overflow every (0.0655) sec
      {
        timerCounter++;
        lcd_conuter++;
        uart_counter++;
        
        if(timerCounter == 230) // 15 sec for the HeartRate
        {
          pulses = counter;
          TMR1H=0;
          TMR1L=0;
          timerCounter = 0;
        }
        if(timerCounter == 0)
        {
          counter=0;
        }
        if ( lcd_conuter == 62)  // 4 sec for LCD
        {
         lcd_update = 1;
         lcd_conuter = 0;
        }
        if ( uart_counter == 154) // 10 sec  for UART
        {
         uart_update = 1;
         uart_counter = 0;
        }
        INTCON.T0IF=0;
      }
}

void main(void)
{

  /////Temperature sensor/////////////////////
   u8* Temperature_value;

  ///////call timer0 and timer1 init//////////
    TIMER0_voidInit(); // Timer mode
    TIMER1_voidInit(); // Counter mode
    
  /// LM35- ADC init /////////////////////////////
    LM35_sensor_init();
    ADC_Init();
    
  ///////////////SPI-LCD/////////////////////
    SPI_IO_Init();
    SPI_MasterInit();
    LCD_void_init();
    
  ///////////////UART-PC/////////////////////
    UART_IO_Init();
    Serial_Init();
    
    
    //////////////////////////////////////// #define  to the pins
     // inintalize the toggles
     // inputs button and switch
     TRISD.B2=1;
     TRISD.B0=1;
     // outputs LEDs
     TRISD.B1=0; // which one
     TRISD.B3=0;
     // Darlington Configuration
     TRISD.B4=0;
     
     // Darlington Configuration high
     PORTD.B4=1;
     // ON/OFF TOGGLE Low
     PORTD.B3=0;

     // config the analog pins
     SET_BIT(ANSEL,ANS0);
     SET_BIT(TRISA,TRISA0);


///////////////Program Code/////////////////////
while (1)
{
    // TOGGLE BUTTON LOW
    PORTD.B1=0;
    // Darlington Configuration high
    PORTD.B4=1;
    // check both ON/OFF TOGGLE & TOGGLE BUTTON
    checker();
    
    /////////////////////// HEART RATE ////////////////
    counter = (TMR1H<<8)|(TMR1L);      /// HERE !!!

    if (digital_heartRate > 99){
       HeartRate[0]  = 1 + 48;              // Put 1 (for hundreds)
    }
    else{
      HeartRate[0]  = ' ';               // Put space
    }
    digital_heartRate = pulses * 4;
    HeartRate[1]  = (digital_heartRate / 10) % 10  + 48;
    HeartRate[2]  = digital_heartRate % 10  + 48;
    //////////////////////////////////////////////////////
    
    // UART MODES get updated every 10 Sec
    if (uart_update == 1)
    {
       uart_update=0;

        checker();
        if (counter_mode == 0) // BPM and TEMP
          {
          // Send Data TO PC
          TX_String("Mode BPM & Temp");
          TX_Charachter(13);  // new Line
          TX_String(" BPM = ");
          TX_String(HeartRate);
          TX_Charachter(13);  // new Line

          TX_String(" Temp = ");
          TX_String(Temperature_value);
          TX_Charachter(13); // new Line
          }
          else if (counter_mode == 1) // TEMP ONLY
          {

          // Send Data To PC
          TX_String("Mode Temp only");
          TX_Charachter(13);  // new Line
          TX_String(" Temp = ");
          TX_String(Temperature_value);
          TX_Charachter(13); // new Line
          TX_String("---------");
          }
          else if (counter_mode == 2)  // BPM ONLY
          {
          // Send Data To PC
          TX_String("Mode BPM only");
          TX_Charachter(13); // new Line
          TX_String(" BPM = ");
          TX_String(HeartRate);
          TX_Charachter(13); // new Line
          TX_String("---------");
          }
        TX_Charachter(13); // new Line
        
        checker();
    }
    else
    {
      // wait for the 10 sec
    }
       

    if (lcd_update == 1)
    {
        lcd_update=0;
        
        checker();
       if (counter_mode == 0) // BPM and TEMP
          {
          LCD_Home(); // clear LCD
          LCD_Send_String(" BPM: ");
          LCD_Send_String(HeartRate);
          
          LCD_Second_Row();
          
          Temperature_value = LM35_SensorREAD(); // Read temperature
          LCD_Send_String(" Temp:");
          LCD_Send_String(Temperature_value);
          
          }
          else if (counter_mode == 1) // TEMP ONLY
          {
          LCD_Home(); // clear LCD
          // Display data on LCD
          Temperature_value = LM35_SensorREAD(); // Read temperature
          LCD_Send_String(" Temp:");
          LCD_Send_String(Temperature_value);

          }
          else if (counter_mode == 2) // BPM ONLY
          {
          LCD_Home(); // clear LCD
          // Display data on LCD
          LCD_Send_String(" BPM: ");
          LCD_Send_String(HeartRate);

          }
          checker();
        }
        else
        {
           // wait for the 4 Sec
        }
    }
}