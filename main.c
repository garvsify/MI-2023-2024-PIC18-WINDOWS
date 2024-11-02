#include <xc.h>
#include "system_uC.h"


/*IMPORTANT INFO ABOUT BUILDING:

Use XC8 v2.50 and Pack v1.25.433

 */

/*IMPORTANT INFO ABOUT USAGE:

MPLAB:

 - Use Windows MPLAB v6.20 ONLY for MCC as macOS Sequoia causes MPLAB v6.15/v6.20 to shit itself when trying to use MCC
 - Use macOS to actually build and run the program, but currently due to macOS Sequoia you have to program in MPLAB IPE not the IDE
 
Usage of each peripheral:

 - TMR0 generates the interrupt to change the value loaded into the TMR0H register, which controls the frequency of the oscillation.
 - TMR1 is currently unused but could be used for DMA to generate the interrupt to trigger the data transfer of ADC values into working variables.
 - TMR2 is used exclusively by the CCP module and interrupts should not be enabled
 
 */

/*
 
HOW THE DMA/ADCC STUFF WORKS:

1.	Set up the ADCC_type and DMA1_type such that they are the same, e.g. waveshape. They will need to be incremented at separate times by the completion of an ADCC conversion and a DMA1 transfer completion, so they cannot be the same physical variable.
2.	Enable TMR1 interrupts
3.	Start TMR1 counting
4.	TMR1 interrupts will cause ADCC conversion to occur, based off whatever ADCC_type is currently set (symmetry, waveshape, speed, and depth) ? its own interrupt will cause DMA1 transfer. At the end of the ADCC conversion, the ADCC_type is incremented.
5.	DMA1 transfer will directly update the adres variable, and depending on the state of the DMA1_type, will transfer this into the correct variable, e.g. current_waveshape, current_speed, etc.

 */

int main(void){

    SYSTEM_Initialize();
    
    //set some arbitrary speed values
    /*T0CON1bits.CKPS = 0b0100;
    final_TMR0 = 100;*/
    
    PIE2bits.DMA1DCNTIE = 0;
    PIE4bits.TMR3IE = 0;
    PIE3bits.TMR1IE = 1;
    
    INTERRUPT_GlobalInterruptEnable();

    TMR1_Write(TMR1_OVERFLOW_COUNT);
    TMR1_Start(); //ADCC is triggered on overflow, including TMR3, which then triggers the DMA transfer on its overflow
    //LATC5 = 1;
    
    //while(ready_to_start_oscillator == 0){} //wait for all adcc values to be loaded
    
    process_TMR0_raw_speed_and_prescaler(); 
    process_TMR0_and_prescaler_adjust();
    
    TMR0_Start(); //start oscillator

    while(1){

        process_TMR0_raw_speed_and_prescaler();
        process_TMR0_and_prescaler_adjust();

        ClrWdt();
    }
}