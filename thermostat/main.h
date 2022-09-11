/*
 * main.h
 *
 * Created: 18.08.2022 13:07:34
 *  Author: vadim
 *
 *	Thermostat
 *
 *	Application area:
 *		Apartments;
 *		House;
 *		Greenhouse;
 *		Growbox;
 *		Other places where distantionaly temperature controlling could be useful;
 *
 *	Used technologies:
 *		C, 1-Wire, UART, EEPROM;
 *
 *	Used equipment:
 *		Microcontroller - microchip AVR ATMEGA8 DIP-28 pins - 1 unit;
 *		Temperature sensor Dallas/Maxim DS18B20 - 1 unit;
 *		LCD LM016L - 1 unit;
 *		Led-GREEN - 1 unit;
 *		Led-YELLOW - 1 unit;
 *		Led-BLUE - 1 unit;
 *		Resistor 300 Om - 3 units;
 *		Resistor 4k7 Om - 1 unit;
 *
 *	Ports:
 *		PD(0, 1) - UART;
 *		PD(2, 3, 4, 5, 6, 7) - LCD;
 *		PC(0) - 1-WIRE;
 *		PB(0, 1, 2) - Temperature controller;
 *
 *	Interrupts/Timer counters:
 * 		First 16 bytes timer counter:
 *			Temperature controller;
 *			Getting temperature from sensor;
 *			Printing data on the LCD;
 */ 

#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "LCD.h"
#include "DS18B20.h"
#include "UART.h"
#include "interrupt.h"
#include "EEPROM.h"
#include "temperature_control.h"

#endif /* MAIN_H_ */