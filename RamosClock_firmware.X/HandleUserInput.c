#include "HandleUserInput.h"

void handleEncoder(State *  state, volatile unsigned short long * timers)
{
    char encoder;
    
    encoder = pollEncoder();
    if(encoder != 0){
        timers[BRIGHTNESS_TIMER] = 0;
    }

    // menu activity
    if((state->mode == MENU || state->mode == MENU_SET) &&
            encoder != 0)
    {
        timers[MENU_TIMEOUT_TIMER] = 0;
    }

    if(state->lockDownAndAlarmState != NEITHER){  // alarm is going off or lockdownmode is active
        return;
    }else if(state->mode == SET_ALARM){ // Set alarm
        if(state->setHourMode){
            switch(encoder)
            {
            case -1:
                if(state->alarmHours != 0){
                    --state->alarmHours;
                }else{
                    state->alarmHours = 23;
                }
                break;
            case 0:
                break;
            case 1:
                if(state->alarmHours != 23){
                    ++state->alarmHours;
                }else{
                    state->alarmHours = 0;
                }
                break;
            default:
                /* error */;
           }
        }else{ // setMinuteMode
            switch(encoder)
            {
                case -1:
                    if(state->alarmMinutes != 0){
                        --state->alarmMinutes;
                    }else{
                        state->alarmMinutes = 59;
                    }
                    break;
                case 0:
                    break;
                case 1:
                    if(state->alarmMinutes != 59){
                        ++state->alarmMinutes;
                    }else{
                       state->alarmMinutes = 0;
                    }
                    break;
                default:
                    /* error */;
            }
        }
    }else if(state->mode == SET_TIME){ // set time
        if(state->setHourMode){
            switch(encoder)
            {
            case -1:
                if(state->hours != 0){
                    -- state->hours;;;
                }else{
                    state->hours = 23;
                }
                break;
            case 0:
                break;
            case 1:
                if(state->hours != 23){
                    ++state->hours;
                }else{
                    state->hours = 0;
                }
                break;
            default:
                /* error */;
           }
        }else{ // setMinuteMode
            switch(encoder)
            {
                case -1:
                    if(state->minutes != 0){
                        --state->minutes;
                    }else{
                        state->minutes = 59;
                    }
                    // precise time to seconds
                    RTC_setSeconds(0);
                    break;
                case 0:
                    break;
                case 1:
                    if(state->minutes != 59){
                        ++state->minutes;
                    }else{
                        state->minutes = 0;
                    }
                    // prices time to seconds
                    RTC_setSeconds(0);
                    break;
                default:
                    /* error */;
            }
        }
    }else if(state->mode == MENU){ // cycle througgh menu options
        if(encoder == -1){
            if(state->curOption != 0){
                --state->curOption;
            }else{
                state->curOption = NUM_OPTIONS-1;
            }
        }else if(encoder == 1){
            if(state->curOption != NUM_OPTIONS-1){
                ++state->curOption;
            }else{
                state->curOption = 0;
            }
        }
    }else if(state->mode == MENU_SET){ // Controls for setting options
        if(encoder == -1){
            if(state->options[state->curOption] !=
                    optionLower(state, state->curOption)){
                state->options[state->curOption] -= optionIncrement(state->curOption);
            }else{
                state->options[state->curOption] =
                        optionUpper(state, state->curOption);
            }
        }else if(encoder == 1){
            if(state->options[state->curOption] !=
                    optionUpper(state, state->curOption)){
                state->options[state->curOption] += optionIncrement(state->curOption);
            }else{
                state->options[state->curOption] =
                        optionLower(state, state->curOption);
            }
        }
    }
}

