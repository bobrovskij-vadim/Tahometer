/*
 * EEPROM.h
 *
 * Created: 28.07.2022 16:36:42
 *  Author: vadim
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "main.h"

void EEPROM_write(unsigned int uiAddress, unsigned char ucData);           //Writing data to EEPROM.

unsigned char EEPROM_read(unsigned int uiAddress);                         //Reading data from EEPROM.

void EEPROM_write_two_bytes(unsigned int uiAddress, unsigned int ucData);  //Writing two bytes data to EEPROM. First byte writes to uiAddress, second byte to uiAdderess + 1.

unsigned int EEPROM_read_two_bytes(unsigned int uiADdress);                //Reads two bytes data from EEPROM. First byte reads from uiAddress, second byte from uiAdderess + 1

#endif /* EEPROM_H_ */