#include "Nixie_display.h"

/**
 * @brief Runs the multiplexing scheme that handles brightness, blanking, PWM,
 * timers, and peripherals.
 */
static void Nixie_muxAway(void);


/**
 * @brief Table that contains all the proper digit mapping
 */
volatile unsigned char nixieDigitTable [4][11];

/**
 * @brief Value for the PM light. 1 on, 0 off
 */
volatile unsigned char PMlight_val = 1;

/**
 * @brief Value for the colon light. 1 on, 0 off
 */
volatile unsigned char colon_val = 1;

/**
 * @brief Value for the alarm light. 1 on, 0 off
 */
volatile unsigned char alarmLight_val = 1;

/**
 * @brief Digit brightness values, 0-32. Each digit's brightness can be
 * independantly controlled
 */
volatile unsigned char digit0Brightness = 32;
volatile unsigned char digit1Brightness = 32;
volatile unsigned char digit2Brightness = 32;
volatile unsigned char digit3Brightness = 32;

/**
 * @brief Initial digit values.
 */
volatile unsigned char digit0Val = 1;
volatile unsigned char digit1Val = 2;
volatile unsigned char digit2Val = 3;
volatile unsigned char digit3Val = 4;


/**
 * @brief Temporary display value holders
 */
volatile unsigned char tempDisp0, tempDisp1, tempDisp2, tempDisp3;

/**
 * @brief Peripheral brighness. colon, ampm light and alarm on led
 */
volatile unsigned char periphBrightness = 32;

/**
 * @brief LED on alarm
 */
volatile unsigned char ringBrightness = 32;

/**
 * @brief Number of PWM timer steps counted so far. When i get here, reset and
 * incr PWM level step unsigned char num_timerCountPWM=0; number of digit 
 * timer counts. When = timerCountDigit_tresh, reset, move on to next digit
 */
volatile unsigned int PWM_counter;

/**
 * @brief Millisecond function:
 */
volatile static unsigned short long Timer_millis = 0;

/** I N T E R R U P T S ***********************************************/

//----------------------------------------------------------------------------
// Low priority interrupt vector

#pragma code InterruptVectorLow= 0x18

/**
 * @brief This is a low priority interrupt vector that runs the multiplexed
 * display
 */
void InterruptVectorLow(void) {
    _asm
    goto Nixie_muxAway //jump to interrupt routine
            _endasm
}

void init_Display() {
    //Set the pins as outputs
    SHIFTREG_TRIS_CLOCK = 0;
    SHIFTREG_TRIS_DATA = 0;
    SHIFTREG_TRIS_LATCH = 0;
    HV_ENABLE_TRIS = 0;

    //enable the HV power supply
    HV_ENABLE = 1; //high enabled.

    //turn on the colons!!!
    Colon = 1;

    //init
    SHIFTREG_DATA = 0;
    SHIFTREG_CLOCK = 0;
    SHIFTREG_LATCH = 0;

    /*--- T I M E R - 0 ------------*/
    INTCONbits.TMR0IF = 0; //clear roll over interrupt flag
    INTCON2bits.TMR0IP = 0; //display is a low priority interrupt
    INTCONbits.TMR0IE = 1; //enable the timer overflow interrupt

    T0CONbits.T08BIT = 1; //8bit timer
    T0CONbits.T0CS = 0; //internal clock
    T0CONbits.PSA = 0; //prescale
    T0CONbits.T0PS = 0b011; //1:16 presale 512us

    TMR0H = 0; //clear timer - always write upper byte first;
    TMR0L = 0; //lower bit clear
    T0CONbits.TMR0ON = 1; //enable the timer

    //initialize the nixie digit table
    /* Digit 3, Rightmost digit */
    nixieDigitTable[3][0] = 6;
    nixieDigitTable[3][1] = 9;
    nixieDigitTable[3][2] = 8;
    nixieDigitTable[3][3] = 7;
    nixieDigitTable[3][4] = 1;
    nixieDigitTable[3][5] = 0;
    nixieDigitTable[3][6] = 2;
    nixieDigitTable[3][7] = 3;
    nixieDigitTable[3][8] = 4;
    nixieDigitTable[3][9] = 5;
    nixieDigitTable[3][10] = 99; //blank

    nixieDigitTable[2][0] = 10;
    nixieDigitTable[2][1] = 19;
    nixieDigitTable[2][2] = 18;
    nixieDigitTable[2][3] = 17;
    nixieDigitTable[2][4] = 16;
    nixieDigitTable[2][5] = 15;
    nixieDigitTable[2][6] = 14;
    nixieDigitTable[2][7] = 13;
    nixieDigitTable[2][8] = 12;
    nixieDigitTable[2][9] = 11;
    nixieDigitTable[2][10] = 99; //blank

    nixieDigitTable[1][0] = 20;
    nixieDigitTable[1][1] = 29;
    nixieDigitTable[1][2] = 28;
    nixieDigitTable[1][3] = 27;
    nixieDigitTable[1][4] = 26;
    nixieDigitTable[1][5] = 25;
    nixieDigitTable[1][6] = 24;
    nixieDigitTable[1][7] = 23;
    nixieDigitTable[1][8] = 22;
    nixieDigitTable[1][9] = 21;
    nixieDigitTable[1][10] = 99; //blank

    nixieDigitTable[0][0] = 30;
    nixieDigitTable[0][1] = 32;
    nixieDigitTable[0][2] = 33;
    nixieDigitTable[0][3] = 34;
    nixieDigitTable[0][4] = 35;
    nixieDigitTable[0][5] = 36;
    nixieDigitTable[0][6] = 37;
    nixieDigitTable[0][7] = 38;
    nixieDigitTable[0][8] = 39;
    nixieDigitTable[0][9] = 31;
    nixieDigitTable[0][10] = 99; //blank

}

