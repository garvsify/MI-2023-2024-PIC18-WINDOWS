#ifndef SYSTEM_UC_H

    #define SYSTEM_UC_H

    #include <xc.h>
    #include "wavetables.h"
    #include "pinouts.h"
    #include <stdint.h>
    #include <stdbool.h>
    #include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/mcc_generated_files/system/system.h"
    #include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/mcc_generated_files/system/pins.h"
    #include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/mcc_generated_files/system/interrupt.h"
    #include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/mcc_generated_files/system/config_bits.h"
    #include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/mcc_generated_files/system/clock.h"
    #include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/mcc_generated_files/timer/tmr3.h"
    #include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/mcc_generated_files/timer/tmr2.h"
    #include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/mcc_generated_files/timer/tmr1.h"
    #include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/mcc_generated_files/timer/tmr0.h"
    #include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/mcc_generated_files/timer/timer_interface.h"
    #include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/mcc_generated_files/pwm/ccp1.h"
    #include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/mcc_generated_files/adc/adcc.h"
    #include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/mcc_generated_files/dma/dma1.h"



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
    #define TMR1_OVERFLOW_COUNT 65450 
    #define TMR3_OVERFLOW_COUNT 65450

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


    const uint8_t TMR0_prescaler_bits[9] = {0b00001000,0b00000111,0b00000110,0b00000101,0b00000100,0b00000011,0b00000010,0b00000001,0b00000000}; //256,128,64,32,16,8,4,2,1 - values do extend beyond 256 but we don't need them
    adcc_channel_t waveshape_adc_config_value = channel_ANC0;
    adcc_channel_t speed_adc_config_value = channel_ANC1;
    adcc_channel_t depth_adc_config_value = channel_ANC2;
    adcc_channel_t symmetry_adc_config_value = channel_ANC3;
    const uint8_t POSITIVE = 1;
    const uint8_t NEGATIVE = 0;
    const uint8_t DO_NOTHING = 0;
    const uint8_t DIVIDE_BY_TWO = 1;
    const uint8_t MULTIPLY_BY_TWO = 2;
    const uint8_t DIVIDE_BY_FOUR = 3;
    const uint8_t DONT_CARE = 4;
    const uint8_t YES = 1;
    const uint8_t NO = 0;

    adcc_channel_t *adcc_type_array[4] = {&waveshape_adc_config_value, &speed_adc_config_value, &depth_adc_config_value, &symmetry_adc_config_value};
    adcc_channel_t *dma_type_array[4] = {&waveshape_adc_config_value, &speed_adc_config_value, &depth_adc_config_value, &symmetry_adc_config_value}; //DMA type obviously need not be of adcc_channel_t type but just using for sameness
    adcc_channel_t *current_adcc_type_ptr;
    adcc_channel_t *current_dma_type_ptr; //DMA type obviously need not be of adcc_channel_t type but just using for sameness
    
    
    uint8_t get_current_pot_values(void);
    uint8_t process_TMR0_raw_speed_and_prescaler(void);
    uint8_t turn_TMR0_prescaler_OFF(void);
    uint8_t turn_TMR0_prescaler_ON(void);
    uint8_t adjust_TMR0(void);
    uint8_t adjust_and_set_TMR0_prescaler(void);
    uint8_t shorten_period(void);
    uint8_t lengthen_period(void);
    uint8_t process_TMR0_and_prescaler_adjust(void);

    
    volatile extern uint32_t final_TMR0;
    volatile extern uint8_t TMR0_prescaler_adjust;
    volatile extern uint32_t raw_TMR0;
    volatile extern uint8_t base_prescaler_bits_index;
    volatile extern uint8_t symmetry_status;
    volatile extern uint16_t speed_control;
    volatile extern uint32_t speed_control_32;
    volatile extern uint8_t how_many_128;
    volatile extern uint16_t duty;
    volatile extern uint8_t duty_low_byte;
    volatile extern uint8_t duty_high_byte;
    volatile extern uint8_t current_waveshape;
    volatile extern uint16_t current_speed_linear;
    volatile extern uint32_t current_speed_linear_32;
    volatile extern uint16_t current_depth;
    volatile extern uint32_t current_symmetry;
    volatile extern uint8_t current_one_quadrant_index;
    volatile extern uint8_t current_halfcycle;
    volatile extern uint8_t current_quadrant;
    volatile extern uint8_t prescaler_overflow_flag;
    volatile extern uint8_t prescaler_final_index;
    volatile extern uint8_t ADC_type_flag;
    adc_result_t ADC_result;
    volatile extern uint8_t dutyL;
    volatile extern uint8_t dutyH;
    volatile extern uint8_t current_depthL;
    volatile extern uint16_t result_of_low_by_low;
    volatile extern uint32_t result_of_low_by_high;
    volatile extern uint32_t multiply_product;
    volatile extern uint8_t res0;
    volatile extern uint8_t res1;
    volatile extern uint8_t res2;
    volatile extern uint8_t res3;
    
#endif