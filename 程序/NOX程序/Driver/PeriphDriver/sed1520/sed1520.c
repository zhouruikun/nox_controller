#include "stm32f10x.h"
#include "datatype.h"
#include "BitReadWrite.h"
#define charlib_globals
#include "charlib.H"
#include "sed1520.h"


#define LCD_DATA     (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5\
                         |GPIO_Pin_6|GPIO_Pin_7)
#define LCD_PORTC GPIOC

#define     LCD_RIS       GPIO_Pin_5
#define     LCD_E1        GPIO_Pin_6
#define     LCD_E2        GPIO_Pin_7
#define     LCD_RW        GPIO_Pin_8
#define     LCD_A0        GPIO_Pin_9
#define     LCD_Busy      GPIO_Pin_7


#define RIS_high()    GPIO_SetBits(GPIOB,LCD_RIS);

#define LCD_E1_high() GPIO_SetBits(GPIOB,LCD_E1);
#define LCD_E1_low()  GPIO_ResetBits(GPIOB,LCD_E1);

#define LCD_E2_high() GPIO_SetBits(GPIOB,LCD_E2);
#define LCD_E2_low()  GPIO_ResetBits(GPIOB,LCD_E2);

#define LCD_RW_high() GPIO_SetBits(GPIOB,LCD_RW);
#define LCD_RW_low()  GPIO_ResetBits(GPIOB,LCD_RW);

#define LCD_A0_high() GPIO_SetBits(GPIOB,LCD_A0);
#define LCD_A0_low()  GPIO_ResetBits(GPIOB,LCD_A0); 
//-------------------------------------------------------------------------------
//����XPOS,YPOS��������ָʾ��ǰ�������λ�õ�Ԥ����
//�û��ڱ�дӦ�ó���ʱ,�谴�Լ���ʵ�����������Ҫ�����¶���
uint8 XPOS;                     //�з���LCD����λ��ָ��
uint8 YPOS;                     //�з���LCD����λ��ָ��
uint8 CharImageReverse;                   //�ַ���ͼ�εķ��Կ���,0(������ʾ),1(����)

#define XDOTS   122                     //ͼ�οռ�X�����С
#define YDOTS   32                      //ͼ�οռ�X�����С
#define ENGLISHCHARSIZE    8       //Ӣ���ַ�X������ʾ��ĸ���
#define CHINESECHARSIZE    16      //�����ַ�X������Ӣ���ַ�Y������ʾ��ĸ���
#define ENGLISHCHARDOTSIZE 16      //����Ӣ���ַ�������ֽ���
#define CHINESECHARDOTSIZE 32      //���������ַ�������ֽ���


void LCD_I0_Config(void)
{ 
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LCD_RIS | LCD_E1 | LCD_E2 | LCD_RW | LCD_A0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LCD_DATA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(LCD_PORTC, &GPIO_InitStructure);
}

void LCD_DataIo_Out(void)//���������
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LCD_DATA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(LCD_PORTC, &GPIO_InitStructure);	
}

void LCD_DataIo_In(void)//����������
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LCD_DATA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(LCD_PORTC, &GPIO_InitStructure);		
}

