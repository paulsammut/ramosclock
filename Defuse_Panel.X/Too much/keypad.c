#include "keypad.h"

unsigned int keyCount = 0;
unsigned char oldVal = 99; // no change
unsigned char tempVal;
unsigned char keypad_num = 99;

/**
 * Reads the keypad and returns a pressed number. Not debounced
 *
 * @return 0-9, 10 for star, 11 for hash
 */
static unsigned char readKeypad(void);

void init_keypad(void) {
    INTCON2bits.RBPU = 0; // enable PORTB internal pullups


    //Set I/O
    TRIS_Col0 = 1; //Col0 input
    TRIS_Col1 = 1; //Col1 input
    TRIS_Col2 = 1; //Col2 input
    TRIS_Row0 = 0; //Row0 output
    TRIS_Row1 = 0; //Row1 output
    TRIS_Row2 = 0; //Row2 output
    TRIS_Row3 = 0; //Row3 output

    //enable pull-ups for col0 thru col2
    WPUB_Col0 = 1;
    WPUB_Col1 = 1;
    WPUB_Col2 = 1;

}

void set_debug_disp(unsigned char num) {
    LATD = num;
}

static unsigned char readKeypad(void) {
    keypad_num = 99; //this is the return num
    //set the Rows to all high. I'm using pullups on the columns so they read high when nothings pressed.
    //I need to read low when they are pressed, so I scan through the rows by setting them low.
    Row0 = 1;
    Row1 = 1;
    Row2 = 1;
    Row3 = 1;

    //------COLUMN 0 ----------
    Row0 = 0; //Row 0 set to low
    if (!Col0) //number 1 is pressed!
        keypad_num = 1;
    Row0 = 1; //set it back to high

    Row1 = 0;
    if (!Col0) //number 4 is pressed!
        keypad_num = 4;
    Row1 = 1;

    Row2 = 0;
    if (!Col0) //number 7 is pressed!
        keypad_num = 7;
    Row2 = 1;

    Row3 = 0;
    if (!Col0) //star is pressed
        keypad_num = 10;
    Row3 = 1;

    //------COLUMN 1 ----------
    Row0 = 0; //Row 0 set to low
    if (!Col1) //number 2 is pressed!
        keypad_num = 2;
    Row0 = 1; //set it back to high

    Row1 = 0;
    if (!Col1) //number 5 is pressed!
        keypad_num = 5;
    Row1 = 1;

    Row2 = 0;
    if (!Col1) //number 8 is pressed!
        keypad_num = 8;
    Row2 = 1;

    Row3 = 0;
    if (!Col1) //0 is pressed
        keypad_num = 0;
    Row3 = 1;

    //------COLUMN 3 ----------
    Row0 = 0; //Row 0 set to low
    if (!Col2) //number 3 is pressed!
        keypad_num = 3;
    Row0 = 1; //set it back to high

    Row1 = 0;
    if (!Col2) //number 6 is pressed!
        keypad_num = 6;
    Row1 = 1;

    Row2 = 0;
    if (!Col2) //number 9 is pressed!
        keypad_num = 9;
    Row2 = 1;

    Row3 = 0;
    if (!Col2) //hash is pressed
        keypad_num = 11; //no feature for this
    Row3 = 1;

    return keypad_num;
}

unsigned char pollKeypad(void) {
    tempVal = 99;
    if (readKeypad() != oldVal) {
        keyCount++;
        if (keyCount > 100) {//we've passed the threshold
            if (readKeypad() < 99)//if we have a real press event
                tempVal = readKeypad();
            keyCount = 0;
            oldVal = readKeypad();
        }
    } else
        keyCount = 0;
    return tempVal;
}

