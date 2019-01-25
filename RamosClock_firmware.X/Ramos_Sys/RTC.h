#ifndef RTC_H
#define RTC_H


#define _12HOUR 1
#define _24HOUR 0



/**
 * Writes a byte to the SPI port. Does not handle CS!
 * @param addr Command/Address byte
 * @param data Data byte
 */
void RTC_byte_Write(unsigned char addr, unsigned char data);

/**
 * Reads a byte to the SPI port. Does not handle CS!
 * @param addr Command/Address byte
 * @return  data read from device
 */
unsigned char RTC_byte_Read(unsigned char addr);

/**
 * Returns the seconds as an unsigned byte.
 * @return
 */
unsigned char RTC_getSeconds(void);

/**
 * Returns the minutes as an unsigned char.
 * @return Minutes
 */
unsigned char RTC_getMinutes(void);

/**
 * Returns either 12 or 24 hours depending on the RTC setting.
 * @return
 */
unsigned char RTC_getHours(void);

/**
 * Sets the RTC seconds
 * @param secsSet Seconds to set the RTC
 */
void RTC_setSeconds(unsigned char secsSet);

/**
 * Sets the minutes of the clock
 * @param minsSet Minutes to set the RTC
 */
void RTC_setMinutes(unsigned char minsSet);

/**
 * Returns 1 if system is in 12 hour mode. 0 if 24 hour mode.
 * @return
 */
unsigned char RTC_is12Hours(void);

/**
 * Sets the hours based on whether the clock is set at 12 or 24 hours.
 * @param hoursSet This number sets the hours. Must put in the correct format, either 12 or 24.
 */
void RTC_setHours(unsigned char hoursSet);

/**
 * Sets the 12 or 24 hour mode. 0 for 24, 1 for 12 hour,
 * @param set1224 0 for 24, 1 for 12 hour
 */
void RTC_set1224(unsigned char set1224);

/**
 * Sets the day
 * @param daySet
 */
void RTC_setDay(unsigned char daySet);

/**
 * Gets the day
 * @return Day 0-31
 */
unsigned char RTC_getDay(void);

/**
 * Sets the weekday 0, Sunday, through 6, Saturday.
 * @param weekdaySet 0-6 corresping to Sunday (0) through Saturday (6)
 */
void RTC_setWeekday(unsigned char weekdaySet);

/**
 * Gets the weekday
 * @return 0-6 corresping to Sunday (0) through Saturday (6)
 */
unsigned char RTC_getWeekday(void);

/**
 * Sets the year 0-99
 * @param yearSet 0-99
 */
void RTC_setYear(unsigned char yearSet);

/**
 * Gets the year 0-99
 * @return 0-99
 */
unsigned char RTC_getYear(void);

/**
 * Sets the month 0-12
 * @param monthSet 0-12, month
 */
void RTC_setMonth(unsigned char monthSet);

/**
 * Gets the month, 0-12
 * @return Month, 0-12
 */
unsigned char RTC_getMonth(void);

/**
 * Sets the hours in 12 Hour mode along with the AM/PM bit.
 * @param hoursSet Hours in 12 Hour mode
 * @param AMPMset AM = 0, PM = 1;
 */
void RTC_setHoursAMPM(unsigned char hoursSet, unsigned char AMPMset);

/**
 * Returns 1 if PM, 0 if AM
 * @return 1 if PM, 0 if AM
 */
unsigned char RTC_isPM(void);

/**
 * Sets all the time stuff for 12 hour mode
 * @param secsSet 0-59
 * @param minsSet 0-59
 * @param hoursSet 0-12
 * @param AMPMset 0 for AM, 1 for PM
 */
void RTC_setTime12hr(unsigned char secsSet, unsigned char minsSet, unsigned char hoursSet, unsigned char AMPMset);

/**
 * Sets all the time stuff for 24 hour mode
 * @param secsSet 0-59
 * @param minsSet 0-59
 * @param hoursSet 0-23
 */
void RTC_setTime24hr(unsigned char secsSet, unsigned char minsSet, unsigned char hoursSet);

/**
 * Sets all the date stuff
 * @param dayOfWeekSet 0 (Sunday) through 6 (Saturday)
 * @param daySet Day of the month. BE CAREFUL WITH FEBRUARY AND LEAP YEARS. Set VALID days.
 * @param monthSet 0-12 Month set up
 * @param yearSet 0-99 year.
 */
void RTC_setDate(unsigned char dayOfWeekSet, unsigned char daySet, unsigned char monthSet, unsigned char yearSet);

/**
 * Resets the OSF flag. Page 7 of the DS
 */
void RTC_init(void);

#endif RTC_H

