#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
typedef struct _Eyes {
	int delay;
	int frames;
	unsigned char images[][2][8];
} Eyes;
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
void playAnimationsOnEyes(Eyes*);
void twi_init(void);
void twi_start(void);
void twi_stop(void);
void twi_tx(unsigned char);
void wait(int);
void init_intterupts(void);
int winkFlag = 0;


#pragma region wink 
Eyes wink = {
	100,
	5,
	{//frames
		{//frame 1
			{//left eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111110,
				0B01111110,
				0B00111100,
				0B00000000,
				0B00000000
			},{//right eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111110,
				0B01111110,
				0B00111100,
				0B00000000,
				0B00000000
			}
		},
		{//frame 2
			{//left eye
				0B00000000,
				0B00000000,
				0B00011100,
				0B00111100,
				0B00111100,
				0B00011100,
				0B00000000,
				0B00000000
			},{//right eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111110,
				0B01111110,
				0B00111100,
				0B00000000,
				0B00000000
			}
		},
		{//frame 3
			{//left eye
				0B00000000,
				0B00000000,
				0B00001000,
				0B00011100,
				0B00011100,
				0B00001000,
				0B00000000,
				0B00000000
			},{//right eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111110,
				0B01111110,
				0B00111100,
				0B00000000,
				0B00000000
			}
		},
		{//frame 4
			{//left eye
				0B00000000,
				0B00000000,
				0B00000000,
				0B00001000,
				0B00001000,
				0B00000000,
				0B00000000,
				0B00000000
			},{//right eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111110,
				0B01111110,
				0B00111100,
				0B00000000,
				0B00000000
			}
		},
		{//frame 5
			{//left eye
				0B00000000,
				0B00000000,
				0B00000000,
				0B00000000,
				0B00000000,
				0B00000000,
				0B00000000,
				0B00000000
			},{//right eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111110,
				0B01111110,
				0B00111100,
				0B00000000,
				0B00000000
			}
		}
	}
};
#pragma endregion wink

void init_intterupts(){
	DDRA = 0x00;
	EICRA |= 0x3C;
	EIMSK |= 0x06;

	//enable global interupt system
	sei();
}

ISR( INT1_vect)//interupt no 1
{
	winkFlag = 1;
}

ISR( INT2_vect)//interupt no2
{
	winkFlag = 1;
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


int main( void )
{
	int brightness = 0;
	twi_init();
	setupRegister();
	setChipPins();
	setupDisplay();
	clearDisplay1();
	clearDisplay2();
	while(1){
		playAnimationsOnEyes(&wink);
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
