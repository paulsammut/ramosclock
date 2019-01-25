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
#include "RAWRPI.h"


#pragma idata


#pragma code

void main() {
    RAWRPI rawrp;

    unsigned char panelMode;
    unsigned int keypadNumReturn;


    initDefusePanel();
    init_keypad();
    init_CC1101();
    
    //This was added on 10/12/13 to allow the guy that is programming these fucking things
    //to quickly and definitively asses if the RGB LED works. We have had issues with 
    //certain colors not working in the LED, and without this check you'll find out 
    //after you solder on a keypad which is too late as it involves more rework.
    
    //go red
    setLights(0,1,1);
    Delay10KTCYx(15); //100ms
    //go green
    setLights(1,0,1);
    Delay10KTCYx(15); //100ms
    //end of light check
    checkBattery();


    //set the temp packet address
    rawrp.rAddress1 = getAddr1();
    rawrp.rAddress0 = getAddr0();


    panelMode = DEFUSECODEENTRY;

    while (1) {

        ClrWdt(); //clear the 1 second watch dog

        switch (panelMode) {
            case DEFUSECODEENTRY:
                showStandbyLight(); //set back to solid blue as we are now in business
                keypadNumReturn = handleUserInput(4);
                if (keypadNumReturn == HASH) {
                    panelMode = RANGECHECK;
                } else if (keypadNumReturn > 9999) {//star code entry
                    panelMode = STARCODEENTRY;
                } else { //this means we have a defuse code to send to the clocky clock
                    panelMode = DEFUSECODESEND;
                }
                break;
            case RANGECHECK:
                CMD_HANDLER_rangeCheck();
                panelMode = DEFUSECODEENTRY;
                break;
            case STARCODEENTRY:
                solidPink();
                if (keypadNumReturn == CODE_ADDRTRAIN) { //code for address pairing
                    CMD_HANDLER_addrTrain();
                }else if(keypadNumReturn == CODE_FACTORY_RESET_REQUEST){
                    CMD_HANDLER_factoryReset();
                }
                panelMode = DEFUSECODEENTRY;
                break;
            case DEFUSECODESEND:
                CMD_HANDLER_defuseCodeSend(keypadNumReturn);
                panelMode = DEFUSECODEENTRY;
                break;
            default:
                break;
        }
    }
}
