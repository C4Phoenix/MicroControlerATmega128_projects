/*
 * dotmatrix.c
 *
 * Created: 31-3-2018 11:01:21
 * Author: Robin Hobbel & Jacco Steegman
 */ 
//https://cdn-shop.adafruit.com/datasheets/ht16K33v110.pdf
/*
	Adresses & Bits of the 8x8 matrix
	xxxx128-1-2-4-8-16-32-64
	0x00
	0x02
	0x04
	0x06
	0x08
	0x0A
	0x0C
	0x0E
*/

#include "dotmatrix.h"

//send data to dotmatix
void sendData(int matrixaddress, int data){
	twi_start();
	twi_tx(matrixaddress);
	twi_tx(data);
	twi_stop();
}

//set leds on dotmatix
void setLedsInRow(int matrixaddress, int row, int data) {
	int newData = data >> 1;
	twi_start();
	twi_tx(matrixaddress);	// Display I2C addres + R/W bit //1110 0000
	twi_tx(row);	// Address
	twi_tx(newData);	// data if
	twi_stop();
}


//clear leds on dotmatix
void clearDisplay(int matrixaddress){
	setLedsInRow(matrixaddress,0x00,0);
	setLedsInRow(matrixaddress,0x02,0);
	setLedsInRow(matrixaddress,0x04,0);
	setLedsInRow(matrixaddress,0x06,0);
	setLedsInRow(matrixaddress,0x08,0);
	setLedsInRow(matrixaddress,0x0A,0);
	setLedsInRow(matrixaddress,0x0C,0);
	setLedsInRow(matrixaddress,0x0E,0);
}

//set brightness of leds of both dotmatrix displays (Datasheet page 17)
//waarden van 0 t/m 15
void setBrightness(int brightness){
	if(brightness > 15) {
		brightness = 15;
		} else if(brightness < 0) {
		brightness = 0;
	}
	sendData(MATRIX_1,(0b11100000+(brightness)));
	sendData(MATRIX_2,(0b11100000+(brightness)));
}

//sets the register of both dotmatrix displays (Datasheet page 13)
void setupRegister(){
	sendData(MATRIX_1,0b00100001);
	sendData(MATRIX_2,0b00100001);
}

//sets the chip pins of both dotmatrix displays (Datasheet page 13)
void setChipPins(){
	sendData(MATRIX_1,0b10100000);
	sendData(MATRIX_2,0b10100000);
}

//setup of both dotmatrix displays (Datasheet page 14)
void setupDisplay(){
	sendData(MATRIX_1,0b10000001);
	sendData(MATRIX_2,0b10000001);
}

//print an image on dotmatrix
void printImage(int matrixaddress, unsigned char* img){
	for(int row = 0; row <= 7; row++) {
		setLedsInRow(matrixaddress,(row*2),img[row]);
	}
}
