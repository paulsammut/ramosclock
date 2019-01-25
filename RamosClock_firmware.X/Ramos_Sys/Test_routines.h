#ifndef TEST_ROUTINES_H
#define TEST_ROUTINES_H


/**
 * Blinks the colon every second. The time is read from the RTC
 */
void Test_blinkColonOnSec(void);

/***
 * Prints the seconds to the LED Display
 */

void Test_printMinSec(void);

/**
 * Prints hours and minutes on the LED Display
 */
void Test_printHrMin(void);

/**
 * pulse lights
 */
void Test_pulseLights(void);

/**
 * Tests the switch, alarm button and knob switch by polling the event based functions!
 */
void Test_SwitchWithDebugAndEventBasedFunctions(void);

/**
 * Knob switch shows day/month, Aset switch should min, sec, Tset switch shows year,
 * alam button shows day of the week. Idle shows Hours mins.
 */
void Test_basicClockFunctions(void);

/**
 * Put the brightness from 255 (darkest) to 1 (brightest) on the screen. Buttons do some stuff. Knob is cool.
 */
void Test_photoRes(void);

/**
 * Test the encoder but not the switch
 */
void Test_encoder(void);

/**
 *
 */
void Test_pulseLights(void);

void Test_RF_echoAck(void);

#endif TEST_ROUTINES_H