/*
 * GccApplication1.c
 *
 * Created: 2013-05-07 18:35:49
 *  Author: student
 */ 

//#define 

//TODO wlaczyc po inicie
//Zalozenie
// R E x x 1 2 3 4
// Wyslanie 121
// 1 0 x x 1 1 1 1
// 1 1 x x 1 1 1 1
// 1 0 x x 0 0 0 1
// 1 1 x x 0 0 0 1

#define F_CPU 16000000 

#include <avr/io.h>

#include <util/delay.h>

#include "dodatki.h"
#include "eeprom.h"

void initLCD()
{
	_delay_ms(15);
	for (int i=0;i<3;i++)
	{
		wyslijComend(0b00000011);
		_delay_ms(5);		
	}
	wyslijComend(0b00000010);
	_delay_ms(5);
	
	wyslijComend(0b00000010);
	_delay_ms(5);
	wyslijComend(0b00001000);
	_delay_ms(5);
	
	
	wyslijComend(0b00000000);
	_delay_ms(5);
	wyslijComend(0b00001000);
	_delay_ms(5);
	
	wyslijComend(0b00000000);
	_delay_ms(5);
	wyslijComend(0b00000001);
	_delay_ms(5);
	
	wyslijComend(0b00000000);
	_delay_ms(5);
	wyslijComend(0b00000110);
	_delay_ms(5);
	
	wyslijComend(0x00);
	_delay_ms(5);
	wyslijComend(0x0F);
	_delay_ms(5);
	wyslijComend(0x0C);
	_delay_ms(5);
	wyslijComend(0x00);
	
}

int main(void)
{
	//DDRA = 0xFF;
	//initLCD();
		dodajString("aa\0");
		char* tab = czytajString(0);
		//printf("%s",tab);
}