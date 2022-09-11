/*
 * temperature_control.h
 *
 * Created: 31.08.2022 13:46:17
 *  Author: vadim
 */ 


#ifndef TEMPERATURE_CONTROL_H_
#define TEMPERATURE_CONTROL_H_

#include "main.h"

void t_control_ports_settings(void);                       //Function for port settings to control the temperature;

void temperature_controller(float set_t, float cur_t);     //Function controls heating and cooling; 

#endif /* TEMPERATURE_CONTROL_H_ */