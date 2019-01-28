/*
 * File:   Display.h
 * Author: Nolan
 *
 * Created on July 26, 2012, 2:05 AM
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#include <p18f45k20.h>
#include "Ramos_sys/LED_display.h"
#include "Constructs.h"
#include "Ramos_Sys/Test_routines.h"

#define ERROR 9999
#define R0 20.f
#define PULSE_LIGHTS_PERIOD 1000
#define DEFUSE_CODE_DISPLAY_LENGTH 1000
#define MENU_ANIM_LENGTH 100
#define MENU_ANIM_LIMIT 2400    // needs to be 24*MENU_ANIM_LEGNTH
#define MENU_EXIT_LENGTH 200
#define MENU_EXIT_LIMIT MENU_EXIT_LENGTH*12

#define A 0b00000001
#define B 0b00000010
#define C 0b00000100
#define D 0b00001000
#define E 0b00010000
#define F 0b00100000
#define G 0b01000000
#define Blank 0b00000000


/**
 * @brief displays the current state
 *
 * @param state
 */
void displayState(State * state, State * prev,volatile unsigned short long * timers);

/**
 * @brief  Displays time on RTC
 */
void displayCurTime(unsigned char is24mode, unsigned char pmlight);

/**
 * @brief Displays time from argument
 */
void displaySetTime(unsigned char hours, unsigned char minutes,
        unsigned char is24mode, unsigned char pmlight);


/**
 * @brief Honestly I forgot what this function does.
 *
 * @param t Float one
 * @param t1 Float two, cause hey two's a tango
 * @param x0 Unsigned char to you know, do some stuff
 * @param xc Another unsigned char that is used for solar polarity.
 *
 * @return The modulus of age vs cat_loving_quality
 */
unsigned char getDigit(float t, float t1, unsigned char x0, unsigned char xc);

/**
 * @brief Takes the next hours and minutes and does the digit cycling
 *
 * @param t
 * @param hours
 * @param minutes
 */
void displayDigitCycling(float t, unsigned char hours, unsigned char minutes);

/**
 * @brief Displays the menu animation when getting into the menu
 *
 * @param timer
 */
void displayMenuAnim(unsigned short long timer);

/**
 * @brief Displays the exit animation.
 *
 * @param timer
 */
void displayExitAnim(unsigned short long timer);

/**
 * @brief pulses the lights, if hours == 1 pulse hours, if hours == 0 pulse minutes
 *
 * @param hours
 * @param t
 */
void pulseLights(unsigned char hours, unsigned char minutes, unsigned char alarmLight,
        volatile unsigned short long * t, unsigned char brightNess);


/**
 * @brief This maps a brightness rage for 0-10 to 0-32
 *
 * @param b 0-10 brightness range
 *
 * @return 0-32 brightness range
 */
unsigned char tenTo32(unsigned char b);

/**
 * @brief Autodim brightness helper function
 *
 * @param room
 * @param setting
 * @param autodim
 *
 * @return 
 */
unsigned char roomTo10(unsigned char room, unsigned char setting, unsigned char autodim);

/**
 * @brief Autodim brightness helper function 
 *
 * @param room
 * @param setting
 * @param autodim
 *
 * @return 
 */
unsigned char roomTo32(unsigned char room, unsigned char setting, unsigned char autodim);

/**
 * @brief Displays the defuse code on the display. Helpful to show the user the
 * code's they've gotta input into the defuse code to shut the damn thing off!
 *
 * @param state
 */
void displayDefuseCode(State * state);


#endif
