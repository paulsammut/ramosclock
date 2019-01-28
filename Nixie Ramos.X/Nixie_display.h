/* 
 * File:   Nixie_display.h
 * Author: paul
 *
 * Created on September 20, 2012, 1:32 AM
 */

#ifndef NIXIE_DISPLAY_H
#define	NIXIE_DISPLAY_H

#include "Ramos_sys.h"
#include <p18f45k20.h>
#include <timers.h>

// Shift register pin definition
#define SHIFTREG_DATA LATDbits.LATD1
#define SHIFTREG_CLOCK LATDbits.LATD3
#define SHIFTREG_LATCH LATDbits.LATD2

#define SHIFTREG_TRIS_DATA TRISDbits.TRISD1
#define SHIFTREG_TRIS_CLOCK TRISDbits.TRISD3
#define SHIFTREG_TRIS_LATCH TRISDbits.TRISD2

// High voltage enable line
#define HV_ENABLE LATDbits.LATD0
#define HV_ENABLE_TRIS TRISDbits.TRISD0

/** Placeholder bits for the digits to display
 * The namaing convention is Digit_Value
 * Rightmost ones minute digit is 0, leftmost is 3
 * So if you are showing 1 all the way on the right tube
 * it would be Zero_One
 * The value is the the bit number in the 40 bit shifted code to the shift registers
 */

// Constant that sets the display to blank
#define BLANK 99

/**
 * @brief Initializes the Nixie display system.
 */
void init_Display(void);

/**
 * @brief Display a number to the nixie clock. Blanks leading 0.
 *
 * @param dsp_num_nixie Number to the display.
 */
void Display_showNumber(unsigned int dsp_num_nixie);

/**
 * @brief Sets all the 4 digits of the display. 99, or BLANK, blanks.
 *
 * @param tD0 X000
 * @param tD1 0X00
 * @param tD2 00X0
 * @param tD3 000X
 */
void Display_setAll4(unsigned char tD0, unsigned char tD1, unsigned char tD2, unsigned char tD3);

/**
 * @brief Sets the brightness level for all lights on the clock
 *
 * @param brightParam Brightness level from 0-32
 */
void Display_setBrightnessAll(unsigned char brightParam);

/**
 * @brief Sets the brightness of everything but the ring light. For use when autodim and lockdown mode are both activated.
 *
 * @param brightParam 0 - 32 brightness
 */
void Display_setBrightnessEverythingButRing(unsigned char brightParam);

/**
 * @brief Sets the brightness of the ring light only. 0-32
 *
 * @param ringBparam
 */
void Display_setRingBrightness(unsigned char ringBparam);

/**
 * @brief Sets individual digit brightness from 0 to 32.
 *
 * @param b0 Digit 0 (left most digit)
 * @param b1 Digit 1
 * @param b2 Digit 2
 * @param b3 Digit 3
 */
void Display_setIndividualBright(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3);

/**
 * @brief Turns the colon on.
 */
void turnOnColon(void);

/**
 * @brief Turns off the colon.
 */
void turnOffColon(void);

/**
 * @brief Turn on PM light
 */
void turnOnPMLight(void);

/**
 * @brief Turn PM light off
 */
void turnOffPMLight(void);


/**
 * @brief Turn the alarm light off.
 */
void turnOffAlarmLight(void);

/**
 * @brief Turn on the alarm light.
 */
void turnOnAlarmLight(void);

/**
 * @brief Displays the word on.
 */
void Display_On(void);

/**
 * @brief Displays the word off.
 */
void Display_Off(void);

void Display_setIndividualElements(unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3);

/**
 * @brief Returns milliseconds since last Timer_reset() function call.
 *
 * @returns 0 to 16,777,216 in milliseconds.
 */
unsigned short long Timer_msSinceReset(void);

/**
 * @brief Resets the millisecond timer.
 */
void Timer_reset(void);

#endif	/* NIXIE_DISPLAY_H */
