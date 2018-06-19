#include "CAN.h"
 #include "para.h"
 #include "PID.H"
#define MAX_MAIL_NUM  3
//CAN���ߵ���:0=���� 1=�Ի�����
#define CAN_DEBUG     0
//CAN���߲�����:0=250kbps,1=500kbps,2=1Mbps
#define CAN1_BPS      0
 
unsigned char can1_addr = 0;
 
unsigned short  Can1_Tx_Count =0;
unsigned short  Can1_Rx_Count =0;
 
unsigned short  Can1_Send_Delay =0;
 
unsigned char   Can1_Send_Buf[10]={0xeb,0x90,0x01,0x55,0xAA};
unsigned char   Can1_Recv_Buf[10]={0};

 
static  u8 CAN_msg_num[MAX_MAIL_NUM];   // ����������
 		u16 std_id =0x7e9;  
		u32 ext_id =0x18fedf00;  
		u32 mask =0;  
void CAN1_Config_init(void)
{
     CAN_InitTypeDef        CAN_InitStructure;
     CAN_FilterInitTypeDef  CAN_FilterInitStructure;
 
     /* CAN register init */
     CAN_DeInit(CAN1);
     CAN_StructInit(&CAN_InitStructure);
  
     /* CAN cell init */ //36MHz 500Kbps
     CAN_InitStructure.CAN_TTCM=DISABLE;//��ֹʱ�䴥��ͨ��ģʽ
     CAN_InitStructure.CAN_ABOM=DISABLE;//�����CAN_MCR�Ĵ�����INRQλ������1�����0��,һ��Ӳ�����
                                        //��128��11λ����������λ,���˳�����״̬
     CAN_InitStructure.CAN_AWUM=DISABLE;//˯��ģʽͨ�����CAN_MCR�Ĵ�����SLEEPλ,���������
     CAN_InitStructure.CAN_NART=DISABLE;//CAN�����Ƿ�ֻ��1��,���ܷ��͵Ľ�����(�ɹ�/������ٲö�ʧ)
     CAN_InitStructure.CAN_RFLM=DISABLE;//�ڽ��յ����ʱFIFOδ������,�����յ�FIFO����δ������,��һ���յ��ı��ĻḲ��ԭ�еı���
     CAN_InitStructure.CAN_TXFP=DISABLE;//���͵�FIFO���ȼ��ɱ��ĵı�ʶ��������
      
#if CAN_DEBUG
     CAN_InitStructure.CAN_Mode= CAN_Mode_LoopBack;
#else
     CAN_InitStructure.CAN_Mode= CAN_Mode_Normal; 
#endif
     //���䲨����
 
     if(CAN1_BPS ==  0)
     {
        CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;//����ͬ����Ծ���1��ʱ�䵥λ
        CAN_InitStructure.CAN_BS1=CAN_BS1_12tq;//ʱ���1Ϊ9��ʱ�䵥λ
        CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;//ʱ���2Ϊ8��ʱ�䵥λ
        CAN_InitStructure.CAN_Prescaler= 9;//36M/(1+12+3)/9= 250kbps
                                            //36M/(1+5+2)/9 = 500kbps
                                           //36M(1+2+1)/9 = 1M
     }
     else if(CAN1_BPS == 1)
     {
        CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;//����ͬ����Ծ���1��ʱ�䵥λ
        CAN_InitStructure.CAN_BS1=CAN_BS1_5tq;//ʱ���1Ϊ9��ʱ�䵥λ
        CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;//ʱ���2Ϊ8��ʱ�䵥λ
        CAN_InitStructure.CAN_Prescaler= 9;//36M/(1+12+3)/9= 250kbps
        
     }
     else
     {
        CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;//����ͬ����Ծ���1��ʱ�䵥λ
        CAN_InitStructure.CAN_BS1=CAN_BS1_2tq;//ʱ���1Ϊ9��ʱ�䵥λ
        CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;//ʱ���2Ϊ8��ʱ�䵥λ
        CAN_InitStructure.CAN_Prescaler= 9;//36M/(1+12+3)/9= 250kbps
         
     }
     CAN_Init(CAN1,&CAN_InitStructure); 
                                         
     /* CAN filter init */
     CAN_FilterInitStructure.CAN_FilterNumber=0;  //ָ���˴���ʼ���Ĺ�����0
     CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;//ָ���˹�����������ʼ������ģʽΪ��ʶ������λģʽ
     CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;;//�����˹�����λ��1��32λ������ 
//     CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;//�����趨��������ʶ����32λλ��ʱΪ��߶�λ��16λλ��ʱΪ��һ����
//     CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;;//�����趨��������ʶ����32λλ��ʱΪ��Ͷ�λ��16λλ��ʱΪ�ڶ���)
//     CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//�����趨���������α�ʶ�����߹�������ʶ����32λλ��ʱΪ��߶�λ��16λλ��ʱΪ��һ��)
//     CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;//�����趨���������α�ʶ�����߹�������ʶ����32λλ��ʱΪ��Ͷ�λ��16λλ��ʱΪ�ڶ���)


		 CAN_FilterInitStructure.CAN_FilterIdHigh=((ext_id<<3) >>16) &0xffff;  //���ñ�ʶ���Ĵ������ֽڡ�  
			CAN_FilterInitStructure.CAN_FilterIdLow=(u16)(ext_id<<3) | CAN_ID_EXT;   //���ñ�ʶ���Ĵ������ֽ�  
			mask =(std_id<<18);//����Ϊʲô����18λ����Ϊ��ISO11898�п��Կ�������׼CAN IDռID18~ID28��Ϊ����CAN_FilterIdHigh���룬Ӧ����2λ������Ϊ������չCAN��Ӧ����Ӧ��������16λ����ˣ��ܹ�Ӧ����2+16��18λ��Ҳ��������һ����ʽ����⣺ֱ�ӿ�Mapping�����ݣ�����STDID���EXID[0]ƫ����18λ,�������18λ.  
			mask ^=ext_id;//�������ı�׼CAN����չCAN����ȡ��  
			mask =~mask;  
			mask <<=3;//����������3λ  
			mask |=0x02; //ֻ��������֡��������Զ��֡  
			CAN_FilterInitStructure.CAN_FilterMaskIdHigh=(mask>>16)&0xffff; //�������μĴ������ֽ�  
			CAN_FilterInitStructure.CAN_FilterMaskIdLow=mask&0xfff7;   //�������μĴ������ֽ�  
		 
		 CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;;//�趨��ָ���������FIFO0 
     CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;//ʹ�ܹ�����
     CAN_FilterInit(&CAN_FilterInitStructure);
 
}
 
