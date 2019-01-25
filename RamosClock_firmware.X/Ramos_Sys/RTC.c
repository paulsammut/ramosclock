/**
 * Sammut Tech LLC, (C) 10/17/12
 *
 * 10/17/12:
 *
 * Cleaned up all the unused functions
 *
 */


#include "Ramos_sys.h"
#include "p18f45k20.h"
#include <timers.h>
#include <spi.h>
#include "RTC.h"

/**-- S P I - C O M M S -----------------------------*/
#define RTC_Control_1   0x00
#define RTC_Control_2   0x01
#define RTC_Control_3   0x02
#define RTC_Seconds     0x03
#define RTC_Mins        0x04
#define RTC_Hours       0x05
#define RTC_Days        0x06
#define RTC_Weekdays    0x07
#define RTC_Months      0x08
#define RTC_Years       0x09

//used as a dummy holder for spi comms


unsigned char RTC_tempChar1;
#pragma code

void RTC_init(void) {
    /* RTC initilization */
    RTC_byte_Write(0x03, 0x00); //resets the OSF flag. PAge 7 of the DS
}

void RTC_byte_Write(unsigned char addr, unsigned char data) {
    INTCONbits.GIEH = 0; // Interrupting dis
    CS_RTC = 0;
    putcSPI(addr | 0b00100000); //write mask
    putcSPI(data);
    CS_RTC = 1;
    INTCONbits.GIEH = 1; // Interrupting enabled.
}

unsigned char RTC_byte_Read(unsigned char addr) {
    unsigned char var;
    INTCONbits.GIEH = 0; // Interrupting enabled.
    CS_RTC = 0;
    putcSPI(addr | 0b10100000); //read mask
    var = getcSPI();
    CS_RTC = 1;
    INTCONbits.GIEH = 1; // Interrupting enabled.
    return (var);
}

unsigned char RTC_getSeconds(void) {
    unsigned char RTC_tempChar;
    unsigned char RTC_tempChar1;
    RTC_tempChar = RTC_byte_Read(RTC_Seconds);
    RTC_tempChar1 = ((RTC_tempChar & 0b01110000) >> 4)*10; // mask and power up tens number
    RTC_tempChar1 += (RTC_tempChar & 0b00001111);
    return RTC_tempChar1;
}

void RTC_setSeconds(unsigned char secsSet) {
    unsigned char RTC_tempChar;
    unsigned char RTC_tempChar1;
    RTC_tempChar = (secsSet % 10); //ones place
    RTC_tempChar1 = secsSet / 10;
    RTC_tempChar1 = RTC_tempChar1 << 4; //shift over 4 places
    RTC_tempChar |= RTC_tempChar1; //add the ones to the byte
    RTC_byte_Write(RTC_Seconds, RTC_tempChar);
}

unsigned char RTC_getMinutes(void) {
    unsigned char RTC_tempChar;
    unsigned char RTC_tempChar1;
    RTC_tempChar = RTC_byte_Read(RTC_Mins);
    RTC_tempChar1 = ((RTC_tempChar & 0b01110000) >> 4)*10; // mask and power up tens number
    RTC_tempChar1 += (RTC_tempChar & 0b00001111);
    return RTC_tempChar1;
}

void RTC_setMinutes(unsigned char minsSet) {
    unsigned char RTC_tempChar;
    unsigned char RTC_tempChar1;
    RTC_tempChar = (minsSet % 10); //ones place
    RTC_tempChar1 = minsSet / 10;
    RTC_tempChar1 = RTC_tempChar1 << 4; //shift over 4 places
    RTC_tempChar |= RTC_tempChar1; //add the ones to the byte
    RTC_byte_Write(RTC_Mins, RTC_tempChar);
}

unsigned char RTC_getHours(void) {
    unsigned char RTC_tempChar;
    unsigned char RTC_tempChar1;
    //if 12 hour mode:
    if (RTC_is12Hours()) {
        RTC_tempChar = RTC_byte_Read(RTC_Hours);
        RTC_tempChar1 = ((RTC_tempChar & 0b00010000) >> 4)*10; //mask and power up the tens
        RTC_tempChar1 += (RTC_tempChar & 0b00001111);
    } else { //24 mode
        RTC_tempChar = RTC_byte_Read(RTC_Hours);
        RTC_tempChar1 = ((RTC_tempChar & 0b00110000) >> 4)*10; //mask and power up the tens
        RTC_tempChar1 += (RTC_tempChar & 0b00001111);
    }
    return RTC_tempChar1;
}

void RTC_setHours(unsigned char hoursSet) {
    unsigned char RTC_tempChar;
    unsigned char RTC_tempChar1;
    RTC_tempChar = (hoursSet % 10); //ones place
    RTC_tempChar1 = hoursSet / 10;
    RTC_tempChar1 = RTC_tempChar1 << 4; //shift over 4 places
    RTC_tempChar |= RTC_tempChar1; //add the ones to the byte
    RTC_byte_Write(RTC_Hours, RTC_tempChar);
}

void RTC_setHoursAMPM(unsigned char hoursSet, unsigned char AMPMset) {
    unsigned char RTC_tempChar;
    unsigned char RTC_tempChar1;
    RTC_tempChar = (hoursSet % 10); //ones place
    RTC_tempChar1 = hoursSet / 10;
    RTC_tempChar1 = RTC_tempChar1 << 4; //shift over 4 places
    RTC_tempChar |= RTC_tempChar1; //add the ones to the byte
    RTC_tempChar |= (AMPMset << 5);
    RTC_byte_Write(RTC_Hours, RTC_tempChar);
}

