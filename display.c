#include "display.h"

/**
  * Write multiple characters to the display to be shown
  * @param key: The string to be written out on the display
  * @return void
	*/
void Write_Characters_2_Display(char *key) {
	
	// Write out the string, by incrementing ADP each time written
  for (int i = 0; i < strlen(key); i++) {
    Write_Character_2_Display(key[i]);
  }
}

/**
  * Change the display to show a new "side"
  * @param view: Which view to display to the user
  * @return void
	*/
void Display_Screen(VIEW view){
	switch(view){
		// Display the first screen to the user
		case _VIEW_SELECT_DATE:
			// Data 1
			Write_Data_2_Display(0x00); 
			// Data 2
			Write_Data_2_Display(0x00); 
			// Set Text Home Address OPCODE 
			Write_Command_2_Display(0x40); 
			break;
		// Display the second screen to the user
		case _VIEW_MENU:
			// Data 1
			Write_Data_2_Display(0x80); 
			// Data 2
			Write_Data_2_Display(0x02); 
			// Set Text Home Address OPCODE
			Write_Command_2_Display(0x40); 
			break;
		// Display the third screen to the user
		case _VIEW_RECORDS:
			// Data 1
			Write_Data_2_Display(0x00);
			// Data 2
			Write_Data_2_Display(0x05); 
			// Set Text Home Address OPCODE
			Write_Command_2_Display(0x40); 
			break;
	}
}

/**
  * Write a string to display starting at position of row.
	* Each row has 40 pixels
	* Screen has 0-39 columns and 0-15 rows by default
	* View is the screen's next buffer positions aka, 16 * 40 pixels beyond the start pixel place
  * @param key: The string to be written out on the display
  * @param column: Y position of the display
  * @param row: X position of the display
  * @param view: Which "side" that needs to be written to
  * @return void
	*/
void Write_Characters_2_DisplayPosition(char *key, unsigned char column, unsigned char row, VIEW view) {
	
	// Calculate the position based on the view, row and column
	unsigned int position =  column + 
													 (row * 40) +
													 (view * 16 * 40);
	unsigned char data = (position & 0xFF);
	unsigned char data1 = ((position >> 8) & 0xFF);
	
	// the start address for writing to
  Write_Data_2_Display(data);
  Write_Data_2_Display(data1);
  Write_Command_2_Display(0x24);
  
	// Write out the string, by incrementing ADP each time written
	size_t n = strlen(key);
  for (int i = 0; i < n; i++) {
    Write_Character_2_Display(key[i]);
  }
}

/**
  * Write a single character to the display, 
	*	also houses most characters that can be written out.
  * @param key: The string to be written out on the display
  * @return void
	*/
