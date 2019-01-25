

/** I N C L U D E S **************************************************/
#include "defusePanel_sys.h"

/** C O N F I G U R A T I O N   B I T S ******************************/
#pragma config FOSC = INTIO67, FCMEN = OFF, IESO = OFF                      // CONFIG1H
#pragma config PWRT = OFF, BOREN = ON, BORV = 18                           // CONFIG2L
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
unsigned char shutOffTime = 19;
unsigned int RF_TIMER = 0;
/* If in the past it was turned off, then turn it on! */
unsigned char PWM_past = 0;

#pragma udata
unsigned char SYS_addr0;
unsigned char SYS_addr1;
unsigned char PWM_enable;
unsigned char PWM_blueOldVal;
unsigned char PWM_redOldVal;
unsigned char PWM_greenOldVal;

#pragma code

/** P R O T O T Y P E S **********************************************/

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
    setLights(0, 0, 1);

    /**--- L O W - B A T T - D E T E C T ---------------*/
    //enable the HLVD
    //HLVDCONbits.HLVDL = 0b0100; //2.3 volts so 1.15
    HLVDCONbits.HLVDL = 0b0111; //2.46 2.61 2.76 (min typ max)
    HLVDCONbits.VDIRMAG = 0;
    HLVDCONbits.HLVDEN = 1;
    //clear the interrupt flag
    PIR2bits.HLVDIF = 0;
    while (!HLVDCONbits.IRVST); //wait for stability

    /*--- T I M E R S ---------------------------------*/
    /* Turn on Timer0. This is the PWM interrupt timer to make the LEDs not so
     * fucking bright. */
    T0CONbits.T08BIT = 1; //8 Bit timer
    T0CONbits.T0PS = 0b010; //1:16 prescale value
    T0CONbits.PSA = 0; //Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output.
    T0CONbits.T0CS = 0; //Internal instruction cycle clock (CLKOUT)
    T0CONbits.TMR0ON = 1; //Turn timer0 on
    INTCONbits.TMR0IF = 0; //Clear the Interrupt Flag
    INTCONbits.TMR0IE = 1; //enable the timer0 interrupt


    /* Turn on Timer 1, this shuts off the units when not in use. */
    T1CONbits.T1CKPS = 0b11; //1:8 prescale
    T1CONbits.TMR1CS = 0; //Internal clock
    T1CONbits.TMR1ON = 1; //turn the timer on

    /*--- I N T E R R U P T S ------------------------*/
    RCONbits.IPEN = 0; //no priority levels please
    INTCONbits.GIE = 1; // enable interrupts
    INTCONbits.PEIE = 1; // enable peripheral interrupts.

    //Read the address bytes from memory
    SYS_addr0 = EEPROM_Read(MEM_SYS_ADDR0);
    SYS_addr1 = EEPROM_Read(MEM_SYS_ADDR1);

}

void enterSleep(void) {
    INTCONbits.GIE = 0; //so we don't get interrupted
    RF_send_Strobe(SIDLE);
    RF_send_Strobe(SPWD);
    CSn_RF = 1;
    T0CONbits.TMR0ON = 0; //stop Timer 0
    INTCONbits.TMR0IE = 0; //turn off the interrupt
    INTCONbits.TMR0IF = 0; //clear the flag
    T1CONbits.TMR1ON = 0; //stop Timer 1
    PIE1bits.TMR1IE = 0; //turn off the interrupt enable.
    PIR1bits.TMR1IF = 0; //clear the flag

    CloseSPI();

    RF_POW = 0; //as of 11/6/12 this works well.
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
    PIR1bits.TMR1IF = 0; //clear the timer1 interrupt flag

    //clear the flags
    INTCONbits.INT0IF = 0;
    INTCON3bits.INT1IF = 0;
    INTCON3bits.INT2IF = 0;

    INTCON2bits.INTEDG0 = 0; //trigger on a falling edge
    INTCON2bits.INTEDG1 = 0; //trigger on a falling edge
    INTCON2bits.INTEDG2 = 0; //trigger on a falling edge

    //enable the external interrupts
    INTCONbits.INT0IE = 1;
    INTCON3bits.INT1IE = 1;
    INTCON3bits.INT2IE = 1;

    Sleep();

}

void checkBattery(void) {
    if (PIR2bits.HLVDIF) {//Battery to no PWM point
        // check for No PWM point
        PIR2bits.HLVDIF = 0;
        PWM_enable = 0; //turn off the PWM to make the LEDs brighter
        // check for Low Voltage point
        HLVDCONbits.HLVDL = 0b0101; //2.37 volts so 1.185
        while (!HLVDCONbits.IRVST); //wait for stability
        PIR2bits.HLVDIF = 0;
        if (PIR2bits.HLVDIF) { //   Low voltage point
            setLights(0, 1, 1);
            blinkRed();
            setStandbyLight(0); //low battery red standby light
        }

    } else {
        setLights(1, 1, 0);
        blinkBlue();
        setStandbyLight(1); //blue standby light.
        PWM_enable = 1; //turn on the PWM to not make it so fucking bright
    }
}

