#include "byte_manipulator.h"

/**
  * Set 1 specific byte at a specific position in a unsigned integer
  * binary wise
  * @param custom_register: the int to be changed
  * @param byte: the byte to be added to the register integer
  * @param position: position in hexadecimal ( 1 steps at a time )
  * @return void
  */
void Set_1_Byte(unsigned int *custom_register, unsigned char byte, unsigned char position) {
  if (position > 7)
    return;
	
  position = (7 - position);
  //Create a temporary integer to activate a specific byte for the next step.
  unsigned int byte_check = (0xF) << (4 * position);
  //Clear the specific byte in the value integer
  *custom_register &= ~(byte_check);
  //Insert the number in the custom_register without changing the rest of the bytes.
  *custom_register |= (byte & 0x0F) << (4 * position);
}

/**
  * Set 2 specific bytes at a specific position in a unsigned integer
  * binary wise
  * @param custom_register: the int to be changed
  * @param bytes: the bytes to be added to the register integer
  * @param position: position in hexadecimal ( 2 steps at a time )
  * @return void
  */
void Set_2_Bytes(unsigned int *custom_register, unsigned char bytes, unsigned char position) {
  if (position > 7)
    return;
	
  char string[3];
  snprintf(string, 3, "%02d", bytes);
  Set_1_Byte(custom_register, string[0], (position));
  Set_1_Byte(custom_register, string[1], (position + 1));
}

/**
  * Set 4 specific bytes at a specific position in a unsigned integer
  * binary wise
  * @param custom_register: the int to be changed
  * @param bytes: the bytes to be added to the register integer
  * @param position: position in hexadecimal ( 4 steps at a time )
  * @return void
  */
void Set_4_Bytes(unsigned int *custom_register, unsigned short bytes, unsigned char position) {
  if (position > 7) 
    return;
  
  char string[5];
  snprintf(string, 5, "%04d", bytes);
  for (int i = 3; i >= 0; i--)
    Set_1_Byte(custom_register, string[i], (4*position) + i);
}

/**
  * Set 4 specific bytes at a specific position in a unsigned integer
  * binary wise and with a byte represent if the number is signed
  * @param custom_register: the int to be changed
  * @param bytes: the bytes to be added to the register integer
  * @param position: position in hexadecimal ( 4 steps at a time )
  * @return void
	*/
void Set_4_Signed_Bytes(unsigned int *custom_register, short bytes, unsigned char position) {
    if (position > 7) 
        return;
    char string[5];
    snprintf(string, 5, "%04d", bytes);
    for (int i = 3; i >= 0; i--) {
        if(string[i] == '-')
            string[i] = 1;
        Set_1_Byte(custom_register, string[i], (4 * position) + i);
    }
}

/**
  * Get 1 specific byte from an integer and convert it into the raw 
	* decimal number
  * @param custom_register the byte holder to get the value from
  * @param position from where in the byte holder we collect our byte
  * @return an unsigned char of the bytes raw value
  */
unsigned char Get_1_Byte(unsigned int *custom_register, unsigned char position) {
  position = 7 - position;
  // Turn hexadecimal to decimal without conversion
  unsigned char temp = ((0xF) & (*custom_register >> ((position) * 4)));
  return temp;
}

/**
  * Get 1 specific byte from an integer and convert it into the raw 
	* decimal number
  * @param custom_register the byte holder to get the value from
  * @param position from where in the byte holder we collect our 2 bytes
  * @return an unsigned char of the 2 bytes raw value
  */
unsigned char Get_2_Bytes(unsigned int *custom_register, unsigned char position) {
  position = (6 - position);
  
  // Turn 2 hexadecimal to decimal without conversion
  unsigned char temp = ((0xF) & (*custom_register >> ((position + 1) * 4))) * 10;
  temp += ((0xF) & (*custom_register >> ((position) * 4)));
  return temp;
}

/**
  * Get 1 specific byte from an integer and convert it into the raw 
	* decimal number
  * @param custom_register the byte holder to get the value from
  * @param position from where in the byte holder we collect our 4 bytes
  * @return an unsigned short of the 4 bytes raw unsigned value
  */
unsigned short Get_4_Bytes(unsigned int *custom_register, unsigned char position) {
  position = 4 - (position * 4);
  
  // Turn 4 hexadecimal to decimal without conversion
  unsigned short temp = 0;
  for (int i = 0; i <= 3; i++)
    temp += ((0xF) & (*custom_register >> (((position) + i) * 4))) * ((unsigned short) pow(10, i));
  return temp;
}

/**
  * Get 1 specific byte from an integer and convert it into the raw 
	* decimal number
  * @param custom_register the byte holder to get the value from
  * @param position from where in the byte holder we collect our 4 bytes
  * @return an unsigned short of the 3 bytes raw signed value
  */
short Get_4_Signed_Bytes(unsigned int *custom_register, unsigned char position) {
    position = 4 - (position * 4);

    // Turn 4 hexadecimal to decimal without conversion
    short temp = 0;
    for (int i = 0; i <= 2; i++)
        temp += ((0xF) & (*custom_register >> (((position) + i) * 4))) *
                ((unsigned short)pow(10, i));
    if((Get_1_Byte(custom_register,position+4) == 1))
        temp *= -1;
    return temp;
}

/**
  * Increment 2 bytes total raw value by 1
  * @param custom_register the byte holder to get the value from
  * @param position from where in the byte holder we collect our 4 bytes
  * @return void
	*/
void Increment_2_Bytes(unsigned int *custom_register, unsigned char position){
  Set_2_Bytes(custom_register, (Get_2_Bytes(custom_register, position) + 1), position);
}

/**
  * Increment 4 bytes total raw value by 1
  * @param custom_register the byte holder to get the value from
  * @param position from where in the byte holder we collect our 4 bytes
  * @return void
	*/
void Increment_4_Bytes(unsigned int *custom_register, unsigned char position){
  Set_4_Bytes(custom_register, (Get_4_Bytes(custom_register, position) + 1), position);
}


