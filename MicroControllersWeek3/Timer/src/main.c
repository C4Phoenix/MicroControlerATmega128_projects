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

int countOverFlow = 0;
int highMode = 1;

int main(void)
{
	DDRD = 0xFF;//Set d to output
		
	TCNT2 = 0;//Timer/Counter Register, value of timer is stored here, Initialize counter
	OCR2 = 100; //Compare value timer 2, interrupts after compare is true, made value higher so its beter visible on camera
	TIMSK |= (1 << 7);//Timer/Counter Interrupt Mask, turn the 1 in 0b0100 0000 on to enable overflow interrupts
	SREG |= (1 << 7); //Set global interrupt bit
	
	TCCR2 = 0b00001101; // Counting via D, prescaler: 1024
	//TCCR2 = 0b00001001; // prescaler: none
	//TCCR2 = 0b00001010; // prescaler: 8
	//TCCR2 = 0b00001011; // prescaler: 32
	//TCCR2 = 0b00001100; // prescaler: 256
	sei();//activate interrupts
	

    while (1) 
    {
		//empty while loop to keep code running
    }
}


ISR( TIMER2_COMP_vect ) //Interrupt for timer 2, after a compare
{
	//moet 15ms hoog, 25ms laag
	countOverFlow++;
	if(highMode) {
		if(countOverFlow == 15) {
			PORTD = 0b01000000;//laag
			highMode = 0;//turn highmode off
			countOverFlow =0;
		}
	} else {
		if (countOverFlow == 25) {
			PORTD = 0b10000000;//hoog
			highMode = 1; //turn highmode on
			countOverFlow = 0;
		}
	}
}
