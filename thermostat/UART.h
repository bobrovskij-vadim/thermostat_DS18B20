/*
 * UART.h
 *
 * Created: 24.08.2022 12:49:45
 *  Author: vadim
 */ 


#ifndef UART_H_
#define UART_H_

#include "main.h"


void UART_settings(unsigned int ubrr);                    //The UART initialization function;

void UART_transmit(unsigned char data);                   //Data Transmission function. Sending Frames with 5 to 8 data bits;

void UART_print_string(char *str);                        //Function prints sent char array;         

unsigned char UART_receive(void);                         //Data Receiving function;

float UART_set_temperature();                             //Setting temperature function;

void UART_get_temperature(float set_t, float cur_t);      //Function returns temperature from sensor to UART; 

char UART_menu();                                         //Menu temperature controlling;


#endif /* UART_H_ */