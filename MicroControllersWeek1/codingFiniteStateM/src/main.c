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

typedef void *(*StateFunc)();

//states
void *s1();
void *s2();
void *s3();
void *start();
void *end();

void *s1()
{
	PORTA = 0b00000010;
	
	if(PIND & (1<<PD5)){ return s2;}
	if(PIND & (1<<PD7)){ return start;}
	return s1;
}

void *s2()
{
	PORTA = 0b00000100;
	
	if(PIND & (1<<PD5)){ return s3;}
	if(PIND & (1<<PD6)){ return s1;}
	if(PIND & (1<<PD7)){ return start;}
	return s2;
}

void *s3()
{
	PORTA = 0b00001000;
	
	if(PIND & (1<<PD5)){ return end;}
	if(PIND & (1<<PD6)){ return end;}
	if(PIND & (1<<PD7)){ return start;}
	return s3;
}

void *start()
{
	PORTA = 0b00000001;
	
	if(PIND & (1<<PD5)){ return s2;}
	if(PIND & (1<<PD6)){ return s1;}
	return start;
}

void *end()
{
	PORTA = 0b11100000;
	
	if(PIND & (1<<PD7)){ return start;}
	return end;
}

int main (void)
{
	StateFunc statefunc = start;
	DDRD = 0b00000000;
	DDRA = 0b11111111;
	
	while(1)
	{
		statefunc = (StateFunc) (*statefunc)();
		wait(100);
	}
}