void LCD_Busy_In(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LCD_Busy;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(LCD_PORTC, &GPIO_InitStructure);
}
//-------------------------------------------------------------------------------
//�ӳ�������:voidlcdwaitidle1(void).
//����:æ���,�ڶ�Һ����ʾ������������ÿһ��ָ��֮ǰ,����Һ����ʾ���Ƿ����.
//�޸�����:2009.09.29
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwaitidle1(void)                 //������1æ����ӳ���
{  
    
    
    LCD_E1_low();			//��ֹ
    LCD_E2_low();			//	
    //��״̬
    LCD_A0_low();			//ָ��
    LCD_RW_high();			//��
    LCD_DataIo_Out();//���������Ƴ����
    GPIO_Write(LCD_PORTC,0XFF);
    //delay_us(1);
    LCD_Busy_In();//����Ϊ����
    while(1)
    {
            LCD_E1_high();		//ʹ����������
            //delay_us(1);
            if(!(GPIO_ReadInputDataBit(LCD_PORTC,LCD_Busy)&0x80))	//��æ
                    break;
            LCD_E1_low();		//��ֹ
            //delay_us(1);
    }
    LCD_E1_low();	
}
//-------------------------------------------------------------------------------
//�ӳ�������:voidlcdwaitidle2(void).
//����:æ���,�ڶ�Һ����ʾ������������ÿһ��ָ��֮ǰ,����Һ����ʾ���Ƿ����.
//�޸�����:2009.09.29
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwaitidle2(void)                 //������2æ����ӳ���
{   
    LCD_E1_low();			//��ֹ
    LCD_E2_low();			//	
    //��״̬
    LCD_A0_low();			//ָ��
    LCD_RW_high();			//��
    LCD_DataIo_Out();//���������Ƴ����
    GPIO_Write(LCD_PORTC,0XFF);
    //delay_us(1);
    LCD_Busy_In();//����Ϊ����
    while(1)
    {
            LCD_E2_high();		//ʹ�ܴӿ�����
            //delay_us(1);
            if(!(GPIO_ReadInputDataBit(LCD_PORTC,LCD_Busy)&0x80))	//��æ
                    break;
            LCD_E2_high();		//��ֹ
            //delay_us(1);
    }
    LCD_E2_low();	
}

