/*
 * lcd.c
 *
 * Created: 2013-06-22 13:24:09
 *  Author: Bagieta
 */ 

#define F_CPU 16000000
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "dodatki.h"
#include "lcd.h"

char lineup[41];
char linedown[40];
int curPos=0;
int lcdi=0;

void wyslijNapis(char* text)
{
	while (*text != 0)
	{		
		wyslijDane(*text);
		text++;
		_delay_ms(1);
	}
}


void SetLineEmpty()
{
	
	for (lcdi=0;lcdi<41;lcdi++)
	{
		lineup[lcdi]=' ';
	}
	for (lcdi=0;lcdi<40;lcdi++)
	{
		linedown[lcdi]=' ';
	}
	
	//String breaker
	linedown[40]=0;
	lineup[40]=0;
	
}

void SetDisplay(int myPos, int obstaclex,int obstacley)
{

	SetLineEmpty();
	switch (myPos)
	{
		case 1:
			lineup[0]='\'';
			break;
		case 2:
			lineup[0]=',';
			break;
		case 3:
			linedown[0]='\'';
			break;
		case 4:
			linedown[0]=',';
			break;;			
	}
		
	switch (obstacley)
	{
			case 1:
			lineup[obstaclex]='\'';
			break;
			case 2:
			lineup[obstaclex]=',';
			break;
			case 3:
			linedown[obstaclex]='\'';
			break;
			case 4:
			linedown[obstaclex]=',';
			break;;
	}
	if(obstaclex==0 && obstacley == myPos)
	{
		switch (obstacley)
		{
			case 1:
			lineup[obstaclex]='$';
			break;
			case 2:
			lineup[obstaclex]='$';
			break;
			case 3:
			linedown[obstaclex]='$';
			break;
			case 4:
			linedown[obstaclex]='$';
			break;;
		}
	}
	
	wyslijNapis(lineup);
	
	wyslijNapis(linedown);
	_delay_ms(30);
	
}

void wyslijLine2(char* text, char* text2)
{
	while (*text != 0)
	{
		lineup[curPos]= *text;
		curPos++;
		
	}
	curPos=0;
	while (*text != 0)
	{
			linedown[curPos]= *text2;
			curPos++;
			
	}
	curPos=0;
}

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
    wyslijComend(0x80);//Do pierwszej lini
	_delay_ms(5);
	wyslijComend(0x00);
	/*
	wyslijComend(0xC0);//Do 2 lini
	_delay_ms(5);
	wyslijComend(0x00);*/
	
	
	_delay_ms(5);
	
	//wyslijComend(0x04);//Tryb pisanie [_DCDA      ]
	//wyslijComend(0x05);//Tryb pisanie [      _DCBA]
	//wyslijComend(0x06);//Tryb pisanie [      ABCD_]
	//wyslijComend(0x07);//Tryb pisanie [ABCD_      ]
	
	
}