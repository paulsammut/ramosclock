#include "LED_display.h"



/* digit values */
volatile static unsigned char digit0 = 1;
volatile static unsigned char digit1 = 2;
volatile static unsigned char digit2 = 3;
volatile static unsigned char digit3 = 4;

volatile static unsigned char individualElements0 = 0xFF;
volatile static unsigned char individualElements1 = 0xFF;
volatile static unsigned char individualElements2 = 0xFF;
volatile static unsigned char individualElements3 = 0xFF;

/* peripheral values */
/* 1 is on 0 is off */
volatile unsigned char PMlight_val = 0;
volatile unsigned char colon_val = 1;
volatile unsigned char alarmLight_val = 1;

/*brightness values, out of 32*/
volatile unsigned char digit0Brightness = 32;
volatile unsigned char digit1Brightness = 32;
volatile unsigned char digit2Brightness = 32;
volatile unsigned char digit3Brightness = 32;


/*peripheral brighness. colon, ampm light and alarm on led*/
volatile unsigned char periphBrightness = 32;

/*LED on alarm*/
volatile unsigned char ringBrightness = 32;

/*digit we are currently working on while muxing*/
volatile unsigned char curDisplayDigit = 0;

/*length of a timer period in microseconds*/
volatile unsigned char TIMER0_PERIOD_US;
/*Time in microseconds to show one digit*/
volatile double digitShowTime_us;

/*--- Timing Counters ---*/
/* the number of counts done to get to PWM brightness threshold*/
//unsigned char timerCountPWM_tresh;
/* the nubmer of counts done to get to the digit threshold and move on to the next one*/
volatile unsigned char timerCountDigit_tresh;
/*number of PWM timer steps counted so far. When i get here, reset and incr PWM level step*/
//unsigned char num_timerCountPWM=0;
/*number of digit timer counts. When = timerCountDigit_tresh, reset, move on to next digit*/
volatile unsigned char num_timerCountDigit=0;
/*number of PWM levels counted so far*/
volatile unsigned char num_levels_PWM=0;


/* Boolean that says whether we or not we have individual element control. This is solely for printing cool animations */
volatile unsigned char settingIndividualElements = 0; //default is off, which is normal mode.

//Millisecond function:
volatile static unsigned short long Timer_millis = 0;

/*--- STATIC PROTOTYPES ---*/

/**
 * Runs the multiplexing scheme that handles brightness, blanking, PWM, timers, and peripherals.
 */
static void LED_muxAway(void);

/** I N T E R R U P T S ***********************************************/

//----------------------------------------------------------------------------
// Low priority interrupt vector

#pragma code InterruptVectorLow= 0x18
void InterruptVectorLow (void)
{
  _asm
    goto LED_muxAway //jump to interrupt routine
  _endasm
}
/**----------- C O D E -------------------------------*/

void init_Display() {

    /*--- IO SETTINGS ---*/
    TRISAbits.RA4 = 0; //PM Light
    TRISD = 0x00; //all outputs
    TRISAnode0 = 0; //Digit 0
    TRISAnode1 = 0; //Digit 1
    TRISAnode2 = 0; //Digit 2
    TRISAnode3 = 0; //Digit 3
      
    


    /*--- T I M E R - 0 ------------*/
    INTCONbits.TMR0IF = 0; //clear roll over interrupt flag
    INTCON2bits.TMR0IP = 0; //display is a low priority interrupt
    INTCONbits.TMR0IE = 1; //enable the timer overflow interrupt

    T0CONbits.T08BIT = 1; //8bit timer
    T0CONbits.T0CS = 0; //internal clock
    T0CONbits.PSA = 0; //prescale
    T0CONbits.T0PS = 0b001; //1:4 presale 128us
    
    TMR0H = 0; //clear timer - always write upper byte first;
    TMR0L = 0; //lower bit clear
    T0CONbits.TMR0ON = 1; //enable the timer

    TIMER0_PERIOD_US = 128; //this timer setting gives this period
    

    /*--- VARIABLE INITS ---*/

    //make sure everything in the off state
    LATD = 0x00; //active high turning off
    Anode2 = 1; //active low turning off because we share it with the D port
    Colon = 1; //off
    PMLight = 1; //off

    /*--- TIMING CALCULATIONS ---*/
    digitShowTime_us = 1/((double)LED_DSP_REFRESH_RATE)/4*1000000; //calculate the time to show one digit
    timerCountDigit_tresh = 32;//(char)(digitShowTime_us/((double)TIMER0_PERIOD_US));       //calc number of timer steps to get to next digit
    //timerCountPWM_tresh = digitShowTime_us/LED_PWM_BRIGHTNESS_LEVELS/TIMER0_PERIOD_US; //calc number of steps to get to next PWM level

}

