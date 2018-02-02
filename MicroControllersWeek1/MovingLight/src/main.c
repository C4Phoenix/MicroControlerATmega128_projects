/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** main.c
**
** Beschrijving:	Switches between bit 6 and bit 7
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c switch.c
**					avr-gcc -g -mmcu=atmega128 -o switch.elf switch.o
**					avr-objcopy -O ihex switch.elf switch.hex
**					or type 'make'
** Author: 			rm.hobbel@gmail.com && jacc.stee@gmail.com
** -------------------------------------------------------------------------*/
#define F_CPU 8000000
#define BIT(x) (1 << (x))


#include <avr/io.h>
#include <util/delay.h>
void wait( int ms );


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
int main( void ){
	int i = 0;
	DDRD = 0b11111111;	
	PORTD = BIT(0);
	while (1)
	{	
		PORTD = BIT(i%8);
		i++;
		wait(50);
	}
	return 1;
}