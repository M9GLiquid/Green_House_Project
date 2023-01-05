#ifndef KEY_PAD_H
	#define KEY_PAD_H

	// Includes
	#include "system_sam3x.h"
	#include "at91sam3x8.h"
	#include "main.h"

	// PIN Help
	#define _KEYPAD_COLUMN_PINS ((unsigned int)0x380) // 3 Pins (7-9)
	#define _KEYPAD_ROW_PINS ((unsigned int)0x3C)     // 4 Pins (2-5)
	#define _KEYPAD_OE ((unsigned int)0x4)           	// 1 Pin
	#define _KEYPAD_PINS ((unsigned int)0x3BC)       	// 7 Pins (2-5, 7-9)

	// Functions
	void Init_Keypad(void);
	char Read_Keys(void);

#endif 