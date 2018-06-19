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
 * ��������timer_rev1
 * ����  �������жϴ���1��ʱ����
 * ����  : ��
 * ���  ����
 */		

extern u16 temper1 ;
void timer_rev1(void)
{
    TimerRx1Count++;
    if(Rx1InterruptFlag==1)//���봮���жϺ󣬻�Զ�ʱ�������㣬ֱ��û�н����ж�ʱ�����濪ʼ��ʱ20MS
    {
        if(TimerRx1Count>=5)//��ʱ20MS
        {
            TimerRx1Count=0;//��ʱ����                    
            RX_Mark1=1;//���ս�����־
            Rx1InterruptFlag=0;//�����жϱ�־λ
        }
    }	
}

/*
 * ��������timer_rev2
 * ����  �������жϴ���2��ʱ����
 * ����  : ��
 * ���  ����
 */																	 
void timer_rev2(void)
{
    TimerRx2Count++;
    if(Rx2InterruptFlag==1)//���봮���жϺ󣬻�Զ�ʱ�������㣬ֱ��û�н����ж�ʱ�����濪ʼ��ʱ20MS
    {
        if(TimerRx2Count>=5)//��ʱ20MS
        {
            TimerRx2Count=0;//��ʱ����
            RX_Mark2=1;//���ս�����־
            Rx2InterruptFlag=0;//�����жϱ�־λ
        }
    }	
}

void pressure_measurement_timer(void)
{
 
    pressure_timer_count++;
    if(pressure_timer_count>=samp_time)//һ��
    {   
        pressure_timer_count=0;//�������
        pressure_timer1s_flag=1;//1�뵽��λ
    }
}

/****************************************************************************************
author     : lqm_8
description:��ʱ��0,modus����֡���5MS
            end_send=0;//�������
version    :timer_send v1.0.0
date:      : 13/01/21
***************************************************************************************/
/*
void timer_send1(void)
{
    TimerTx1Count++;
    if(Tx1InterruptFlag==1)//���봮���жϺ󣬻�Զ�ʱ�������㣬ֱ��û�н����ж�ʱ�����濪ʼ��ʱ5MS
    {
        if(TimerTx1Count>=1)//5ms
        {
            TX_Mark1=1;//���ͽ�����־
            TimerTx1Count=0;//��ʱ���ͼ���
            Tx1InterruptFlag=0;//�����жϱ�־
                
        }
    }

}
*/
/****************************************************************************************
author     : lqm_8
description:��ʱ��0,modus����֡���5MS
            end_send=0;//�������
version    :timer_send v1.0.0
date:      : 13/01/21
***************************************************************************************/
/*
void timer_send2(void)
{
    TimerTx2Count++;
    if(Tx2InterruptFlag==1)//���봮���жϺ󣬻�Զ�ʱ�������㣬ֱ��û�н����ж�ʱ�����濪ʼ��ʱ5MS
    {
        if(TimerTx2Count>=800)//5ms
        {
           // TX_Mark2=1;//���ͽ�����־
            TimerTx2Count=0;//��ʱ���ͼ���
            Tx2InterruptFlag=0;//�����жϱ�־
            //Rts1485(0);
                
        }
      
    }
     

}
*/












