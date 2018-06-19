#ifndef __sed1520_H 
#define __sed1520_H



#ifdef   sed1520_globals
#define  sed1520_ext
#else
#define  sed1520_ext  extern   
#endif


//以下为演示程序的函数定义
sed1520_ext void LCD_I0_Config(void);

//sed1520_ext void putchar(uint16 c);           //定位写字符子程序
sed1520_ext void putstr(uint8 x,uint8 y,uint8  *s,uint8 CharReverse);//显示字符串子程序,字符码为0时退出
sed1520_ext void PrintfStr(uint8 x,uint8 y,uint8 *s,uint8 CharReverse);//显示字符
sed1520_ext uint8 const *getchinesecodepos(uint16 ac);
sed1520_ext uint8 const *getenglishcodepos(uint8 ac);
sed1520_ext void putimage(uint8 x,uint8 y,uint8 const *s);   //显示图形子程序
sed1520_ext void putsizeimage(uint8 XSIZE,uint8 YSIZE,uint8 const *s);//显示指定大小的图形子程序
sed1520_ext void point(uint8 x,uint8 y,uint8 b);//画点
sed1520_ext void line(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 b);
sed1520_ext void cursor_disp(uint8 x,uint8 y,uint8 b);//光标显示
//smg12232a2_ext void cursor_on (uint8 x,uint8 y);//光标移回一第位
//smg12232a2_ext void cursor_off (uint8 x,uint8 y);//光标移回一第位
sed1520_ext void lineto(uint8 x1,uint8 y1,uint8 b);//绘制(XPOS,YPOS)-(X1,Y1)的直线
sed1520_ext void rect(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 b);
sed1520_ext void lcdfill(uint8 d);          //整屏显示d代表的字节数据子程序
sed1520_ext void ClearScreen(void);
sed1520_ext void lcdpos(void);                      //设置坐标点(XPOS,YPOS)内部RAM地址的子程序
sed1520_ext void SED1520_init(void);                    //液晶显示控制器初始化子程序
sed1520_ext void setlcdvoltage(uint8 vol);   //LCD电压设置
sed1520_ext void lcdwd(uint8 d);            //送图形数据子程序
sed1520_ext uint8 lcdrd(void);              //读图形数据子程序
sed1520_ext void lcdwc(uint8 c);            //送指令子程序
sed1520_ext void lcdwaitidle(void);                 //忙检测子程序
sed1520_ext void lcdwd1(uint8 d);           //送图形数据子程序
sed1520_ext uint8 lcdrd1(void);             //读图形数据子程序
sed1520_ext void lcdwc1(uint8 c);           //送指令子程序
sed1520_ext void lcdwaitidle1(void);                //忙检测子程序
sed1520_ext void lcdwd2(uint8 d);           //送图形数据子程序
sed1520_ext uint8 lcdrd2(void);             //读图形数据子程序
sed1520_ext void lcdwc2(uint8 c);           //送指令子程序
sed1520_ext void lcdwaitidle2(void);                //忙检测子程序





#endif
