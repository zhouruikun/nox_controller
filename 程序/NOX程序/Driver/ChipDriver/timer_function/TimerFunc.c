
#define  TimerFunc_globals
#include "stm32f10x.h"
#include "datatype.h"
#include "timer.h"
#include "usart1.h"
#include "timerfunc.h"
#include "led.h"
#include "key.h"
//光标1秒闪一次
void timer_1s_cousor(void)
{   
    cousor_count++;
    if(cousor_count>=6)
    {
         //beibuang=0;//关
         timer_b=1;
    } 
    if(cousor_count>=11)
    {
         cousor_count=0;
         timer_b=0;
         //beibuang=1;//关
    } 
}
//背光30秒关
void timer_30s_brightness(void)
{

    brightness_count++;
    if(brightness_count>300)//30秒
    {
        brightness_count=0;
        brightness_off;
    }
}
//串口接收完成后再延时25MS
void timer_rev1(void)
{
    TimerRx1Count++;
    if(Rx1InterruptFlag==1)//进入串口中断后，会对定时计数清零，直到没有接收中断时，下面开始定时20MS
    {
        if(TimerRx1Count>=25)//定时20MS
        {
            TimerRx1Count=0;//定时计数                    
            RX_Mark1=1;//接收结束标志
            Rx1InterruptFlag=0;//接收中断标志位
        }
    }	
}

//按键1Ms扫描一次
void key_timer(void)
{
    key_timer_count++;
    if(key_timer_count>=10)//1MS扫描一次
    {
        key_flag=1;
        key_timer_count=0;
        
    }       
    
}