/*
 * CFile1.c
 *
 * Created: 2013-06-11 18:50:12
 *  Author: Przemo
 */ 

#include <avr/io.h>
#include <avr/eeprom.h>

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

char* czytajString(int start)
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