// ***************************************************************
//       BaudRate = 1 / NominalBitTime
//       NominalBitTime = 1tq + tBS1 + tBS2
//       tq = (BRP[9:0] + 1) x tPCLK
//       tPCLK = CAN's clock = APB1's clock
//   1Mbps �����£����õ��λ����6tqλ�ô���BS1=5, BS2=2
//   500kbps �����£����õ��λ����8tqλ�ô���BS1=7, BS2=3
//   250kbps �����£����õ��λ����14tqλ�ô���BS1=13, BS2=2
//   125k, 100k, 50k, 20k, 10k �Ĳ��õ�λ���� 250K ��ͬ
// ****************************************************************
 
void  CAN1_Com_init(void)
{
      GPIO_InitTypeDef GPIO_InitStruct;
      NVIC_InitTypeDef NVIC_InitStructure;
      
      /* Enable CAN RX0 interrupt IRQ channel */
      NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&NVIC_InitStructure);
       
      NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&NVIC_InitStructure);
       
      NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX1_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&NVIC_InitStructure);
       
       
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
      //Can Rx
      GPIO_InitStruct.GPIO_Pin  =  GPIO_Pin_11;
      GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStruct.GPIO_Mode =  GPIO_Mode_IPU;
      GPIO_Init(GPIOA,&GPIO_InitStruct);
      
      //Can Tx
      GPIO_InitStruct.GPIO_Pin  =  GPIO_Pin_12;
      GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStruct.GPIO_Mode =  GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA,&GPIO_InitStruct);
       
      CAN1_Config_init();
       
      CAN_ITConfig(CAN1,CAN_IT_FMP0 | CAN_IT_FF0 | CAN_IT_FOV0, ENABLE);  // fifo0�ж�
      CAN_ITConfig(CAN1,CAN_IT_FMP1 | CAN_IT_FF1 | CAN_IT_FOV1, ENABLE);  // fifo1�ж�
      CAN_ITConfig(CAN1,CAN_IT_TME, DISABLE);                // �����ж�
      CAN_ITConfig(CAN1,CAN_IT_EWG | CAN_IT_EPV | CAN_IT_BOF | CAN_IT_LEC | CAN_IT_ERR | CAN_IT_WKU | CAN_IT_SLK, ENABLE);  // ERR�ж�
 
      // CAN�����ʼ��
      memset(CAN_msg_num,0,MAX_MAIL_NUM);   
}
 
 
int CAN1_Tx_msg(CanTxMsg TxMessage)
{
    u8 TransmitMailbox = 0;
  
    TransmitMailbox = CAN_Transmit(CAN1,&TxMessage);
    if(CAN_NO_MB == TransmitMailbox)
    {
        //����ʧ��
        return 0;
    }
    else
    {         
        CAN_msg_num[TransmitMailbox] = 1;
       
    }
    CAN_ITConfig(CAN1,CAN_IT_TME, ENABLE);
     
    return 1;
}
 
 
 
