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
//以下XPOS,YPOS变量用于指示当前操作点的位置的预定义
//用户在编写应用程序时,需按自己的实际软件程序需要来重新定义
uint8 XPOS;                     //列方向LCD点阵位置指针
uint8 YPOS;                     //行方向LCD点阵位置指针
uint8 CharImageReverse;                   //字符及图形的反显控制,0(正常显示),1(反显)

#define XDOTS   122                     //图形空间X方向大小
#define YDOTS   32                      //图形空间X方向大小
#define ENGLISHCHARSIZE    8       //英文字符X方向显示点的个数
#define CHINESECHARSIZE    16      //中文字符X方向及中英文字符Y方向显示点的个数
#define ENGLISHCHARDOTSIZE 16      //单个英文字符点阵的字节数
#define CHINESECHARDOTSIZE 32      //单个中文字符点阵的字节数


void LCD_I0_Config(void)
{ 
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LCD_RIS | LCD_E1 | LCD_E2 | LCD_RW | LCD_A0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LCD_DATA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(LCD_PORTC, &GPIO_InitStructure);
}

void LCD_DataIo_Out(void)//数据线输出
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LCD_DATA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(LCD_PORTC, &GPIO_InitStructure);	
}

void LCD_DataIo_In(void)//数据线输入
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
//子程序名称:voidlcdwaitidle1(void).
//功能:忙检测,在对液晶显示控制器操作的每一条指令之前,需检测液晶显示器是否空闲.
//修改日期:2009.09.29
//修改人:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwaitidle1(void)                 //控制器1忙检测子程序
{  
    
    
    LCD_E1_low();			//禁止
    LCD_E2_low();			//	
    //读状态
    LCD_A0_low();			//指令
    LCD_RW_high();			//读
    LCD_DataIo_Out();//数据线配制成输出
    GPIO_Write(LCD_PORTC,0XFF);
    //delay_us(1);
    LCD_Busy_In();//设置为输入
    while(1)
    {
            LCD_E1_high();		//使能主控制器
            //delay_us(1);
            if(!(GPIO_ReadInputDataBit(LCD_PORTC,LCD_Busy)&0x80))	//判忙
                    break;
            LCD_E1_low();		//禁止
            //delay_us(1);
    }
    LCD_E1_low();	
}
//-------------------------------------------------------------------------------
//子程序名称:voidlcdwaitidle2(void).
//功能:忙检测,在对液晶显示控制器操作的每一条指令之前,需检测液晶显示器是否空闲.
//修改日期:2009.09.29
//修改人:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwaitidle2(void)                 //控制器2忙检测子程序
{   
    LCD_E1_low();			//禁止
    LCD_E2_low();			//	
    //读状态
    LCD_A0_low();			//指令
    LCD_RW_high();			//读
    LCD_DataIo_Out();//数据线配制成输出
    GPIO_Write(LCD_PORTC,0XFF);
    //delay_us(1);
    LCD_Busy_In();//设置为输入
    while(1)
    {
            LCD_E2_high();		//使能从控制器
            //delay_us(1);
            if(!(GPIO_ReadInputDataBit(LCD_PORTC,LCD_Busy)&0x80))	//判忙
                    break;
            LCD_E2_high();		//禁止
            //delay_us(1);
    }
    LCD_E2_low();	
}

