#define PinInputOutput_globals

#include "pininputoutput.h"

void Base11_init(void)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;        //定义GPIO初始化结构体

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB.5端口时钟

    /* Configure PE.0,PE.1,PE.2,PE.3,PE.4,PE.5,P.6,PE.7 as Output push-pull */ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3  ; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出 
    GPIO_Init(GPIOE, &GPIO_InitStructure); 
}

void Base11_Output(uint8 val)
{
    switch(val)
    {
    case 0:
        GPIO_ResetBits(GPIOE,GPIO_Pin_3);
        break;
    case 1:
        GPIO_SetBits(GPIOE,GPIO_Pin_3);
        break;
    }
}

void start1_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;        //定义GPIO初始化结构体

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB.5端口时钟

    /* Configure PE.0,PE.1,PE.2,PE.3,PE.4,PE.5,P.6,PE.7 as Output push-pull */ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2  ; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出 
    GPIO_Init(GPIOE, &GPIO_InitStructure); 
}
void set_start1(uint8 val)
{
    switch(val)
    {
    case 0:
        GPIO_ResetBits(GPIOE,GPIO_Pin_2);
        break;
    case 1:
        GPIO_SetBits(GPIOE,GPIO_Pin_2);
        break;
    }
    
}
//夹纱器引脚初始化
void Gripper_pin_init(void)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;        //定义GPIO初始化结构体

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //使能PB.5端口时钟

    /* Configure PE.0,PE.1,PE.2,PE.3,PE.4,PE.5,P.6,PE.7 as Output push-pull */ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出 
    GPIO_Init(GPIOD, &GPIO_InitStructure); 
    
}
//夹纱器A输出
void GripperOutA(uint8 val)
{
    switch(val)
    {
    case 0:
        GPIO_ResetBits(GPIOD,GPIO_Pin_8);
        break;
    case 1:
        GPIO_SetBits(GPIOD,GPIO_Pin_8);
        break;
    }
    
}
//夹纱器B输出
void GripperOutB(uint8 val)
{
    switch(val)
    {
    case 0:
        GPIO_ResetBits(GPIOD,GPIO_Pin_10);
        break;
    case 1:
        GPIO_SetBits(GPIOD,GPIO_Pin_10);
        break;
    }
    
}



