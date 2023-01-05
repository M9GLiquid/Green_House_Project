#include "view_menu.h"

/**
  * Select a menu selection
	* 0. Select a new date & time
	* 1. View the recorded data
	* 2. Toggle between Faster Modes [1*|10*|100*|1000*]
	* 3. Reset the Alarm both LED and Display
	* 3. Configure Temperature Alarm Limits
  * @return void
	*/
void menu_selection(){
	char key = Read_Keys();
	
	 // Only listen for keys for the menu
	if ( key > 12)
		return;
	
	// Select what todo on the keypress
	switch(key){
		// Select new date & time
		case 0: 
			Display_Screen(_VIEW_SELECT_DATE);
			Set_Boolean_Flag(0, VIEW_RECORDS);
			view_select_date();
			Init_Counter();
			break;
		// View recorded data
		case 1: 
			Display_Screen(_VIEW_RECORDS);
			Set_Boolean_Flag(1, VIEW_RECORDS);
			View_Records();
			Init_Counter();
			break;
		// Enable Faster Mode [10*|100*|1000*]
		case 2: 
			toggle_fast_mode();
			// disable the fast "pressing mode"
			Delay(2500000); 
			break;
		// Reset Alarm
		case 3: 
			// Check if the alarm of the temperature is active
			if (Get_Boolean_Flag(TEMP_ALARM) == 0)
				return;
			// Reset the boolean alarm flag
			Set_Boolean_Flag(0, TEMP_ALARM);
			// Clear the Alarm from the screen
			Write_Characters_2_DisplayPosition("                    ", 0, 1, _VIEW_SELECT_DATE);
			Write_Characters_2_DisplayPosition("                    ", 0, 1, _VIEW_MENU);
  		Write_Characters_2_DisplayPosition("DD/MM/YYYY   MIN        AVG   MAX", 0, 1, _VIEW_RECORDS);
			Write_Characters_2_DisplayPosition("                    ", 0, 1, _VIEW_TEMPERATURE_LIMITS);
  		*AT91C_PIOA_CODR = (AT91C_PIO_PA7);
			break;
		// Configure the temperature limits
		case 4: 
			Display_Screen(_VIEW_TEMPERATURE_LIMITS);
			Display_Configure_Limits();
 	 		Write_Characters_2_DisplayPosition("DD/MM/YYYY hh:mm:ss", 21, 0, _VIEW_TEMPERATURE_LIMITS);
			Init_Counter();
			Configure_Temperature_Limits();
			break;
		// Return to Menu view
		case 10:
		case 12:
			// Set the adress of display to second view
			Display_Screen(_VIEW_MENU);
			// Write out the defaults of the menu view
			display_view_menu(); 
			// Reset the boolean view_records flag
			Set_Boolean_Flag(0, VIEW_RECORDS);
			// Initiate counter for the new view
			Init_Counter();
			// Write out the speed factor on the display again
			Display_Speed_Factor();	
			break;
	}
}

/**
  * Write out the defaults of the menu view
  * @return void
	*/
void display_view_menu(){
  Write_Characters_2_DisplayPosition("DD/MM/YYYY hh:mm:ss", 21, 0, _VIEW_MENU);
	Write_Characters_2_DisplayPosition("Speed:[   1*]", 27, 1, _VIEW_MENU);
  Write_Characters_2_DisplayPosition("Press (keypad) to select..", 3, 3, _VIEW_MENU);
	Write_Characters_2_DisplayPosition("Menu:", 2, 5, _VIEW_MENU);
  Write_Characters_2_DisplayPosition("0. Select new date & time", 2, 6, _VIEW_MENU);
  Write_Characters_2_DisplayPosition("1. View recorded data", 2, 7, _VIEW_MENU);
  Write_Characters_2_DisplayPosition("2. Toggle Faster Mode [10*|100*|1000*]", 2, 8, _VIEW_MENU);
  Write_Characters_2_DisplayPosition("3. Reset Alarm", 2, 9, _VIEW_MENU);
  Write_Characters_2_DisplayPosition("4. Configure Alarm Limits", 2, 9, _VIEW_MENU);
}