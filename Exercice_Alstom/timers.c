/*
 * Timers.c
 *
 * Created: 21-04-22 21:13:19
 *  Author: Tom DUBOIS
 */ 

#include <avr/io.h>
#include "main.h"
#include "hardware.h"
#include "lcd.h"
#include "timers.h"
#include "OS.h"

void TIMER0_Init_1ms(void)
{
	// On a une fréquence d'horloge de 1MHz par defaut 
	// Utilisation du TIMER 0, comptage sur 8 bits
	// Si diviseur par 8 --> 1000000/8 = 125 Khz
	// Une periode = un coup de clock tous les 8us
	// 1 ms / 8us = 125 ==> On doit faire 125 coups de clock pour avoir 1ms
	
	//Prescaler de division par 8
	CLR_BIT(TCCR0B,CS02);
	SET_BIT(TCCR0B,CS01); 
	CLR_BIT(TCCR0B,CS00);
	
	// On va pré-remplir le compteur pour qu'il ne doive faire que 125 coup de clock --> 256 - 125 = 131
	TCNT0 = 131;
}

