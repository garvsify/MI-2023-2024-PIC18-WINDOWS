#include <xc.h>
#include "../pins.h"

/*    RC0 -> Waveshape CV
    RC1 -> Speed CV
    RC2 -> Depth CV
    RC3 -> Symmetry CV
    RC4 -> NC
    RC5 -> ISR length measurement OUT
    RA0 -> ICSPDAT
    RA1 -> ICSPCLK
    RA2 -> PWM OUT
    RA3 -> MCLR
    RA4 -> NC
    RA5 -> NC
*/

#include "../pins.h"


void PIN_MANAGER_Initialize(void)
{
   /**
    LATx registers
    */
    LATA = 0x0;
    LATC = 0x0;
    /**
    ODx registers
    */
    ODCONA = 0x0;
    ODCONC = 0x0;

    /**
    TRISx registers
    */
    TRISA = 0x3B;
    TRISC = 0xF;

    /**
    ANSELx registers
    */
    ANSELA = 0x37;
    ANSELC = 0xF;

    /**
    WPUx registers
    */
    WPUA = 0x0;
    WPUC = 0x0;


    /**
    SLRCONx registers
    */
    SLRCONA = 0x37;
    SLRCONC = 0x3F;

    /**
    INLVLx registers
    */
    INLVLA = 0x3F;
    INLVLC = 0x3F;

   /**
    RxyI2C | RxyFEAT registers   
    */
    RC0I2C = 0x0;
    RC1I2C = 0x0;
    /**
    PPS registers
    */
    CCP1PPS = 0x2;  //RA2->CCP1:CCP1;
    RA2PPS = 0x09;  //RA2->CCP1:CCP1;

   /**
    IOCx registers 
    */
    IOCAP = 0x0;
    IOCAN = 0x0;
    IOCAF = 0x0;
    IOCCP = 0x0;
    IOCCN = 0x0;
    IOCCF = 0x0;


}
  
void PIN_MANAGER_IOC(void)
{
}
/**
 End of File
*/