void shutOffTickTock(void) {
    if (PIR1bits.TMR1IF) {
        shutOffCounter++;
        PIR1bits.TMR1IF = 0;
    }
    //if we have wated till our shut off time
    if (shutOffCounter >= shutOffTime) {
        enterSleep();
    }
}

void resetTickTock(void) {
    shutOffCounter = 0;
}

#pragma code isr = 0x08
#pragma interrupt isr

void isr(void) {
    if (INTCONbits.TMR0IF) { //this is the PWM routine

        //=====================================
        //shutOffTickTock();
        if (PIR1bits.TMR1IF) {
            shutOffCounter++;
            PIR1bits.TMR1IF = 0;
        }
        //if we have wated till our shut off time
        if (shutOffCounter >= shutOffTime) {
            enterSleep();
        }
        //------------------------------------
        
        RF_TIMER++; //this is for the RF delay wait
        INTCONbits.TMR0IF = 0; //set the overflow to 0
        if (PWM_enable) { //PWM is enabled, so we'll go ahead with the dimming
            if (PWM_past < 6) { //If we haven't turned it off in the past, then turn the lights off
                //then turn them off
                Red = 1;
                Green = 1;
                Blue = 1;
                PWM_past++; //note it down that we turned the light off
            } else { //they were off in the past, so turn them on
                Blue = PWM_blueOldVal;
                Green = PWM_greenOldVal;
                Red = PWM_redOldVal;
                PWM_past = 0; //note it down that we turned the lights on
            }
        } else {
            LATEbits.LATE0 = PWM_blueOldVal;
            LATEbits.LATE1 = PWM_greenOldVal;
            LATEbits.LATE2 = PWM_redOldVal;
        }
    } else {
        //this is the wake up routine
        //Reset(); OLD CODE before ISR change
        _asm reset _endasm
    }
}

#pragma code

