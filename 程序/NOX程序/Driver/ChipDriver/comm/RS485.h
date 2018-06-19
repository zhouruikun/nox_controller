//#include <includes.h>

#ifndef _RS485_H_
#define _RS485_H_


#ifdef   RS485_globals
#define  RS485_ext
#else
#define  RS485_ext  extern   
#endif

#ifdef   RS485_globals

#define     RTS    GPIO_PIN_7
#define RTS_high() GPIOPinWrite(GPIO_PORTA_BASE,RTS,RTS)//�ߵ�ƽΪ����
#define RTS_low()  GPIOPinWrite(GPIO_PORTA_BASE,RTS,(0xFF-RTS))//�͵�ƽΪ����



RS485_ext void init_RS485(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);                          /*  ʹ��GPIOH                   */
	GPIOPadConfigSet(GPIO_PORTA_BASE, RTS, GPIO_STRENGTH_2MA,
                    GPIO_PIN_TYPE_STD); 								  /*  ����Ƭѡ�ܽ�Ϊ������2MA���*/
	GPIODirModeSet(GPIO_PORTA_BASE, RTS, GPIO_DIR_MODE_OUT);         /*  ����Ƭѡ�ܽ�Ϊ���         */

}
#else
#define     RTS    GPIO_PIN_7
#define RTS_high() GPIOPinWrite(GPIO_PORTA_BASE,RTS,RTS)
#define RTS_low()  GPIOPinWrite(GPIO_PORTA_BASE,RTS,(0xFF-RTS))
RS485_ext  void init_RS485(void);

#endif
#endif
