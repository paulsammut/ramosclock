#include <p18f45k20.h>
#include "Test_routines.h"
#include <delays.h>
#include "Ramos_sys.h"
#include "LED_display.h"
#include "RTC.h"
#include <timers.h>
#include "RAWRPI.h"
#include "CC1101_slave.h"
#include "Sound.h"

/**----------------------------------------------
 * This contains various test routines for debug. 
 */
static char brightnessLevel = 0;
static char goUpDown = 1;
static unsigned int result;
static char tempChar = 0;

void Test_blinkColonOnSec(void) {
    Delay10KTCYx(10);
    if (RTC_byte_Read(0x03) & 0b00000001)
        turnOffColon();
    else
        turnOnColon();
}

void Test_printMinSec(void) {
    //Delay10KTCYx(10);
    LED_setDisplay(0, ((RTC_byte_Read(0x04)&0b01110000) >> 4));
    LED_setDisplay(1, RTC_byte_Read(0x04)&0b00001111);
    LED_setDisplay(2, ((RTC_byte_Read(0x03)&0b01110000) >> 4));
    LED_setDisplay(3, RTC_byte_Read(0x03)&0b00001111);
}

void Test_printHrMin(void) {
    //Delay10KTCYx(10);
    result = RTC_getHours();
    result *= 100; //make room for the minutes
    result += RTC_getMinutes();
    LED_displayNumber(result);
}

void Test_pulseLights(void) {
    result = ReadTimer1();

    if (result >= 0xF000) {
        LATAbits.LATA0 = ~LATAbits.LATA0;
        LED_setBrightnessAll(brightnessLevel);
        if (goUpDown) {
            brightnessLevel++;
            if (brightnessLevel > 50) {
                goUpDown = 0;
                LED_setDisplay(0, 1);
                LED_setDisplay(1, 2);
                LED_setDisplay(2, 3);
                LED_setDisplay(3, 5);
            }
        } else {
            brightnessLevel--;
            if (brightnessLevel < 0) {
                goUpDown = 1;
                brightnessLevel = 0;
                LED_setDisplay(0, 1);
                LED_setDisplay(1, 2);
                LED_setDisplay(2, 3);
                LED_setDisplay(3, 4);
            }
        }
        WriteTimer1(0);
    }
}

void Test_Switches(void) {
    if (SWITCH_ALARM_SET)
        LED_setDisplay(0, 0);
    else
        LED_setDisplay(0, 1);
    if (SWITCH_TIME_SET)
        LED_setDisplay(1, 0);
    else
        LED_setDisplay(1, 1);
    if (SWITCH_ALARM)
        LED_setDisplay(2, 0);
    else
        LED_setDisplay(2, 1);
    if (SWITCH_KNOB)
        LED_setDisplay(3, 0);
    else
        LED_setDisplay(3, 1);
}

void Test_SwitchWithDebugAndEventBasedFunctions(void) {
    //Alarm set polling
    tempChar = pollAset();
    if (tempChar == PRESSED)
        turnOnPMLight();
    else if (tempChar == DEPRESSED)
        turnOffPMLight();
    //Time set polling
    tempChar = pollTset();
    if (tempChar == PRESSED)
        turnOnColon();
    else if (tempChar == DEPRESSED)
        turnOffColon();
    //Alarm button polling
    tempChar = pollAlarmBtn();
    if (tempChar == PRESSED) {
        LED_setDisplay(0, 6);
        LED_setDisplay(1, 9);
    } else if (tempChar == DEPRESSED) {
        LED_setDisplay(0, 0);
        LED_setDisplay(1, 0);
    }
    //Knob button polling
    tempChar = pollKnobBtn();
    if (tempChar == PRESSED) {
        LED_setDisplay(2, 6);
        LED_setDisplay(3, 9);
    } else if (tempChar == DEPRESSED) {
        LED_setDisplay(2, 0);
        LED_setDisplay(3, 0);
    }
}

void Test_basicClockFunctions(void) {
    if (!SWITCH_ALARM_SET) {
        Test_printMinSec();
    } else if (!SWITCH_KNOB)
        LED_displayNumber((unsigned int) RTC_getDay()*100 + RTC_getMonth());
    else if (!SWITCH_TIME_SET)
        LED_displayNumber(2000 + (unsigned int) RTC_getYear());
    else if (!SWITCH_ALARM)
        LED_displayNumber(RTC_getWeekday());
    else
        Test_printHrMin();
    setPM_Light(RTC_isPM());
}

void Test_photoRes(void) {

    //non blocking photo-res sensor readings
    if (ADCON0bits.GO_DONE == 0) {
        LED_displayNumber(ADRESH); // return high byte of result
        ADCON0bits.GO_DONE = 1; // start conversion
    }

    tempChar = pollAset();
    if (tempChar == PRESSED)
        turnOnPMLight();
    else if (tempChar == DEPRESSED)
        turnOffPMLight();
    tempChar = pollTset();
    if (tempChar == PRESSED)
        turnOnColon();
    else if (tempChar == DEPRESSED)
        turnOffColon();
    tempChar = pollAlarmBtn();
    if (tempChar == PRESSED)
        turnOnPMLight();
    else if (tempChar == DEPRESSED)
        turnOffPMLight();
    tempChar = pollKnobBtn();
    if (tempChar == PRESSED)
        LED_setBrightnessAll((unsigned char) (((float) ADRESH / 255)*32));
    else if (tempChar == DEPRESSED)
        LED_setBrightnessAll(32);

}

void Test_encoder(void) {
    result += pollEncoder();
    LED_displayNumber(result);
}

void Test_RF_echoAck() {
    RAWRPI tempRAWPI;
    if (GD0) {
        tempRAWPI = RF_readRAWRPI();
        tempRAWPI.isValid = 1;
        tempRAWPI.rData0 = 0xFF;
        tempRAWPI.rData1 = 0xFF;
        RF_sendRAWRPI(tempRAWPI);
        //Sound_playSpeech(SND_VOLUME);
    }
}
/*--- E E P R O M -------------*/
/*
//Didn't have the heart to erase this code

unsigned char dick = 51;
unsigned char dickHold=0;


    while (1) {
        dick += pollEncoder();

        if(pollKnobBtn() == PRESSED){//write to eeprom
            EEPROM_Write(0, dick);
            turnOnColon();
        }
        if(pollTset() == PRESSED){
            dickHold = EEPROM_Read(0);
            turnOffColon();
        }
        if(!SWITCH_TIME_SET)
            LED_displayNumber(dickHold);
        else
            LED_displayNumber(dick);
        }
 */