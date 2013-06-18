/*
 * CFile1.c
 *
 * Created: 2013-06-11 18:50:12
 *  Author: Przemo
 */ 

#include <avr/io.h>
#include <avr/eeprom.h>

int actual_position = 0;

char* dodajString(char* s)
{
	int length;
	
	char* txt;
	
	while(txt != NULL)
	{
		length ++;
		txt ++;
	}
	
	write_eeprom_array(actual_position,s,length);
	
	actual_position += 50;
}

char* czytajString(int start, int length)
{
	
	char* txt;
	read_eeprom_array(start,txt,length);
	
	return txt;
}