int CAN1_Tx_data(void)
{
    CanTxMsg TxMessage;
    u8 TransmitMailbox = 0,i=0;
    
    /* transmit */
    TxMessage.StdId=0X00;//�趨��׼��ʶ��
    TxMessage.ExtId=0x18F00f52;//������չ��ʶ��
    TxMessage.RTR=CAN_RTR_DATA;//�趨��������Ϣ��֡����
    TxMessage.IDE=CAN_ID_EXT;//�趨��Ϣ��ʶ��������
    TxMessage.DLC=8; //���ݳ���
 
	
    Can1_Send_Buf[0]=((((-Arg_all.NOX_PPM)+200))*20.4)/256;  //NOX���ֽ�
    Can1_Send_Buf[1]=(int )((((-Arg_all.NOX_PPM)+200))*20.4)%256;  //NOX���ֽ�
    Can1_Send_Buf[2]=(((-Arg_all.O2PP+1200))*19.86)/256;  //O2���ֽ�
    Can1_Send_Buf[3]=(int )(((-Arg_all.O2PP+1200))*19.86)%256;  //O2���ֽ�
    Can1_Send_Buf[4]=0;  //״̬
    Can1_Send_Buf[5]=6;
    Can1_Send_Buf[6]=0;
    Can1_Send_Buf[7]=6;     
    for(i=0;i < TxMessage.DLC;i++)
    {
       TxMessage.Data[i] = Can1_Send_Buf[i];
    }
     
    TransmitMailbox = CAN_Transmit(CAN1,&TxMessage);
    if(CAN_NO_MB == TransmitMailbox)
    {
        //����ʧ��,û�п�����
        return 0;
    }
    else
    {         
        CAN_msg_num[TransmitMailbox] = 1;   
    }
    CAN_ITConfig(CAN1,CAN_IT_TME, ENABLE);
     
    Can1_Tx_Count++;
    if(Can1_Tx_Count > 10000)
       Can1_Tx_Count =0;
     
    Can1_Send_Delay =200;
    return 1;
}
 
//��������
void  CAN1_Rx_Data(CanRxMsg RxMessage)
{     
      u8  i =0;
      if((RxMessage.ExtId==0x18fedf00))
      {
           
          if(RxMessage.Data[7]==0x04)
					{
					//��������
						status_ON_OFF(1);
					}
         
          Can1_Rx_Count++;
          if(Can1_Rx_Count > 10000)
             Can1_Rx_Count =0;
      }
			if(RxMessage.ExtId==0x18fedf01)
			{
							*((u8 *)&Arg_all+RxMessage.Data[0]*2)=RxMessage.Data[2];
							*((u8 *)&Arg_all+RxMessage.Data[0]*2+1)=RxMessage.Data[1];
						  Save_PID_Arg();
			}
}
//�������жϺ���
void CAN1_Send(void)
{
     if(CAN_msg_num[0])
     {
        if(CAN_GetITStatus(CAN1,CAN_IT_RQCP0))
        {
            CAN_ClearITPendingBit(CAN1,CAN_IT_RQCP0);
            CAN_ITConfig(CAN1,CAN_IT_TME, DISABLE);
            CAN_msg_num[0] = 0;
        }
     }
     if(CAN_msg_num[1])
     {
        if(CAN_GetITStatus(CAN1,CAN_IT_RQCP1))
        {
            CAN_ClearITPendingBit(CAN1,CAN_IT_RQCP1);
            CAN_ITConfig(CAN1,CAN_IT_TME, DISABLE);
            CAN_msg_num[1] = 0;
        }
     }  
    if(CAN_msg_num[2])
    {
        if(CAN_GetITStatus(CAN1,CAN_IT_RQCP2))
        {
            CAN_ClearITPendingBit(CAN1,CAN_IT_RQCP2);
            CAN_ITConfig(CAN1,CAN_IT_TME, DISABLE);
            CAN_msg_num[2] = 0;
        }
    }
}
//�����жϺ���
void CAN1_Recv(unsigned char num)
{
     CanRxMsg RxMessage;
     switch(num)
     {
     case 0:
          if(CAN_GetITStatus(CAN1,CAN_IT_FF0))
          {
             CAN_ClearITPendingBit(CAN1,CAN_IT_FF0);
          }
          else if(CAN_GetITStatus(CAN1,CAN_IT_FOV0))
          {
             CAN_ClearITPendingBit(CAN1,CAN_IT_FOV0);
          }
          else
          {
             CAN_Receive(CAN1,CAN_FIFO0, &RxMessage);
             //��������:
             CAN1_Rx_Data(RxMessage);
          } 
          break;
     case 1:
          if(CAN_GetITStatus(CAN1,CAN_IT_FF1))
          {
             CAN_ClearITPendingBit(CAN1,CAN_IT_FF1);
          }
          else if(CAN_GetITStatus(CAN1,CAN_IT_FOV1))
          {
             CAN_ClearITPendingBit(CAN1,CAN_IT_FOV1);
          }
          else
          {
             CAN_Receive(CAN1,CAN_FIFO1, &RxMessage);
            //��������
             CAN1_Rx_Data(RxMessage);
          } 
          break;
     } 
}
 
void USB_HP_CAN1_TX_IRQHandler()
{
	CAN1_Send();
}
void USB_LP_CAN1_RX0_IRQHandler()
{
	CAN1_Recv(0);	
}
           
void CAN1_RX1_IRQHandler()
{
CAN1_Recv(1);	
}
                
void CAN1_SCE_IRQHandler()
{
	
}
          