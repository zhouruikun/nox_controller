
#define DMA_globals
#include "stm32f10x.h"
#include "datatype.h"
#include "delay.h"
#include "DMA.h"
#include "usart1.h"
#include "usart2.h"
#include "StructUsartBuf.h"

#define USART1_DR_BASE    ((u32)0x40013804)
#define USART2_DR_BASE    ((u32)0x40004404)

/*
 * ��������Delay
 * ����  ����ʱ����
 * ����  : dly
 * ���  ����
 */	



void DMA1_RCC_Configuration(void)
{
    /* Enable DMA1 clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); 
}



void Uart1_DMA_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    DMA1_RCC_Configuration(); 
    
    //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�������ȼ����飺��ռ���ȼ��ʹ����ȼ�
	//Enable DMA Channel4 Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    
    /*Enable DMA Channel5 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    
}

void Uart2_DMA_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    DMA1_RCC_Configuration(); 
    //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�������ȼ����飺��ռ���ȼ��ʹ����ȼ�
/*Enable DMA Channel6 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
     //Enable DMA Channel7 Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
}    

/*
 * ��������USART1_DMA_RxConfig
 * ����  ��DMA1ͨ��5�������ú���
 * ����  : RxInitBuf1
 * ���  ����
 */	
void USART1_DMA_RxConfig(uint8 *RxInitBuf1)
{
   /* DMA1 Channel5 (triggered by USART1 Rx event) Config */
  DMA_InitTypeDef DMA_InitStructure;
  DMA_DeInit(DMA1_Channel5);  
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_BASE;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxInitBuf1;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 256;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel5, &DMA_InitStructure);
  
  DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
  DMA_ITConfig(DMA1_Channel5, DMA_IT_TE, ENABLE);
  
  /* Enable USART1 DMA RX request */
  USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
  
  DMA_Cmd(DMA1_Channel5, ENABLE);

}
/*
 * ��������USART1_DMA_TxConfig
 * ����  ��DMA1ͨ��4�������ú���
 * ����  : TxInitBuffer
 * ���  ����
 */	
void USART1_DMA_TxConfig(uint8 *TxInitBuf1)
{
   /* DMA1 Channel4 (triggered by USART1 Tx event) Config */
  DMA_InitTypeDef DMA_InitStructure;
  DMA_DeInit(DMA1_Channel4);  
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_BASE;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxInitBuf1;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 256;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
  
  DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
  DMA_ITConfig(DMA1_Channel4, DMA_IT_TE, ENABLE);
  /* Enable USART1 DMA TX request */
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
  
  DMA_Cmd(DMA1_Channel4, DISABLE);
  
}

/*
 * ��������USART2_DMA_RxConfig
 * ����  ��DMA1ͨ��6�������ú���
 * ����  : RxInitBuffer
 * ���  ����
 */	
void USART2_DMA_RxConfig(uint8 *RxInitBuf2)
{
  /* DMA channel6 configuration USART RX*/
  DMA_InitTypeDef DMA_InitStructure;
  DMA_DeInit(DMA1_Channel6);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)USART2_DR_BASE;  //���������ַ����2
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)RxInitBuf2;	  //���ô洢����ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;   //�����ַΪ�����Դ��ַ
  DMA_InitStructure.DMA_BufferSize = 256;	//���ݴ��䳤��
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ������
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	 //�洢����ַ����
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //�������ݿ�� 8λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//�洢�����ݿ��
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular	 //ѭ��ģʽ
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;  //�����ȼ�
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	//�ڴ浽�ڴ洫��ʧ��
  DMA_Init(DMA1_Channel6, &DMA_InitStructure);

  DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);  //��������ж�ʹ��
  DMA_ITConfig(DMA1_Channel6, DMA_IT_TE, ENABLE);  //��������ж�ʹ��
  USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE); //ʹ��USART2�Ľ���,����DMA����

  DMA_Cmd(DMA1_Channel6, ENABLE); //����DMA1ͨ��6
}

/*
 * ��������USART2_DMA_TxConfig
 * ����  ��DMA1ͨ��7�������ú���
 * ����  : TxInitBuffer
 * ���  ����
 */	

