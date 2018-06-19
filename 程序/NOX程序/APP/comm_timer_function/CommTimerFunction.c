#define PinInputOutput_globals
#define CommTimerFunction_globals
#include "stm32f10x.h"
#include "datatype.h"
#include "CommTimerFunction.h"
//#include "led.h"
#include "timer.h"
#include "usart1.h"
#include "usart2.h"
#include "calculate_val.h"
//#include "adc.h"
//#include "dma.h"
//#include "PinInputOutput.h"
//#include "delay.h"
#include "para.h"

 #include "comm.h"
#include "usart1.h"
#include "usart2.h"
#include "StructUsartBuf.h"
/*
 * 函数名：timer_rev1
 * 描述  ：接收中断串口1定时函数
 * 输入  : 无
 * 输出  ：无
 */		

extern u16 temper1 ;
void timer_rev1(void)
{
    TimerRx1Count++;
    if(Rx1InterruptFlag==1)//进入串口中断后，会对定时计数清零，直到没有接收中断时，下面开始定时20MS
    {
        if(TimerRx1Count>=5)//定时20MS
        {
            TimerRx1Count=0;//定时计数                    
            RX_Mark1=1;//接收结束标志
            Rx1InterruptFlag=0;//接收中断标志位
        }
    }	
}

/*
 * 函数名：timer_rev2
 * 描述  ：接收中断串口2定时函数
 * 输入  : 无
 * 输出  ：无
 */																	 
void timer_rev2(void)
{
    TimerRx2Count++;
    if(Rx2InterruptFlag==1)//进入串口中断后，会对定时计数清零，直到没有接收中断时，下面开始定时20MS
    {
        if(TimerRx2Count>=5)//定时20MS
        {
            TimerRx2Count=0;//定时计数
            RX_Mark2=1;//接收结束标志
            Rx2InterruptFlag=0;//接收中断标志位
        }
    }	
}

void pressure_measurement_timer(void)
{
 
    pressure_timer_count++;
    if(pressure_timer_count>=samp_time)//一秒
    {   
        pressure_timer_count=0;//清计数器
        pressure_timer1s_flag=1;//1秒到置位
    }
}

/****************************************************************************************
author     : lqm_8
description:定时器0,modus发送帧间隔5MS
            end_send=0;//发送完成
version    :timer_send v1.0.0
date:      : 13/01/21
***************************************************************************************/
/*
void timer_send1(void)
{
    TimerTx1Count++;
    if(Tx1InterruptFlag==1)//进入串口中断后，会对定时计数清零，直到没有接收中断时，下面开始定时5MS
    {
        if(TimerTx1Count>=1)//5ms
        {
            TX_Mark1=1;//发送结束标志
            TimerTx1Count=0;//定时发送计数
            Tx1InterruptFlag=0;//发送中断标志
                
        }
    }

}
*/
/****************************************************************************************
author     : lqm_8
description:定时器0,modus发送帧间隔5MS
            end_send=0;//发送完成
version    :timer_send v1.0.0
date:      : 13/01/21
***************************************************************************************/
/*
void timer_send2(void)
{
    TimerTx2Count++;
    if(Tx2InterruptFlag==1)//进入串口中断后，会对定时计数清零，直到没有接收中断时，下面开始定时5MS
    {
        if(TimerTx2Count>=800)//5ms
        {
           // TX_Mark2=1;//发送结束标志
            TimerTx2Count=0;//定时发送计数
            Tx2InterruptFlag=0;//发送中断标志
            //Rts1485(0);
                
        }
      
    }
     

}
*/












