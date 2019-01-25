#include "EEPROM.h"

// These two functions read/write one byte to the EEPROM. Taken from the examples on the C18 library
// 7-12-12
unsigned char EEPROM_Read(unsigned char memAddress) { // reads and returns the EEPROM byte value at the address given
    // given in "address".
    EECON1bits.EEPGD = 0; // Set toaccessEEPROMmemory
    EECON1bits.CFGS = 0; // Do notaccessConfigregisters
    EEADR = memAddress; //Load EEADRwith address of location to write.
    // execute the read
    EECON1bits.RD = 1; //Set the RDbit to execute the EEPROM read
    //The value read is ready the next instruction cycle in EEDATA. No wait is
    //needed.

    return EEDATA;
}

void EEPROM_Write(unsigned char memAddress, unsigned char databyte) { // writes the "databyte" value to EEPROM at the address given
    // location in "address".

    EECON1bits.EEPGD = 0; // Set to access EEPROM memory
    EECON1bits.CFGS = 0; // Do not access Config registers
    EEDATA = databyte; // Load EEDATA with byte to be written
    EEADR = memAddress; // Load EEADR with address of location to write.
    EECON1bits.WREN = 1; // Enable writing
    INTCONbits.GIE = 0; // Disable interrupts
    EECON2 = 0x55; // Begin Write sequence
    EECON2 = 0xAA;
    EECON1bits.WR = 1; // Set WR bit to begin EEPROM write
    INTCONbits.GIE = 1; // re-enable interrupts
    while (EECON1bits.WR == 1) { // wait for write to complete.
    };
    EECON1bits.WREN = 0;
}
