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

void initadc(){
	ADMUX = 0b11100000;
	ADCSRA = 0b10000010;
}

int main(void) {	
	DDRF = 0x00;				//PORTF for input ADC
	DDRD = 0x00;				//PORTA for output
	
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;

	char string[16];

	init();
	initadc();
	while (1) {
		void clearDisplay();
		int temp = ADC;
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