unsigned char RTC_is12Hours(void) {
    unsigned char RTC_tempChar;
    RTC_tempChar = RTC_byte_Read(RTC_Control_1);
    RTC_tempChar &= 0b00000100; //isolate the 12/24 hour bit
    RTC_tempChar = RTC_tempChar >> 2; //shift the bit to the right 3 bits.
    return (RTC_tempChar);
}

void RTC_set1224(unsigned char set1224) {
    if (set1224)//setting 12 hour mode
        RTC_byte_Write(RTC_Control_1, 0b00000100);
    else //setting 24 hour mode
        RTC_byte_Write(RTC_Control_1, 0b00000000);
}

void RTC_setDay(unsigned char daySet) {
    unsigned char RTC_tempChar;
    unsigned char RTC_tempChar1;
    RTC_tempChar = (daySet % 10); //ones place
    RTC_tempChar1 = daySet / 10;
    RTC_tempChar1 = RTC_tempChar1 << 4; //shift over 4 places
    RTC_tempChar |= RTC_tempChar1; //add the ones to the byte
    RTC_byte_Write(RTC_Days, RTC_tempChar);
}

unsigned char RTC_getDay(void) {
    unsigned char RTC_tempChar;
    unsigned char RTC_tempChar1;
    RTC_tempChar = RTC_byte_Read(RTC_Days);
    RTC_tempChar1 = ((RTC_tempChar & 0b00110000) >> 4)*10; // mask and power up tens number
    RTC_tempChar1 += (RTC_tempChar & 0b00001111);
    return RTC_tempChar1;
}

/* UNUSED 10/17/12 */
//unsigned char RTC_getWeekday(void) {
//    unsigned char RTC_tempChar;
//    unsigned char RTC_tempChar1;
//    RTC_tempChar = RTC_byte_Read(RTC_Weekdays);
//    RTC_tempChar1 = (RTC_tempChar & 0b00000111);
//    return RTC_tempChar1;
//}

void RTC_setWeekday(unsigned char weekdaySet) {
    RTC_byte_Write(RTC_Weekdays, weekdaySet);
}

void RTC_setYear(unsigned char yearSet) {
    unsigned char RTC_tempChar;
    unsigned char RTC_tempChar1;
    RTC_tempChar = (yearSet % 10); //ones place
    RTC_tempChar1 = yearSet / 10;
    RTC_tempChar1 = RTC_tempChar1 << 4; //shift over 4 places
    RTC_tempChar |= RTC_tempChar1; //add the ones to the byte
    RTC_byte_Write(RTC_Years, RTC_tempChar);
}

unsigned char RTC_getYear(void) {
    unsigned char RTC_tempChar;
    unsigned char RTC_tempChar1;
    RTC_tempChar = RTC_byte_Read(RTC_Years);
    RTC_tempChar1 = ((RTC_tempChar & 0b11110000) >> 4)*10; // mask and power up tens number
    RTC_tempChar1 += (RTC_tempChar & 0b00001111);
    return RTC_tempChar1;
}

unsigned char RTC_getMonth(void) {
    unsigned char RTC_tempChar;
    unsigned char RTC_tempChar1;
    RTC_tempChar = RTC_byte_Read(RTC_Months);
    RTC_tempChar1 = ((RTC_tempChar & 0b00010000) >> 4)*10; // mask and power up tens number
    RTC_tempChar1 += (RTC_tempChar & 0b00001111);
    return RTC_tempChar1;
}

void RTC_setMonth(unsigned char monthSet) {
    unsigned char RTC_tempChar;
    unsigned char RTC_tempChar1;
    RTC_tempChar = (monthSet % 10); //ones place
    RTC_tempChar1 = monthSet / 10;
    RTC_tempChar1 = RTC_tempChar1 << 4; //shift over 4 places
    RTC_tempChar |= RTC_tempChar1; //add the ones to the byte
    RTC_byte_Write(RTC_Months, RTC_tempChar);
}

/* UNUSED 10/17/12 */
//unsigned char RTC_isPM() {
//    unsigned char RTC_tempChar;
//    RTC_tempChar = RTC_byte_Read(RTC_Hours) & 0b00100000; //get the AMPM bit
//    RTC_tempChar = RTC_tempChar >> 5;
//    return RTC_tempChar;
//}

/* UNUSED 10/17/12 */
//void RTC_setTime12hr(unsigned char secsSet, unsigned char minsSet, unsigned char hoursSet, unsigned char AMPMset) {
//    RTC_set1224(_12HOUR);
//    RTC_setSeconds(secsSet);
//    RTC_setMinutes(minsSet);
//    RTC_setHoursAMPM(hoursSet, AMPMset);
//}

/* UNUSED 10/17/12 */
//void RTC_setTime24hr(unsigned char secsSet, unsigned char minsSet, unsigned char hoursSet) {
//    RTC_set1224(_24HOUR);
//    RTC_setSeconds(secsSet);
//    RTC_setMinutes(minsSet);
//    RTC_setHours(hoursSet);
//}

/* UNUSED 10/17/12 */
//void RTC_setDate(unsigned char dayOfWeekSet, unsigned char daySet, unsigned char monthSet, unsigned char yearSet) {
//    RTC_setWeekday(dayOfWeekSet);
//    RTC_setDay(daySet);
//    RTC_setMonth(monthSet);
//    RTC_setYear(yearSet);
//}
//
