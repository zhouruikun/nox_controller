/* ��ֹ�ض���-----------------------------------------------------------------*/
#ifndef _DMA_H
#define _DMA_H
/* ����ͷ�ļ� *****************************************************************/

/* �������� ------------------------------------------------------------------*/
/* �궨�� --------------------------------------------------------------------*/    
/* ���� ----------------------------------------------------------------------*/
/* �������� ------------------------------------------------------------------*/
/* �������� ------------------------------------------------------------------*/
#ifdef   DMA_globals
#define  DMA_ext
#else
#define  DMA_ext  extern
#endif



DMA_ext void DMA_NVIC_Configuration(void);	//���� DMA �ж�����
DMA_ext void USART1_DMA_RxConfig(uint8 *RxInitBuf1); //����1���ճ�ʼ��
DMA_ext void USART1_DMA_TxConfig(uint8 *TxInitBuf1); //����1���ճ�ʼ��
DMA_ext void USART2_DMA_RxConfig(uint8 *RxInitBuf2); //����2���ճ�ʼ��
DMA_ext void USART2_DMA_TxConfig(uint8 *TxInitBuf2);
DMA_ext void USART2_DMA_Config(uint8 *TxInitBuf2,uint8 *RxInitBuf2);
DMA_ext void USART1_DMA_Config(uint8 *TxInitBuf1,uint8 *RxInitBuf1);
DMA_ext void Start_USART_DMAReceive(uint8 Channel,uint8 *Getbuf);
DMA_ext void Start_USART_DMASend(uint8 Channel,uint8 *Sendbuf,uint8 Buffersize);
DMA_ext void DMA1_RCC_Configuration(void);


DMA_ext void NVIC_Config(void);
DMA_ext void USART_Config(void);

#endif
