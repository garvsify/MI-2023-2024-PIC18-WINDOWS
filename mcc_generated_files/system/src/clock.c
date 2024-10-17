#include <xc.h>
#include "../clock.h"

void CLOCK_Initialize(void)
{
    // Set the CLOCK CONTROL module to the options selected in the user interface.
    OSCCON1 = (0 << _OSCCON1_NDIV_POSN)   // NDIV 1
        | (6 << _OSCCON1_NOSC_POSN);  // NOSC HFINTOSC
    OSCCON3 = (0 << _OSCCON3_SOSCPWR_POSN)   // SOSCPWR Low power
        | (0 << _OSCCON3_CSWHOLD_POSN);  // CSWHOLD may proceed
    OSCEN = (0 << _OSCEN_EXTOEN_POSN)   // EXTOEN disabled
        | (0 << _OSCEN_HFOEN_POSN)   // HFOEN disabled
        | (0 << _OSCEN_MFOEN_POSN)   // MFOEN disabled
        | (0 << _OSCEN_LFOEN_POSN)   // LFOEN disabled
        | (0 << _OSCEN_SOSCEN_POSN)   // SOSCEN disabled
        | (0 << _OSCEN_ADOEN_POSN)   // ADOEN disabled
        | (0 << _OSCEN_PLLEN_POSN);  // PLLEN disabled
    OSCFRQ = (8 << _OSCFRQ_HFFRQ_POSN);  // HFFRQ 64_MHz
    OSCTUNE = (0 << _OSCTUNE_TUN_POSN);  // TUN 0x0
    ACTCON = (1 << _ACTCON_ACTEN_POSN)   // ACTEN enabled
        | (1 << _ACTCON_ACTUD_POSN);  // ACTUD disabled

}
/**
 End of File
*/