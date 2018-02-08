/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** main.c
**
** Beschrijving:	ISR on PORTD demonstrattion
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ioisr.c
**					avr-gcc -g -mmcu=atmega128 -o ioisr.elf ioisr.o
**					avr-objcopy -O ihex ioisr.elf ioisr.hex
**					or type 'make'
** Author: 			jacc.stee@gmail.com
** -------------------------------------------------------------------------*/

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#define F_CPU 800000

#include <asf.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait( int ms );
void moveLight(void);

int main (void)
{
	//Init io controls
	DDRD = 0x00;//make two buttons input
	
	DDRC = 0b11111111;//set everyone to output
	PORTC= 0b00000001;// set the first bit in the "walking" chain
	
	//init interupt
	EICRA |= 0x3C;// 0b1011
	EIMSK |= 0x06;// 0b0110
	
	
	
	//enable global interupt system
	sei();
	
	while(1)
	{
		//empty while loop to make the main spin for nothing
		//wait(100);
		//moveLight();
	}	
}

void moveLight(void)//move light by one step
{
	if (PORTC == 0b10000000)//if last bit is set
	{
		PORTC = 0b00000001;//start over again
		return;
	}
	PORTC <<= 1;//shift the bit by one also the light
}

ISR( INT1_vect)//interupt no 1
{
	moveLight(); //move light by one step
}

ISR( INT2_vect)//interupt no2
{
	moveLight(); //move light one step
}

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

