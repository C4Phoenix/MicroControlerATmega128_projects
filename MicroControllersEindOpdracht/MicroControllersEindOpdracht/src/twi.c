/*
 * twi.c
 *
 * Created: 31-3-2018 10:57:50
 * Author: Robin Hobbel & Jacco Steegman
 */ 
#include "twi.h"

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