//-------------------------------------------------------------------------------
//子程序名称:void lcdwd1(uint8 d).
//功能:向液晶显示控制器1写图形数据.
//修改日期:2013.4.27
//修改人:lqm_8
//-------------------------------------------------------------------------------
void lcdwd1(uint8 d)
{   
    lcdwaitidle1();
    LCD_E1_low();			//禁止主控制器
    //delay_us(1);
    //写数据
    LCD_A0_high();			//数据
    LCD_RW_low();			//写
    //delay_us(1);
    LCD_E1_high();			//使能主控制器
    //delay_us(1);
    LCD_DataIo_Out();//数据线配制成输出
    GPIO_Write(LCD_PORTC,d);
    //delay_us(1);
    LCD_E1_low();			//写完后，禁止主控制器
    //delay_us(1);
    //读状态（最好写完后都回到读状态，显示稳定）
    LCD_A0_low();			//指令
    LCD_RW_high();			//读
    //delay_us(1);
    GPIO_Write(LCD_PORTC,0XFF);
}
//-------------------------------------------------------------------------------
//子程序名称:void lcdwd2(uint8 d).
//功能:向液晶显示控制器2写图形数据.
//修改日期:2009.09.29
//修改人:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwd2(uint8 d)
{   
    lcdwaitidle2();
    LCD_E2_low();			//禁止从控制器
    //delay_us(1);
    //写数据
    LCD_A0_high();			//数据
    LCD_RW_low();			//写
    //delay_us(1);
    LCD_E2_high();			//使能从控制器
    //delay_us(1);
    LCD_DataIo_Out();//数据线配制成输出
    GPIO_Write(LCD_PORTC,d);
    //delay_us(1);
    LCD_E2_low();			//写完后，禁止从控制器
    //delay_us(1);
    //读状态（最好写完后都回到读状态，显示稳定）
    LCD_A0_low();			//指令
    LCD_RW_high();			//读
    //delay_us(1);
    GPIO_Write(LCD_PORTC,0XFF);
}
//-------------------------------------------------------------------------------
//子程序名称:uint8 lcdrd1(void).
//功能:从液晶显示控制器1中读图形数据.
//修改日期:2009.09.29
//修改人:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
uint8 lcdrd1(void)              //读图形数据子程序
{  
    uint8 d;
    lcdwaitidle1();                     //检测液晶显示控制器是否空闲
    LCD_E1_low();			//禁止主控制器
    //delay_us(1);
    //读数据
    LCD_A0_high();			//数据
    LCD_RW_high();			//读
    //delay_us(1);
    LCD_E1_high();			//使能主控制器
    //delay_us(1);
    LCD_DataIo_In();//数据线输入
    d = GPIO_ReadInputData(LCD_PORTC);  
    //delay_us(1);
    LCD_E1_low();			//写完后，禁止主控制器
    //delay_us(1);
    //读状态（最好写完后都回到读状态，显示稳定）
    LCD_A0_low();			//指令
    LCD_RW_high();			//读
    //delay_us(1);
    LCD_DataIo_Out();//数据线配制成输出
    GPIO_Write(LCD_PORTC,0XFF);
    return d;
}
//-------------------------------------------------------------------------------
//子程序名称:uint8 lcdrd2(void).
//功能:从液晶显示控制器2中读图形数据.
//修改日期:2009.09.29
//修改人:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
uint8 lcdrd2(void)              //读图形数据子程序
{   
    uint8 d;
    lcdwaitidle2();                     //检测液晶显示控制器是否空闲
    LCD_E2_low();			//禁止主控制器
    //delay_us(1);
    //读数据
    LCD_A0_high();			//数据
    LCD_RW_high();			//读
    //delay_us(1);
    LCD_E2_high();			//使能主控制器
    //delay_us(1);
    LCD_DataIo_In();//数据线输入
    d = GPIO_ReadInputData(LCD_PORTC);  
    //delay_us(1);
    LCD_E2_low();			//写完后，禁止主控制器
    //delay_us(1);
    //读状态（最好写完后都回到读状态，显示稳定）
    LCD_A0_low();			//指令
    LCD_RW_high();			//读
    //delay_us(1);
    LCD_DataIo_Out();//数据线配制成输出
    GPIO_Write(LCD_PORTC,0XFF);
    return d;
}
//-------------------------------------------------------------------------------
//子程序名称:lcdwc1(uint8 c).
//功能:向液晶显示控制器1送指令.
//修改日期:2009.09.29
//修改人:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwc1(uint8 c)            //向液晶显示控制器1送指令
{   
    lcdwaitidle1();
    LCD_E1_low();			//禁止主控制器
    //delay_us(1);
    //写指令
    LCD_A0_low();			//指令
    LCD_RW_low();			//写
    //delay_us(1);
    LCD_E1_high();			//使能主控制器
    //delay_us(1);
    LCD_DataIo_Out();//数据线配制成输出
    GPIO_Write(LCD_PORTC,c);
    //delay_us(1);
    LCD_E1_low();			//写完后，禁止主控制器
    //delay_us(1);
    //读状态（最好写完后都回到读状态，显示稳定）
    LCD_A0_low();			//指令
    LCD_RW_low();			//读
    //delay_us(1);
    //GPIOPadConfigSet(g_port, LCD_DATA, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD); /*  PG0-PG7配置片选管脚为上拉，2MA输出*/
    //GPIOPinTypeGPIOOutput(g_port,LCD_DATA);	 //设置输出口
    GPIO_Write(LCD_PORTC,0xff);
}
//-------------------------------------------------------------------------------
//子程序名称:lcdwc2(uint8 c).
//功能:向液晶显示控制器2送指令.
//修改日期:2009.09.29
//修改人:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwc2(uint8 c)            //向液晶显示控制器2送指令
{   
    lcdwaitidle2();
    LCD_E2_low();			//禁止从控制器
    //delay_us(1);
    //写指令
    LCD_A0_low();			//指令
    LCD_RW_low();			//写
    //delay_us(1);
    LCD_E2_high();			//使能从控制器
    //delay_us(1);
    LCD_DataIo_Out();//数据线配制成输出
    GPIO_Write(LCD_PORTC,c);
    //delay_us(1);
    LCD_E2_low();			//写完后，禁止从控制器
    //delay_us(1);
    //读状态（最好写完后都回到读状态，显示稳定）
    LCD_A0_low();			//指令
    LCD_RW_high();			//读
    //delay_us(1);
    //GPIOPadConfigSet(g_port, LCD_DATA, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD); /*  PG0-PG7配置片选管脚为上拉，2MA输出*/
    //GPIOPinTypeGPIOOutput(g_port,LCD_DATA);	 //设置输出口
    GPIO_Write(LCD_PORTC,0xff);
}






