#include <p18f45k20.h>
#include <delays.h>
#include "Ramos_Sys/Ramos_sys.h"
#include "Nixie_display.h" //this is the only thing that gets changed in a port
#include <timers.h>
#include "Ramos_Sys/Test_routines.h"
#include "Ramos_Sys/RTC.h"
#include "HandleStateChanges.h"
#include "Ramos_Sys/Sound.h"
#include "Constructs.h"
#include "HandleUserInput.h"
#include "Display.h"
#include "CC1101_slave.h"


#pragma code

#define COUNT_TOL 100

void main() {
    State state, prev; // stores the state of the clock
    volatile unsigned short long timers[NUM_TIMERS];
    unsigned char minTemp, hourTemp, snoozeCount, prev_rampup_vol,
            justPMenuSound, alarmHourStore, alarmMinStore;
    unsigned int photoCount;
    unsigned char photoLast;

//    //new defuse code time
//    unsigned long defusecounter = 0;
//    unsigned char old_second;

    justPMenuSound = snoozeCount = 0;
    photoCount = 0;
    photoLast = 255;

   /* INITIALIZATIONS */
   init_Ramos_sys();
   init_Display();
   init_Sound();
   init_CC1101();

   /* Set the initial state */
   setInitState(&state);
   prev.mode = TIME;

   /* Seed the random generator*/
   // get seed
   srand((unsigned int)(RTC_getYear()+RTC_getMonth()+RTC_getDay()+RTC_getMinutes()+RTC_getHours() ));

   Sound_playSpeech(SND_STARTUP);

   initTimers(timers);

   alarmHourStore = state.alarmHours;
   alarmMinStore = state.alarmMinutes;

   // get a defuse code at the start
   setDefuseCode(&state);
   while (1)
   {
//       // Added on 11/19/13 as a defuse code fix
//       //first we keep a running counter of seconds
//       if(RTC_getSeconds()!=old_second){
//           defusecounter++;
//           old_second = RTC_getSeconds();
//       }


       // Update Timers
       updateTimers(timers);

       /********** DETERMINE STATE ***************/
       /* handle events from the user */
       if(timers[MENU_ANIM_TIMER] > MENU_ANIM_LIMIT)
       {
           handleSwitch(&state, timers);
           /*  knob input */
           handleKnob(&state, timers);
           /* alarm button input */
           handleAlarmBtn(&state, timers);
           /* remote panel input */
           handleRemotePanel(&state);
       }

       // time out menu and alarm
       handleTimeOuts(&state, timers);

       /********** HANDLE STATE CHANGES *********/
       handleStateChanges(&prev, &state, timers, &justPMenuSound);

       /* encoder input */
       handleEncoder(&state, timers);

       /*** Play correct sounds ***/
       handleSounds(&state, &prev, timers, &justPMenuSound);

       // handle what happens to the sound when the alarm is triggered
       handleCourt(&state, timers, &prev_rampup_vol);

       // Determine brightness if in autdim
       if(state.options[AUTO_DIM_LEVEL] < state.options[BRIGHTNESS] &&
         (state.mode == TIME))
       {
           // override if should be displaying the defuse code
           if(state.lockDownAndAlarmState == ALARM_TRIGGERED ||
                timers[BRIGHTNESS_TIMER] < BRIGHTNESS_TIMER_LIMIT){
               Display_setBrightnessAll(32);
           }
           else if(timers[DEFUSE_CODE_TIMER] < DEFUSE_CODE_DISPLAY_LENGTH){
               Display_setBrightnessAll( 32 );
           }
           else
           {
               if(photoCount < COUNT_TOL){
                   ++photoCount;
               }else{
                   photoLast = photoResVal();
                   photoCount = 0;
               }

               if(state.mode == TIME && state.lockDownAndAlarmState == NEITHER)
               {
                   Display_setBrightnessAll( roomTo32( photoLast,
                           state.options[BRIGHTNESS],
                           state.options[AUTO_DIM_LEVEL]) );
               }
               // lockdown mode brightness
               else if(state.mode == TIME)
               {
                   Display_setBrightnessEverythingButRing( roomTo32( photoLast,
                           state.options[BRIGHTNESS],
                           state.options[AUTO_DIM_LEVEL]) );
               }
           }
       }

       // Set the display
       displayState(&state, &prev, timers);

       // Handle what happens when the minute changes
       // This includes making the alarm go off and digit cycling

        minTemp = RTC_getMinutes();
        hourTemp = RTC_getHours();
        if(prev.minutes != minTemp)
        {
            if(state.mode != SET_TIME){
                timers[DIGIT_TIMER] = 0;
               state.minutes = minTemp;
               state.hours = hourTemp;
            }

           // check if the alarm should be going off
           if( (state.alarmHours == hourTemp &&
               state.alarmMinutes == minTemp) &&
               state.alarmOn)
           {
               state.mode = TIME;
               turnOnColon();
               state.lockDownAndAlarmState = ALARM_TRIGGERED;
               if( Sound_isBusy() ){
                   Sound_shutUp();
               }

               // play the correct done
               Sound_playSpeech(state.options[ALARM_TONE]);
               Sound_loopPlay();
               timers[ALARM_TIMER] = 0;

               //wait for the busy line to pop high
               //it is important that we wait 250 ms. For this reason, we
               // are turning off the interrupts while we do this.
               INTCONbits.GIE  = 0;
               Delay1KTCYx(2000);//wait 250 ms
               INTCONbits.GIE  = 1;


               // get a new code if we haven't gotten one
               if(!state.options[LOCKDOWN] && state.snoozeCount == 0){
                    setDefuseCode(&state);
               }
           }
           // check to see if we should be in lockdown mode
           else if( getAlarmDistance((unsigned int)(hourTemp)*60+(unsigned int)(minTemp),
                   (unsigned int)(state.alarmHours)*60+(unsigned int)(state.alarmMinutes)) <=
                   60 // hard code lockdown period to 60 minutes
                   && (state.alarmOn
                   && state.options[LOCKDOWN]))
           {
               /* Old code to get new code only when just entering lockdown mode
                *
               if( getAlarmDistance((unsigned int)(hourTemp)*60+(unsigned int)(minTemp),
                   (unsigned int)(state.alarmHours)*60+(unsigned int)(state.alarmMinutes)) ==
                   60 )
               {
                   setDefuseCode(&state); //get new code
               } */
               // get new code if we were not in lockdown and the alarm was not going off
               if( state.lockDownAndAlarmState == NEITHER )
               {
                   setDefuseCode(&state);
               }

               state.lockDownAndAlarmState = INLOCKDOWN;
           }

            /* Code to run at midnight everyday */
            if( hourTemp == 0 && minTemp == 0 ){
                //calibrate RF Chip
                RF_send_Strobe(SCAL);
                RF_send_Strobe(SRX);
            }
        }
        // Store state
        prev = state;
        prev.minutes = minTemp;

        if(state.lockDownAndAlarmState == NEITHER &&
           state.mode == TIME){
            state.alarmHours = alarmHourStore;
            state.alarmMinutes = alarmMinStore;;
        }else if(state.mode == SET_ALARM){
            alarmHourStore = state.alarmHours;
            alarmMinStore = state.alarmMinutes;
        }

       //---- FAIL CHECK ----------------------
       //--------------------------------------
       //----Added 10/5/13
        // This checks to see if the alarm should be going off. If it should
        // it checks to see if the alarm is actually going off. If it is not, it
        // sends the play alarm command untill it sees that the alarm is actually
        // going off.
        // PS. do NOT do this when in courtesy mode.
        if(state.lockDownAndAlarmState == ALARM_TRIGGERED && !state.options[COURTESY]){
            //if the line is not busy, then we have to send it again.
            if(WT588D_Not_Busy){
                //If we find ourselves in here something very bad has happened.
                // play the correct one
                Sound_playSpeech(state.options[ALARM_TONE]);
                Sound_loopPlay();
                INTCONbits.GIE = 0; //Disable the interrupts we get perfect timing
                Delay1KTCYx(2000);//wait 250 ms
                INTCONbits.GIE = 1; //Enable the interrupts again
            }
        //----------------------------------------------------------
        }
   }
}
