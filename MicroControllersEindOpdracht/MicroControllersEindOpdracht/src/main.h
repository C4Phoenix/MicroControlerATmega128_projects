/*
 * main.h
 *
 * Created: 29-3-2018 09:30:52
 * Author: Robin Hobbel & Jacco Steegman
 */ 

#ifndef MAIN_H_
#define MAIN_H_

#include "animations.h"
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
void playAnimationsOnEyes(Eyes*);
void twi_init(void);
void twi_start(void);
void twi_stop(void);
void twi_tx(unsigned char);
void wait(int);
void initButtons(void);


#endif /* MAIN_H_ */