/**
 * Timer
 *
 * Created: 28-2-2018 13:54:27
 * Author : Robin Hobbel, Jacco Steegman
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int overflowCount = 0;

int main(void)
{
	DDRD = 0xFF;//Set d to output
		
	TCNT2 = 0;//Timer/Counter Register, value of timer is soterd here, Initialize counter
	OCR2 = 125;
	TIMSK |= (1 << 7);//Timer/Counter Interrupt Mask, turn the 1 in 0b0100 0000 on to enable overflow interrupts
	SREG |= (1 << 7); //Set global interrupt bit
	
	TCCR2 = 0b00001101; // Counting via D, prescaler:
	//TCCR2 = 0b;
	sei();//activate interrupts
	

    while (1) 
    {
		//empty while loop to keep code running
    }
}


ISR( TIMER2_COMP_vect ) //Interrupt for timer 2
{
	overflowCount++;
	overflowCount = overflowCount % 40;
	if(overflowCount == 0) {
		PORTD = 0b10000000;
		} else if(overflowCount == 15) {
		PORTD = 0b00000000;
	}
}
