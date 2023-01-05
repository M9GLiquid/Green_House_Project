#ifndef MAIN_H
	#define MAIN_H

	// Includes
	#include "view_select_date.h"
	#include "byte_manipulator.h"
	#include "light_sensor.h"
	#include "system_sam3x.h"
	#include "temperature.h"
	#include "servo_motor.h"
	#include "at91sam3x8.h"
	#include "view_menu.h"
	#include "light_LED.h"
	#include "datelist.h"
	#include "timelist.h"
	#include "display.h"
	#include "alarm.h"
	#include "time.h"
	#include <stdio.h>

	//Global variables
	extern unsigned int DATE_REGISTER;
	extern unsigned int TIME_REGISTER;
	extern unsigned int time;
	extern unsigned short TICKS;
	extern unsigned short booleanFlagSet; // check FLAG Enum for details
	
	// Enums
	typedef enum Flag{ // Used in booleanFlagSet
		TC_RISING_EDGE = 0,	// Detect the rising edge of the light sensor
		LIGHT_SENSORS = 1,	// Read data from Light sensors
		NO_LIGHT = 2, 			// No Light detected
		TEMP_ALARM = 3, 		// Alarm enable/disable
		FAST_MODE_100 = 4, 	// 100 ms
		FAST_MODE_10 = 5,		// 10 ms
		FAST_MODE_1 = 6,		// 1 ms
		SUN_LAMP = 7,				// Sun lamp enabled/disable
		ALARM_TOGGLE = 8,		// Alarm toggling on display
		VIEW_RECORDS = 9,		// We are on the view where we display the records
		NEW_SECOND = 10,		// A new second is registered
		NEW_MINUTE = 11,		// A new minute is registered
		NEW_HOUR = 12,			// A new hour is registered
		NEW_DAY = 13,				// A new day is registered
		NEW_MONTH = 14,			// A new month is registered
		NEW_YEAR = 15				// A new year is registered
	}FLAG;

	// Handlers
	void SysTick_Handler(void);

	// Functions
	void config(void);
	void Delay(int Value);
	char Get_Boolean_Flag(FLAG flag);
	void Set_Boolean_Flag(char x, FLAG flag);
	void update_every_second(void);
	void update_every_minute(void);
	void update_every_hour(void);
	void update_every_day(void);
	void update_every_month(void);
	void update_every_year(void);

#endif