void Write_Character_2_Display(char key) {
	
	// Set the data to 0 by default
	unsigned char data = 0x00;
	
  // TODO: Set the rest of the characters!
  switch (key) {
  case ' ':
    data = 0x00;
    break;
  case '!':
    data = 0x01;
    break;
  case '"':
    data = 0x02;
    break;
  case '#':
    data = 0x03;
    break;
  case '$':
    data = 0x04;
    break;
  case '%':
    data = 0x05;
    break;
  case '&':
    data = 0x06;
    break;
  case '\'':
    data = 0x07;
    break;
  case '(':
    data = 0x08;
    break;
  case ')':
    data = 0x09;
    break;
  case '*':
    data = 0x0A;
    break;
  case '+':
    data = 0x0B;
    break;
  case ',':
    data = 0x0C;
    break;
  case '-':
    data = 0x0D;
    break;
  case '.':
    data = 0x0E;
    break;
  case '/':
    data = 0x0F;
    break;
// ^ First Row ^
  case '0':
    data = 0x10;
    break;
  case '1':
    data = 0x11;
    break;
  case '2':
    data = 0x12;
    break; 
  case '3':
    data = 0x13;
    break;
  case '4':
    data = 0x14;
    break;
  case '5':
    data = 0x15;
    break;
  case '6':
    data = 0x16;
    break;
  case '7':
    data = 0x17;
    break;
  case '8':
    data = 0x18;
    break;
  case '9':
    data = 0x19;
    break;
  case ':':
    data = 0x1A;
    break;
  case ';':
    data = 0x1B;
    break;
  case '<':
    data = 0x1C;
    break;
  case '=':
    data = 0x1D;
    break;
  case '>':
    data = 0x1E;
    break;
  case '?':
    data = 0x1F;
    break;
// ^ Second Row^^
  case '@':
    data = 0x20;
    break;
  case 'A':
    data = 0x21;
    break;
  case 'B':
    data = 0x22;
    break;
  case 'C':
    data = 0x23;
    break;
  case 'D':
    data = 0x24;
    break;
  case 'E':
    data = 0x25;
    break;
  case 'F':
    data = 0x26;
    break;
  case 'G':
    data = 0x27;
    break;
  case 'H':
    data = 0x28;
    break;
  case 'I':
    data = 0x29;
    break;
  case 'J':
    data = 0x2A;
    break;
  case 'K':
    data = 0x2B;
    break;
  case 'L':
    data = 0x2C;
    break;
  case 'M':
    data = 0x2D;
    break;
  case 'N':
    data = 0x2E;
    break;
  case 'O':
    data = 0x2F;
    break;
// ^ Third Row ^
  case 'P':
    data = 0x30;
    break;
  case 'Q':
    data = 0x31;
    break;
  case 'R':
    data = 0x32;
    break;
  case 'S':
    data = 0x33;
    break;
  case 'T':
    data = 0x34;
    break;
  case 'U':
    data = 0x35;
    break;
  case 'V':
    data = 0x36;
    break;
  case 'W':
    data = 0x37;
    break;
  case 'X':
    data = 0x38;
    break;
  case 'Y':
    data = 0x39;
    break;
  case 'Z':
    data = 0x3A;
    break;
  case '[':
    data = 0x3B;
    break;
  case '\\':
    data = 0x3C;
    break;
  case ']':
    data = 0x3D;
    break;
  case '^':
    data = 0x3E;
    break;
  case '_':
    data = 0x3F;
    break;
// ^ Fourth Row ^
  case 'a':
    data = 0x41;
    break;
  case 'b':
    data = 0x42;
    break;
  case 'c':
    data = 0x43;
    break;
  case 'd':
    data = 0x44;
    break;
  case 'e':
    data = 0x45;
    break;
  case 'f':
    data = 0x46;
    break;
  case 'g':
    data = 0x47;
    break;
  case 'h':
    data = 0x48;
    break;
  case 'i':
    data = 0x49;
    break;
  case 'j':
    data = 0x4A;
    break;
  case 'k':
    data = 0x4B;
    break;
  case 'l':
    data = 0x4C;
    break;
  case 'm':
    data = 0x4D;
    break;
  case 'n':
    data = 0x4E;
    break;
  case 'o':
    data = 0x4F;
    break;
// ^ Fifth Row ^
  case 'p':
    data = 0x50;
    break;
  case 'q':
    data = 0x51;
    break;
  case 'r':
    data = 0x52;
    break;
  case 's':
    data = 0x53;
    break;
  case 't':
    data = 0x54;
    break;
  case 'u':
    data = 0x55;
    break;
  case 'v':
    data = 0x56;
    break;
  case 'w':
    data = 0x57;
    break;
  case 'x':
    data = 0x58;
    break;
  case 'y':
    data = 0x59;
    break;
  case 'z':
    data = 0x5A;
    break;
  case '{':
    data = 0x5B;
    break;
  case '|':
    data = 0x5C;
    break;
  case '}':
    data = 0x5D;
    break;
  case '~':
    data = 0x5E;
    break;
// ^ Sixth Row ^
  default:
    return;
  }
	
  // Write the data, by incrementing ADP each time written
  Write_Data_2_Display(data);
  Write_Command_2_Display(0xC0);
}

/**
  * Clear the screen of characters, leave it with "spaces"
  * @return void
	*/
