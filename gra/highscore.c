/*
 * highscore.c
 *
 * Created: 2013-06-22 13:48:48
 *  Author: Bagieta
 */ 
#define F_CPU 16000000

#include "lcd.h"
#include "highscore.h"
#include "eeprom.h"
//#include "eeprom.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

void DisplayHighScore(int which)
{
	char* temp=czytajString(which);
	wyslijNapis(temp ) ;
	_delay_ms(100);
	
}