/*
 * OS.c
 *
 * Created: 21-04-22 20:43:01
 *  Author: Tom DUBOIS
 */ 

#include <avr/io.h>
#include "main.h"
#include "hardware.h"
#include "lcd.h"
#include "timers.h"
#include "OS.h"
#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include "avr/interrupt.h"

int nombre;
uint8_t volatile etape1; // variable bol qui active l'etape 1
uint8_t volatile etape2; // variable bol qui active l'etape 2
uint8_t volatile etape3; // variable bol qui active l'etape 3
uint16_t resultat_joueur; // Temps en ms que le joueur aura fait en appuyant sur le bouton
uint32_t timing; //timer en ms
uint16_t nombre_random1; //nombre de ms d'attente avant que la LED s'allume aleatoire
uint16_t nombre_random2; //nombre de ms d'activation de la LED  aleatoire
int16_t delta; // Difference entre le temps du joueur et de la LED
char buffer[10]; //buffer pour y stocker des characteres qui seront genere par la fonction itoa() pour afficher des entiers sur le LCD



void loop_OS() // Boucle infninie
{
	while (1)
	{	
		SET_BIT(TIMSK0,TOIE0); //activation du timer pour pouvoir generer un nombre a chaque fois different a la focntion srand()
		lcd_clrscr(); // effacement de ce qui est affiche sur le LCD
		lcd_puts("Appuyez pour"); // affichage du texte sur le LCD
		lcd_gotoxy(0,1); // commencer a la position (x,y) sur le LCD
		lcd_puts("commencer"); // affichage du texte sur le LCD
		etape1 = TRUE; // activation de l'etape 1, pour uniquement rentrer dans la condition 1 dans l'ISR lors de l'interrutpion du bouton
		while (etape1 == TRUE); // Periode d'attente du premier appuis du bouton
		lcd_clrscr();
		lcd_puts("...");	
		srand(timing); // definition d'un "seed" pour ne pas generer a chaque fois les mêmes nombre par la fonction rand()
		CLR_BIT(TIMSK0,TOIE0); // desactivation du timer
		nombre = rand() % (MAX1 + 1); // generation d'un nombre aleatoire, en lui imposant un nombre maximal defini grace a une loi mathematique du modulo
		nombre_random1 = MIN1 + nombre; // ajout d'une valeur minimum de temps a cette valeur 
		my_delay_ms(nombre_random1); // delay en ms
		nombre = rand() % (MAX2 + 1);
		nombre_random2 = MIN2 + nombre;
		SET_BIT(PORTD,PD7); // activation de la LED
		my_delay_ms(nombre_random2);
		CLR_BIT(PORTD,PD7); //desactivation de la LED
		lcd_clrscr();
		lcd_puts("A toi de jouer !");
		etape2 = TRUE; // activation de l'etape 2, pour uniquement rentrer dans la condition 2 dans l'ISR lors de l'interrutpion du bouton
		while(etape2 == TRUE); // Periode d'attente du deuxieme appuis du bouton
		etape3 = TRUE; // activation de l'etape 3, pour uniquement rentrer dans la condition 3 dans l'ISR lors de l'interrutpion du bouton
		while(etape3 == TRUE); //Periode d'attente de l'enlevement du doigt du bouton
		resultat_joueur = timing; // Definition du resultat grâce au timing encode
		delta = nombre_random2 - resultat_joueur; // Delta entre le temps réel et celui appuye par le joueur
		lcd_clrscr();
		lcd_puts("Resultat :");
		lcd_gotoxy(0,1);
		itoa(delta,buffer,10);
		lcd_puts(buffer);
 		lcd_gotoxy(5,1);
 		lcd_puts("ms");
		_delay_ms(2500);
	}
}

void my_delay_ms(uint16_t ms) // Fonction de delay pour entrer une variable en paramètre
{
	while (0 < ms)
	{
		_delay_ms(1);
		--ms;
	}
}

ISR(TIMER0_OVF_vect) // Interruption d'overflow du timer0
{
	timing++; // +1 à chaque ms
	TCNT0 = 131; // on re-rempli de timer à 131 
}

ISR(INT0_vect)
{
	if (etape1 == TRUE)
	{
		etape1 = 0; // desactivation de l'etape 1, pour que la condition de la boucle while ne soit plus verifiee

	}
	if (etape2 == TRUE)
	{
		SET_BIT(EICRA,ISC00); // re-definition du parametre de l'interruption, pour le faire reagir lors dans flancs montants et non plus sur les descendnants, pour le relachement du bouton
		timing = 0; // Reinitiation du timing
		SET_BIT(TIMSK0,TOIE0); // activation du timer 
		SET_BIT(PORTD,PD7); // activation de la LED
		etape2 = FALSE; // desactivation de l'etape 2, pour que la condition de la boucle while ne soit plus verifiee
	}
	if (etape3 == TRUE)
	{
		CLR_BIT(EICRA,ISC00); // re-definition du parametre de l'interruption, pour le faire reagir lors dans flancs descendants
		CLR_BIT(TIMSK0,TOIE0); //desactivation du timer
		CLR_BIT(PORTD,PORTD7); // desactivation de la LED
		etape3 = FALSE; // desactivation de l'etape 3, pour que la condition de la boucle while ne soit plus verifiee
	}
}