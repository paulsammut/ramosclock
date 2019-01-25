#include "CC1101_slave.h"

/*------------------------------------------------*/
/*------ R A M O S ------- S L A V E -------------*/
/*------------------------------------------------*/
/*
 * 10/17/12: Got rid of unused functions
 *
 */

static unsigned char CC1101_config_DefusePanel[NR_OF_CONFIG_REGISTERS] = {
    0x06, //GDO2
    0x2E, //GDO1
    0x07, //GDO0 The one we work with
    0x07,
    0xD3,
    0x91,
    0x3D,
    0x0C, //PCTCTRL1 4 is default changing it to C for use with the GDO0 0x07 due to CRC issue.
    0x05,
    0x00,
    0x00,
    0x0A,
    0x00,
    0x22,
    0xB6,
    0x27,
    0x35,
    0x83,
    0x03,
    0x21,
    0xEE,
    0x65,
    0x07,
    0x3F, //MCSM1 0x30 is default.FOr Master 3B, For slave, it will be 3F which is say in RF mode always!
    0x18, //18 is default
    0x16,
    0x6C,
    0x07,
    0x40,
    0x91,
    0x87,
    0x6B,
    0xF8,
    0x57,
    0x10,
    0xE9,
    0x2A,
    0x00,
    0x1F,
    0x41,
    0x00,
    0x59,
    0x7F,
    0x3C,
    0x88,
    0x35,
    0x09
};

/*
 * Initalizes the SPI system for use with the NXP RTC and CC1101
 */
void init_CC1101(void) {
    ANSELbits.ANS6 = 0; //digital input buffer for the GD02 pin enabled

    // Set the interrupt pins
    TRIS_GD0 = 1; //input
    TRIS_GD2 = 1; //input

    // Already openings in the Ramos_sys
//    /* SPI periphal setting */
//    TRIS_CSn_RF = 0; //CS output
//    OpenSPI(SPI_FOSC_16, MODE_00, SMPMID);

    //set the chip select to idle high
    CSn_RF = 1;


    Delay10KTCYx(100);
    //from the datasheet
    LATCbits.LATC3 = 1; //clock high
    LATCbits.LATC5 = 0; //Digital out low
    CSn_RF = 0;
    CSn_RF = 1;
    CSn_RF = 0;
    Delay10TCYx(10); //around 40us
    CSn_RF = 1;
    Delay10TCYx(10); //around 40us
    CSn_RF = 0;

    Delay10KTCYx(100);
    RF_send_Strobe(SRES); //issue reset strobe
    Delay10KTCYx(100);
    CSn_RF = 1;
    //chip is now ready to go!

    RF_send_Strobe(SIDLE);

    RF_configDefusePanel();
    RF_byte_Write(0x3E, 0xCB); //Power table

    //Put in RX mode
    RF_send_Strobe(SRX);
}

void RF_byte_Write(unsigned char addr, unsigned char data) {
    INTCONbits.GIEH = 0; // Interrupting dis
    CSn_RF = 0;
    while (PORTCbits.SDI); //wait for chip ready
    putcSPI(addr);
    putcSPI(data);
    CSn_RF = 1;
    INTCONbits.GIEH = 1; // Interrupting enabled.
}

unsigned char RF_byte_Read(unsigned char addr) {
    unsigned char var;
    INTCONbits.GIEH = 0; // Interrupting enabled.
    CSn_RF = 0;
    while (PORTCbits.SDI); //wait for chip ready
    putcSPI(addr | 0b10000000); //read mask
    var = getcSPI();
    CSn_RF = 1;
    INTCONbits.GIEH = 1; // Interrupting enabled.
    return (var);
}

void RF_burst_Write(unsigned char addrStart, unsigned char burstData[], unsigned char burstDataLength) {
    unsigned char i = 0;
    //first send the burst command with the first address
    INTCONbits.GIEH = 0; // Interrupting dis
    CSn_RF = 0;
    while (PORTCbits.SDI); //wait for chip ready
    putcSPI(addrStart | 0b01000000); //send the address masked with the Burst bit
    for (i = 0; i < burstDataLength; i++)
        putcSPI(burstData[i]);
    CSn_RF = 1;
    INTCONbits.GIEH = 1; // Interrupting enabled.
}

void RF_configDefusePanel(void) {
    RF_burst_Write(0x00, CC1101_config_DefusePanel, NR_OF_CONFIG_REGISTERS);
}

