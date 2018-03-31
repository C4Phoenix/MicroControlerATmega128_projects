/*
 * main.c
 *
 * Created: 14-3-2018 12:25:26
 * Author: Robin Hobbel & Jacco Steegman
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "main.h"

int main( void )
{
	//initialize counter, for blinking
	int counter = 0;

	//initializes all necessary components
	twi_init();
	initButtons();
	setupRegister();
	setChipPins();
	setupDisplay();
	clearDisplay(MATRIX_1);
	clearDisplay(MATRIX_2);

	while(1){
		if(counter%100==0) {//Blink every 10 seconds
			playAnimationsOnEyes(&blink);
		} else {
			if(PINA & (1<<PA0)) {
				playAnimationsOnEyes(&wink);
			} else if(PINA & (1<<PA1)) {
				playAnimationsOnEyes(&happy);
			} else if(PINA & (1<<PA2)) {
				playAnimationsOnEyes(&angry);
			} else if(PINA & (1<<PA3)) {
				playAnimationsOnEyes(&lookleft);
			} else if(PINA & (1<<PA4)) {
				playAnimationsOnEyes(&lookright);
			} else if(PINA & (1<<PA5)) {
				playAnimationsOnEyes((&squint));
			} else if(PINA & (1<<PA6)) {
				playAnimationsOnEyes((&sad));
			} else if(PINA & (1<<PA7)) {
				playAnimationsOnEyes((&blink));
			}
		}
		wait(100);
		counter++;
	}
	return 1;
}

//Wait function
void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

//initializes the a buttons as input
void initButtons() {
	DDRA = 0b00000000;
}

//playes an animation on the dotmatixdisplays
void playAnimationsOnEyes(Eyes* eyes) {
	for(int i = 0; i<eyes->frames; i++) {
		printImage(MATRIX_1,eyes->images[i][0]);
		printImage(MATRIX_2,eyes->images[i][1]);
		wait(eyes->delay);
	}
	for(int i = (eyes->frames-2); i>=0; i--) {
		printImage(MATRIX_1,eyes->images[i][0]);
		printImage(MATRIX_2,eyes->images[i][1]);
		wait(eyes->delay);
	}
}