void USART2_DMA_TxConfig(uint8 *TxInitBuf2)
{
    /* DMA channel7 configuration USART TX*/
   DMA_InitTypeDef DMA_InitStructure;
   DMA_DeInit(DMA1_Channel7);
   DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)USART2_DR_BASE; //���������ַ����2
   DMA_InitStructure.DMA_MemoryBaseAddr = (u32)TxInitBuf2;	  //���ô洢����ַ
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;		 //�����ַΪ�����Ŀ�ĵ�ַ
   DMA_InitStructure.DMA_BufferSize = 256;		//���ݴ��䳤��
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	 //�����ַ������
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	   //�洢����ַ����
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //�������ݿ�� 8λ
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 	//�洢�����ݿ��
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA_Mode_Normal;  //ѭ��ģʽ
   DMA_InitStructure.DMA_Priority = DMA_Priority_High;	 //�����ȼ�
   DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	  //�ڴ浽�ڴ洫��ʧ��
   DMA_Init(DMA1_Channel7, &DMA_InitStructure);

   DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);  //��������ж�ʹ��
   DMA_ITConfig(DMA1_Channel7, DMA_IT_TE, ENABLE);	//��������ж�ʹ��
   USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);	//ʹ��USART2�ķ���,����DMA����
   DMA_Cmd(DMA1_Channel7, DISABLE);		//�ر�DMA1ͨ��7


}


void USART2_DMA_Config(uint8 *TxInitBuf2,uint8 *RxInitBuf2)
{
    Uart2_DMA_NVIC_Configuration();
    USART2_DMA_RxConfig(RxInitBuf2);
    USART2_DMA_TxConfig(TxInitBuf2);
}

void USART1_DMA_Config(uint8 *TxInitBuf1,uint8 *RxInitBuf1)
{
    Uart1_DMA_NVIC_Configuration();
    USART1_DMA_RxConfig(RxInitBuf1);
    USART1_DMA_TxConfig(TxInitBuf1);
}


/*
 * ��������Start_USART_DMAReceive
 * ����  ���������� DMA ���պ���
 * ����  : Getbuf,com
 * ���  ����
 */

void Start_USART_DMAReceive(uint8 Channel,uint8 *Getbuf)
{
    //getbuf = USART2_RECEIVE_DATA;
    if(Channel==1)//
    {
        DMA_Cmd(DMA1_Channel5, DISABLE); //�ر�ͨ��6
        DMA1_Channel5->CMAR = (u32)Getbuf;	//���ô洢�������ַ 
        DMA1_Channel5->CNDTR = 256;//��װ��䳤��
        DMA_Cmd(DMA1_Channel5, ENABLE);//������,�ؿ�DMA
    }
    else if(Channel==2)
    {
        DMA_Cmd(DMA1_Channel6, DISABLE); //�ر�ͨ��6
        DMA1_Channel6->CMAR = (u32)Getbuf;	//���ô洢�������ַ 
        DMA1_Channel6->CNDTR = 256;//��װ��䳤��
        DMA_Cmd(DMA1_Channel6, ENABLE);//������,�ؿ�DMA
    }	
}

/*
uint8 Get_DMA_ReceiveData(USART_TypeDef* USARTx,uint8 *RecData)
{
	 if(USARTx==USART1)
	 return *RecData;
	 else if(USARTx==USART2)
	 return *RecData;
}

*/
/*
 * ��������USART_DMA_SendStart
 * ����  ���������� DMA ���ͺ���
 * ����  : Sendbuf,Buffersize,com
 * ���  ����
 */
/*
void Start_USART_DMASend(USART_TypeDef* USARTx,uint8 *Sendbuf,uint8 Buffersize)
{	
    if(USARTx==USART1)
    {
        //�ı�datasizeǰ��Ҫ��ֹͨ������
        DMA_Cmd(DMA1_Channel4, DISABLE); //�ر�ͨ��7
        DMA1_Channel4->CNDTR=Buffersize; //DMA1,����������
        DMA1_Channel4->CMAR = (u32)Sendbuf;//���ô洢�������ַ	
        DMA_Cmd(DMA1_Channel4, ENABLE);	 //ʹ��DMA����
    }
    else if(USARTx==USART2)
    {
        //�ı�datasizeǰ��Ҫ��ֹͨ������
        DMA_Cmd(DMA1_Channel7, DISABLE); //�ر�ͨ��7
        DMA1_Channel7->CNDTR=Buffersize; //DMA1,����������
        DMA1_Channel7->CMAR = (u32)Sendbuf;//���ô洢�������ַ	
        DMA_Cmd(DMA1_Channel7, ENABLE);	 //ʹ��DMA����
    }
}
*/

/*
uint8 Get_DMA_ReceiveData(USART_TypeDef* USARTx,uint8 *RecData)
{
	 for()   
}

*/
/*
 * ��������USART_DMA_SendStart
 * ����  ���������� DMA ���ͺ���
 * ����  : Sendbuf,Buffersize,com
 * ���  ����
 */