/*--- UNUSED -------------*/
//void LED_setDisplay(char digit, char value) {
//    settingIndividualElements = 0;
//    switch(digit){
//        case 0: digit0 = value; break;
//        case 1: digit1 = value; break;
//        case 2: digit2 = value; break;
//        case 3: digit3 = value; break;
//        default: break;
//    }
//}

void turnOffColon() {
    colon_val = 0;
    //Colon = 1; //active low
}

void turnOnColon() {
    colon_val = 1;
    //Colon = 0; //active low
}

void turnOnPMLight() {
    PMlight_val = 1;
    //PMLight = 0; //active low
}

void turnOffPMLight() {
    PMlight_val = 0;
    //PMLight = 1; //active low
}

void turnOffAlarmLight(){
    alarmLight_val = 0;
}

void turnOnAlarmLight(){
    alarmLight_val = 1;
}

void Display_setBrightnessAll(unsigned char brightParam){
    digit0Brightness = brightParam;
    digit1Brightness = brightParam;
    digit2Brightness = brightParam;
    digit3Brightness = brightParam;
    periphBrightness = brightParam;
    ringBrightness = brightParam;
}

void Display_setBrightnessEverythingButRing(unsigned char brightParam){
    digit0Brightness = brightParam;
    digit1Brightness = brightParam;
    digit2Brightness = brightParam;
    digit3Brightness = brightParam;
    periphBrightness = brightParam;
}



void Display_setRingBrightness(unsigned char ringBparam){
    ringBrightness = ringBparam;
}

void Display_setAll4(unsigned char tD0,unsigned char tD1,unsigned char tD2,unsigned char tD3){
    settingIndividualElements = 0;
    digit0 = tD0;
    digit1 = tD1;
    digit2 = tD2;
    digit3 = tD3;
}



void Display_showNumber(unsigned int num2Disp){    
    volatile unsigned char tempDisp0, tempDisp1, tempDisp2, tempDisp3;
    volatile unsigned char leadBlank;
    settingIndividualElements = 0;
    leadBlank = 1;
    tempDisp3=(unsigned char)(num2Disp%10);
    num2Disp /= 10;
    tempDisp2=(unsigned char)(num2Disp%10);
    num2Disp /= 10;
    tempDisp1=(unsigned char)(num2Disp%10);
    num2Disp /= 10;
    tempDisp0=(unsigned char)(num2Disp%10);

    if(!tempDisp0)//its 0
        tempDisp0 = BLANK;
    else
        leadBlank = 0;
    if(!tempDisp1 && leadBlank)//its 0
        tempDisp1 = BLANK;
    else
        leadBlank = 0;
    if(!tempDisp2 && leadBlank)//its 0
        tempDisp2 = BLANK;
    else
        leadBlank = 0;

    Display_setAll4(tempDisp0, tempDisp1, tempDisp2, tempDisp3);
}

void Display_On(void){
    settingIndividualElements = 0;
    turnOffColon();
    digit0 = BLANK;
    digit1 = BLANK;
    digit2 = LETTER_O;
    digit3 = LETTER_N;
}

void Display_Off(void){
    settingIndividualElements = 0;
    turnOffColon();
    digit0 = BLANK;
    digit1 = LETTER_O;
    digit2 = LETTER_F;
    digit3 = LETTER_F;
}

void Display_setIndividualBright(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3){
    digit0Brightness = b0;
    digit1Brightness = b1;
    digit2Brightness = b2;
    digit3Brightness = b3;
}

