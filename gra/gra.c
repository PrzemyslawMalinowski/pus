/*
 * GccApplication1.c
 *
 * Created: 2013-05-07 18:35:49
 *  Author: student
 */ 

//#define 

//TODO wlaczyc po inicie
//Zalozenie
// R E x x 1 2 3 4
// Wyslanie 121
// 1 0 x x 1 1 1 1
// 1 1 x x 1 1 1 1
// 1 0 x x 0 0 0 1
// 1 1 x x 0 0 0 1
#define F_CPU 16000000

#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include "dodatki.h"
#include "eeprom.h"
#include "klawiatura.h"
#include "lcd.h"
#include "highscore.h"

typedef enum { main_menu, high_score, game,ins_name,lost_game } GameMode_T;
	
char charFromKeyBoard[100]; //aka player name;
int cursosPosition=0;
int comConf=0;
int insertingName=0;
int timepkt=0;
int timerConfigured=0;
GameMode_T gm= ins_name;
int lost=0;
char buforPKT[20];
char buforWyniku[20]= "Zdoby³: ";
char * s;
//Game:
int playerY,enemyX,enemyY;
ISR(USART_RXC_vect)
{
	//if(UDR==ENTER)
	//{
		//skoncz
	//}
	if(insertingName==0){
		//escape nie wiem jaki ma enter roznie jest odbierany na rozne systemy
		if(UDR==27)
		{
			insertingName=1;
			gm=game;
		}
		//backspaec
		if(UDR==8)
		{
			UDR=' ';
			cursosPosition--;
		}		
		else
		{
			charFromKeyBoard[cursosPosition]=UDR;
			UDR=charFromKeyBoard[cursosPosition];
			cursosPosition++;
		}
	}	
	
}

void configurePorts(void){
		//wlaczenie Przerwania com
		
		UCSRB |= (1<<RXEN)| (1<<TXEN);
		UCSRB |= 1<< RXCIE;
		UCSRC |= (1<<URSEL) | 1<<UCSZ0| 1<<UCSZ1; //8bit mode
		UBRRL=103;//dzielnik 19200
		comConf=1;
}
void configureTimer(void)
{
	 TCCR0 = 0x05; //(1 << CS02) | (1 << CS00); prescaler na 1024
	 // TIFR |= (1 << TOV0);
	 TIMSK |= (1 << TOIE0); // aktywne przerwanie overflow
	 // timer_enable_int(_BV(TOIE1));
	 TCNT0 = 0;
	 sei();	
	 timerConfigured=1;
}
void gameTest(int py,int ex,int ey)
{
	if(ex==0 && ey==py)
	{
		lost=1;
	}	
	SetDisplay(py,ex--,ey);

}
void resetGameVal(int ey)
{
	playerY=1;
	enemyX=30;
	enemyY=	ey;
	lost=0;
}

int main(void)
{
	
	/* Wszystkie linie portu A bêd¹ wyjœciami */
	DDRA = 0xFF;  /* 0xFF binarnie 1111 1111 */	
	DDRC = 0x00;
	PORTC = 0xFF;
	uint8_t a = 0;
	/////////////////////////////////////
	int zarodek ;
	zarodek= 12345;	
	srand(zarodek); 
	resetGameVal( rand()%4+1);
	
	while(1)
	{
		//Pobieranie klawiszów
		key_init();
		uint8_t t = get_key();
		if(t != a && t != 0)
		{
			a = 0;
			a = t;
		}
		PORTA = a;
		
		if(lost==1)
		{
			gm=lost_game;
		}
					
		switch(gm)
		{
			case game:		
				
				if(t==3) //up
				{
					gameTest((playerY-1)%4+1,enemyX,enemyY);
				}
				else
				{
					gameTest((playerY+1)%4+1,enemyX,enemyY);					
				}
				
				if(timerConfigured==0)
				{
					configureTimer();
				}
				
				break;
			case high_score:
				DisplayHighScore(10);
				DisplayHighScore(20);
				DisplayHighScore(30);
				DisplayHighScore(40);
				DisplayHighScore(50);
				DisplayHighScore(60);
				DisplayHighScore(70);
				break;
			case main_menu:
				wyslijLine2("1. Graj","2. Wyniki");
				if(t==1)
				{
					gm=ins_name;
				}
				if(t==2)
				{
					gm=high_score;
				}
				break;
			case ins_name:
				if(comConf==0)
				{
					configurePorts();
				}				
				break;
			case lost_game:
				itoa(timepkt,buforPKT,10);
				strcat(buforWyniku, buforPKT);
				wyslijLine2(charFromKeyBoard,buforWyniku);
		}
			
						
	}	
}


ISR(INT1_vect) 
{
	timepkt++;
	//Wysweitlc na 8segmentowym
}


