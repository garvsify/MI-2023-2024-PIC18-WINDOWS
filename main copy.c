#include <xc.h>
#include "system_uC.h"

int main(void)
{
    SYSTEM_Initialize();
    
    /*get_current_pot_values();
    process_TMR0_raw_speed_and_prescaler();
    process_TMR0_and_prescaler_adjust();
    TMR0H = (uint8_t) final_TMR0;
    */
    
    INTERRUPT_GlobalInterruptEnable();
    current_waveshape = SQUARE_MODE;
    
    while(1){
        
        //get_current_pot_values();
        //process_TMR0_raw_speed_and_prescaler();
        //process_TMR0_and_prescaler_adjust();
        
        
        ClrWdt();
    }    
}
