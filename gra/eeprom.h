/*
 * CFile1.c
 *
 * Created: 2013-06-11 18:50:12
 *  Author: Przemo
 */ 

#ifndef EEPROM_H
#define EEPROM_H

#include <avr/io.h>
#include <avr/eeprom.h>



uint8_t* dodajString(char* s);
char* czytajString(uint8_t* start);
uint8_t* pozycja();
void resetEEPROM();
char* readString(uint8_t start);

#endif