#include "lightPlay.h"

/**
 * This standby light was added because at low voltages the blue light doesn't show.
 * So, when the battery is low, show the red light, and not the blue.
 * When STANDBY_LIGHT is 1, blue
 * When 0, red. Red light shows well at low voltage
 */
unsigned char STANDBY_LIGHT = 1; //blue by default

void blinkBlue(void) {
    unsigned char oldRed = getRedOldVal();
    unsigned char oldGreen = getGreenOldVal();
    unsigned char oldBlue = getBlueOldVal();
    //turn off lights
    setLights(1, 1, 1);
    Delay10KTCYx(10);
    //Turn on blue
    setLights(1, 1, 0);
    Delay10KTCYx(10);
    //Reset
    setLights(oldRed, oldGreen, oldBlue);
}

void blinkRed(void) {
    unsigned char oldRed = getRedOldVal();
    unsigned char oldGreen = getGreenOldVal();
    unsigned char oldBlue = getBlueOldVal();
    //turn off lights
    setLights(1, 1, 1);
    Delay10KTCYx(10);
    //Turn on red
    setLights(0, 1, 1);
    Delay10KTCYx(10);
    setLights(oldRed, oldGreen, oldBlue);
}

void blinkGreen(void) {
    unsigned char oldRed = getRedOldVal();
    unsigned char oldGreen = getGreenOldVal();
    unsigned char oldBlue = getBlueOldVal();
    //turn off lights
    setLights(1, 1, 1);
    Green = 1;
    //Turn on green
    setLights(1, 0, 1);
    Delay10KTCYx(10);
    setLights(oldRed, oldGreen, oldBlue);
}

void solidGreen(void) {
    setLights(1, 0, 1);
}

void solidBlue(void) {
    setLights(1, 1, 0);
}

void solidRed(void) {
    setLights(0, 1, 1);
}

void solidOrange(void) {
    setLights(0, 0, 1);
}

void solidPink(void) {
    setLights(0, 1, 0);
}

void solidCyan(void) {
    setLights(1, 0, 0);
}

void solidWhite(void) {
    setLights(0, 0, 0);
}

void startUpAnim(void) {
    //Initialization routine
    setLights(1, 1, 0);
    Delay10KTCYx(8);
    setLights(0, 1, 1);
    Delay10KTCYx(2);
    setLights(1, 1, 0);
    Delay10KTCYx(8);
    setLights(1, 0, 1);
    Delay10KTCYx(2);
    setLights(0, 0, 1);
    Delay10KTCYx(8);
    setLights(0, 0, 0);
}

void showStandbyLight(void) {
    if (STANDBY_LIGHT == 1)//blue
        solidBlue();
    else
        solidRed();
}

void setStandbyLight(unsigned char sLight){
    STANDBY_LIGHT = sLight;
}