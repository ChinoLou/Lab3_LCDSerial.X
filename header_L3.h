
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef HEADER_L3_H
#define	HEADER_L3_H
#define _XTAL_FREQ 4000000
#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>
void LCD_DATO(int var);
void LCD_iniciar(void);
void LCD_CLEAR(void);
void LCD_CURSOR(int a, int b);
void LCD_CHAR(char a);
void LCD_STRING(char *a);

void conf(void);
//void Freq_Osc(char op);

#endif	/* XC_HEADER_TEMPLATE_H */

