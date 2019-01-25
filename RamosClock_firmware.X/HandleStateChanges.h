/*
 * File:   HandleStateChanges.h
 * Author: Nolan
 *
 * Created on July 29, 2012, 2:24 AM
 */

#ifndef HANDLESTATECHANGES_H
#define	HANDLESTATECHANGES_H

#include "Constructs.h"
#include "options.h"
#include "Display.h"
#include "Ramos_Sys/Ramos_sys.h"
#include "Ramos_Sys/LED_display.h"
#include "Ramos_Sys/Sound.h"
#include "Ramos_Sys/EEPROM.h"

#include "stdlib.h"

void handleStateChanges(State * prev, State * state, volatile unsigned short long * timers,
        unsigned char * justPMenuSoundPtr);

void handleTimeOuts(State * state, volatile unsigned short long * timers);

void handleSounds(State * state, State * prev,volatile unsigned short long * timers,
        unsigned char * justPMenuSound);

void handleCourt(State * state, volatile unsigned short long * timers,
        unsigned char * prev_rampup_vol);

void setDefuseCode(State * state);

void updateTimers(volatile unsigned short long * timers);

void initTimers(volatile unsigned short long * timers);

unsigned short long timerLimits(unsigned int time_enum);


#endif	/* HANDLESTATECHANGES_H */

