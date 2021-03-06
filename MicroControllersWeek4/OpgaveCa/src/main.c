#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h> 
#define BIT(x)  ( 1<<x )

#define DDR_SPI  DDRB  // spi Data direction register 
#define PORT_SPI PORTB  // spi Output register 
#define SPI_SCK  1  // PB1: spi Pin System Clock 
#define SPI_MOSI 2  // PB2: spi Pin MOSI 
#define SPI_MISO 3  // PB3: spi Pin MISO 
#define SPI_SS  0  // PB0: spi Pin Slave Select 
void spi_masterInit(void);
void spi_write( unsigned char );
char spi_writeRead( unsigned char );
void spi_slaveSelect(unsigned char );
void spi_slaveDeSelect(unsigned char);
void displayDriverInit(void);
void displayOn(void);
void displayOff(void);
void wait(int);
int main(void);
void writeLedDisplay( int  );
void spi_writeWord ( unsigned char , unsigned char );

 void wait(int ms) {  
	for (int i=0; i<ms; i++){   
		_delay_ms(1); 
	} 
}
 void spi_masterInit(void) {
	DDR_SPI = 0xff;     // All pins output: MOSI, SCK, SS, SS_display  
	DDR_SPI &= ~BIT(SPI_MISO);   //  except: MISO input  
	PORT_SPI |= BIT(SPI_SS);   // SS_ADC == 1: deselect slave  
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1); // or: SPCR = 0b11010010; 
	// Enable spi, MasterMode, Clock rate fck/64 
	//   bitrate=125kHz, Mode = 0: CPOL=0, CPPH=0 
} 
 // Write a byte from master to slave 
 void spi_write( unsigned char data )     {  
	SPDR = data;     // Load byte --> starts transmission  
	while( !(SPSR & BIT(SPIF)) );   // Wait for transmission complete  
 } 
 // Write a byte from master to slave and read a byte from slave - not used here 
 char spi_writeRead( unsigned char data ) {  
	SPDR = data;     // Load byte --> starts transmission  
	while( !(SPSR & BIT(SPIF)) );   // Wait for transmission complete   
	data = SPDR;     // New received data (eventually, MISO) in SPDR  
	return data;     // Return received byte 
 } 
 // Select device on pinnumer PORTB 
 void spi_slaveSelect(unsigned char chipNumber) {  
	PORTB &= ~BIT(chipNumber); 
 } 
 // Deselect device on pinnumer PORTB 
 void spi_slaveDeSelect(unsigned char chipNumber) {  
	PORTB |= BIT(chipNumber); 
} 
 // Initialize the driver chip (type MAX 7219) 
 void displayDriverInit(void)  {  
	spi_slaveSelect(0);   // Select display chip (MAX7219)    
	spi_write(0x09);        // Register 09: Decode Mode    
	spi_write(0xFF);   //  -> 1's = BCD mode for all digits    
	spi_slaveDeSelect(0);  // Deselect display chip
	spi_slaveSelect(0);   // Select dispaly chip    
	spi_write(0x0A);        // Register 0A: Intensity    
	spi_write(0x0F);       //  -> Level 4 (in range [1..F])		-->Put on F for maximum Intensity 
	spi_slaveDeSelect(0);  // Deselect display chip
	spi_slaveSelect(0);   // Select display chip    
	spi_write(0x0B);     // Register 0B: Scan-limit    
	spi_write(0x03);      //  -> 1 = Display digits 0..1		-->Put on 3 to display 0..3  
	spi_slaveDeSelect(0);  // Deselect display chip
	spi_slaveSelect(0);   // Select display chip    
	spi_write(0x0C);    // Register 0B: Shutdown register    
	spi_write(0x01);    //  -> 1 = Normal operation    
	spi_slaveDeSelect(0);  // Deselect display chip 
 }
 // Set display on ('normal operation') 
 void displayOn(void)  {    
	 spi_slaveSelect(0);   // Select display chip    
	spi_write(0x0C);    // Register 0B: Shutdown register    
	spi_write(0x01);    //  -> 1 = Normal operation    
	spi_slaveDeSelect(0);  // Deselect display chip 
 }
 // Set display off ('shut down') 
 void displayOff(void)  {    
	spi_slaveSelect(0);   // Select display chip    
	spi_write(0x0C);    // Register 0B: Shutdown register    
	spi_write(0x00);    //  -> 1 = Normal operation    
	spi_slaveDeSelect(0);  // Deselect display chip 
 }

 int main(void) {  
	DDRB=0x01;     // Set PB0 pin as output for display select  
	spi_masterInit();               // Initialize spi module  
	displayDriverInit();            // Initialize display chip
	// clear display (all zero's)  
	for (char i =1; i<=4; i++) {        
		spi_slaveSelect(0);   // Select display chip        
		spi_write(i);     //  digit adress: (digit place)        
		spi_write(0);   //  digit value: 0        
		spi_slaveDeSelect(0); // Deselect display chip  
	}      
	wait(1000);
	// write 4-digit data     
	for (char i =1; i<=4; i++) {   
		spi_slaveSelect(0);       // Select display chip   
		spi_write(i);          //  digit adress: (digit place)   
		spi_write(i);     //  digit value: i (= digit place)   
		spi_slaveDeSelect(0);   // Deselect display chip     
		wait(1000);    
	}  
	writeLedDisplay(2587);  
	wait(1000);
	writeLedDisplay(-638);  
	return (1); 
}


void spi_writeWord ( unsigned char adress, unsigned char data ) {
	spi_slaveSelect(0);			// Select display chip
	spi_write(adress);				//  digit adress: (digit place)
	spi_write(data);				//  digit value: i (= digit place)
	spi_slaveDeSelect(0);		// Deselect display chip 
}

//schijf een positieve integer van maximaal 4 getalen weg of een negatieve van maximaal 3 integers
void writeLedDisplay( int value ){
	int i;
	if(value < 10000 && value >=0) {
		for(i=1; i<=4;i++) {
			spi_writeWord(i,(value%10));
			value = value/10;
		}
	} else if(value < 0 && value > -1000) {
		value = value * -1; //make value positive
		for(i=1; i<=3;i++) {
			spi_writeWord(i,(value%10));
			value = value/10;
		}
		spi_writeWord(4,10);
	}
}




