#include "light_sensor.h"

/**
  * Write multiple characters to the display to be shown
  * @param key: The string to be written out on the display
  * @return void
	*/
void Init_LightSensor(){
	// Enable Power Management Controller for PIOA clock
  *AT91C_PMC_PCER = (1 << AT91C_ID_PIOA); 
	// Start clock for ADC_Clock (37)
  *AT91C_PMC_PCER1 = (1 << 5); 
	// Enable PIN A27
  *AT91C_PIOA_PER = (AT91C_PIO_PA27);
	// Disable the pullup to save on energy
  *AT91C_PIOA_PPUDR = (AT91C_PIO_PA27);
	
	// Set the prescaler to 2 in ADC_MR->ADCClock = 14MHz
	// ADCClock = 84000000 / ( (PRESCAL+1) * 2 ) == 14 000 000 => PRESCAL = 2, (1 << 9). 
  *AT91C_ADCC_MR= (1 << 9);   
  

  *AT91C_ADCC_CHER = (0x6); // Enable (ADC) Channel 1 & 2
	// Setup the Nested Vector Interrupt Control
  NVIC_ClearPendingIRQ((IRQn_Type) 37);
  NVIC_SetPriority((IRQn_Type) 37, 1);
  NVIC_EnableIRQ((IRQn_Type) 37);
	
	// Start a measurement
  Light_Measurement();
} 

/**
  * Setup a new measurement for the light sensors
  * @return void
	*/
void Light_Measurement(){
	// Start a analog to digital convertion
  *AT91C_ADCC_CR = (1 << 1); 
	// reset boolean flag ADC Light Sensor 
	Set_Boolean_Flag(0, LIGHT_SENSORS); 
	
	// Clear the old values
  *AT91C_ADCC_SR; 
	
	// Enable interrupt
  *AT91C_ADCC_IER = (1 << 1); 
}

/**
  * Analog Digital Converter Interrupt
	*	A Analog signal has been converted into a digital 
	*	signal for us to work with and an interrupt has happened
  * @return void
	*/
void ADC_Handler(){
	// Set boolean flag for ADC Light Sensor
	Set_Boolean_Flag(1, LIGHT_SENSORS);  
	// Disable interrupt for ADC
  *AT91C_ADCC_IDR = (1 << 1); 
}

/**
  * Read the current light level on both of the light sensors
  * @return void
	*/
void Read_Light(){	
	// Check if an interrupt has happened
  if (Get_Boolean_Flag(LIGHT_SENSORS) != 1)
		return;
	
	// Prepaire a new reading
  Light_Measurement();
	
	float cdr1 = ((*AT91C_ADCC_CDR1 * 3.3)/0xF);
	float cdr2 = ((*AT91C_ADCC_CDR2 * 3.3)/0xF);
	
	// If we fall outside of "daylight" range, aka no light set the boolean flag
	if ((cdr1 + cdr2) > 650)
  	Set_Boolean_Flag(1, NO_LIGHT);
	else
  	Set_Boolean_Flag(0, NO_LIGHT);
	
  int lightCDR = 0;
	// Calculate the where most light is coming from, positive represent sensor 1 negative sensor 2
  lightCDR = (int) (cdr1 - cdr2);
	
	// Max degrees is 90 and Min is -90
	if (lightCDR > 90)
		lightCDR = 90;
	if (lightCDR < -90)
		lightCDR = -90;
	
	// Re-structure value to between 0 and 180 degrees instead of (-90 and 90)
	lightCDR = (int) (fabs((-90) - lightCDR));
	// Move the Motorised Servo to corresponding light source
	Move_Servo(lightCDR);
	
	// Display the position on the display
	Display_Light_Position((unsigned char) lightCDR);
	
}

/**
	* Function to display the lights position
	*/
void Display_Light_Position(unsigned char light){
	char string[15];
  snprintf(string, 16, "%02d %s", light, "Sun degrees");
	Write_Characters_2_DisplayPosition(string, 0, 0, _VIEW_MENU);
}