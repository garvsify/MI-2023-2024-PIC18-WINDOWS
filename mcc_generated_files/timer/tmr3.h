/**
 * TMR3 Generated Driver API Header File
 *
 * @file tmr3.h
 *
 * @defgroup tmr3 TMR3
 *
 * @brief This file contains the API prototypes and other data types for the TMR3 driver.
 *
 * @version TMR3 Driver Version 3.1.4
*/
/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef TMR3_H
#define TMR3_H

#include <stdbool.h>
#include <stdint.h>
#include "timer_interface.h"


/**
 * @ingroup tmr3
 * @brief Defines the Custom Name for the \ref TMR3_Initialize API
 */
#define Timer3_Initialize TMR3_Initialize

/**
 * @ingroup tmr3
 * @brief Defines the Custom Name for the \ref TMR3_Start API
 */
#define Timer3_Start TMR3_Start

/**
 * @ingroup tmr3
 * @brief Defines the Custom Name for the \ref TMR3_Stop API
 */
#define Timer3_Stop TMR3_Stop

/**
 * @ingroup tmr3
 * @brief Defines the Custom Name for the \ref TMR3_Read API
 */
#define Timer3_Read TMR3_Read

/**
 * @ingroup tmr3
 * @brief Defines the Custom Name for the \ref TMR3_Write API
 */
#define Timer3_Write TMR3_Write

/**
 * @ingroup tmr3
 * @brief Defines the Custom Name for the \ref TMR3_PeriodCountSet API
 */
#define Timer3_PeriodCountSet TMR3_PeriodCountSet

/**
 * @ingroup tmr3
 * @brief Defines the Custom Name for the \ref TMR3_OverflowISR API
 */
#define Timer3_OverflowISR TMR3_OverflowISR

/**
 * @ingroup tmr3
 * @brief Defines the Custom Name for the \ref TMR3_Reload API
 */
#define Timer3_Reload TMR3_Reload

/**
 * @ingroup tmr3
 * @brief Defines the Custom Name for the \ref TMR3_GateCallbackRegister API
 */
#define Timer3_GateCallbackRegister TMR3_GateCallbackRegister

/**
 * @ingroup tmr3
 * @brief Defines the Custom Name for the \ref TMR3_GateISR API
 */
#define Timer3_GateISR TMR3_GateISR

/**
 * @ingroup tmr3
 * @brief Defines the Custom Name for the \ref TMR3_HasOverflowOccured API
 */
#define Timer3_HasOverflowOccured TMR3_HasOverflowOccured

/**
 * @ingroup tmr3
 * @brief Defines the Custom Name for the \ref TMR3_CheckGateValueStatus API
 */
#define Timer3_CheckGateValueStatus TMR3_CheckGateValueStatus

/**
 * @ingroup tmr3
 * @brief Defines the Custom Name for the \ref TMR3_StartSinglePulseAcquisition API
 */
#define Timer3_StartSinglePulseAcquisition TMR3_StartSinglePulseAcquisition

/**
 * @ingroup tmr3
 * @brief Defines the Custom Name for the \ref TMR3_OverflowCallbackRegister API
 */
#define Timer3_OverflowCallbackRegister TMR3_OverflowCallbackRegister

/**
 * @ingroup tmr3
 * @brief Defines the Custom Name for the \ref TMR3_Tasks API
 */
#define Timer3_Tasks TMR3_Tasks


/**
 * @ingroup tmr3
 * @struct TMR_INTERFACE
 * @brief This is an instance of TMR_INTERFACE for Timer module
 */
extern const struct TMR_INTERFACE Timer3;

/**
 * @ingroup tmr3
 * @brief Initializes the timer module.
 *        This routine must be called before any other timer routines.
 * @param None.
 * @return None.
 */
void TMR3_Initialize(void);

/**
 * @ingroup tmr3
 * @brief Starts the timer.
 * @pre The timer should be initialized with TMR3_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void TMR3_Start(void);

/**
 * @ingroup tmr3
 * @brief Stops the timer.
 * @pre The timer should be initialized with TMR3_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void TMR3_Stop(void);

/**
 * @ingroup tmr3
 * @brief Reads the 16-bit from the TMR3 register.
 *        The Timer should be initialized with TMR3_Initialize() before calling this API.
 * @param None.
 * @return uint16_t - 16-bit data from the TMR3 register.
 */
uint16_t TMR3_Read(void);

/**
 * @ingroup tmr3
 * @brief Writes the 16-bit value to the TMR3 register.
 * @pre The timer should be initialized with TMR3_Initialize() before calling this API.
 * @param size_t timerVal - 16-bit value written to the TMR3 register.
 * @return None.
 */
void TMR3_Write(size_t timerVal);

/**
 * @ingroup tmr3
 * @brief Loads the 8-bit value to the TMR3 register.
 * @pre The timer should be initialized with TMR3_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void TMR3_Reload(void);

/**
 * @ingroup tmr3
 * @brief Loads the 16-bit value to the timer3ReloadVal variable.
 * @param periodVal - 16-bit value. 
 * @return None.
 */
void TMR3_PeriodCountSet(size_t periodVal);

/**
 * @ingroup tmr3
 * @brief Starts the single pulse acquisition in TMR3 gate operation.
 * @pre This function must be used when the TMR3 gate is enabled.
 * @param None.
 * @return None.
 */
void TMR3_StartSinglePulseAcquisition(void);

/**
 * @ingroup tmr3
 * @brief Reads the TMR3 gate value and returns it.
 * @pre This function must be used when the TMR3 gate is enabled.
 * @param None.
 * @return uint8_t - Gate value status.
 */
uint8_t TMR3_CheckGateValueStatus(void);


/**
 * @ingroup tmr3
 * @brief Setter function for the Timer overflow callback.
 * @param void (* CallbackHandler)(void) - Pointer to the custom callback.
 * @return None.
 */
 void TMR3_OverflowCallbackRegister(void (* CallbackHandler)(void));

/**
 * @ingroup tmr3
 * @brief Performs the tasks to be executed on timer overflow event.
 * @param None.
 * @return None.
 */
void TMR3_Tasks(void);

/**
 * @ingroup tmr3
 * @brief Checks for the timer overflow flag when in Polling mode.
 * @param None.
 * @retval true  - Timer overflow has occured.
 * @retval false - Timer overflow has not occured.
 */
bool TMR3_HasOverflowOccured(void);

/**
 * @ingroup tmr3
 * @brief Timer Gate Interrupt Service Routine (ISR) called by the Interrupt Manager.
 * @param None.
 * @return None.
 */
void TMR3_GateISR(void);

/**
 * @ingroup tmr3
 * @brief Setter function for the Timer gate callback.
 * @param void (* CallbackHandler)(void) - Pointer to the custom callback.
 * @return None.
 */
 void TMR3_GateCallbackRegister(void (* CallbackHandler)(void));

#endif // TMR3_H