void Blank_Display() {
  // The start address for writing to is set to the beginning of the beginning [0,0]
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x24);

	// 1920 ~ 3 screens/views
  for (int x = 0; x < 1920; x++) {
      // Write "nothing" into each "pixel" of the screen
      Write_Data_2_Display(0x00);
      Write_Data_2_Display(0x00);
      Write_Command_2_Display(0xC0);
  }

  // The start address for writing to is set to the beginning of the beginning [0,0]
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x24);
}

/**
  * Reads the Displays status pins of the display
  * @return databus with information about the display status
	*/
unsigned char Read_Status_Display() {
  unsigned char databus;

  *AT91C_PIOC_OER = (0x1F000);
	// make databus as input
  *AT91C_PIOC_ODR = (_DISPLAY_DATABUS);

	// Set dir as input
  *AT91C_PIOC_SODR = (_DISPLAY_DIR);
	// Clear/enable output (74chip 0 = enable)
  *AT91C_PIOC_CODR = (_DISPLAY_OE);  
	// Set C/D
  *AT91C_PIOC_SODR = (_DISPLAY_CD);  
	// Clear chip select display CE
  *AT91C_PIOC_CODR = (_DISPLAY_CE);  
	// Clear read display
  *AT91C_PIOC_CODR = (_DISPLAY_RD); 
	// Make a Delay
  Delay(25);               
	// Read data bus and save it in databus
  databus = (*AT91C_PIOC_PDSR &
          (_DISPLAY_DATABUS));    
	// Set chip select display
  *AT91C_PIOC_SODR = (_DISPLAY_CE);  
	// Set read display
  *AT91C_PIOC_SODR = (_DISPLAY_RD);  
	// Disable output (74chip)
  *AT91C_PIOC_SODR = (_DISPLAY_OE);  
	// Set dir as output (74chip)
  *AT91C_PIOC_CODR = (_DISPLAY_DIR); 
	
  return databus;
}

/**
  * Sends the OPCODE to the displays chip todo a 
	*	command such as move the adress pointer and so on
  * @param command: The OPCODE to be written to the display for use
  * @return void
	*/
void Write_Command_2_Display(unsigned char command) {
	
  // Wait until Read_Status_Display returns an OK
  while ((~Read_Status_Display() & (0xC)) == 0xC);

	// make Command pins as input
  *AT91C_PIOC_OER = (0x2F000);       
	// make databus as input
  *AT91C_PIOC_OER = (_DISPLAY_DATABUS); 

	// Clear databus
  *AT91C_PIOC_CODR = (_DISPLAY_DATABUS); 
	// Set Command to databus PC(2-9)
  *AT91C_PIOC_SODR = (command << 2); 
	// Set dir as output (74chip)
  *AT91C_PIOC_CODR = (_DISPLAY_DIR);    
	// Enable 'output' (74chip)
  *AT91C_PIOC_CODR = (_DISPLAY_OE);     
	// Set databus as output
  *AT91C_PIOC_OER = (_DISPLAY_DATABUS); 
	// Set C/D signal High (1 = Command) //CD
  *AT91C_PIOC_SODR = (_DISPLAY_CD); 
	// Clear chip select display
  *AT91C_PIOC_CODR = (_DISPLAY_CE);     
	// Clear write display
  *AT91C_PIOC_CODR = (_DISPLAY_WR);    
	// Make a Delay
  Delay(25);                        
	// Set chip enable display
  *AT91C_PIOC_SODR = (_DISPLAY_CE);
	// Set write display
  *AT91C_PIOC_SODR = (_DISPLAY_WR);     
	// Disable output (74chip)
  *AT91C_PIOC_SODR = (_DISPLAY_OE);     
	// Make databus as input
  *AT91C_PIOC_ODR = (_DISPLAY_DATABUS); 
}

/**
  * Sends the DATA to the displays chip todo a 
	*	command with this data such as move the adress pointer too data point
  * @param data: The DATA to be written to the display for use
  * @return void
	*/
