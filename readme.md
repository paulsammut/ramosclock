# Ramos Alarm Clock

The Ramos Alarm Clock was an alarm clock that forced people to get out of bed in
the morning by making it impossible to shut off the alarm from bed and simply
going back to sleep. It accomplished this by the use of a "defuse panel" which
was a wireless keypad that the user would place somewhere far away from their
bedroom. Most users put it in the bathroom; more extreme users put in their car.
When the alarm went off, the user had to get out of bed, and walk to the defuse
panel and punch in a defuse code to turn off the alarm. This gave well
intentioned users that really wanted to get up early but just had a hard time
escaping the cozy gravitational field of their bed the push they needed to start
their day fresh and early (kinda like how mom woke you up during highschool).

This project started out as a [kickstarter
campaign](https://www.kickstarter.com/projects/2074185253/ramos-alarm-clock)

![Maple Nixie Ramos](images/maple.jpg?raw=true "Nixie_Ramos")

## Source Code

This source was written by Nolan Sandberg, and Paul Sammut.

This is the source code for the Nixie Ramos, LED Ramos and the defuse panel.
These 3 devices shared similar code and all ran on the same PIC18F
microcontroller. The code includes the MPLAB project files and the compiler used
was the C18 compiler. All source is written in C and programmed using a PicKit3.
There are loads of features in the clock such as:

* Sound system for playing tones and a voice menu Digit cycling on each minute
* for Nixie Tube health The defuse code could be either the day's date or a
* random code An external RTC with an built in XTCO with a clock accuracy of
* 4PPM Multiplex display driver that allowed for 32 levels of brightness for
* each tube Autodim brightness with an light sensor, to dim the display to a
* settable level when there is no light in the room.

![LED Ramos left and Nixie Ramos right](images/IMG_1116.JPG?raw=true
"LED_Nixie_Ramos")

## Circuit Files

Included in this repo are also all the schematics, gerbers and altium files. The
boards were panelized and mass produced. Great consideration was taken to
minimize the BOM count and facilitate assembly. These clocks all passed FCC
testing, even the Nixie! One of the very few Nixie Clocks that's FCC certed. The
EMC report is included in the schematics folder.

![Circuit Board](images/nixie_board.gif?raw=true "Nixie board")

### Nixie Circuit

IN-12A Nixie tubes were used. I bought thousands in bulk from sellers in the
Ukraine and Russia. When I bought them in 2012-2014 the price was around $1.50 a
tube shipped. 

The nixie circuit used a Taylor Edge 1364 high voltage power supply that
supplied the 170 Volts. The display was controlled using ULN2003s in a neat way.
You can't find 8 channel transistor IC's that can handle 180V's anymore, and I
didn't want to use the original Russian nixie drivers IC's for reliability
issues, so I used the ULN2003's which had a max volt rating of 100V and clamped
the common voltage to 91V. This meant that in their off state, the tubes saw
91V, which wasn't enough to fire the tubes, and in their on state they saw the
full 170V. The ULN's only saw the delta of 170 and 91, which was below the max
rated voltage, so it was happy. Out of the thousand clocks we sold, we never had
an issue with the driver circuitry. 

### Wireless

The wireless data link betweeon the defuse panel and the clock is handled by a
CC1101 chip on board an Anaren module. This module was the most expensive part
of the bom ($11 at high volume) but it was pre-certed as an intentional
radiator. Iterfacing to the CC1101 chip was a bit of a pain, the but the source
is all there as a reference. Great chip and we had very good range throughout a
house and sometimes outside the house.

### The Alarm Not Going Off Bug

We made a thousand of these clocks and only had one return. But, there was one
major bug that we caught early on and it had to do with the sound system
communication. A couple of people would email us, swearing that their alarm
didn't go off.

It was a really interesting problem because you could never replicated it on the
bench, and when the user would power cycle their clock it would magically work
again. This was because the problem was related to accumulated ossilator drift
which effected the PWM communication timing with the sound chip, meaning that
whenever you restarted the clock the problem would go away. The problem would
only manifiest itself in a tiny percentage of our clocks, after the clock was
running for a long period of time. I was never ever able to reproduce the
problem, but I was able to pin point it to a less than robust communications PWM
protocol with the sound chip.

In the original firmware, the PIC18, who handled all the state flow stuff, would
send a signal to the sound chip using a PWM serial comms protocol to play a
sound. The PIC18 would assume that the sound was playing and happily move on.
This worked all the time during bench testing and our beta testing, and our
inital shipments. But it had no error checking and when you start playing
statistics, with a 1000 devices each with an alarm event every day, with
oscillator drift ranges, it meant that a tiny percentage of those sound commands
sent through PWM had their pulse widths exceeding the limits, meaning a poor
person's alarm wouldn't go off that morning. 

I fixed it by monitoring a DO line from the sound chip that would go high when
sound was playing. On every sound command sent by the PIC18, it made sure to
monitor the response from the sound chip. If it detected no sound was playing it
would do a live oscillator re-cal and resend the command. I was lucky to have
routed this line to a DI pin on the PIC18, so it was a simple firmware fix. 

### Altium Board Files

![Panelized boards](images/panelized_nixie.PNG?raw=true "Panelized Board")

Included are packged Altium files for all the boards. They were packed using
Altium 2019. Included are also all the panelized boards.
