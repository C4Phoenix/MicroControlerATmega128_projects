#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
//https://cdn-shop.adafruit.com/datasheets/ht16K33v110.pdf

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
	clearDisplay1();
	clearDisplay2();

	while(1){
		if(counter%100==0) {//elke 10 seconde knippert hij
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

void twi_init(void)
{
	TWSR = 0;	//Set Status to 0
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

void twi_start(void)
{
	TWCR = (0x80 | 0x20 | 0x04); //1010 0100 //bit 5 -> startcondition for TWI, bit 7 -> Interrupt flag, bit 3 -> Collision flag
	while( 0x00 == (TWCR & 0x80) );
}

void twi_stop(void)
{
	TWCR = (0x80 | 0x10 | 0x04); //1001 0100 //bit 4 -> Stop condition for TWI, 
}

void twi_tx(unsigned char data)
{
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

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
		printImageD1(eyes->images[i][0]);
		printImageD2(eyes->images[i][1]);
		wait(eyes->delay);
	}
	for(int i = (eyes->frames-2); i>=0; i--) {
		printImageD1(eyes->images[i][0]);
		printImageD2(eyes->images[i][1]);
		wait(eyes->delay);
	}
}

//send data to dotmatix1 (left eye)
void sendDataD1(int data){
	twi_start();
	twi_tx(0xE0);
	twi_tx(data);
	twi_stop();
}

//send data to dotmatix2 (right eye)
void sendDataD2(int data){
	twi_start();
	twi_tx(0xE4);
	twi_tx(data);
	twi_stop();
}

//set leds on dotmatix1 (left eye)
void setLedsInRowD1(int row, int data){
	int newData = data >> 1;
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit //1110 0000	
	twi_tx(row);	// Address
	twi_tx(newData);	// data if
	twi_stop();
}

//set leds on dotmatix2 (right eye)
void setLedsInRowD2(int row, int data){
	int newData = data >> 1;
	twi_start();
	twi_tx(0xE4);	// Display I2C addres + R/W bit //1110 0000
	twi_tx(row);	// Address
	twi_tx(newData);	// data
	twi_stop();
}

//clear leds on dotmatix1 (left eye)
void clearDisplay1(){
	setLedsInRowD1(0x00,0);
	setLedsInRowD1(0x02,0);
	setLedsInRowD1(0x04,0);
	setLedsInRowD1(0x06,0);
	setLedsInRowD1(0x08,0);
	setLedsInRowD1(0x0A,0);
	setLedsInRowD1(0x0C,0);
	setLedsInRowD1(0x0E,0);
}

//clear leds on dotmatix2 (right eye)
void clearDisplay2(){
	setLedsInRowD2(0x00,0);
	setLedsInRowD2(0x02,0);
	setLedsInRowD2(0x04,0);
	setLedsInRowD2(0x06,0);
	setLedsInRowD2(0x08,0);
	setLedsInRowD2(0x0A,0);
	setLedsInRowD2(0x0C,0);
	setLedsInRowD2(0x0E,0);
}


//set brightness of leds of both dotmatrix displays (Datasheet page 17)
//waarden van 0 t/m 15
void setBrightness(int brightness){
	if(brightness > 15) {
		brightness = 15;
	} else if(brightness < 0) {
		brightness = 0;
	}
	sendDataD1((0b11100000+(brightness)));
	sendDataD2((0b11100000+(brightness)));
}

//sets the register of both dotmatrix displays (Datasheet page 13)
void setupRegister(){
	sendDataD1(0b00100001);
	sendDataD2(0b00100001);
}

//sets the chip pins of both dotmatrix displays (Datasheet page 13)
void setChipPins(){
	sendDataD1(0b10100000);
	sendDataD2(0b10100000);
}

//setup of both dotmatrix displays (Datasheet page 14)
void setupDisplay(){
	sendDataD1(0b10000001);
	sendDataD2(0b10000001);
}

//print an image on dotmatrix1 (left eye)
void printImageD1(unsigned char* img){
	for(int row = 0; row <= 7; row++) {
		setLedsInRowD1((row*2),img[row]);
	}
}

//print an image on dotmatrix2 (right eye)
void printImageD2(unsigned char* img){
	for(int row = 0; row <= 7; row++) {
		setLedsInRowD2((row*2),img[row]);
	}
}
