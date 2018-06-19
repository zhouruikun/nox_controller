
#define EXTI_globals
#include "exti.h"
#include "gpio.h"
#include "nvic.h"
#include "pwm.h"
#include "Gripper_Valve.h"
/*******************************************************************************
*�������ܣ�										
*����������	 DK_EXTI_Init(2,EXTI_Line8,1)
***********************************************************************************/
void DK_EXTI_Init(u8 GPIOx,u16 EXTI_Linex,u8 Type)
{					   
    EXTI_InitTypeDef 	 EXTI_InitStructure;		
    u8 GPIO_PortSource,GPIO_PinSource;	//����ѡ��ܽ�
    EXTI_InitStructure.EXTI_Line = EXTI_Linex; 
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
    switch(Type)
    {
        case 1://������
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
        break;
        case 2://����
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
        break;
        case 3://�����غ�������
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling ; 	
        break;
    }
    EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
    switch(GPIOx)	 //
    {
        case 1:	
                EXTI_Init(&EXTI_InitStructure);
                GPIO_PortSource = GPIO_PortSourceGPIOA;	 //����ѡ��ܽ�
        break;
        case 2:	
                EXTI_Init(&EXTI_InitStructure);
                GPIO_PortSource = GPIO_PortSourceGPIOB;	  //����ѡ��ܽ�
        break;
        case 3:	
                EXTI_Init(&EXTI_InitStructure);
                GPIO_PortSource = GPIO_PortSourceGPIOC;	  //����ѡ��ܽ�
        break;
        case 4:	
                EXTI_Init(&EXTI_InitStructure);
                GPIO_PortSource = GPIO_PortSourceGPIOD;	 //����ѡ��ܽ�
        break;
        case 5:	
                EXTI_Init(&EXTI_InitStructure);
                GPIO_PortSource = GPIO_PortSourceGPIOE;	 //����ѡ��ܽ�
        break;
        case 6:	
                EXTI_Init(&EXTI_InitStructure);
                GPIO_PortSource = GPIO_PortSourceGPIOF;	 //����ѡ��ܽ�
        break;
        case 7:	
                EXTI_Init(&EXTI_InitStructure);
                GPIO_PortSource = GPIO_PortSourceGPIOG;	 //����ѡ��ܽ�
        break;
    }	
    //EXTI_GenerateSWInterrupt(EXTI_Linex);  //�ж�������(������仰�ϵ�ͻ�����ж�)
    switch(EXTI_Linex)
    {
            case EXTI_Line0:	
                            EXTI_ClearITPendingBit(EXTI_Line0);//
                            GPIO_PinSource = GPIO_PinSource0;	 //����ѡ��ܽ�
            break;
            case EXTI_Line1:	
                            EXTI_ClearITPendingBit(EXTI_Line1);//
                            GPIO_PinSource = GPIO_PinSource1;	 //����ѡ��ܽ�
            break;
            case EXTI_Line2:	  
                            EXTI_ClearITPendingBit(EXTI_Line2);//
                            GPIO_PinSource = GPIO_PinSource2;	 //����ѡ��ܽ�
            break;
            case EXTI_Line3:	  
                            EXTI_ClearITPendingBit(EXTI_Line3);//
                            GPIO_PinSource = GPIO_PinSource3;	  //����ѡ��ܽ�
            break;
            case EXTI_Line4:	 
                            EXTI_ClearITPendingBit(EXTI_Line4);//
                            GPIO_PinSource = GPIO_PinSource4;	 //����ѡ��ܽ�
            break;
            case EXTI_Line5:	
                            EXTI_ClearITPendingBit(EXTI_Line5);//
                            GPIO_PinSource = GPIO_PinSource5;	 //����ѡ��ܽ�
            break;
            case EXTI_Line6:		  
                            EXTI_ClearITPendingBit(EXTI_Line6);//
                            GPIO_PinSource = GPIO_PinSource6;	 //����ѡ��ܽ�
            break;
            case EXTI_Line7:	
                            EXTI_ClearITPendingBit(EXTI_Line7);//	
                            GPIO_PinSource = GPIO_PinSource7;	 //����ѡ��ܽ�
            break;
            case EXTI_Line8:	
                            EXTI_ClearITPendingBit(EXTI_Line8);// 
                            GPIO_PinSource = GPIO_PinSource8;	 //����ѡ��ܽ�
            break;
            case EXTI_Line9:	
                            EXTI_ClearITPendingBit(EXTI_Line9);// 
                            GPIO_PinSource = GPIO_PinSource9;	 //����ѡ��ܽ�
            break;
            case EXTI_Line10:	
                            EXTI_ClearITPendingBit(EXTI_Line10);//	
                            GPIO_PinSource = GPIO_PinSource10;	 //����ѡ��ܽ�
            break;
            case EXTI_Line11:	
                            EXTI_ClearITPendingBit(EXTI_Line11);//
                            GPIO_PinSource = GPIO_PinSource11;	 //����ѡ��ܽ�
            break;
            case EXTI_Line12:	
                            EXTI_ClearITPendingBit(EXTI_Line12);//
                            GPIO_PinSource = GPIO_PinSource12;	 //����ѡ��ܽ�
            break;
            case EXTI_Line13:	
                            EXTI_ClearITPendingBit(EXTI_Line13);//
                            GPIO_PinSource = GPIO_PinSource13;	 //����ѡ��ܽ�
            break;
            case EXTI_Line14:	
                            EXTI_ClearITPendingBit(EXTI_Line14);//
                            GPIO_PinSource = GPIO_PinSource14;	 //����ѡ��ܽ�
            break;
            case EXTI_Line15:	
                            EXTI_ClearITPendingBit(EXTI_Line15);//
                            GPIO_PinSource = GPIO_PinSource15;	 //����ѡ��ܽ�
            break;
    }
    //ѡ��ܽ�		example:GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);
    GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource);
}
/*******************************************************************************
*�������ܣ�								
*����������	
***********************************************************************************/
void INT_Disable(u16 EXTI_Linex)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_InitStructure.EXTI_Line = EXTI_Linex;
	EXTI_Init(&EXTI_InitStructure); 
}
/*******************************************************************************
*�������ܣ�								
*����������	
***********************************************************************************/
void INT_Enable(u16 EXTI_Linex)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Line = EXTI_Linex;
	EXTI_Init(&EXTI_InitStructure); 
}
 
