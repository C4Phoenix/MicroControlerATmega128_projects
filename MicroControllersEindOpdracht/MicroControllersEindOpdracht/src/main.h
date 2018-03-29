/*
 * main.h
 *
 * Created: 29-3-2018 09:30:52
 *  Author: Robin Hobbel
 */ 

#ifndef MAIN_H_
#define MAIN_H_


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
void initButtons(void);




#endif /* MAIN_H_ */