#include <xc.h>
#include "../system.h"
#include "../clock.h"
#include "../pins.h"
#include "../config_bits.h"
#include "../../dma/dma1.h"
#include "../../adc/adcc.h"
#include "../../pwm/ccp1.h"
#include "../../timer/tmr0.h"
#include "../../timer/tmr1.h"
#include "../../timer/tmr2.h"
#include "../../system/interrupt.h"

void CPU_Initialize(void);

void SystemArbiter_Initialize(void);

void SYSTEM_Initialize(void)
{
    CLOCK_Initialize();
    PIN_MANAGER_Initialize();
    ADCC_Initialize();
    CPU_Initialize();
    DMA1_Initialize();
    CCP1_Initialize();
    TMR0_Initialize();
    TMR1_Initialize();
    TMR2_Initialize();
    INTERRUPT_Initialize();
    SystemArbiter_Initialize();
}

void CPU_Initialize(void)
{
    //PRLOCKED unlocked; 
    PRLOCK = 0x0;
    //PR priority level 7; 
    SCANPR = 0x7;
    //PR priority level 7; 
    DMA1PR = 0x7;
    //PR priority level 7; 
    DMA2PR = 0x7;
    //PR priority level 7; 
    DMA3PR = 0x7;
    //PR priority level 7; 
    DMA4PR = 0x7;
    //PR priority level 7; 
    MAINPR = 0x7;
    //PR priority level 7; 
    ISRPR = 0x7;
    //PRODH undefined; 
    PRODH = 0x0;
    //PRODL undefined; 
    PRODL = 0x0;
}


void SystemArbiter_Initialize(void)
{
    // This function is dependant on the PR1WAY CONFIG bit
    PRLOCK = 0x55;
    PRLOCK = 0xAA;
    PRLOCKbits.PRLOCKED = 1;
}
