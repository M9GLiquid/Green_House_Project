#include "alarm.h"

/**
	* Start alarms on display and lamp
	* Returns nothing
	*/
void Alarm(){
	// Checks whether the alarm is supposed to be on or not
	if (Get_Boolean_Flag(TEMP_ALARM) == 0)
		return;
	
	// Start the alarm
	Set_Alarm();
}

/**
	* Display the alarm on the screen aswell as by a LED
	* Returns nothing
	*/
void Set_Alarm(){
	if (Get_Boolean_Flag(ALARM_TOGGLE) == 1){
		// Write to all displays
		Write_Characters_2_DisplayPosition("TEMPERATURE ALERT!  ", 0, 1, _VIEW_SELECT_DATE);
		Write_Characters_2_DisplayPosition("TEMPERATURE ALERT!  ", 0, 1, _VIEW_MENU);
		Write_Characters_2_DisplayPosition("TEMPERATURE ALERT!  ", 0, 1, _VIEW_RECORDS);
		// Turn the LED on (Set)
  	*AT91C_PIOA_SODR = (AT91C_PIO_PA7);
		// Toggle the alarm bit
		Set_Boolean_Flag(0, ALARM_TOGGLE);
	}else{
		// Write to all displays
		Write_Characters_2_DisplayPosition("                    ", 0, 1, _VIEW_SELECT_DATE);
		Write_Characters_2_DisplayPosition("                    ", 0, 1, _VIEW_MENU);
		Write_Characters_2_DisplayPosition("                    ", 0, 1, _VIEW_RECORDS);
		// Turn the LED off (Clear)
  	*AT91C_PIOA_CODR = (AT91C_PIO_PA7);
		// Toggle the alarm bit
		Set_Boolean_Flag(1, ALARM_TOGGLE);
	}
}