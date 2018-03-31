/*
 * dotmatrix.h
 *
 * Created: 31-3-2018 11:01:30
 * Author: Robin Hobbel & Jacco Steegman
 */ 


#ifndef DOTMATRIX_H_
#define DOTMATRIX_H_

#include "twi.h"

#define MATRIX_1 0xE0
#define MATRIX_2 0xE4
void setBrightness(int);
void sendData(int, int);
void setupRegister(void);
void setChipPins(void);
void setupDisplay(void);
void clearDisplay(int);
void setLedsInRow(int, int, int);
void printImage(int, unsigned char*);

#endif /* DOTMATRIX_H_ */