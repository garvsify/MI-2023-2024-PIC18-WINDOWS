#ifndef SYSTEM_UC_H

    #define SYSTEM_UC_H

    #include <xc.h>
    #include "wavetables.h"
    #include "pinouts.h"
    #include <stdint.h>
    #include <stdbool.h>
    #include "mcc_generated_files/system/system.h"
    #include "mcc_generated_files/system/pins.h"
    #include "mcc_generated_files/system/interrupt.h"
    #include "mcc_generated_files/system/config_bits.h"
    #include "mcc_generated_files/system/clock.h"
    #include "mcc_generated_files/timer/tmr3.h"
    #include "mcc_generated_files/timer/tmr2.h"
    #include "mcc_generated_files/timer/tmr1.h"
    #include "mcc_generated_files/timer/tmr0.h"
    #include "mcc_generated_files/timer/timer_interface.h"
    #include "mcc_generated_files/pwm/ccp1.h"
    #include "mcc_generated_files/adc/adcc.h"
    #include "mcc_generated_files/dma/dma1.h"



    #define MAX_QUADRANT_INDEX 128
    #define MIN_QUADRANT_INDEX 0
    #define TRIANGLE_MODE 0
    #define SINE_MODE 1
    #define SQUARE_MODE 2
    #define NUMBER_OF_FREQUENCY_STEPS 600; //883 in calcs, seems to be wrong, but 650 gives 15Hz max freq.
    #define FIRST_HALFCYCLE 0
    #define SECOND_HALFCYCLE 1
    #define FIRST_QUADRANT 0
    #define SECOND_QUADRANT 1
    #define TRIANGLE_MODE_ADC_THRESHOLD 1365
    #define SINE_MODE_ADC_THRESHOLD 2730
    #define SQUARE_MODE_ADC_THRESHOLD 4095
    #define CW 1
    #define CCW 0
    #define MAX_SYMMETRY_TOTAL 361
    #define SHORTEN_PERIOD_FRACTION_16_BIT_NUMBER 47926
    #define LENGTHEN_PERIOD_FRACTION_16_BIT_NUMBER 17609
    #define RESOLUTION_OF_TOTAL_SYMMETRY_FRACTION 16
    #define SHORTEN_POWER_OF_TWO_CONSTANT_8_BIT_SYM 1024
    #define SHORTEN_POWER_OF_TWO_DIVISOR_8_BIT_SYM 12
    #define SHORTEN_POWER_OF_TWO_CONSTANT_10_BIT_SYM 4096
    #define SHORTEN_POWER_OF_TWO_DIVISOR_10_BIT_SYM 14
    #define LENGTHEN_CONSTANT_8_BIT_SYM 896
    #define LENGTHEN_POWER_OF_TWO_DIVISOR_8_BIT_SYM 9
    #define LENGTHEN_CONSTANT_10_BIT_SYM 3584
    #define LENGTHEN_POWER_OF_TWO_DIVISOR_10_BIT_SYM 11
    #define TWELVEBITMINUSONE 4095
    #define TENBITMINUSONE 1023
    #define EIGHTBITMINUSONE 255
    #define ON 1
    #define OFF 0
    #define WAVESHAPE_FLAG 0
    #define SPEED_FLAG 1
    #define DEPTH_FLAG 2
    #define SYMMETRY_FLAG 3
    #define TMR1_OVERFLOW_COUNT 65301 //okay for some STRANGE AF reason, if you set the TMR1 and TMR3 count periods exactly the same it fucks things up so DON'T CHANGE THESE VALUES
    #define TMR3_OVERFLOW_COUNT 65300 //okay for some STRANGE AF reason, if you set the TMR1 and TMR3 count periods exactly the same it fucks things up so DON'T CHANGE THESE VALUES
    #define WAVESHAPE_ADC_CONFIG_VALUE 0x10;
    #define SPEED_ADC_CONFIG_VALUE 0x11;
    #define DEPTH_ADC_CONFIG_VALUE 0x12;
    #define SYMMETRY_ADC_CONFIG_VALUE 0x13;


    #define SYMMETRY_ADC_RESOLUTION 8


    #define SYMMETRY_ON_OR_OFF OFF
    #define DEPTH_ON_OR_OFF OFF



    #if SYMMETRY_ADC_RESOLUTION == 12
        #define SYMMETRY_ADC_HALF_SCALE_NO_BITS 11
        #define SYMMETRY_ADC_FULL_SCALE 4095
        #define SYMMETRY_ADC_HALF_SCALE 2047
    #endif


    #if SYMMETRY_ADC_RESOLUTION == 8
        #define SYMMETRY_ADC_HALF_SCALE_NO_BITS 7
        #define SYMMETRY_ADC_FULL_SCALE 255
        #define SYMMETRY_ADC_HALF_SCALE 128
    #endif
    
    const uint8_t POSITIVE = 1;
    const uint8_t NEGATIVE = 0;
    const uint8_t DO_NOTHING = 0;
    const uint8_t DIVIDE_BY_TWO = 1;
    const uint8_t MULTIPLY_BY_TWO = 2;
    const uint8_t DIVIDE_BY_FOUR = 3;
    const uint8_t DONT_CARE = 4;
    const uint8_t YES = 1;
    const uint8_t NO = 0;
    
    struct Global_Variables{
        volatile uint32_t final_TMR0;
        volatile uint8_t TMR0_prescaler_adjust;
        volatile uint32_t raw_TMR0;
        volatile uint8_t TMR0_base_prescaler_bits_index;
        volatile uint8_t TMR0_prescaler_final_index;
        volatile uint8_t symmetry_status;
        volatile uint16_t speed_control;
        volatile uint32_t speed_control_32;
        volatile uint8_t how_many_128;
        volatile uint16_t duty;
        volatile uint8_t current_waveshape;
        volatile uint16_t current_speed_linear;
        volatile uint32_t current_speed_linear_32;
        volatile uint16_t current_depth;
        volatile uint32_t current_symmetry;
        volatile uint8_t current_one_quadrant_index;
        volatile uint8_t current_halfcycle;
        volatile uint8_t current_quadrant;
        volatile uint8_t prescaler_final_index;
        adc_result_t ADC_result;
        volatile uint8_t dutyL;
        volatile uint8_t dutyH;
        volatile uint8_t current_depthL;
        volatile uint16_t result_of_low_by_low;
        volatile uint32_t result_of_low_by_high;
        volatile int32_t multiply_product;
        volatile uint8_t res0;
        volatile uint8_t res1;
        volatile uint8_t res2;
        volatile uint8_t res3;
        volatile uint8_t ready_to_start_oscillator;
        
        volatile const uint8_t TMR0_prescaler_bits[9];
        volatile const adcc_channel_t** volatile current_dma_type_ptr;
        volatile const adcc_channel_t waveshape_adc_config_value;
        volatile const adcc_channel_t speed_adc_config_value;
        volatile const adcc_channel_t depth_adc_config_value;
        volatile const adcc_channel_t symmetry_adc_config_value;
        };
    
    uint8_t process_TMR0_raw_speed_and_prescaler(struct Global_Variables global_variables);
    uint8_t process_TMR0_and_prescaler_adjust(struct Global_Variables global_variables);
    uint8_t adjust_and_set_TMR0_prescaler(struct Global_Variables global_variables);
    uint8_t shorten_period(void);
    uint8_t lengthen_period(void);
    
    extern struct Global_Variables global_variables;
    
#endif