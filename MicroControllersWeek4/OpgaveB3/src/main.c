/*
 * Opdrachtb2.c
 *
 * Created: 7-3-2018 12:04:38
 * Author : Robin Hobbel
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "lcd.h"
void wait(int);

int main(void) {	
	DDRF = 0x00;				//PORTF for input ADC
	DDRD = 0x00;				//PORTA for output
	
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;

	char string[16];

	ADMUX = 0b11100000;			//spanning met 2,56V ref
	ADCSRA = 0b11100110;		//Bit 7 enable ADC. Bit 6 ADC start conversie. Bit 5 Free running aan of uit. Bit 2 t/m 0 is voor de prescaler (64).
    
	init();
	while (1) {
		lcd_write_command(0b00000001);//clear display
		int temp = ADCH;
		sprintf(string, "Temp: %d", temp);
		lcd_write_string(string);
		PORTA = ADCH;//Show on LEDS
		//PORTB = ADCL;
		wait(1000);
    }
}

void wait( int ms ) {
	for (int tms=0; tms<ms; tms++) {
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}