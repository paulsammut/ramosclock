#ifndef _DEFUSEPANEL_SYS_H
#define _DEFUSEPANEL_SYS_H

#include "keypad.h"
#include <delays.h>
#include "CC1101_master.h"
#include <timers.h>
#include <spi.h>
#include "lightPlay.h"
#include <p18f45k20.h>
#include "RAWRPI.h"
#include "math.h"
#include "EEPROM.h"
#include <stdlib.h>

/** TRIS definition for the RGB Light **/
#define TRIS_Blue TRISEbits.RE0 //Blue actlow
#define TRIS_Green TRISEbits.RE1 //Green actlow
#define TRIS_Red TRISEbits.RE2 //Red light ActLow, has 39 ohm clim res


/** latch input definitions for the RGB Light **/
#define Blue LATEbits.LATE0 //Blue actlow
#define Green LATEbits.LATE1 //Green actlow
#define Red LATEbits.LATE2 //Blue actlow

/* Timer flag */
#define TIMER0_FLAG INTCONbits.TMR0IF

/** Mem Locations for EEPROM*/
#define MEM_SYS_ADDR1 100
#define MEM_SYS_ADDR0 101

/* Commands */
#define CMD_RANGECHECK  1
#define CMD_DEFUSECODE  2
#define CMD_ADDRTRAIN   3
#define CMD_RESENT      4

/* Codes */
#define CODE_ADDRTRAIN 10938 

enum panelState {
    STARCODEENTRY,
    ADDRESSENTRY,
    RANGECHECK,
    DEFUSECODEENTRY
};

/**
 * Initializes the sleep stuff and other system stuff
 */
void initDefusePanel(void);

/**
 * Go to sleep 
 */
void enterSleep(void);

/**
 * Does the battery checks
 */
void checkBattery(void);

/**
 * Runs the code that checks if we should send the defuse panel to sleep
 */
void shutOffTickTock(void);

/**
 * Resets the turn off counter
 */
void resetTickTock(void);

/**
 * Sends a rawpri packet and retries for 3 times. If the transmission is a success, it
 * @param rawrpiPacket  Passed in rawrpi packet
 * @return Echoed rawrpi packet. If transmission failed, isValid on the packet will be FAILED
 */
RAWRPI sendRAWRPI(RAWRPI rawrpiPacket);

/**
 * Returns input caught from the keypad as per defuse panel requirements. 
 * @return 
 */
unsigned int handleUserInput(char numDigits);

/**
 * Handles all range checking processes and prints correct lights. 
 */
void CMD_HANDLER_rangeCheck(void);

void CMD_HANDLER_addrTrain(void);

unsigned char getAddr0(void);
unsigned char getAddr1(void);
void setAddr0(unsigned char set_addr);
void setAddr1(unsigned char set_addr);

#endif _DEFUSEPANEL_SYS_H