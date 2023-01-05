#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "..\..\include\UART_Config.h"

void Serial_Init()
{
    TXSTA = 0x20; // BRGH=0, TXEN = 1, Asynchronous Mode, 8-bit mode
    RCSTA = 0x80; // Serial Port enabled, 8-bit reception
    SPBRG = 5;    // 10417 baudrate for 4Mhz
    CLR_BIT(PIR1,TXIF);
    CLR_BIT(PIR1,RCIF);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

// transfer and print a character
void TX_Charachter(u8* character)
{
    TXREG = character;
    while (!PIR1.TXIF); // check if the transmitter register is empty
    CLR_BIT(PIR1,TXIF);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

// transfer and print a string
void TX_String(u8* string)
{

    while (* string)
    {

        if(*string == 223)  // to print the degree symbol ( � )
        {
           *string  = 176;
        }
        TX_Charachter(* string);  // Transmit predefined string
        string++;
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////

// transfer and pring a number
void TX_Number(float number)
{
    u8 tempTxt[7];
    FloatToStr(number, tempTxt);
//    IntToStr(number,tempTxt)  ;
    TX_String(tempTxt);
    
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void UART_IO_Init()
{
    PORTC = 0x00;
    ANSEL = 0x00; // Sets PORTC as Digital I/O
    CLR_BIT(TRISC,6);   // Output (TX)
    SET_BIT(TRISC,7);   // Input (RX)
}