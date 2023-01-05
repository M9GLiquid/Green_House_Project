#ifndef BYTE_MANIPULATOR_H
  #define BYTE_MANIPULATOR_H

	// Includes
	#include <math.h>
	#include <stdio.h>

	// Functions
  void Set_1_Byte(unsigned int *custom_register, unsigned char byte, unsigned char position);
  void Set_2_Bytes(unsigned int *custom_register, unsigned char bytes, unsigned char position);
  void Set_4_Bytes(unsigned int *custom_register, unsigned short bytes, unsigned char position);
	void Set_4_Signed_Bytes(unsigned int *custom_register, short bytes, unsigned char position);
  unsigned char Get_1_Byte(unsigned int *custom_register, unsigned char position);
	unsigned char Get_2_Bytes(unsigned int *custom_register, unsigned char position);
  unsigned short Get_4_Bytes(unsigned int *custom_register, unsigned char position);
	short Get_4_Signed_Bytes(unsigned int *custom_register, unsigned char position);
	void Increment_2_Bytes(unsigned int *custom_register, unsigned char position);
	void Increment_4_Bytes(unsigned int *custom_register, unsigned char position);
	
	// Enums
	typedef enum position{
		DAY = 0,
		MONTH = 2,
		YEAR = 1,
		SECONDS = 6,
		MINUTES = 4,
		HOURS = 2		
	}POSITION;
#endif