/*
void main(void)
{  
    rst=1;
    SED1520_init();                     //初始化液晶显示控制器
    while(1)
    {   
        exsample();                     //演示程序
    }
}
void exsample(void)                     //演示程序
{
    uint16 i;
//0.演示前的准备,将LCD液晶显示全部清空
    //CharImageReverse=0;                 //反显关闭
    lcdfill(0);                         //清屏

//1.图片测试: 在(5,0)位置显示32点阵SUNMAN图标
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

    //putimage(5,0,Img_sunman_32);            //写数据到当前LCDRAM地址中
    exdelay();                          //延时约600mS

//2.字符串测试: 在(53,0)位置显示"SUNMAN"字符串.
	putstr(53,0,"太哈阳人 电子",0);
    //putstr(3,0,"SUNMAN123abc",0);
    //putstr(0,0,"SUNMAN456",0);
    exdelay();                          //延时约600mS

//3.字符串测试: 在(37,16)位置显示"太阳人电子"字符串.
    putstr(37,16,"太阳人电子",0);
    exdelay();                          //延时约600mS

//4.反显测试: 在(37,16)位置反显"太阳人电子"字符串.
    //CharImageReverse=1;
    putstr(37,16,"太阳人电子",1);
    //CharImageReverse=0;
    exdelay();                          //延时约600mS

//5.绘图测试: RECT(6,0)-(116,15),画矩形.
    lcdfill(0);                         //清屏
    putstr(37,0,"SUNMAN",0);
    rect(6,0,116,15,1);
    exdelay();                          //延时约600mS

//6.绘图测试: POINT(6,18),画点.

    point(6,18,1);
    exdelay();                          //延时约600mS

//7.绘图测试: LINE(6,18)-(61,30),画线.
    line(6,18,61,30,1);
    exdelay();                          //延时约600mS

//8.绘图测试: lineto(116,18),画线.
    lineto(116,18,1);
    exdelay();                          //延时约600mS

//9.绘图测试: lineto(6,18),画线.
    lineto(6,18,1);
    exdelay();                          //延时约600mS

//13.全屏测试: 所有坐标点全部显示.
    lcdfill(0xff);                      //全显
    exdelay();                          //延时约600mS

}
void exdelay(void)                      //演示延时子程序
{ uint8 i,j,k;                  //延时约600mS
  for(i=0;i<60;i++)
    for(j=0;j<64;j++)
      for(k=0;k<51;k++);
}
*/
//-------------------------------------------------------------------------------
//以下putchar为字符对象的基本子程序,putstr为字符对象的扩充子程序,getchinesecodepos,
//getenglishcodepos为字符对象的辅助子程序.
//-------------------------------------------------------------------------------
//子程序名称:void putchar(uint16 c).
//功能:在(XPOS,YPOS)位置写单个字符点阵,若c>128 表示为中文字符,否则为西文字符
//修改日期:2009.8.18
//修改人:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void putchar(uint16 c)            //定位写字符子程序
{   if(c>128)
        putsizeimage(CHINESECHARSIZE,CHINESECHARSIZE,getchinesecodepos(c));
    else
        putsizeimage(ENGLISHCHARSIZE,CHINESECHARSIZE,getenglishcodepos(c));
}
//-------------------------------------------------------------------------------
//ASCII(8*16) 及 汉字(16*16) 混合字符串显示函数
//x,y显示字符串的左上角xy坐标.x..1点一字节位置; y..一条扫描线定位
//子程序名称:void putstr(uint8 code *s).
//功能:写字符串点阵,若*s=0 表示字符串结束.
//	*s...字符串指针，本函数所指的是flash字串
//  CharReverse 为反写
//修改日期:2013.4.27
//修改人:lqm_8
//-------------------------------------------------------------------------------

