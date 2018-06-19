#define key_globals
#include "stm32f10x.h"
#include "datatype.h"
#include "BitReadWrite.h"
#include "timerfunc.h"
#include "key.h"
#include "led.h"
#include "delay.h"
#include "wdg.h"


#define key_col_bit     (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5\
                         |GPIO_Pin_6|GPIO_Pin_7)
					   
#define key_row_bit     (GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)					      



uint16 keyteb[25]={      0xA07F,//0
                         0x60EF,//1
                         0xA0EF,//2
                         0xC0EF,//3
                         0x60DF,//4
                         0xA0DF,//5
                         0xC0DF,//6
                         0x60BF,//7
                         0xA0BF,//8
                         0xC0BF,//9
                         0x607F,//.
                         0xC07F,//
                         0x60FE,//enter
                         0x60FD,//f1
                         0x60FB,//f2
                         0x60F7,//f3
			 0xA0FE,//<-
                         0xA0FB,//->
                         0xC0FD,//箭下
                         0xA0FD,//箭上
                         0xC0FE,//F4
                         0xC0FB,//esc
                         0xA0F7,//15
                         0xC0F7,//16
                         0x00};

void key_col_out(void) //IO初始化
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
    GPIO_InitStructure.GPIO_Pin = key_col_bit;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
		 
}
void key_col_in(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = key_col_bit;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void key_row_out(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = key_row_bit;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void key_row_in(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = key_row_bit;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void keyboard_init(void)//按键初始化
{
   key_flag=1;
   key_timer_count=0;
   key_col_out();
   key_row_out();
}


uint8 get_key(void)
{
    uint8 col;
    uint16  keycode=0xffff,row;
    uint8 keyval;
    uint16 const *kptr;
    key_row_in();
    key_col_out();
    GPIO_ResetBits(GPIOA,key_col_bit);
    row=GPIO_ReadInputData(GPIOB); 
    row=row & 0xE000;
    keyval=0xff;
    if(row!=0xE000)
    {
        row=GPIO_ReadInputData(GPIOB); 
        row=row & 0xE000;
        keyval=0xff;
        if(row!=0xE000)
        {
            key_row_out();
            key_col_in();
            GPIO_ResetBits(GPIOB,key_row_bit); 
            col=GPIO_ReadInputData(GPIOA); 
            //col=col & 0xff;
            if(col!=0xff)
            {
                col=GPIO_ReadInputData(GPIOA); 
               // col=col & 0xff;              
                key_row_in();
                keycode=row+col;
                keyval=0;
                kptr=&keyteb[0];
                while(*kptr!=0x00)
                {
                    if(keycode==*kptr)break;
                    keyval++;
                    kptr++;
                }
            }                        
        }
    }
    return keyval;
}

uint8 key_scan_wait(void)
{
    uint8 key=0xff,temp=0;
    do
    {
        if(key_flag==1)
        {
            key=get_key();
        }
        IWDG_Feed();	
    }
    while(key==0xff);
    if(key!=0xff)
    {
        key_flag=0; 
        key_timer_count=0;
        brightness_on;
        brightness_count=0;
        do
        {
            if(key_flag==1)
            {
                temp=get_key();
            }
            IWDG_Feed();
                    
        }
        while(temp!=0xff);//只有当按键放开的时候才会下去
    }
    return key;
}
uint8 key_scan_nowait(void)
{
    uint8 key=0xff,temp=0;
    if(key_flag==1)
    {
        key=get_key();
    }
    IWDG_Feed();
    if(key!=0xff)
    {
        key_flag=0; 
        key_timer_count=0;
        brightness_on;
        brightness_count=0;
        do
        {
            if(key_flag==1)
            {
                temp=get_key();
            }
            IWDG_Feed();
                    
        }
        while(temp!=0xff);//只有当按键放开的时候才会下去
    }
    return key;
}

