#include "lightPlay.h"

void blinkBlue(void) {
    unsigned char oldRed = Red;
    unsigned char oldGreen = Green;
    unsigned char oldBlue = Blue;
    //turn off lights
    Red = 1;
    Green = 1;
    Blue = 1;
    Delay10KTCYx(10);
    //Turn on blue
    Blue = 0;
    Delay10KTCYx(10);
    //Reset
    Red = oldRed;
    Green = oldGreen;
    Blue = oldBlue;
}

void blinkRed(void) {
    unsigned char oldRed = Red;
    unsigned char oldGreen = Green;
    unsigned char oldBlue = Blue;
    //turn off lights
    Red = 1;
    Green = 1;
    Blue = 1;
    Delay10KTCYx(10);
    //Turn on red
    Red = 0;
    Delay10KTCYx(10);
    Red = oldRed;
    Green = oldGreen;
    Blue = oldBlue;
}

void blinkGreen(void) {
    unsigned char oldRed = Red;
    unsigned char oldGreen = Green;
    unsigned char oldBlue = Blue;
    //turn off lights
    Red = 1;
    Green = 1;
    Blue = 1;
    Delay10KTCYx(10);
    //Turn on green
    Green = 0;
    Delay10KTCYx(10);
    Red = oldRed;
    Green = oldGreen;
    Blue = oldBlue;
}

void solidGreen(void) {
    //turn off lights
    Red = 1;
    Green = 0;
    Blue = 1;
}

void solidBlue(void) {
    //turn off lights
    Red = 1;
    Green = 1;
    Blue = 0;
}

void solidRed(void) {
    //turn off lights
    Red = 0;
    Green = 1;
    Blue = 1;
}

void solidOrange(void) {
    //turn off lights
    Red = 0;
    Green = 0;
    Blue = 1;
}

void solidPink(void) {
    //turn off lights
    Red = 0;
    Green = 1;
    Blue = 0;
}

void solidCyan(void) {
    //turn off lights
    Red = 1;
    Green = 0;
    Blue = 0;
}

void solidWhite(void) {
    //turn off lights
    Red = 0;
    Green = 0;
    Blue = 0;
}

void startUpAnim(void) {
    //Initialization routine
    Blue = 0;
    Delay10KTCYx(8);
    Red = 0;
    Delay10KTCYx(2);
    Blue = 1;
    Delay10KTCYx(8);
    Green = 0;
    Delay10KTCYx(2);
    Red = 1;
    Delay10KTCYx(8);
    Green = 1;
}

