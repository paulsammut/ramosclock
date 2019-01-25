#ifndef SOUND_H
#define SOUND_H

#include "p18f45k20.h"
#include "delays.h"
#include "Ramos_sys.h"

#define WT588D_Data LATCbits.LATC2
#define WT588D_Reset LATCbits.LATC1
/*Tested! This works. */
#define WT588D_Not_Busy PORTAbits.RA2

/* Device commands */
#define VOLUME_7    0xE7
#define VOLUME_6    0xE6
#define VOLUME_5    0xE5
#define VOLUME_4    0xE4
#define VOLUME_3    0xE3
#define VOLUME_2    0xE2
#define VOLUME_1    0xE1
#define VOLUME_0    0xE0

enum SOUNDS {
    //Menu options
    SND_REMOTEALARMSYSTEM=0,
    SND_RANDOM_DEFUSE,
    SND_ALARM_TONE,
    SND_LOCKDOWNMODE,
    SND_COURTESYMODE,
    SND_COURTESYMODEPERIOD,
    SND_NUMSNOOZES,
    SND_SNOOZE_PERIOD,
    SND_DAY,
    SND_MONTH,
    SND_YEAR,
    SND_DATE_FORMAT,
    SND_TWENTY4HOURMODE,
    SND_PMLIGHT24HR,
    SND_DIGITCYCLING,
    SND_BRIGHTNESS,
    SND_AUTODIMLEVEL,
    //System sounds
    SND_DAYMONTH,
    SND_MONTHDAY,
    SND_ACTIVATED,
    SND_DEACTIVATED,
    SND_GOODBYE,
    SND_WELCOMEMENU,
    SND_STARTUP,
    START_ALARM_TONES,
    ALARM_TONE_OFFSET = START_ALARM_TONES - 1,
    SND_TONE_1 = START_ALARM_TONES,
    SND_TONE_2,
    SND_TONE_3,
    SND_TONE_4,
    SND_TONE_5,
    SND_TONE_6,
    SND_TONE_7,
    SND_TONE_8,
    SND_TONE_9,
    //Custom tone
    //SND_TONE_CUST,
    /** End of alarm tones **/
    END_ALARM_TONES,
    NUM_ALARM_TONES = END_ALARM_TONES - START_ALARM_TONES - 1
};

/**
 * Sends a byte to the sound module
 * @param soundData Byte to send to the sound module
 */
void Sound_playSpeech(unsigned char soundData);

void Sound_loopPlay(void);

/**TEST
 * Initializes the sound module
 */
void init_Sound(void);

/**
 * Stops the playback.
 */
void Sound_shutUp(void);

/**
 * Sets the volume while something is playing.
 * @param volParam volume VOLUME_0 - VOLUME_6
 */
void Sound_setVolume(unsigned char vol);

/**
 * Plays a sound with associated volume. Use VOLUME_0 - VOLUME_7 definitions for volume. 0 is lowest and 7 is loudes
 * @param soundData speech address
 * @param volParam volume VOLUME_0 - VOLUME_6
 */
void Sound_playSpeechVol(unsigned char soundData, unsigned char volParam);

/**
 * Returns 1 if busy, 0 if not busy
 * @return
 */
unsigned char Sound_isBusy(void);


#endif SOUND_H