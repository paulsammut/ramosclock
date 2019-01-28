/**
 * -----------------------------------------------------
 * SAMMUT TECH LLC
 * -----------------------------------------------------
 * LED Ramos system file.
 */

#include "Ramos_sys.h"


/** C O N F I G U R A T I O N   B I T S ******************************/
// CONFIG1H
#pragma config FOSC = INTIO67   // Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)

#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)

#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)


// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)

#pragma config BOREN = ON      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)

#pragma config BORV = 30        // Brown Out Reset Voltage bits (VBOR set to 3.0 V nominal)


// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bit (WDT is controlled by SWDTEN bit of the WDTCON register)

#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)


// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)

#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)

#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)

#pragma config HFOFST = ON      // HFINTOSC Fast Start-up (HFINTOSC starts clocking the CPU without waiting for the oscillator to stablize.)

#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)


// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)

#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)

#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))


// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000800-001FFFh) not code-protected)

#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (002000-003FFFh) not code-protected)

#pragma config CP2 = OFF        // Code Protection Block 2 (Block 2 (004000-005FFFh) not code-protected)

#pragma config CP3 = OFF        // Code Protection Block 3 (Block 3 (006000-007FFFh) not code-protected)


// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)

#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)


// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-001FFFh) not write-protected)

#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (002000-003FFFh) not write-protected)

#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (004000-005FFFh) not write-protected)

#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (006000-007FFFh) not write-protected)


// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)

#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)

#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)


// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)

#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)

#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)

#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)


// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)                                             // CONFIG7H


/**--- V A R I A B L E S ---------------*/
// Toggle filter counter for alarm and time setting
static unsigned int filterToggle1 = 0;
static unsigned int filterToggle2 = 0;
// Alarm button counter
static unsigned int filterAlarm = 0;
//Knob switch filter
static unsigned int filterKnobSw = 0;
//Values from the last event
static unsigned char SW_ASET_OLD;
static unsigned char SW_TSET_OLD;
static unsigned char SW_ALRM_OLD;
static unsigned char SW_KNOB_OLD;

//return value
static unsigned char retVal = 0;

static unsigned char RESULT;

//encoder vars
static char ENC_A_OLD;
static char ENC_B_OLD;
static unsigned int filterA = 0;
static unsigned int filterB = 0;
static unsigned int filterCnt = 1;
static unsigned char changeA = 0;
static unsigned char changeB = 0;
static char retValSigned = 0;



/* UNUSED 10/17/12 */
//void show_time() {
//    //Delay10KTCYx(10);
//    RESULT = RTC_getHours();
//    RESULT *= 100; //make room for the minutes
//    RESULT += RTC_getMinutes();
//    Display_showNumber(RESULT);
//}

void init_Ramos_sys(void) {
    /*--- CLOCK SETTING ---*/
    ANSEL = 0x00;
    ANSELH = 0x00;
    OSCCONbits.IRCF = 0b110; //8mHz clock
    OSCTUNEbits.PLLEN = 1; //enable 4x multiplier

    /* --- PIN SETTINGS ---*/
    TRISB = 0xFF; //All inputs
    INTCON2bits.RBPU = 0; //Enable the pullups
    WPUB = 0xFF; //All pullups on

    //10-16-12 Debugging the lag in the menu option
    //TRISCbits.RC6 = 1; //input


    //lights are output
    TRISAbits.RA7 = 0; //Alarm LED    
    TRISAbits.RA3 = 0; //Colon output
    TRISAbits.RA4 = 0; //PM Light


    /* General purpose timer */
    // PIR1bits.TMR1IF overflows every 32ms.
    OpenTimer1(TIMER_INT_OFF &
            T1_8BIT_RW &
            T1_SOURCE_INT &
            T1_PS_1_4 &
            T1_OSC1EN_OFF &
            T1_SYNC_EXT_OFF);
    T1CONbits.T1OSCEN = 0; //for some reason the open timer opens the fucking oscilator. Which disables my my RC0 pin.
    PIR1bits.TMR1IF = 0; //clear roll over interrupt flag
    IPR1bits.TMR1IP = 0; //display is a low priority interrupt
    PIE1bits.TMR1IE = 1; //enable the timer overflow interrupt

    // Set up global interrupts
    RCONbits.IPEN = 1; // Enable priority levels on interrupts
    INTCONbits.GIEL = 1; // Low priority interrupts allowed
    INTCONbits.GIEH = 1; // Interrupting enabled.

    /* SPI periphal setting */
    TRISAbits.RA0 = 0; //CS output
    TRISAbits.RA1 = 0; //CS output
    OpenSPI(SPI_FOSC_16, MODE_00, SMPMID);
    //set the chip select to idle high
    CS_RF = 1;
    CS_RTC = 1;


    /** --- Switch stuff ---*/
    SW_ALRM_OLD = SWITCH_ALARM;
    SW_ASET_OLD = SWITCH_ALARM_SET;
    SW_KNOB_OLD = SWITCH_KNOB;
    SW_TSET_OLD = SWITCH_TIME_SET;

    /** --- SUBSYSTEM INITS ---*/
    init_Sound();

    /** --- E N C O D E R ------*/
    ENC_A_OLD = ENC_A;
    ENC_B_OLD = ENC_B;

    /**---A N A L O G - I N I T --*/
    TRISAbits.RA5 = 1; //set as an input
    ANSELbits.ANS4 = 1; //turn on the AN4 analog channel that's connected to the photores
    //Set up the analog convertor
    ADCON2 = 0b00111101; // 2us Tad, 4Tad (8us) aquisition time for the sample
    //Set the voltage references to Vss to Vdd
    ADCON1bits.VCFG1 = 0; //set neg ref to Vss
    ADCON1bits.VCFG0 = 0; //set pos ref to Vdd
    ADCON0 = 0b00010011; //Select the right channel and turn the bitch on AND start converting

}

