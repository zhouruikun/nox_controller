
#define  TimerFunc_globals
#include "stm32f10x.h"
#include "datatype.h"
#include "timer.h"
#include "usart1.h"
#include "timerfunc.h"
#include "led.h"
#include "key.h"
//���1����һ��
void timer_1s_cousor(void)
{   
    cousor_count++;
    if(cousor_count>=6)
    {
         //beibuang=0;//��
         timer_b=1;
    } 
    if(cousor_count>=11)
    {
         cousor_count=0;
         timer_b=0;
         //beibuang=1;//��
    } 
}
//����30���
void timer_30s_brightness(void)
{

    brightness_count++;
    if(brightness_count>300)//30��
    {
        brightness_count=0;
        brightness_off;
    }
}
//���ڽ�����ɺ�����ʱ25MS
void timer_rev1(void)
{
    TimerRx1Count++;
    if(Rx1InterruptFlag==1)//���봮���жϺ󣬻�Զ�ʱ�������㣬ֱ��û�н����ж�ʱ�����濪ʼ��ʱ20MS
    {
        if(TimerRx1Count>=25)//��ʱ20MS
        {
            TimerRx1Count=0;//��ʱ����                    
            RX_Mark1=1;//���ս�����־
            Rx1InterruptFlag=0;//�����жϱ�־λ
        }
    }	
}

//����1Msɨ��һ��
void key_timer(void)
{
    key_timer_count++;
    if(key_timer_count>=10)//1MSɨ��һ��
    {
        key_flag=1;
        key_timer_count=0;
        
    }       
    
}