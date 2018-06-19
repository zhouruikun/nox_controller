
#define EXTI_globals
#include "exti.h"
#include "gpio.h"
#include "nvic.h"
#include "pwm.h"
#include "Gripper_Valve.h"
/*******************************************************************************
*函数功能：										
*函数描述：	 DK_EXTI_Init(2,EXTI_Line8,1)
***********************************************************************************/
void DK_EXTI_Init(u8 GPIOx,u16 EXTI_Linex,u8 Type)
{					   
    EXTI_InitTypeDef 	 EXTI_InitStructure;		
    u8 GPIO_PortSource,GPIO_PinSource;	//用于选择管脚
    EXTI_InitStructure.EXTI_Line = EXTI_Linex; 
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
    switch(Type)
    {
        case 1://上升沿
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
        break;
        case 2://下沿
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
        break;
        case 3://上升沿和下升沿
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling ; 	
        break;
    }
    EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
    switch(GPIOx)	 //
    {
        case 1:	
                EXTI_Init(&EXTI_InitStructure);
                GPIO_PortSource = GPIO_PortSourceGPIOA;	 //用于选择管脚
        break;
        case 2:	
                EXTI_Init(&EXTI_InitStructure);
                GPIO_PortSource = GPIO_PortSourceGPIOB;	  //用于选择管脚
        break;
        case 3:	
                EXTI_Init(&EXTI_InitStructure);
                GPIO_PortSource = GPIO_PortSourceGPIOC;	  //用于选择管脚
        break;
        case 4:	
                EXTI_Init(&EXTI_InitStructure);
                GPIO_PortSource = GPIO_PortSourceGPIOD;	 //用于选择管脚
        break;
        case 5:	
                EXTI_Init(&EXTI_InitStructure);
                GPIO_PortSource = GPIO_PortSourceGPIOE;	 //用于选择管脚
        break;
        case 6:	
                EXTI_Init(&EXTI_InitStructure);
                GPIO_PortSource = GPIO_PortSourceGPIOF;	 //用于选择管脚
        break;
        case 7:	
                EXTI_Init(&EXTI_InitStructure);
                GPIO_PortSource = GPIO_PortSourceGPIOG;	 //用于选择管脚
        break;
    }	
    //EXTI_GenerateSWInterrupt(EXTI_Linex);  //中断线允许(加上这句话上电就会进入中断)
    switch(EXTI_Linex)
    {
            case EXTI_Line0:	
                            EXTI_ClearITPendingBit(EXTI_Line0);//
                            GPIO_PinSource = GPIO_PinSource0;	 //用于选择管脚
            break;
            case EXTI_Line1:	
                            EXTI_ClearITPendingBit(EXTI_Line1);//
                            GPIO_PinSource = GPIO_PinSource1;	 //用于选择管脚
            break;
            case EXTI_Line2:	  
                            EXTI_ClearITPendingBit(EXTI_Line2);//
                            GPIO_PinSource = GPIO_PinSource2;	 //用于选择管脚
            break;
            case EXTI_Line3:	  
                            EXTI_ClearITPendingBit(EXTI_Line3);//
                            GPIO_PinSource = GPIO_PinSource3;	  //用于选择管脚
            break;
            case EXTI_Line4:	 
                            EXTI_ClearITPendingBit(EXTI_Line4);//
                            GPIO_PinSource = GPIO_PinSource4;	 //用于选择管脚
            break;
            case EXTI_Line5:	
                            EXTI_ClearITPendingBit(EXTI_Line5);//
                            GPIO_PinSource = GPIO_PinSource5;	 //用于选择管脚
            break;
            case EXTI_Line6:		  
                            EXTI_ClearITPendingBit(EXTI_Line6);//
                            GPIO_PinSource = GPIO_PinSource6;	 //用于选择管脚
            break;
            case EXTI_Line7:	
                            EXTI_ClearITPendingBit(EXTI_Line7);//	
                            GPIO_PinSource = GPIO_PinSource7;	 //用于选择管脚
            break;
            case EXTI_Line8:	
                            EXTI_ClearITPendingBit(EXTI_Line8);// 
                            GPIO_PinSource = GPIO_PinSource8;	 //用于选择管脚
            break;
            case EXTI_Line9:	
                            EXTI_ClearITPendingBit(EXTI_Line9);// 
                            GPIO_PinSource = GPIO_PinSource9;	 //用于选择管脚
            break;
            case EXTI_Line10:	
                            EXTI_ClearITPendingBit(EXTI_Line10);//	
                            GPIO_PinSource = GPIO_PinSource10;	 //用于选择管脚
            break;
            case EXTI_Line11:	
                            EXTI_ClearITPendingBit(EXTI_Line11);//
                            GPIO_PinSource = GPIO_PinSource11;	 //用于选择管脚
            break;
            case EXTI_Line12:	
                            EXTI_ClearITPendingBit(EXTI_Line12);//
                            GPIO_PinSource = GPIO_PinSource12;	 //用于选择管脚
            break;
            case EXTI_Line13:	
                            EXTI_ClearITPendingBit(EXTI_Line13);//
                            GPIO_PinSource = GPIO_PinSource13;	 //用于选择管脚
            break;
            case EXTI_Line14:	
                            EXTI_ClearITPendingBit(EXTI_Line14);//
                            GPIO_PinSource = GPIO_PinSource14;	 //用于选择管脚
            break;
            case EXTI_Line15:	
                            EXTI_ClearITPendingBit(EXTI_Line15);//
                            GPIO_PinSource = GPIO_PinSource15;	 //用于选择管脚
            break;
    }
    //选择管脚		example:GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);
    GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource);
}
/*******************************************************************************
*函数功能：								
*函数描述：	
***********************************************************************************/
void INT_Disable(u16 EXTI_Linex)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_InitStructure.EXTI_Line = EXTI_Linex;
	EXTI_Init(&EXTI_InitStructure); 
}
/*******************************************************************************
*函数功能：								
*函数描述：	
***********************************************************************************/
void INT_Enable(u16 EXTI_Linex)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Line = EXTI_Linex;
	EXTI_Init(&EXTI_InitStructure); 
}
 
