/*
 * twi.h
 *
 * Created: 31-3-2018 10:58:00
 * Author: Robin Hobbel & Jacco Steegman
 */ 
#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>

void twi_init(void);
void twi_start(void);
void twi_stop(void);
void twi_tx(unsigned char);

#endif /* TWI_H_ */