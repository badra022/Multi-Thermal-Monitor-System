/*
 * thermal_sensor.c
 *
 *  Created on: Jan 2, 2020
 *      Author: badra069
 */

#include"thermal_sensor.h"
volatile double Temp;
void THERMAL_conversion(void)
{
	Temp =((current_reading * 2.56)/1024)*100;
}
