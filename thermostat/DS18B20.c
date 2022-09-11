/*
 * DS18B20.c
 *
 * Created: 22.08.2022 12:43:54
 *  Author: vadim
 */ 

#include "DS18B20.h"


bool DS18B20_check(void)                    //Function checks availability temperature sensor on the line;
{
	cli();                                  //Disabling all interrupts;
	bool exist = false;
	DDRC |= (1<<PC0);                       //Setting the PC1 to exit; 
	PORTC &= ~(1<<PC0);                     //Occupy the data line;
	_delay_us(500);
	DDRC &= ~(1<<PC0);                      //Release the data line;
	_delay_us(120);
	if(~PINC & (1<<PC0))                    //Checking the sensor presetting on the line;
	{
		exist = true;
	}
	sei();                                  //Enabling interrupts; 
	_delay_us(380);                         //Waiting for completing the time slot;
	return exist;
}

void DS18B20_command_to_sensor(char data_byte)   //Function sends data and commands (size 1 byte) to the temperature sensor;
{	
	for(int i = 0; i < 8; ++i)
	{
		if(data_byte & (1<<i))
		{
			cli();                           //Disabling all interrupts;
			DDRC |= (1<<PC0);                //Setting the PC1 to exit; 
			PORTC &= ~(1<<PC0);              //Occupy the data line;
			_delay_us(2);                    //Creating logical "1";
			DDRC &= ~(1<<PC0);               //Release the data line;
			_delay_us(58);                   //Waiting for completing the time slot;
			sei();                           //Enabling interrupts; 
		} 
		else
		{
			cli();                           //Disabling all interrupts;
			DDRC |= (1<<PC0);                //Setting the PC1 to exit;
			PORTC &= ~(1<<PC0);              //Occupy the data line;
			_delay_us(65);                   //Creating logical "0";
			DDRC &= ~(1<<PC0);               //Release the data line;
			sei();                           //Enabling interrupts; 
		}
	}
}

int DS18B20_read_from_sensor(void)           //Function reads data (1 byte) from the sensor;
{		
	int data_byte = 0;
	for(int i = 0; i < 8; ++i)
	{
		cli();                               //Disabling all interrupts;
		DDRC |= (1<<PC0);                    //Setting the PC1 to exit;
		_delay_us(2);
		DDRC &= ~(1<<PC0);	                 //Release the data line;
		_delay_us(13);
		
		if(PINC & (1<<PC0))
		{
			data_byte |= (1<<i);             //Assign "1";
		}
		else
		{
			data_byte &= ~(1<<i);            //Assign "0";
		}
		_delay_us(45);
		sei();                               //Enabling interrupts; 
	}
	return data_byte;
}

int DS18B20_temper_in_bytes(void)            //Function gets the temperature from the sensor in bytes;
{		
	unsigned int temper_in_bytes = 0;
	if(DS18B20_check())                      //Checking the sensor presetting on the line;
	{
		DS18B20_command_to_sensor(0xCC);     //ROM Commands: Skip ROM;
		DS18B20_command_to_sensor(0x44);     //ROM Commands: Convert temperature;
		_delay_ms(750);                      //Time to convert temperature. Using 12 bit data;
		DS18B20_check();                     //Checking the sensor presetting on the line;
		DS18B20_command_to_sensor(0xCC);     //ROM Commands: Skip ROM;
		DS18B20_command_to_sensor(0xBE);     //ROM Commands: Read Scratchpad; 
			
		temper_in_bytes = DS18B20_read_from_sensor() | (DS18B20_read_from_sensor() << 8);    //Get 16 bit data from the sensor;
	}
	return temper_in_bytes;
}

double DS18B20_get_temperature(void)               //Function returns the temperature from the sensor in decimal value;
{	
	const int neg_temper_level = 2048;             //Under value 2048 (0x800) sensor shows negative temperature;        
	const double sensor_discreteness = 0.0625;     //Sensor discreteness of 12-bit data is 0.0625;
	
	if(DS18B20_temper_in_bytes() >= neg_temper_level)
	{
		return (((~DS18B20_temper_in_bytes()) + 1) * sensor_discreteness) * (-1);        //Return negative temperature;
	}
	else
	{
		return DS18B20_temper_in_bytes() * sensor_discreteness;                          //Return positive temperature;
	}
} 