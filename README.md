# Lab 3: Timers and Interrupts

#Gray Thurston 

# Button Interrupt

## Introduction

The purpsose of this lab was to get familiar with setting up and 
controling interupts on the MSP430. To do this we needed to configure 
the P1IE, P1IES, and P1IFG registers. The LED P1OUT bits are then 
corntrolled from the Intertupt Service Routine.


##Implimented Devices
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430G2553


## Functioanlity

Toggles the onboard LEDs by using an interuppt serivce routine controlled
by an onboard button.

## Dependencies
There are no external dependencies that need to be used in order for this 
code to function as intended. Just the standerd MSP430.h header file.

## Errors
The only known errors in this lab have to do with the bounce of the mechanical 
switch. This can be fixed with a simple hardware RC circuit ot in software. 
This issue was not fixed in this lab.

## Tasks

Recreate lab 2 push button toggle using interupts to toggle the LED instead of polling.

# Timer A Blink 

## Introduction

The Purpose of this lab was to blink the LED using the MSP430's 
built in timer modules. To do this we needed to cofigure the 
TACCTL0, TA0CTL, TACCR0, and TA0CCTL0 registers. Using these registers
timer A was configured to run off of the Sub master clock, run in 
up mode, be divided by 8 and run in comapre mode. When the counter 
reached the value in in the Capture Compare register it would trigger an
interupt that toggled the on board LED's.

##Implimented Devices
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430G2553

## Functioanlity
Blinks the onboard LEDs using the TIMER A module.

## Errors
No known errors

## Tasks

Recreate lab 2 led blink using TIMER A instead of a counter. 

# Button Based Delay

## Introduction

In this lab we were asked to control the frequancy at which one of the one board led's blinked
with one of the on board buttons. In order to do this we needed to initialize two timers.
One that controlled the interrupt that blinked the led, and one that counted for the duration of the button 
press. On startup timer a0 is set to blink the led at a set rate of 10hz. Once the on board led has been 
pressed, timer a1 counts till the falling edge of the button. Then the value in the TA1R becomes the 
value in the timer a0 capture and comapre register.

##Implimented Devices
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430G2553


## Tasks
Control the blinking speed of an led with a button. The duration of the button press is to be the delay in the 
button blink cycle. 














