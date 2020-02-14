/*
 * File:   Funciones.c
 * Author: Andres Sierra
 *
 * Created on 5 de febrero de 2020, 01:07 PM
 */
#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 4000000
#include "header_L3.h"



void conf(void){
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
    /*INTCONbits.T0IE =1;
    INTCONbits.T0IF =1;*/
    
    //PIE1bits.ADIE = 1;      // HABILITA INTERRUPCION DE ADC
    //PIR1bits.ADIF = 0;      // BANDERA DE A/D  
    ADCON0bits.ADON = 1;      // HABILITA ADC
    __delay_ms(20);
    ADCON0bits.GO_DONE = 1;   // EMPEZAR LA CONVERCION A/D
   }

// ------------ Configuracion de la Frecuencia del Oscilador ------------------

