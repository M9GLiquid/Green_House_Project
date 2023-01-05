#ifndef DISPLAY_H
	#define DISPLAY_H

	// Includes
	#include "at91sam3x8.h"
	#include "light_sensor.h"
	#include "system_sam3x.h"
	#include <string.h>

	// Enums
	typedef enum View{
		_VIEW_SELECT_DATE = 0,
		_VIEW_MENU = 1,
		_VIEW_RECORDS = 2,
		_VIEW_TEMPERATURE_LIMITS = 3
	}VIEW;


	// PIN Help
	// PIOC
	#define _DISPLAY_RV ((unsigned int)1 << 19)  		// Reverse Display
	#define _DISPLAY_FS ((unsigned int)1 << 18)  		// Font System
	#define _DISPLAY_WR ((unsigned int)1 << 17)  		// Write to display
	#define _DISPLAY_RD ((unsigned int)1 << 16)  		// Read from display
	#define _DISPLAY_CE ((unsigned int)1 << 15)  		// Chip Enable pin
	#define _DISPLAY_CD ((unsigned int)1 << 14)  		// Command/Data Select or Register Select 
	#define _DISPLAY_DIR ((unsigned int)1 << 13) 		// Direction of data [O/I]
	#define _DISPLAY_OE ((unsigned int)1 << 12)  		// Output enable
	#define _DISPLAY_DATABUS ((unsigned int)0x3FC)
	// PIOD
	#define _DISPLAY_RESET ((unsigned int)0x1) 			// reset the display

	// Functions
	void Blank_Display(void);
	unsigned char Read_Status_Display(void);
	void Write_Command_2_Display(unsigned char command);
	void Write_Data_2_Display(unsigned char data);
	void Write_Character_2_Display(char key);
	void Write_Characters_2_Display(char *key);
	// TODO: unsigned int can be turned into unsigned char [0-255]
	void Write_Characters_2_DisplayPosition(char *key, unsigned char column, unsigned char row, VIEW view);
	void Init_Display(void);
	void Display_Screen(VIEW view);

#endif