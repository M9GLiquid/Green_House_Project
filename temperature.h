#ifndef TEMPERATURE_H
	#define TEMPERATURE_H

	// Includes
	#include "system_sam3x.h"
	#include "at91sam3x8.h"
	#include "display.h"
	#include "main.h"
	#include <stdio.h>

	//Functions
	void Init_Temp(void);
	short Read_Temp(void);
	void Temp_Mesurement(void);
	void Display_Temp(short temp);

	//Handlers
	void TC0_Handler(void);

	// Global Variables
	extern short minimum_limit;
	extern short maximum_limit;
#endif