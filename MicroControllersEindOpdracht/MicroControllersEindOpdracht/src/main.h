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

Eyes blink = {
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
				0B00011100,
				0B00111100,
				0B00111100,
				0B00011100,
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
				0B00001000,
				0B00011100,
				0B00011100,
				0B00001000,
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
				0B00000000,
				0B00001000,
				0B00001000,
				0B00000000,
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
				0B00000000,
				0B00000000,
				0B00000000,
				0B00000000,
				0B00000000,
				0B00000000
			}
		}
	}
};

Eyes happy = {
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
				0B00111110,
				0B01111110,
				0B00111100,
				0B00000000,
				0B00000000
				},{//right eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111110,
				0B00111110,
				0B00011100,
				0B00000000,
				0B00000000
			}
		},
		{//frame 3
			{//left eye
				0B00000000,
				0B00000000,
				0B00001100,
				0B00011110,
				0B00111110,
				0B00111100,
				0B00000000,
				0B00000000
				},{//right eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B00111110,
				0B00011110,
				0B00001100,
				0B00000000,
				0B00000000
			}
		},
		{//frame 4
			{//left eye
				0B00000000,
				0B00000000,
				0B00001100,
				0B00011110,
				0B00111110,
				0B00111100,
				0B00000000,
				0B00000000
				},{//right eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B00111110,
				0B00011110,
				0B00001100,
				0B00000000,
				0B00000000
			}
		},
		{//frame 5
			{//left eye
				0B00000000,
				0B00000000,
				0B00001100,
				0B00011110,
				0B00111110,
				0B00111100,
				0B00000000,
				0B00000000
				},{//right eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B00111110,
				0B00011110,
				0B00001100,
				0B00000000,
				0B00000000
			}
		}
	}
};

Eyes angry = {
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
				0B00111000,
				0B01111100,
				0B01111110,
				0B00111100,
				0B00000000,
				0B00000000
				},{//right eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111110,
				0B01111100,
				0B00111000,
				0B00000000,
				0B00000000
			}
		},
		{//frame 3
			{//left eye
				0B00000000,
				0B00000000,
				0B00110000,
				0B01111000,
				0B01111100,
				0B00111100,
				0B00000000,
				0B00000000
				},{//right eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111100,
				0B01111000,
				0B00110000,
				0B00000000,
				0B00000000
			}
		},
		{//frame 4
			{//left eye
				0B00000000,
				0B00000000,
				0B00110000,
				0B01111000,
				0B01111100,
				0B00111100,
				0B00000000,
				0B00000000
				},{//right eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111100,
				0B01111000,
				0B00110000,
				0B00000000,
				0B00000000
			}
		},
		{//frame 5
			{//left eye
				0B00000000,
				0B00000000,
				0B00110000,
				0B01111000,
				0B01111100,
				0B00111100,
				0B00000000,
				0B00000000
				},{//right eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111100,
				0B01111000,
				0B00110000,
				0B00000000,
				0B00000000
			}
		}
	}
};

Eyes lookleft = {
	150,
	3,
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
				0B00111100,
				0B01111110,
				0B01111110,
				0B00111100,
				0B00000000,
				0B00000000,
				0B00000000
				},{//right eye
				0B00000000,
				0B00111100,
				0B01111110,
				0B01111110,
				0B00111100,
				0B00000000,
				0B00000000,
				0B00000000
			}
		},
		{//frame 3
			{//left eye
				0B00111100,
				0B01111110,
				0B01111110,
				0B00111100,
				0B00000000,
				0B00000000,
				0B00000000,
				0B00000000
				},{//right eye
				0B00111100,
				0B01111110,
				0B01111110,
				0B00111100,
				0B00000000,
				0B00000000,
				0B00000000,
				0B00000000
			}
		}
	}
};

Eyes lookright = {
	150,
	3,
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
				0B00000000,
				0B00111100,
				0B01111110,
				0B01111110,
				0B00111100,
				0B00000000
				},{//right eye
				0B00000000,
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111110,
				0B01111110,
				0B00111100,
				0B00000000
			}
		},
		{//frame 3
			{//left eye
				0B00000000,
				0B00000000,
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111110,
				0B01111110,
				0B00111100
				},{//right eye
				0B00000000,
				0B00000000,
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111110,
				0B01111110,
				0B00111100
			}
		}
	}
};

Eyes squint = {
	250,
	2,
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
				0B01111000,
				0B11111100,
				0B11111100,
				0B01111000,
				0B00000000,
				0B00000000,
				0B00000000
				},{//right eye
				0B00000000,
				0B00000000,
				0B00000000,
				0B01111000,
				0B11111100,
				0B11111100,
				0B01111000,
				0B00000000
			}
		}
	}
};

Eyes sad = {
	100,
	2,
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
				0B00111100,
				0B01111110,
				0B01111100,
				0B00111000,
				0B00000000,
				0B00000000
				},{//right eye
				0B00000000,
				0B00000000,
				0B00111000,
				0B01111100,
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
				0B00111100,
				0B01111100,
				0B01111000,
				0B00110000,
				0B00000000,
				0B00000000
				},{//right eye
				0B00000000,
				0B00000000,
				0B00110000,
				0B01111000,
				0B01111100,
				0B00111100,
				0B00000000,
				0B00000000
			}
		},
		{//frame 4
			{//left eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111100,
				0B01111000,
				0B00110000,
				0B00000000,
				0B00000000
				},{//right eye
				0B00000000,
				0B00000000,
				0B00110000,
				0B01111000,
				0B01111100,
				0B00111100,
				0B00000000,
				0B00000000
			}
		},
		{//frame 5
			{//left eye
				0B00000000,
				0B00000000,
				0B00111100,
				0B01111100,
				0B01111000,
				0B00110000,
				0B00000000,
				0B00000000
				},{//right eye
				0B00000000,
				0B00000000,
				0B00110000,
				0B01111000,
				0B01111100,
				0B00111100,
				0B00000000,
				0B00000000
			}
		}
	}
};

#endif /* MAIN_H_ */