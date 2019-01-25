
#include "Display.h"

void displayState(State * state, State * prev, volatile unsigned short long * timers)
{
    unsigned char tHours;

    if(state->mode != prev->mode){
        timers[PULSE_TIMER]= 0;
    }

    /* Determines what to display based on state */
    // defuse code
    if(state->lockDownAndAlarmState != NEITHER &&
        timers[DEFUSE_CODE_TIMER] < DEFUSE_CODE_DISPLAY_LENGTH)
    {
        turnOffColon();
        displayDefuseCode(state);
        return;
    }
    // menu exit anim
    else if(state->mode == TIME && timers[MENU_ANIM_TIMER] <= MENU_EXIT_LIMIT)
    {
        turnOffColon();
        displayExitAnim(timers[MENU_ANIM_TIMER]);
    } // Digit cycling
    else if(state->mode == TIME && (timers[DIGIT_TIMER] <= 5000) &&
               state->options[DIGIT_CYCLING])
     {
        turnOnColon();
        if(state->options[TWENTY4_HOUR]){
           displayDigitCycling((float)(timers[DIGIT_TIMER])/1000.f,
                   state->hours,state->minutes);
        }else{
            tHours = state->hours;

            if(tHours == 0){
                tHours = 12;
            }else if(tHours > 12){
                tHours -= 12;
            }
            displayDigitCycling((float)(timers[DIGIT_TIMER])/1000.f,
                   tHours,state->minutes);
        }
     }
     else // Normal display
     {
        switch(state->mode)
        {
            case TIME:
               turnOnColon();
               displayCurTime(state->options[TWENTY4_HOUR],
                       state->options[PM_LIGHT_24HR_VAL]);

               if(state->lockDownAndAlarmState != NEITHER){
                   pulseLights(0, 0, 1, &timers[PULSE_TIMER], 0 /* value doesn't matter*/);
               }
               break;
            case SET_TIME:
                turnOnColon();
               displaySetTime(state->hours, state->minutes, state->options[TWENTY4_HOUR],
                       state->options[PM_LIGHT_24HR_VAL]);
               if(state->setHourMode){
                   pulseLights(1, 0, 0, &timers[PULSE_TIMER], state->options[BRIGHTNESS]);
               }else{
                   pulseLights(0, 1, 0, &timers[PULSE_TIMER], state->options[BRIGHTNESS]);
               }
               break;
            case SET_ALARM:
               turnOnColon();
               displaySetTime(state->alarmHours, state->alarmMinutes,
                       state->options[TWENTY4_HOUR], state->options[PM_LIGHT_24HR_VAL]);
               if(state->setHourMode){
                   pulseLights(1, 0, 0, &timers[PULSE_TIMER], state->options[BRIGHTNESS]);
               }else{
                   pulseLights(0, 1, 0, &timers[PULSE_TIMER], state->options[BRIGHTNESS]);
               }
               break;
            case MENU:
                turnOffColon();
                if(timers[MENU_ANIM_TIMER] < MENU_ANIM_LIMIT){
                    displayMenuAnim(timers[MENU_ANIM_TIMER]);
                }else{
                    Display_showNumber(state->curOption+1);
                }
                break;
            case MENU_SET:
                turnOffColon();
                pulseLights(1, 1, 0, &timers[PULSE_TIMER], state->options[BRIGHTNESS]);
                switch(state->curOption)
                {
                    case YEAR:
                        Display_showNumber(2000+(unsigned int)(state->options[state->curOption]));
                        break;
                    // Display Number
                    case DAY:
                    case MONTH:
                    case BRIGHTNESS:             
                    case NUM_SNOOZES:
                    case SNOOZE_PERIOD:
                    case COURTESY_PERIOD:
                        Display_showNumber((unsigned int)(state->options[state->curOption]));
                        break;
                    case ALARM_TONE:
                        Display_showNumber((unsigned int)(state->options[state->curOption])
                                -ALARM_TONE_OFFSET);
                        break;
                    case DATE_FORMAT:
                        if(state->options[state->curOption] == 0){
                            Display_setAll4(state->options[DAY]/10, state->options[DAY]%10,
                                    state->options[MONTH]/10, state->options[MONTH]%10);
                        }else{
                            Display_setAll4(state->options[MONTH]/10, state->options[MONTH]%10,
                                    state->options[DAY]/10, state->options[DAY]%10);
                        }
                        break;
                    // Display On or Off
                    case LOCKDOWN:
                    case COURTESY:
                    case TWENTY4_HOUR:
                    case DIGIT_CYCLING:
                    case REMOTE_ALARM:
                    case PM_LIGHT_24HR_VAL:
                    case DEFUSE_CODE:
                        if(state->options[state->curOption] == 0){
                            Display_Off();
                        }else{
                            Display_On();
                        }
                        break;
                    case AUTO_DIM_LEVEL:
                        // code for the LED
                        if(state->options[state->curOption] != 10){
                            Display_showNumber((unsigned int)(state->options[state->curOption]));
                        }else{
                            Display_Off();
                        }
                        // code for the Nixie
                        // Display_showNumber((unsigned int)(state->options[state->curOption]));
                        break;
                    default:
                        Display_showNumber(9999);
                }
                break;
            default:
                /* Undefined state */
                Display_showNumber(ERROR);
        }

        // Alarm button
        if(prev->alarmOn != state->alarmOn){
            if(state->alarmOn){
               turnOnAlarmLight();
            }else{
               turnOffAlarmLight();
            }
        }
     }
}


