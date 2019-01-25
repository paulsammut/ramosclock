#ifndef _EEPROM
#define _EEPROM

#include <p18f45k20.h>
#include "Constructs.h"

#define EEPROM_READ_FLAG_MEM_ADR 0xFF
#define EEPROM_READ_FLAG_BEENREAD 42

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

/**
 * Writes the setting options for the clock that are passed in to the non-volatile EEPROM.
 * @param EEPROM_settings The clock options
 * @param EEPROM_addr0 RF Addr0 of the clock for RAWRPI stuff
 * @param EEPROM_addr1 RF Addr1 of the clock for RAWRPI stuff
 */
void EEPROM_writeSettings(unsigned char* EEPROM_settings, unsigned char* EEPROM_addr0,
        unsigned char* EEPROM_addr1, unsigned char *alarmHours, unsigned char *alarmMins);

/**
 * Reads the clock settings from the EEPROM. Used to set the clock options after a reboot.
 * @param EEPROM_settings Clock settings
 * @param EEPROM_addr0 RF Addr0 of the clock for RAWRPI stuff
 * @param EEPROM_addr1 RF Addr1 of the clock for RAWRPI stuff
 */
void EEPROM_readSettings(unsigned char* EEPROM_settings, unsigned char* EEPROM_addr0,
        unsigned char* EEPROM_addr1, unsigned char *alarmHours, unsigned char *alarmMins);


/**
 * Returns 1 if the EEPROM has been read before. 0 if it has never been read.
 * @return
 */
unsigned char EEPROM_isFresh(void);

#endif _EEPROM