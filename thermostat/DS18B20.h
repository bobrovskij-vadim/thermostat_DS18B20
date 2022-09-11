/*
 * DS18B20.h
 *
 * Created: 22.08.2022 12:43:39
 *  Author: vadim
 */ 


#ifndef DS18B20_H_
#define DS18B20_H_

#include "main.h"

bool DS18B20_check(void);                          //Function checks availability temperature sensor on the line;

void DS18B20_command_to_sensor(char data);         //Function sends data and commands (size 1 byte) to the temperature sensor;

int DS18B20_read_from_sensor(void);                //Function reads data (1 byte) from the sensor;

int DS18B20_temper_in_bytes(void);                 //Function gets the temperature from the sensor in bytes;

double DS18B20_get_temperature(void);              //Function returns the temperature from the sensor in decimal value; 

#endif /* DS18B20_H_ */