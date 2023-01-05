#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "..\..\include\SPI_Config.h"
#include "..\..\include\LCD_Config.h"

u8 LCDpins;
///////////////////////////////////////////////////////////////////////////////////////////////////
void SPI_MasterInit(void)
{       
    CLR_BIT(SSPCON,SSPEN);
    
    // Register SSPSTAT 6-7
    CLR_BIT(SSPSTAT,SMP); // Input data sampled at middle of data output time
    SET_BIT(SSPSTAT,CKE); // Data transmitted on rising edge of SCK

    // Register SSPCON  0-5
    // SPI Master mode, clock = FOSC/4
    CLR_BIT(SSPCON,SSPM0);
    CLR_BIT(SSPCON,SSPM1);
    CLR_BIT(SSPCON,SSPM2);
    CLR_BIT(SSPCON,SSPM3);

    // Clock Polarity Select bit ,  Idle state for clock is a low level
    CLR_BIT(SSPCON,CKP);
    
    // Synchronous Serial Port Enable bit, Enables serial port and configures SCK, SDO, SDI and SS as the source of the serial port pins
    SET_BIT(SSPCON,SSPEN);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void SPI_IO_Init(void)
{

    SET_BIT(TRISA,B5); // SS must have TRISA5 bit set (input)
    CLR_BIT(TRISC,B3); // SCK (Master mode) must have TRISC3 bit cleared (output)
    CLR_BIT(TRISC,B5); // SDO has this bit cleared (output)
    
    CLR_BIT(TRISE,B0); // 74HC595 configuration (RCK)
}
///////////////////////////////////////////////////////////////////////////////////////////////////
/* Function writes to the SPI*/
u8 SPI_Transmit_Data(u8 _data)
{
    SSPBUF = _data; // write byte to SSPBUF register
    while (!SSPSTAT.BF); // wait until SSPBUF register if full
    return (SSPBUF);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
/* copies contents of LCD pins variable to parallel outputs of shift register (74HC595) */
void SPI_to_74HC595(void)
{
    SPI_Transmit_Data(LCDpins); // send LCD pins out the SPI
    SET_BIT(PORTE,B0);          // move data to parallel pins
    CLR_BIT(PORTE,B0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/* LCD initialization by instruction                */
/* 4-bit 2 line                                     */
/* wait times are set for 8MHz clock (TCY 500ns)    */
void LCD_Void_Init(void)
{
    LCDpins &= ~RS;
    PORTE.B0 = 0;
    /* wait 100msec */
    Delay_ms(100);
    /* send 0x03 */
    LCDpins = 0x30; // send 0x3
    LCDpins |= E;
    SPI_to_74HC595();
    LCDpins &= ~E;
    SPI_to_74HC595();
    /* wait 10ms */
    Delay_ms(10);
    LCDpins |= E; // send 0x3
    SPI_to_74HC595();
    LCDpins &= ~E;
    SPI_to_74HC595();
    /* wait 10ms */
    Delay_ms(10);
    LCDpins |= E; // send 0x3
    SPI_to_74HC595();
    LCDpins &= ~E;
    SPI_to_74HC595();
    /* wait 1ms */
    Delay_ms(10);
    LCDpins = 0x20; // send 0x2 - switch to 4-bit
    LCDpins |= E;
    SPI_to_74HC595();
    LCDpins &= ~E;
    SPI_to_74HC595();
    
    /* regular transfers start here */ /// LCD init
    Delay_ms(10);
    LCD_Sendcmd(0x28); // 4-bit 2-line 5x7-font
    Delay_ms(10);
    LCD_SendCmd(0x01); // clear display
    Delay_ms(10);
    LCD_SendCmd(0x0c); // turn off cursor, turn on display
    Delay_ms(10);
    LCD_SendCmd(0x06); // Increment cursor automatically
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void LCD_SendByte(u8 tosend)
{
    LCDpins &= 0x0f;            // prepare place for the upper nibble
    LCDpins |= (tosend & 0xf0); // copy upper nibble to LCD variable
    LCDpins |= E;               // send
    SPI_to_74HC595();
    LCDpins &= ~E;
    SPI_to_74HC595();
    LCDpins &= 0x0f;                 // prepare place for the lower nibble
    LCDpins |= (tosend << 4) & 0xf0; // copy lower nibble to LCD variable
    LCDpins |= E;                    // send
    SPI_to_74HC595();
    LCDpins &= ~E;
    SPI_to_74HC595();
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void LCD_Sendcmd(u8 a)
{
    LCDpins &= ~RS;
    LCD_SendByte(a);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void LCD_SendChar(u8 a)
{
    LCDpins |= RS;
    LCD_SendByte(a);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void LCD_Send_String(u8 *str_ptr)
{
    while (*str_ptr)
    {
        LCD_SendChar(*str_ptr);
        str_ptr++;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void LCD_Second_Row()
{
    LCD_SendCmd(0xc0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void LCD_Home()
{
    LCD_SendCmd(LCD_CLRSCR);
    Delay_ms(10);
    LCD_SendCmd(LCD_HOME);
}