void handleSwitch(State * state, volatile unsigned short long * timers)
{
    unsigned char a_tog, t_tog;

    /* toggle */
    t_tog = !SWITCH_TIME_SET;
    a_tog = !SWITCH_ALARM_SET;

    if(a_tog || t_tog){
        timers[BRIGHTNESS_TIMER] = 0;
    }

    if(((state->lockDownAndAlarmState == ALARM_TRIGGERED &&
            state->options[REMOTE_ALARM]) ||
            (state->lockDownAndAlarmState == INLOCKDOWN)) &&
            (a_tog || t_tog))
    {
        timers[DEFUSE_CODE_TIMER] = 0;
        return;
    }else if(state->lockDownAndAlarmState == ALARM_TRIGGERED){
        return;
    }
    else if(state->lockDownAndAlarmState == PSUEDOLOCKDOWN){
        return;
    }
    else if(state->mode != MENU && state->mode != MENU_SET){
        if(t_tog == PRESSED){
           state->mode = SET_TIME;
        }else if(a_tog == PRESSED){
           state->mode = SET_ALARM;
        }else{
            if(state->mode != MENU){
                state->mode = TIME;
            }
        }
    }
    else{ // EXIT MENU
        if(t_tog == PRESSED || a_tog == PRESSED)
        {
            state->mode = TIME;
        }
    }
}

static unsigned char knob_pressed_recently = 0;
void handleKnob( State * state, volatile unsigned short long * timers)
{
    unsigned char temp;
    temp = pollKnobBtn();

    if(temp){
        timers[BRIGHTNESS_TIMER] = 0;
    }

    if(temp &&
        state->lockDownAndAlarmState == INLOCKDOWN &&
        state->options[REMOTE_ALARM])
    {
        timers[DEFUSE_CODE_TIMER] = 0;
        return;
    }

    // handle snoozes
    if( (temp == PRESSED) && state->lockDownAndAlarmState == ALARM_TRIGGERED &&
        state->snoozeCount < state->options[NUM_SNOOZES])
    {
        ++state->snoozeCount;
        Sound_shutUp();
        state->lockDownAndAlarmState = NEITHER;
        if( state->minutes + state->options[SNOOZE_PERIOD] < 60){
            state->alarmMinutes = state->minutes + state->options[SNOOZE_PERIOD];
        }else{
            if(state->hours != 23){
                state->alarmHours = state->hours+1;
            }else{
                state->alarmHours = 0;
            }

            state->alarmMinutes = (state->minutes+state->options[SNOOZE_PERIOD])-60;
        }
        if(!state->options[REMOTE_ALARM]){
            state->lockDownAndAlarmState = PSUEDOLOCKDOWN;
        }else{
            state->lockDownAndAlarmState = INLOCKDOWN;
        }
        Display_setRingBrightness(32);
        return;
    }else if(state->lockDownAndAlarmState == ALARM_TRIGGERED){
        return;
    }

    // normal functioning
    if(temp == PRESSED)
    {
        // Setting time functions
        if(state->mode == SET_TIME || state->mode == SET_ALARM){
            state->setHourMode = !state->setHourMode;
        }else if(state->mode == MENU){
            state->mode = MENU_SET;
        }else if(state->mode == MENU_SET){
            state->mode = MENU;
        }
        // enter menu
        else if(state->mode == TIME){
            timers[MENU_ENTER_TIMER] = 0;
            knob_pressed_recently = 1;
        }
    }else if(temp == DEPRESSED)
    {
        knob_pressed_recently = 0;
    }

    // knob is being held
    if(state->mode == TIME)
    {
        if(knob_pressed_recently ){
            // See if we should enter the menu
            if(timers[MENU_ENTER_TIMER] > MENU_TIMER_LIMIT){
                state->mode = MENU;
            }
        }
    }
}

void handleAlarmBtn(State * state, volatile unsigned short long * timers)
{
    unsigned char a_but;
    a_but = pollAlarmBtn();

    if(a_but != 0){
        timers[BRIGHTNESS_TIMER] = 0;
    }

    // instances where the button does nothing
    if(state->mode == MENU || state->mode == MENU_SET){ // menu mode
        return;
    }else if( state->lockDownAndAlarmState == PSUEDOLOCKDOWN){ // lockdown
        if(state->options[REMOTE_ALARM] == 0 && a_but){
            state->lockDownAndAlarmState = NEITHER;
            state->alarmOn = 0;
        }
        return;
    }else if( a_but == 1 && !state->options[REMOTE_ALARM] &&
            state->lockDownAndAlarmState == ALARM_TRIGGERED )
    {
        // turn off the alarm
        Sound_shutUp();
        state->lockDownAndAlarmState = NEITHER;
        Display_setRingBrightness(32);
        state->snoozeCount = 0;
        return;
    }
    else if( state->lockDownAndAlarmState != NEITHER){
        return;
    }

    if(a_but == PRESSED)
    {
        state->alarmOn = !state->alarmOn;
        if(state->alarmOn){
            turnOnAlarmLight();
        }else{
            turnOffAlarmLight();
        }
    }
}

