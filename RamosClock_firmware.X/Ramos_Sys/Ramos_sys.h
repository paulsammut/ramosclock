#ifndef RAMOS_SYS_H
#define RAMOS_SYS_H

#include "LED_display.h"
#include <p18f45k20.h>
#include <timers.h>
#include <spi.h>
#include "Sound.h"
#include "EEPROM.h"
#include "RTC.h"


#define TIMER0_OFLOW INTCONbits.T0IF
#define TIMER1_OFLOW PIR1bits.TMR1IF

/** C L O C K - S T U F F -----------------------*/
#define CS_RTC  LATAbits.LATA0
#define CS_RF   LATAbits.LATA1

/** P I N - S E T T I N G ----------------------*/
//switches
/* 0 is pressed, 1 is not pressed */
#define SWITCH_ALARM_SET PORTBbits.RB0
#define SWITCH_TIME_SET PORTBbits.RB1
#define SWITCH_ALARM PORTBbits.RB2
#define SWITCH_KNOB PORTBbits.RB5
//#define SWITCH_KNOB PORTCbits.RC6  //just for debug testing so the programmer lines are free
#define ENC_A PORTBbits.RB3
#define ENC_B PORTBbits.RB4


/** Alarm LED pin access */
#define ALARM_LED LATAbits.LATA7
/** Colon */
#define Colon LATAbits.LATA3

/**--- S W I T C H -- D E F I N E S ---------*/
#define PRESSED 1
#define DEPRESSED 2

/** E N C O D E R ----------*/
#define HIGH2LOW 1
#define LOW2HIGH 2



/**
 * Initializes the clock settings to 32mHz using 4x PLL
 */
void init_Ramos_sys(void);

/**
 * For the alarm setting toggle switch. Returns PRESSED or DEPRESSED once on that event.
 * @return PRESSED, DEPRESSED or 0 for no change
 */
unsigned char pollAset(void);

/**
 * For the time setting toggle switch. Returns PRESSED or DEPRESSED once on that event.
 * @return PRESSED, DEPRESSED or 0 for no change
 */
unsigned char pollTset(void);

/**
 * Returns PRESSED or DEPRESSED once on that event.
 * @return PRESSED, DEPRESSED or 0 for no change.
 */
unsigned char pollAlarmBtn(void);

/**
 * Returns PRESSED or DEPRESSED once on that event.
 * @return PRESSED, DEPRESSED or 0 for no change.
 */
unsigned char pollKnobBtn(void);

/**
 * Returns 1 if increment, returns 0 if no change, and -1 if decrement
 */
char pollEncoder(void);



/**
 * Returns the brightness value of the room from 0 being full dark to 255 being full bright.
 * @return
 */unsigned char photoResVal(void);

#endif RAMOS_SYS_H
