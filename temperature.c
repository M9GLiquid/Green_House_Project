#include "temperature.h"

/**
  * Initialize the pins for Temperature measurements
  * @return void
	*/
void Init_Temp() {
	// Enable Power management clock for PIOB
  *AT91C_PMC_PCER = (AT91C_ID_PIOB);   
	// Enable PIO pin needed 
  *AT91C_PIOB_PER = (AT91C_PIO_PB25); 
	// Enable TC0 clocks
  *AT91C_PMC_PCER = (1 << AT91C_ID_TC0); 
	// Capture mode for Timer_Clock1 (Value = 0)
  *AT91C_TC0_CMR = (AT91C_TC_CLKS_TIMER_DIV1_CLOCK); 
	// Enable Clock and do a software trigger
  *AT91C_TC0_CCR = (AT91C_TC_SWTRG | AT91C_TC_CLKEN);
	// Enable "waiting" for a falling edge on LDRA
  *AT91C_TC0_CMR = (AT91C_TC_LDRA_FALLING);
	// Also enable "waiting" for a rising edge on LDRB
  *AT91C_TC0_CMR = (*AT91C_TC0_CMR | (1 << 18));
	// Enable PIO pin needed as output
  *AT91C_PIOB_OER = (AT91C_PIO_PB25); 
	// ###
	// Wait for RESET pulse to complete
	while (time < 17); 
  time = 0;
	// Disable PIO pin needed as output
  *AT91C_PIOB_ODR = (AT91C_PIO_PB25); 
	// ###
	
	// Enable corresponding NVIC
  NVIC_EnableIRQ((IRQn_Type)27);
  NVIC_ClearPendingIRQ((IRQn_Type)27);
  // NVIC_SetPriority((IRQn_Type)27, 2);
	
	// Enable interrupt for LDRBS
  *AT91C_TC0_IER = (AT91C_TC_LDRBS); 
	Temp_Mesurement();
}

/**
  * Start up a temperature measure
  * @return void
	*/
void Temp_Mesurement() {
	// ###
	// Send a START pulse
	// Enable PIO pin needed as output
  *AT91C_PIOB_OER = (AT91C_PIO_PB25); 
  Delay(25);
	// Send a bit in pin
  *AT91C_PIOB_SODR = (AT91C_PIO_PB25);
	// Disable PIO pin needed as output
  *AT91C_PIOB_ODR = (AT91C_PIO_PB25); 
	// Clear a bit in pin
  *AT91C_PIOB_CODR = (AT91C_PIO_PB25);
  Delay(25);
	// ###
	
	// Set TC_RISING_EDGE flag to 0
	Set_Boolean_Flag(0, TC_RISING_EDGE);
	// Do a software trigger
  *AT91C_TC0_CCR = (AT91C_TC_SWTRG);
	// Enable interrupt for LDRBS
  *AT91C_TC0_IER = (AT91C_TC_LDRBS); 
}

/**
  * Timer Counter Interrupt that activates whenever there is a new value ready
  * @return void
	*/
void TC0_Handler() {
	// Disable interrupt for LDRBS
  *AT91C_TC0_IDR = (AT91C_TC_LDRBS);
	// Set TC_RISING_EDGE flag to 1
	Set_Boolean_Flag(1, TC_RISING_EDGE);
	// Read and clear.
	*AT91C_TC0_SR; 
}

/**
  * Read the temperature
  * @return void
	*/
short Read_Temp() {
	// Wait for an interrupt
	if (Get_Boolean_Flag(TC_RISING_EDGE) == 0)
    return -300;
	
  short temperature = 0; 
	// ###
	// Calculate the temperature measurement based on the value received
	int ra = *AT91C_TC0_RA;
	int rb = *AT91C_TC0_RB;
  int tempDifference = (rb - ra);
	// 42 from MCK/2
  temperature = (int) ((tempDifference / (42*5)) - 273.15); 
	// ###
	
	// Set TEMP_ALARM flag to true if temperature falls outside the preset intervalls
  if (temperature > maximum_limit || temperature < minimum_limit)
		Set_Boolean_Flag(1, TEMP_ALARM);
	
	// Display current temperature
	Display_Temp(temperature);
	
	// Prepaire a new temperature reading
  Temp_Mesurement();
	
	return temperature;
}

/**
  * Display the temperature on Display
  * @param temperature: The temperature to be displayed
  * @return void
	*/
void Display_Temp(short temperature){
  char string[21];
	Write_Characters_2_DisplayPosition("Temperature:       ", 0, 1, _VIEW_MENU);
	snprintf(string, 22, "%02d%s", temperature, "'c");
	Write_Characters_2_DisplayPosition(string, 14, 1, _VIEW_MENU);
}