//GPIO�ڵ����� 
void Exti_GPIO_Configuration(void)
{
    DK_GPIO_Init(PB,GripperIn1 | GripperIn2 | Valvein1 | Valvein2,IPU); //���������ж��ĸ��ź���
    DK_GPIO_Init(PA,CoilFeederInA | CoilFeederInB,IPU); //�������� ��Ҫ�㶯
}
//�ⲿ�ж�����
void Exti_Configuration(void)
{
    //four signal
    DK_EXTI_Init(PB, EXTI_LINE_GripperIn1 , Trigger_Rising);//��ɴ��1
    DK_EXTI_Init(PB, EXTI_LINE_GripperIn2 , Trigger_Rising);//��ɴ��2
    DK_EXTI_Init(PB, EXTI_LINE_Valvein1 , Trigger_Rising);//ת��1
    DK_EXTI_Init(PB, EXTI_LINE_Valvein2, Trigger_Rising);//ת��2
    //two point signal
    DK_EXTI_Init(PA, EXTI_LINE_CoilFeederInA, Trigger_Falling);//feederA
    DK_EXTI_Init(PA, EXTI_LINE_CoilFeederInB, Trigger_Falling);//feederB
    
}
//��ռ���ȼ�
void Exti_NVIC_Configuration(void)
{
    DK_NVIC_Init(0);//ѡ��NVIC_PriorityGroup_0��40λȫ��Ϊռ��ʽ���ȼ���Ҫʵ���жϱ����ȳ�ʼ��NVIC
    DK_NVIC_IRQ_Set(EXTI9_5_IRQn,0,0,ENABLE); //�������ȼ�0
    DK_NVIC_IRQ_Set(EXTI1_IRQn,0,0,ENABLE); //�������ȼ�0
    DK_NVIC_IRQ_Set(EXTI2_IRQn,0,0,ENABLE); //�������ȼ�0

}
//�ⲿ�ж�0�������
//��ʼ��PA0,PA13,PA15Ϊ�ж�����.
void Extix_Init(void)
{  

    Exti_GPIO_Configuration();
    Exti_Configuration();
    Exti_NVIC_Configuration();
}


//����ͷ��A�ĵ㶯�źţ�ȥ�����ɴ��A���ź�
void EXTI1_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_LINE_CoilFeederInA) != RESET)	  //���ָ����EXTI0��·�������������
    {
        
    }
    EXTI_ClearITPendingBit(EXTI_LINE_CoilFeederInA);  //���EXTI_LINE_GripperIn1��·����λ
    
    
}
//����ͷ��B�ĵ㶯�źţ�ȥ�����ɴ��B���ź�
void EXTI2_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_LINE_CoilFeederInB) != RESET)	  //���ָ����EXTI0��·�������������
    {
        
    }
    EXTI_ClearITPendingBit(EXTI_LINE_CoilFeederInB);  //���EXTI_LINE_GripperIn1��·����λ
}


void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_LINE_GripperIn1) != RESET)	  //���ָ����EXTI0��·�������������
    {	  
         
    }
    EXTI_ClearITPendingBit(EXTI_LINE_GripperIn1);  //���EXTI_LINE_GripperIn1��·����λ
    
    
    if(EXTI_GetITStatus(EXTI_LINE_GripperIn2) != RESET)	  //���ָ����EXTI0��·�������������
    {	  
        
    }
    EXTI_ClearITPendingBit(EXTI_LINE_GripperIn2);  //���EXTI0��·����
    
    if(EXTI_GetITStatus(EXTI_LINE_Valvein1) != RESET)	  //���ָ����EXTI0��·�������������
    {	  
       
    }
    EXTI_ClearITPendingBit(EXTI_LINE_Valvein1);  //���EXTI0��·����λ
    
    if(EXTI_GetITStatus(EXTI_LINE_Valvein2) != RESET)	  //���ָ����EXTI0��·�������������
    {	  
       
    }
    EXTI_ClearITPendingBit(EXTI_LINE_Valvein2);  //���EXTI0��·����λ
    
}
