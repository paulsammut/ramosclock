

/** I N C L U D E S **************************************************/
#include "defusePanel_sys.h"

/** C O N F I G U R A T I O N   B I T S ******************************/
#pragma config FOSC = INTIO67, FCMEN = OFF, IESO = OFF                      // CONFIG1H
#pragma config PWRT = OFF, BOREN = OFF, BORV = 30                           // CONFIG2L
#pragma config WDTEN = OFF, WDTPS = 8192                                    // CONFIG2H
#pragma config MCLRE = ON, LPT1OSC = OFF, PBADEN = OFF, CCP2MX = PORTC       // CONFIG3H
#pragma config STVREN = ON, LVP = OFF, XINST = OFF                          // CONFIG4L
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF                   // CONFIG5L
#pragma config CPB = OFF, CPD = OFF                                         // CONFIG5H
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF               // CONFIG6L
#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF                           // CONFIG6H
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF           // CONFIG7L
#pragma config EBTRB = OFF                                                  // CONFIG7H


#pragma idata
/* Counts how many seconds we've waited in inactivty */
unsigned char shutOffCounter = 0;
/* Time treshold in seconds of how long to stay on while inactive*/
unsigned char shutOffTime = 10;

#pragma udata
EEPROM_settings EEPROM_SETTINGS;

#pragma code

/** P R O T O T Y P E S **********************************************/
static void wakeUp();

void initDefusePanel(void) {


    //Get rid of the analog input stuff
    ANSELH = 0x00; // AN8-12 are digital inputs (AN12 on RB0)

    /*--- P O W E R - O P T I M I Z A T I O N ----------*/
    // As per http://ww1.microchip.com/downloads/en/AppNotes/01416a.pdf
    // "An unused I/O pin should be left unconnected, but configured as an output pin, driving to either state (high or
    //  low)
    TRISA = 0; //output
    TRISB = 0; //output
    TRISC = 0; //output
    TRISD = 0; //output
    TRISE = 0; //output
    LATA = 0;
    LATB = 0;
    //LATC = 0;
    LATD = 0;
    //LATE has the LEDS on the line, so leave it high
    LATE = 0xFF;


    /*--- S Y S - C O N F I G --------------------------*/
    OSCCONbits.IRCF = 0b110; //8 mhz clock
    // Delay10K(10) is 50 ms

    //Set the LEDs as outputs
    TRIS_Blue = 0;
    TRIS_Green = 0;
    TRIS_Red = 0;

    //Go Orange
    Blue = 1;
    Red = 0;
    Green = 0;

    /**--- L O W - B A T T - D E T E C T ---------------*/
    //enable the HLVD
    HLVDCONbits.HLVDL = 0b0100; //2.3 volts so 1.15
    HLVDCONbits.VDIRMAG = 0;
    HLVDCONbits.HLVDEN = 1;
    //clear the interrupt flag
    PIR2bits.HLVDIF = 0;
    LATDbits.LATD0 = 1; //debug
    while (!HLVDCONbits.IRVST); //wait for stability

    /*--- T I M E R S ---------------------------------*/
    OpenTimer0(TIMER_INT_OFF &
            T0_16BIT &
            T0_SOURCE_INT &
            T0_PS_1_32);
    //with 32 prescale and Fosc/4 (no PLL), timer0's flag on INTCONbits.TMR0IF will
    //toggle every 1.05 seconds

    /*--- W A T C H - D O G - T I M E R -------------*/
    WDTCONbits.SWDTEN = 1;

    /*--- EEPROM LOAD -------------------------------*/

    EEPROM_SETTINGS.addrHi = EEPROM_Read(0);
    EEPROM_SETTINGS.addrLow = EEPROM_Read(1);

    RF_send_Strobe(STX);

}

void enterSleep(void) {
    RF_send_Strobe(SIDLE);
    RF_send_Strobe(SPWD);
    CSn_RF = 1;
    CloseTimer0();
    CloseSPI();
    WDTCONbits.SWDTEN = 0; //turn off the WDT
    //RF_POW = 0; This actually makes the unit draw more
    //All off
    Blue = 1;
    Red = 1;
    Green = 1;

    //Peripheral shut-down
    HLVDCONbits.HLVDEN = 0;
    CVRCON = 0;
    CVRCON2 = 0;
    CCP1CON = 0;
    CCP2CON = 0;
    CM2CON0bits.C2ON = 0;
    CM1CON0bits.C1ON = 0;
    OSCCONbits.IDLEN = 0; //enter sleep on sleep instruction
    SSPCON1bits.SSPEN = 0;
    T1CONbits.T1OSCEN = 0; //nada

    //Set the RB ports to low to make sure we're good for wakeup
    Row0 = 0;
    Row1 = 0;
    Row2 = 0;
    Row3 = 0;

    //Enabling the interrupts on the keypad lines INT0 INT1 and INT2
    INTCONbits.GIE = 1;
    RCONbits.IPEN = 0; //no priority levels please

    //clear the flags
    INTCONbits.INT0IF = 0;
    INTCON3bits.INT1IF = 0;
    INTCON3bits.INT2IF = 0;

    INTCON2bits.INTEDG0 = 0; //trigger on a falling edge
    INTCON2bits.INTEDG1 = 0; //trigger on a falling edge
    INTCON2bits.INTEDG2 = 0; //trigger on a falling edge

    INTCONbits.INT0IE = 1;
    INTCON3bits.INT1IE = 1;
    INTCON3bits.INT2IE = 1;

    Sleep();

}