void Display_showNumber(unsigned int dsp_num_nixie) {
    volatile unsigned char tempDisp0, tempDisp1, tempDisp2, tempDisp3;
    volatile unsigned char leadBlank;
    leadBlank = 1;
    tempDisp3 = (unsigned char) (dsp_num_nixie % 10);
    dsp_num_nixie /= 10;
    tempDisp2 = (unsigned char) (dsp_num_nixie % 10);
    dsp_num_nixie /= 10;
    tempDisp1 = (unsigned char) (dsp_num_nixie % 10);
    dsp_num_nixie /= 10;
    tempDisp0 = (unsigned char) (dsp_num_nixie % 10);

    if (!tempDisp0)//its 0
        tempDisp0 = 10; //10 is blank
    else
        leadBlank = 0;
    if (!tempDisp1 && leadBlank)//its 0
        tempDisp1 = 10; //blank!
    else
        leadBlank = 0;
    if (!tempDisp2 && leadBlank)//its 0
        tempDisp2 = 10; //blank!
    else
        leadBlank = 0;

    //set the display vals
    digit0Val = tempDisp0;
    digit1Val = tempDisp1;
    digit2Val = tempDisp2;
    digit3Val = tempDisp3;

}

void Display_setBrightnessAll(unsigned char brightParam) {
    digit0Brightness = brightParam;
    digit1Brightness = brightParam;
    digit2Brightness = brightParam;
    digit3Brightness = brightParam;
    periphBrightness = brightParam;
    ringBrightness = brightParam;
}

void Display_setBrightnessEverythingButRing(unsigned char brightParam){
    digit0Brightness = brightParam;
    digit1Brightness = brightParam;
    digit2Brightness = brightParam;
    digit3Brightness = brightParam;
    periphBrightness = brightParam;
}

void Display_setRingBrightness(unsigned char ringBparam){
    ringBrightness = ringBparam;
}

void Display_setIndividualBright(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3){
    digit0Brightness = b0;
    digit1Brightness = b1;
    digit2Brightness = b2;
    digit3Brightness = b3;
}

void turnOffColon() {
    colon_val = 0;
}

void turnOnColon() {
    colon_val = 1;
}

void turnOnPMLight() {
    PMlight_val = 1;
}

void turnOffPMLight() {
    PMlight_val = 0;
}

void turnOffAlarmLight() {
    alarmLight_val = 0;
}

void turnOnAlarmLight() {
    alarmLight_val = 1;
}

void Display_On(void) {
    Display_showNumber(1);
}

void Display_Off(void) {
    Display_setAll4(99,99,0,0);
}

