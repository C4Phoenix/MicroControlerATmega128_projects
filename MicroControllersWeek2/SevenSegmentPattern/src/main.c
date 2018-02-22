/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** main.c
**
** Beschrijving:	Ledpatroon op PORTD dmv table lookup (scheiding logica en data). Used with a 7 segment display.   
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c switch.c
**					avr-gcc -g -mmcu=atmega128 -o lookup.elf lookup.o
**					avr-objcopy -O ihex lookup.elf lookup.hex 
**					or type 'make'
** Author: 			Robin Hobbel, Jacco Steegman
** -------------------------------------------------------------------------*/
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
void wait( int ms );

//a struct used to build the animations
typedef struct { 
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT; 

//this is the animation pattern
PATTERN_STRUCT pattern[] = { 
   //0b0gfedcba
	{0b00000001,100},
	{0b00000010,100},
	{0b01000000,100},
	{0b00010000,100},
	{0b00001000,100},
	{0b00000100,100},
	{0b01000000,100},
	{0b00100000,100},
};

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


/******************************************************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			
Version :    	Robin Hobbel, Jacco Steegman, Initial code
*******************************************************************/
{
	DDRD = 0b11111111;					// PORTD all output 
	int frame = 0;
	int animationLenth = 8;
	while (1==1)
	{
	//this loop keeps repeating the pattern using modulo based on the length of the animation.
		frame++;
		frame %= animationLenth;
		PORTD = pattern[frame].data;
		wait(pattern[frame].delay);
	}

	return 1;
}