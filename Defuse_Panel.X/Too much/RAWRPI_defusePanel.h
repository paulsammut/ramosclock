#ifndef _RAWRPI_H
#define _RAWRPI_H


/*--- R A W R P I --------------*/
typedef struct {
    /* Address high byte */
    unsigned char rAddress1;
    /* Address low byte */
    unsigned char rAddress0;
    /* Command */
    unsigned char rCommand;
    /* Data 1 */
    unsigned char rData1;
    /* Data 0 */
    unsigned char rData0;
    /* 1 if valid, 0 if  not valid*/
    unsigned char isValid;
}RAWRPI;

typedef enum {
    Resend,
    DefuseCodeAttempt,
    DefuseCodeGood,
    DefuseCodeBad,
    AddressTrainingRequest,
    AddressTrained,
    AddressTrainingFail,
    RangeCheckRequest,
    RangeGood,
    Invalid
}stateRAWRPI;


#define VALID 1
#define INVALID 0

/*--- P R O T O T Y P E S ---*/
/**
 * Decodes and returns the message the received RAWRPI packet is relaying.
 * @param rawrpiPacket Packet o pass in
 * @return State returned by the packet. 
 */
stateRAWRPI decodeRAWRPI(RAWRPI rawrpiPacket, unsigned char tAddrHi, unsigned char tAddrLow);




#endif _RAWRPI_H