#include "../dma1.h"
#include "../../../system_uC.h"

extern struct Global_Variables global_variables;

void (*DMA1_SCNTI_InterruptHandler)(void);

void (*DMA1_DCNTI_InterruptHandler)(void);

/**
 * @ingroup dma1
 * @brief Default interrupt handler for all interrupt events.
 * @param None.
 * @return None.
 */
void DMA1_DefaultInterruptHandler(void);

static uint8_t adres[2];

/**
  Section: DMA1 APIs
*/

void DMA1_Initialize(void)
{   
    
    //DMA Instance Selection : 0x0
    DMASELECT = 0x0;
    //Source Address : (uint24_t) &ADRESL
    DMAnSSA = (uint24_t) &ADRESL;
    //Destination Address : (uint16_t) &adres
    DMAnDSA = (uint16_t) &adres;
    //SSTP not cleared; SMODE incremented; SMR SFR; DSTP not cleared; DMODE incremented; 
    DMAnCON1 = 0x42;
    //Source Message Size : 2
    DMAnSSZ = 2;
    //Destination Message Size : 2
    DMAnDSZ = 2;
    //Start Trigger : SIRQ TMR3; 
    DMAnSIRQ = 0x24;
    //Abort Trigger : AIRQ HLVD; 
    DMAnAIRQ = 0x1;
	
    // Clear Destination Count Interrupt Flag bit
    PIR2bits.DMA1DCNTIF = 0; 
    // Clear Source Count Interrupt Flag bit
    PIR2bits.DMA1SCNTIF = 0; 
    // Clear Abort Interrupt Flag bit
    PIR2bits.DMA1AIF = 0; 
    // Clear Overrun Interrupt Flag bit
    PIR2bits.DMA1ORIF =0; 
    
    PIE2bits.DMA1DCNTIE = 1;
	DMA1_DCNTIInterruptHandlerSet(DMA1_DefaultInterruptHandler);
    PIE2bits.DMA1SCNTIE = 1;
    PIE2bits.DMA1AIE = 0;
    PIE2bits.DMA1ORIE = 0;
	
    //AIRQEN disabled; DGO not in progress; SIRQEN enabled; EN enabled; 
    DMAnCON0 = 0xC0;
	 
}

void DMA1_Enable(void)
{
    DMASELECT = 0x0;
    DMAnCON0bits.EN = 0x1;
}

void DMA1_Disable(void)
{
    DMASELECT = 0x0;
    DMAnCON0bits.EN = 0x0;
}

void DMA1_SourceRegionSelect(uint8_t region)
{
    DMASELECT = 0x0;
	DMAnCON1bits.SMR  = region;
}

void DMA1_SourceAddressSet(uint24_t address)
{
    DMASELECT = 0x0;
	DMAnSSA = address;
}

uint24_t DMA1_SourceAddressGet(void)
{
    DMASELECT = 0x0;
    return DMAnSSA;
}

void DMA1_DestinationAddressSet(uint16_t address)
{
    DMASELECT = 0x0;
	DMAnDSA = address;
}

uint16_t DMA1_DestinationAddressGet(void)
{
    DMASELECT = 0x0;
    return DMAnDSA;
}

void DMA1_SourceSizeSet(uint16_t size)
{
    DMASELECT = 0x0;
	DMAnSSZ= size;
}

uint16_t DMA1_SourceSizeGet(void)
{
    DMASELECT = 0x0;
    return DMAnSSZ;
}

void DMA1_DestinationSizeSet(uint16_t size)
{                     
    DMASELECT = 0x0;
	DMAnDSZ= size;
}

uint16_t DMA1_DestinationSizeGet(void)
{                     
    DMASELECT = 0x0;
    return DMAnDSZ;
}

uint24_t DMA1_SourcePointerGet(void)
{
    DMASELECT = 0x0;
	return DMAnSPTR;
}

uint16_t DMA1_DestinationPointerGet(void)
{
    DMASELECT = 0x0;
	return DMAnDPTR;
}

uint16_t DMA1_SourceCountGet(void)
{
    DMASELECT = 0x0;
    return DMAnSCNT;
}

uint16_t DMA1_DestinationCountGet(void)
{                     
    DMASELECT = 0x0;
    return DMAnDCNT;
}

void DMA1_StartTriggerSet(uint8_t sirq)
{
    DMASELECT = 0x0;
	DMAnSIRQ = sirq;
}

void DMA1_AbortTriggerSet(uint8_t airq)
{
    DMASELECT = 0x0;
	DMAnAIRQ = airq;
}