#pragma interruptlow LED_muxAway
static void LED_muxAway(){
    volatile unsigned char curVal2Disp;
    //LATAbits.LATA0 =1; way to test the ISR
    if(TIMER0_OFLOW) {
        
        TIMER0_OFLOW = 0; //Clear the T0IF flag
        num_timerCountDigit++; //incrememnt Digit timer count

        //check to see if we're done with this digit
        if(num_timerCountDigit >= timerCountDigit_tresh){
            //we're done with this digit! reset everything and move on to the next digit

            num_timerCountDigit = 0;
            num_levels_PWM = 0;
            //enact the set peripheral values
            
            /*-----------START OF enactPeriphs()-----------------------*/
            if(num_levels_PWM >= periphBrightness){
                //turn off the periphal for the remainder of this period
                PMLight = 1;
                Colon = 1;
            }else{
                PMLight = ~PMlight_val; //negated because it is active low
                Colon = ~colon_val;
            }
            //ring light
            if (num_levels_PWM >= ringBrightness) {
                //turn off the periphal for the remainder of this period
                ALARM_LED = 0; //active high
            }else{
                ALARM_LED = alarmLight_val;
            }
            /*-----------END OF enactPeriphs()-----------------------*/

            //move on to the next digit
            if(curDisplayDigit >=3)
                curDisplayDigit = 0;
            else
                curDisplayDigit++;
            //display it!
            
            //---------START OF enactDisplay()-------------------------
            //current value to display holder


            //turn the anodes off to prevent ghosting
             Anode0 = 1; Anode1 =  1; Anode2 = 1; Anode3 = 1;

            if(!settingIndividualElements){
                //Get the current value to display
                switch(curDisplayDigit){
                    case 0: curVal2Disp = digit0; break;
                    case 1: curVal2Disp = digit1; break;
                    case 2: curVal2Disp = digit2; break;
                    case 3: curVal2Disp = digit3; break;
                }


                //Set the cathodes for the current values
                switch (curVal2Disp) {
                    case 0: LATD = SEG_0;   break;
                    case 1: LATD = SEG_1;   break;
                    case 2: LATD = SEG_2;   break;
                    case 3: LATD = SEG_3;   break;
                    case 4: LATD = SEG_4;   break;
                    case 5: LATD = SEG_5;   break;
                    case 6: LATD = SEG_6;   break;
                    case 7: LATD = SEG_7;   break;
                    case 8: LATD = SEG_8;   break;
                    case 9: LATD = SEG_9;   break;
                    case 10: LATD = SEG_o;  break;
                    case 11: LATD = SEG_n;  break;
                    case 12: LATD = SEG_f;  break;
                    default:LATD = 0b10000000;  break; //display off
                }
            }else{ //This is for individual element control
                switch(curDisplayDigit){
                    case 0: curVal2Disp = individualElements0; break;
                    case 1: curVal2Disp = individualElements1; break;
                    case 2: curVal2Disp = individualElements2; break;
                    case 3: curVal2Disp = individualElements3; break;
                }

                LATD = curVal2Disp;
            }


            //Set the right anode
            switch (curDisplayDigit) { //digit anode control
                case 0: if(num_levels_PWM >= digit0Brightness) LATD &= 0b10000000; else { Anode0 = 0; Anode1 =  1; Anode2 = 1; Anode3 = 1; } break;
                case 1: if(num_levels_PWM >= digit1Brightness) LATD &= 0b10000000; else { Anode0 = 1; Anode1 =  0; Anode2 = 1; Anode3 = 1; } break;
                case 2: if(num_levels_PWM >= digit2Brightness) LATD &= 0b10000000; else { Anode0 = 1; Anode1 =  1; Anode2 = 0; Anode3 = 1; } break;
                case 3: if(num_levels_PWM >= digit3Brightness) LATD &= 0b10000000; else { Anode0 = 1; Anode1 =  1; Anode2 = 1; Anode3 = 0; } break;
                default: break;
            }
            //---------END OF enactDisplay() -------------------------------------------
        }


        /*--- PWM Brightness handler ---*/
        //do a check to see if we need to turn anything off
        //----------START OF ENACT Brigthness---------------------------------------
        //first check the digit
        switch(curDisplayDigit){
            case 0: if(num_levels_PWM >= digit0Brightness) LATD &= 0b10000000; break;
            case 1: if(num_levels_PWM >= digit1Brightness) LATD &= 0b10000000; break;
            case 2: if(num_levels_PWM >= digit2Brightness) LATD &= 0b10000000; break;
            case 3: if(num_levels_PWM >= digit3Brightness) LATD &= 0b10000000; break;
        }
        //then check the peripherals
        if(num_levels_PWM >= periphBrightness){
            //turn off the periphal for the remainder of this period
            PMLight = 1;
            Colon = 1;
        }
        if(num_levels_PWM >= ringBrightness){
            //turn off the periphal for the remainder of this period
            ALARM_LED = 0; //active high
        }
        //----------END OF ENACT Brigthness---------------------------------------
        //we've reached a PWM level
        num_levels_PWM++; //increment the level counter
        //num_timerCountPWM = 0; //reset the timer step counter

        
    } if(TIMER1_OFLOW){ //timer 1 counter
        Timer_millis += 33; //increment by 33 ms
        TIMER1_OFLOW = 0; //reset it

    }
    //LATAbits.LATA0 =0; way to test the ISR
}

void setPM_Light(unsigned char onOff){
    PMlight_val = onOff;
}


void Display_setIndividualElements(unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3){
    settingIndividualElements = 1;
    individualElements0 = d0;
    individualElements1 = d1;
    individualElements2 = d2;
    individualElements3 = d3;
}

/*--- T I M E R - 0 --- N O L A N -------------*/
unsigned short long Timer_msSinceReset(void) {
    return Timer_millis;
}

void Timer_reset(void) {
    Timer_millis = 0;
}