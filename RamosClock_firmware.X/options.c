#include "options.h"
#include "EEPROM.h"

void setDefaultOptions(unsigned char *options)
{
    options[REMOTE_ALARM] = 1;
    options[NUM_SNOOZES] = 0;
    options[SNOOZE_PERIOD] = 5;  // change back
    options[LOCKDOWN] = 0;
    options[COURTESY] = 0;
    options[COURTESY_PERIOD] = 10;
    options[TWENTY4_HOUR] = 0;
    options[BRIGHTNESS] = 10;
    options[AUTO_DIM_LEVEL] = 10;
    options[DEFUSE_CODE] = 0;
    options[DIGIT_CYCLING] = 1;
    options[ALARM_TONE] = START_ALARM_TONES+1;
    options[PM_LIGHT_24HR_VAL] = 1;
    options[DATE_FORMAT] = 1;

    // date
    options[YEAR] = 15;
    options[MONTH] = 10;
    options[DAY] = 12;

}

unsigned char optionUpper(State * state, unsigned int opt)
{
    switch(opt)
    {
        case DAY:
            return maxDays(state);
        case MONTH:
            return 12;
        case YEAR:
            return 99;
        case REMOTE_ALARM:
            return 1;
        case NUM_SNOOZES:
            return 10;
        case SNOOZE_PERIOD:
            return 60;
        case LOCKDOWN:
            return 1;
        case COURTESY:
            return 1;
        case COURTESY_PERIOD:
            return 60;
        case TWENTY4_HOUR:
            return 1;
        case BRIGHTNESS:
            return 10;
        case AUTO_DIM_LEVEL:
            return 10; // equal to brightness
        case DEFUSE_CODE:
            return 1;
        case DIGIT_CYCLING:
            return 1;
        case ALARM_TONE:
            return END_ALARM_TONES - 1;
        case PM_LIGHT_24HR_VAL:
            return 1;
        case DATE_FORMAT:
            return 1;
        default:
            /* Undefined state*/
            ;
    }
    return 0;
}

unsigned char optionLower(State * state, unsigned int opt)
{
    switch(opt)
    {
        case DAY:
            return 1;
        case MONTH:
            return 1;
        case YEAR:
            return 0;
        case REMOTE_ALARM:
            return 0;
        case NUM_SNOOZES:
            return 0;
        case SNOOZE_PERIOD:
            return 5;
        case LOCKDOWN:
            return 0;
        case COURTESY:
            return 0;
        case COURTESY_PERIOD:
            return 5;
        case TWENTY4_HOUR:
            return 0;;
        case BRIGHTNESS:
            return 1;
        case AUTO_DIM_LEVEL:
            return 0;
        case DEFUSE_CODE:
            return 0;
            break;
        case DIGIT_CYCLING:
            return 0;
        case ALARM_TONE:
            return START_ALARM_TONES;
        case PM_LIGHT_24HR_VAL:
            return 0;
        case DATE_FORMAT:
            return 0;
        default:
            /* Undefined state*/
            ;
    }
    return 0;
}

unsigned char optionIncrement(unsigned int opt)
{
    switch(opt)
    {
        case DAY:
        case MONTH:
        case YEAR:
        case REMOTE_ALARM:
        case NUM_SNOOZES:
        case LOCKDOWN:
        case COURTESY:
        case TWENTY4_HOUR:
        case BRIGHTNESS:
        case AUTO_DIM_LEVEL:
        case DEFUSE_CODE:
        case DIGIT_CYCLING:
        case ALARM_TONE:
        case PM_LIGHT_24HR_VAL:
        case DATE_FORMAT:
        case SNOOZE_PERIOD:
            return 1;
            break;
        case COURTESY_PERIOD:
            return 5;
            break;
        default:
            /* error */;
    }

    /* should never reach here */
    return 0;
}

unsigned char maxDays(State * state)
{
    unsigned char days;
    /* Determine if it is a leap year */
    unsigned int year;
    year = 2000 + (unsigned int)(state->options[YEAR]);
    /* is leap year */
    if((year & 3) == 0 && ((year%25) != 0 || (year & 15) == 0))
    {
        switch(state->options[MONTH])
        {
            case SEP:
            case APR:
            case JUN:
            case NOV:
                days = 30;
                break;
            case JAN:
            case MAR:
            case MAY:
            case JUL:
            case AUG:
            case OCT:
            case DEC:
                days = 31;
                break;
            case FEB:
                days = 29;
                break;
            default:
                /* error */;
        }
    }else{ // is not a leap year
        switch(state->options[MONTH])
        {
           case SEP:
           case APR:
           case JUN:
           case NOV:
                days = 30;
                break;
            case JAN:
            case MAR:
            case MAY:
            case JUL:
            case AUG:
            case OCT:
            case DEC:
                days = 31;
                break;
            case FEB:
                days = 28;
                break;
            default:
                /* error */;
        }
    }

    return days;
}

void setInitState(State * state)
{
    state->alarmHours = 9;
    state->alarmMinutes = 34;

   // EEPROM has never been written
   if(!EEPROM_isFresh())
   {
       EEPROM_readSettings(state->options, &state->address0, &state->address1,
               &state->alarmHours, &state->alarmMinutes);

       if( !inBounds(state, state->options) )
       {
           setDefaultOptions(state->options);
           state->alarmMinutes = 0;
           state->alarmHours = 0;
       }
   }
   else
   {
       // set default RTC settings
       RTC_set1224(0);
       RTC_setHours(1);
       RTC_setMinutes(44);
       RTC_setDay(9);
       RTC_setMonth(11);
       RTC_setYear(14);

       state->hours = RTC_getHours();
       state->minutes = RTC_getMinutes();
       state->mode = TIME;       
       
       state->snoozeCount = 0;
       state->lockDownAndAlarmState = NEITHER;
       state->setHourMode = 0;
       state->alarmOn = 1;
       state->curOption = DAY;
       setDefaultOptions(state->options);
       state->address0 = 0x00;
       state->address1 = 0x00;
   }

    RTC_setYear(state->options[YEAR]);
    state->lockDownAndAlarmState = NEITHER;

    state->snoozeCount = 0;

    state->mode = TIME;
    state->alarmOn = 0;
    turnOffAlarmLight();
   // set the brightness
   Display_setBrightnessAll( tenTo32(state->options[BRIGHTNESS]) );
}

unsigned int getAlarmDistance(unsigned int current, unsigned int alarm)
{
    if(current <= alarm){
        return alarm-current;
    }

    return alarm+1440-current;
}

unsigned int getBWAlarmDistance(unsigned int current, unsigned int alarm)
{
    if(alarm <= current){
        return current-alarm;
    }

    return current+1440-current;
}

unsigned char isMenuSettingWTone(unsigned int * currentOption)
{
    switch(*currentOption)
    {
        case REMOTE_ALARM:
        case LOCKDOWN:
        case COURTESY:
        case TWENTY4_HOUR:
        case PM_LIGHT_24HR_VAL:
        case ALARM_TONE:
        case AUTO_DIM_LEVEL:
        case DEFUSE_CODE:
        case DIGIT_CYCLING:
        case DATE_FORMAT:
            return 1;
        default:
            return 0;
    }

    return 0;
}

unsigned char inBounds(State * state, unsigned char *options)
{
    unsigned int it;

    for(it = 0;it<NUM_OPTIONS;++it)
    {
        if( options[it] < optionLower(state, it) ||
            options[it] > optionUpper(state, it) ||
            options[it]%optionIncrement(it) != 0)
        {
            return 0;
        }
    }

    return 1;
}