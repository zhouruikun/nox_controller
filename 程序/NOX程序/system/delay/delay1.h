#ifndef __IAR_DELAY_H
#define __IAR_DELAY_H

#include <intrinsics.h>

#define   XTAL   3.6864   //可定义为你所用的晶振频率（单位Mhz） 


#define   delay_nus(x)   __delay_cycles ( (unsigned long)((x) * (XTAL))  ) 
#define   delay_nms(x)   __delay_cycles ( (unsigned long)((x) * (XTAL)*1000U) )
#define   delay_s(x)    __delay_cycles ( (unsigned long)((x) * (XTAL)*1000000U) )


#endif
