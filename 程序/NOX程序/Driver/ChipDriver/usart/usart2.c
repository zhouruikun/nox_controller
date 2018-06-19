#define USART2_globals
#include "stm32f10x.h"
#include "datatype.h"
#include "BitReadWrite.h"
#include "usart2.h"
#include "DMA.h"
#include "led.h"
/**
  * @brief  开启GPIOB,串口1时钟 
  * @param  None
  * @retval None
  * @note  对于某些GPIO上的默认复用功能可以不开启服用时钟，如果用到复用功能的重
           映射，则需要开启复用时钟
  */



void rts2485init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;        //定义GPIO初始化结构体

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能PB.5端口时钟

    /* Configure PE.0,PE.1,PE.2,PE.3,PE.4,PE.5,P.6,PE.7 as Output push-pull */ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11  ; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出 
    GPIO_Init(GPIOC, &GPIO_InitStructure); 
}

void Rts2485(u8 bit)
{
    if(bit==0)
    {
        PCout(11)=0;
    }
    else
    {
        PCout(11)=1;
    }
    
}


void USART2_RCC_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);//开复用时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//串口配制时钟为36MHZ
	 
}

/**
  * @brief  设置串口2发送与接收引脚的模式 
  * @param  None
  * @retval None
  */
void USART2_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

 
}

/**
  * @brief  初始化串口2接收中断 
  * @param  None
  * @retval None
  */
/*******************************************************************************
* Function Name   : NVIC_Configuration
* Description        : Configures NVIC and Vector Table base location.
* Input                    : None
* Output                 : None
* Return                 : None
*******************************************************************************/
void USART2_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Set the Vector Table base location at 0x08000000 */
    //对FLASH，该参数值必须高于0x08000100；对RAM必须高于0x100。它
    //同时必须是256（64×4）的整数倍
    //NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

    /* Configure the NVIC Preemption Priority Bits */  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//设置优先级分组：先占优先级和从优先级

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE); //使能空闲中断
    USART_ITConfig(USART2, USART_IT_TC, ENABLE); //使能发送完成中断//////
}


/**
  * @brief  配置串口1，并使能串口1，使能串口1接收中断  
  * @param  None
  * @retval None
  */
void Usart2_Configuration(u32 baud,u16 UsartParity)
{
    USART_InitTypeDef USART_InitStruct;

    USART2_RCC_Configuration();
    //配置串口参数
    USART_InitStruct.USART_BaudRate = baud;//115200
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_Parity = UsartParity; //USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    //初始化串口
    USART_Init(USART2, &USART_InitStruct);
    //使能串口
    USART_Cmd(USART2, ENABLE);
    //配置串口中断向量表及接收中断使能
    USART2_NVIC_Configuration();
    //配置串口接收发送引脚
    USART2_GPIO_Configuration();
    //初始化串口接收超时控制定时器
    //USART1_Timer3_Config();
    //初始化串口接收超时定时器中断
    //USART1_Timer3_Interrupts_Config();
    /* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
    如下语句解决第1个字节无法正确发送出去的问题 */
    USART_ClearFlag(USART2, USART_FLAG_TC);	  //清除发送完成标志
  //  rts2485init();
 //   Rts2485(0);
    RX_Mark2=0;
    Rx2InterruptFlag=0;
    TimerRx2Count=0;
	
}
/*******************************************************************/
/*                                                                 */
/* STM32向串口2发送1字节                                           */
/*                                                                 */
/*                                                                 */
/*******************************************************************/
/*
void Uart2_PutChar(u8 ch)
{
  USART_SendData(USART2, (u8) ch);
  while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}
*/
/*******************************************************************/
/*                                                                 */
/* STM32在串口1接收1字节                                           */
/* 说明：串口1接收中断                                             */
/*                                                                 */
/*******************************************************************/
/*
 * 函数名：USART2_IRQHandler
 * 描述  ：串口2中断函数
 * 输入  : 
 * 输出  ：无
 */
void USART2_IRQHandler(void)
{
    uint16 i;
    if(USART_GetITStatus(USART2,USART_IT_IDLE)!=RESET)	//空闲中断
    {
         // USART_ClearITPendingBit(USART2, USART_IT_IDLE);
        //读SR后读DR清除Idle
        i = USART2->SR;
        i = USART2->DR;
        i=i;
        RX_Mark2=0;
        Rx2InterruptFlag=1;
        TimerRx2Count=0;                             
    }
    if(USART_GetITStatus(USART2, USART_IT_PE | USART_IT_FE | USART_IT_NE) != RESET)//出错
    {
        USART_ClearITPendingBit(USART2, USART_IT_PE | USART_IT_FE | USART_IT_NE);  //清除错误中断
    }
   // LED0=1;
    
    if(USART_GetITStatus(USART2,USART_IT_TC)!=RESET)
    {
        
        Rts2485(0);
        //USART_ClearITPendingBit(USART2, USART_IT_TXE);
        USART_ClearITPendingBit(USART2, USART_IT_TC);	   //清楚传输完成中断
        //USART_ITConfig(USART2, USART_IT_TC, DISABLE);
    }
   	       
}

/*********************************END OF FILE**********************************/


