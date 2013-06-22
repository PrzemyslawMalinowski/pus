/*
 * lcd.h
 *
 * Created: 2013-06-22 15:27:21
 *  Author: Bagieta
 */ 


#ifndef LCD_H_
#define LCD_H_


void SetDisplay(int myPos, int obstaclex,int obstacley);
void wyslijNapis(char* text);
void wyslijLine2(char* text, char* text2);
void initLCD();


#endif /* LCD_H_ */