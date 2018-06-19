#include "stm32f10x.h"
#include "led.h"

   

//初始化PA8和PD2为输出口.并使能这两个口的时钟		    
//LED IO初始化


void LED1_Init(void)//PB,GPIO_Pin_5,Out_P
{
    DK_GPIO_Init(PB,GPIO_Pin_5,Out_PP); //推挽输出

}
 
void led1_H(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_5);
}

void led1_L(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_5);
}
