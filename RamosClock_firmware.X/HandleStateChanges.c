#include "HandleStateChanges.h"

void handleStateChanges(State * prev, State * state,volatile unsigned short long * timers,
        unsigned char * justPMenuSoundPtr)
{
    // restart timeout timer
    if((state->mode != MENU) && (state->mode != MENU_SET)){
        timers[MENU_TIMEOUT_TIMER] = 0; // we did something, reset inactivity timer
    }

    // If state didn't change exit
    if( prev->mode == state->mode){
        return;
    }

    /********* CHANGES IN SET TIME ************/
    // was setting time but not any more
    if(prev->mode == SET_TIME && state->mode != SET_TIME){
        // Set the RTC
        RTC_setHours( state->hours );
        RTC_setMinutes( state->minutes );
        Display_setBrightnessAll( tenTo32(state->options[BRIGHTNESS]) );
        prev->hours = state->hours;
        prev->minutes = state->minutes;
    } // Wasn't setting time but now we are
    else if(prev->mode != SET_TIME && state->mode == SET_TIME){
        state->hours = RTC_getHours();
        state->minutes = RTC_getMinutes();
        timers[PULSE_TIMER] = 0;
        state->setHourMode = 0;
    }

    /******** CHANGES IN SET ALARM *******/
    // was setting alarm but not anymore
    if(prev->mode == SET_ALARM && state->mode != SET_ALARM)
    {
        Display_setBrightnessAll( tenTo32(state->options[BRIGHTNESS]) );

        // Write the EEMPROM
        EEPROM_writeSettings(state->options, &state->address0,
                &state->address1, &state->alarmHours, &state->alarmMinutes);
    }
    // wasnt setting time but are now
    if((prev->mode != SET_TIME && prev->mode != SET_ALARM) &&
       (state->mode == SET_TIME || state->mode == SET_ALARM))
    {
        timers[PULSE_TIMER] = 0;
        state->setHourMode = 0;
    }

    /******** CHANGES IN MENU ********/
    if((prev->mode != MENU && prev->mode != MENU_SET) &&
            state->mode == MENU)
    {
        timers[MENU_SOUND_TIMER] = MENU_SND_WAIT_TIME + 1;
        *justPMenuSoundPtr = 0;
    }

    if(prev->mode != state->mode &&
       (prev->mode == MENU || prev->mode == MENU_SET) &&
        (state->mode == MENU || state->mode == MENU_SET))
    {
        timers[PULSE_TIMER]= 0;
        if(Sound_isBusy()){
            Sound_shutUp();
        }
    }

    if( prev->mode != state->mode &&
       (prev->mode == MENU) &&
       (state->mode == MENU_SET))
    {
        timers[PULSE_TIMER]= 0;
        *justPMenuSoundPtr = 0;
        if(Sound_isBusy()){
            Sound_shutUp();
        }
    }

    // was in menu set but not anymore
    if( prev->mode == MENU_SET && state->mode != MENU_SET ){
        // Set the days and month to the RTC clock
        RTC_setMonth(state->options[MONTH]);
        RTC_setYear(state->options[YEAR]);
        if(state->options[DAY] <= maxDays(state)){
            RTC_setDay(state->options[DAY]);
        }else{ // Clip invalid days
            state->options[DAY] = maxDays(state);
            RTC_setDay(maxDays(state));
        }
    }

    // Was setting options but not anymore
    if((prev->mode == MENU || prev->mode == MENU_SET) &&
       (state->mode != MENU && state->mode != MENU_SET))
    {
        setDefuseCode(state);
        // Set the days and month to the RTC clock
        RTC_setMonth(state->options[MONTH]);
        RTC_setYear(state->options[YEAR]);
        if(state->options[DAY] <= maxDays(state)){
            RTC_setDay(state->options[DAY]);
        }else{ // Clip invalid days
            state->options[DAY] = maxDays(state);
            RTC_setDay(maxDays(state));
        }
        // reset brightness
        Display_setBrightnessAll( tenTo32(state->options[BRIGHTNESS]) );
        // turn back on colon
        turnOnColon();
        // play goodbye sound
        Sound_shutUp();
        Sound_playSpeech(SND_GOODBYE);

        // Write the EEMPROM
        EEPROM_writeSettings(state->options, &state->address0,
                &state->address1, &state->alarmHours, &state->alarmMinutes);

        // use the same timer for the exit menu anim
        timers[MENU_ANIM_TIMER] = 0;
    } // Wasn't setting menu options but now we are
    else if((prev->mode != MENU && prev->mode != MENU_SET) &&
            (state->mode == MENU || state->mode == MENU_SET))
    {
        state->options[MONTH] = RTC_getMonth();
        state->options[DAY] = RTC_getDay();
        state->options[YEAR] = RTC_getYear();
        // turn off colon
        turnOffColon();
        // set full brighs
        Display_setBrightnessAll(32);
    }

    // entering menu
    if(prev->mode == TIME && state->mode == MENU){
        Sound_shutUp();
        Sound_playSpeech(SND_WELCOMEMENU);
        state->curOption = 0; // start at date
        prev->curOption = 0;
        timers[MENU_ENTER_TIMER] = 0;
       // *justPMenuSoundPtr = 1;
        timers[MENU_ANIM_TIMER] = 0;
    }

    // always set brightness to full in the menu
    if(prev->mode != MENU && state->mode == MENU){
        Display_setBrightnessAll(32);
    }

    if(state->mode == SET_TIME || state->mode == SET_ALARM){
        Display_setBrightnessAll(32);
    }

    if(prev->mode == MENU_SET && state->mode == MENU){
        *justPMenuSoundPtr = 1;
    }
}

