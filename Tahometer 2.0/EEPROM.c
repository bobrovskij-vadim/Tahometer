/*
 * EEPROM.c
 *
 * Created: 28.07.2022 16:36:56
 *  Author: vadim
 */ 

#include "EEPROM.h"

void EEPROM_write(unsigned int uiAddress, unsigned char ucData)  //Writing data to EEPROM.
{
	while(EECR & (1<<EEWE))         //Wait for completion of previous write
	;
	EEAR = uiAddress;               //Set up address
	EEDR = ucData;                  //and data registers.
	EECR |= (1<<EEMWE);             //Write logical one to EEMWE.
	EECR |= (1<<EEWE);              //Start EEPROM write by setting EEWE.
}

unsigned char EEPROM_read(unsigned int uiAddress)             //Reading data to EEPROM.
{
	while(EECR & (1<<EEWE))          //Wait for completion of previous write.
	;
	EEAR = uiAddress;                //Set up address register.
	EECR |= (1<<EERE);               //Start EEPROM read by writing EERE.
	return EEDR;                     //Return data from data register.
}

void EEPROM_write_two_bytes(unsigned int uiAddress, unsigned int ucData)   //Writing two bytes data to EEPROM.
{
	int first_half = ucData >> 8;
	EEPROM_write(uiAddress, first_half);
	EEPROM_write(uiAddress + 1, ucData);
}

unsigned int EEPROM_read_two_bytes(unsigned int uiADdress)                 //Reads two bytes data from EEPROM.
{
	return (EEPROM_read(uiADdress) << 8) + EEPROM_read(uiADdress + 1);
}