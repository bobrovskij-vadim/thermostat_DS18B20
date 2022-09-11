/*
 * EEPROM.h
 *
 * Created: 02.09.2022 14:13:46
 *  Author: vadim
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "main.h"


void EEPROM_write(unsigned int uiAddress, unsigned char ucData);           //Writing data to EEPROM;

unsigned char EEPROM_read(unsigned int uiAddress);                         //Reading data from EEPROM;

float EEPROM_float_read(unsigned int uiAddress);                           //Writing float data to EEPROM;

void EEPROM_float_write(unsigned int uiAddress, float num);                //Reading float data from EEPROM;


#endif /* EEPROM_H_ */