//-------------------------------------------------------------------------------
//�ӳ�������:void lcdwd1(uint8 d).
//����:��Һ����ʾ������1дͼ������.
//�޸�����:2013.4.27
//�޸���:lqm_8
//-------------------------------------------------------------------------------
void lcdwd1(uint8 d)
{   
    lcdwaitidle1();
    LCD_E1_low();			//��ֹ��������
    //delay_us(1);
    //д����
    LCD_A0_high();			//����
    LCD_RW_low();			//д
    //delay_us(1);
    LCD_E1_high();			//ʹ����������
    //delay_us(1);
    LCD_DataIo_Out();//���������Ƴ����
    GPIO_Write(LCD_PORTC,d);
    //delay_us(1);
    LCD_E1_low();			//д��󣬽�ֹ��������
    //delay_us(1);
    //��״̬�����д��󶼻ص���״̬����ʾ�ȶ���
    LCD_A0_low();			//ָ��
    LCD_RW_high();			//��
    //delay_us(1);
    GPIO_Write(LCD_PORTC,0XFF);
}
//-------------------------------------------------------------------------------
//�ӳ�������:void lcdwd2(uint8 d).
//����:��Һ����ʾ������2дͼ������.
//�޸�����:2009.09.29
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwd2(uint8 d)
{   
    lcdwaitidle2();
    LCD_E2_low();			//��ֹ�ӿ�����
    //delay_us(1);
    //д����
    LCD_A0_high();			//����
    LCD_RW_low();			//д
    //delay_us(1);
    LCD_E2_high();			//ʹ�ܴӿ�����
    //delay_us(1);
    LCD_DataIo_Out();//���������Ƴ����
    GPIO_Write(LCD_PORTC,d);
    //delay_us(1);
    LCD_E2_low();			//д��󣬽�ֹ�ӿ�����
    //delay_us(1);
    //��״̬�����д��󶼻ص���״̬����ʾ�ȶ���
    LCD_A0_low();			//ָ��
    LCD_RW_high();			//��
    //delay_us(1);
    GPIO_Write(LCD_PORTC,0XFF);
}
//-------------------------------------------------------------------------------
//�ӳ�������:uint8 lcdrd1(void).
//����:��Һ����ʾ������1�ж�ͼ������.
//�޸�����:2009.09.29
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
uint8 lcdrd1(void)              //��ͼ�������ӳ���
{  
    uint8 d;
    lcdwaitidle1();                     //���Һ����ʾ�������Ƿ����
    LCD_E1_low();			//��ֹ��������
    //delay_us(1);
    //������
    LCD_A0_high();			//����
    LCD_RW_high();			//��
    //delay_us(1);
    LCD_E1_high();			//ʹ����������
    //delay_us(1);
    LCD_DataIo_In();//����������
    d = GPIO_ReadInputData(LCD_PORTC);  
    //delay_us(1);
    LCD_E1_low();			//д��󣬽�ֹ��������
    //delay_us(1);
    //��״̬�����д��󶼻ص���״̬����ʾ�ȶ���
    LCD_A0_low();			//ָ��
    LCD_RW_high();			//��
    //delay_us(1);
    LCD_DataIo_Out();//���������Ƴ����
    GPIO_Write(LCD_PORTC,0XFF);
    return d;
}
//-------------------------------------------------------------------------------
//�ӳ�������:uint8 lcdrd2(void).
//����:��Һ����ʾ������2�ж�ͼ������.
//�޸�����:2009.09.29
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
uint8 lcdrd2(void)              //��ͼ�������ӳ���
{   
    uint8 d;
    lcdwaitidle2();                     //���Һ����ʾ�������Ƿ����
    LCD_E2_low();			//��ֹ��������
    //delay_us(1);
    //������
    LCD_A0_high();			//����
    LCD_RW_high();			//��
    //delay_us(1);
    LCD_E2_high();			//ʹ����������
    //delay_us(1);
    LCD_DataIo_In();//����������
    d = GPIO_ReadInputData(LCD_PORTC);  
    //delay_us(1);
    LCD_E2_low();			//д��󣬽�ֹ��������
    //delay_us(1);
    //��״̬�����д��󶼻ص���״̬����ʾ�ȶ���
    LCD_A0_low();			//ָ��
    LCD_RW_high();			//��
    //delay_us(1);
    LCD_DataIo_Out();//���������Ƴ����
    GPIO_Write(LCD_PORTC,0XFF);
    return d;
}
//-------------------------------------------------------------------------------
//�ӳ�������:lcdwc1(uint8 c).
//����:��Һ����ʾ������1��ָ��.
//�޸�����:2009.09.29
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwc1(uint8 c)            //��Һ����ʾ������1��ָ��
{   
    lcdwaitidle1();
    LCD_E1_low();			//��ֹ��������
    //delay_us(1);
    //дָ��
    LCD_A0_low();			//ָ��
    LCD_RW_low();			//д
    //delay_us(1);
    LCD_E1_high();			//ʹ����������
    //delay_us(1);
    LCD_DataIo_Out();//���������Ƴ����
    GPIO_Write(LCD_PORTC,c);
    //delay_us(1);
    LCD_E1_low();			//д��󣬽�ֹ��������
    //delay_us(1);
    //��״̬�����д��󶼻ص���״̬����ʾ�ȶ���
    LCD_A0_low();			//ָ��
    LCD_RW_low();			//��
    //delay_us(1);
    //GPIOPadConfigSet(g_port, LCD_DATA, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD); /*  PG0-PG7����Ƭѡ�ܽ�Ϊ������2MA���*/
    //GPIOPinTypeGPIOOutput(g_port,LCD_DATA);	 //���������
    GPIO_Write(LCD_PORTC,0xff);
}
//-------------------------------------------------------------------------------
//�ӳ�������:lcdwc2(uint8 c).
//����:��Һ����ʾ������2��ָ��.
//�޸�����:2009.09.29
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwc2(uint8 c)            //��Һ����ʾ������2��ָ��
{   
    lcdwaitidle2();
    LCD_E2_low();			//��ֹ�ӿ�����
    //delay_us(1);
    //дָ��
    LCD_A0_low();			//ָ��
    LCD_RW_low();			//д
    //delay_us(1);
    LCD_E2_high();			//ʹ�ܴӿ�����
    //delay_us(1);
    LCD_DataIo_Out();//���������Ƴ����
    GPIO_Write(LCD_PORTC,c);
    //delay_us(1);
    LCD_E2_low();			//д��󣬽�ֹ�ӿ�����
    //delay_us(1);
    //��״̬�����д��󶼻ص���״̬����ʾ�ȶ���
    LCD_A0_low();			//ָ��
    LCD_RW_high();			//��
    //delay_us(1);
    //GPIOPadConfigSet(g_port, LCD_DATA, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD); /*  PG0-PG7����Ƭѡ�ܽ�Ϊ������2MA���*/
    //GPIOPinTypeGPIOOutput(g_port,LCD_DATA);	 //���������
    GPIO_Write(LCD_PORTC,0xff);
}






