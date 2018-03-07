/*
 * Opdrachtb2.c
 *
 * Created: 7-3-2018 11:48:27
 * Author : Robin Hobbel
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void wait(int);

int main(void) {	
	DDRF = 0x00;				//PORTF for input ADC
	DDRA = 0xFF;				//PORTA for output
	DDRB = 0xFF;				//PORTB for output

	ADMUX = 0b11100000;			//Bit 7 en 6 zorgen voor de ADC output.  
								//Bit 5 is ADLAR die op 1 wordt gezet. 
								//Bit 4 tot en met 0 is voor het kiezen van pinF0 tot en met pinF7.
	ADCSRA = 0b11100110;		//Bit 7 enable ADC. Bit 6 ADC start conversie. Bit 5 Free running aan of uit. Bit 2 t/m 0 is voor de prescaler (64).
    while (1) {
		PORTA = ADCL;			// Show MSB/LSB (bit 10:0) of ADC
		PORTB = ADCH;			// ADCH reads the high byte, ADCL reads the low byte, 
								//ADCW read the whole "word"->needs checking if true
		wait(100);
    }
}

void wait( int ms ) {
	for (int tms=0; tms<ms; tms++) {
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}