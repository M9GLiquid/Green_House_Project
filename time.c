#include "time.h"

/**
  * Setup view's clock to the date and time selected
  * @return void
	*/
void Init_Counter(){
	// Push the time to the differnet Views
	update_seconds_on_display();
	update_minutes_on_display();
	update_hours_on_display();
	update_days_on_display();
	update_months_on_display();
	update_years_on_display();
	
	// Make sure we don't trigger anything at the very start
	Set_Boolean_Flag(0, NEW_SECOND);
	Set_Boolean_Flag(0, NEW_MINUTE);
	Set_Boolean_Flag(0, NEW_HOUR);
	Set_Boolean_Flag(0, NEW_DAY);
	Set_Boolean_Flag(0, NEW_MONTH);
  Set_Boolean_Flag(0, NEW_YEAR);
	time = 0;
}
char string[2] = {0, 0};

/**
  * Calculate the time
  * @return void
	*/
void count_time(){			
	// Check if new second
	if (Get_Boolean_Flag(NEW_SECOND) == 0)
		return;
	
	// Update seconds on display
	update_seconds_on_display();
	
	// A New minute
	if (Get_2_Bytes(&TIME_REGISTER, SECONDS) > 59){
		// Increment the minutes
		Increment_2_Bytes(&TIME_REGISTER, MINUTES);
		// Reset the seconds
		Set_2_Bytes(&TIME_REGISTER, (Get_2_Bytes(&TIME_REGISTER, SECONDS) % 60), SECONDS);
		// Update both on display
		update_minutes_on_display();
		update_seconds_on_display();
	}else
		return;
	// A New hour
	if (Get_2_Bytes(&TIME_REGISTER, MINUTES) > 59){
		// Increment the hours
		Increment_2_Bytes(&TIME_REGISTER, HOURS);
		// Reset the minutes
		Set_2_Bytes(&TIME_REGISTER, 0, MINUTES);
		// Update both on display
    update_hours_on_display();
		update_minutes_on_display();
  }else
		return;
	// A New Day
	if (Get_2_Bytes(&TIME_REGISTER, HOURS) > 23){
		// Increment the days
		Increment_2_Bytes(&DATE_REGISTER, DAY);
		// Reset the hours
		Set_2_Bytes(&TIME_REGISTER, 0, HOURS);
		// Update both on display
    update_days_on_display();
    update_hours_on_display();
  }else
		return;
	// A New Month
	unsigned char daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (Get_2_Bytes(&DATE_REGISTER, DAY) > daysInMonth[Get_2_Bytes(&DATE_REGISTER, MONTH)]){
		// Increment the month
		Increment_2_Bytes(&DATE_REGISTER, MONTH);
		// Reset the days
		Set_2_Bytes(&DATE_REGISTER, 1, DAY);
		// Update both on display
    update_months_on_display();
    update_days_on_display();
  }else
		return;
	// A New Year
	if (Get_2_Bytes(&DATE_REGISTER, MONTH) > 12){
		// Increment the year
		Increment_4_Bytes(&DATE_REGISTER, YEAR);
		// Reset the months
		Set_2_Bytes(&DATE_REGISTER, 1, MONTH);
		// Update both on display
    update_years_on_display();
    update_months_on_display();
  }else
		return;
}

/**
  * Display change of seconds to the screen
  * @return void
	*/
void update_seconds_on_display(){
  snprintf(string, 3, "%02d", Get_2_Bytes(&TIME_REGISTER, SECONDS));
	Write_Characters_2_DisplayPosition(string, 38, 0, _VIEW_MENU);
	Write_Characters_2_DisplayPosition(string, 38, 0, _VIEW_RECORDS);
	Write_Characters_2_DisplayPosition(string, 38, 0, _VIEW_TEMPERATURE_LIMITS);
}

/**
  * Display change of minutes to the screen
  * @return void
	*/
void update_minutes_on_display(){
	// Set the boolean flag of NEW MINUTE
	Set_Boolean_Flag(1, NEW_MINUTE);
	snprintf(string, 3, "%02d", Get_2_Bytes(&TIME_REGISTER, MINUTES));
	Write_Characters_2_DisplayPosition(string, 35, 0, _VIEW_MENU);
	Write_Characters_2_DisplayPosition(string, 35, 0, _VIEW_RECORDS);
	Write_Characters_2_DisplayPosition(string, 35, 0, _VIEW_TEMPERATURE_LIMITS);
}

/**
  * Display change of hours to the screen
  * @return void
	*/
void update_hours_on_display(){
	// Set the boolean flag of NEW HOUR
	Set_Boolean_Flag(1, NEW_HOUR);
  snprintf(string, 3, "%02d", Get_2_Bytes(&TIME_REGISTER, HOURS));
	Write_Characters_2_DisplayPosition(string, 32, 0, _VIEW_MENU);
	Write_Characters_2_DisplayPosition(string, 32, 0, _VIEW_RECORDS);
	Write_Characters_2_DisplayPosition(string, 32, 0, _VIEW_TEMPERATURE_LIMITS);
}

