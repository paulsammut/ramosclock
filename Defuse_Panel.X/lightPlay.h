#ifndef _LIGHTPLAY_H
#define _LIGHTPLAY_H

#include "defusePanel_sys.h"
#include <p18f45k20.h>
#include "defusePanel_sys.h"
#include <delays.h>


void lightPlay(void);
void startUpAnim(void);
void blinkBlue(void);
void blinkRed(void);
void blinkGreen(void);
/**
 * Turns on the light and leaves it solid.
 */
void solidGreen(void);
void solidRed(void);
void solidBlue(void);
void solidOrange(void);
void solidCyan(void);
void solidWhite(void);
void solidPink(void);

/**
 * Shows the standby light.
 */
void showStandbyLight(void);

/**
 * Used to get around the issue of the blue light dissappearing in low voltage conditions
 * 
 * @param sLight 1 for blue, 0 for red.
 */
void setStandbyLight(unsigned char sLight);
#endif