void handleRemotePanel(State* state)
{
    RAWRPI tempRAWRPI;
    stateRAWRPI decodeCode;
   // RAWRPI SHIT
   if( GD0 ){
       tempRAWRPI = RF_readRAWRPI();
       //RF_sendRAWRPI(tempRAWRPI);
       decodeCode = decodeRAWRPI(&tempRAWRPI, state->address1, state->address0);
       switch(decodeCode)
       {
           case AddressTrainingRequest:
               if(state->mode == MENU){
                   state->address0 = tempRAWRPI.rAddress0;
                   state->address1 = tempRAWRPI.rAddress1;
                   returnSucces(&tempRAWRPI);
               }else{
                   returnFailure(&tempRAWRPI);
               }
               break;
           case RangeCheckRequest:
               if( addressesMatch(state, &tempRAWRPI)){

                   returnSucces(&tempRAWRPI);
               }
               break;
           case DefuseCodeAttempt:
               // addresses match
               if( addressesMatch(state, &tempRAWRPI) ){
                   if(state->lockDownAndAlarmState == INLOCKDOWN){
                       if( defuseCodeMatches(&tempRAWRPI, state)){
                           state->lockDownAndAlarmState = NEITHER;
                           state->alarmOn = 0;
                           state->snoozeCount = 0;
                           returnSucces(&tempRAWRPI);
                           Display_setRingBrightness(32);
                       }else{
                           returnFailure(&tempRAWRPI);
                       }
                   }else if(state->lockDownAndAlarmState == ALARM_TRIGGERED){
                       if( defuseCodeMatches(&tempRAWRPI, state)){
                           state->lockDownAndAlarmState = NEITHER;
                           Sound_shutUp();
                           returnSucces(&tempRAWRPI);
                           state->snoozeCount = 0;
                           Display_setRingBrightness(32);
                       }else{
                           returnFailure(&tempRAWRPI);
                       }
                   }else{
                       // do nothing?
                   }
               }
               break;
           case FactoryResetRequest:
               if( addressesMatch(state, &tempRAWRPI)){
                   setDefaultOptions(state->options);
                   state->alarmHours = 0;
                   state->alarmMinutes = 0;
                   tempRAWRPI.rCommand = 5;
                    returnSucces(&tempRAWRPI);
               }
               else
               {
                   returnFailure(&tempRAWRPI);
               }
               break;
           default:
               ;
       }
   }
}

unsigned char addressesMatch(State * state, RAWRPI * tempRAWRPI)
{
    if( state->address0 == tempRAWRPI->rAddress0 &&
        state->address1 == tempRAWRPI->rAddress1)
    {
        return 1;
    }

    return 0;
}

unsigned char defuseCodeMatches(RAWRPI * tempRAWRPI, State * state)
{
    // check either way, so it is not as strict
    if( (tempRAWRPI->rData0 == state->defuseFirst && tempRAWRPI->rData1 == state->defuseSecond) ||
        (tempRAWRPI->rData0 == state->defuseSecond && tempRAWRPI->rData1 == state->defuseFirst))
    {
        return 1;
    }

    return 0;
}

void returnSucces(RAWRPI * tempRAWRPI)
{
    tempRAWRPI->rData0 = 0xFF;
    tempRAWRPI->rData1 = 0xFF;

    RF_sendRAWRPI(*tempRAWRPI);
}

void returnFailure(RAWRPI * tempRAWRPI)
{
    tempRAWRPI->rData0 = 0x00;
    tempRAWRPI->rData1 = 0x00;

    RF_sendRAWRPI(*tempRAWRPI);
}