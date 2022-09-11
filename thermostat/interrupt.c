/*
 * interrupt.c
 *
 * Created: 01.09.2022 15:36:16
 *  Author: vadim
 */ 

#include "interrupt.h"

void interrupt_settings(void)            //Interrupt settings for TCNT1;
{
	 TCCR1B |= (1<<CS11) | (1<<CS10);    //Timer/Counter1 settings. Frequency divider 8;
	 TIMSK |= (1<<TOIE1);                //Timer/Counter1 overflow interrupt Enable;
	 TCNT1 = 0;                          //TCNT1 set to zero;
	 
	 sei();                              //All interrupts enabled;                         
}