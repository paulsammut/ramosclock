/*
 * File:   options.h
 * Author: Nolan
 *
 * Created on July 21, 2012, 10:13 PM
 */

#ifndef OPTIONS_H
#define	OPTIONS_H

#include "Constructs.h"
#include "Ramos_Sys/Sound.h"
#include "LED_display.h"
#include "Display.h"


void setInitState(State * state);
void setDefaultOptions(unsigned char *options);

unsigned char optionUpper(State * state, unsigned int opt);
unsigned char optionLower(State * state, unsigned int opt);
unsigned char optionIncrement(unsigned int opt);

unsigned char maxDays(State * state);

unsigned int getAlarmDistance(unsigned int current, unsigned int alarm);

unsigned int getBWAlarmDistance(unsigned int current, unsigned int alarm);

/**
 * Returns 1 if the current option is one that plays a sound when changing
 * @param currentOption
 * @return
 */
unsigned char isMenuSettingWTone(unsigned int * currentOption);

unsigned char inBounds(State * state, unsigned char *options);


#endif	/* OPTIONS_H */

