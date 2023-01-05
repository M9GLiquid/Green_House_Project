#include "main.h"

// Global Variables
unsigned int DATE_REGISTER = 0x0;
unsigned int TIME_REGISTER = 0x0;
DateNode *dateList = NULL;
TimeNode *timeList = NULL;
unsigned int time = 0;
unsigned short booleanFlagSet = 0;
unsigned short TICKS = 1000;

// Local Variables
unsigned int darkCounter = 0;
unsigned int sunCounter = 0;
short temperature;

int main(void) {
	// Setup all the pins and configs of all the components needed
  config(); 
	// Start initial View
	view_select_date();
	// reset the darkCounter and sunCounter
	darkCounter = sunCounter = 0;
	
	// Setup the 7 days so that we know we don't run out of memory for them
	for (int i = 0; i < 7; i++)
  	Insert_First(&dateList, Create_DateNode(&dateList, &timeList, DATE_REGISTER));
	
	// Read the initial temperature so the first value isn't 0'c
	temperature = Read_Temp();
	while(1){
		// Check for a time update
		if (Get_Boolean_Flag(NEW_SECOND) == 1)
			update_every_second();
		else if (Get_Boolean_Flag(NEW_MINUTE) == 1)
			update_every_minute();
		else if (Get_Boolean_Flag(NEW_HOUR) == 1)
			update_every_hour();
		else if (Get_Boolean_Flag(NEW_DAY) == 1)
			update_every_day();
		else if (Get_Boolean_Flag(NEW_MONTH) == 1)
			update_every_month();
		else if (Get_Boolean_Flag(NEW_YEAR) == 1)
			update_every_year();
		
		// Check for keypress associated with menu
		menu_selection();
	}
}

/**
	* Function to handle everything that must happen every second
	*/
void update_every_second(){
	// Update time once a second
	count_time();
	// Read the light
	Read_Light();
		
	// if 8 hours of darkness in the day has passed
	if ((darkCounter / 3600) >= 8)
		Sunlamp();
	// Stuff to happen every "real" second
	if (time >= 1000){
		temperature = Read_Temp();
		Alarm();
		// If we are faster than one cycle we need to get back the proper time
		time %= 1000;
	}
	
	// Set the boolean NEW_SECOND to false
	Set_Boolean_Flag(0, NEW_SECOND);
}

/**
	* Function to handle everything that must happen every minute
	*/
void update_every_minute(){
	unsigned int save = 0x0;
	// Set the hours and minutes aswell as the temperature to the save variable
	// Bytes correspond to -> 0xhhmmTTTT
	Set_2_Bytes(&save, Get_2_Bytes(&TIME_REGISTER, HOURS), DAY);
	Set_2_Bytes(&save, Get_2_Bytes(&TIME_REGISTER, MINUTES), MONTH);
	Set_4_Signed_Bytes(&save, temperature, 1);
	// Add a new temperature measure to the list
  putFirst(&timeList, create_timeNode(&timeList, save));
	// Display the sun degree's on display
	Display_Sundegree_2_Display(darkCounter, sunCounter);	
	// Set the boolean NEW_MINUTE to false
	Set_Boolean_Flag(0, NEW_MINUTE);
}

/**
	* Function to handle everything that must happen every hour
	*/
void update_every_hour(){
	// Set the boolean NEW_HOUR to false
	Set_Boolean_Flag(0, NEW_HOUR);
}

/**
	* Function to handle everything that must happen every day
	*/
void update_every_day(){
	// Reset the Counters to start counting for the new day
	darkCounter = sunCounter = 0;
	
	// Set the timelist with temperatures into the datelist (Day)
  Insert_First(&dateList, Create_DateNode(&dateList, &timeList, DATE_REGISTER));
	
	// Display the everyday records if we are on that view
	if (Get_Boolean_Flag(VIEW_RECORDS) == 1)
		Display_Everyday_Record();
	
	// Set the boolean NEW_DAY to false
	Set_Boolean_Flag(0, NEW_DAY);
}

/**
	* Function to handle everything that must happen every month
	*/
void update_every_month(){
	// Set the boolean NEW_MONTH to false
	Set_Boolean_Flag(0, NEW_MONTH);
}

/**
	* Function to handle everything that must happen every year
	*/
void update_every_year(){
	// Set the boolean NEW_YEAR to false
	Set_Boolean_Flag(0, NEW_YEAR);
}

/**
  * Setup all the initial settings such as pins
  * @return void
	*/
void config() {
  SystemInit();
  SysTick_Config((int) (SystemCoreClock * 0.001)); // 1 ms Initiate Pulse (0.001)
	Init_Keypad();
  Init_Display();
  Init_Temp();
  Init_LightSensor();
  Init_Servo_Motor();
	Init_Light_LED();
}

/**
  * a function to delay [x] ns, 
	*	not exact science without checking with electric tools
  * @param value: The amount of ns to delay
  * @return void
	*/
void Delay(int value) {
  for (int i = 0; i < value; i++)
    __asm("nop"); 
	// asm() Doesn't work in newer versions of c, c99 does not
  // support asm(); command
}

/**
  * An interrupt that activates every ms
  * @return void
	*/
void SysTick_Handler() { 
	time++; 
	
	// Placed in SysTick_Handler because of the speed(precision) needed...
	if ((time % TICKS) == 0){
		// Increment the seconds
		Increment_2_Bytes(&TIME_REGISTER, SECONDS);
		// We have a new second
		Set_Boolean_Flag(1, NEW_SECOND);
		// Increment corresponding counter dependent on if we have light or not
		if (Get_Boolean_Flag(NO_LIGHT) == 1)
			darkCounter++;
		else
			sunCounter++;
	}
}

/**
  * Set a specific boolean flag (Bit)
  * @param flag: the bit that needs to be set
  * @return void
	*/
void Set_Boolean_Flag(char x, FLAG flag){
	 booleanFlagSet = (booleanFlagSet & ~(1 << flag)) | (x << flag);
}

/**
  * Get a specific boolean flag (Bit)
  * @param flag: the bit that needs to be retrieved
  * @return the bit's value
	*/
char Get_Boolean_Flag(FLAG flag){
	if (booleanFlagSet & (1 << flag))
		return 1;
	return 0;
}
