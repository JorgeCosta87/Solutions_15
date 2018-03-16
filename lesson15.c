

/*
 * Exercise 1. Simulate and comment the following C code for the  μC8051 microcontroller.
*/

//This program copies the sentence from the code space to the external memory
#include "C8051F340.h"

//VariÃ¡veis globais. Estas tem de ser globais

__code unsigned char cFrase[]="O meu nome e Bond! James Bond!";	//declare variables at ...
__data __at(0x40) unsigned char iFrase[30]; 	//declare variables at internal data space
__xdata __at(0x300) unsigned char xFrase[30];	//declare variables at external data space


void main (void)
{
	unsigned char idx=0;


		while (cFrase[idx] != '\0')  // cycle until? 

		{ //till it reaches the end of the setence
			iFrase[idx] = cFrase[idx];	//Copy the sentence from the code address to the internal ram
			xFrase[idx] = iFrase[idx];	//Copy the sentence from the internal ram to the external memory
			idx++;
		}; 

		while(1); // Endless cycle
}//--------- END MAIN ---------


/*
 * Exercise 2. Simulate and comment the following C code for the  μC8051 microcontroller.
 * The proposed code has an execution error that should be identified and corrected. Submit
 * both code versions: the one with identified error with the appropriate comments identifying 
 * the code malfunctioning; also the corrected code version should be submitted. 
*/

include "C8051F340.h"

#define MAXINT 32
#define MAXEXT 32

//VariÃ¡veis globais. Estas tem de ser globais

__data __at(0x30) unsigned char iNum1[MAXINT]; //declare variables at internal data spcae at the address (0x30)
__data __at(0x40) unsigned char iNum2[MAXINT]; //declare variables at internal data spcae at the address (0x40)

__xdata __at(0x300) unsigned char xNum1[MAXEXT]; //declare variables at external data spcae at the address (0x300)
__xdata __at(0x2D9) unsigned char xNum2[MAXEXT]; //declare variables at external data spcae at the address (0x2D9)


void main (void)
{
	unsigned char idx=0;

	for (idx=0;idx<MAXINT;idx++){ // ciclo ate 31
		iNum1[idx] = idx;
		iNum2[idx]= idx;	//?
	}

	for (idx=MAXINT;idx>0;idx--){ // ciclo ate ? 
		iNum2[idx] = iNum2[idx];	//?
	}

	for (idx=0;idx<MAXEXT;idx++){ // ciclo ate ? 
		xNum2[idx] = xNum1[idx];	//?
	}

	while(1); // Endless cycle
}//--------- END MAIN ---------

/*
 * Exercise 3. Simulate and comment the following C code for the  μC8051 microcontroller.
 * This program does not generate generates errors but a number of warnings may be identified.
 * You should interpret the generated warnings, correct them and then proceed with the simulation
 * and commenting of the code.
*/

#include "C8051F340.h"

#define SIZE 132

//Declare big array at code space
__code __at(0x2000) int ValorLido[] = {479,479,477,477,476,476,476,476,475,473,473,473,473,472,
471,469,469,469,468,465,465,464,461,461,461,459,457,456,453,453,450,449,449,449,449,451,451,449,
449,449,448,445,445,446,444,444,444,443,441,442,441,440,439,440,440,441,446,453,460,469,478,485,
493,501,509,516,521,525,532,537,538,541,543,545,545,549,551,551,553,555,553,553,553,552,551,552,549,
551,549,549,549,548,549,549,549,549,548,548,545,549,545,545,547,545,545,552,543,543,543,541,540,540,
537,537,536,533,533,531,528,527,525,523,521,515,515,513,511,509,508,505,501};  //Overflow 509508, just set a comma.

__xdata __at(0x300) int xNum[SIZE]; //declare variables at external data space


void main (void)
{
	unsigned int idx=0; // char idx=0; char range is -128 to 127
	int valor;

		for (idx=0;idx<SIZE;idx++){ // 0 to 131
			xNum[idx] = ValorLido[idx];
		}; 
		
		for (idx=0;idx<SIZE;idx++){ // cycle
			valor = xNum[idx];	//?
			valor = valor>>8;
			xNum[idx] = valor;
		}

		while(1); // Endless cycle
}//--------- END MAIN ---------



/*
 * Exercise 4. In this project a program that is able to transfer data between different
 * μC8051 memory spaces is proposed. Using the C language, create a project and define,
 * in its properties, the use of external memory (see figure). Write the phrase "Hello," 
 * in the internal RAM (starting at address 0x30), the phrase "how are" in the external 
 * RAM (starting at address 0x0300), and the phrase "You?" also in the external RAM at a
 * ddress 0x400. Copy the contents of the three sentences to the external RAM, from address
 * 0x0500, in the correct order to create an english sentence. Simulate and verify the contents 
 * of the memories at the proposed addresses..
*/

#include "C8051F340.h"


__data __at(0x30) 	unsigned char iMsg1[] = "Hello";
__xdata __at(0x0300) 	unsigned char xMsg2[] = "How are";
__xdata __at(0x0400) 	unsigned char xMsg3[] = "you?";

__xdata __at(0x0500) 	unsigned char finalMsg[20]; 

