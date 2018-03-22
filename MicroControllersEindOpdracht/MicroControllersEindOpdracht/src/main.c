#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

void setBrightness(int);
void sendDataD1(int);
void sendDataD2(int);
void setupRegister(void);
void setChipPins(void);
void setupDisplay(void);
void setLedsInRowD1(int, int);
void clearDisplay1(void);
void clearDisplay2(void);
void setLedsInRowD2(int, int);
void printImageD1(unsigned char*);
void printImageD2(unsigned char*);
void playAnimation(Animation);
//unsigned char* mirror_img(unsigned char*);
typedef struct _Animation {
	int delay;
	int frames;
	unsigned char images[][8];
} Animation;

Animation blink = {
	100,
	9,
	{{
		0B00000000,
		0B00011000,
		0B00111100,
		0B00111100,
		0B00111100,
		0B00111100,
		0B00011000,
		0B00000000
		},{
		0B00000000,
		0B00011000,
		0B00111100,
		0B00111100,
		0B00111100,
		0B00111100,
		0B00011000,
		0B00000000
		},{
		0B00000000,
		0B00000000,
		0B00011000,
		0B00111100,
		0B00111100,
		0B00111100,
		0B00000000,
		0B00000000
		},{
		0B00000000,
		0B00000000,
		0B00000000,
		0B00011000,
		0B00111100,
		0B00011000,
		0B00000000,
		0B00000000
		},{
		0B00000000,
		0B00000000,
		0B00000000,
		0B00000000,
		0B00011000,
		0B00000000,
		0B00000000,
		0B00000000
		},{
		0B00000000,
		0B00000000,
		0B00000000,
		0B00000000,
		0B00000000,
		0B00000000,
		0B00000000,
		0B00000000
		},{
		0B00000000,
		0B00000000,
		0B00000000,
		0B00000000,
		0B00011000,
		0B00000000,
		0B00000000,
		0B00000000
		},{
		0B00000000,
		0B00000000,
		0B00000000,
		0B00011000,
		0B00111100,
		0B00011000,
		0B00000000,
		0B00000000
		},{
		0B00000000,
		0B00000000,
		0B00011000,
		0B00111100,
		0B00111100,
		0B00111100,
		0B00000000,
		0B00000000
	}}
};


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


int main( void )
{
	int brightness = 0;
	unsigned char image[8]= {
		0b00110011,
		0b00110011,
		0b00110011,
		0b00110011,
		0b00110011,
		0b00110011,
		0b00110011,
		0b00110011,
	};
	twi_init();
	setupRegister();
	setChipPins();
	setupDisplay();
	clearDisplay1();
	clearDisplay2();
	printImageD1(image);
	wait(1000);
	printImageD2(image);
	wait(1000);
	while(1){
		playAnimation(blink);
	}
	while (1)
	{
		brightness++;
		setBrightness(brightness%16);
		wait(100);
	}

	return 1;
}

void sendDataD1(int data){
	twi_start();
	twi_tx(0xE0);
	twi_tx(data);
	twi_stop();
}

void sendDataD2(int data){
	twi_start();
	twi_tx(0xE4);
	twi_tx(data);
	twi_stop();
}


void setLedsInRowD1(int row, int data){
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit //1110 0000	
	twi_tx(row);	// Address
	twi_tx(data);	// data
	twi_stop();
}

void setLedsInRowD2(int row, int data){
		twi_start();
		twi_tx(0xE4);	// Display I2C addres + R/W bit //1110 0000
		twi_tx(row);	// Address
		twi_tx(data);	// data
		twi_stop();
}

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


//give a value from 
void setBrightness(int brightness){
	sendDataD1((0b11100000+(brightness)));
	sendDataD2((0b11100000+(brightness)));
}

void setupRegister(){
	sendDataD1(0b00100001);
	sendDataD2(0b00100001);
}

void setChipPins(){
	sendDataD1(0b10100000);
	sendDataD2(0b10100000);
}

void setupDisplay(){
	sendDataD1(0b10000001);
	sendDataD2(0b10000001);
}
/*
unsigned char* mirror_img(unsigned char* imge){
	unsigned char* toReturn = malloc(sizeof(unsigned char)*sizeof(imge));

	short len = 0;
	for(len =0; len< sizeof(imge); len++)
	{
		unsigned char toMir = imge[len];
		int i=7;
		unsigned char j=0;
		unsigned char temp=0;

		while(i>=0){
			temp |= (( toMir >> j ) &1 ) << i;
			i--;
			j++;
		}
		toReturn[len] = temp;
	}
	return toReturn;
}
*/

void printImageD1(unsigned char* img){
	for(int row = 0; row <= 7; row++) {
		setLedsInRowD1((row*2),img[row]);
	}
}

void printImageD2(unsigned char* img){
	for(int row = 0; row <= 7; row++) {
		setLedsInRowD2((row*2),img[row]);
	}
}

void playAnimation(Animation animation){
	for(int i = 0; i<=animation.frames; i++){
		wait(animation.delay);
		printImageD2(animation.images[i]);
	}
}
