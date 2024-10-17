#include <xc.h>
#include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/system_uC.h"

/*
  Section: Macro Declarations
*/

#define PWM1_INITIALIZE_DUTY_VALUE    0

/**
  Section: PWM1 Module APIs
*/

void CCP1_Initialize(void)
{
    // Set the PWM1 to the options selected in the User Interface
    
    // CCPM PWM; EN enabled; FMT left_aligned; 
    CCP1CON = 0x9C;
    
    // CCPRH 0; 
    CCPR1H = 0x0;
    
    // CCPRL 0; 
    CCPR1L = 0x0;
    
    // Selecting Timer 2
    CCPTMRS0bits.C1TSEL = 0x1;
}

void CCP1_LoadDutyValue(uint16_t dutyValue)
{
	  dutyValue &= 0x03FF;
    
    // Load duty cycle value
    if(CCP1CONbits.FMT)
    {
        dutyValue <<= 6;
        CCPR1H = (uint8_t)(dutyValue >> 8);
        CCPR1L = (uint8_t)dutyValue;
    }
    else
    {
        CCPR1H = (uint8_t)(dutyValue >> 8);
        CCPR1L = (uint8_t)dutyValue;
    }
}
bool CCP1_OutputStatusGet(void)
{
    // Returns the output status
    return(CCP1CONbits.OUT);
}
/**
 End of File
*/
