/*
 * eeprom.c
 *
 * Created: 2013-06-22 16:54:20
 *  Author: Bagieta
 */ 

#include <avr/io.h>
#include <avr/eeprom.h>
#include "eeprom.h"
uint8_t* actual_position = 0;

uint8_t* dodajString(char* s)
{
	uint8_t length = 0;
	
	char* txt = s;
	
	while(*txt != '\0')
	{
		eeprom_write_byte(actual_position + length, (uint8_t) *txt);
		length += 1;
		txt++;
	}
	
	eeprom_write_byte(actual_position + length, (uint8_t)'\0');
	
	actual_position += 50;
	
	return actual_position - 50;
}

char* czytajString(uint8_t start)
{
	uint8_t * actual = start;
	
	char tab[50];
	int i = 0;
	while(i < 50)
	{
		tab[i++] = (char)eeprom_read_byte(actual);
		
		actual++;
	}
	
	char * txt = tab;
	
	return txt;
}