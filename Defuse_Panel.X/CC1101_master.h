#ifndef _CC1101_MASTER_H
#define _CC1101_MASTER_H

#include <p18f45k20.h>
#include "defusePanel_sys.h"
#include <spi.h>
#include <delays.h>
#include "RAWRPI.h"

/*--- P I N --- S E T T I N G S ------------------*/
/* Chip enable pin */
#define CSn_RF   LATAbits.LATA2
#define TRIS_CSn_RF TRISAbits.TRISA2

/** Power pins **/
#define TRIS_RF_POW TRISD
#define RF_POW LATD

/*--- I N T E R R U P T S ---------------------- */
#define GD0 PORTAbits.RA0
#define GD2 PORTAbits.RA1
#define TRIS_GD0 TRISAbits.TRISA0
#define TRIS_GD2 TRISAbits.TRISA1


/*--- C C 1 1 0 1 --- S T R O B E S --------------*/
#define SRES            0x30    //Reset the chip
#define SFSTXON         0x31    //Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1). If in RX (with CCA): Go to a wait state where only the synthesizer is running (for quick RX / TX turnaround).
#define SXOFF           0x32    //Turn off crystal oscillator.
#define SCAL            0x33    //Calibrate frequency synthesizer and turn it off. SCAL can be strobed
//from IDLE mode without setting manual calibration mode (MCSM0.FS_AUTOCAL=0)
#define SRX             0x34    //Enable RX. Perform calibration first if coming from IDLE and MCSM0.FS_AUTOCAL=1.
#define STX             0x35    //In IDLE state: Enable TX. Perform calibration first if MCSM0.FS_AUTOCAL=1.
//If in RX state and CCA is enabled: Only go to TX if channel is clear.
#define SIDLE           0x36    //Exit RX / TX, turn off frequency synthesizer and exit Wake-On-Radio mode if applicable.
#define SWOR            0x38    //Start automatic RX polling sequence (Wake-on-Radio) as described in Section 19.5 if
//WORCTRL.RC_PD=0.
#define SPWD            0x39    //Enter power down mode when CSn goes high.
#define SFRX            0x3A    //Flush the RX FIFO buffer. Only issue SFRX in IDLE or RXFIFO_OVERFLOW states.
#define SFTX            0x3B    //Flush the TX FIFO buffer. Only issue SFTX in IDLE or TXFIFO_UNDERFLOW states.
#define SWORRST         0x3C    //Reset real time clock to Event1 value.
#define SNOP            0x3D    //No operation. May be used to get access to the chip status byte.

/*--- C C 1 1 0 1 --- R E G I S T O R S ----------*/
#define	IOCFG2		0x00
#define	IOCFG1		0x01
#define	IOCFG0		0x02
#define	FIFOTHR		0x03
#define	SYNC1		0x04
#define	SYNC0		0x05
#define	PKTLEN		0x06
#define	PKTCTRL1	0x07
#define	PKTCTRL0	0x08
#define	ADDR		0x09
#define	CHANNR		0x0A
#define	FSCTRL1		0x0B
#define	FSCTRL0		0x0C
#define	FREQ2		0x0D
#define	FREQ1		0x0E
#define	FREQ0		0x0F
#define	MDMCFG4		0x10
#define	MDMCFG3		0x11
#define	MDMCFG2		0x12
#define	MDMCFG1		0x13
#define	MDMCFG0		0x14
#define	DEVIATN		0x15
#define	MCSM2		0x16
#define	MCSM1		0x17
#define	MCSM0		0x18
#define	FOCCFG		0x19
#define	BSCFG		0x1A
#define	AGCTRL2		0x1B
#define	AGCTRL1		0x1C
#define	AGCTRL0		0x1D
#define	WOREVT1		0x1E
#define	WOREVT0		0x1F
#define	WORCTRL		0x20
#define	FREND1		0x21
#define	FREND0		0x22
#define	FSCAL3		0x23
#define	FSCAL2		0x24
#define	FSCAL1		0x25
#define	FSCAL0		0x26
#define	RCCTRL1		0x27
#define	RCCTRL0		0x28
#define	FSTEST		0x29
#define	PTEST		0x2A
#define	AGCTEST		0x2B
#define	TEST2		0x2C
#define	TEST1		0x2D
#define	TEST0		0x2E

//satus registers
#define	PARTNUM         0x30
#define	VERSION         0x31
#define	FREQEST         0x32
#define	LQI             0x33
#define	RSSI            0x34
#define	MARCSTATE	0x35
#define	WORTIME1	0x36
#define	WORTIME0	0x37
#define	PKTSTATUS	0x38
#define	VCO_VC_DAC	0x39
#define	TXBYTES         0x3A
#define	RXBYTES         0x3B
#define	RCCTRL1_STATUS	0x3C
#define	RCCTRL0_STATUS	0x3D

/**
 * Define booleans
 */
#define true    1
#define false   0



#define NR_OF_CONFIG_REGISTERS 47
// list the registers in the same order as CCxRegisterSettings
// stored in progmem to save on RAM

/*
 * Initalizes the SPI system for use with the NXP RTC and CC1101
 */
void init_CC1101(void);

/**
 * Writes a byte to the RF mod by disabling interrupts first.
 * @param addr
 * @param data
 */
void RF_byte_Write(unsigned char addr, unsigned char data);

/**
 * Reads a byte by sending the address masked with the read bit
 * @param addr
 * @return
 */
unsigned char RF_byte_Read(unsigned char addr);

/**
 * Burst writes from a starting address to the end of the data
 * @param addrStart
 * @param burstData
 * @param burstDataLength
 */
void RF_burst_Write(unsigned char addrStart, unsigned char burstData[], unsigned char burstDataLength);

/**
 * Configurse the RF module with config set 1.
 */
void RF_configDefusePanel(void);

/**
 * Sends whatever strobe you wanna send.
 */
void RF_send_Strobe(unsigned char strobe);

/**
 * Put a packet in the FIFO as per Rawrpi standard.
 * @param cmd_byte
 * @param data_byte1
 * @param data_byte2
 */
void RF_send_Packet(unsigned char cmd_byte, unsigned char data_byte1, unsigned char data_byte2);

/**
 * Burst read from start address. Doesn't actually save anything yet.
 * @param addr
 * @param numBytes
 */
void RF_burst_Read(unsigned char addr, unsigned char numBytes);

/**
 * Reads the status register
 * @param addr Status register
 * @return data read
 */
unsigned char RF_read_status_Reg(unsigned char addr);

/**
 * Returns the number of RX bytes in the RX FIFO.
 * @return Number of RX bytes in the RX FIFO
 */
unsigned char RF_numBytesRX(void);

/**
 * Reads and returns a RAWRPI packet. Expects 9 bytes to be in the fifo
 * @return
 */
RAWRPI RF_readRAWRPI(void);

/**
 * Sends a RAWRPI packet as per RAWRPI standard
 * @param tempPacket
 */
void RF_sendRAWRPI(RAWRPI tempPacket);



#endif _CC1101_MASTER_H





