/*
 * interrupts.h
 *
 * Switching on and setting interrupts configuration.
 *		Dynamic indication interrupts - Timer counter TCNT0.
 *		Frequency interrupts - Timer counter TCNT1.
 *		External interrupts - PORT INT0.
 *
 * Created: 21.07.2022 12:34:01
 *  Author: vadim
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "main.h"

void dynamic_indication_interrupts(void);    //Interrupts settings for dynamic indication.

void frequency_counter_interrupts(void);     //Interrupts settings for frequency counter.

void external_interrupts_enable(void);       //External interrupts for INT0.

void hours_counter_interrupts(void);         //Asynchronous operation of TCNT2

void all_interrupts_enabled(void);           //Enabling all interrupts. 
      



#endif /* INTERRUPTS_H_ */