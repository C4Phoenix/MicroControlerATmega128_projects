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

#define F_CPU 8000000

#include <asf.h>
#include <util/delay.h>

void wait(int);

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();//does nothing but O well

	/* Insert application code here, after the board has been initialized. */
	DDRD = 0b11111111;
	DDRC = 0;
	bool needsinit = true;
	PORTD = 0b10000000;
	
	while (1)
	{
		while(PINC & 1<< PC0)
		{
			PORTD ^= 0b11000000;
			wait(250);
		}
	}
}

void wait(int ms)
{
	for (int i =0; i < ms; i++)
	{
		_delay_ms(1);
	}
}
