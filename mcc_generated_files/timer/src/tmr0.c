#include <xc.h>
#include "../tmr0.h"
#include "../../../system_uC.h"

const struct TMR_INTERFACE Timer0 = {
    .Initialize = TMR0_Initialize,
    .Start = TMR0_Start,
    .Stop = TMR0_Stop,
    .PeriodCountSet = TMR0_Reload,
    .TimeoutCallbackRegister = TMR0_OverflowCallbackRegister,
    .Tasks = NULL
};

static void (*TMR0_OverflowCallback)(struct Global_Variables global_variables);
static void TMR0_DefaultOverflowCallback(struct Global_Variables global_variables);

/**
  Section: TMR0 APIs
*/  

void TMR0_Initialize(void){

    //TMR0H 255; 
    TMR0H = 0xFF;

    //TMR0L 0; 
    TMR0L = 0x0;

    //T0CS FOSC/4; T0CKPS 1:1; T0ASYNC synchronised; 
    T0CON1 = 0x40;


    //Set default callback for TMR0 overflow interrupt
    TMR0_OverflowCallbackRegister(TMR0_DefaultOverflowCallback);

    //Clear Interrupt flag before enabling the interrupt
    PIR3bits.TMR0IF = 0;
	
    //Enable TMR0 interrupt.
    PIE3bits.TMR0IE = 1;
	
    //T0OUTPS 1:1; T0EN enabled; T016BIT 8-bit; 
    T0CON0 = 0x80;
}

void TMR0_Start(void)
{
    T0CON0bits.T0EN = 1;
}

void TMR0_Stop(void)
{
    T0CON0bits.T0EN = 0;
}

uint8_t TMR0_Read(void)
{
    uint8_t readVal;

    //Read TMR0 register, low byte only
    readVal = TMR0L;

    return readVal;
}

void TMR0_Write(uint8_t timerVal)
{
    //Write to TMR0 register, low byte only
    TMR0L = timerVal;
 }

void TMR0_Reload(size_t periodVal)
{
   //Write to TMR0 register, high byte only
   TMR0H = (uint8_t)periodVal;
}

void TMR0_OverflowISR(void)
{
    //Clear the TMR0 interrupt flag
    PIR3bits.TMR0IF = 0;
    if(TMR0_OverflowCallback)
    {
        TMR0_OverflowCallback();
    }
}

void TMR0_OverflowCallbackRegister(void (* CallbackHandler)(struct Global_Variables global_variables))
{
    TMR0_OverflowCallback = CallbackHandler;
}

uint8_t multiply_duty_by_current_depth_and_divide_by_256(struct Global_Variables global_variables){
    
    global_variables.dutyL = (uint8_t)global_variables.duty;
    global_variables.dutyH = global_variables.duty >> 8;
    global_variables.current_depthL = (uint8_t)global_variables.current_depth;
    
    asm("MOVF _global_variables.current_depthL, W");
    asm("MULWF _global_variables.dutyL");
    asm("MOVFF PRODH, _global_variables.res1");
    asm("MOVFF PRODL, _global_variables.res0");
    global_variables.result_of_low_by_low = (uint16_t)((uint16_t)(global_variables.res1 << 8) | global_variables.res0);
    
    asm("MOVF _global_variables.current_depthL, W");
    asm("MULWF _global_variables.dutyH");
    asm("MOVFF PRODH, _global_variables.res3");
    asm("MOVFF PRODL, _global_variables.res2");
    global_variables.result_of_low_by_high = (uint32_t)(((uint32_t)(global_variables.res3 << 8) | (uint32_t)global_variables.res2) << 8);
    
    global_variables.multiply_product = global_variables.result_of_low_by_high + global_variables.result_of_low_by_low;
    global_variables.duty = 1023 - (uint16_t)(global_variables.multiply_product >> 8);
    
    return 1;
}

static void TMR0_DefaultOverflowCallback(struct Global_Variables global_variables)
{
    TMR0H = (uint8_t)global_variables.final_TMR0; //this line must go here, or at least very near the beginning!
        //LATC5 = 1; //start ISR length measurement
        TMR0IF = 0; //clear TMR0 interrupt flag

        if(global_variables.current_waveshape == TRIANGLE_MODE){
            global_variables.duty = tri_table_one_quadrant[global_variables.current_one_quadrant_index];
        }
        else if(global_variables.current_waveshape == SINE_MODE){
            global_variables.duty = sine_table_one_quadrant[global_variables.current_one_quadrant_index];
        }
        else if(global_variables.current_waveshape == SQUARE_MODE){
            global_variables.duty = 1023;
        }
        if(global_variables.current_one_quadrant_index == MAX_QUADRANT_INDEX){
            global_variables.current_quadrant = SECOND_QUADRANT;
        }
        else if(global_variables.current_one_quadrant_index == MIN_QUADRANT_INDEX){
            global_variables.current_quadrant = FIRST_QUADRANT;
            if(global_variables.current_halfcycle == FIRST_HALFCYCLE){
                global_variables.current_halfcycle = SECOND_HALFCYCLE;
            }
            else{
                global_variables.current_halfcycle = FIRST_HALFCYCLE;
            }
        }
        if(global_variables.current_quadrant == FIRST_QUADRANT){
            global_variables.current_one_quadrant_index++;
        }
        else{
            global_variables.current_one_quadrant_index--;
        }
        if(global_variables.current_halfcycle == SECOND_HALFCYCLE){
        global_variables.duty = 1023 - global_variables.duty;
        }

        #if DEPTH_ON_OR_OFF == 1

            //Apply Depth
            if(current_depth == 255){
                duty = 1023 - duty;
            }
            else if(current_depth != 0){
                //duty = 1023 - duty*(current_depth >> 8);
                multiply_duty_by_current_depth_and_divide_by_256();
            }
            else{
                duty = 1023; //if depth is 0, just output 1023
            }
        
        #endif

        //Write Duty
        CCP1_LoadDutyValue(global_variables.duty);

        //Finish Up
        //LATC5 = 0; //finish ISR length measurement
}

