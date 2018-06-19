/**
  ******************************************************************************
  * @file    usart.c
  * $Author: wdluo $
  * $Revision: 17 $
  * $Date:: 2012-07-06 11:16:48 +0800 #$
  * @brief   ������غ�����
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
    
    DK_GPIO_Init(PA,GPIO_Pin_11,Out_PP); //�������
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
  * @brief  ����GPIOA,����1ʱ�� 
  * @param  None
  * @retval None
  * @note  ����ĳЩGPIO�ϵ�Ĭ�ϸ��ù��ܿ��Բ���������ʱ�ӣ�����õ����ù��ܵ���
           ӳ�䣬����Ҫ��������ʱ��
  */
void USART1_RCC_Configuration(void)
{
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//������ʱ��
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    //GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);//��������ʱ��Ϊ72MHZ
}



/**
  * @brief  ���ô���1������������ŵ�ģʽ 
  * @param  None
  * @retval None
  */
void USART1_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}


/**
  * @brief  ��ʼ������1�����ж� 
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
    //��FLASH���ò���ֵ�������0x08000100����RAM�������0x100����
    //ͬʱ������256��64��4����������
    //NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

    /* Configure the NVIC Preemption Priority Bits */  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//�������ȼ����飺��ռ���ȼ��ʹ����ȼ�

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); /*�����ж�ʹ��*/
    USART_ITConfig(USART1, USART_IT_TC, ENABLE);//ʹ�ܷ�������ж� ///////
}




/**
  * @brief  ���ô���1����ʹ�ܴ���1��ʹ�ܴ���1�����ж�  
  * @param  None
  * @retval None
  */
void Usart1_Configuration(u32 baud,u16 UsartParity)
{
    USART_InitTypeDef USART_InitStruct;

    USART1_RCC_Configuration();
    //���ô��ڲ���
    USART_InitStruct.USART_BaudRate = baud;//115200
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;//�˴�������żУ��ʱ��Ҫ9������λ������żУ��ʱ8��
    USART_InitStruct.USART_Parity = UsartParity;//USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    //��ʼ������
    USART_Init(USART1, &USART_InitStruct);
    //ʹ�ܴ���
    USART_Cmd(USART1, ENABLE);
    //���ô����ж������������ж�ʹ��
    USART1_NVIC_Configuration();
    //���ô��ڽ��շ�������
    USART1_GPIO_Configuration();
    USART_ClearFlag(USART1, USART_FLAG_TC);     /* �巢����ɱ�־��Transmission Complete flag */
//    //��ʼ�����ڽ��ճ�ʱ���ƶ�ʱ��
//    rts1485init();
//    Rts1485(0);
    RX_Mark1=0;
    Rx1InterruptFlag=0;
    TimerRx1Count=0;

}



/*******************************************************************/
/*                                                                 */
/* STM32�򴮿�1����1��                                           */
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
        //TimerTxCount=0;//��ʱ���ͼ���
        //TxInterruptFlag=1;//�����жϱ�־
        //TxCount=0;//���͸���
    }
    delay_ms(1);
    Rts1485(0);
  
  
}
*/
/*******************************************************************/
/*                                                                 */
/* STM32�򴮿�1����1�ֽ�                                           */
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
/* STM32�ڴ���1����1�ֽ�                                           */
/* ˵��������1�����ж�                                             */
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
    if(USART_GetITStatus(USART1,USART_IT_IDLE)!=RESET)	//�����ж�
    {
          //USART_ClearITPendingBit(USART2, USART_IT_IDLE);
        //��SR���DR���Idle
         i = USART1->SR;
         i = USART1->DR;
         i=i;
         RX_Mark1=0;
         Rx1InterruptFlag=1;
         TimerRx1Count=0;      
    }
    if(USART_GetITStatus(USART1, USART_IT_PE | USART_IT_FE | USART_IT_NE) != RESET)//����
    {
        USART_ClearITPendingBit(USART1, USART_IT_PE | USART_IT_FE | USART_IT_NE);  //��������ж�
    }
    
    if(USART_GetITStatus(USART1,USART_IT_TC)!=RESET)
    {
        //LED0=0;
        Rts1485(0);
        USART_ClearITPendingBit(USART1, USART_IT_TC);	   //�����������ж�
        //USART_ITConfig(USART1, USART_IT_TC, DISABLE);
    }
    
    //USART_ClearITPendingBit(USART1, USART_IT_IDLE);

}





/*********************************END OF FILE**********************************/
