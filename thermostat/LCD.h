/*
 * LCD.h
 *
 * Created: 18.08.2022 13:46:48
 *  Author: vadim
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "main.h"

#define RS_1 PORTD |= (1<<PD2)                         //Sending data to LCD;
#define RS_0 PORTD &= ~(1<<PD2)                        //Sending commands to LSD;

#define E_1 PORTD |= (1<<PD3)                          //Raising the potential on the enabling output;
#define E_0 PORTD &= ~(1<<PD3)                         //Reducing the potential on the enabling output;


void LCD_ports_settings(void);                         //Microcontroller ports settings which connect with the LCD; 

void LCD_initialization(void);                         //LCD initialization function;

void LCD_clean(void);                                  //Function cleans the LCD; 

void LCD_command(unsigned char command);               //Commands send function; 

void LCD_data(unsigned char data);                     //Datas send function;

void LCD_set_address(uint8_t line, uint8_t position);  //Setting the output position on the LCD display;
   
void LCD_print_string(char str_arr[]);                 //Output data to LCD;

void LCD_show_temperature(float set_t, float cur_t);   //Function displays set temperature and actual temperature;

#endif /* LCD_H_ */