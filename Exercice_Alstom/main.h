/*
 * main.h
 *
 * Created: 21-04-22 20:42:10
 *  Author: Tom DUBOIS
 */ 


#ifndef MAIN_H_
#define MAIN_H_

// DEFINES
#define FALSE	0
#define TRUE	1
#define SET_BIT(port,bit)  (port |= (1<<bit))   //Set bit dans le port 
#define CLR_BIT(port,bit)  (port &= ~(1<<bit))  //Clear bit dans le port 
#define TOGGLE_IO(port,bit) (port ^= (1<<bit))   //Toggle bit dans le port





#endif /* MAIN_H_ */