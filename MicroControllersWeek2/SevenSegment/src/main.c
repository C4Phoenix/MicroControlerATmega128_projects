/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** main.c
**
** Beschrijving:	Display numbers on a seven segment display on PORTD using a table lookup. using interupts to make the number go up or down with buttons.
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c switch.c
**					avr-gcc -g -mmcu=atmega128 -o lookup.elf lookup.o
**					avr-objcopy -O ihex lookup.elf lookup.hex 
**					or type 'make'
** Author: 			Robin Hobbel & Jacco Steegman
** -------------------------------------------------------------------------*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void wait( int ms );
void display(int digit);

int lookup[] = {
  //0b0gfedcba
	0b00111111,//0
	0b00000110,//1
	0b01011011,//2
	0b01001111,//3
	0b01100110,//4
	0b01101101,//5
	0b01111101,//6
	0b00000111,//7
	0b01111111,//8
	0b01101111,//9
	0b01110111,//a
	0b01111100,//b
	0b00111001,//c
	0b01011110,//d
	0b01111001,//e
	0b01110001,//f
};
int button1Pressed = 0;//0 = button not pressed, 1 = button pressed
int button2Pressed = 0;//0 = button not pressed, 1 = button pressed


/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR( INT1_vect)//interupt no 1
{
	button1Pressed = 1;
}

ISR( INT2_vect)//interupt no 2
{
	button2Pressed = 1;	
}
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			
Version :    	Robin Hobbel, Initial code
*******************************************************************/
{
	int currentNumber = 0;
	DDRC = 0b11111111;	// PORTD all output 
	DDRD = 0b00000000;	//PORTC all input
	EICRA |= 0x3C;
	EIMSK |= 0x06;
	sei();
	while (1)
	{
		wait(250);
		if(button1Pressed && button2Pressed){
		//sets everything to zero when both buttons are pressed
			currentNumber=0;
			button1Pressed=0;
			button2Pressed=0;
		} else if (button1Pressed){
		//count up
			currentNumber++;
			button1Pressed=0;
		} else if (button2Pressed){
		//count down
			currentNumber--;
			button2Pressed=0;
		}
		display(currentNumber);
	}
	return 1;
}
/******************************************************************/
void display(int digit){
/*
short:			display(), displays a digit hexadecimal on the seven segment display by getting the requerd bits from a list
inputs:			int
outputs:		
notes:
Version :    	Robin Hobbel, Initial code
*******************************************************************/
	//contains a check so the digit doesn't go past 14
	if(0 <= digit && digit <=15){
		PORTC = lookup[digit];
	} else {
		PORTC = lookup[14];
	}
	
}


