#define Gripper_Valve_globals
#include "Gripper_Valve.h"
#include "exti.h"
#include "pwm.h"
#include "gpio.h"
//��ɴ�����ų�ʼ��
void Valve_pin_init(void)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;        //����GPIO��ʼ���ṹ��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB.5�˿�ʱ��

    /* Configure PE.0,PE.1,PE.2,PE.3,PE.4,PE.5,P.6,PE.7 as Output push-pull */ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//������� 
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
    
}
//ת�����
void ValveOut(uint8 val)
{
    switch(val)
    {
    case 0:
        GPIO_ResetBits(GPIOB,GPIO_Pin_10);
        break;
    case 1:
        GPIO_SetBits(GPIOB,GPIO_Pin_10);
        break;
    }
    
}
void Gripper_pin_init(void)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;        //����GPIO��ʼ���ṹ��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB.5�˿�ʱ��

    /* Configure PE.0,PE.1,PE.2,PE.3,PE.4,PE.5,P.6,PE.7 as Output push-pull */ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//������� 
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
    
}
//��ɴ��A���
void Gripper1Out(uint8 val)
{
    switch(val)
    {
    case 0:
        GPIO_ResetBits(GPIOB,GPIO_Pin_12);
        break;
    case 1:
        GPIO_SetBits(GPIOB,GPIO_Pin_12);
        break;
    }
    
}

//��ɴ��B���
void Gripper2Out(uint8 val)
{
    switch(val)
    {
    case 0:
        GPIO_ResetBits(GPIOB,GPIO_Pin_13);
        break;
    case 1:
        GPIO_SetBits(GPIOB,GPIO_Pin_13);
        break;
    }
    
}

