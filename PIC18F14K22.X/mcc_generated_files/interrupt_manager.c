/**
  @Generated Interrupt Manager File

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.c

  @Summary:
    This is the Interrupt Manager file generated using MPLAB?Code Configurator

  @Description:
    This header file provides implementations for global interrupt handling.
    For individual peripheral handlers please see the peripheral driver for
    all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB?Code Configurator - v2.25.2
        Device            :  PIC18F14K22
        Driver Version    :  1.02
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

#include "interrupt_manager.h"
#include "mcc.h"

void INTERRUPT_Initialize(void) {
    // Enable Interrupt Priority Vectors
    RCONbits.IPEN = 1;

    // Assign peripheral interrupt priority vectors

    // TMRI - high priority
    IPR2bits.TMR3IP = 1;


    // TXI - low priority
    IPR1bits.TXIP = 0;

    // RCI - low priority
    IPR1bits.RCIP = 0;

    // TMRI - low priority
    INTCON2bits.TMR0IP = 0;


}

void interrupt INTERRUPT_InterruptManagerHigh(void) {
    // interrupt handler
    if (PIE2bits.TMR3IE == 1 && PIR2bits.TMR3IF == 1) {
        TMR3_ISR();
    }
}

void interrupt low_priority INTERRUPT_InterruptManagerLow(void) {
    // interrupt handler
    if (PIE1bits.TXIE == 1 && PIR1bits.TXIF == 1) {
        EUSART_Transmit_ISR();
    }
    if (PIE1bits.RCIE == 1 && PIR1bits.RCIF == 1) {
        EUSART_Receive_ISR();
    }
    if (INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1) {
        TMR0_ISR();
    }
}
/**
 End of File
 */