void displayCurTime(unsigned char is24mode, unsigned char pmlight)
{
    unsigned char hours, minutes;
    hours = RTC_getHours(); minutes = RTC_getMinutes();
   if(is24mode)
    {
        Display_setAll4( hours/10, hours%10, minutes/10, minutes%10);
    }
    else
    {
        if((unsigned int)(hours) <= 12){
            if((unsigned int)(hours) != 0){
                Display_showNumber( (unsigned int)(hours)*100+(unsigned int)(minutes) );
            }else{
                Display_showNumber( 1200 + (unsigned int)(minutes) );
            }
        }else{
            Display_showNumber(((unsigned int)(hours)-12)*100+
                    (unsigned int)(minutes));
        }
    }

    if(!is24mode)
    {
        // PM light
        if(hours >= 12 && hours < 24){
            turnOnPMLight();
        }else{
            turnOffPMLight();
        }
    }
    else // not 24 hour mode
    {
        if(pmlight){
            turnOnPMLight();
        }else{
            turnOffPMLight();
        }
    }
}

void displaySetTime(unsigned char hours, unsigned char minutes,
        unsigned char is24mode, unsigned char pmlight)
{
    if(is24mode)
    {
        Display_setAll4( hours/10, hours%10, minutes/10, minutes%10);
    }
    else
    {
        if((unsigned int)(hours) <= 12){
            if((unsigned int)(hours) != 0){
                Display_showNumber( (unsigned int)(hours)*100+(unsigned int)(minutes) );
            }else{
                Display_showNumber( 1200 + (unsigned int)(minutes) );
            }
        }else{
            Display_showNumber(((unsigned int)(hours)-12)*100+
                    (unsigned int)(minutes));
        }
    }

    if(!is24mode)
    {
        // PM light
        if(hours >= 12 && hours < 24){
            turnOnPMLight();
        }else{
            turnOffPMLight();
        }
    }
    else // not 24 hour mode
    {
        if(pmlight){
            turnOnPMLight();
        }else{
            turnOffPMLight();
        }
    }
}

unsigned char getDigit(float t, float t1, unsigned char x0, unsigned char xc)
{
    float t0, x;
    if(t >= t1){
        return (x0+xc)%10;
    }

    t0 = (2.f/R0)*(float)(xc)-t1;

    if(t <= t0){
        return ((unsigned char)(R0*t)+x0)%10;
    }

    x = (t-t0)/(t0-t1);
    x *= R0;
    x += 2.f*R0;
    x *= 0.5f*(t-t0);
    x += R0*t0;

    return ((unsigned char)(x)+x0)%10;
}

void displayDigitCycling(float t, unsigned char hours, unsigned char minutes)
{
    unsigned char xc[4], c[4], d1[4], d2[4], now[4];
    unsigned char prev_min, prev_hour, i;
    float t1[4];
   // Digit cycling stuff
   t1[0] = 5.f;   xc[0] = 60;
   t1[1] = 4.f;   xc[1] = 50;
   t1[2] = 3.f;   xc[2] = 40;
   t1[3] = 2.f;   xc[3] = 30;

   // determine previous time
   if( minutes != 0){
       prev_min = minutes-1;
       prev_hour = hours;
   }
   else{
       prev_min = 59;
       if(hours != 1){
           prev_hour = hours - 1;
       }else{
           prev_hour = 24;
       }
   }

   // determine the digits
   d1[0] = (prev_hour/10); d2[0] = hours/10;
   d1[1] = prev_hour%10; d2[1] = hours%10;
   d1[2] = prev_min/10; d2[2] = minutes/10;
   d1[3] = prev_min%10; d2[3] = minutes%10;

   for(i=0;i<4;++i)
   {
       c[i] = xc[i] + (d2[i]-d1[i]);
   }

   for(i=0;i<4;++i)
   {
       now[i] = getDigit(t, t1[i], d1[i], c[i]);
   }

   Display_setAll4(now[0], now[1], now[2], now[3]);
}

//void displayMenuAnim(unsigned short long timer)
//{
//    while(timer >= 600){
//        timer -= 600;
//    }
//
//    if(timer < 100){
//        Display_setIndividualElements( Blank, A, D, Blank);
//    }else if(timer < 200){
//        Display_setIndividualElements( A, Blank, Blank, D);
//    }else if(timer < 300){
//        Display_setIndividualElements( F, Blank, Blank, C);
//    }else if(timer < 400){
//        Display_setIndividualElements( E, Blank, Blank, B);
//    }else if(timer < 500){
//        Display_setIndividualElements(D, Blank, Blank, A);
//    }else if(timer < 600){
//        Display_setIndividualElements(Blank, D, A, Blank);
//    }
//}

