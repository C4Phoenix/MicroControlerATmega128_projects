/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <util/delay.h>

#define F_CPU 8000000

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

int main (void)
{
	
	int animation[][4]={
		{
			0b00100000,
			0b00010000,
			0b00001000,
			0b00000100
			},{
			0b10000000,
			0b11110000,
			0b00001110,
			0b00000001
			},{
			0b00000001,
			0b00001110,
			0b01110000,
			0b10000000
			},{
			0b00000100,
			0b00001000,
			0b00010000,
			0b00100000
		}
	};
	
	DDRD = 0b11111111;
	DDRC = 0b11111111;
	DDRB = 0b11111111;
	DDRA = 0b11111111;
	
	int frame = 0;
	int animationLenth = 4;
	
	while (1)
	{
		frame++;
		frame %= animationLenth;
		
		PORTA = animation[frame][0];
		PORTB = animation[frame][1];
		PORTC = animation[frame][2];
		PORTD = animation[frame][3];
		
		wait(100);
	}
	return 1;
}
