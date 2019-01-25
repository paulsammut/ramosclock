/**
 * -----------------------------------------------------
 * SAMMUT TECH LLC
 * -----------------------------------------------------
 * Sound system file.
 *
 * 10/17/12: Cleaned up all the unused code
 *
 */

#include "Sound.h"


static void send_Zero(void);
static void send_One(void);
static void send_CMD(unsigned char CMD);
static void reset_Chip(void);

unsigned char waitingForBusy = 0;

void init_Sound(void) {
    //Set up the tris bits of port C2 which is P1A
    ANSELbits.ANS2 = 0; //Digital input buffer of RA2, the Busy input line is enabled
    TRISCbits.RC2 = 0; //set as output
    TRISCbits.RC1 = 0; //set the reset line as input
    TRISAbits.RA2 = 1; //set the busy line as input

    WT588D_Reset = 1; //idle high
    WT588D_Data = 1; //idle high

    //Sound_setVolume(6);

}

void Sound_shutUp(void) {
    waitingForBusy = 0;
    send_CMD(0xFE); //stops playback
    WT588D_Data = 1; //idle high added on 8/2/12
    //avoid a pop
    //Delay1KTCYx(0xFF);
}

/* UNUSED 10/17/12 */
//void Sound_setVolume(unsigned char vol) {
//    switch (vol) {
//        case 0:
//            send_CMD(VOLUME_0);
//            break;
//        case 1:
//            send_CMD(VOLUME_1);
//            break;
//        case 2:
//            send_CMD(VOLUME_2);
//            break;
//        case 3:
//            send_CMD(VOLUME_3);
//            break;
//        case 4:
//            send_CMD(VOLUME_4);
//            break;
//        case 5:
//            send_CMD(VOLUME_5);
//            break;
//        case 6:
//            send_CMD(VOLUME_6);
//            break;
//        default:
//            ;
//    }
//}

void Sound_loopPlay() {
    send_CMD(0xF2);
}

void Sound_playSpeech(unsigned char soundData) {

    Sound_shutUp(); //avoid a pop incase of playing sound when another one is playing
    //reset_Chip();

    INTCONbits.GIE = 0; // Disable interrupts;F
    WT588D_Data = 0;
    //wait 5 ms
    //Delay1KTCYx(14); //correction of 8/3/2012... for some reason the clock is fucked. THIS WAS WITH THE OLD V1 code
    Delay1KTCYx(40); //a proper 5 ms delay
    //--------------------------------
    

    //-- SEND THE BITS!! -------------
    if (soundData & 0b00000001)
        send_One();
    else
        send_Zero();
    if (soundData & 0b00000010)
        send_One();
    else
        send_Zero();
    if (soundData & 0b00000100)
        send_One();
    else
        send_Zero();
    if (soundData & 0b00001000)
        send_One();
    else
        send_Zero();
    if (soundData & 0b00010000)
        send_One();
    else
        send_Zero();
    if (soundData & 0b00100000)
        send_One();
    else
        send_Zero();
    if (soundData & 0b01000000)
        send_One();
    else
        send_Zero();
    if (soundData & 0b10000000)
        send_One();
    else
        send_Zero();

    Delay100TCYx(32); //Idle for a bit in case we stack commands. added 11/21
    INTCONbits.GIE = 1; // enable interrupts
    WT588D_Data = 1; //idle high

    // Set the waiting for busy high so that we know that we need to wait for the busy line to go low first.
    waitingForBusy = 1;

    //Delay10KTCYx(30); //wait for the busy line to pop high   This is the OLD way of doing it, AKA the BAD WAY. Now doing it with waiting for busy. This hangs up the system
}

static void send_CMD(unsigned char CMD) {

    INTCONbits.GIE = 0; // Disable interrupts
    //reset_Chip();
    WT588D_Data = 0;
    //wait 5 ms
    Delay1KTCYx(40); //5ms as 1 = 0.144ms
    //--------------------------------
    
    //-- SEND THE BITS!! -------------
    if (CMD & 0b00000001)
        send_One();
    else
        send_Zero();
    if (CMD & 0b00000010)
        send_One();
    else
        send_Zero();
    if (CMD & 0b00000100)
        send_One();
    else
        send_Zero();
    if (CMD & 0b00001000)
        send_One();
    else
        send_Zero();
    if (CMD & 0b00010000)
        send_One();
    else
        send_Zero();
    if (CMD & 0b00100000)
        send_One();
    else
        send_Zero();
    if (CMD & 0b01000000)
        send_One();
    else
        send_Zero();
    if (CMD & 0b10000000)
        send_One();
    else
        send_Zero();

    Delay100TCYx(32); //Idle for a bit in case we stack commands. added 11/21
    INTCONbits.GIE = 1; // Enable interrupts
}

static void send_Zero(void) {
    WT588D_Data = 1;
    //wait 200us
    //Delay100TCYx(14); old and wrong
    Delay100TCYx(16); //corrected 8/2
    WT588D_Data = 0;
    //Delay100TCYx(29); old and wrong
    Delay100TCYx(32); //corrected 8/2
    WT588D_Data = 1;
}

static void send_One(void) {
    WT588D_Data = 1;
    //wait 200us
    Delay100TCYx(32);
    WT588D_Data = 0;
    Delay100TCYx(16);
    WT588D_Data = 1;
}

static void reset_Chip(void) {
    //--- Preamble -------------
    WT588D_Reset = 0;
    //wait 5 ms
    // Delay1KTCYx(35); //5ms as 1 = 0.144ms
    Delay1KTCYx(15); //Updated on 8/3
    WT588D_Reset = 1;
    //wait 17 ms
    Delay1KTCYx(49); //Updated on 8/3
}

unsigned char Sound_isBusy(void) {
    unsigned char tempRetVal;

    //If the line hasn't dipped low yet, we're still busy!!!
    if(waitingForBusy & WT588D_Not_Busy){
        tempRetVal = 1;
    }else if(~WT588D_Not_Busy){
        tempRetVal = 1;
        waitingForBusy = 0;
    }else
        tempRetVal = 0;

    /* OBSELETE GARBAGE */
    //turn off the ADC so that the RA2
    //    ADCON0bits.ADON = 0; //turn ADC off
    //    TRISAbits.RA2 = 1; //input
    //    ANSELbits.ANS2 = 0;
    //tempRetVal = (~WT588D_Not_Busy) & 1; //i'm only after the last bit
    //    ADCON0bits.ADON = 1;

    return tempRetVal;
}
