/*
 * EEPROM.c
 *
 * Created: 02.09.2022 14:13:59
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

float EEPROM_float_read(unsigned int uiAddress)                //Writing float data to EEPROM;

{
	char arr[4];
	for(char i = 0; i < 4; i++) 
	{
		arr[i] = EEPROM_read(i + uiAddress);
	}
	float *num = (float *)&arr;
	return num[0];
}

void EEPROM_float_write(unsigned int uiAddress, float num)     //Writing float data to EEPROM;
{
	char *arr = (char *)&num;
	for(char i = 0; i < 4; i++) 
	{
		EEPROM_write(i + uiAddress, arr[i]);	
	}
}

