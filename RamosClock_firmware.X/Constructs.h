/*
 * File:   Constructs.h
 * Author: Nolan
 *
 * Created on July 11, 2012, 7:21 PM
 */

#ifndef CONSTRUCTS_H
#define	CONSTRUCTS_H

#include <p18f45k20.h>
#include "Ramos_Sys/LED_display.h"
#include "Ramos_sys/Ramos_sys.h"
#include "Ramos_sys/RTC.h"
#include "Ramos_sys/Sound.h"

/* Timer limits */
#define MENU_TIMER_LIMIT 2500   // How long the alarm button needs to be held to enter the menu mode
#define MENU_SND_WAIT_TIME 450 // how long we wait for play menu sound
#define MENU_TIMEOUT_TIME 20000 // how long until the menu times out
#define RAMPUP_PERIOD 15000  // how long we wait to increment the volume during rampup
#define ALARM_TIMEOUT_LIMIT 45 // how many minutes to wait before timing out alarm
#define AUTODIM_SPEED 50 // how long we wait to increment

// pulse settings
#define PULSE_MIN 4
#define PULSE_MAX 32
#define PULSE_RATE 15 //number of milliseconds to wait until changing

#define BRIGHTNESS_TIMER_LIMIT  3000

enum Mode
{
    TIME=0,
    SET_TIME,
    SET_ALARM,
    MENU,       // cycling through options in the menu
    MENU_SET    // setting selected options in the menu
};

enum months
{
    JAN=1,
    FEB,
    MAR,
    APR,
    MAY,
    JUN,
    JUL,
    AUG,
    SEP,
    OCT,
    NOV,
    DEC
};

enum options
{
    REMOTE_ALARM=0,
    DEFUSE_CODE,
    ALARM_TONE,
    LOCKDOWN,
    COURTESY,
    COURTESY_PERIOD,
    NUM_SNOOZES,
    SNOOZE_PERIOD,
    DAY,
    MONTH,
    YEAR,
    DATE_FORMAT,
    TWENTY4_HOUR,
    PM_LIGHT_24HR_VAL,
    DIGIT_CYCLING,
    BRIGHTNESS,
    AUTO_DIM_LEVEL,
    NUM_OPTIONS
};

enum timers_enum
{
    TEMP_TIMER,
    ALARM_TIMER,        // how long the timer has been going off
    MENU_ENTER_TIMER,   // how long we have to hold alarm button to enter menu
    MENU_ANIM_TIMER,
    MENU_SOUND_TIMER,
    MENU_TIMEOUT_TIMER,
    DIGIT_TIMER,
    PULSE_TIMER,
    DEFUSE_CODE_TIMER,
    BRIGHTNESS_TIMER,   // timer to show brightness at full whenever a button is hit
    NUM_TIMERS
};

enum lockdownandalarmstate
{
    NEITHER=0,
    INLOCKDOWN,
    PSUEDOLOCKDOWN,
    ALARM_TRIGGERED
};


typedef struct
{
    unsigned char setHourMode; // true == set hours, false == set minutes
    unsigned char alarmOn;     // alarm on
    unsigned char lockDownAndAlarmState;
    /* Time */
    unsigned char hours;
    unsigned char minutes;
    /* Alarm Time */
    unsigned char alarmHours;
    unsigned char alarmMinutes;
    unsigned char snoozeCount;
    unsigned char defuseFirst;
    unsigned char defuseSecond;
    /* Display mode */
    unsigned char mode;
    /* options */
    unsigned int curOption;
    unsigned char options[NUM_OPTIONS];
    /* Addresses for remote alarm */
    unsigned char address0;
    unsigned char address1;
} State;



#endif	/* CONSTRUCTS_H */