RAWRPI sendRAWRPI(RAWRPI rawrpiPacket) {
    RAWRPI retRAWRPI;
    char sendRetries = 1;
    //starts off being invalid
    retRAWRPI.isValid = INVALID;

    while (sendRetries > 0) {
        //send the packet
        RF_sendRAWRPI(rawrpiPacket);
        //We're using the 16 bit Timer0 that overflows every 1,048.576 ms. Every count is .016ms
        RF_TIMER = 0;
        while (!GD0 && (RF_TIMER < 300)) {
            //RF_send_Strobe(SNOP); //for debug to monitor the module's state
        }; //120ms is 7500 counts //300 is 18750
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
        shutOffTickTock();
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

unsigned char getAddr0(void) {
    return SYS_addr0;
}

void setAddr0(unsigned char set_addr) {
    SYS_addr0 = set_addr;
}

unsigned char getAddr1(void) {
    return SYS_addr1;
}

void setAddr1(unsigned char set_addr) {
    SYS_addr1 = set_addr;
}

void CMD_HANDLER_rangeCheck(void) {
    RAWRPI RC_tempRawrp;
    RAWRPI rawrpReturn;
    //white is the "thinking light"
    solidWhite();
    RC_tempRawrp.rAddress0 = SYS_addr0;
    RC_tempRawrp.rAddress1 = SYS_addr1;
    RC_tempRawrp.rCommand = 1;
    RC_tempRawrp.rData1 = 99;
    RC_tempRawrp.rData0 = 99;
    rawrpReturn = sendRAWRPI(RC_tempRawrp);
    if (decodeRAWRPI(&rawrpReturn, SYS_addr1, SYS_addr0) == RangeGood) {
        solidGreen();
    }
    //try again to make sure
    rawrpReturn = sendRAWRPI(RC_tempRawrp);
    if (decodeRAWRPI(&rawrpReturn,
            SYS_addr1,
            SYS_addr0) == RangeGood) {
        solidGreen();
        Delay10KTCYx(80);
        showStandbyLight();

    } else {
        blinkRed();
        blinkRed();
        blinkRed();
        blinkRed();
        blinkRed();
        blinkRed();
        blinkRed();
        showStandbyLight();
    }
    resetTickTock();
}

void CMD_HANDLER_addrTrain(void) {
    RAWRPI tempRawrpi;
    int addr;
    unsigned char Temp_addr0;
    unsigned char Temp_addr1;
    //Generate a new random address
    srand(ReadTimer0());
    addr = rand(); //random number for 0x0000 to 0x7FFF
    Temp_addr1 = (unsigned char) ((addr & 0xFF00) >> 8);
    Temp_addr0 = (unsigned char) (addr & 0xFF);
    //build the command packet:
    tempRawrpi.rAddress1 = Temp_addr1;
    tempRawrpi.rAddress0 = Temp_addr0;
    tempRawrpi.rCommand = CMD_ADDRTRAIN;
    tempRawrpi.rData1 = 99; //request
    tempRawrpi.rData0 = 99; //request
    //broadcast it to any listening ramos that is in training mode
    tempRawrpi = sendRAWRPI(tempRawrpi);
    //lets see what get after we sent it out:
    if (tempRawrpi.isValid
            && tempRawrpi.rAddress1 == Temp_addr1
            && tempRawrpi.rAddress0 == Temp_addr0
            && tempRawrpi.rData1 == 255
            && tempRawrpi.rData0 == 255) { //succeeded in pairing!
        //write to EEPROM
        EEPROM_Write(MEM_SYS_ADDR1, Temp_addr1);
        EEPROM_Write(MEM_SYS_ADDR0, Temp_addr0);
        //set the system address to the temp so that its set for if we want to
        //use the pad during this session
        SYS_addr0 = Temp_addr0;
        SYS_addr1 = Temp_addr1;
        solidGreen();
        Delay10KTCYx(50);
    } else {
        solidRed();
        Delay10KTCYx(50);
        blinkRed();
        blinkRed();
        blinkRed();
        solidRed();
        Delay10KTCYx(50);
        showStandbyLight();
    }
}

void CMD_HANDLER_factoryReset(void) {
    RAWRPI tempRawrpi;
    //build the command packet:
    tempRawrpi.rAddress1 = SYS_addr1;
    tempRawrpi.rAddress0 = SYS_addr0;
    tempRawrpi.rCommand = CMD_FACTORYRESET;
    tempRawrpi.rData1 = 99; //request
    tempRawrpi.rData0 = 99; //request
    //broadcast it to the listening ramos
    tempRawrpi = sendRAWRPI(tempRawrpi);
    //lets see what get after we sent it out:
    if (tempRawrpi.isValid
            && tempRawrpi.rCommand == 5
            && tempRawrpi.rAddress1 == SYS_addr1
            && tempRawrpi.rAddress0 == SYS_addr0
            && tempRawrpi.rData1 == 255
            && tempRawrpi.rData0 == 255) { //succeeded in resetting!
        solidGreen();
        Delay10KTCYx(50);
        showStandbyLight();
    } else {
        solidRed();
        Delay10KTCYx(50);
        blinkRed();
        blinkRed();
        blinkRed();
        solidRed();
        Delay10KTCYx(50);
        showStandbyLight();
    }
}

void CMD_HANDLER_defuseCodeSend(unsigned int codeParam) {
    RAWRPI RC_tempRawrp;
    RAWRPI rawrpReturn;
    unsigned char b1; //high byte
    unsigned char b0; //low byte

    b0 = (unsigned char) (codeParam % 100);
    b1 = (unsigned char) (codeParam / 100);

    solidWhite(); //white is the "thinking light"
    RC_tempRawrp.rAddress0 = SYS_addr0;
    RC_tempRawrp.rAddress1 = SYS_addr1;
    RC_tempRawrp.rCommand = 2;
    RC_tempRawrp.rData1 = b1;
    RC_tempRawrp.rData0 = b0;
    RC_tempRawrp.isValid = 1; //just to be nice
    rawrpReturn = sendRAWRPI(RC_tempRawrp);
    if (rawrpReturn.isValid
            && rawrpReturn.rAddress1 == SYS_addr1
            && rawrpReturn.rAddress0 == SYS_addr0
            && rawrpReturn.rData1 == 255
            && rawrpReturn.rData0 == 255) { //succeeded in defusing!

        blinkGreen();
        blinkGreen();
        blinkGreen();
        solidGreen();
        Delay10KTCYx(0xFF);
        enterSleep();


    } else {
        blinkRed();
        blinkRed();
        blinkRed();
        blinkRed();
        showStandbyLight();
    }

}

void setLights(unsigned char lRed, unsigned char lGreen, unsigned char lBlue) {
    PWM_blueOldVal = lBlue;
    PWM_greenOldVal = lGreen;
    PWM_redOldVal = lRed;
}

unsigned char getRedOldVal(void) {
    return PWM_redOldVal;
}

unsigned char getGreenOldVal(void) {
    return PWM_greenOldVal;
}

unsigned char getBlueOldVal(void) {
    return PWM_blueOldVal;
}