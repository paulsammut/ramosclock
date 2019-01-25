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
} RAWRPI;

typedef enum stateRAWRPI {
    Resend,
    DefuseCodeAttempt,
    DefuseCodeGood,
    DefuseCodeBad,
    AddressTrainingRequest,
    AddressTrained,
    AddressTrainingFail,
    RangeCheckRequest,
    RangeGood,
    FactoryResetRequest,
    FactoryResetGood,
    FactoryResetFail,
    Invalid
} stateRAWRPI;

/* RAWRPI Packet data valid */
#define VALID           1
/* RAWRPI Packet data invalid (bad address) */
#define INVALID         0

/* RAWRPI Packet send success */
#define SEND_SUCCESS    1
/* RAWRPI Packet send fail  */
#define SEND_FAIL       0

/*--- P R O T O T Y P E S ---*/
/**
 * 
 * @param r
 * @return State returned by the packet.
 */
/**
 * Decodes and returns the message the received RAWRPI packet is relaying.
 * @param rawrpiPacket awrpiPacket Packet to pass in
 * @param tAddr1
 * @param tAddr0
 * @return 
 */
stateRAWRPI decodeRAWRPI(RAWRPI *rawrpiPacket, unsigned char tAddr1, unsigned char tAddr0);



#endif _RAWRPI_H