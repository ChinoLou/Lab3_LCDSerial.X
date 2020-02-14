/*
 * File:   Lib_LCD.c
 * Author: Andres Sierra
 *
 * Created on 8 de febrero de 2020, 08:52 PM
 */

#define RS RA3
#define EN RA4
#define D0 RD0
#define D1 RD1
#define D2 RD2
#define D3 RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
#define puerto PORTD
#define _XTAL_FREQ 4000000
#include <stdint.h>
#include <xc.h>
#include "header_L3.h"


void LCD_iniciar(void){
    __delay_ms(20);
    LCD_DATO(0x30);
    __delay_ms(5);
    LCD_DATO(0x30);
    __delay_us(100);
    LCD_DATO(0x30);
    __delay_us(100);
    LCD_DATO(0x38);
    __delay_us(53);
    LCD_DATO(0x08);
    __delay_us(53);
    LCD_DATO(0x01);
    __delay_ms(4);
    LCD_DATO(0x06);
    __delay_us(53);
    LCD_DATO(0x0C);
    __delay_us(53);
}

void LCD_DATO(int var){
    RS = 0;
    __delay_ms(5);
    EN = 1;
    puerto = var;
    __delay_ms(5);
    EN = 0;
    __delay_ms(5);
}

void LCD_CLEAR(void){
    LCD_DATO(0x00);
    LCD_DATO(0x01);
    __delay_ms(5);
}
    

void LCD_CURSOR(int a, int b)
{
    int d;
	if(a == 1)
	{
        d = 0x80 + b - 1;
		LCD_DATO(d);
	}
	else if(a == 2)
	{
		d = 0xC0 + b - 1;
		LCD_DATO(d);
	}
}



void LCD_CHAR(char a)
{   
    RS = 1;
    // LCD_Port(caracter);
    PORTD = a;
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void LCD_STRING(char *a)
{
    int n;
    for(n = 0; a[n] != '\0'; n++){
        LCD_CHAR(a[n]);
    }
}
                  