void putstr(uint8 x,uint8 y,uint8 *s,uint8 CharReverse)      //显示字符串子程序,字符码为0时退出
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
//  ASCII(8*16) 及 汉字(16*16) 混合字符串显示函数
//  输入参数约定：
//	x,y显示字符串的左上角xy坐标.x..8点一字节位置; y..一条扫描线定位
//	*s...字符串指针，本函数所指的是flash字串
//  CharReverse 为反写
//修改日期:2013.4.27
//修改人:lqm_8
//==============================================================================
void PrintfStr(uint8 x,uint8 y,uint8 *s,uint8 CharReverse)
{
	x=x*8;
	y=y*16;
	putstr(x,y,s,CharReverse);
}
//-------------------------------------------------------------------------------
//子程序名称:uint8 code *getchinesecodepos(uint8 ac).
//功能:根据当前中文字符码查表后计算得到当前中文字符码的字库点阵位置.
//修改日期:2013.4.27
//修改人:lqm_8
//-------------------------------------------------------------------------------

uint8 const *getchinesecodepos(uint16 ac)
{   
    uint16 j;
    for(j=0;j<sizeof(ChineseCode)/sizeof(ChineseCode[0]);j++)	// 查找定位
//sizeof用与测试变量类型长度（即所占字节数），格式sizeof（ 变量类型 ）
//例如：测试整形int所占字节数 ，sizeof（ int ），显示结果：4
    {
        if(ac == ChineseCode[j])
        {
            break;
        }
            
    } 
    return ChineseCharDot+j*CHINESECHARDOTSIZE;
}

//-------------------------------------------------------------------------------
//子程序名称:uint8 code *getenglishcodepos(uint8 ac).
//功能:根据当前ASCII字符码查表后计算得到当前ASCII字符码的字库点阵位置.
//修改日期:2013.4.27
//修改人:lqm_8
//-------------------------------------------------------------------------------

uint8 const  *getenglishcodepos(uint8 ac)
{   

    uint16 j;
    for(j=0;j<sizeof(EnglishCode)/sizeof(EnglishCode[0]);j++)	// 查找定位
//sizeof用与测试变量类型长度（即所占字节数），格式sizeof（ 变量类型 ）
//例如：测试整形int所占字节数 ，sizeof（ int ），显示结果：4
    {
        if(ac == EnglishCode[j])
        {
            break;
        }
            
    }
    return EnglishCharDot+j*ENGLISHCHARDOTSIZE;
}

//-------------------------------------------------------------------------------
//以下putsizeimage为图形对象的基本子程序,putimage为图形对象的扩充子程序
//-------------------------------------------------------------------------------
//子程序名称:void putsizeimage(uint8 XSIZE,unsigned YSIZE,
//                             uint8 code *s)
//功能:在(XPOS,YPOS)位置绘制XSIZE列及YISZE行点阵的图形*S.
//修改日期:2013.4.27
//修改人:lqm_8
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
//子程序名称:void putimage(uint8 code *s).
//功能:在(XPOS,YPOS)位置绘制XSIZE[*s]列及YISZE[*(s+1)]行点阵的图形[*(s+2)].
//修改日期:2013.4.27
//修改人:lqm_8
//-------------------------------------------------------------------------------
void putimage(uint8 x,uint8 y,uint8 const *s)    //显示图形子程序
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
//以下point为绘图操作的基本子程序,line,lineto,rect为绘图操作的扩充子程序.
//-------------------------------------------------------------------------------
//子程序名称:void point(uint8 b).
//功能:按b的数据在(XPOS,YPOS)位置绘制点.
//修改日期:2013.4.27
//修改人:lqm_8
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
//子程序名称:void line(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 b)
//功能:按b的数据绘制(x0,y0)-(x1,y1)的直线
//修改日期:2013.4.27
//修改人:lqm_8
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
//  显示光标
//  输入参数约定：
//	x,y显示字符串的左上角xy坐标.x..8点一字节位置; y..一条扫描线定位
//	*s...字符串指针，本函数所指的是flash字串
//  b 为反写
//修改日期:2013.4.27
//修改人:lqm_8
//==============================================================================
void cursor_disp(uint8 x,uint8 y,uint8 b)
{
	x=x*8;
	y=y*16+14;   
	line(x,y,x+6,y,b);
	line(x,y+1,x+6,y+1,b);
}
/*
void cursor_on (uint8 x,uint8 y)//光标移回一第位
{

}
void cursor_off (uint8 x,uint8 y)//光标移回一第位
{

}
*/
//-------------------------------------------------------------------------------
//子程序名称:void lineto(uint8 x1,uint8 y1,uint8 b)
//功能:按b的数据绘制(XPOS,YPOS)-(x1,y1)的直线
//修改日期:2013.4.27
//修改人:lqm_8
//-------------------------------------------------------------------------------
void lineto(uint8 x1,uint8 y1,uint8 b)//绘制(XPOS,YPOS)-(X1,Y1)的直线
{   line(XPOS,YPOS,x1,y1,b);
}
//-------------------------------------------------------------------------------
//子程序名称:void rect(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 b)
//功能:按b的数据绘制(x0,y0)-(x1,y1)的矩形
//修改日期:2013.4.27
//修改人:lqm_8
//-------------------------------------------------------------------------------
void rect(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 b)
{   line(x0,y0,x1,y0,b);
    line(x1,y0,x1,y1,b);
    line(x1,y1,x0,y1,b);
    line(x0,y1,x0,y0,b);
}
//-------------------------------------------------------------------------------
//以下lcdfill,lcdpos,lcdreset为SED1520A型硬件接口的12232液晶显示模块的基本子程序
//-------------------------------------------------------------------------------
//子程序名称:void lcdfill(uint8 d).
//功能:整屏显示d表示的字节数据.
//修改日期:2013.4.27
//修改人:lqm_8
//-------------------------------------------------------------------------------
void lcdfill(uint8 d)           //整屏显示d代表的字节数据子程序
{   uint8 j;
    for(YPOS=0;YPOS<32;YPOS+=8)         //8页
    {   XPOS=0;
        lcdpos();
        for(j=0;j<61;j++)              //61列
            lcdwd1(d);                 //送图形数据
        XPOS=61;
        lcdpos();
        for(j=0;j<61;j++)              //61列
            lcdwd2(d);                 //送图形数据
    }
    XPOS=0;
    YPOS=0;
}
void ClearScreen(void)
{
    lcdfill(0);
}

