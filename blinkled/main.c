/*
 * main.c
 *
 *  Created on: Feb 26, 2020
 *      Author: badra069
 */

#include<avr/io.h>
#include <util/delay.h>



int main(void)
{

	DDRD |= 0b00000100;
	PORTD &= ~(1 << PD2);
	while(1)
	{
		PORTD ^=(1 << PD2);
		_delay_ms(500);
	}
}
