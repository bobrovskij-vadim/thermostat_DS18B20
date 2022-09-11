/*
 * UART.c
 *
 * Created: 24.08.2022 12:50:01
 *  Author: vadim
 */ 

#include "UART.h"

void UART_settings(unsigned int ubrr)                           //The UART initialization function;
{                                                               //ubrr - accepts baud rate settings;
	UBRRH = (unsigned char)(ubrr >> 8);                         //Set the baud rate - 9600 BAUD. fOSC = 1 000 000 Hz. 
	UBRRL = (unsigned char)(ubrr);                              //Asynchronous double speed mode (U2X = 1);
	UCSRA |= (1<<U2X);                                          //Double the UART transmission speed;
	UCSRB = (1<<RXEN) | (1<<TXEN);                              //RXEN: Receiver Enable. TXEN: Transmitter Enable;
	UCSRC = (1<<URSEL) | (1<<USBS) | (1<<UCSZ1) | (1<<UCSZ0);   //URSEL: Register Select - Asynchronous mode. USBS: Stop Bit Select - 2-bit. UCSZ1:0: Character Size - 8-bit;                  
}

void UART_transmit(unsigned char data)                          //Data Transmission function. Sending Frames with 5 to 8 data bits;
{
	while (!( UCSRA & (1<<UDRE)))                               //Wait for empty transmit buffer;
	;
	UDR = data;                                                 //Put data into buffer, sends the data;
}

void UART_print_string(char *str)                               //Function prints sent char array;     
{
	while(*str != '\0')
	{
		UART_transmit(*str);
		str++;
	}
}

unsigned char UART_receive(void)                                //Data Receiving function;
{
	while ( !(UCSRA & (1<<RXC)) )                               //Wait for data to be received;
	;
	return UDR;                                                 //Get and return received data from buffer;
}

float UART_set_temperature()                                    //Setting temperature function;
{
	char str[6];
	for(int i = 0; i <= 6; ++i)
	{
		str[i] = UART_receive();
		if(str[i] == ',')
		{
			str[i] = '.';
		}
		else if(str[i] == 13)
		{
			break;
		}
	}
	float temperature = atof(str);
	
	if(temperature < -55) temperature = -55;                    //Measures Temperatures from -55°C     
	else if(temperature > 125) temperature = 125;               //to +125°C;
	
	return temperature;
}

void UART_get_temperature(float set_t, float cur_t)             //Function returns temperature from sensor to UART; 
{
	char temperature[6];
	UART_print_string("\r\rSettled t: ");
	dtostrf(set_t, 2, 1, temperature);
	UART_print_string(temperature);
	UART_print_string(" C\r\n");
	
	UART_print_string("Current t: ");
	dtostrf(cur_t, 2, 1, temperature);
	UART_print_string(temperature);
	UART_print_string(" C\r\n");	
}

char UART_menu(void)                                            //Menu temperature controlling;
{
	UART_print_string("\rTemperature control menu:\n\r");
	UART_print_string("1. Get temperature input '1';\n\r");
	UART_print_string("2. Set temperature input '2';\n\r");
	UART_print_string("Your input: ");
	char response = UART_receive();
	if(response == '2')
	{
		UART_print_string("\rEnter the temperature: ");
	}
	return response;
}