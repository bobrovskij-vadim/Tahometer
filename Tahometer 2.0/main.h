/*
 * Tachometer.c
 *
 *	Tachometer with a moto hours counter. 
 *
 *	Application area:
 *		Outboard motors;
 *		Moto technique;
 *		Petrol tools.
 *
 *  Used equipment: 
 *		Microcontroller - microchip AVR ATMEGA8 DIP-28 pins - 1 unit;
 *		Shift registers (74HC595) - 2 units;
 *		Seven segments display (7SEG-MPZ1-CC) - 1 unit;
 *      Resistor 300 Om - 10 units;
 *		Led-GREEN - 1 unit;
 *		Led-YELLOW - 1 unit;
 *		Button - 3 units; 
 *		Quartz resonator 1MHz - 1 unit;
 *		Capacitor 12pF - 2 units.
 *
 *  Ports: 
 *		PB (0,1,2,3) PD (6,7) - dynamic indication;
 *		PC6 - Reset button;
 *		PD3 - HOURS/RPM Switcher button;
 *		PD4 - Reset hours counter button;
 *		PD2 - External frequency generator INT0;
 *		PB (6,7) - External quartz resonator.
 *
 *  Interrupts/Timer counters:
 *		TCNT0 - Dynamic indication. Overflow interrupts. Frequency divider is 8.
 *		TCNT1 - Frequency generator. External interrupts for INT0. No prescaling.
 *		TCNT2 - MOTO-HOURS counter. Asynchronous operation. Frequency divider is 128.
 *
 * Created: 18.07.2022 11:56:28
 * Author : Vadym Bobrovskyi
 */ 


#ifndef MAIN_H_
#define MAIN_H_

//#define DEMO_MODE    //Demo mode. The Moto-hours counter works in accelerated mode (1 second = 1 hour).

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "dynamic_indication.h"
#include "interrupts.h"
#include "buttons.h"
#include "EEPROM.h"


#endif /* M_ */