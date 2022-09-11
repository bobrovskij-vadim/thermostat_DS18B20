/*
 * LCD.c
 *
 * Created: 18.08.2022 13:47:01
 *  Author: vadim
 */ 

#include "LCD.h"

void LCD_ports_settings(void)       //Microcontroller ports settings which connect with the LCD; 
{
	DDRD |= (1<<PD7) | (1<<PD6) | (1<<PD5) | (1<<PD4) | (1<<PD3) | (1<<PD2);
	PORTD &= ~((1<<PD7) | (1<<PD6) | (1<<PD5) | (1<<PD4) | (1<<PD3) | (1<<PD2));	
}

void LCD_initialization(void)       //LCD initialization function;
{
	_delay_ms(15);                  //Delay after power on;
	LCD_command(0b00110000);        //Standard installation function;
	_delay_ms(5);
	LCD_command(0b00110000);        //Standard installation function;
	_delay_us(100);
	LCD_command(0b00110000);        //Standard installation function;
	_delay_ms(1);
	LCD_command(0b00000010);        //Standard installation function;
	_delay_ms(2);
	LCD_command(0b00101000);        //Display settings: 4-bit bus mode with MPU; 2-line display; Font type - Low 5x8;
	_delay_ms(1);
	LCD_command(0b00001100);        //Display ON/OFF control. Display ON; Cursor OFF; Cursor blink OFF;
	_delay_ms(1);
	LCD_command(0b00000001);        //Clear display;
	_delay_ms(2);
	LCD_command(0b00000110);        //Entry mode set. Cursor moves to right;
	_delay_ms(1);  
}

void LCD_clean(void)                //Function cleans the LCD; 
{
	LCD_command(0b00000001);        //Clear display command;
	_delay_ms(2);
}

void LCD_command(unsigned char command)      //Commands send function. 
{
	PORTD = command;
	RS_0;                            //Sending command;
	E_1;                             //Raising the potential on the enabling output;
	_delay_us(50);
	E_0;                             //Reducing the potential on the enabling output;
	PORTD = (command<<4);
	RS_0;
	E_1;
	_delay_us(50);
	E_0;
	_delay_us(50);
}

void LCD_data(unsigned char data)      //Data send function.
{
	PORTD = data;
	RS_1;                            //Sending data;
	E_1;                             //Raising the potential on the enabling output;
	_delay_us(50);
	E_0;                             //Reducing the potential on the enabling output;
	PORTD = (data<<4);
	RS_1;
	E_1;
	_delay_us(50);
	E_0;
	_delay_us(50);
}

void LCD_set_address(uint8_t line, uint8_t position)               //Setting the output position on the LCD display;
{	
	switch(line)
	{
		case 0: LCD_command(position | (1<<7)); break;             //Setting output address. The first line and position number;  
		case 1: LCD_command((position + 0x40) | (1<<7)); break;    //Setting output address. The second line and position number.
	}
}

void LCD_print_string(char str_arr[])                     //Output data to LCD;
{
	for(int i = 0; str_arr[i] != '\0'; ++i)
	{
		LCD_data(str_arr[i]);
	}
}

void LCD_show_temperature(float set_t, float cur_t)       //Function displays set temperature and actual temperature;
{                                                         //Not used 'sprintf()' function, because it uses 20% more program memory.
	LCD_clean();
	
	char temperature[6];
	LCD_set_address(0, 0);                                //Setting the output position. First line, zero position;
	LCD_print_string("Set_t: ");
	dtostrf(set_t, 2, 1, temperature);
	LCD_print_string(temperature);
	LCD_print_string(" C");
	 
	LCD_set_address(1, 0);                                //Setting the output position. Second line, zero position;
	LCD_print_string("Cur_t: ");
	dtostrf(cur_t, 2, 1, temperature);
	LCD_print_string(temperature);
	LCD_print_string(" C");
}

