#include "stm32f10x.h"
#include "led.h"

   

//��ʼ��PA8��PD2Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��


void LED1_Init(void)//PB,GPIO_Pin_5,Out_P
{
    DK_GPIO_Init(PB,GPIO_Pin_5,Out_PP); //�������

}
 
void led1_H(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_5);
}

void led1_L(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_5);
}
