/*
 * GccApplication1.c
 *
 * Created: 2013-05-07 18:35:49
 *  Author: student
 */ 

	#define MENU_GLOWNE 0
	#define ROZGRYWKA 1
	#define WYNIKI 2
	#define OPCJE 3


//TODO wlaczyc po inicie
//Zalozenie
// R E x x 1 2 3 4
// Wyslanie 121
// 1 0 x x 1 1 1 1
// 1 1 x x 1 1 1 1
// 1 0 x x 0 0 0 1
// 1 1 x x 0 0 0 1
#define F_CPU 16000000

	/************************************************************************/
	/* PLIKI NAG£ÓWKOWE                                                     */
	/************************************************************************/
	
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
		
	/*
		Prototypy
	*/
	
	void show_main_menu();
	void show_highscore();
	void show_option();
	void input_name();
	void check_and_add_to_hotlist();
	void show_game();
	
	/************************************************************************/
	/* JAKIEŒ ZMIENNE!!                                                     */
	/************************************************************************/
	
	char charFromKeyBoard[100]; //aka player name;
	
	int cursosPosition=0;
	int comConf=0;
	int insertingName=0;
	int timepkt=0;
	int timerConfigured=0;
	int lost=0;
	int speed_value = 0;
		
	
	GameMode_T gm= ins_name;
	
	char buforPKT[20];
	char buforWyniku[20]= "Zdoby³: ";
	char * s;

	//Game:
	int playerY=0,enemyX=0,enemyY=0;
	
	/*
		Jakaœ funkcja
	*/
	
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
	
	/*
		Konfigurowanie portów
	*/
	void configurePorts(void){
			//wlaczenie Przerwania com
		
			UCSRB |= (1<<RXEN)| (1<<TXEN);
			UCSRB |= 1<< RXCIE;
			UCSRC |= (1<<URSEL) | 1<<UCSZ0| 1<<UCSZ1; //8bit mode
			UBRRL=103;//dzielnik 19200
			
			comConf=1;
	}
	
	/*
		Konfigurowanie timera
	*/

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

	int speed_game = 1000;
	void gameTest(int py,int ex,int ey)
	{
		
		if(ex==0 && ey==py)
		{
			lost = 1;			
		}
		
		if(ex == -1)
		{
			enemyX = 16;
			enemyY = rand() % 4 + 1;
			speed_game -= (50 + speed_value*40);
			
		}
		//enemyX=enemyX-1;
		
		SetDisplay(py,enemyX--,ey);
		_delay_ms(speed_game - speed_value*400);
		
		
	}

	void resetGameVal(int ey)
	{
		playerY=1;
		enemyX=10;
		enemyY=	ey;
		lost=0;
	}

//parametry okna
	int bylo_pierwszy_raz = 0;
	int bylo_w_menu_wlasciwym = 1;

	uint8_t wybor = 0;

	int wyswietl_okno = 0;
	int state = MENU_GLOWNE;

/*

	TUTAJ ROZPOCZYNAMY

*/

int main(void)
{
	resetEEPROM();
	/* Ustawienia portow */ 
		DDRA = 0xFF;
		DDRC = 0x00;
		PORTC = 0xFF;
		uint8_t a = 0;
	
	
	
	initLCD();
	
	while(1)
	{
		//Pobieranie klawiszów
			key_init();
			wybor = get_key();
			
		
		//PORTA = a;
		
		//ustawianie aktualnego stanu
			switch(state){
				case MENU_GLOWNE : {
					show_main_menu();
				} break;
				
				case ROZGRYWKA : {
					show_game();
				} break;
				
				case WYNIKI : {
					show_highscore();
				} break;
				
				case OPCJE : {
					show_option();
				} break;
			}
		
		
		
	}	
}


ISR(INT1_vect) 
{
	timepkt++;
	//Wysweitlc na 8segmentowym
}