void Start_USART_DMASend(uint8 Channel,uint8 *Sendbuf,uint8 Buffersize)
{	
    if(Buffersize>4)
    {
        if(Channel==1)//����1
        {

            //convert485_rts(USART1,1);
            Rts1485(1);
            //�ı�datasizeǰ��Ҫ��ֹͨ������
            DMA_Cmd(DMA1_Channel4, DISABLE); //�ر�ͨ��7
            DMA1_Channel4->CNDTR=Buffersize; //DMA1,����������
            DMA1_Channel4->CMAR = (u32)Sendbuf;//���ô洢����ַ	
            
            DMA_Cmd(DMA1_Channel4, ENABLE);	 //ʹ��DMA����
            
            
            //while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==0);
            //USART_ClearFlag(USART1,USART_FLAG_TC);
            //Rts1485(0);
        }
        else if(Channel==2)//����2
        {

            //convert485_rts(USART2,1);
            Rts2485(1);
            //�ı�datasizeǰ��Ҫ��ֹͨ������
            DMA_Cmd(DMA1_Channel7, DISABLE); //�ر�ͨ��7
            DMA1_Channel7->CNDTR=Buffersize; //DMA1,����������
            DMA1_Channel7->CMAR = (u32)Sendbuf;//���ô洢����ַ	
            DMA_Cmd(DMA1_Channel7, ENABLE);	 //ʹ��DMA����
            //USART_ITConfig(USART2, USART_IT_TC, ENABLE);
            //while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==0);
           // USART_ClearFlag(USART2,USART_FLAG_TC);
           // Rts2485(0);

        }
    } 
    
    //delay(1000);
    //Send_end_rec(Channel);
}

/*
 * ��������DMA1_Channel6_IRQHandler
 * ����  ��DMA1_Channel6�жϺ���
 * ����  : 
 * ���  ����
 */
void DMA1_Channel6_IRQHandler(void)//usart2 rx
{
  DMA_ClearITPendingBit(DMA1_IT_HT6); //�����������ж�
  DMA_ClearITPendingBit(DMA1_IT_TC6); //�����������ж�
  DMA_ClearITPendingBit(DMA1_IT_TE6); //�����������ж�
  DMA_Cmd(DMA1_Channel6, DISABLE);//�ر�DMA,��ֹ�������������
  DMA1_Channel6->CNDTR = 256;//��װ��
  DMA_Cmd(DMA1_Channel6, ENABLE);//������,�ؿ�DMA

}

/*
 * ��������DMA1_Channel7_IRQHandler
 * ����  ��DMA1_Channel7�жϺ���
 * ����  : 
 * ���  ����
 */
void DMA1_Channel7_IRQHandler(void)//usart2 tx
{
  
 // RTS2485(0);
  if(DMA_GetITStatus(DMA1_IT_TC7)!=RESET)
  {
      //USART_ITConfig(USART2, USART_IT_TC, ENABLE);/////////
      DMA_ClearITPendingBit(DMA1_IT_TC7);  //�����������ж�  
  }
  DMA_ClearITPendingBit(DMA1_IT_HT7);//�����������ж�
  DMA_ClearITPendingBit(DMA1_IT_TE7); //�����������ж�
  DMA_Cmd(DMA1_Channel7, DISABLE);//�ر�DMA
  
}


void DMA1_Channel5_IRQHandler(void)//usart1 rx
{
  DMA_ClearITPendingBit(DMA1_IT_HT5); //�����������ж�
  DMA_ClearITPendingBit(DMA1_IT_TC5); //�����������ж�
  DMA_ClearITPendingBit(DMA1_IT_TE5); //�����������ж�
  DMA_Cmd(DMA1_Channel5, DISABLE);//�ر�DMA,��ֹ�������������
  DMA1_Channel5->CNDTR = 256;//��װ��
  DMA_Cmd(DMA1_Channel5, ENABLE);//������,�ؿ�DMA

}



void DMA1_Channel4_IRQHandler(void)//usart1 tx
{
  if(DMA_GetITStatus(DMA1_IT_TC4)!=RESET)
  {
      //USART_ITConfig(USART1, USART_IT_TC, ENABLE);///////
      DMA_ClearITPendingBit(DMA1_IT_TC4);  //�����������ж�  
  }
  DMA_ClearITPendingBit(DMA1_IT_HT4);//�����������ж�
  DMA_ClearITPendingBit(DMA1_IT_TE4); //�����������ж�
  DMA_Cmd(DMA1_Channel4, DISABLE);//�ر�DMA
  
}
