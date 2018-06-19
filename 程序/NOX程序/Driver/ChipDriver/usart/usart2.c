#define USART2_globals
#include "stm32f10x.h"
#include "datatype.h"
#include "BitReadWrite.h"
#include "usart2.h"
#include "DMA.h"
#include "led.h"
/**
  * @brief  ����GPIOB,����1ʱ�� 
  * @param  None
  * @retval None
  * @note  ����ĳЩGPIO�ϵ�Ĭ�ϸ��ù��ܿ��Բ���������ʱ�ӣ�����õ����ù��ܵ���
           ӳ�䣬����Ҫ��������ʱ��
  */



void rts2485init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;        //����GPIO��ʼ���ṹ��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //ʹ��PB.5�˿�ʱ��

    /* Configure PE.0,PE.1,PE.2,PE.3,PE.4,PE.5,P.6,PE.7 as Output push-pull */ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11  ; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//������� 
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);//������ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//��������ʱ��Ϊ36MHZ
	 
}

/**
  * @brief  ���ô���2������������ŵ�ģʽ 
  * @param  None
  * @retval None
  */
void USART2_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

 
}

/**
  * @brief  ��ʼ������2�����ж� 
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
    //��FLASH���ò���ֵ�������0x08000100����RAM�������0x100����
    //ͬʱ������256��64��4����������
    //NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

    /* Configure the NVIC Preemption Priority Bits */  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//�������ȼ����飺��ռ���ȼ��ʹ����ȼ�

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE); //ʹ�ܿ����ж�
    USART_ITConfig(USART2, USART_IT_TC, ENABLE); //ʹ�ܷ�������ж�//////
}


/**
  * @brief  ���ô���1����ʹ�ܴ���1��ʹ�ܴ���1�����ж�  
  * @param  None
  * @retval None
  */
void Usart2_Configuration(u32 baud,u16 UsartParity)
{
    USART_InitTypeDef USART_InitStruct;

    USART2_RCC_Configuration();
    //���ô��ڲ���
    USART_InitStruct.USART_BaudRate = baud;//115200
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_Parity = UsartParity; //USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    //��ʼ������
    USART_Init(USART2, &USART_InitStruct);
    //ʹ�ܴ���
    USART_Cmd(USART2, ENABLE);
    //���ô����ж������������ж�ʹ��
    USART2_NVIC_Configuration();
    //���ô��ڽ��շ�������
    USART2_GPIO_Configuration();
    //��ʼ�����ڽ��ճ�ʱ���ƶ�ʱ��
    //USART1_Timer3_Config();
    //��ʼ�����ڽ��ճ�ʱ��ʱ���ж�
    //USART1_Timer3_Interrupts_Config();
    /* CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
    �����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
    USART_ClearFlag(USART2, USART_FLAG_TC);	  //���������ɱ�־
  //  rts2485init();
 //   Rts2485(0);
    RX_Mark2=0;
    Rx2InterruptFlag=0;
    TimerRx2Count=0;
	
}
/*******************************************************************/
/*                                                                 */
/* STM32�򴮿�2����1�ֽ�                                           */
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
/* STM32�ڴ���1����1�ֽ�                                           */
/* ˵��������1�����ж�                                             */
/*                                                                 */
/*******************************************************************/
/*
 * ��������USART2_IRQHandler
 * ����  ������2�жϺ���
 * ����  : 
 * ���  ����
 */
void USART2_IRQHandler(void)
{
    uint16 i;
    if(USART_GetITStatus(USART2,USART_IT_IDLE)!=RESET)	//�����ж�
    {
         // USART_ClearITPendingBit(USART2, USART_IT_IDLE);
        //��SR���DR���Idle
        i = USART2->SR;
        i = USART2->DR;
        i=i;
        RX_Mark2=0;
        Rx2InterruptFlag=1;
        TimerRx2Count=0;                             
    }
    if(USART_GetITStatus(USART2, USART_IT_PE | USART_IT_FE | USART_IT_NE) != RESET)//����
    {
        USART_ClearITPendingBit(USART2, USART_IT_PE | USART_IT_FE | USART_IT_NE);  //��������ж�
    }
   // LED0=1;
    
    if(USART_GetITStatus(USART2,USART_IT_TC)!=RESET)
    {
        
        Rts2485(0);
        //USART_ClearITPendingBit(USART2, USART_IT_TXE);
        USART_ClearITPendingBit(USART2, USART_IT_TC);	   //�����������ж�
        //USART_ITConfig(USART2, USART_IT_TC, DISABLE);
    }
   	       
}

/*********************************END OF FILE**********************************/