void RF_send_Strobe(unsigned char strobe) {
    INTCONbits.GIEH = 0;
    CSn_RF = 0; //set the enable pin low
    while (PORTCbits.SDI); //wait for chip ready
    putcSPI(strobe);
    CSn_RF = 1; //set the enable pin high
    INTCONbits.GIEH = 1;
}

void RF_send_Packet(unsigned char cmd_byte, unsigned char data_byte1, unsigned char data_byte2) {
    //set the TX fifo:
    CSn_RF = 0; //set the enable pin low
    while (PORTCbits.SDI); //wait for chip ready
    putcSPI(0x7f); //send out the tx fifo address for burst byte access to TX FIFO
    putcSPI(4); //send out the packet length byte (address + data)
    putcSPI(0); //send out the address byte
    putcSPI(cmd_byte); //send out the command byte
    putcSPI(data_byte1); //send out the data byte
    putcSPI(data_byte2); //send out the data byte
    CSn_RF = 1; //set the enable pin high
    RF_send_Strobe(STX);
}

void RF_burst_Read(unsigned char addr, unsigned char numBytes) {
    unsigned char i = 0;
    CSn_RF = 0; //enable set low
    while (PORTCbits.SDI); //wait for chip ready
    putcSPI(addr | 0xC0); //add the read and burst bit
    for (i = 0; i < numBytes; i++) {
        putcSPI(SNOP);
    }
    CSn_RF = 1;
}

/* UNUSED 10/17/12 */
//unsigned char RF_read_status_Reg(unsigned char addr) {
//    unsigned char var;
//    CSn_RF = 0; //enable set low
//    while (PORTCbits.SDI); //wait for chip ready
//    putcSPI(addr | 0xC0); //add the read and burst bit
//    var = getcSPI();
//    CSn_RF = 1;
//    return var;
//}

void RF_sendRAWRPI(RAWRPI tempPacket) {
    //make sure we don't have any junk in the trunk
    RF_send_Strobe(SIDLE);
    RF_send_Strobe(SFRX);
    CSn_RF = 0; //set the enable pin low
    while (PORTCbits.SDI); //wait for chip ready
    putcSPI(0x7f); //send out the tx fifo address for burst byte access to TX FIFO
    putcSPI(6); //send out the packet length byte (address + data)
    putcSPI(0); //send out the address byte
    putcSPI(tempPacket.rAddress1); //send out the address high byte
    putcSPI(tempPacket.rAddress0); //send out the address low byte
    putcSPI(tempPacket.rCommand); //send out the command byte
    putcSPI(tempPacket.rData1); //send out the data1 byte
    putcSPI(tempPacket.rData0); //send out the data0 byte
    CSn_RF = 1; //set the enable pin high

    RF_send_Strobe(STX); //make sure we are in TX mode

}

RAWRPI RF_readRAWRPI(void) {
    RAWRPI tempP;
    unsigned char tNumBytes = RF_numBytesRX();
    //we are expecting an RX fifo that contains 9 bytes
    if (tNumBytes == 9) {
        CSn_RF = 0; //set the enable pin low

        while (PORTCbits.SDI); //wait for chip ready
        putcSPI(0x3F | 0xC0); // burst read the RX FIFO
        /*--- Read the packet ----------*/
        getcSPI(); //first byte is crap
        getcSPI(); //2nds byte is the address which is 0
        tempP.rAddress1 = getcSPI();
        tempP.rAddress0 = getcSPI();
        tempP.rCommand = getcSPI();
        tempP.rData1 = getcSPI();
        tempP.rData0 = getcSPI();
        getcSPI(); //byte is crap
        getcSPI(); //byte is crap


        CSn_RF = 1; //set the enable pin high

        //the packet is valid
        tempP.isValid = VALID;
    } else {
        RF_burst_Read(0x3F, tNumBytes);

        //The packet we received is invalid because it is incomplete.
        tempP.isValid = INVALID;
    }

    return tempP;
}

unsigned char RF_numBytesRX(void) {
    unsigned char var;
    CSn_RF = 0; //enable set low
    while (PORTCbits.SDI); //wait for chip ready
    putcSPI(RXBYTES | 0xC0); //add the read and burst bit for the num RX bytes fifo
    var = getcSPI();
    CSn_RF = 1;
    return var;
}



