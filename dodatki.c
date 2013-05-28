/*
 * CFile1.c
 *
 * Created: 2013-05-07 18:37:04
 *  Author: student
 */ 

#include <stdio.h>
#include <avr/io.h>

void wyluskajStare(uint8_t vale){
	PORTA = (PORTA&0xF0)|((vale&0xF0)>>4);
}

void wyluskajMlode(uint8_t vale){
	PORTA = (PORTA&0xF0)|(vale & 0x0F);
}

void wyslijDane(uint8_t v){
		
	PORTA =  (PORTA | 0b01000000);//Wlac		
	PORTA =  (PORTA | 0b10000000);//Nadajemy   literki asf sa f
	wyluskajStare(v);
	PORTA =  (PORTA & 0b10111111); //Wylacz lock
	
	PORTA =  (PORTA | 0b01000000);//Lock
	wyluskajMlode(v);
	PORTA =  (PORTA & 0b10111111); //Wylacz lock
	PORTA &=  0b10111111;
	PORTA =  (PORTA & 0b10111111); //Wylacz lock
	
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