/*
void main(void)
{  
    rst=1;
    SED1520_init();                     //��ʼ��Һ����ʾ������
    while(1)
    {   
        exsample();                     //��ʾ����
    }
}
void exsample(void)                     //��ʾ����
{
    uint16 i;
//0.��ʾǰ��׼��,��LCDҺ����ʾȫ�����
    //CharImageReverse=0;                 //���Թر�
    lcdfill(0);                         //����

//1.ͼƬ����: ��(5,0)λ����ʾ32����SUNMANͼ��
    PrintfStr(0,0,"123",0);
    cursor_disp(0,0,1);
	PrintfStr(0,1,"123",0);
	PrintfStr(4,0,"123",0);
    putstr(61,0,"123",0);
    putstr(85,0,"123",0);
    
   // putstr(3,0," ",1);

    for(i=0;i<2;i++)
    {
         putimage(3,8,Img_cursor8_3);
         exdelay();
         putstr(3,0,"123",0);
        //line(3,15,11,15,1);
        //line(3,14,11,14,1);
        
        
        putimage(3,8,Img_cursor8_3r);
        exdelay();
        putstr(3,0,"123",0);
        //line(3,15,11,15,0);
        //line(3,14,11,14,0);
        
        
    }
    for(i=0;i<2;i++)
    {
        line(3+8,15,11+8,15,1);
        line(3+8,14,11+8,14,1);
        exdelay();
        line(3+8,15,11+8,15,0);
        line(3+8,14,11+8,14,0);
        exdelay();
    }

    //putimage(5,0,Img_sunman_32);            //д���ݵ���ǰLCDRAM��ַ��
    exdelay();                          //��ʱԼ600mS

//2.�ַ�������: ��(53,0)λ����ʾ"SUNMAN"�ַ���.
	putstr(53,0,"̫������ ����",0);
    //putstr(3,0,"SUNMAN123abc",0);
    //putstr(0,0,"SUNMAN456",0);
    exdelay();                          //��ʱԼ600mS

//3.�ַ�������: ��(37,16)λ����ʾ"̫���˵���"�ַ���.
    putstr(37,16,"̫���˵���",0);
    exdelay();                          //��ʱԼ600mS

//4.���Բ���: ��(37,16)λ�÷���"̫���˵���"�ַ���.
    //CharImageReverse=1;
    putstr(37,16,"̫���˵���",1);
    //CharImageReverse=0;
    exdelay();                          //��ʱԼ600mS

//5.��ͼ����: RECT(6,0)-(116,15),������.
    lcdfill(0);                         //����
    putstr(37,0,"SUNMAN",0);
    rect(6,0,116,15,1);
    exdelay();                          //��ʱԼ600mS

//6.��ͼ����: POINT(6,18),����.

    point(6,18,1);
    exdelay();                          //��ʱԼ600mS

//7.��ͼ����: LINE(6,18)-(61,30),����.
    line(6,18,61,30,1);
    exdelay();                          //��ʱԼ600mS

//8.��ͼ����: lineto(116,18),����.
    lineto(116,18,1);
    exdelay();                          //��ʱԼ600mS

//9.��ͼ����: lineto(6,18),����.
    lineto(6,18,1);
    exdelay();                          //��ʱԼ600mS

//13.ȫ������: ���������ȫ����ʾ.
    lcdfill(0xff);                      //ȫ��
    exdelay();                          //��ʱԼ600mS

}
void exdelay(void)                      //��ʾ��ʱ�ӳ���
{ uint8 i,j,k;                  //��ʱԼ600mS
  for(i=0;i<60;i++)
    for(j=0;j<64;j++)
      for(k=0;k<51;k++);
}
*/
//-------------------------------------------------------------------------------
//����putcharΪ�ַ�����Ļ����ӳ���,putstrΪ�ַ�����������ӳ���,getchinesecodepos,
//getenglishcodeposΪ�ַ�����ĸ����ӳ���.
//-------------------------------------------------------------------------------
//�ӳ�������:void putchar(uint16 c).
//����:��(XPOS,YPOS)λ��д�����ַ�����,��c>128 ��ʾΪ�����ַ�,����Ϊ�����ַ�
//�޸�����:2009.8.18
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void putchar(uint16 c)            //��λд�ַ��ӳ���
{   if(c>128)
        putsizeimage(CHINESECHARSIZE,CHINESECHARSIZE,getchinesecodepos(c));
    else
        putsizeimage(ENGLISHCHARSIZE,CHINESECHARSIZE,getenglishcodepos(c));
}
//-------------------------------------------------------------------------------
//ASCII(8*16) �� ����(16*16) ����ַ�����ʾ����
//x,y��ʾ�ַ��������Ͻ�xy����.x..1��һ�ֽ�λ��; y..һ��ɨ���߶�λ
//�ӳ�������:void putstr(uint8 code *s).
//����:д�ַ�������,��*s=0 ��ʾ�ַ�������.
//	*s...�ַ���ָ�룬��������ָ����flash�ִ�
//  CharReverse Ϊ��д
//�޸�����:2013.4.27
//�޸���:lqm_8
//-------------------------------------------------------------------------------

