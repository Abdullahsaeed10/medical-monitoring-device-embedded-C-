#ifndef _LCD_CONFIG_H
#define _LCD_CONFIG_H
#include "STD_TYPES.h"

//////Macros//////
#define RS 0x04 // RS pin
#define E 0x08  // E pin
#define SET_RS LCDpins |= RS
#define CLR_RS LCDpins &= ~RS
#define SET_E LCDpins |= E
#define CLR_E LCDpins &= ~E

#define Scroll_right 0x1e    /* Scroll display one character right (all lines) */
#define Scroll_left 0x18     /* Scroll display one character left (all lines)*/
#define LCD_HOME 0x02        /* Home (move cursor to top/left character position)*/
#define Cursor_left 0x10     /* Move cursor one character left*/
#define Cursor_right 0x14    /* Move cursor one character right */
#define Cursor_uline 0x0e    /* Turn on visible underline cursor */
#define Cursor_block 0x0f    /* Turn on visible blinking-block cursor */
#define Cursor_invis 0x0c    /* Make cursor invisible*/
#define Display_blank 0x08   /* Blank the display (without clearing)*/
#define Display_restore 0x0c /* Restore the display (with cursor hidden)*/
#define LCD_CLRSCR 0x01      /* Clear Screen*/
#define SET_CURSOR 0x80      /* Set cursor position (Set_cursor+DDRAM address)*/
#define Set_CGRAM 0x40       /* Set pointer in character-generator RAM Set_CGRAM+(CGRAM address)*/

//////Functions prototypes//////
void LCD_Void_Init(void);
void LCD_SendByte(u8 tosend);
void LCD_SendCmd(u8 a);
void LCD_SendChar(u8 a);
void LCD_Send_String(u8 *str_ptr);
void LCD_Second_Row();
void LCD_Home();

#endif