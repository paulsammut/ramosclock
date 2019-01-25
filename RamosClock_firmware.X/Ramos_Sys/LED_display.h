/**
 * @file    LED_display.h
 * @author  Paul Sammut <paul@sammut-tech.com>
 * @version 1.0
 *
 * @License
 * This program is not free software. It is the property of Sammut Tech LLC.
 *
 * @Description
 * Definitions for the LED display module for Rev 1 and Rev 2 boards.
 */


#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H

#include "Ramos_sys.h"
#include <p18f45k20.h>
#include <timers.h>

/** PM Light pin access */
#define PMLight LATAbits.LATA4

/** LED multiplexing, brightness, and refresh rate settings */
/* PWM brightness levels. This number divided by (refreshrate)^-1 dictates minimum display refresh rate.*/
#define LED_PWM_BRIGHTNESS_LEVELS 32
/*Refresh rate in Hz*/
#define LED_DSP_REFRESH_RATE 60

/** Anode TRIS definition for the LED Display */
#define TRISAnode0 TRISEbits.RE0 //Anode 1
#define TRISAnode1 TRISDbits.RD7 //Anode 2
#define TRISAnode2 TRISEbits.RE1 //Anode 3
#define TRISAnode3 TRISEbits.RE2 //Anode 4


/* Anode latch input definitions for the Anodes of the LED Display */
#define Anode0 LATEbits.LATE0 //Anode 1
#define Anode1 LATDbits.LATD7 //Anode 2
#define Anode2 LATEbits.LATE1 //Anode 3
#define Anode3 LATEbits.LATE2 //Anode 4


/*Constant that sets the display to blank*/
#define BLANK 99

/* Active high*/
#define SEG_0 0b10111111
#define SEG_1 0b10000110
#define SEG_2 0b11011011
#define SEG_3 0b11001111
#define SEG_4 0b11100110
#define SEG_5 0b11101101
#define SEG_6 0b11111101
#define SEG_7 0b10000111
#define SEG_8 0b11111111
#define SEG_9 0b11101111

#define SEG_n 0b11010100
#define SEG_o 0b10111111
#define SEG_f 0b11110001

/* Letter assignments */
#define LETTER_O 10
#define LETTER_N 11
#define LETTER_F 12

/*
// Global digit variables


/**
 * Initializes the LED display system.
 */
void init_Display(void);

/**
 * Displays selected digit with value.
 * @param digit Selected digit. 0-3 with 0 being leftmost digit.
 * @param value Value to display. 99 blanks. Valid range is 0-9, 99, BLANK.
 */
/*--- UNUSED ----*/
//void LED_setDisplay(char digit, char value);

/**
 * Blanks the entire display.
 */
void LED_blank(void);

/**
 * Turns the colon on.
 */
void turnOnColon(void);

/**
 * Turns off the colon.
 */
void turnOffColon(void);

/**
 *Turn on PM light
 */
void turnOnPMLight(void);

/**
 *Turn PM light off
 */
void turnOffPMLight(void);


/**
 * Turn the alarm light off.
 */
void turnOffAlarmLight(void);

/**
 * Turn on the alarm light.
 */
void turnOnAlarmLight(void);

/**
 * Sets the brightness level for all lights on the clock
 * @param brightParam Brightness level from 0-32
 */
void Display_setBrightnessAll(unsigned char brightParam);


/**
 * Set the PM light, Alarm switch LED, and colon light
 * @param periphBright Peripheral brightness from 0-32
 */
//void LED_setPeriphBrightness(unsigned char periphBright);

/**
 * Sets the brightness of everything but the ring light. For use when autodim and lockdown mode are both activated.
 * @param brightParam 0 - 32 brightness
 */
void Display_setBrightnessEverythingButRing(unsigned char brightParam);

/**
 * Displays a 4 digit number. Takes care of blanking
 * @param num2Disp Number to display
 */
void Display_showNumber(unsigned int num2Disp);


/**
 * Sets all the 4 digits of the display. 99, or BLANK, blanks.
 * @param tD0 X000
 * @param tD1 0X00
 * @param tD2 00X0
 * @param tD3 000X
 */
void Display_setAll4(unsigned char tD0, unsigned char tD1, unsigned char tD2, unsigned char tD3);

/**
 * Alternative to the turnOn, turnOff functions for setting the PM light.
 * @param onOff 1 is on and 0 is off.
 */
void setPM_Light(unsigned char onOff);

/**
 * Displays the word on.
 */
void Display_On(void);

/**
 * Displays the word off.
 */
void Display_Off(void);

/**
 * Sets individual digit brightness from 0 to 32.
 * @param b0 Digit 0 (left most digit)
 * @param b1 Digit 1
 * @param b2 Digit 2
 * @param b3 Digit 3
 */
void Display_setIndividualBright(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3);
/**
 * Sets the brightness of the ring light only. 0-32
 * @param ringBparam
 */
void Display_setRingBrightness(unsigned char ringBparam);

/**
 * Sets the individual elements of each digits using a boolean bit field. Elements are 
 * GFEDCBA. 0 is all elements off, 0b00000001 is element A on. The first bit doesn't matter.
 * So if you set d0 to 0b01000001, elements G and A will be on on D0 which is the left most digit.
 * @param d0 Bit field for the 7 segments of the first digit which is the left most one.
 * @param d1 Bit field for the 7 segments.
 * @param d2 Bit field for the 7 segments.
 * @param d3 Big field for the 7 segments of the last digit, which is the rightmost digit.
 */
void Display_setIndividualElements(unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3);

/**
 * Returns milliseconds since last Timer_reset() function call.
 * @returns 0 to 16,777,216 in milliseconds.
 */
unsigned short long Timer_msSinceReset(void);

/**
 * Resets the millisecond timer.
 */
void Timer_reset(void);


#endif LED_DISPLAY_H