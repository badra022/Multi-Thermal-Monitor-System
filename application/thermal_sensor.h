/*
 * thermal_sensor.h
 *
 *  Created on: Jan 2, 2020
 *      Author: badra069
 */

#ifndef THERMAL_SENSOR_H_
#define THERMAL_SENSOR_H_

#include"adc.h"
void THERMAL_conversion(void);
extern volatile long long Temp;

#endif /* THERMAL_SENSOR_H_ */
