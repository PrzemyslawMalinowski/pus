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

#include "dodatki.h"
#include "eeprom.h"
#include "klawiatura.h"

int charFromKeyBoard[100];
int cursosPosition=0;

void configurePorts(void) {
	// A: Which segments are lit (active 0).
	
	/*UBRRL = 103; //dzielnik dla 9600
	UCSRB |= 1<<RXEN;
	UCSRB |= 1<<RXCIE;*/
	
	//wlaczenie Przerwania com
	
	UCSRB |= (1<<RXEN)| (1<<TXEN);
	UCSRB |= 1<< RXCIE;
	UCSRC |= (1<<URSEL) | 1<<UCSZ0| 1<<UCSZ1; //8bit mode

	UBRRL=103;//dzielnik 19200
	
	
}
/*ISR(USART_RXC_vect)
{
	if(UDR==8)
	{
		cursosPosition--;	
	}else	
	{
		charFromKeyBoard[cursosPosition]=UDR;

		UDR=charFromKeyBoard[cursosPosition];
		cursosPosition++;
	}
	
}*/
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

int main(void)
{
	
	/* Wszystkie linie portu A bêd¹ wyjœciami */
	DDRA = 0xFF;  /* 0xFF binarnie 1111 1111 */
	
	//
	DDRC = 0x00;
	PORTC = 0xFF;
	

	/* Pocz¹tek nieskoñczonej pêtli */
	
	uint8_t a = 0;
	
	while(1)
	{
		key_init();
		
		uint8_t t = get_key();
		
		if(t != a && t != 0)
		{
				a = 0;
				a = t;
		}

		PORTA = a;
	}
	
}