void putstr(uint8 x,uint8 y,uint8 *s,uint8 CharReverse)      //��ʾ�ַ����ӳ���,�ַ���Ϊ0ʱ�˳�
{   
    uint16 c;
	XPOS=x;
	YPOS=y;
	CharImageReverse=CharReverse;
    while(1)
    {   
        c=*s;
        s++;
        if(c==0) break;
        if(c<128)
            putchar(c);
        else
        {   putchar(c*256+*s);
            s++;
        }
    }
}
//=============================================================================
//  ASCII(8*16) �� ����(16*16) ����ַ�����ʾ����
//  �������Լ����
//	x,y��ʾ�ַ��������Ͻ�xy����.x..8��һ�ֽ�λ��; y..һ��ɨ���߶�λ
//	*s...�ַ���ָ�룬��������ָ����flash�ִ�
//  CharReverse Ϊ��д
//�޸�����:2013.4.27
//�޸���:lqm_8
//==============================================================================
void PrintfStr(uint8 x,uint8 y,uint8 *s,uint8 CharReverse)
{
	x=x*8;
	y=y*16;
	putstr(x,y,s,CharReverse);
}
//-------------------------------------------------------------------------------
//�ӳ�������:uint8 code *getchinesecodepos(uint8 ac).
//����:���ݵ�ǰ�����ַ���������õ���ǰ�����ַ�����ֿ����λ��.
//�޸�����:2013.4.27
//�޸���:lqm_8
//-------------------------------------------------------------------------------

uint8 const *getchinesecodepos(uint16 ac)
{   
    uint16 j;
    for(j=0;j<sizeof(ChineseCode)/sizeof(ChineseCode[0]);j++)	// ���Ҷ�λ
//sizeof������Ա������ͳ��ȣ�����ռ�ֽ���������ʽsizeof�� �������� ��
//���磺��������int��ռ�ֽ��� ��sizeof�� int ������ʾ�����4
    {
        if(ac == ChineseCode[j])
        {
            break;
        }
            
    } 
    return ChineseCharDot+j*CHINESECHARDOTSIZE;
}

//-------------------------------------------------------------------------------
//�ӳ�������:uint8 code *getenglishcodepos(uint8 ac).
//����:���ݵ�ǰASCII�ַ���������õ���ǰASCII�ַ�����ֿ����λ��.
//�޸�����:2013.4.27
//�޸���:lqm_8
//-------------------------------------------------------------------------------

