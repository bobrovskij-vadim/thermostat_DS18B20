/*
 * thermostat.c
 *
 * Created: 18.08.2022 13:00:58
 * Author : vadim
 *
 */ 

#include "main.h"

float settled_t = 0;        //Settled temperature from UART;
float current_t = 0;		//Current temperature from temperature sensor.

ISR(TIMER1_OVF_vect)       
{
	current_t = DS18B20_get_temperature();               //Getting temperature from DS18B20;
	LCD_show_temperature(settled_t, current_t);          //Printing temperature on the LCD;
	temperature_controller(settled_t, current_t);        //Controlling heating and cooling; 
}

int main(void)
{	
	LCD_ports_settings();                   //Microcontroller ports settings which connect with the LCD; 
	
	t_control_ports_settings();             //Function for port settings to control the temperature;
	 
	LCD_initialization();                   //LCD initialization function;
	
	UART_settings(12);                      //Set the baud rate - 9600 BAUD. fOSC = 1 000 000 Hz. Asynchronous double speed mode (U2X = 1); 
	
	interrupt_settings();                   //Turning on First timer counter, frequency divider is 8, overflow interrupt enable;
		
	settled_t = EEPROM_float_read(0);       //Reading last settled temperature; 

    while (1) 
    {
		char res = UART_menu(); 
		if(res == '1')                                         //Get temperature; 
		{
			UART_get_temperature(settled_t, current_t);
		}
		else if(res == '2')                                    //Set temperature;
		{
			settled_t = UART_set_temperature();                //Setting the temperature;
			EEPROM_float_write(0, settled_t);                  //Save settled temperature to EEPROM;
		}
    }
}

