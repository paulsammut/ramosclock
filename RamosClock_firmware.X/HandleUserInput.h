/*
 * File:   HandleUserInput.h
 * Author: Nolan
 *
 * Created on July 25, 2012, 11:48 PM
 */

#ifndef HANDLEUSERINPUT_H
#define	HANDLEUSERINPUT_H

#include <p18f45k20.h>
#include "Ramos_Sys/LED_display.h"
#include "Ramos_sys/Ramos_sys.h"
#include "Ramos_sys/RTC.h"
#include "Ramos_sys/Sound.h"
#include "options.h"
#include "Constructs.h"
#include "CC1101_slave.h"
#include "RAWRPI.h"
#include "Ramos_Sys/EEPROM.h"

/**
 * Handles the encoder input
 */
void handleEncoder(State *  state, volatile unsigned short long * timers);

/**
 *  Handles the toggle switch input
 */
void handleSwitch( State * state, volatile unsigned short long * timers);

/**
 *  Handles the knob input
 */
void handleKnob(State * state, volatile unsigned short long * timers);

/**
 * Handles the alarm button input
 */
void handleAlarmBtn(State * state, volatile unsigned short long * timer);


void handleRemotePanel(State * state);

/**
 * returns 1 if addresses match, otherise 0
 * @param state
 * @param tempRAWRPI
 * @return
 */
unsigned char addressesMatch(State * state, RAWRPI * tempRAWRPI);

/**
 * returns 1 if the code matches the defuse code and false if not
 * @param tempRAWRPI
 * @return
 */
unsigned char defuseCodeMatches(RAWRPI * tempRAWRPI, State * state);

void returnSucces(RAWRPI * tempRAWRPI);

void returnFailure(RAWRPI * tempRAWRPI);


#endif	/* HANDLEUSERINPUT_H */

