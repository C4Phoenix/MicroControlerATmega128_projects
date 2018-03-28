#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
typedef struct _Animation {
	int delay;
	int frames;
	unsigned char images[][8];
} Animation;
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
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
void playAnimation(Animation*);
void playAnimationWithReverse(Animation*);
//unsigned char* rotate_clockwise(unsigned char*);
//void setBitOn(int,int);
//int isBitOn(unsigned char* , int , int );
//int getByteNr(unsigned char);
//unsigned char setByte(unsigned char, int, int);
//unsigned char* mirror_img(unsigned char*);
//unsigned char* workingRotation;

Animation blink = {
	100,
	5,
	{{
		0B01000010,
		0B10000001,
		0B00111100,
		0B01111110, 
		0B01111110,
		0B00111100,
		0B10000001,
		0B01000010
		},{
		0B00000000,
		0B00000000,
		0B00011100,
		0B00111100,
		0B00111100,
		0B00011100,
		0B00000000,
		0B00000000
		},{
		0B00000000,
		0B00000000,
		0B00001000,
		0B00011100,
		0B00011100,
		0B00001000,
		0B00000000,
		0B00000000
		},{
		0B00000000,
		0B00000000,
		0B00000000,
		0B00001000,
		0B00001000,
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
		}
	}
};
/*
{  K0B1234 5678
	0B0000 0000,	1R
	0B0001 1000,	2R
	0B0011 1100,	3R
	0B0011 1100,	4R
	0B0011 1100,	5R
	0B0011 1100,	6R
	0B0001 1000,	7R
	0B0000 0000		8R
}
*/

//rechter rij wordt bovenste rij
//void draaistuff(unsigned char *image) {
	//unsigned char newImage[8];
	//for(int i = 0; i < 8; i++) { //loop langs alle rijen
		//unsigned char byte = image[i]; //0B0001 1000
		//unsigned char newByte;
		//for(int j = 0; j <8; j++) { //loop langs alle 8 bits in de rij
			//plak alle bits uit kolom 7 achter elkaar.
			//newByte = setByte(newByte,j,getByteNr(image[j], i));
		//}
		//newImage[i] = newByte;//0B0000 0000
	//}
//}

//int getByteNr(unsigned char *image, unsigned char byte) {
	
//}

//unsigned char setByte(unsigned char byte, int location, int value) {

//}


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
	while(1){
		playAnimation(&blink);
		wait(1000);
		playAnimationWithReverse(&blink);
		wait(1000);
		
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
		int newData = data >> 1;
		if(CHECK_BIT(data,7)) {
			newData ^= 0b10000000;
		}
		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit //1110 0000	
		twi_tx(row);	// Address
		twi_tx(newData);	// data if
		twi_stop();
}

void setLedsInRowD2(int row, int data){
		int newData = data >> 1;
		if(CHECK_BIT(data,7)) {
			newData ^= 0b10000000;
		}
		twi_start();
		twi_tx(0xE4);	// Display I2C addres + R/W bit //1110 0000
		twi_tx(row);	// Address
		twi_tx(newData);	// data
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

void playAnimation(Animation* animation){
	for(int i = 0; i<animation->frames; i++){
		wait(animation->delay);
		printImageD1(animation->images[i]);
		printImageD2(animation->images[i]);
	}
}

void playAnimationWithReverse(Animation* animation) {
	for(int i = 0; i<animation->frames; i++) {
		wait(animation->delay);
		printImageD2(animation->images[i]);
		printImageD2(animation->images[i]);
	}
	for(int i = (animation->frames-2); i>=0; i--) {
		wait(animation->delay);
		printImageD1(animation->images[i]);
		printImageD2(animation->images[i]);
	}
}

/*
unsigned char* rotate_clockwise(unsigned char* toRotate)
{
	if (workingRotation != NULL) free(workingRotation);
	workingRotation = calloc(0,sizeof(unsigned char) *8);

	for(int y = 0; y < 8; y++)// array y (top to bottom)
	{
		for(int x = 0; x < 8; x++)// x coordinate
		{
			if(isBitOn(toRotate, x, y) == 1)
			{
				setBitOn(x,y);
			}
		}
	}

	return workingRotation;
}

void setBitOn(int x,int y)
{
	int newX, newY;
	newX = 7-y;
	newY = x;
	workingRotation[newY] |= 1 << newX;
}

int isBitOn(unsigned char* toCheck, int x, int y)
{
	unsigned char byte = toCheck[y];
	return ((byte >> x)%2);
}

*/