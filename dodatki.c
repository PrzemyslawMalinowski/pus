/*
 * CFile1.c
 *
 * Created: 2013-05-07 18:37:04
 *  Author: student
 */ 
#define F_CPU 16000000
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
char lineup[41]; 
char a;
char linedown[40];
int i=0;
void wyluskajStare(uint8_t vale){
	PORTA = (PORTA&0xF0)|((vale&0xF0)>>4);
}

void wyluskajMlode(uint8_t vale){
	PORTA = (PORTA&0xF0)|(vale & 0x0F);
}

void wyslijDane(uint8_t v){
		
	PORTA =0;
    PORTA |= 0x80;
	
		
    PORTA |= 0x40;
    PORTA =  ((PORTA & 0xF0)|( v>>4 & 0x0F));
	PORTA &= ~0x40;
	
	PORTA |= 0x40;
	PORTA =  ((PORTA & 0xF0)|( v & 0x0F));
	PORTA &= ~0x40;

	
	PORTA &= ~0x80;
	PORTA = 0;
	
}
void wyslijComend(uint8_t v){
	PORTA |= 0x40;
	PORTA =  ((PORTA & 0xF0)|( v & 0x0F));
	PORTA &= ~0x40;

}

void wyslijNapis(char* text){
	while (*text != 0)
	{
		wyslijDane(*text);
		text++;
	}
}