void Write_Data_2_Display(unsigned char data) {
  // Wait until Read_Status_Display returns an OK
  while ((~Read_Status_Display() & (0xC)) == 0xC);

	// Set databus as output
  *AT91C_PIOC_OER = (0x2F000);          
  *AT91C_PIOC_OER = (_DISPLAY_DATABUS); 

	// Clear databus
  *AT91C_PIOC_CODR = (_DISPLAY_DATABUS); 
	// Set "data" to databus
  *AT91C_PIOC_SODR = (data << 2);       
	// Set dir as output (74chip)
  *AT91C_PIOC_CODR = (_DISPLAY_DIR);     
	// Enable 'output' (74chip)
  *AT91C_PIOC_CODR = (_DISPLAY_OE);     
	// Set databus as output
  *AT91C_PIOC_OER = (_DISPLAY_DATABUS);  
	// Set C/D signal Low (0 = data) //CD Low
  *AT91C_PIOC_CODR = (_DISPLAY_CD); 
  // Clear chip select display              
  *AT91C_PIOC_CODR = (_DISPLAY_CE);     
	// Clear write display
  *AT91C_PIOC_CODR = (_DISPLAY_WR);     
	// Make a Delay
  Delay(25);                           
	// Set chip enable display
  *AT91C_PIOC_SODR = (_DISPLAY_CE);   
	// Set write display
  *AT91C_PIOC_SODR = (_DISPLAY_WR);     
	// Disable output (74chip)
  *AT91C_PIOC_SODR = (_DISPLAY_OE);     
	// Make databus as input
  *AT91C_PIOC_ODR = (_DISPLAY_DATABUS); 
}

/**
  * Initialize all the pins and default settings of the display
  * @return void
	*/
void Init_Display() {
  // Activating power for peripheral clocks [Power Management Clock] [Peripheral Clock Enable register]
  *AT91C_PMC_PCER = (0x6000); 
	
	// Peripheral I/O [Peripheral/Pin Enable Register]
  *AT91C_PIOC_PER = (0xFFF3FC);
  *AT91C_PIOD_PER = (_DISPLAY_RESET); 

	// Disable the inner resistor of the pin handler (always disable to conserve power) 
  *AT91C_PIOC_PPUDR = (0xFFF3FC);       
  *AT91C_PIOD_PPUDR = (_DISPLAY_RESET); 

	// Turn the pin to an output "channel" [Output Enable register]
  *AT91C_PIOD_OER = (_DISPLAY_RESET);
  *AT91C_PIOC_OER = (_DISPLAY_FS); 
  *AT91C_PIOC_OER = (_DISPLAY_RV); 
	
	// Set/Clear specific bits [Set/Clear Output Data Register] 
  *AT91C_PIOC_SODR = (_DISPLAY_FS);
  *AT91C_PIOC_CODR = (_DISPLAY_RV);

	// Turn the pin to an output "channel" [Output Enable register]
  *AT91C_PIOC_OER = (AT91C_PIO_PC12); // (1 << 12)
  *AT91C_PIOC_OER = (AT91C_PIO_PC13);

	// Reset the display
  *AT91C_PIOD_CODR = (_DISPLAY_RESET);
  Delay(25);
  *AT91C_PIOD_SODR = (_DISPLAY_RESET);

	// Send in D1, D2 and then the OPCODE
	// Set text home address
  Write_Data_2_Display(0x00); // D1
  Write_Data_2_Display(0x00); // D2
  Write_Command_2_Display(0x40); // OPCODE
	// Set graphic home address
  Write_Data_2_Display(0x00); // D1
  Write_Data_2_Display(0x40); // D2
  Write_Command_2_Display(0x42);  // OPCODE
	// Set text area
  Write_Data_2_Display(0x28); // D1
  Write_Data_2_Display(0x00); // D2
  Write_Command_2_Display(0x41);  // OPCODE
	// Set graphic area
  Write_Data_2_Display(0x1e); // D1
  Write_Data_2_Display(0x00); // D2
  Write_Command_2_Display(0x43);  // OPCODE
	// text mode
  Write_Command_2_Display(0x80);  // OPCODE
	// Text on graphic off
  Write_Command_2_Display(0x94);  // OPCODE

	// Clear the screen of the junk that it "arrives" with
  Blank_Display();
}