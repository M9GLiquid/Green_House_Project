#ifndef TIME_H
	#define TIME_H

	// Includes
	#include "byte_manipulator.h"
	#include "light_sensor.h"
	#include "view_records.h"
	#include "display.h"
	#include "alarm.h"
	#include "main.h"
	#include <math.h>
	#include <stdio.h>

	// Functions
	void Init_Counter(void);
	void count_time(void);
	void update_seconds_on_display(void);
	void update_minutes_on_display(void);
	void update_hours_on_display(void);
	void update_days_on_display(void);
	void update_months_on_display(void);
	void update_years_on_display(void);
	void toggle_fast_mode(void);
	void Display_Speed_Factor(void);

#endif 