uint8 const  *getenglishcodepos(uint8 ac)
{   

    uint16 j;
    for(j=0;j<sizeof(EnglishCode)/sizeof(EnglishCode[0]);j++)	// ���Ҷ�λ
//sizeof������Ա������ͳ��ȣ�����ռ�ֽ���������ʽsizeof�� �������� ��
//���磺��������int��ռ�ֽ��� ��sizeof�� int ������ʾ�����4
    {
        if(ac == EnglishCode[j])
        {
            break;
        }
            
    }
    return EnglishCharDot+j*ENGLISHCHARDOTSIZE;
}

//-------------------------------------------------------------------------------
//����putsizeimageΪͼ�ζ���Ļ����ӳ���,putimageΪͼ�ζ���������ӳ���
//-------------------------------------------------------------------------------
//�ӳ�������:void putsizeimage(uint8 XSIZE,unsigned YSIZE,
//                             uint8 code *s)
//����:��(XPOS,YPOS)λ�û���XSIZE�м�YISZE�е����ͼ��*S.
//�޸�����:2013.4.27
//�޸���:lqm_8
//-------------------------------------------------------------------------------
void putsizeimage(uint8 XSIZE,uint8 YSIZE,uint8 const *s)
{  uint8 k,lx,ly,a1,a2,y,Lcd_Mask;
   k=YPOS&0x7;
   YSIZE+=k;
   y=YPOS;
   s--;
   for(lx=0;lx<XSIZE;lx++,XPOS++)
   {  for(YPOS=y,ly=k;ly<YSIZE;)
      {  uint8 p;
         a1=*s;
         s++;
         a2=*s;
         if(CharImageReverse)
         {   a1=~a1;
             a2=~a2;
         }
         for(p=0;p<k;p++)
         {  a2>>=1;
            if((a1&0x1)==1)
               a2+=0x80;
            a1>>=1;
         }
         if((k==0) && (YSIZE<ly+8))
         {   lcdpos();
             ly+=8;
             YPOS+=8;
         }
         else
         {   lcdpos();
             a1=lcdrd();
             lcdpos();
             ly+=8;
             YPOS+=8;
             Lcd_Mask=0xff;
             p=YSIZE&0x7;
             while(p>0)
             {   Lcd_Mask>>=1;
                 YPOS--;
                 p--;
             }
             p=0xff;
             while(YSIZE<ly)
             {   ly--;
                 YPOS--;
                 p<<=1;
             }
             Lcd_Mask&=p;
             a2&=Lcd_Mask;
             a2|=a1&(~Lcd_Mask);
         }
         lcdwd(a2);
      }
      if((k!=0) && (YSIZE&0x7 != 0) && (k >= YSIZE&0x7)) s--;
   }
   YPOS=y;
}
//-------------------------------------------------------------------------------
//�ӳ�������:void putimage(uint8 code *s).
//����:��(XPOS,YPOS)λ�û���XSIZE[*s]�м�YISZE[*(s+1)]�е����ͼ��[*(s+2)].
//�޸�����:2013.4.27
//�޸���:lqm_8
//-------------------------------------------------------------------------------
void putimage(uint8 x,uint8 y,uint8 const *s)    //��ʾͼ���ӳ���
{   
    uint8 XSIZE,YSIZE;
    XPOS=x;
    YPOS=y;
    XSIZE=*s;
    s++;
    YSIZE=*s;
    s++;
    putsizeimage(XSIZE,YSIZE,s);
}
//-------------------------------------------------------------------------------
//����pointΪ��ͼ�����Ļ����ӳ���,line,lineto,rectΪ��ͼ�����������ӳ���.
//-------------------------------------------------------------------------------
//�ӳ�������:void point(uint8 b).
//����:��b��������(XPOS,YPOS)λ�û��Ƶ�.
//�޸�����:2013.4.27
//�޸���:lqm_8
//-------------------------------------------------------------------------------
void point(uint8 x,uint8 y,uint8 b)
{   
    uint8 i,Lcd_Mask,j;
	XPOS=x;
    YPOS=y;
    Lcd_Mask=0x01;
    i=YPOS&0x7;
    while(i>0)
    {   Lcd_Mask<<=1;
        i--;
    }
    lcdpos();
    j=lcdrd();
    lcdpos();
    if(b)
        lcdwd(j|Lcd_Mask);
    else
        lcdwd(j&(~Lcd_Mask));
}
//-------------------------------------------------------------------------------
//�ӳ�������:void line(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 b)
//����:��b�����ݻ���(x0,y0)-(x1,y1)��ֱ��
//�޸�����:2013.4.27
//�޸���:lqm_8
//-------------------------------------------------------------------------------
void line(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 b)
{   uint8 dx,dy;
    uint16 dk;
    XPOS=x0;
    YPOS=y0;
    point(XPOS,YPOS,b);
    dx=(x1>=x0)?x1-x0:x0-x1;
    dy=(y1>=y0)?y1-y0:y0-y1;
    if(dx==dy)
    {   while(XPOS!=x1)
        {   if(x1>x0) XPOS++;else XPOS--;
            if(y1>y0) YPOS++;else YPOS--;
            point(XPOS,YPOS,b);
        }
    }
    else if (dx>dy)
    {   dk=dy;
        dy=0;
        while(XPOS!=x1)
        {   if(x1>x0) XPOS++;else XPOS--;
            dy++;
            if(y1>y0) YPOS=y0+(dk*dy+dx/2)/dx;else YPOS=y0-(dk*dy+dx/2)/dx;
            point(XPOS,YPOS,b);
        }
    }
    else
    {   dk=dx;
        dx=0;
        while(YPOS!=y1)
        {   if(y1>y0) YPOS++;else YPOS--;
            dx++;
            if(x1>x0) XPOS=x0+(dk*dx+dy/2)/dy;else XPOS=x0-(dk*dx+dy/2)/dy;
            point(XPOS,YPOS,b);
        }
    }
}
//=============================================================================
//  ��ʾ���
//  �������Լ����
//	x,y��ʾ�ַ��������Ͻ�xy����.x..8��һ�ֽ�λ��; y..һ��ɨ���߶�λ
//	*s...�ַ���ָ�룬��������ָ����flash�ִ�
//  b Ϊ��д
//�޸�����:2013.4.27
//�޸���:lqm_8
//==============================================================================
void cursor_disp(uint8 x,uint8 y,uint8 b)
{
	x=x*8;
	y=y*16+14;   
	line(x,y,x+6,y,b);
	line(x,y+1,x+6,y+1,b);
}
/*
void cursor_on (uint8 x,uint8 y)//����ƻ�һ��λ
{

}
void cursor_off (uint8 x,uint8 y)//����ƻ�һ��λ
{

}
*/
//-------------------------------------------------------------------------------
//�ӳ�������:void lineto(uint8 x1,uint8 y1,uint8 b)
//����:��b�����ݻ���(XPOS,YPOS)-(x1,y1)��ֱ��
//�޸�����:2013.4.27
//�޸���:lqm_8
//-------------------------------------------------------------------------------
void lineto(uint8 x1,uint8 y1,uint8 b)//����(XPOS,YPOS)-(X1,Y1)��ֱ��
{   line(XPOS,YPOS,x1,y1,b);
}
//-------------------------------------------------------------------------------
//�ӳ�������:void rect(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 b)
//����:��b�����ݻ���(x0,y0)-(x1,y1)�ľ���
//�޸�����:2013.4.27
//�޸���:lqm_8
//-------------------------------------------------------------------------------
void rect(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 b)
{   line(x0,y0,x1,y0,b);
    line(x1,y0,x1,y1,b);
    line(x1,y1,x0,y1,b);
    line(x0,y1,x0,y0,b);
}
//-------------------------------------------------------------------------------
//����lcdfill,lcdpos,lcdresetΪSED1520A��Ӳ���ӿڵ�12232Һ����ʾģ��Ļ����ӳ���
//-------------------------------------------------------------------------------
//�ӳ�������:void lcdfill(uint8 d).
//����:������ʾd��ʾ���ֽ�����.
//�޸�����:2013.4.27
//�޸���:lqm_8
//-------------------------------------------------------------------------------
void lcdfill(uint8 d)           //������ʾd������ֽ������ӳ���
{   uint8 j;
    for(YPOS=0;YPOS<32;YPOS+=8)         //8ҳ
    {   XPOS=0;
        lcdpos();
        for(j=0;j<61;j++)              //61��
            lcdwd1(d);                 //��ͼ������
        XPOS=61;
        lcdpos();
        for(j=0;j<61;j++)              //61��
            lcdwd2(d);                 //��ͼ������
    }
    XPOS=0;
    YPOS=0;
}
void ClearScreen(void)
{
    lcdfill(0);
}

