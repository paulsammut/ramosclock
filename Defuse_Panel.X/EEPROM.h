#ifndef _EEPROM
#define _EEPROM

#include <p18f45k20.h>

/**
 * Reads and returns the EEPROM byte value at the address given in "address".
 * @param memAddress Address to read from. 0-255
 * @return Data in the address
 */
unsigned char EEPROM_Read(unsigned char memAddress);

/**
 * Writes the "databyte" value to EEPROM at the address given location in "address".
 * @param memAddress Address to write to. 0-255
 * @param databyte
 */
void EEPROM_Write(unsigned char memAddress, unsigned char databyte);

#endif _EEPROM