/*
 * functions.c
 *
 * Created: 28/02/2018 14:59:22
 *  Author: Jacco Steegman
 */ 
#define F_CPU 8000000

#include "LCD.h"
#include <asf.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait( int ms );


#define LCD_E 	3
#define LCD_RS	2



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
	_delay_ms(1);			// nodig
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			// nodig?
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

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();

}

void init()
{
	init_4bits_mode()
}

void dislay_text(char *str)
{
	lcd_write_string(str);
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
	// Het kan met een while:

	// while(*str) {
	// 	lcd_write_data(*str++);
	// }

	// of met een for:
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
int func_main( void )
/*
short:			main() loop, entry point of executable
inputs:
outputs:
notes:			Slow background task after init ISR
Version :    	DMK, Initial code
*******************************************************************/
{
	// Init I/O
	DDRD = 0xFF;			// PORTD(7) output, PORTD(6:0) input

	// Init LCD
	init_4bits_mode();

	// Write sample string
	lcd_write_string("Yedi you are");

	// Loop forever
	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		_delay_ms( 250 );
	}

	return 1;
}


//tried to code things myself aparently i can just copy code
//#define LCD_data P3
//#define LCD_D7   P2_7
//#define LCD_rs   2//bitshift 2 bits
//#define LCD_rw   P1_1
//#define LCD_en   3//bitshift 3 bits
//
//void LCD_init()
//{
	//DDRC = 0xFF;
	//PORTC = 0x00;
	//
	//LCD_data = 0b0010;   //Function set: 2 Line, 4-bit, 5x7 dots part 1
	//LCD_rs   = 0;        //Selected command register
	//LCD_rw   = 0;        //We are writing in data register
	//LCD_en   = 1;        //ready sent
	//LCD_en   = 0;        //sent/activate
//
	//wait(4);             //Wait for LCD to process the command
	//LCD_data = 0b1000;   // part 2
	//LCD_en   = 1;        //ready sent
	//LCD_en   = 0;        //sent/activate
	//wait(4);
	////------------------------------------
//
	//LCD_data = 0b0000;   //Display on, Curson blinking command part 1
	//LCD_en   = 1;        ///sent/activate
	//LCD_en   = 0;
//
	//wait(4);             //Wait for LCD to process the command
	//LCD_data = 0b1111;   //part 2
	//LCD_en   = 1;        //sent/activate
	//LCD_en   = 0;
	//wait(4);
	////------------------------------------
//
	//LCD_data = 0b0000;   //Clear LCD
	//LCD_en   = 1;        //Enable H->
	//LCD_en   = 0;
//
	//wait(4);             //Wait for LCD to process the command
	//LCD_data = 0b0001;
	//LCD_en   = 1;
	//LCD_en   = 0;
	//wait(4);
	////------------------------------------
//
	//LCD_data = 0b0000;     //Entry mode, auto increment with no shift
	//LCD_en   = 1;          //Enable H->
	//LCD_en   = 0;
	//wait(4);
//
	//LCD_data = 0b0110;     //part 2
	//
	//LCD_en   = 1;
	//LCD_en   = 0;
	//wait(4);
//}
//
//
//
//void wait( int ms )
//{
	//for (int i=0; i<ms; i++)
	//{
		//_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	//}
//}
//
//
//#define LCD_E 	3
//#define LCD_RS	2 //
//
//void lcd_strobe_lcd_e(void)
///*
//short:			Strobe LCD module E pin --__
//inputs:
//outputs:
//notes:			According datasheet HD44780
//Version :    	DMK, Initial code
//*******************************************************************/
//{
	//PORTC |= (1<<LCD_E);//bitshift 3	// E high
	//_delay_ms(1);			// nodig
	//PORTC &= ~(1<<LCD_E);//bitshift 3  	// E low
	//_delay_ms(1);			// nodig?
//}
//
////didrich code
//{
	//// PORTC output mode and all low (also E and RS pin)
	//DDRC = 0xFF;//1111 1111
	//PORTC = 0x00;//0000 0000
//
	//// Step 2 (table 12)
	//PORTC = 0x20;// 0010 0000	// function set
	//lcd_strobe_lcd_e();
//
	//// Step 3 (table 12)
	//PORTC = 0x20;   // function set
	//lcd_strobe_lcd_e();
	//PORTC = 0x80; //1000 0000
	//lcd_strobe_lcd_e();
//
	//// Step 4 (table 12)
	//PORTC = 0x00; //0000 0000  // Display on/off control
	//lcd_strobe_lcd_e();
	//PORTC = 0xF0; //1111 0000
	//lcd_strobe_lcd_e();
//
	//// Step 4 (table 12)
	//PORTC = 0x00;  // 0000 0000  // Entry mode set
	//lcd_strobe_lcd_e();
	//PORTC = 0x60; // 0110 0000
	//lcd_strobe_lcd_e();
//
//}'