//-------------------------------------------------------------------------------
//�ӳ�������:void lcdpos(void).
//����:���������(XPOS,YPOS)λ�ö�Ӧ���ڲ�RAM��ַ.
//�޸�����:2013.4.27
//�޸���:lqm_8
//-------------------------------------------------------------------------------
void lcdpos(void)                       //���������(XPOS,YPOS)�ڲ�RAM��ַ���ӳ���
{
   if(XPOS<61)
   {   lcdwc1(0xB8|((YPOS/8)&0x3));     //ҳ��ַ����
       lcdwc1(XPOS);                    //�е�ַ����
   }
   else
   {   lcdwc2(0xB8|((YPOS/8)&0x3));     //ҳ��ַ����
       lcdwc2(XPOS-61);                 //�е�ַ����
   }
}
//-------------------------------------------------------------------------------
//�ӳ�������:void lcdreset(void)
//����:Һ����ʾ��������ʼ��
//�޸�����:2013.4.27
//�޸���:lqm_8
//-------------------------------------------------------------------------------
void SED1520_init(void)                     //Һ����ʾ��������ʼ���ӳ���
{
    RIS_high();
    lcdwc1(0xC0);                       //������ʾ��ʼ��
    lcdwc2(0xC0);                       //������ʾ��ʼ��
    lcdwc1(0xA0);                       //����������Ϊ����
    lcdwc2(0xA0);                       //����������Ϊ����
    lcdwc1(0xA4);                       //������ʾģʽΪ������ʾ
    lcdwc2(0xA4);                       //������ʾģʽΪ������ʾ
    lcdwc1(0xA9);                       //������ʾռ�ձ�Ϊ1/32
    lcdwc2(0xA9);                       //������ʾռ�ձ�Ϊ1/32
    lcdwc1(0xAF);                       //����ʾ
    lcdwc2(0xAF);                       //����ʾ
}
//-------------------------------------------------------------------------------
//����lcdwc1,lcdwc2,lcdwd,lcdrdΪMCS51ģ����߽ӿڵ�SED1520AҺ����ʾ�������Ļ���
//�ӳ���,lcdwd1,lcdwd2,lcdrd1,lcdrd2,lcdwaitidle1,lcdwaitidle2Ϊ�ڲ��ӳ���.
//-------------------------------------------------------------------------------
//�ӳ�������:uint8 lcdrd(void).
//����:��Һ����ʾ�������ж�ͼ������.
//�޸�����:2013.4.27
//�޸���:lqm_8
//-------------------------------------------------------------------------------
uint8 lcdrd(void)
{uint8 d;
    if(XPOS<61)
    {    d=lcdrd1();
         d=lcdrd1();
    }
    else
    {    d=lcdrd2();
         d=lcdrd2();
    }
    return d;
}
//-------------------------------------------------------------------------------
//�ӳ�������:void lcdwd(uint8 d).
//����:��Һ����ʾ������дͼ������.
//�޸�����:2013.4.27
//�޸���:lqm_8
//-------------------------------------------------------------------------------
void lcdwd(uint8 d)
{   if(XPOS<61)
        lcdwd1(d);
    else
        lcdwd2(d);
}




