/**
  * TMR3 Generated Driver File
  *
  * @file tmr3.c
  *
  * @ingroup tmr3
  *
  * @brief Driver implementation for the TMR3 driver
  *
  * @version TMR3 Driver Version 3.1.4
*/
/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

/**
 * Section: Included Files
*/

#include <xc.h>
#include "../tmr3.h"
#include "../../../system_uC.h"

/**
 * Section: Global Variables Definitions
*/
volatile uint16_t timer3ReloadVal;
void (*TMR3_InterruptHandler)(void);

const struct TMR_INTERFACE Timer3 = {
    .Initialize = TMR3_Initialize,
    .Start = TMR3_Start,
    .Stop = TMR3_Stop,
    .PeriodCountSet = TMR3_PeriodCountSet,
    .TimeoutCallbackRegister = TMR3_OverflowCallbackRegister,
    .Tasks = NULL
};
static void (*TMR3_OverflowCallback)(void);
static void TMR3_DefaultOverflowCallback(void);
static void (*TMR3_GateCallback)(void);
static void TMR3_DefaultGateCallback(void);

void TMR3_Initialize(void)
{
    //Disable timer
    T3CONbits.TMR3ON = 0;
    //TGGO done; TGSPM disabled; TGTM disabled; TGPOL low; TMRGE disabled; 
    T3GCON = 0x0;
    //TGSS T3GPPS; 
    T3GATE = 0x0;
    //TMRCS LFINTOSC; 
    T3CLK = 0x4;
    //TMRH 255; 
    TMR3H = 0xFF;
    //TMRL 170; 
    TMR3L = 0xAA;

    // Load the TMR3 value to reload variable
    timer3ReloadVal=((uint16_t)TMR3H << 8) | TMR3L;

    //Set default callback for TMR3 overflow interrupt
    TMR3_OverflowCallbackRegister(TMR3_DefaultOverflowCallback);

    //Set default callback for TMR3 gate interrupt
    TMR3_GateCallbackRegister(TMR3_DefaultGateCallback);

    // Clearing TMRI IF flag before enabling the interrupt.
    PIR4bits.TMR3IF = 0;
    // Enabling TMRI interrupt.
    PIE4bits.TMR3IE = 1;
    
    //TMRON enabled; TRD16 disabled; nTSYNC do_not_synchronize; TCKPS 1:8; 
    T3CON = 0x35;
}

void TMR3_Start(void)
{
    // Start the Timer by writing to TMRxON bit
    T3CONbits.TMR3ON = 1;
}

void TMR3_Stop(void)
{
    // Stop the Timer by writing to TMRxON bit
    T3CONbits.TMR3ON = 0;
}

uint16_t TMR3_Read(void)
{
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;
    	
    readValLow = TMR3L;
    readValHigh = TMR3H;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;

    return readVal;
}

void TMR3_Write(size_t timerVal)
{
    if (T3CONbits.nT3SYNC == 1)
    {
        // Stop the Timer by writing to TMRxON bit
        T3CONbits.TMR3ON = 0;

        // Write to the Timer3 register
        TMR3H = (uint8_t)(timerVal >> 8);
        TMR3L = (uint8_t)timerVal;

        // Start the Timer after writing to the register
        T3CONbits.TMR3ON = 1;
    }
    else
    {
        // Write to the Timer3 register
        TMR3H = (uint8_t)(timerVal >> 8);
        TMR3L = (uint8_t)timerVal;
    }
}

void TMR3_Reload(void)
{
    TMR3_Write(timer3ReloadVal);
}

void TMR3_PeriodCountSet(size_t periodVal)
{
   timer3ReloadVal = (uint16_t) periodVal;
}

void TMR3_StartSinglePulseAcquisition(void)
{
    T3GCONbits.T3GGO = 1;
}

uint8_t TMR3_CheckGateValueStatus(void)
{
    return (T3GCONbits.T3GVAL);
}

void TMR3_OverflowISR(void)
{

    // Clear the TMR3 interrupt flag
    PIR4bits.TMR3IF = 0;

    if(TMR3_OverflowCallback)
    {
        TMR3_OverflowCallback();
    }
}

void TMR3_OverflowCallbackRegister(void (* CallbackHandler)(void))
{
    TMR3_OverflowCallback = CallbackHandler;
}

static void TMR3_DefaultOverflowCallback(void)
{
    //Add your interrupt code here or
    //Use TMR3_OverflowCallbackRegister function to use Custom ISR
    /*TMR3_Stop();
    LATC5 = 0;
    size_t tmr1_value = TMR1_OVERFLOW_COUNT;
    TMR1_Write(tmr1_value);
    TMR1_Start();
    LATC4 = 1;*/
    
    LATC4 = 0;
}

bool TMR3_HasOverflowOccured(void)
{
    return(PIR4bits.TMR3IF);
}

void TMR3_GateISR(void)
{
    // clear the TMR3 interrupt flag
    PIR4bits.TMR3GIF = 0;
    if(TMR3_GateCallback)
    {
        TMR3_GateCallback();
    }
}

void TMR3_GateCallbackRegister(void (* CallbackHandler)(void))
{
    TMR3_GateCallback = CallbackHandler;
}

static void TMR3_DefaultGateCallback(void)
{
    //Add your interrupt code here or
    //Use TMR3_GateCallbackRegister function to use Custom ISR
}


/**
  End of File
*/