//-------------------------------------------------------------------------------
//子程序名称:void lcdpos(void).
//功能:设置坐标点(XPOS,YPOS)位置对应的内部RAM地址.
//修改日期:2013.4.27
//修改人:lqm_8
//-------------------------------------------------------------------------------
void lcdpos(void)                       //设置坐标点(XPOS,YPOS)内部RAM地址的子程序
{
   if(XPOS<61)
   {   lcdwc1(0xB8|((YPOS/8)&0x3));     //页地址设置
       lcdwc1(XPOS);                    //列地址设置
   }
   else
   {   lcdwc2(0xB8|((YPOS/8)&0x3));     //页地址设置
       lcdwc2(XPOS-61);                 //列地址设置
   }
}
//-------------------------------------------------------------------------------
//子程序名称:void lcdreset(void)
//功能:液晶显示控制器初始化
//修改日期:2013.4.27
//修改人:lqm_8
//-------------------------------------------------------------------------------
void SED1520_init(void)                     //液晶显示控制器初始化子程序
{
    RIS_high();
    lcdwc1(0xC0);                       //设置显示初始行
    lcdwc2(0xC0);                       //设置显示初始行
    lcdwc1(0xA0);                       //设置列序方向为正向
    lcdwc2(0xA0);                       //设置列序方向为正向
    lcdwc1(0xA4);                       //设置显示模式为正常显示
    lcdwc2(0xA4);                       //设置显示模式为正常显示
    lcdwc1(0xA9);                       //设置显示占空比为1/32
    lcdwc2(0xA9);                       //设置显示占空比为1/32
    lcdwc1(0xAF);                       //开显示
    lcdwc2(0xAF);                       //开显示
}
//-------------------------------------------------------------------------------
//以下lcdwc1,lcdwc2,lcdwd,lcdrd为MCS51模拟口线接口的SED1520A液晶显示控制器的基本
//子程序,lcdwd1,lcdwd2,lcdrd1,lcdrd2,lcdwaitidle1,lcdwaitidle2为内部子程序.
//-------------------------------------------------------------------------------
//子程序名称:uint8 lcdrd(void).
//功能:从液晶显示控制器中读图形数据.
//修改日期:2013.4.27
//修改人:lqm_8
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
//子程序名称:void lcdwd(uint8 d).
//功能:向液晶显示控制器写图形数据.
//修改日期:2013.4.27
//修改人:lqm_8
//-------------------------------------------------------------------------------
void lcdwd(uint8 d)
{   if(XPOS<61)
        lcdwd1(d);
    else
        lcdwd2(d);
}




