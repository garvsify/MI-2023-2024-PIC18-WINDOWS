#ifndef TMR0_H
#define TMR0_H

#include <xc.h>
#include <stdint.h>
#include "../../system_uC.h"

extern struct Global_Variables global_variables; //compiler not happy with extern struct declaration even though it's in system_uC.h lol


/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_Initialize API
 */
#define Timer0_Initialize TMR0_Initialize

/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_Start API
 */
#define Timer0_Start TMR0_Start

/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_Stop API
 */
#define Timer0_Stop TMR0_Stop

/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_Read API
 */
#define Timer0_Read TMR0_Read

/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_Write API
 */
#define Timer0_Write TMR0_Write

/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_PeriodCountSet API
 */
#define Timer0_PeriodCountSet TMR0_PeriodCountSet

/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_OverflowISR API
 */
#define Timer0_OverflowISR TMR0_OverflowISR

/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_Reload API
 */
#define Timer0_Reload TMR0_Reload

/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_OverflowCallbackRegister API
 */
#define Timer0_OverflowCallbackRegister TMR0_OverflowCallbackRegister


/**
 @ingroup tmr0
 @struct TMR_INTERFACE
 @brief Declares an instance of TMR_INTERFACE for the Timer0 module
 */
extern const struct TMR_INTERFACE Timer0;

/**
 * @ingroup tmr0
 * @brief Initializes the Timer0 module.
 *        This routine must be called before any other Timer0 routines.
 * @param None.
 * @return None.
 */
void TMR0_Initialize(void);

/**
 * @ingroup tmr0
 * @brief Starts Timer0.
 * @pre Timer0 should be initialized with TMR0_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void TMR0_Start(void);

/**
 * @ingroup tmr0
 * @brief Stops Timer0.
 * @pre Timer0 should be initialized with TMR0_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void TMR0_Stop(void);

/**
 * @ingroup tmr0
 * @brief Reads the 8-bit from the TMR0L register.
 * @pre Timer0 should be initialized with TMR0_Initialize() before calling this API.
 * @param None.
 * @return 8-bit data from the TMR0L register.
 */
uint8_t TMR0_Read(void);

/**
 * @ingroup tmr0
 * @brief Writes the 8-bit value to the TMR0L register.
 * @pre Timer0 should be initialized with TMR0_Initialize() before calling this API.
 * @param timerVal - 8-bit value to be written to the TMR0L register.
 * @return None.
 */
void TMR0_Write(uint8_t timerVal);

/**
 * @ingroup tmr0
 * @brief Loads the 8-bit value to the TMR0H register.
 * @pre Timer0 should be initialized with TMR0_Initialize() before calling this API.
 * @param periodVal - 8-bit value written to the TMR0H register.
 * @return None.
 */
void TMR0_Reload(size_t periodVal);

/**
 * @ingroup tmr0
 * @brief Interrupt Service Routine (ISR) for Timer0 overflow interrupt.
 * @param None.
 * @return None.
 */
void TMR0_OverflowISR(void);

/**
 * @ingroup tmr0
 * @brief Setter function for Timer0 overflow callback.
 * @param CallbackHandler - Pointer to the custom callback.
 * @return None.
 */
 void TMR0_OverflowCallbackRegister(void (* CallbackHandler)(void));

 
 uint8_t multiply_duty_by_current_depth_and_divide_by_256(void);

/**
 * @}
 */
#endif //TMR0_H