unsigned char pollAset(void) {
    retVal = 0;
    if (SWITCH_ALARM_SET != SW_ASET_OLD) {//we have a change, but we must filter
        filterToggle1++;
        if (filterToggle1 >= 100) {
            if (SWITCH_ALARM_SET == 0)
                retVal = PRESSED;
            else
                retVal = DEPRESSED;
            SW_ASET_OLD = SWITCH_ALARM_SET;
            filterToggle1 = 0;
        }
    } else {
        filterToggle1 = 0; //reset if we get any other change
    }
    return retVal;
}

unsigned char pollTset(void) {
    retVal = 0;
    if (SWITCH_TIME_SET != SW_TSET_OLD) {//we have a change, but we must filter
        filterToggle2++;
        if (filterToggle2 >= 100) {
            if (SWITCH_TIME_SET == 0)
                retVal = PRESSED;
            else
                retVal = DEPRESSED;
            SW_TSET_OLD = SWITCH_TIME_SET;
            filterToggle2 = 0;
        }
    } else {
        filterToggle2 = 0; //reset if we get any other change
    }
    return retVal;
}

unsigned char pollAlarmBtn(void) {
    retVal = 0;
    if (SWITCH_ALARM != SW_ALRM_OLD) {//we have a change, but we must filter
        filterAlarm++;
        if (filterAlarm >= 10) { //Changed to 10 from 100 and made it much more responsive.
            if (SWITCH_ALARM == 0)
                retVal = PRESSED;
            else
                retVal = DEPRESSED;
            SW_ALRM_OLD = SWITCH_ALARM;
            filterAlarm = 0;
        }
    } else {
        filterAlarm = 0; //reset if we get any other change
    }
    return retVal;
}

unsigned char pollKnobBtn(void) {
    retVal = 0;
    if (SWITCH_KNOB != SW_KNOB_OLD) {//we have a change, but we must filter
        filterKnobSw++;
        if (filterKnobSw >= 20) { //modified it to 20 from 100 after it was too slow to react
            if (SWITCH_KNOB == 0)
                retVal = PRESSED;
            else
                retVal = DEPRESSED;
            SW_KNOB_OLD = SWITCH_KNOB;
            filterKnobSw = 0;
        }
    } else {
        filterKnobSw = 0; //reset if we get any other change
    }
    return retVal;
}

char pollEncoder(void) {
    retValSigned = 0;
    /*------- A - C H A N G E ----------------*/
    if (ENC_A != ENC_A_OLD) {//we have a change, but we must filter
        filterA++;
        if (filterA >= filterCnt) { //filter's good, we actually have a change inA
            if (ENC_A == 1)
                changeA = LOW2HIGH;
            else
                changeA = HIGH2LOW;
            ENC_A_OLD = ENC_A;
            filterA = 0;
        }
    }/*------- B - C H A N G E ----------------*/
    else if (ENC_B != ENC_B_OLD) {//we have a change, but we must filter
        filterB++;
        if (filterB >= filterCnt) { //filter's good, we actually have a change inA
            if (ENC_B == 1)
                changeB = LOW2HIGH;
            else
                changeB = HIGH2LOW;
            ENC_B_OLD = ENC_B;
            filterB = 0;
        }
    }

    /*---- Q U A D R A T U R E - L O G I C ----*/
    if (changeA == LOW2HIGH) {
        if (ENC_B)//if encoder b is low (remember there are pullups, so enc low is line high
            retValSigned = -1; // we are incremening positive
        else
            retValSigned = 1;
    } else if (changeA == HIGH2LOW) {
        if (!ENC_B)//if encoder b is low (remember there are pullups, so enc low is line high
            retValSigned = -1; // we are incremening positive
        else
            retValSigned = 1;
    } else if (changeB == LOW2HIGH) {
        if (!ENC_A)//if encoder b is low (remember there are pullups, so enc low is line high
            retValSigned = -1; // we are incremening positive
        else
            retValSigned = 1;
    } else if (changeB == HIGH2LOW) {
        if (ENC_A)//if encoder b is high (remember there are pullups, so enc low is line high
            retValSigned = -1; // we are incremening positive
        else
            retValSigned = 1;
    }

    changeA = 0;
    changeB = 0;

    return retValSigned;
}

unsigned char photoResVal(void){
    unsigned char tempRetVal;
    ADCON0bits.GO_DONE = 1; // start conversion
    while(ADCON0bits.GO_DONE == 1); // start conversion)
    tempRetVal = 255-ADRESH;
    return tempRetVal;

}
