/*
 * thermal_sensor.c
 *
 *  Created on: Jan 2, 2020
 *      Author: badra069
 */

#include"thermal_sensor.h"
volatile long long Temp;
void THERMAL_conversion(void)
{
	Temp = current_reading;
	Temp =(Temp * 150 * 5)/(1.5*1023);
}
