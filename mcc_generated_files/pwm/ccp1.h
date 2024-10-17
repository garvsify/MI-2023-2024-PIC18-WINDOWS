#ifndef PWM1_H
#define PWM1_H

#include <xc.h>
#include <stdbool.h>

#define PWM1_Initialize CCP1_Initialize
#define PWM1_LoadDutyValue CCP1_LoadDutyValue
#define PWM1_OutputStatusGet  CCP1_OutputStatusGet

 /**
 * @ingroup pwm1
 * @brief Initializes the CCP1 module. This is called only once before calling other CCP1 APIs.
 * @param None.
 * @return None.
 */
void CCP1_Initialize(void);
/**
 * @ingroup pwm1
 * @brief Loads the 16-bit duty cycle value.
 * @pre CCP1_Initialize() is already called.
 * @param dutyValue - 16-bit duty cycle value.
 * @return None.
 */
void CCP1_LoadDutyValue(uint16_t dutyValue);
/**
 * @ingroup pwm1
 * @brief Returns the PWM output status.
 * @pre CCP1_Initialize() is already called.
 * @param None.
 * @retval True - CCP1 PWM output is high
 * @retval False - CCP1 PWM output is low
 */
bool CCP1_OutputStatusGet(void);
#endif //PWM1_H
/**
 End of File
*/
