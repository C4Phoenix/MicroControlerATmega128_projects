/*
 * functions.h
 *
 * Created: 28/02/2018 15:05:24
 *  Author: Jacco Steegman
 */ 


#ifndef LCD_H_include
#define LCD_H_include

void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_command(unsigned char byte);
int lcd_test_main( void );

void init(void);
void display_text(char *str);
void set_cursor(int position);

#endif /* FUNCTIONS_H_ */