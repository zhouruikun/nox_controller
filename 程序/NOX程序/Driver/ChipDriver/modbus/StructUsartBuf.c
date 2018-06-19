
#define StructUsartBuf_globals
#include "stm32f10x.h"
#include "datatype.h"
#include "StructUsartBuf.h"
#include "usart1.h"
#include "usart2.h"
#include "DMA.h"


uint8 *get_inbuf(com_obj *com)
{
    return &com->rxbuf[0];
    
}
uint8 *get_outbuf(com_obj *com)
{
    
    return &com->txbuf[0];
    
}

uint8 get_end_rec(uint8 channel)
{
    uint8 temp;
    if(channel==1)
    {
        if(RX_Mark1==1)
        {
            //Rts1485(1);
            RX_Mark1=0;
            temp=1;
        }  
        else
        {
            temp=0;
        }
    }
    else if(channel==2)
    {
        if(RX_Mark2==1)
        {
            //Rts2485(1);
            RX_Mark2=0;
            temp=1;
        }
        else
        {
            temp=0;
        }
    }
    return temp;   
}
