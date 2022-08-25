#include "main.h"

unsigned int interrupt_counter = 0;                    //TCNT1 interrupt counter.
unsigned long total_interrupts = 0;                    //Amount of TCNT1 interrupts per one INT0 interrupt.                      
int RPM_counter_100 = 0;                               //One hundred INT0 interrupts.
double average_RPM  = 0;                               //

const int RPM = 60;                                    //Revolutions per minute
const int N_SL = 2;                                    //Number of slots

volatile unsigned int seconds = 0;                     //Volatile is a keyword that informs the compiler 
volatile unsigned int minutes = 0;                     //that the value of a variable can change from outside 
volatile unsigned int hours   = 0;                     //and that the compiler will not optimize this variable.

unsigned int memory_register  = 0;                     //Holds number last used EEPROM register.                    
unsigned int last_record      = 0;                     //Recorded time to continue counting moto-hours.



ISR(INT0_vect)										   //External Interrupt INT0.  
{
	total_interrupts += (TCNT1 + interrupt_counter * 65536);
	TCNT1 = 0;
	interrupt_counter = 0; 
	RPM_counter_100++;
	if(RPM_counter_100 >= 100)
	{
		average_RPM = (float)total_interrupts / RPM_counter_100;
		total_interrupts = 0;
		RPM_counter_100 = 0;
	}
}

ISR(TIMER1_OVF_vect)                                   //Overflow interrupts for TCNT1.
{
	interrupt_counter++;
}

ISR(TIMER2_OVF_vect)                                   //Overflow interrupts for TCNT2. 
{
#ifdef DEMO_MODE
	
	if(++seconds > 1000)
	{
		seconds = 0;
	}
	EEPROM_write_two_bytes(last_record, seconds);
	
#else
	
	if(++seconds > 59)
	{
		seconds = 0;
		++minutes;
		EEPROM_write(last_record, minutes);
	}
	if(minutes > 59)
	{
		minutes = 0;
		++hours;
		EEPROM_write(last_record, minutes);
		EEPROM_write_two_bytes(last_record + 1, hours);
	}
	if(hours > 9999)
	{
		hours = 0;
		EEPROM_write(last_record, minutes);
		EEPROM_write_two_bytes(last_record + 1, hours);	
	}
	
#endif
}

int main(void)
{		
	port_settings();					   //Ports configuration for dynamic indication.
	
	dynamic_indication_interrupts();       //Switching on interrupts for the dynamic indication.
	
	frequency_counter_interrupts();        //Switching on interrupts for the frequency counter.
	
	external_interrupts_enable();          //Switching on external interrupts for INT0.
	
	hours_counter_interrupts();            //Asynchronous operation of TCNT2.
	
	all_interrupts_enabled();              //Switching on all interrupts.
	
	buttons_ports_settings();              //Setting PD3 and PD4 for buttons.
	
	
#ifdef DEMO_MODE

	last_record = EEPROM_read_two_bytes(memory_register);
	seconds = EEPROM_read_two_bytes(last_record); 
	if (++last_record >= 509 && last_record <= 1)
	{
		last_record = 2;
	}
	EEPROM_write_two_bytes(memory_register, last_record);
	EEPROM_write_two_bytes(last_record, seconds);
	
#else

	last_record = EEPROM_read_two_bytes(memory_register);
	minutes = EEPROM_read(last_record);
	hours = EEPROM_read_two_bytes(last_record + 1);
	if (++last_record >= 509 && last_record <= 1)
	{
		last_record = 2;
	}
	EEPROM_write_two_bytes(memory_register, last_record);
	EEPROM_write(last_record, minutes);
	EEPROM_write_two_bytes(last_record + 1, hours);
	
#endif
	
	while (1)
	{
		if(indication_switcher)            //Displays RPM.
		{
			indication((float)F_CPU / average_RPM * RPM / N_SL);	
			RPM_indication();
		}
		else if(!indication_switcher)      //Displays moto-hours.
		{
			
#ifdef DEMO_MODE
			indication(seconds);
#else
			indication(hours);
#endif
			HOURS_indication();
		}
	
		
		if(~PIND & (1<<PD3))               //PD3 button pressed. RPM/HOURS switcher. 
		{
			while(~PIND & (1<<PD3))        //Contact bounce
			;
			indication_switcher = ~indication_switcher;
		}
		
		if(~PIND & (1<<PD4))               //PD4 button pressed. Resetting the moto-hours counter.
		{
			while(~PIND & (1<<PD4))        //Contact bounce
			;
			
#ifdef DEMO_MODE
			seconds = 0;
			EEPROM_write_two_bytes(last_record, minutes);
#else
			minutes = 0;
			hours = 0;
			EEPROM_write(last_record, minutes);
			EEPROM_write_two_bytes(last_record + 1, hours);
#endif		
		}
	}
}
