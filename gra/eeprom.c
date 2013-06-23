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
uint8_t skok = 16;

uint8_t* dodajString(char* s)
{	
	char* txt = s;
	
	int i = 0;
	
	while(i < skok)
	{
		eeprom_write_byte(actual_position + i, ' ');
		i++;
	}
	
	i = 0;
	
	while(*txt != '\0')
	{
		eeprom_write_byte(actual_position + i, (uint8_t) *txt);
		i++;
		txt++;
	}
	
	actual_position += skok;
	
	return (actual_position - skok);
}

char* readString(uint8_t start)
{
	return czytajString(actual_position - (actual_position - start));
}

char* czytajString(uint8_t* start)
{
	uint8_t* actual = start;
	
	char tab[skok];
	int i = 0;
	
	while(i < skok)
	{
		tab[i++] = (char) eeprom_read_byte(actual);
		
		actual++;
	}
	
	char* txt = tab;
	return txt;
}

uint8_t* ilosc_pozycji(){
	return actual_position;
}

void resetEEPROM(){
	
	actual_position = 0;
	
	for (int i = 0; i < 10; i++)
	{
		char tab[16];
		
		itoa(i,tab,10);
		strcat(tab,". ANONIM : 0\0");
		dodajString(tab);
	}
	
}