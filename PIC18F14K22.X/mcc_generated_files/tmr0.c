/**
  TMR0 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr0.c

  @Summary
    This is the generated driver implementation file for the TMR0 driver using MPLAB� Code Configurator

  @Description
    This source file provides APIs for TMR0.
    Generation Information :
        Product Revision  :  MPLAB� Code Configurator - v2.25.2
        Device            :  PIC18F14K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

/**
  Section: Included Files
 */

#include <xc.h>
#include "tmr0.h"

/**
  Section: Global Variables Definitions
 */
volatile uint16_t timer0ReloadVal16bit;

/**
  Section: TMR0 APIs
 */

/**
  Section: Extern
 */
extern volatile uint32_t timer0TenMsTickCounter;

void TMR0_Initialize(void) {
    // Set TMR0 to the options selected in the User Interface

    // TMR0ON enabled; T0SE Increment_hi_lo; PSA not_assigned; T0CS FOSC/4; T08BIT 16-bit; T0PS 1:256; 
    T0CON = 0x9F;

    // TMR0H 99; 
    TMR0H = 0x63;

    // TMR0L 192; 
    TMR0L = 0xC0;

    // Load TMR0 value to the 16-bit reload variable
    timer0ReloadVal16bit = 25536;

    // Clear Interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;

    // Enabling TMR0 interrupt.
    INTCONbits.TMR0IE = 1;

    // Start TMR0
    TMR0_StartTimer();
}

void TMR0_StartTimer(void) {
    // Start the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 1;
}

void TMR0_StopTimer(void) {
    // Stop the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 0;
}

uint16_t TMR0_Read16bitTimer(void) {
    uint16_t readVal;
    uint8_t readValLow;
    uint8_t readValHigh;

    readValLow = TMR0L;
    readValHigh = TMR0H;
    readVal = ((uint16_t) readValHigh << 8) + readValLow;

    return readVal;
}

void TMR0_Write16bitTimer(uint16_t timerVal) {
    // Write to the Timer0 register
    TMR0H = timerVal >> 8;
    TMR0L = (uint8_t) timerVal;
}

void TMR0_Reload16bit(void) {
    // Write to the Timer0 register
    TMR0H = timer0ReloadVal16bit >> 8;
    TMR0L = (uint8_t) timer0ReloadVal16bit;
}

void TMR0_ISR(void) {

    // clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;

    // reload TMR0
    // Write to the Timer0 register
    TMR0H = timer0ReloadVal16bit >> 8;
    TMR0L = (uint8_t) timer0ReloadVal16bit;

    // ticker function call;
    // ticker is 1 -> Callback function gets called every time this ISR executes
    TMR0_CallBack();

    // add your TMR0 interrupt custom code
}

void TMR0_CallBack(void) {
    // Add your custom callback code here
    // this code executes every 1 TMR0 periods
    timer0TenMsTickCounter++;
}
/**
  End of File
 */