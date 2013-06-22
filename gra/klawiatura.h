/*
 * Klawiatura.h
 *
 * Created: 2013-06-19 14:32:21
 *  Author: Przemo
 */ 


#ifndef KLAWIATURA_H
#define KLAWIATURA_H

//USTAWIENIE KLAWIATURY
//PORT[0 - 3] -> W[1 - 4] na przyk³ad PORT[0] -> W[1]
//PORT[4 - 7] -> K[1 - 4] na przyk³ad PORT[4] -> K[1]
// 
//



void key_init(void){
	DDRC = 0xF0;   // 1111 0000
	PORTC = 0x0F;   // 0000 1111
}

uint8_t get_key(void){
	uint8_t key=0;
	
	//pierwszy wiersz
	PORTC = 0b01111111;
	if (!bit_is_set(PINC, 0)) {while(!bit_is_set(PINC, 0)); key = 0x10;}
	if (!bit_is_set(PINC, 1)) {while(!bit_is_set(PINC, 0)); key = 0x20;}
	if (!bit_is_set(PINC, 2)) {while(!bit_is_set(PINC, 0)); key = 0x30;}
	if (!bit_is_set(PINC, 3)) {while(!bit_is_set(PINC, 0)); key = 0x40;}

	//drugi wiersz
	PORTC = 0b10111111;
	if (!bit_is_set(PINC, 0)) {while(!bit_is_set(PINC, 0)); key = 0x04;}
	if (!bit_is_set(PINC, 1)) {while(!bit_is_set(PINC, 0)); key = 0x05;}
	if (!bit_is_set(PINC, 2)) {while(!bit_is_set(PINC, 0)); key = 0x06;}
	if (!bit_is_set(PINC, 3)) {while(!bit_is_set(PINC, 0)); key = 0x07;}	
	
	//trzeci wiersz
	PORTC = 0b11011111;
	if (!bit_is_set(PINC, 0)) {while(!bit_is_set(PINC, 0)); key = 0x08;}
	if (!bit_is_set(PINC, 1)) {while(!bit_is_set(PINC, 0)); key = 0x09;}
	if (!bit_is_set(PINC, 2)) {while(!bit_is_set(PINC, 0)); key = 0x0A;}
	if (!bit_is_set(PINC, 3)) {while(!bit_is_set(PINC, 0)); key = 0x0B;}

	//czwarty wiersz
	PORTC = 0b11101111;
	if (!bit_is_set(PINC, 0)) {while(!bit_is_set(PINC, 0)); key = 0x0C;}
	if (!bit_is_set(PINC, 1)) {while(!bit_is_set(PINC, 0)); key = 0x0D;}
	if (!bit_is_set(PINC, 2)) {while(!bit_is_set(PINC, 0)); key = 0x0E;}
	if (!bit_is_set(PINC, 3)) {while(!bit_is_set(PINC, 0)); key = 0x0F;}
	
	
	// czyszczê syf
	key_init();
	return key;   //zwracam numer klawisza
}


#endif /* KLAWIATURA_H_ */