#include "view_select_date.h"

void view_select_date(){
	// Printing the default Select Date View
	display_view_start();
	
	char string[2] = {0,0};
	char key = 0;
	char i = 0;
	
	// Wait for date & time to be fully set
	while(1){ 
		
		// Make sure time isn't running while setting the date & time
		time = 0;
		
		// Get the key pressed
		key = Read_Keys();
		
		// We didn't read a [0-9] key press
		if (key > 9) 
			continue;
		
		// We go through each date number individually, DD/MM/YYYY hh:mm:ss
		switch(i){
// D_1
			case 0: 
				// 31 Days max
				if (key > 3) 
					key = 3;
  			snprintf(string, 2, "%d", key);
				Write_Characters_2_DisplayPosition(string, 21, 0, _VIEW_SELECT_DATE);
				Write_Characters_2_DisplayPosition(string, 10, 6, _VIEW_SELECT_DATE);
				break;
// D_2
			case 1: 
				// 31 Days max, 1 day min
				if ((Get_1_Byte(&DATE_REGISTER, i - 1) >= 3 && key > 1) 
						|| (Get_1_Byte(&DATE_REGISTER, i - 1) == 0 && key == 0)) 
					key = 1;
  			snprintf(string, 2, "%d", key);
				Write_Characters_2_DisplayPosition(string, 22, 0, _VIEW_SELECT_DATE);
				Write_Characters_2_DisplayPosition(string, 11, 6, _VIEW_SELECT_DATE);
				break;
// M_1
			case 2: 
				if (key > 1) // 12 Month max
					key = 1;
  			snprintf(string, 2, "%d", key);
				Write_Characters_2_DisplayPosition(string, 24, 0, _VIEW_SELECT_DATE);
				Write_Characters_2_DisplayPosition(string, 20, 6, _VIEW_SELECT_DATE);
				break;
 // M_2
			case 3: // KLART ******************************************************************************************************************
				// Month between october and december [10 - 12]
				if (Get_2_Bytes(&DATE_REGISTER, MONTH) >= 10){
					switch(key){
					case 1: // November Max 30 days
						if (Get_2_Bytes(&DATE_REGISTER, DAY) < 30)
							break;
						// Set D_2 to display
						Write_Characters_2_DisplayPosition("30", 21, 0, _VIEW_SELECT_DATE);
						Write_Characters_2_DisplayPosition("30", 10, 6, _VIEW_SELECT_DATE);
						Set_2_Bytes(&DATE_REGISTER, 30, DAY);
						break;
					case 0: // October,
					case 2: // December Max 31 days
						break;
					default: // Max Month is 12
						key = 2;
						break;
					}
				}else{
					// month 0 doesn't exist, januari is first
					if (key == 0)
						key = 1;
				// Month between januari and september [0 - 9]
					switch(key){
					case 2: // Februari
						// Februari has a maximum of 28 days
						if (Get_2_Bytes(&DATE_REGISTER, DAY) < 28)
							break;
						// Set D_2 to display
						Write_Characters_2_DisplayPosition("28", 21, 0, _VIEW_SELECT_DATE);
						Write_Characters_2_DisplayPosition("28", 10, 6, _VIEW_SELECT_DATE);
						Set_2_Bytes(&DATE_REGISTER, 28, DAY);
						break;
					case 4: // April,
					case 6: // June,
					case 9: // September, Max 30 days
						// Set D_2 to display
						Write_Characters_2_DisplayPosition("30", 21, 0, _VIEW_SELECT_DATE);
						Write_Characters_2_DisplayPosition("30", 10, 6, _VIEW_SELECT_DATE);
						Set_2_Bytes(&DATE_REGISTER, 30, DAY);
						break;
					// Januari, Mars, May, July, August
					default: 
						break;
					}
				}
  			snprintf(string, 2, "%d", key);
				Write_Characters_2_DisplayPosition(string, 25, 0, _VIEW_SELECT_DATE);
				Write_Characters_2_DisplayPosition(string, 21, 6, _VIEW_SELECT_DATE);
				break;
// Y_1
			case 4: // 0 - 9 is okey
				// Set Y_1 to display
  			snprintf(string, 2, "%d", key);
				Write_Characters_2_DisplayPosition(string, 27, 0, _VIEW_SELECT_DATE);
				Write_Characters_2_DisplayPosition(string, 29, 6, _VIEW_SELECT_DATE);
				break;
// Y_2
			case 5:  // 0 - 9 is okey
				// Set Y_2 to display
  			snprintf(string, 2, "%d", key);
				Write_Characters_2_DisplayPosition(string, 28, 0, _VIEW_SELECT_DATE);
				Write_Characters_2_DisplayPosition(string, 30, 6, _VIEW_SELECT_DATE);
				break;
// Y_3
			case 6:  // 0 - 9 is okey
				// Set Y_3 to display
  			snprintf(string, 2, "%d", key);
				Write_Characters_2_DisplayPosition(string, 29, 0, _VIEW_SELECT_DATE);
				Write_Characters_2_DisplayPosition(string, 31, 6, _VIEW_SELECT_DATE);
				break;
// Y_4
			case 7:  // 0 - 9 is okey
				// Set Y_4 to display
  			snprintf(string, 2, "%d", key); 
				Write_Characters_2_DisplayPosition(string, 30, 0, _VIEW_SELECT_DATE);
				Write_Characters_2_DisplayPosition(string, 32, 6, _VIEW_SELECT_DATE);
				break;
// h_1
			case 8: 
				// 24 hours is max
				if (key > 2) 
					key = 2;
  			snprintf(string, 2, "%d", key); // Set h_1
				Write_Characters_2_DisplayPosition(string, 32, 0, _VIEW_SELECT_DATE);
				Write_Characters_2_DisplayPosition(string, 11, 7, _VIEW_SELECT_DATE);
				break;
// h_2
			case 9: 
				// 24 hours is max
				if (Get_2_Bytes(&TIME_REGISTER, HOURS) >= 20 && key > 3){ 
					key = 0;
					// Set h_1 to display
  				snprintf(string, 2, "%d", key);
					Write_Characters_2_DisplayPosition(string, 32, 0, _VIEW_SELECT_DATE);
					Write_Characters_2_DisplayPosition(string, 11, 7, _VIEW_SELECT_DATE);
					Set_1_Byte(&TIME_REGISTER, key, i - 1);
				}
					// Set h_2 to display
  			snprintf(string, 2, "%d", key);
				Write_Characters_2_DisplayPosition(string, 33, 0, _VIEW_SELECT_DATE);
				Write_Characters_2_DisplayPosition(string, 12, 7, _VIEW_SELECT_DATE);
				break;
// m_1
			case 10: 
				if (key >= 6) // 60 minutes is max
					key = 5;
  			snprintf(string, 2, "%d", key); // Set m_1
				Write_Characters_2_DisplayPosition(string, 35, 0, _VIEW_SELECT_DATE);
				Write_Characters_2_DisplayPosition(string, 22, 7, _VIEW_SELECT_DATE);
				break;
// m_2
			case 11: 
				if (Get_2_Bytes(&TIME_REGISTER, MINUTES) >= 60){ // 60 Minutes is max
					// Set m_1 to display
  				snprintf(string, 2, "%d", 5);
					Write_Characters_2_DisplayPosition(string, 35, 0, _VIEW_SELECT_DATE);
					Write_Characters_2_DisplayPosition(string, 22, 7, _VIEW_SELECT_DATE);
					Set_1_Byte(&TIME_REGISTER, 5, i - 1);
				}
				// Set m_2 to display
  			snprintf(string, 2, "%d", key);
				Write_Characters_2_DisplayPosition(string, 36, 0, _VIEW_SELECT_DATE);
				Write_Characters_2_DisplayPosition(string, 23, 7, _VIEW_SELECT_DATE);
				break;
// s_1
			case 12: 
				if (key >= 6) // 60 seconds is max
					key = 5;
				// Set s_1 to display
  			snprintf(string, 2, "%d", key); 
				Write_Characters_2_DisplayPosition(string, 38, 0, _VIEW_SELECT_DATE);
				Write_Characters_2_DisplayPosition(string, 33, 7, _VIEW_SELECT_DATE);
				break;
// s_2
			case 13: 
				if (Get_2_Bytes(&TIME_REGISTER, SECONDS) >= 60){ // 60 Minutes is max
					// Set s_1 to display
  				snprintf(string, 2, "%d", 5);
					Write_Characters_2_DisplayPosition(string, 38, 0, _VIEW_SELECT_DATE);
					Write_Characters_2_DisplayPosition(string, 33, 7, _VIEW_SELECT_DATE);
					Set_1_Byte(&TIME_REGISTER, 5, i - 1);
				}
				// Set s_2 to display
  			snprintf(string, 2, "%d", key); 
				Write_Characters_2_DisplayPosition(string, 39, 0, _VIEW_SELECT_DATE);
				Write_Characters_2_DisplayPosition(string, 34, 7, _VIEW_SELECT_DATE);
				
				Set_1_Byte(&TIME_REGISTER, key, i - 6);
				// Date and time has been set
				// Setup next VIEW
				Delay(2500000);
				Display_Screen(_VIEW_MENU);
				display_view_menu(); 
				
				Init_Counter();
				return;
		}
		if (i < 8)
			Set_1_Byte(&DATE_REGISTER, key, i);
		else
			Set_1_Byte(&TIME_REGISTER, key, i - 6);
		i++;
		Delay(2500000);
	}
}


/**
  * Display the defaults of the start view 
  * @return void
	*/
void display_view_start(){	
	//Default before date and time has been set!
  Write_Characters_2_DisplayPosition("DD/MM/YYYY hh:mm:ss", 21, 0, _VIEW_SELECT_DATE);
  Write_Characters_2_DisplayPosition("Using the Keypad..", 9, 3, _VIEW_SELECT_DATE);
  Write_Characters_2_DisplayPosition("Select the date/time", 8, 4, _VIEW_SELECT_DATE);
  Write_Characters_2_DisplayPosition("Day:--, Month:--, Year:----", 6, 6, _VIEW_SELECT_DATE);
  Write_Characters_2_DisplayPosition("Hour:--, Minute:--, Second:--", 6, 7, _VIEW_SELECT_DATE);
}