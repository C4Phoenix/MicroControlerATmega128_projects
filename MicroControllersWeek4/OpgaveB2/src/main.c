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
	DDRB = 0xFF;

	ADMUX = 0b11100000;			//Bit 7 en 6 zorgen voor de ADC output.  
								//Bit 5 is ADLAR die op 1 wordt gezet. 
	ADCSRA = 0b10000110;		//Bit 7 enable ADC. Bit 6 ADC start conversie. Bit 5 Free running aan of uit. Bit 2 t/m 0 is voor de prescaler (64).
    while (1) {
		ADCSRA |= 0b01000000; 
		while(ADCSRA & 0b01000000);
		PORTA = ADCH;
		wait(500);
    }
}

void wait( int ms ) {
	for (int tms=0; tms<ms; tms++) {
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}