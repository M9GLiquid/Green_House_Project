#include "light_LED.h"

/**
  * Initialize the LED lights pins
  * @return void
	*/
void Init_Light_LED(){
	// Enable Power management clock for PIOA (11) & PIOD (14)
	*AT91C_PMC_PCER = (0x9000);
	// Enable PIO pin needed for Sun lamp
	*AT91C_PIOD_PER = (AT91C_PIO_PD3);
	// Enable PIO pin needed for Alarm lamp
	*AT91C_PIOA_PER = (AT91C_PIO_PA7);
	// Enable PIO pin needed as output for Sun lamp
  *AT91C_PIOD_OER = (AT91C_PIO_PD3);
	// Enable PIO pin needed as output for Alarm lamp
  *AT91C_PIOA_OER = (AT91C_PIO_PA7);
	// Disable the inner resistor of the pin handler (always disable to conserve power) for the Sun lamp
	*AT91C_PIOD_PPUDR = (AT91C_PIO_PD3);
	// Enable the inner resistor of the pin handler for the Alarm lamp
	*AT91C_PIOA_PPUDR = (AT91C_PIO_PA7);
}


/**
  * Turn on/off the sun lamp LED
  * @return void
	*/
void Sunlamp(){
	// Check  whether the sunlamp is needed to be on
	if ((Get_Boolean_Flag(SUN_LAMP) == 1) && (Get_Boolean_Flag(NO_LIGHT) == 0))
		return;

	// There is no light available
	if (Get_Boolean_Flag(NO_LIGHT) == 1)
  	*AT91C_PIOD_SODR = (AT91C_PIO_PD3);
	else
  	*AT91C_PIOD_CODR = (AT91C_PIO_PD3);
}

/**
  * Display the Sun lamp active in hours
	* Display the Sun Light duration in hours
	*	Display the No light duration in hours
  * @param no_light: No sunlight, calculated in seconds
  * @param sunlight: Sunlight, calculated in seconds
  * @return void
	*/
void Display_Sundegree_2_Display(int no_light, int sunlight){
	// Calculate the amount of hours the sun lamp has been active
	unsigned char sunLampCounter = (unsigned char)(no_light / 3600);
	// Calculate amount of hours there have been no light on the sensors
	no_light = (no_light / 3600);
	// Calculate amount of hours there have been light on the sensors
	sunlight /= 3600;
	// Just make sure that the calculation doesn't fall below 0 and only active after 8 hours
	if (sunLampCounter < 9)
		sunLampCounter = 0;
	else
		sunLampCounter -= 8;
	
	// Write out the different informations to the Display
	char string[17];
	
	snprintf(string, 18, "%2d%s", sunlight, "h of Sun Light");
	Write_Characters_2_DisplayPosition(string, 0, 13, _VIEW_MENU);
	
	snprintf(string, 16, "%2d%s", no_light, "h of No Light");
	Write_Characters_2_DisplayPosition(string, 0, 144, _VIEW_MENU);
	
	snprintf(string, 16, "%2d%s", sunLampCounter, "h of Sun Lamp");
	Write_Characters_2_DisplayPosition(string, 0, 15, _VIEW_MENU);
}