//GPIO口的配制 
void Exti_GPIO_Configuration(void)
{
    DK_GPIO_Init(PB,GripperIn1 | GripperIn2 | Valvein1 | Valvein2,IPU); //上拉输入中断四根信号线
    DK_GPIO_Init(PA,CoilFeederInA | CoilFeederInB,IPU); //上拉输入 两要点动
}
//外部中断配制
void Exti_Configuration(void)
{
    //four signal
    DK_EXTI_Init(PB, EXTI_LINE_GripperIn1 , Trigger_Rising);//夹纱器1
    DK_EXTI_Init(PB, EXTI_LINE_GripperIn2 , Trigger_Rising);//夹纱器2
    DK_EXTI_Init(PB, EXTI_LINE_Valvein1 , Trigger_Rising);//转阀1
    DK_EXTI_Init(PB, EXTI_LINE_Valvein2, Trigger_Rising);//转阀2
    //two point signal
    DK_EXTI_Init(PA, EXTI_LINE_CoilFeederInA, Trigger_Falling);//feederA
    DK_EXTI_Init(PA, EXTI_LINE_CoilFeederInB, Trigger_Falling);//feederB
    
}
//抢占优先级
void Exti_NVIC_Configuration(void)
{
    DK_NVIC_Init(0);//选择NVIC_PriorityGroup_0，40位全部为占先式优先级，要实现中断必须先初始化NVIC
    DK_NVIC_IRQ_Set(EXTI9_5_IRQn,0,0,ENABLE); //抢先优先级0
    DK_NVIC_IRQ_Set(EXTI1_IRQn,0,0,ENABLE); //抢先优先级0
    DK_NVIC_IRQ_Set(EXTI2_IRQn,0,0,ENABLE); //抢先优先级0

}
//外部中断0服务程序
//初始化PA0,PA13,PA15为中断输入.
void Extix_Init(void)
{  

    Exti_GPIO_Configuration();
    Exti_Configuration();
    Exti_NVIC_Configuration();
}


//捕获头子A的点动信号，去输出夹纱器A的信号
void EXTI1_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_LINE_CoilFeederInA) != RESET)	  //检查指定的EXTI0线路触发请求发生与否
    {
        
    }
    EXTI_ClearITPendingBit(EXTI_LINE_CoilFeederInA);  //清除EXTI_LINE_GripperIn1线路挂起位
    
    
}
//捕获头子B的点动信号，去输出夹纱器B的信号
void EXTI2_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_LINE_CoilFeederInB) != RESET)	  //检查指定的EXTI0线路触发请求发生与否
    {
        
    }
    EXTI_ClearITPendingBit(EXTI_LINE_CoilFeederInB);  //清除EXTI_LINE_GripperIn1线路挂起位
}


void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_LINE_GripperIn1) != RESET)	  //检查指定的EXTI0线路触发请求发生与否
    {	  
         
    }
    EXTI_ClearITPendingBit(EXTI_LINE_GripperIn1);  //清除EXTI_LINE_GripperIn1线路挂起位
    
    
    if(EXTI_GetITStatus(EXTI_LINE_GripperIn2) != RESET)	  //检查指定的EXTI0线路触发请求发生与否
    {	  
        
    }
    EXTI_ClearITPendingBit(EXTI_LINE_GripperIn2);  //清除EXTI0线路挂起
    
    if(EXTI_GetITStatus(EXTI_LINE_Valvein1) != RESET)	  //检查指定的EXTI0线路触发请求发生与否
    {	  
       
    }
    EXTI_ClearITPendingBit(EXTI_LINE_Valvein1);  //清除EXTI0线路挂起位
    
    if(EXTI_GetITStatus(EXTI_LINE_Valvein2) != RESET)	  //检查指定的EXTI0线路触发请求发生与否
    {	  
       
    }
    EXTI_ClearITPendingBit(EXTI_LINE_Valvein2);  //清除EXTI0线路挂起位
    
}
