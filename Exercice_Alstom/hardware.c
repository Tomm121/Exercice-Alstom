/*
 * hardware.c
 *
 * Created: 21-04-22 21:26:42
 *  Author: Tom DUBOIS
 */ 

#include <avr/io.h>
#include "main.h"
#include "avr/interrupt.h"

void hardware_init()
{
	// Configuration des pins en entrées ou en sorties (1 = sortie / 0 = entree)
	SET_BIT(DDRD,DDD7); // LED
	CLR_BIT(DDRD,DDD2); // Bouton poussoir
	
	
	//Pull-up sur le bouton
	SET_BIT(PORTD,PORTD2); //Bouton poussoir
	
	
	//Configuration des interruptions
	SET_BIT(EICRA,ISC01); // flancs descendants 
	CLR_BIT(EICRA,ISC00); // flancs descendants 
	SET_BIT(EIMSK,INT0); // activer INT0
	sei(); // autorise les interruptions globales
}
