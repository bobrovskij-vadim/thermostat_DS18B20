/*
 * temperature_control.c
 *
 * Created: 31.08.2022 13:46:30
 *  Author: vadim
 */ 

#include "temperature_control.h"

void t_control_ports_settings(void)                       //Function for port settings to control the temperature;
{
	DDRB |= (1<<PB2) | (1<<PB1) | (1<<PB0);
	PORTB &= ~((1<<PB2) | (1<<PB1) | (1<<PB0));	
}

void temperature_controller(float set_t, float cur_t)     //Function controls heating and cooling;
{
	if (cur_t < set_t)                                    //Turning on heating;
	{
		PORTB &= ~((1<<PB2) | (1<<PB1));	
		PORTB |= (1<<PB0);
	}
	else if (cur_t > set_t)                               //Turning on cooling;
	{
		PORTB &= ~((1<<PB1) | (1<<PB0));	
		PORTB |= (1<<PB2);
	}
	else 
	{
		PORTB &= ~((1<<PB2) | (1<<PB0));	
		PORTB |= (1<<PB1);
	}
}