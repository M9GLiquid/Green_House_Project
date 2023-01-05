#include "servo_motor.h"


/**
  * Initialize the servo motors pins
  * @param key: The string to be written out on the display
  * @return void
	*/
void Init_Servo_Motor(){
	// Enable Power management controller for PIOB clock
  *AT91C_PMC_PCER = (AT91C_ID_PIOB); // Enable PMC
   // Let peripheral control the pin REG_PIOB_PDR
  *AT91C_PIOB_PDR = (AT91C_PIO_PB17);
  // Activate peripheral B to control the pin
  *AT91C_PIOB_ABMR = (AT91C_PIO_PB17); 
	// Enable Power management controller for Pulse Width Modulation Controller (PWM) clock
  *AT91C_PMC_PCER1 = (1 << 4); 
	// CHID1 AT91C_PWMC_CPRE_MCK_DIV_32
  *AT91C_PWMC_ENA = (1 << 1); 
  *AT91C_PWMC_CH1_CMR = (AT91C_PWMC_CPRE_MCK_DIV_32);
	// 20ms [84 000 000 HZ / 32 * 20 ((1/frek) = period]
  *AT91C_PWMC_CH1_CPRDR = (52500); 
  *AT91C_PWMC_CH1_CDTYR = (1300); 
}

/**
  * Move the servo according to the pulse change
	* 180 Degrees [6200] - 0 Degrees [1300]
  * @param degree: The degree to move the servo motor
  * @return void
	*/
void Move_Servo(int degree){
	// Update the duty cycle to match what we need for the servo motor
  *AT91C_PWMC_CH1_CDTYUPDR = (int)(1300 + 27.2 * degree); 
}