//******************************************************************************
//    THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY.
//    AUTHOR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
//    OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
//    FROM USE OF THIS SOFTWARE.
//******************************************************************************

//##############################################################################
// lcd_hd44780.h
//##############################################################################

//****************************************************************************//
#include "main.h"


#define LCD_D4 GPIO_Pin_1
#define LCD_D5 GPIO_Pin_5
#define LCD_D6 GPIO_Pin_7
#define LCD_D7 GPIO_Pin_5

#define LCD_RS GPIO_Pin_13
#define LCD_EN GPIO_Pin_13
//******************************************************************************//


#define HD44780_CLEAR                            0x01

#define HD44780_HOME                             0x02

#define HD44780_ENTRY_MODE                       0x04
#define HD44780_EM_SHIFT_CURSOR                  0
#define HD44780_EM_SHIFT_DISPLAY                 1
#define HD44780_EM_DECREMENT                     0
#define HD44780_EM_INCREMENT                     2

#define HD44780_DISPLAY_ONOFF                    0x08
#define HD44780_DISPLAY_OFF                      0
#define HD44780_DISPLAY_ON                       4
#define HD44780_CURSOR_OFF                       0
#define HD44780_CURSOR_ON                        2
#define HD44780_CURSOR_NOBLINK                   0
#define HD44780_CURSOR_BLINK                     1

#define HD44780_DISPLAY_CURSOR_SHIFT             0x10
#define HD44780_SHIFT_CURSOR                     0
#define HD44780_SHIFT_DISPLAY                    8
#define HD44780_SHIFT_LEFT                       0
#define HD44780_SHIFT_RIGHT                      4

#define HD44780_FUNCTION_SET                     0x20
#define HD44780_FONT5x7                          0
#define HD44780_FONT5x10                         4
#define HD44780_ONE_LINE                         0
#define HD44780_TWO_LINE                         8
#define HD44780_4_BIT                            0
#define HD44780_8_BIT                            16

#define HD44780_CGRAM_SET                        0x40

#define HD44780_DDRAM_SET                        0x80

//##############################################################
void lcd_init(void);
void lcd_cls(void);
void lcd_str(char * text);
void lcd_strxy(unsigned char * text, unsigned char x, unsigned char y);
void lcd_locate(unsigned char x, unsigned char y);
void lcd_int(int n);
void lcd_intxy(int n, unsigned char x, unsigned char y);

//###############################################################

void lcd_writedata(unsigned char dataToWrite);
void lcd_writecommand(unsigned char commandToWrite);
void lcd_writebinary(unsigned int var, unsigned char bitCount);
void lcd_addchar (unsigned char chrNum, unsigned char n, const unsigned char *p);
