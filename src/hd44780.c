#include "hd44780.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx.h"
#include <stdlib.h>

GPIO_InitTypeDef GPIO_InitStructure;

//-----------------------------------------------------------------------------
void lcd_writenibble(unsigned char nibbleToWrite)
{
  volatile unsigned int delayCnt = 0;
  GPIO_WriteBit(GPIOE, LCD_EN, Bit_SET);
  GPIO_WriteBit(GPIOB, LCD_D4,(BitAction)(nibbleToWrite & 0x01));
  GPIO_WriteBit(GPIOC, LCD_D5,(BitAction)(nibbleToWrite & 0x02));
  GPIO_WriteBit(GPIOA, LCD_D6,(BitAction)(nibbleToWrite & 0x04));
  GPIO_WriteBit(GPIOA, LCD_D7,(BitAction)(nibbleToWrite & 0x08));
  for(delayCnt = 0; delayCnt < 50000; delayCnt++);
  GPIO_WriteBit(GPIOE, LCD_EN, Bit_RESET);
}


//-----------------------------------------------------------------------------
void lcd_writedata(unsigned char dataToWrite)
{
  GPIO_WriteBit(GPIOB, LCD_RS, Bit_SET);
  lcd_writenibble(dataToWrite >> 4);
  lcd_writenibble(dataToWrite & 0x0F);
}


//-----------------------------------------------------------------------------
void lcd_writecommand(unsigned char commandToWrite)
{
  GPIO_WriteBit(GPIOB, LCD_RS, Bit_RESET);
  lcd_writenibble(commandToWrite >> 4);
  lcd_writenibble(commandToWrite & 0x0F);
}
//-----------------------------------------------------------------------------
void lcd_str(char * text)
{
  while(*text) lcd_writedata(*text++);
}
//-----------------------------------------------------------------------------
void lcd_locate(unsigned char x, unsigned char y)
{
  lcd_writecommand(HD44780_DDRAM_SET | (x + (0x40 * y)));
}
//-----------------------------------------------------------------------------
void lcd_strxy(unsigned char * text, unsigned char x, unsigned char y)
{
  lcd_locate(x,y);
  while(*text) lcd_writedata(*text++);
}
//-----------------------------------------------------------------------------
void lcd_writebinary(unsigned int var, unsigned char bitCount)
{
  signed char i;

  for(i = (bitCount - 1); i >= 0; i--)
     {
        lcd_writedata((var & (1 << i))?'1':'0');
     }
}
//-----------------------------------------------------------------------------
void LCD_ShiftLeft(void)
{
  lcd_writecommand(HD44780_DISPLAY_CURSOR_SHIFT | HD44780_SHIFT_LEFT | HD44780_SHIFT_DISPLAY);
}
//-----------------------------------------------------------------------------
void LCD_ShiftRight(void)
{
  lcd_writecommand(HD44780_DISPLAY_CURSOR_SHIFT | HD44780_SHIFT_RIGHT | HD44780_SHIFT_DISPLAY);
}
//-----------------------------------------------------------------------------
void lcd_init(void)
{
  volatile unsigned char i = 0;
  volatile unsigned int delayCnt = 0;
  
  GPIO_InitStructure.GPIO_Pin = LCD_D6|LCD_D7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = LCD_RS|LCD_D4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = LCD_D5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = LCD_EN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_ResetBits(GPIOB, LCD_RS);
  GPIO_ResetBits(GPIOE, LCD_EN);

  for(delayCnt = 0; delayCnt < 300000; delayCnt++);

  for(i = 0; i < 3; i++) 
  {
    lcd_writenibble(0x03);
    for(delayCnt = 0; delayCnt < 30000; delayCnt++);
  }

  lcd_writenibble(0x02);
  for(delayCnt = 0; delayCnt < 6000; delayCnt++);

  lcd_writecommand(HD44780_FUNCTION_SET| HD44780_FONT5x7 | HD44780_TWO_LINE | HD44780_4_BIT);
  lcd_writecommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_OFF);
  lcd_writecommand(HD44780_CLEAR);
  lcd_writecommand(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT);
  lcd_writecommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK);
}


//-----------------------------------------------------------------------------
void lcd_addchar (unsigned char chrNum, unsigned char n, const unsigned char *p)
{
  lcd_writecommand(HD44780_CGRAM_SET | chrNum * 8);
  n *= 8;
  do
    lcd_writedata(*p++);
  while (--n);
}


//-----------------------------------------------------------------------------
void lcd_cls(void)
{
  lcd_writecommand(HD44780_CLEAR);
}
//-----------------------------------------------------------------------------
unsigned char* intToStr(int n){
     int i = 0;
     int j = 0;
   char *tmp = (char*)malloc(sizeof(char));
     unsigned char *ret = (unsigned char*)malloc(12);
   if(n<0 || n>9){
 *tmp = n%10+48;
 n-=n%10;
 n/=10;
 tmp++;
 i++;
}
*tmp = n+48;
i++;
while(i--){
 ret[j++] = *tmp--;
}
return ret;
}
void lcd_int(int a){
 unsigned short ch,
                    first; //you need this to display 0 if there was any char

    //Get first char
    ch = a/10000;
    if(ch){
     lcd_writedata(48+ch);
     first = 1;
    }

    //Get second char
    ch = (a/1000)%10;
    if(ch || first){
     lcd_writedata(48+ch);
     first = 1;
    }

    //Get third char
    ch = (a/100)%10;
    if(ch || first){
     lcd_writedata(48+ch);
     first = 1;
    }

    //Get fourth char
    ch = (a/10)%10;
    if(ch || first){
     lcd_writedata(48+ch);
     //first = 1;                   //q
    }

    //Get fifth char
    ch = a%10;
    //if(ch || first)   //you dont need to check las one if ch is 0 then just display it, unless you dont want to then uncomment this line ("//q" line too)
     lcd_writedata(48+ch);
       // lcd_str(intToStr(n));
}
//-----------------------------------------------------------------------------
void lcd_intxy(int n, unsigned char x, unsigned char y)
{
        lcd_locate(x,y);
        lcd_int(n);
}