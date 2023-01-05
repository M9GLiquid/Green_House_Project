#include "key_pad.h"


/**
  * Initialize the keypad pins
  * @return void
	*/
void Init_Keypad(){
	// Enable PIOC & PIOD
  *AT91C_PMC_PCER = (0x6000); 
  
	// Peripheral enable PC(2-5), PC(7-9), PD(2)
  *AT91C_PIOC_PER = (_KEYPAD_PINS); 
  *AT91C_PIOD_PER = (_KEYPAD_OE);
	
	// Pullup disable PC(2-5), PC(7-9), PD(2)
  *AT91C_PIOC_PPUDR = (_KEYPAD_PINS); 
  *AT91C_PIOD_PPUDR = (_KEYPAD_OE);
}

/**
  * Reads the keypad to determine and send back the key pressed
  * @return the key pressed by the user
	*/
char Read_Keys(){
	// Output Enable Pin (The component/chip)
  *AT91C_PIOD_OER = (_KEYPAD_OE);  
	// Make all Column pins as output
  *AT91C_PIOC_OER = (_KEYPAD_COLUMN_PINS); 

	// Clear OE KEY BUS (Active Low)
  *AT91C_PIOD_CODR = (_KEYPAD_OE);        
	// Set all Column pin as high
  *AT91C_PIOC_SODR = (_KEYPAD_COLUMN_PINS); 
	// Set Row pins as input
  *AT91C_PIOC_ODR = (_KEYPAD_ROW_PINS);  
	
  for (int col = 0; col < 3; col++) {
		// Anti Fast Pressing
    Delay(50);          
		// Clear one column at the time
    *AT91C_PIOC_CODR = (1 << (7 + col)); 
		
    for (int row = 0; row < 4; row++) {  
      // Read row and check if bit is zero
      if ((*AT91C_PIOC_PDSR & (1 << (2 + row))) == 0) {
				
				// key pressed = Row*3+Col+1;
				// If key 0 pressed, set value to 0
        if ((row * 3 + col + 1) == 11)
          return 0;
				
				// KLART		***********************
				
				// Set all Column pin
        *AT91C_PIOC_SODR = (1 << (7 + col));   
				// Make all Column pin as input
        *AT91C_PIOC_ODR = (_KEYPAD_COLUMN_PINS); 
        return (row * 3 + col + 1);
      }
    }
		// Set all Column pin as high
    *AT91C_PIOC_SODR = (1 << (7 + col)); 
  }
	// Make all Column pin as input
  *AT91C_PIOC_ODR = (_KEYPAD_COLUMN_PINS); 
	return -1;
}