void strcat(char dest[], const char src[]);
void strcpy(char dest[], const char src[]);

void main(void)
{
	strcpy(finalMsg,iMsg1);
	strcat(finalMsg,xMsg2);
	strcat(finalMsg,xMsg3);

	while(1);
}

void strcat(char dest[], const char src[])
{
	unsigned int i,j;

	for(i = 0; dest[i] != '\0' ; i++);

	dest[i++] = 31; //31, represents a space in ascii code
	
	for(j = 0; src[j] !='\0' ; i++, j++)
	{
		dest[i] = src[j];
	}
	dest[i] = '\0';
}

void strcpy(char dest[], const char src[])
{
	unsigned int i;

	for(i = 0; src[i] !='\0' ; i++)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';
}


/*
 * Exercise 5. Create a project that creates an array with the alphabet written in
 * upper case letters. Write the created array into internal memory starting at address
 * 0x3A. Store a lowercase copy of the array into the external memory starting at address 0x3AA.
 * Simulate and verify the contents of the memories at the proposed addresses.
*/

#include "C8051F340.h"


#define DIM 24

__data __at(0x3A)  unsigned char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVXZ";
__xdata __at(0x3AA) unsigned char aux[24];

void main(void)
{
	unsigned int i;

	for(i = 0; i < DIM ; i++)
	{
		aux[i] = alphabet[i] + 0x20;
	}

	while(1);
}

/*
 * Exercise 6. Create a project that is able to write your name to the IDE virtual LCD.
 * For this project you may use the C function that writes one byte to the LCD. Also 
 * the LCD configuration function should be called before any writing may be executed.
 * Using the given C functions write your name in uppercase to the LCD. Consult with 
 * your instructor on how to connect the virtual LCD in simulation mode. Configure 
 * the virtual device "Virtual HW -> LCD display "as shown in the figure, option 
 * "disable delays" to select the so it is possible to simulate, ignoring the processing 
 * times. Simulate the application and confirm the result on the LCD.
*/

#include "C8051F340.h"


#define LCD P2
#define RS  P1_0
#define RW  P1_1
#define E   P1_2


void WritetoLCD (unsigned char valor, unsigned char tipo);
void ApagaLCD(void);
void ConfigLCD(void);

void main(void)
{
	ConfigLCD();

	while(1)
	{
		WritetoLCD('J', 1);
		WritetoLCD('O', 1);
		WritetoLCD('R', 1);
		WritetoLCD('G', 1);
		WritetoLCD('E', 1);

		WritetoLCD(0b00000001,0);  	// limpa LCD
		WritetoLCD(0b10000000,0);	// escreve na primeira linha
	}
}


void WritetoLCD (unsigned char valor, unsigned char tipo){

	RW=0;
	RS=tipo;
	LCD=valor;
 	E=1;
 	E=0;
}

void ApagaLCD(void){
	WritetoLCD(0b00000001, 0);
}

void ConfigLCD(void){

	WritetoLCD(0b00111000,0);	// Modo de funcionamento 2 linhas,caracter:5x7 pixeis;
	WritetoLCD(0b00000001,0);  	// limpa LCD
	WritetoLCD(0b00001111,0);	// cursor on e a piscar
	WritetoLCD(0b00000110,0);	// escreve da esquerda para a direita 
	WritetoLCD(0b10000000,0);	// escreve na primeira linha
}

#include "C8051F340.h"


#define DIM 10

__code unsigned char Tabela[]={0b11000000,0b11111001,0b10100100, 0b10110000,0b10011001, 0b10010010,0b10000011, 0b11111000, 0b10000000, 0b10011000}; 


/*
ex_07

*/

void main(void)
{
	char unsigned var = 0b00101010;
	char unsigned testVar = 0b00000000;

	while(1)
	{
		switch(testVar)
		{
			case 0 :
			{
				if (var&0b00000001)
					P1 = 0b11000000;
				else
					P1 = 0b10111111;
				testVar=1;
				break;
			}
			case 1 :
			{
				if (var&0b00000010)
					P1 = 0b11111001;
				else
					P1 = 0b10111111;
				testVar=2;
				break;
			}
			case 2 :
			{
				if (var&0b00000100)
					P1 = 0b10100100;
				else
					P1 = 0b10111111;
				testVar=3;
				break;
			}
			case 3 :
			{
				if (var&0b00001000)
					P1 = 0b10011001;
				else
					P1 = 0b10111111;
				testVar=4;
				break;
			}
			case 4 :
			{
				if (var&0b00010000)
					P1 = 0b10010010;
				else
					P1 = 0b10111111;
				testVar=5;
				break;
			}
			case 5 :
			{
				if (var&0b00100000)
					P1 = 0b10000011;
				else
					P1 = 0b10111111;
				testVar=6;
				break;
			}
			case 6 :
			{
				if (var&0b010000000)
					P1 = 0b11111000;
				else
					P1 = 0b10111111;
				testVar=7;
				break;
			}
			case 7 :
			{
				if (var&0b10000000)
					P1 = 0b10000000;
				else
					P1 = 0b10111111;
				testVar=0;
				break;
			}
		}
	}
	

}