void checkBattery(void) {
    if (PIR2bits.HLVDIF) {//Battery low!!!!!
        PIR2bits.HLVDIF = 0;
        Red = 0;
        Blue = 1;
        Green = 1;
        blinkRed();
    } else {
        Red = 1;
        Blue = 0;
        Green = 1;
        blinkBlue();
    }
}

void shutOffTickTock(void) {
    if (TIMER0_FLAG) {
        shutOffCounter++;
        TIMER0_FLAG = 0;
    }
    //if we have wated till our shut off time
    if (shutOffCounter >= shutOffTime) {
        enterSleep();
    }
}

void resetTickTock(void) {
    shutOffCounter = 0;
}

#pragma code InterruptVectorHigh= 0x08

void InterruptVectorHigh(void) {
    _asm
    goto wakeUp //jump to interrupt routine
            _endasm
}
#pragma interruptlow wakeUp

static void wakeUp() {
    INTCONbits.INT0IF = 0;
    INTCON3bits.INT1IF = 0;
    INTCON3bits.INT2IF = 0;
    INTCONbits.GIE = 0;
    Reset();
}

RAWRPI sendRAWRPI(RAWRPI rawrpiPacket) {
    RAWRPI retRAWRPI;
    char sendRetries = 3;
    //starts off being invalid
    retRAWRPI.isValid = INVALID;

    while (sendRetries > 0) {
        //send the packet
        RF_sendRAWRPI(rawrpiPacket);
        //We're using the 16 bit Timer0 that overflows every 1,048.576 ms. Every count is .016ms
        WriteTimer0(0);
        while (!GD0 && (ReadTimer0() < 18750)) {
        }; //120ms is 7500 counts
        if (GD0) {
            retRAWRPI = RF_readRAWRPI();
            retRAWRPI.isValid = VALID;
            sendRetries = 0;
        } else
            sendRetries--; //we didn't get an ACK back, so lets retry.
    }
    //flush the buffers
    return retRAWRPI; //return whether or not we succeeded in sending.
}

unsigned int handleUserInput(char numDigits) {
    unsigned char tempPressVal;
    unsigned int inputVal = 0;
    char curPlace = (numDigits - 1); //left most number of the digit.
    while (curPlace >= 0) {
        ClrWdt();
        //shutOffTickTock();
        tempPressVal = pollKeypad(); //grab an event from the keypad poller
        if (tempPressVal == HASH) { //we need to break outta here cause HASH is coming
            inputVal = HASH;
            break;
        } else if (tempPressVal != NOPRESS) { //we actually have a digit press
            blinkRed();
            inputVal += (tempPressVal * pow(10, curPlace));
            curPlace--;
        }
    }
    return inputVal;
}

void rangeCheck(void) {
    RAWRPI RC_tempRawrp;
    RAWRPI rawrpReturn;
    //orange is the "thinking light"
    solidOrange();
    RC_tempRawrp.rCommand = 1;
    RC_tempRawrp.rData1 = 99;
    RC_tempRawrp.rData0 = 99;
    rawrpReturn = sendRAWRPI(RC_tempRawrp);
    if (decodeRAWRPI(rawrpReturn,
            EEPROM_SETTINGS.addrHi,
            EEPROM_SETTINGS.addrLow)== RangeGood) {
        solidGreen();
    }
    //try again to make sure
    rawrpReturn = sendRAWRPI(RC_tempRawrp);
    if (decodeRAWRPI(rawrpReturn,
            EEPROM_SETTINGS.addrHi,
            EEPROM_SETTINGS.addrLow)== RangeGood) {
        solidGreen();
        Delay10KTCYx(80);
        solidBlue();
    } else {
        blinkRed();
        blinkRed();
        blinkRed();
        blinkRed();
        blinkRed();
        blinkRed();
        blinkRed();
        solidRed();
    }
}