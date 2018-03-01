/*
 * functions.h
 *
 * Created: 28/02/2018 15:05:24
 *  Author: Jacco Steegman
 */ 


void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);
int lcd_test_main( void );

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_





#endif /* FUNCTIONS_H_ */