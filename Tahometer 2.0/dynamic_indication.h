/*
 * dynamic_indication.h
 * Switch on and set up dynamic indication.
 *
 * Used:
 *		Port B (0,1,2,3), D (6, 7);
 *		Shift registers (74HC595) - 2 units;
 *		Seven segments display (7SEG-MPZ1-CC);
 *      Resistor 300 Om - 10 units
 *
 *
 * Created: 19.07.2022 13:22:39
 *  Author: vadim
 */ 


#ifndef DYNAMIC_INDICATION_H_
#define DYNAMIC_INDICATION_H_

#include "main.h"

int DP_1_1000, DP_2_100, DP_3_10, DP_4_1;      //Position to seven segments display.

int indication_switcher;

int segment;

int digits[10];                                //Array of digits in binary view.

void HC595(uint8_t pack);                      //Send data function to shift register.

void indication(unsigned int num);             //Dividing number to discharges to indicate on the display.

void RPM_indication(void);                     //Lights up the RPM indicator.

void HOURS_indication(void);				   //Lights up the hours indicator.

void port_settings(void);                      //Ports configuration.

ISR(TIMER0_OVF_vect);                          //Overflow interrupt macros.





#endif /* DYNAMIC_INDICATION_H_ */