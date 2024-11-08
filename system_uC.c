#include "system_uC.h"
#include <xc.h>

struct Global_Variables global_variables = {.current_waveshape = SINE_MODE,
                                            .current_speed_linear = 0,
                                            .current_speed_linear_32 = 0,
                                            .current_depth = 0,
                                            .current_symmetry = 0,
                                            .current_one_quadrant_index = 0,
                                            .current_halfcycle = FIRST_HALFCYCLE,
                                            .current_quadrant = FIRST_QUADRANT,
                                            .how_many_128 = 0,
                                            .final_TMR0 = 0,
                                            .TMR0_prescaler_adjust = 0,
                                            .raw_TMR0 = 0,
                                            .TMR0_base_prescaler_bits_index = 0,
                                            .symmetry_status = 0,
                                            .speed_control = 0,
                                            .speed_control_32 = 0,
                                            .duty = 0,
                                            .TMR0_prescaler_final_index = 0,
                                            .ADC_result = 0,
                                            .ready_to_start_oscillator = 0,
                                            .waveshape_adc_config_value = 0x10,//WAVESHAPE_ADC_CONFIG_VALUE,
                                            .speed_adc_config_value = 0x11,//SPEED_ADC_CONFIG_VALUE,
                                            .depth_adc_config_value = 0x12,//DEPTH_ADC_CONFIG_VALUE,
                                            .symmetry_adc_config_value = 0x13,//SYMMETRY_ADC_CONFIG_VALUE
                                            .prescaler_values = {0b00001000,0b00000111,0b00000110,0b00000101,0b00000100,0b00000011,0b00000010,0b00000001,0b00000000}, //256,128,64,32,16,8,4,2,1 - values do extend beyond 256 but we don't need them
                                            .dma_type_array = {&global_variables.waveshape_adc_config_value, &global_variables.speed_adc_config_value, &global_variables.depth_adc_config_value, &global_variables.symmetry_adc_config_value},
                                            .current_dma_type_ptr = &global_variables.dma_type_array[0]
}; 


uint8_t process_TMR0_raw_speed_and_prescaler(void){
    
    global_variables.current_speed_linear_32 = global_variables.current_speed_linear;
    global_variables.speed_control_32 = global_variables.current_speed_linear_32 * NUMBER_OF_FREQUENCY_STEPS;
    global_variables.speed_control_32 = global_variables.speed_control_32 >> 10;
    global_variables.speed_control = (uint16_t) global_variables.speed_control_32;
    //speed_control = (speed_adc_10_bit/1024)*883
        if(global_variables.speed_control <= (127-12)){ //inequality is correct!
            global_variables.raw_TMR0 = (uint8_t) global_variables.speed_control + 12; //set TMR0
            global_variables.TMR0_base_prescaler_bits_index = 1;
        }
        else{ 	//(speed_control > (127-12))
            uint16_t speed_control_subtracted;
            speed_control_subtracted = global_variables.speed_control - (127-12);
            global_variables.how_many_128 = (uint8_t)(speed_control_subtracted >> 7); //divide by 128, i.e. return how many 128s go into the speed_control
            global_variables.raw_TMR0 = (uint8_t)(speed_control_subtracted - (uint16_t)(global_variables.how_many_128 << 7)); //how_many_128*128, set TMR0
            //biggest how_many_128 for NUMBER_OF_FREQUENCY_STEPS == 600 is 3
            //biggest base_prescaler_bits_index == 5 for NUMBER_OF_FREQUENCY_STEPS == 600
            global_variables.TMR0_base_prescaler_bits_index = (uint8_t)(global_variables.how_many_128 + 2);   
        }
    return 1;
}


uint8_t adjust_and_set_TMR0_prescaler(void){
    
    if(global_variables.TMR0_prescaler_adjust == DIVIDE_BY_TWO){
        global_variables.TMR0_prescaler_final_index = global_variables.TMR0_base_prescaler_bits_index + 1;
    }
    else if(global_variables.TMR0_prescaler_adjust == DIVIDE_BY_FOUR){
        global_variables.TMR0_prescaler_final_index = global_variables.TMR0_base_prescaler_bits_index + 2;
    }
    else if(global_variables.TMR0_prescaler_adjust == MULTIPLY_BY_TWO){
        global_variables.TMR0_prescaler_final_index = global_variables.TMR0_base_prescaler_bits_index - 1;
    }
    else if(global_variables.TMR0_prescaler_adjust == DO_NOTHING){
        global_variables.TMR0_prescaler_final_index = global_variables.TMR0_base_prescaler_bits_index;
    }
    T0CON1bits.CKPS = global_variables.TMR0_prescaler_bits[global_variables.TMR0_prescaler_final_index];
    return 1;
}


