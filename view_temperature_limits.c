#include "view_temperature_limits.h"

/**
  * Write out the defaults of the view temperature limits display
  * @return void
	*/
void Display_Configure_Limits(){	
  Write_Characters_2_DisplayPosition("Configure temperature limits", 6, 2, _VIEW_TEMPERATURE_LIMITS);
  Write_Characters_2_DisplayPosition("Change a digit at a time", 0, 3, _VIEW_TEMPERATURE_LIMITS);
  Write_Characters_2_DisplayPosition("Change [Left -> Right]", 0, 4, _VIEW_TEMPERATURE_LIMITS);
  Write_Characters_2_DisplayPosition("Press '*' toggles lower limit's symbol", 0, 5, _VIEW_TEMPERATURE_LIMITS);
	Write_Characters_2_DisplayPosition("Press '#' toggles upper limit's symbol", 0, 6, _VIEW_TEMPERATURE_LIMITS);
  Write_Characters_2_DisplayPosition(" ---'c Temperature lower limit", 0, 8, _VIEW_TEMPERATURE_LIMITS);
  Write_Characters_2_DisplayPosition(" ---'c Temperature upper limit", 0, 9, _VIEW_TEMPERATURE_LIMITS);
  Write_Characters_2_DisplayPosition("                                      ", 0, 10, _VIEW_TEMPERATURE_LIMITS);
  Write_Characters_2_DisplayPosition("                                      ", 0, 11, _VIEW_TEMPERATURE_LIMITS);
}

/**
  * Change the upper and lower limit of the temperature alert.
	*	One digit at a time
  * @return void
	*/
void Configure_Temperature_Limits(){
	char string[2];
	
	int index = 0;
	// Reset Values
	minimum_limit = maximum_limit = 0;
	
	// Remain on this view until we are done
	while(1){
		// Delay the action for an additional key press
		Delay(2500000);
		char key = Read_Keys();
		
		if (key > 12)
			continue;
		
		// Make the value negative without adding to the indexing
		if (key >= 10){
			if (key == 10){
				minimum_limit *= -1;
				if (minimum_limit < 0)
					Write_Characters_2_DisplayPosition("-", 0, 8, _VIEW_TEMPERATURE_LIMITS);
				else
					Write_Characters_2_DisplayPosition(" ", 0, 8, _VIEW_TEMPERATURE_LIMITS);
			continue;
			}else if (key == 12){
				maximum_limit *= -1;
				if (maximum_limit < 0)
					Write_Characters_2_DisplayPosition("-", 0, 9, _VIEW_TEMPERATURE_LIMITS);
				else
					Write_Characters_2_DisplayPosition(" ", 0, 9, _VIEW_TEMPERATURE_LIMITS);
			}
			continue;
		}
		
		switch(index){
// Upper temperature limit [maximum_limit] (+TTT -> -TTT)
		case 0: // T_1
			minimum_limit += (key * 100);
			// Write out the digit to the display
  		snprintf(string, 2, "%d", key);
  		Write_Characters_2_DisplayPosition(string, 1, 8, _VIEW_TEMPERATURE_LIMITS);
			break;
		case 1: // T_2
			minimum_limit += (key * 10);
			// Write out the digit to the display
  		snprintf(string, 2, "%d", key);
  		Write_Characters_2_DisplayPosition(string, 2, 8, _VIEW_TEMPERATURE_LIMITS);
			break;
		case 2: // T_3
			minimum_limit += (key * 1);
			// Write out the digit to the display
  		snprintf(string, 2, "%d", key);
  		Write_Characters_2_DisplayPosition(string, 3, 8, _VIEW_TEMPERATURE_LIMITS);
			break;
			
			
// Lower temperature limit [minimum_limit] (+TTT -> -TTT)
		case 3: // T_1
			maximum_limit += (key * 100);
			// Write out the digit to the display
  		snprintf(string, 2, "%d", key);
  		Write_Characters_2_DisplayPosition(string, 1, 9, _VIEW_TEMPERATURE_LIMITS);
			break;
		case 4: // T_2
			maximum_limit += (key * 10);
			// Write out the digit to the display
  		snprintf(string, 2, "%d", key);
  		Write_Characters_2_DisplayPosition(string, 2, 9, _VIEW_TEMPERATURE_LIMITS);
			break;
		case 5: // T_3
			maximum_limit += (key * 1);
			// Write out the digit to the display
  		snprintf(string, 2, "%d", key);
  		Write_Characters_2_DisplayPosition(string, 3, 9, _VIEW_TEMPERATURE_LIMITS);
  		Write_Characters_2_DisplayPosition("Press [1 - 9] to go back", 7, 10, _VIEW_TEMPERATURE_LIMITS);
  		Write_Characters_2_DisplayPosition("Press 0 to start over", 9, 11, _VIEW_TEMPERATURE_LIMITS);
			break;
		case 6:
			if (key == 0){
				index = -1;
				Display_Configure_Limits();
				minimum_limit = maximum_limit = 0;
				continue;
			}
			// Set the adress of display to second view
			Display_Screen(_VIEW_MENU);
			// Write out the defaults of the menu view
			display_view_menu(); 
			// Initiate counter for the new view
			Init_Counter();
			Delay(2500000);
			return;
		}
		index++;
	}
}