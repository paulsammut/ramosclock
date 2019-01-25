/* 
 * File:   defusePanel_main.c
 * Author: paul
 *
 * Created on July 4, 2012, 11:34 PM
 */

#include "EEPROM.h"


#include <p18f45k20.h>
#include "defusePanel_sys.h"
#include "keypad.h"
#include "CC1101_master.h"
#include "lightPlay.h"
#include <delays.h>
#include "RAWRPI_defusePanel.h"
#include <stdlib.h>


#pragma idata


#pragma code

void main() {

    RAWRPI tempRarwpi;
    RAWRPI rawrp;
    unsigned char panelMode;
    unsigned int keypadNumReturn;
    unsigned int addr;

    initDefusePanel();
    init_keypad();
    init_CC1101();

    checkBattery();

    //Read the address byte

    //set the temp packet address
    rawrp.rAddress1 = EEPROM_SETTINGS.addrHi;
    rawrp.rAddress0 = EEPROM_SETTINGS.addrLow;


    panelMode = DEFUSECODEENTRY;


    while (1) {
        //shutOffTickTock();
        ClrWdt(); //clear the 1 second watch dog

        switch (panelMode) {
            case DEFUSECODEENTRY:
                keypadNumReturn = handleUserInput(4);
                if (keypadNumReturn == HASH) {
                    panelMode = RANGECHECK;
                } else if (keypadNumReturn > 9999) {//star code entry
                    panelMode = STARCODEENTRY;
                } else { //this means we have a defuse code to send to the clocky clock
                    //send defuse code and check for proper ACK
                    //mode stays in DEFUSECODEENTRY
                }
                break;
            case RANGECHECK:
                rangeCheck();
                panelMode = DEFUSECODEENTRY;
                break;
            case STARCODEENTRY:
                solidPink();
                //we take the code from last poll:
                if (keypadNumReturn == CODE_ADDRTRAIN) { //code for address pairing
                    //Generate a new random address
                    addr = rand(); //random number for 0x0000 to 0x7FFF
                    EEPROM_SETTINGS.addrHi = (unsigned char) ((addr & 0xFF00) >> 8);
                    EEPROM_SETTINGS.addrLow = (unsigned char) (addr & 0xFF);
                    //build the command packet:
                    rawrp.rAddress1 = EEPROM_SETTINGS.addrHi;
                    rawrp.rAddress0 = EEPROM_SETTINGS.addrLow;
                    rawrp.rCommand = CMD_ADDRTRAIN;
                    rawrp.rData1 = 99; //request
                    rawrp.rData0 = 99; //request
                    //broadcast it to any listening ramos that is in training mode
                    tempRarwpi = sendRAWRPI(rawrp);
                    if (tempRarwpi.isValid
                            && tempRarwpi.rAddress1 == EEPROM_SETTINGS.addrHi
                            && tempRarwpi.rAddress0 == EEPROM_SETTINGS.addrLow
                            && tempRarwpi.rData1 == 255
                            && tempRarwpi.rData0 == 255) { //succeeded in pairing!
                        //write to EEPROM
                        EEPROM_Write(0, EEPROM_SETTINGS.addrHi);
                        EEPROM_Write(1, EEPROM_SETTINGS.addrLow);
                        solidGreen();
                        Delay10KTCYx(50);
                    } else {
                        solidRed();
                        Delay10KTCYx(50);
                    }
                }
                panelMode = DEFUSECODEENTRY;
                break;
            default:
                break;
        }
    }
}
