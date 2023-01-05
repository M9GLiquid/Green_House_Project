#ifndef LIGHT_LED_H
	#define LIGHT_LED_H

	// Includes
	#include "at91sam3x8.h"
	#include "display.h"
	#include "main.h"

	// Functions
	void Init_Light_LED(void);
	void Sunlamp(void);
	void Display_Sundegree_2_Display(int data1, int data2);

#endif