void Display_setAll4(unsigned char tD0, unsigned char tD1, unsigned char tD2, unsigned char tD3) {
    if (tD0 == 99)
        digit0Val = 10; //this is blank cause of the array issue
    else
        digit0Val = tD0;

    if (tD1 == 99)
        digit1Val = 10; //this is blank cause of the array issue
    else
        digit1Val = tD1;

    if (tD2 == 99)
        digit2Val = 10;
    else
        digit2Val = tD2;
    
    if (tD3 == 99)
        digit3Val = 10;
    else
        digit3Val = tD3;
}

void Display_setIndividualElements(unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3){
    Display_showNumber(RTC_getSeconds()%2);
}


#pragma interruptlow Nixie_muxAway

static void Nixie_muxAway() {
    volatile unsigned char isThereChange = 0;
    volatile int i = 0;
    if (TIMER0_OFLOW) {
        TIMER0_OFLOW = 0; //Clear the T0IF flag
        PWM_counter++; //incrememnt Digit timer count

        //======================================================================
        //=========================enactBrightness()============================
        //======================================================================
        // This used to be function, when I was a silly goose and before I
        // leared about the perils of called functions inside of interrupt
        // routines!

        if (PWM_counter >= digit0Brightness) {
            tempDisp0 = BLANK;
            isThereChange = 1;
        } else if (PWM_counter < digit0Brightness && tempDisp0 != nixieDigitTable[0][digit0Val]) {
            tempDisp0 = nixieDigitTable[0][digit0Val];
            isThereChange = 1;
        }
        if (PWM_counter >= digit1Brightness) {
            tempDisp1 = BLANK;
            isThereChange = 1;
        } else if (PWM_counter < digit1Brightness && tempDisp1 != nixieDigitTable[1][digit1Val]) {
            tempDisp1 = nixieDigitTable[1][digit1Val];
            isThereChange = 1;
        }
        if (PWM_counter >= digit2Brightness) {
            tempDisp2 = BLANK;
            isThereChange = 1;
        } else if (PWM_counter < digit2Brightness && tempDisp2 != nixieDigitTable[2][digit2Val]) {
            tempDisp2 = nixieDigitTable[2][digit2Val];
            isThereChange = 1;
        }
        if (PWM_counter >= digit3Brightness) {
            tempDisp3 = BLANK;
            isThereChange = 1;
        } else if (PWM_counter < digit3Brightness && tempDisp3 != nixieDigitTable[3][digit3Val]) {
            tempDisp3 = nixieDigitTable[3][digit3Val];
            isThereChange = 1;
        }

        if (isThereChange) {
            // Shift in the 40 bits
            for (i = 0; i < 40; i++) {
                if (i == tempDisp0 || i == tempDisp1 || i == tempDisp2 || i == tempDisp3) {
                    SHIFTREG_DATA = 1;
                } else
                    SHIFTREG_DATA = 0;

                SHIFTREG_CLOCK = 1;
                SHIFTREG_CLOCK = 0;
            }
            SHIFTREG_LATCH = 1;
            SHIFTREG_LATCH = 0;
        }

        // Peripherals 
        if (PWM_counter >= periphBrightness) {
            Colon = 0; //turn off the colons
            PMLight = 0; //turn off PM light
        } else if ((PWM_counter < periphBrightness) && (Colon != colon_val || PMLight != PMlight_val)) {
            PMLight = PMlight_val;
            Colon = colon_val;
        }

        if (PWM_counter >= ringBrightness) {
            ALARM_LED = 0; //turn off the alarm LED
        } else if ((PWM_counter < ringBrightness) && (ALARM_LED != alarmLight_val)) {
            ALARM_LED = alarmLight_val;
        }
        //==========================================================================

        // Check to see if we are done with a PWM period
        if (PWM_counter >= 32) {
            PWM_counter = 0;
        }

    } if (TIMER1_OFLOW) { //timer 1 counter
        Timer_millis += 33; //increment by 33 ms
        TIMER1_OFLOW = 0; //reset it

    }
}

/*--- T I M E R - 0 --- N O L A N -------------*/
unsigned short long Timer_msSinceReset(void) {
    return Timer_millis;
}

void Timer_reset(void) {
    Timer_millis = 0;
}
