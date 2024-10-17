#include <xc.h>
#include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/system_uC.h"

const struct TMR_INTERFACE Timer2 = {
    .Initialize = TMR2_Initialize,
    .Start = TMR2_Start,
    .Stop = TMR2_Stop,
    .PeriodCountSet = TMR2_PeriodCountSet,
    .TimeoutCallbackRegister = TMR2_OverflowCallbackRegister,
    .Tasks = NULL
};

static void (*TMR2_OverflowCallback)(void);
static void TMR2_DefaultOverflowCallback(void);

/**
  Section: TMR2 APIs
*/

void TMR2_Initialize(void){

    // Set TMR2 to the options selected in the User Interface
    // TCS FOSC/4; 
    T2CLKCON = 0x1;
    // TMODE Software control; TCKSYNC Synchronized; TCKPOL Rising Edge; TPSYNC Synchronized; 
    T2HLT = 0xA0;
    // TRSEL T2INPPS pin; 
    T2RST = 0x0;
    // PR 255; 
    T2PR = 0xFF;
    // TMR 0x0; 
    T2TMR = 0x0;

    // Set default overflow callback
    TMR2_OverflowCallbackRegister(TMR2_DefaultOverflowCallback);
    
    //DO NOT TURN ON TMR2 INTERRUPTS!!!!
    // Clearing IF flag before enabling the interrupt.
    //PIR3bits.TMR2IF = 0;
    // Enabling TMR2 interrupt.
    //PIE3bits.TMR2IE = 1;
    //DO NOT TURN ON TMR2 INTERRUPTS!!!!
    
    //TCKPS 1:1; TMRON on; TOUTPS 1:1; 
    T2CON = 0x80;
}

void TMR2_ModeSet(TMR2_HLT_MODE mode)
{
   // Configure different types HLT mode
    T2HLTbits.T2MODE = mode;
}

void TMR2_ExtResetSourceSet(TMR2_HLT_EXT_RESET_SOURCE reset)
{
    //Configure different types of HLT external reset source
    T2RSTbits.T2RSEL = reset;
}

void TMR2_Start(void)
{
    // Start the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 1;
}

void TMR2_Stop(void)
{
    // Stop the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 0;
}

uint8_t TMR2_Read(void)
{
    uint8_t readVal;
    readVal = TMR2;
    return readVal;
}

void TMR2_Write(uint8_t timerVal)
{
    // Write to the Timer2 register
    TMR2 = timerVal;;
}

void TMR2_PeriodCountSet(size_t periodVal)
{
   PR2 = (uint8_t) periodVal;
}

void TMR2_ISR(void)
{
    // clear the TMR2 interrupt flag
     PIR3bits.TMR2IF = 0;

    if(TMR2_OverflowCallback)
    {
        TMR2_OverflowCallback();
    }
}

void TMR2_OverflowCallbackRegister(void (* InterruptHandler)(void))
{
   TMR2_OverflowCallback = InterruptHandler;
}

static void TMR2_DefaultOverflowCallback(void)
{
    // add your TMR2 interrupt custom code
    // or set custom function using TMR2_OverflowCallbackRegister()
}

