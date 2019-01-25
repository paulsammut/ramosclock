#include "RAWRPI.h"

stateRAWRPI decodeRAWRPI(RAWRPI *rawrpiPacket, unsigned char tAddr1, unsigned char tAddr0) {
    if (rawrpiPacket->isValid) {
        switch (rawrpiPacket->rCommand) {
            case 1: //range check
                if (rawrpiPacket->rData0 == 99
                        && rawrpiPacket->rData1 == 99
                        && rawrpiPacket->rAddress1 == tAddr1
                        && rawrpiPacket->rAddress0 == tAddr0) {
                    return RangeCheckRequest;
                } else if (rawrpiPacket->rData0 == 255 && rawrpiPacket->rData1 == 255) {
                    return RangeGood; //incorrect defuse code
                } else
                    return Invalid;
                break;
            case 2: //defuse code
                if (rawrpiPacket->rData0 == 255 && rawrpiPacket->rData1 == 255) { //correct defuse code
                    return DefuseCodeGood;
                } else if (rawrpiPacket->rData0 == 0 && rawrpiPacket->rData1 == 0) { //incorrect defuse code
                    return DefuseCodeBad; //incorrect defuse code
                } else {
                    return DefuseCodeAttempt;
                }
                break;
            case 3: //Ramos address training.
                if (rawrpiPacket->rData0 == 99 && rawrpiPacket->rData1 == 99) {
                    return AddressTrainingRequest;
                } else if (rawrpiPacket->rData0 == 255 && rawrpiPacket->rData1 == 255) {
                    return AddressTrained; //Address properly trained
                } else {
                    return AddressTrainingFail;
                }
                break;
            case 4: //Resend the message
                return Resend;
                break;
            case 5: //Factory default set back
                if (rawrpiPacket->rData0 == 99 && rawrpiPacket->rData1 == 99) {
                    return FactoryResetRequest;
                } else if (rawrpiPacket->rData0 == 255 && rawrpiPacket->rData1 == 255) {
                    return FactoryResetGood;
                } else {
                    return FactoryResetFail;
                }
                break;
            default:
                return Invalid;
                break;
        }
    } else
        return Invalid;
}

