/*
 * Exercice_Alstom.c
 *
 * Created: 21-04-22 20:41:41
 * Author : Tom DUBOIS
 */ 

////////////////////////////////////////////////////////
///////// EXERCICE ALSTOM SUR AVR ATMEGA1284P /////////
//////////////////////////////////////////////////////

#include <avr/io.h>
#include "main.h"
#include "hardware.h"
#include "lcd.h"
#include "timers.h"
#include "OS.h"

int main(void)
{
	TIMER0_Init_1ms(); //initiation du timer compteur
	hardware_init(); // initiation de l'hardware
	lcd_init(LCD_DISP_ON); // initiation du LCD
	loop_OS(); // Entree dans la boucle infinie
}

