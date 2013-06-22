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
		_delay_ms(10);
	}
}

void SetDisplay(int myPos, int obstaclex,int obstacley)
{

	////////////////////////////
	for (i=0;i<41;i++)
	{
		lineup[i]=' ';		
	}
	for (i=0;i<40;i++)
	{
		linedown[i]=' ';
	}
	
	
	linedown[40]=0;
	lineup[40]=0;
	
	/////////////////////////
	/*
	
	if(myPos == 3 || myPos == 4)
	{
		if (myPos == 3)
		{
			linedown[0]='u';
		}else
		{
			linedown[0]='d';
		}				
				
	}else
		{
			if (myPos == 1)
			{
				lineup[0]='u';
			}else
			{
				lineup[0]='d';
			}		
		}	
	
	
	*////////////////////////////////
	
	if(obstacley == 3 || obstacley == 4)
	{
		if (obstacley == 3)
		{
			linedown[obstaclex]='<';
		}else
		{
			linedown[obstaclex]='_';
		}
		
	}else
	{
		if (obstacley == 1)
		{
			lineup[obstaclex]='<';
		}else
		{
			lineup[obstaclex]='_';
		}
	}
	wyslijNapis(lineup);
	
	wyslijNapis(linedown);
	_delay_ms(300);
	
}