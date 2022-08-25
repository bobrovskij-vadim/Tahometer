/*
 * buttons.c
 *
 * Created: 27.07.2022 11:57:21
 *  Author: vadim
 */ 
#include "buttons.h"

void buttons_ports_settings(void)
{
	//Settings for HOUR/RPM switcher. PORT PD3
	DDRD &= ~(1<<PD3);
	PORTD |= (1<<PD3);
	
	//Settings for resetting the moto-hours counter. PD4
	DDRD &= ~(1<<PD4);
	PORTD |= (1<<PD4);
}