//entry animation. Have display go from  9999 to 8888 to 7777 ... 0000
void displayMenuAnim(unsigned short long timer)
{
    while(timer >= 600)
    {
        timer -= 600;
    }

    if(timer <60){
        Display_setAll4(9, 9, 9, 9);
    }else if(timer < 120){
        Display_setAll4(8, 8, 8, 8);
    }else if(timer < 180){
        Display_setAll4(7, 7, 7, 7);
    }else if(timer < 240){
        Display_setAll4(6, 6, 6, 6);
    }else if(timer < 300){
        Display_setAll4(5, 5, 5, 5);
    }else if(timer < 360){
        Display_setAll4(4, 4, 4, 4);
    }else if(timer < 420){
        Display_setAll4(3, 3, 3, 3);
    }else if(timer < 480){
        Display_setAll4(2, 2, 2, 2);
    }else if(timer < 540){
        Display_setAll4(1, 1, 1, 1);
    }else if(timer < 600){
        Display_setAll4(0, 0, 0, 0);
    }
}


//void displayExitAnim(unsigned short long timer)
//{
//    while(timer >= MENU_EXIT_LENGTH*4){
//        timer -= MENU_EXIT_LENGTH*4;
//    }
//
//    if(timer < MENU_EXIT_LENGTH){
//        Display_setIndividualElements(Blank, B | C, F | E, Blank);
//    }else if(timer < 2*MENU_EXIT_LENGTH){
//        Display_setIndividualElements(Blank, E | F, B | C, Blank);
//    }else if(timer < 3*MENU_EXIT_LENGTH){
//        Display_setIndividualElements(B | C, Blank, Blank, F | E);
//    }else if(timer < 4*MENU_EXIT_LENGTH){
//        Display_setIndividualElements(F | E, Blank, Blank, B | C);
//    }
//}

//nixie exit animation. have 1 scroll accross the screen.
void displayExitAnim(unsigned short long timer)
{
     while(timer >= MENU_EXIT_LENGTH*4){
        timer -= MENU_EXIT_LENGTH*4;
    }

     if(timer < MENU_EXIT_LENGTH){
        Display_setAll4(1, BLANK, BLANK, BLANK);
    }else if(timer < 2*MENU_EXIT_LENGTH){
        Display_setAll4(BLANK, 1, BLANK, BLANK);
    }else if(timer < 3*MENU_EXIT_LENGTH){
        Display_setAll4(BLANK, BLANK, 1, BLANK);
    }else if(timer < 4*MENU_EXIT_LENGTH){
        Display_setAll4(BLANK, BLANK, BLANK, 1);
    }

}

static unsigned char bright = 16;
static unsigned char up = 1;
void pulseLights(unsigned char hours, unsigned char minutes, unsigned char alarmLight,
        volatile unsigned short long * t, unsigned char brightNess)
{
    brightNess = tenTo32(brightNess);
    while(*t >= PULSE_RATE)
    {
        if(up && bright != PULSE_MAX){
            ++bright;
        }else if(up && bright == PULSE_MAX){
            up = 0;
        }else if(!up && bright != PULSE_MIN){
            --bright;
        }else if(!up && bright == PULSE_MIN){
            up = 1;
        }

        *t -= PULSE_RATE;
    }

    if(hours && !minutes)
    {
        Display_setIndividualBright(bright, bright, brightNess, brightNess);
    }
    else if(minutes && !hours)
    {
        Display_setIndividualBright(brightNess, brightNess, bright, bright);
    }
    else if(minutes && hours)
    {
        Display_setIndividualBright(bright, bright, bright, bright);
    }

    if(alarmLight){
        Display_setRingBrightness( bright);
    }
}

unsigned char tenTo32(unsigned char b)
{
    unsigned int lowest;
    lowest = 1;
    return (unsigned char)(((32-lowest)*(unsigned int)(b)/9)+lowest-(23-lowest)/9);
}

unsigned char roomTo10(unsigned char room, unsigned char setting, unsigned char autodim)
{
    int a, b, r;
    a = (int)(autodim);
    b = (int)(setting);
    r = (int)(room);

    return (unsigned char)( ((b-a)*r)/255 + a );
}

unsigned char roomTo32(unsigned char room, unsigned char setting, unsigned char autodim)
{
    unsigned int r, a;
    r = (unsigned int)(room);
    a = (unsigned int)(autodim);

    return (unsigned char)((((255-a*25)*r)/255+a*25)*32/255);
}

void displayDefuseCode(State * state)
{
    Display_setAll4( state->defuseFirst/10, state->defuseFirst%10,
            state->defuseSecond/10, state->defuseSecond%10 );
}