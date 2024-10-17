#ifndef CLOCK_H
#define	CLOCK_H

#include <xc.h>

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 64000000
#endif

/**
 * @ingroup clockdriver
 * @brief Initializes all the Internal Oscillator sources and the clock switch configurations. 
 * @param None.
 * @return None.
 */
void CLOCK_Initialize(void);

#endif
