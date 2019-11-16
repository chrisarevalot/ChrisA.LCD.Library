#include <avr/io.h>
#include <util/delay.h>

#define REGDIR  DDRA
#define DATAD   PORTA
#define CONDIR  DDRC
#define INSTR   PORTC

void Init(void);						// Initializes the Screen
void ClearS(void);
void PrintC(unsigned char one);		// Prints a character.
void PrintS(char *numb);				// Prints a string.
void LCD_SecLine(void);				// Print on Second Line of LCD. (Must be together with PrintS() to write to second line)
void PrintN(int number);				// Print an Integer.
void printD(double dou);				// Print a Double.



void Init(void)
{
	 REGDIR = 255;		// Set Port A as Output. (0b11111111)
	 CONDIR = 255;		// Set Port C as Output. (0b11111111)
						// Initializing the LCD
	 INSTR = 0;			// Write to E = PINC2,RW = PINC1, RS = PINC0. (0b00000000), E = 0 (Enable OFF),
						// RW = 0 (Write to LCD), RS = 0 (Receive Instructions).
	 _delay_ms(20);		// Delay by 30ms.
	 DATAD = 15;			// Write Data 0b00001111 to Port A. Initialize LCD, Display ON, Cursor ON, Blink ON. (Instructions)
	 _delay_ms(1);		// Delay by 1ms.
	 INSTR = 4;			// Write 0b00000100 to Port C, Enable = ON.
	 _delay_ms(0.5);		// Delay by 0.5ms.
	 INSTR = 00;			// Write 0b00000000 to Port C, ENable = OFF and Ready to receive Instructions.
	 _delay_ms(20);		// Delay by 30ms.
	 DATAD = 01;			// Write Data 0b00000001 to Port A. Clear Screen Instruction
	 _delay_ms(1);		// Delay by 1ms.
	 INSTR = 4;			// Write 0b00000100 to Port C, Enable = ON.
	 _delay_ms(0.5);		// Delay by 0.5ms.
	 INSTR = 00;			// Write 0b00000000 to Port C, ENable = OFF and Ready to receive Instructions.
	 _delay_ms(20);		// Delay by 30ms.
	 return;
}

void PrintC(unsigned char one)
{
	 DATAD = one;		// Write Character "S" to Port A.
	 INSTR = 01;			// Write Instruction to Port C. 0b00000001, RS = ON. PINC0 = 1.(Receive Data)
	 _delay_ms(20);		// Delay by 30ms.
	 INSTR = 5;			// RS = ON, Enable = ON.
	 _delay_ms(0.5);		 // Delay by 0.5ms.
	 INSTR = 00;			// RS = OFF, Enable = OFF.
	 _delay_ms(20);		// Delay by 30ms
	 return;
}

void PrintS(char *numb)			// Print a String
{
	 while(*numb > 0)			//Loop to Print each character at the time.
	 {
		 PrintC(*numb++);
	 }
	 return;
}

void LCD_SecLine()
{
	DATAD = 0xBC;		// Write Data 0b00000001 to Port A. Print to 2nd Line of LCD instruction.
	_delay_ms(2);		// Delay by 2ms.
	INSTR = 4;			// Write 0b00000100 to Port C, Enable = ON.
	_delay_ms(0.5);		// Delay by 0.5ms.
	INSTR = 00;			// Write 0b00000000 to Port C, ENable = OFF and Ready to receive Instructions.
	_delay_ms(20);		// Delay by 20ms.
	return;
}

void PrintN(int number)		// Prints an Integer to LCD.
{
	char numstring[10];		// Character array.
	int y = number;			// Integer
	itoa(y,numstring,10);	// Converts integer to array of characters.
	PrintS(numstring);		// Print the array of characters as a string.
	return;
}

void PrintD(double dou)			// Prints a double to LCD.
{
	char doub[10];				// Character array.
	dtostrf(dou,5,4,doub);		// Converts double to array of characters.
	PrintS(doub);				// Prints the array of characters as a string.
	return;
}

void ClearS()
{
	DATAD = 01;			// Write Data 0b00000001 to Port A. Clear Screen Instruction
	_delay_ms(1);		// Delay by 1ms.
	INSTR = 4;			// Write 0b00000100 to Port C, Enable = ON.
	_delay_ms(0.5);		// Delay by 0.5ms.
	INSTR = 00;			// Write 0b00000000 to Port C, ENable = OFF and Ready to receive Instructions.
	_delay_ms(2);		// Delay by 30ms.
	return;
}