#if SYMMETRY_ON_OR_OFF == 1

    uint8_t shorten_period(void){
        #if SYMMETRY_ADC_RESOLUTION == 8
            uint32_t twofiftysix_minus_TMR0_final = (((256-raw_TMR0)*(SHORTEN_POWER_OF_TWO_CONSTANT_8_BIT_SYM+(24*current_symmetry)))>>SHORTEN_POWER_OF_TWO_DIVISOR_8_BIT_SYM);
        #endif
        #if SYMMETRY_ADC_RESOLUTION == 10
            uint32_t twofiftysix_minus_TMR0_final = (((256-raw_TMR0)*(SHORTEN_POWER_OF_TWO_CONSTANT_10_BIT_SYM+(24*current_symmetry)))>>SHORTEN_POWER_OF_TWO_DIVISOR_10_BIT_SYM);
        #endif

        final_TMR0 = (256-twofiftysix_minus_TMR0_final);
        TMR0_prescaler_adjust = DO_NOTHING;
        return 1;
    }   

    uint8_t lengthen_period(void){
        #if SYMMETRY_ADC_RESOLUTION == 8
            uint32_t twofiftysix_minus_TMR0_final = (((256-raw_TMR0)*(LENGTHEN_CONSTANT_8_BIT_SYM-(3*current_symmetry)))>>LENGTHEN_POWER_OF_TWO_DIVISOR_8_BIT_SYM);
        #endif
        #if SYMMETRY_ADC_RESOLUTION == 10
            uint32_t twofiftysix_minus_TMR0_final = (((256-raw_TMR0)*(LENGTHEN_CONSTANT_10_BIT_SYM-(3*current_symmetry)))>>LENGTHEN_POWER_OF_TWO_DIVISOR_10_BIT_SYM);
        #endif

        if(twofiftysix_minus_TMR0_final > 256){
            twofiftysix_minus_TMR0_final = (twofiftysix_minus_TMR0_final >> 1);
            final_TMR0 = (256-twofiftysix_minus_TMR0_final);
            TMR0_prescaler_adjust = MULTIPLY_BY_TWO;
        }
        else{
            final_TMR0 = 256-twofiftysix_minus_TMR0_final;
            TMR0_prescaler_adjust = DO_NOTHING;
        }
        return 1;
    }
#endif


uint8_t process_TMR0_and_prescaler_adjust(void){
    
    #if SYMMETRY_ON_OR_OFF == 1
        if(current_symmetry == SYMMETRY_ADC_HALF_SCALE){
            final_TMR0 = raw_TMR0;
            TMR0_prescaler_adjust = DO_NOTHING;
        }
        else{
            uint8_t symmetry_status = CCW;
            if(current_symmetry > SYMMETRY_ADC_HALF_SCALE){
                current_symmetry = SYMMETRY_ADC_FULL_SCALE - current_symmetry; //converts current_symmetry to 128 -> 0 range (same range as CCW regime, more or less)
                symmetry_status = CW;
            }
            if(current_halfcycle == FIRST_HALFCYCLE){
                if(symmetry_status == CCW){
                    shorten_period();
                }
                else{
                    lengthen_period();
                }
            }
            else if(current_halfcycle == SECOND_HALFCYCLE){
                if(symmetry_status == CW){
                    shorten_period();
                }
                else{
                    lengthen_period();
                }
            }
        }

        adjust_and_set_TMR0_prescaler();

        //Adjust TMR0 for 2 instruction tick delay on update (for low prescaler values)
        if(TMR0_prescaler_final_index == 8){//prescaler is 1:1
            final_TMR0 = final_TMR0 + 2; //(256-TMR0_final) needs to be 2 counts less
        }
        else if(TMR0_prescaler_final_index == 7){//prescaler is 2:1
            final_TMR0 = final_TMR0 + 1; //(256-TMR0_final) needs to be 1 counts less
        }

    #endif

    #if SYMMETRY_ON_OR_OFF == 0
        global_variables.final_TMR0 = global_variables.raw_TMR0;
        global_variables.TMR0_prescaler_adjust = DO_NOTHING;
        adjust_and_set_TMR0_prescaler();
    #endif

    return 1;
}