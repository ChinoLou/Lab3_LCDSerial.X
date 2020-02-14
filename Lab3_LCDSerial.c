/*
 * File:   LAB3_LCD_USART.c
 * Author: Josue Castillo Lou
 * Carné:  17169
 * LAB3: Uso de LCD con Librería y USART_PC
 * Created on 6 de febrero de 2020, 11:43 PM
 */

#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// -------- PUERTOS DE LA LCD -----------------
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

//-------- Librerías a utilizar ---------------// 
#include <xc.h>
#include <stdint.h>
#include <stdio.h>

#define _XTAL_FREQ 4000000      // 4MHz
#include "header_L3.h"

//------- Definición de Variables Globales ----// 
int     Pots;
char    Cont;
char    comp;
float   Volt_uno;
float   Volt_dos;
char    lcd_valor[16];

// Prototipos de Funciones 
void config_PORTS(void);
void config_Serial(void);


//************************ Programa Principal **********************************

void main(void) {
    config_PORTS();
    Cont = 0;
    config_Serial();
   
    LCD_iniciar();
    LCD_CLEAR();
    LCD_CURSOR(1,1);
    LCD_STRING ("POT1   POT2  TTL");
    
    PIE1bits.RCIE = 1;      //USART
    PIR1bits.RCIF = 0;
    
    while(1){
        ADCON0bits.ADCS1 = 1;   // fosc/32
        ADCON0bits.ADCS0 = 0;  
        
        ADCON0bits.CHS3 = 0;    // Seleccion canal analogica AN0
        ADCON0bits.CHS2 = 0;   
        ADCON0bits.CHS1 = 0;   
        ADCON0bits.CHS0 = 0;   
        
        PIR1bits.ADIF = 0;      //Reseteamos la bandera del ADC     
        ADCON0bits.GO = 1;      // Enable convertion
        
        Volt_uno = (5.0*ADRESH)/255.0;
        Pots = ADRESH;
                
        __delay_us(600);        //DELAY! IMPORTANTE PARA PODER HACER EL CAMBIO DE CANAL
        
        ADCON0bits.CHS3 = 0;    // Seleccion canal analogica AN1
        ADCON0bits.CHS2 = 0;   
        ADCON0bits.CHS1 = 0;   
        ADCON0bits.CHS0 = 1;   
        
        PIR1bits.ADIF = 0;      //Reseteamos la bandera del ADC
        ADCON0bits.GO = 1;
        
        Volt_dos = (5.0*ADRESH)/255.0;
     
        __delay_us(600);        //DELAY! IMPORTANTE PARA PODER HACER EL CAMBIO DE CANAL
        
        sprintf(lcd_valor, "%.2fV  %.2fV %d", Volt_uno, Volt_dos, Cont);
        LCD_CURSOR(2,1);
        LCD_STRING(lcd_valor);
        
        __delay_us(600);
        
        TXREG = ADRESH;
        while (PIR1bits.TXIF == 0){   
        }
        
        TXREG = Pots;
        while (PIR1bits.TXIF ==0){  
        }

     
        comp = RCREG;
        if (comp == 43){
            Cont++; 
        
        }
        
        if (RCREG == 45){
            Cont--; 
        
        }
       
    
    }
  
    return;
}


void config_PORTS(void){
    PORTA = 0;          
    PORTB = 0;
    PORTC = 0;  
    PORTD = 0;
    
    TRISA = 0b00000011; 
    TRISB = 0; 
    TRISC = 0; 
    TRISD = 0;
    ANSEL = 0b00000011;     // RA0 RA1 ENTRADAS ANALOGICAS
    ANSELH = 0;            // TODAS LAS ENTRADAS DIGITALES
    
 
    ADCON1 = 0;
    INTCONbits.PEIE =1;     // HABILITA INTERRUPCIONES 
    ADCON0bits.ADON = 1;      // HABILITA ADC
    __delay_ms(20);
    ADCON0bits.GO_DONE = 1;   // EMPEZAR LA CONVERCION A/D
   }

void config_Serial(void){
     //////////////////// serial  
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;
    TXSTAbits.TXEN = 1;
    
    BAUDCTLbits.BRG16 = 1;
    SPBRG = 103;
    SPBRGH = 0;
    
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9  = 0;
    RCSTAbits.CREN = 1;
    ///////////////////
}