void handleTimeOuts(State * state, volatile unsigned short long * timers)
{
   unsigned char hourTemp, minTemp;
   hourTemp = RTC_getHours();
   minTemp = RTC_getMinutes();

   // Time out menu
   if((state->mode == MENU || state->mode == MENU_SET) &&
      (timers[MENU_TIMEOUT_TIMER] > MENU_TIMEOUT_TIME))
   {
       state->mode = TIME;
   }

   // alarm time out
   if(state->lockDownAndAlarmState == ALARM_TRIGGERED &&
      getBWAlarmDistance((unsigned int)(hourTemp)*60+(unsigned int)(minTemp),
               (unsigned int)(state->alarmHours)*
           60+(unsigned int)(state->alarmMinutes)) >= ALARM_TIMEOUT_LIMIT)
   {
       Sound_shutUp();
       state->lockDownAndAlarmState = NEITHER;
   }
}

void handleSounds(State * state, State * prev, volatile unsigned short long * timers,
        unsigned char * justPMenuSound)
{
    unsigned char tempSoundCode;
    /* Decide what sounds to play as we cycle through menu features */
   if(state->mode == MENU)
   {
       // changed the option we are setting
       // timer is greater than threshold
       if(timers[MENU_SOUND_TIMER] > MENU_SND_WAIT_TIME &&
               !(*justPMenuSound))
       {
           if(!Sound_isBusy()){
               Sound_playSpeech(state->curOption);
               *justPMenuSound = 1;
           }
       }
       else if(prev->curOption != state->curOption)
       {
           if(Sound_isBusy()){
               Sound_shutUp();
           }
           timers[MENU_SOUND_TIMER] = 0;
           *justPMenuSound = 0;
           timers[MENU_TIMEOUT_TIMER] = 0; // activity
       }
   }
   else if(state->mode == MENU_SET)
   {
       if(!isMenuSettingWTone(&state->curOption)){
            // do nothing
       }else if((prev->options[state->curOption] != state->options[state->curOption]) ||
          (prev->mode == MENU && state->mode == MENU_SET)){
           if(Sound_isBusy()){
               Sound_shutUp();
           }
           timers[MENU_SOUND_TIMER] = 0;
           *justPMenuSound = 0;
           timers[MENU_TIMEOUT_TIMER] = 0;
       }else if(timers[MENU_SOUND_TIMER] > MENU_SND_WAIT_TIME &&
               !*justPMenuSound)
       {
           if(!Sound_isBusy()){
               tempSoundCode = 0xFF;
               switch(state->curOption)
               {
                   case REMOTE_ALARM:
                   case LOCKDOWN:
                   case COURTESY:
                   case TWENTY4_HOUR:
                   case PM_LIGHT_24HR_VAL:
                   case DIGIT_CYCLING:
                   case DEFUSE_CODE:
                       if(state->options[state->curOption]){
                           tempSoundCode = SND_ACTIVATED;
                       }else{
                           tempSoundCode = SND_DEACTIVATED;
                       }
                       break;
                   case ALARM_TONE:
                       tempSoundCode = state->options[state->curOption];
                       break;
                   case AUTO_DIM_LEVEL:
                       if(state->options[state->curOption] == 11){
                           tempSoundCode = SND_DEACTIVATED;
                       }else{
                           return;
                       }
                       break;
                   case DATE_FORMAT:
                       if(state->options[state->curOption] == 1){
                           tempSoundCode = SND_MONTHDAY;
                       }else{
                           tempSoundCode = SND_DAYMONTH;
                       }
                       break;
                   default:
                       ;
               }
               Sound_playSpeech(tempSoundCode);
               *justPMenuSound = 1;
           }
       }
   }
}