void DMA1_TransferStart(void)
{
    DMASELECT = 0x0;
	DMAnCON0bits.DGO = 1;
}

void DMA1_TransferWithTriggerStart(void)
{
    DMASELECT = 0x0;
	DMAnCON0bits.SIRQEN = 1;
}

void DMA1_TransferStop(void)
{
    DMASELECT = 0x0;
	DMAnCON0bits.SIRQEN = 0; 
	DMAnCON0bits.DGO = 0;
}

void DMA1_DMAPrioritySet(uint8_t priority)
{
    uint8_t GIESaveState = INTCON0bits.GIE;
    INTCON0bits.GIE = 0;
	PRLOCK = 0x55;
	PRLOCK = 0xAA;
	PRLOCKbits.PRLOCKED = 0;
	DMA1PR = priority;
	PRLOCK = 0x55;
	PRLOCK = 0xAA;
	PRLOCKbits.PRLOCKED = 1;
    INTCON0bits.GIE = GIESaveState;
}

void DMA1_DMASCNTI_ISR(void)
{
    // Clear the source count interrupt flag
    PIR2bits.DMA1SCNTIF = 0;

    if (DMA1_SCNTI_InterruptHandler)
            DMA1_SCNTI_InterruptHandler();
}

void DMA1_SCNTIInterruptHandlerSet(void (* InterruptHandler)(void))
{
	 DMA1_SCNTI_InterruptHandler = InterruptHandler;
}

void DMA1_DMADCNTI_ISR(void)
{
    // Clear the source count interrupt flag
    PIR2bits.DMA1DCNTIF = 0;

    if (DMA1_DCNTI_InterruptHandler)
            DMA1_DCNTI_InterruptHandler();
}

void DMA1_SetDCNTIInterruptHandler(void (* InterruptHandler)(void))
{
	 DMA1_DCNTI_InterruptHandler = InterruptHandler;
}

void DMA1_DefaultInterruptHandler(void){
    // add your DMA1 interrupt custom code
    // or set custom function using DMA1_SCNTIInterruptHandlerSet() /DMA1_DCNTIInterruptHandlerSet() /DMA1_AIInterruptHandlerSet() /DMA1_ORIInterruptHandlerSet()
    
    //LATC4 = 0;
    
    PIE2bits.DMA1DCNTIE = 0;
    PIE4bits.TMR3IE = 0;
    
    uint16_t ADC_result; //concatenated ADC result
    ADC_result = (uint16_t)adres[0] | ((uint16_t)adres[1] << 8);
    ADC_result = TWELVEBITMINUSONE - ADC_result;
    
    
    switch(**global_variables.current_dma_type_ptr){
        
        case 0x10: //waveshape_adc_config_value
            
            if(ADC_result <= TRIANGLE_MODE_ADC_THRESHOLD){
                global_variables.current_waveshape = TRIANGLE_MODE; //triangle wave
            }
            else if (ADC_result <= SINE_MODE_ADC_THRESHOLD){
                global_variables.current_waveshape = SINE_MODE; //sine wave
            }
            else if (ADC_result <= SQUARE_MODE_ADC_THRESHOLD){
                global_variables.current_waveshape = SQUARE_MODE; //square wave
            }
            else{
                global_variables.current_waveshape = SINE_MODE; //if error, return sine
            }
            global_variables.current_dma_type_ptr++;
            break;
        
        case 0x11: //speed_adc_config_value
            
            global_variables.current_speed_linear = ADC_result;
            global_variables.current_speed_linear = global_variables.current_speed_linear >> 2; //convert to 10-bit
            global_variables.current_dma_type_ptr++;
            break;
            
        case 0x12: //depth_adc_config_value
            
            global_variables.current_depth = ADC_result;
            global_variables.current_depth = global_variables.current_depth >> 4; //convert to 8-bit
            global_variables.current_dma_type_ptr++;
            break;
        
        case 0x13: //symmetry_adc_config_value
            
            global_variables.current_symmetry = ADC_result;
            global_variables.current_symmetry = global_variables.current_symmetry >> 4; //convert to 8-bit
            global_variables.current_dma_type_ptr = &global_variables.dma_type_array[0];
            break;
        
        default:
            
            break;
    }
    
    TMR1_Write(TMR1_OVERFLOW_COUNT);
    TMR1_Start(); //ADCC is triggered on overflow
    
    PIE3bits.TMR1IE = 1;

    //LATC5 = 1;
}
/**
 End of File
*/