/*
	Wyœwietlenie menu g³ównego
*/

	void show_main_menu(){
		//Pierwsze wyœwietlenie okna
	
		if(!bylo_pierwszy_raz){
		    SetLineEmpty();
			writeTwoLines("PUS ver 1.0 MENU:", "1. Rozpocznij");
			bylo_pierwszy_raz = 1;
		}
	
	
		if(!bylo_w_menu_wlasciwym){
		
			//clearLCD();
		
			switch(wyswietl_okno){
			
				case 0: {
					writeTwoLines("PUS ver 1.0 MENU:", "1. Rozpocznij");
				} break;
			
				case 1: {
					writeTwoLines("PUS ver 1.0 MENU:\0", "2. Najlepsi\0");
				} break;
			
				case 2: {
					writeTwoLines("PUS ver 1.0 MENU:\0", "3. Opcje\0");
				} break;
			
			}
		
			bylo_w_menu_wlasciwym = 1;
		}
	
		//zachowanie po naciœniêciu przycisku
	
			//lewego
	
			if(wybor == 0x06){
				wyswietl_okno -= ((wyswietl_okno > 0) ? 1 : 0);
				bylo_w_menu_wlasciwym = 0;
				wybor = 0x00;
				_delay_ms(300);
			}
	
			//prawego
	
			if(wybor == 0x0E){
				wyswietl_okno += ((wyswietl_okno < 2) ? 1 : 0);
				bylo_w_menu_wlasciwym = 0;
				wybor = 0x00;
				_delay_ms(300);
			}
	
			//srodkowy - akceptacja
	
			if(wybor == 0x0A){
				
				state = wyswietl_okno + 1;
				bylo_w_menu_wlasciwym = 0;
				bylo_pierwszy_raz = 0;
				
				_delay_ms(300);
				
			}
	}
	
	uint8_t max_wynikow = 0;
	uint8_t numer_wyniku = 0;
	
	char* wyniki[10];
	
	/*
		Poka¿ hotlistê!
	*/
	
	void show_highscore(){
		
		//pierwsze wywolanie funkcji 
			if(!bylo_pierwszy_raz) {
				
				char* pierwszy;
				
				max_wynikow = 10;				
				
				
				pierwszy = readString(0);
					
				writeTwoLines("Najlepsi gracze:", pierwszy);
				
				bylo_w_menu_wlasciwym = 1;
				bylo_pierwszy_raz = 1;
			}
		
			if(!bylo_w_menu_wlasciwym){
				//clearLCD();
				writeTwoLines("Najlepsi gracze:", readString(numer_wyniku * 16));
				bylo_w_menu_wlasciwym = 1;
			}
		
		//zachowanie po naciœniêciu przycisku
		
			//lewego
		
				if(wybor == 0x06){
					
					numer_wyniku -= ((numer_wyniku > 0) ? 1 : 0);
					bylo_w_menu_wlasciwym = 0;
					
					wybor = 0x00;
					_delay_ms(300);
				}
		
			//prawego
		
				if(wybor == 0x0E){
					numer_wyniku += ((numer_wyniku < max_wynikow - 1) ? 1 : 0);
					bylo_w_menu_wlasciwym = 0;

					wybor = 0x00;
					_delay_ms(300);
				}
		
			//srodkowy - akceptacja
		
				if(wybor == 0x0A){
					
					state = MENU_GLOWNE;
					
					bylo_w_menu_wlasciwym = 0;
					bylo_pierwszy_raz = 0;
					
					//clearLCD();
					
					_delay_ms(300);
					
				}
		
	}

	/*
		Poka¿ opcjê dotycz¹c¹ gry
	*/
	
	void show_option(){
		
		//pierwsze wywolanie funkcji
		if(!bylo_pierwszy_raz) {
			
			if(!speed_value)
			{
				writeTwoLines("Opcje:", "level: easy");
			}
			else
			{
				writeTwoLines("Opcje:", "level: HARD");
			}
			
			
			
			bylo_w_menu_wlasciwym = 1;
			bylo_pierwszy_raz = 1;
		}
		
		if(!bylo_w_menu_wlasciwym){
			//clearLCD();
			
			if(!speed_value)
			{
				writeTwoLines("Opcje:", "level: easy");
			}
			else
			{
				writeTwoLines("Opcje:", "level: HARD");
			}
			
			bylo_w_menu_wlasciwym = 1;
		}
		
		//zachowanie po naciœniêciu przycisku
		
		//lewego
		
		if(wybor == 0x06){
			
			speed_value = 0;
			bylo_w_menu_wlasciwym = 0;
			
			wybor = 0x00;
			_delay_ms(300);
		}
		
		//prawego
		
		if(wybor == 0x0E){
			speed_value = 1;
			bylo_w_menu_wlasciwym = 0;

			wybor = 0x00;
			_delay_ms(300);
		}
		
		//srodkowy - akceptacja
		
		if(wybor == 0x0A){
			
			state = MENU_GLOWNE;
			
			bylo_w_menu_wlasciwym = 0;
			bylo_pierwszy_raz = 0;
			
			_delay_ms(300);
			
		}
		
	}
	
	void show_game()
	{
		//SPRAWDZAM YCZY PIERWSZY RAZ WESZLIŒMY DO OKNA
			if(!bylo_pierwszy_raz)
			{
				//configureTimer();
				//sei();
				
				input_name();
				gm = game;
				
				int zarodek ;
				zarodek= 12345;
				srand(zarodek);
				resetGameVal( rand() % 4 + 1);
				
				bylo_pierwszy_raz = 1;
			}
			
		//SPRAWDZAMY CZY NIE PRZEGRALEŒ
			if(lost == 1)
			{
				gm = lost_game;
				_delay_ms(1000);
			}
		
		//sprawdzamy odpowiednie akcje
			switch(gm)
			{
				//stan gry
					case game: {
						
						if(wybor == 0x09)
						{
							playerY= (playerY+2)%4+1;
							gameTest(playerY,enemyX,enemyY);
						}
						else if(wybor == 0x0a)
						{
							
							playerY=(playerY+4)%4+1;
							gameTest(playerY,enemyX,enemyY);
						}else
						{
							gameTest(playerY,enemyX,enemyY);
						}
						
						/*
						if(timerConfigured == 0)
						{
							configureTimer();
						}*/
						
						
						/*
						char* a;
						char* b;
						
						itoa(playerY,a,10);
						itoa(enemyY,b,10);
						
						writeTwoLines(a,b);
						_delay_ms(5000);*/
						
					} break;
				
				
				//w przypadku przegranej
					case lost_game: {
						
						itoa(timepkt,buforPKT,10);
						strcat(buforWyniku, buforPKT);
						
						writeTwoLines("Przegrana punkty:",buforWyniku);
						_delay_ms(4000);
						
						state = main_menu;
						bylo_pierwszy_raz = 0;
						bylo_w_menu_wlasciwym = 1;
						
					} break; 
			}
	}

	void input_name()
	{
		//TODO
	}
	
	void check_and_add_to_hotlist()
	{
		//TODO
	}