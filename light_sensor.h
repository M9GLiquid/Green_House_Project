#ifndef LIGHT_SENSOR_H
	#define LIGHT_SENSOR_H

	#include "main.h"
	#include "alarm.h"
	#include "display.h"
	#include "servo_motor.h"
	#include "at91sam3x8.h"
	#include "system_sam3x.h"
	#include <stdio.h>
	#include <math.h>

	void Init_LightSensor(void);
	void Read_Light(void);
	void Light_Measurement(void);
	void Display_Light_Position(unsigned char light);

	// Handlers
	void ADC_Handler(void);
	
#endif