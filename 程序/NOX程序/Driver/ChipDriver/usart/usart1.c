/**
  ******************************************************************************
  * @file    usart.c
  * $Author: wdluo $
  * $Revision: 17 $
  * $Date:: 2012-07-06 11:16:48 +0800 #$
  * @brief   串口相关函数。
  ******************************************************************************
  * @attention
  *
  *<h3><center>&copy; Copyright 2009-2012, ViewTool</center>
  *<center><a href="http:\\www.viewtool.com">http://www.viewtool.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#define USART1_globals
#include "stm32f10x.h"
#include "datatype.h"
#include "BitReadWrite.h"
#include "usart1.h"
#include "dma.h"
#include "led.h"
//#include "fsmc.h"
//#include "delay.h"
/* Private functions ---------------------------------------------------------*/


void rts1485init(void)
{
    
    DK_GPIO_Init(PA,GPIO_Pin_11,Out_PP); //推挽输出
}

void Rts1485(u8 bit)
{
    if(bit==0)
    {
        PAout(11)=0;
    }
    else
    {
        PAout(11)=1;
    }
    
}
/* Private typedef -----------------------------------------------------------*/

/**
  * @brief  开启GPIOA,串口1时钟 
  * @param  None
  * @retval None
  * @note  对于某些GPIO上的默认复用功能可以不开启服用时钟，如果用到复用功能的重
           映射，则需要开启复用时钟
  */
void USART1_RCC_Configuration(void)
{
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//开复用时钟
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    //GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);//串口配制时钟为72MHZ
}



/**
  * @brief  设置串口1发送与接收引脚的模式 
  * @param  None
  * @retval None
  */
void USART1_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}


/**
  * @brief  初始化串口1接收中断 
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
void USART1_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Set the Vector Table base location at 0x08000000 */
    //对FLASH，该参数值必须高于0x08000100；对RAM必须高于0x100。它
    //同时必须是256（64×4）的整数倍
    //NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

    /* Configure the NVIC Preemption Priority Bits */  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//设置优先级分组：先占优先级和从优先级

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); /*接收中断使能*/
    USART_ITConfig(USART1, USART_IT_TC, ENABLE);//使能发送完成中断 ///////
}




/**
  * @brief  配置串口1，并使能串口1，使能串口1接收中断  
  * @param  None
  * @retval None
  */
void Usart1_Configuration(u32 baud,u16 UsartParity)
{
    USART_InitTypeDef USART_InitStruct;

    USART1_RCC_Configuration();
    //配置串口参数
    USART_InitStruct.USART_BaudRate = baud;//115200
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;//此处在有奇偶校验时需要9个数据位，无奇偶校验时8个
    USART_InitStruct.USART_Parity = UsartParity;//USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    //初始化串口
    USART_Init(USART1, &USART_InitStruct);
    //使能串口
    USART_Cmd(USART1, ENABLE);
    //配置串口中断向量表及接收中断使能
    USART1_NVIC_Configuration();
    //配置串口接收发送引脚
    USART1_GPIO_Configuration();
    USART_ClearFlag(USART1, USART_FLAG_TC);     /* 清发送完成标志，Transmission Complete flag */
//    //初始化串口接收超时控制定时器
//    rts1485init();
//    Rts1485(0);
    RX_Mark1=0;
    Rx1InterruptFlag=0;
    TimerRx1Count=0;

}



/*******************************************************************/
/*                                                                 */
/* STM32向串口1发送1串                                           */
/*                                                                 */
/*                                                                 */
/*******************************************************************/
/*
void Uart1_PutCharString(u8 *ptr,u8 num)
{
    u8 i;
    Rts1485(1);   
    for(i=0;i<num;i++)
    {
        USART_SendData(USART1, (u8) *(ptr+i));
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        //TimerTxCount=0;//定时发送计数
        //TxInterruptFlag=1;//发送中断标志
        //TxCount=0;//发送个数
    }
    delay_ms(1);
    Rts1485(0);
  
  
}
*/
/*******************************************************************/
/*                                                                 */
/* STM32向串口1发送1字节                                           */
/*                                                                 */
/*                                                                 */
/*******************************************************************/
/*
void Uart1_PutChar(u8 ch)
{
  USART_SendData(USART1, (u8) ch);
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

*/

/*******************************************************************/
/*                                                                 */
/* STM32在串口1接收1字节                                           */
/* 说明：串口1接收中断                                             */
/*                                                                 */
/*******************************************************************/
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

void USART1_IRQHandler(void)
{
   uint16 i;
    if(USART_GetITStatus(USART1,USART_IT_IDLE)!=RESET)	//空闲中断
    {
          //USART_ClearITPendingBit(USART2, USART_IT_IDLE);
        //读SR后读DR清除Idle
         i = USART1->SR;
         i = USART1->DR;
         i=i;
         RX_Mark1=0;
         Rx1InterruptFlag=1;
         TimerRx1Count=0;      
    }
    if(USART_GetITStatus(USART1, USART_IT_PE | USART_IT_FE | USART_IT_NE) != RESET)//出错
    {
        USART_ClearITPendingBit(USART1, USART_IT_PE | USART_IT_FE | USART_IT_NE);  //清除错误中断
    }
    
    if(USART_GetITStatus(USART1,USART_IT_TC)!=RESET)
    {
        //LED0=0;
        Rts1485(0);
        USART_ClearITPendingBit(USART1, USART_IT_TC);	   //清楚传输完成中断
        //USART_ITConfig(USART1, USART_IT_TC, DISABLE);
    }
    
    //USART_ClearITPendingBit(USART1, USART_IT_IDLE);

}





/*********************************END OF FILE**********************************/
