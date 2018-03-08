/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
** Author: 			Robin Hobbel
** -------------------------------------------------------------------------*/


#define F_CPU 8000000

#include "lcd.h"

#include <asf.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	3
#define LCD_RS	2


void init(void )
{
	init_4bits_mode();
}
void clearDisplay(void){
	lcd_write_command(0b00000001);
}
void display_text(char *str)
{
	lcd_write_string(str);
}
void set_cursor(int position)
{
	lcd_write_command(0b10000000 + position);
}

/******************************************************************/
void lcd_strobe_lcd_e(void)
/*
short:			Strobe LCD module E pin --__
inputs:
outputs:
notes:			According datasheet HD44780
Version :    	DMK, Initial code
*******************************************************************/
{
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);			// needed to give the board some time
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			// needed for the next command
}

/******************************************************************/
void init_4bits_mode(void)
/*
short:			Init LCD module in 4 bits mode.
inputs:
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
	// PORTC output mode and all low (also E and RS pin)

	DDRC = 0xFF;
	PORTC = 0x00;

	// Step 2 (table 12)
	PORTC = 0x20;	// function set
	lcd_strobe_lcd_e();

	//lcd_write_command(0b00101000);
	lcd_write_command(0b00000001);//clear screen
	lcd_write_command(0b00001110);//make cursof visible display on blink off
	lcd_write_command(0b00000110);//increases cursor pos and scroll display off. to write left to right
}

/******************************************************************/
void lcd_write_string(char *str)
/*
short:			Writes string to LCD at cursor position
inputs:
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
	lcd_write_command(0b00000001);//clear screen
	for(;*str; str++){
		lcd_write_data(*str);
	}
}


/******************************************************************/
void lcd_write_data(unsigned char byte)
/*
short:			Writes 8 bits DATA to lcd
inputs:			byte - written to LCD
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

/******************************************************************/
void lcd_write_command(unsigned char byte)
/*
short:			Writes 8 bits COMMAND to lcd
inputs:			byte - written to LCD
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
	// First nibble.
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}



/******************************************************************/