/**
  * Display change of days to the screen
  * @return void
	*/
void update_days_on_display(){
	// Set the boolean flag of NEW DAY
	Set_Boolean_Flag(1, NEW_DAY);
	snprintf(string, 3, "%02d", Get_2_Bytes(&DATE_REGISTER, DAY));
	Write_Characters_2_DisplayPosition(string, 21, 0, _VIEW_MENU);
	Write_Characters_2_DisplayPosition(string, 21, 0, _VIEW_RECORDS);
	Write_Characters_2_DisplayPosition(string, 21, 0, _VIEW_TEMPERATURE_LIMITS);
}

/**
  * Display change of months to the screen
  * @return void
	*/
void update_months_on_display(){
	// Set the boolean flag of NEW MONTH
	Set_Boolean_Flag(1, NEW_MONTH);
  snprintf(string, 3, "%02d", Get_2_Bytes(&DATE_REGISTER, MONTH));
	Write_Characters_2_DisplayPosition(string, 24, 0, _VIEW_MENU);
	Write_Characters_2_DisplayPosition(string, 24, 0, _VIEW_RECORDS);
	Write_Characters_2_DisplayPosition(string, 24, 0, _VIEW_TEMPERATURE_LIMITS);
}

/**
  * Display change of year to the screen
  * @return void
	*/
void update_years_on_display(){
	// Set the boolean flag of NEW YEAR
	Set_Boolean_Flag(1, NEW_YEAR);
	// Divide the year into 2 2-bytes and display them seperately due to the constraints of the *char
	snprintf(string, 3, "%02d", Get_2_Bytes(&DATE_REGISTER, MINUTES));
	Write_Characters_2_DisplayPosition(string, 27, 0, _VIEW_MENU);
	Write_Characters_2_DisplayPosition(string, 27, 0, _VIEW_RECORDS);
	Write_Characters_2_DisplayPosition(string, 27, 0, _VIEW_TEMPERATURE_LIMITS);
	snprintf(string, 3, "%02d", Get_2_Bytes(&DATE_REGISTER, SECONDS));
	Write_Characters_2_DisplayPosition(string, 29, 0, _VIEW_MENU);
	Write_Characters_2_DisplayPosition(string, 29, 0, _VIEW_RECORDS);
	Write_Characters_2_DisplayPosition(string, 29, 0, _VIEW_TEMPERATURE_LIMITS);
}

/**
  * Toggle between  the 4 different fast modes, Normal (*1), Faster (*10), Fast (100*) and Fastest(1000*)
  * @return void
	*/
void toggle_fast_mode(){
// 10 ms Speed
	if (Get_Boolean_Flag(FAST_MODE_100) == 1){
		Set_Boolean_Flag(0, FAST_MODE_100);
		Set_Boolean_Flag(1, FAST_MODE_10);
		// Update clock ~once every 10 ms
		TICKS = 1000 *  0.01; 
		Display_Speed_Factor();	
// 1 ms Speed
	}else if (Get_Boolean_Flag(FAST_MODE_10) == 1){
		Set_Boolean_Flag(0, FAST_MODE_10);
		Set_Boolean_Flag(1, FAST_MODE_1);
		// Update clock ~once every 1 ms
		TICKS = 1000 *  0.001; 
		Display_Speed_Factor();	
// 1000 ms Speed
	}else if (Get_Boolean_Flag(FAST_MODE_1) == 1){
		Set_Boolean_Flag(0, FAST_MODE_10);
		Set_Boolean_Flag(0, FAST_MODE_100);
		Set_Boolean_Flag(0, FAST_MODE_1);
		// Update clock ~once every sec
    TICKS = 1000; 
		Display_Speed_Factor();	
// 100 ms Speed
	}else{
		Set_Boolean_Flag(1, FAST_MODE_100);
		// Update clock ~once every 100 ms
		TICKS = 1000 *  0.1; 
		Display_Speed_Factor();	
	}
}

/**
  * Display the speed factor to Display
  * @param temperature: The temperature to be displayed
  * @return void
	*/
void Display_Speed_Factor(){
	// Dependent on which of the boolean flag's 
	// that is set display the factor of speed
	if (Get_Boolean_Flag(FAST_MODE_100) == 1)
		Write_Characters_2_DisplayPosition("[  10*]", 33, 1, _VIEW_MENU);
	else if (Get_Boolean_Flag(FAST_MODE_10) == 1)
		Write_Characters_2_DisplayPosition("[ 100*]", 33, 1, _VIEW_MENU);
	else if (Get_Boolean_Flag(FAST_MODE_1) == 1)
		Write_Characters_2_DisplayPosition("[1000*]", 33, 1, _VIEW_MENU);	
	else
		Write_Characters_2_DisplayPosition("[   1*]", 33, 1, _VIEW_MENU);
}

