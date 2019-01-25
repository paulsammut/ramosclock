#ifndef _KEYPAD_H
#define _KEYPAD_H

#include "defusePanel_sys.h"
#include <p18f45k20.h>

/** Pin input definitions for the columns **/
#define Col0 PORTBbits.RB0 //column 0  Pin 3
#define Col1 PORTBbits.RB1 //column 1  Pin 1
#define Col2 PORTBbits.RB2 //column 2  Pin 5

//** Pin outputs for the rows **//
#define Row0 LATBbits.LATB3 //row 0 Pin 2
#define Row1 LATBbits.LATB4 //row 1 Pin 7
#define Row2 LATAbits.LATA6 //row 2 Pin 6
#define Row3 LATAbits.LATA7 //row 3 Pin 4

//** TRIS settings for all the pins **//
#define TRIS_Col0 TRISBbits.RB0
#define TRIS_Col1 TRISBbits.RB1
#define TRIS_Col2 TRISBbits.RB2
#define TRIS_Row0 TRISBbits.RB3
#define TRIS_Row1 TRISBbits.RB4
#define TRIS_Row2 TRISAbits.RA6
#define TRIS_Row3 TRISAbits.RA7

//** Pullups **//
#define WPUB_Col0 WPUBbits.WPUB0
#define WPUB_Col1 WPUBbits.WPUB1
#define WPUB_Col2 WPUBbits.WPUB2


/*-- N U M B E R S -------*/
#define STAR 10
#define HASH 11
#define NOPRESS 99
/**
 * Initializes the keypad
 */
void init_keypad(void);

/**
 * Polls, debugs, and returns a press event only once.
 * @return If 99, no event. 0-9 a number, 10 start, 11 hash pressed.
 */
unsigned char pollKeypad(void);


#endif _KEYPAD_H