#include <xc.h>
#include "/Users/jamesgarvey/Documents/Git/MI-2023_2024-PIC18/system_uC.h"


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
    TRISC = 0x1F;

    /**
    ANSELx registers
    */
    ANSELA = 0x37;
    ANSELC = 0x1F;

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