void handleCourt(State * state, volatile unsigned short long * timers,
        unsigned char * prev_rampup_vol)
{
   if(state->lockDownAndAlarmState == ALARM_TRIGGERED)
   {
        // Courtesy mode
        if(state->options[COURTESY]){
            // in the off period
            if((timers[ALARM_TIMER] >
              (unsigned short long)(state->options[COURTESY_PERIOD])*1000) &&
              (timers[ALARM_TIMER] <=
              ((unsigned short long)(state->options[COURTESY_PERIOD])*1000+60000)))
            {
                if( !WT588D_Not_Busy){
                    Sound_shutUp();
                }
            }else{
               //ERROR CHECK. If the sound did not play, then we will make sure to
               //play it
               if( WT588D_Not_Busy){
                   // play the correct one
                   Sound_playSpeech(state->options[ALARM_TONE]);
                   Sound_loopPlay();
                   INTCONbits.GIE = 0; //Disable the interrupts we get perfect timing
                   Delay1KTCYx(2000);//wait 250 ms
                   INTCONbits.GIE = 1; //Enable the interrupts again
               }
            }
        }
    }
}

void setDefuseCode(State * state)
{
    volatile unsigned int defuse_temp;
    // using date
    if( !state->options[DEFUSE_CODE] )
    {
        if( state->options[DATE_FORMAT] ) // Use American mode
        {
            state->defuseFirst = RTC_getMonth();
            state->defuseSecond = RTC_getDay();
        }else{      // non american
            state->defuseFirst = RTC_getDay();
            state->defuseSecond = RTC_getMonth();
        }
    }
    else // using randomly generated code
    {
        // get rand
        defuse_temp = (rand()%7499)+2500;
        state->defuseFirst = (unsigned char)((defuse_temp/100)%100);
        state->defuseSecond = (unsigned char)(defuse_temp%100);
    }
}

void updateTimers(volatile unsigned short long * timers)
{
   unsigned int i;

   timers[TEMP_TIMER] = Timer_msSinceReset(); Timer_reset();
   for(i=1;i<NUM_TIMERS;++i)
   {
       if(timers[i] <= 16000000){
           timers[i] += timers[TEMP_TIMER];
       }
   }
}

void initTimers(volatile unsigned short long * timers)
{
    unsigned int i;

    for(i=0;i<NUM_TIMERS;++i)
    {
       timers[i] = 0;
    }

    timers[MENU_ANIM_TIMER] = 16000000;
    timers[MENU_SOUND_TIMER] = 16000000;
    timers[DEFUSE_CODE_TIMER] = 16000000;
    timers[BRIGHTNESS_TIMER] = 16000000;

    Timer_reset();
}

unsigned short long timerLimits(unsigned int time_enum)
{
    switch(time_enum)
    {
        case ALARM_TIMER:
            return RAMPUP_PERIOD*6;
        case MENU_ENTER_TIMER:
            return MENU_TIMER_LIMIT;
        case MENU_ANIM_TIMER:
            return MENU_ANIM_LIMIT;
        case MENU_SOUND_TIMER:
            return MENU_SND_WAIT_TIME;
        case MENU_TIMEOUT_TIMER:
            return MENU_TIMEOUT_TIME;
        case DIGIT_TIMER:
            return 5000;
        case DEFUSE_CODE_TIMER:
            return DEFUSE_CODE_DISPLAY_LENGTH;
        case BRIGHTNESS_TIMER:
            return BRIGHTNESS_TIMER_LIMIT;
        default:
            return 16000000;
    }
}
