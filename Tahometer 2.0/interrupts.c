/*
 * interrupts.c
 *
 * Created: 21.07.2022 12:34:18
 *  Author: vadim
 */ 

#include "interrupts.h"

void dynamic_indication_interrupts(void)
{
	//Dynamic indication
	TCCR0 |= (1<<CS01);					   //Timer/counter control register. Frequency divider is 8.
	TIMSK |= (1<<TOIE0);				   //Timer/Counter interrupt mask register. Overflow Interrupt Enable
	TCNT0 = 0;							   //Setting the timer counter into zero.
}

void frequency_counter_interrupts(void)
{
	TCCR1B |= (1<<CS10);                   //Start the first timer counter with (No prescaling).
	TIMSK  |= (1<<TOIE1);                  //Timer/Counter1, Overflow Interrupt Enable.
	TCNT1  = 0;                            //Setting the first timer counter into zero.
}

void external_interrupts_enable(void)
{
	MCUCR |= (1<<ISC01);                   //The falling edge of INT0 generates an interrupt request.
	GICR  |= (1<<INT0);                    //External Interrupt Request 0 Enable.
}

void hours_counter_interrupts(void)
{
	ASSR  |= (1<<AS2);                     //Asynchronous Timer/Counter2 enabled.
	TCNT2 = 0;                             //Setting the second timer counter into zero.
	TCCR2 |= (1<<CS22) | (1<<CS20);        //Timer/counter control register. Frequency divider is 128.
	TIMSK |= (1<<TOIE2);                   //Timer/Counter2 Overflow Interrupt Enable.
}

void all_interrupts_enabled(void)
{
	SREG |= (1<<INT1);                     //Status Register. External Interrupt Request Enable.
}