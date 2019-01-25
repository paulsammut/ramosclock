#include "RAWRPI_defusePanel.h"

stateRAWRPI decodeRAWRPI(RAWRPI rawrpiPacket, unsigned char tAddrHi, unsigned char tAddrLow) {
    if (rawrpiPacket.isValid) {
        switch (rawrpiPacket.rCommand) {
            case 1: //range check
                if (rawrpiPacket.rData0 == 99
                        && rawrpiPacket.rData1 == 99
                        && rawrpiPacket.rAddress1 == tAddrHi
                        && rawrpiPacket.rAddress0 == tAddrLow) {
                    return RangeCheckRequest;
                    break;
                } else if (rawrpiPacket.rData0 == 255 && rawrpiPacket.rData1 == 255) {
                    return RangeGood; //incorrect defuse code
                    break;
                }
            case 2: //defuse code
                if (rawrpiPacket.rData0 == 255 && rawrpiPacket.rData1 == 255) { //correct defuse code
                    return DefuseCodeGood;
                    break;
                } else if (rawrpiPacket.rData0 == 0 && rawrpiPacket.rData1 == 0) { //incorrect defuse code
                    return DefuseCodeBad; //incorrect defuse code
                    break;
                } else {
                    return DefuseCodeAttempt;
                    break;
                }
            case 3: //Ramos address training.
                if (rawrpiPacket.rData0 == 99 && rawrpiPacket.rData1 == 99) {
                    return AddressTrainingRequest;
                    break;
                } else if (rawrpiPacket.rData0 == 255 && rawrpiPacket.rData1 == 255) {
                    return AddressTrained; //incorrect defuse code
                    break;
                } else {
                    return AddressTrainingFail;
                    break;
                }
            case 4: //Resend the message
                return Resend;
                break;
            default:
                return Invalid;
                break;
        }
    } else
        return Invalid;
}