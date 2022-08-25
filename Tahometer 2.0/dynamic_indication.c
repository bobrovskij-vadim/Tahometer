/*
 * dynamic_indication.c
 *
 * Created: 19.07.2022 13:23:39
 *  Author: vadim
 */ 
#include "dynamic_indication.h"

DP_1_1000 = 0; 
DP_2_100  = 0; 
DP_3_10   = 0;
DP_4_1    = 0;

segment = 0;

indication_switcher = 0; 

int digits[10] = {	0b00111111, //0
					0b00000110, //1
					0b01011011, //2
					0b01001111, //3
					0b01100110, //4
					0b01101101, //5
					0b01111101, //6
					0b00000111, //7
					0b01111111, //8
					0b01101111  //9
					};

void HC595(uint8_t pack)          //Send data function to shift register
{
	for(int i = 0; i < 8; ++i)    //Split the PACK into bits.
	{
		if(pack&(1<<i))
		{
			PORTB |= (1<<PB0);
		}
		else
		{
			PORTB &= ~(1<<PB0);
		}
		
		PORTB |= (1<<PB1);         //SH_CP - SHift register Clock input
		_delay_us(10);
		PORTB &= ~(1<<PB1);
		_delay_us(10);
	}
}


void indication(unsigned int num)  //Dividing number into segments to indicate on the display.
{
	DP_1_1000 = num / 1000;		   //thousands
	DP_2_100  = num / 100 % 10;    //hundreds
	DP_3_10   = num / 10 % 10;     //tens
	DP_4_1    = num % 10;	       //units
}

void RPM_indication(void)          //Lights up the RPM indicator.
{
	PORTD |= (1<<PD7);
	PORTD &= ~(1<<PD6);
}

void HOURS_indication(void)        //Lights up the hours indicator.
{
	PORTD |= (1<<PD6);
	PORTD &= ~(1<<PD7);
}


ISR(TIMER0_OVF_vect)                //Overflow interrupt macros.
{	
	PORTB &= ~(1<<PB3);             //Resetting the shift register.
	_delay_us(10);
	PORTB |= (1<<PB3);              //Power to shift register. 
	_delay_us(10);
	
	segment++;
	if(segment > 8) segment = 1;
	if (segment == 2)
	{
		HC595(0b11111110);           //Turning on the fourth segment.
		HC595(digits[DP_1_1000]);    //Displaying thousands	
	}
	else if (segment == 4)
	{
		HC595(0b11111101);           //Turning on the third segment.
		HC595(digits[DP_2_100]);     //Displaying hundreds.
	}
	else if (segment == 6)
	{
		HC595(0b11111011);           //Turning on the second segment.
		HC595(digits[DP_3_10]);      //Displaying tens
	}
	else if (segment == 8)
	{
		HC595(0b11110111);           //Turning on the first segment. 
		HC595(digits[DP_4_1]);       //Displaying units.
	}
	
	PORTB |= (1<<PB2);               //ST_CP Latch line. 
	_delay_us(10);
	PORTB &= ~(1<<PB2);
	_delay_us(10);	
}

void port_settings(void)   //Enable and configure interrupts.
{
	//Ports settings for digit indication.
	DDRB |= (1<<PB3) | (1<<PB2) | (1<<PB1) | (1<<PB0);      //Setting ports to exit
	PORTB &= ~((1<<PB2) | (1<<PB1) | (1<<PB0));             //Setting ports to zero
	
	//Ports settings for indication switcher.
	DDRD  |= (1<<PD6) | (1<<PD7);                            //Setting ports to exit
	PORTD &= ~((1<<PD6) | (1<<PD7));						 //Setting ports to zero
	

}
