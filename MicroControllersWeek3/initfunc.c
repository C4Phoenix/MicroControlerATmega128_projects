
#define LCD_data P3
#define LCD_D7   P2_7
#define LCD_rs   P1_0
#define LCD_rw   P1_1
#define LCD_en   P1_2

void LCD_init()
{
     LCD_data = 0b0010;   //Function set: 2 Line, 4-bit, 5x7 dots part 1
     LCD_rs   = 0;        //Selected command register
     LCD_rw   = 0;        //We are writing in data register
     LCD_en   = 1;        //ready sent
     LCD_en   = 0;        //sent/activate

     wait(4);             //Wait for LCD to process the command
     LCD_data = 0b1000;   // part 2
     LCD_en   = 1;        //ready sent
     LCD_en   = 0;        //sent/activate
     wait(4);
     //------------------------------------

     LCD_data = 0b0000;   //Display on, Curson blinking command part 1
     LCD_en   = 1;        ///sent/activate
     LCD_en   = 0;

     wait(4);             //Wait for LCD to process the command
     LCD_data = 0b1111;   //part 2
     LCD_en   = 1;        //sent/activate
     LCD_en   = 0;
     wait(4);
     //------------------------------------

     LCD_data = 0b0000;   //Clear LCD
     LCD_en   = 1;        //Enable H->
     LCD_en   = 0;

     wait(4);             //Wait for LCD to process the command
     LCD_data = 0b0001;
     LCD_en   = 1;
     LCD_en   = 0;
     wait(4);
     //------------------------------------

     LCD_data = 0b0000;     //Entry mode, auto increment with no shift
     LCD_en   = 1;          //Enable H->
     LCD_en   = 0;
     wait(4);

     LCD_data = 0b0110;     //part 2
     
     LCD_en   = 1;
     LCD_en   = 0;
     wait(4);
}

void SendLCD_DATA(int data)
{
    LCD_data = data 
}
