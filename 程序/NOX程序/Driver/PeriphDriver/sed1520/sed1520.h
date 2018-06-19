#ifndef __sed1520_H 
#define __sed1520_H



#ifdef   sed1520_globals
#define  sed1520_ext
#else
#define  sed1520_ext  extern   
#endif


//����Ϊ��ʾ����ĺ�������
sed1520_ext void LCD_I0_Config(void);

//sed1520_ext void putchar(uint16 c);           //��λд�ַ��ӳ���
sed1520_ext void putstr(uint8 x,uint8 y,uint8  *s,uint8 CharReverse);//��ʾ�ַ����ӳ���,�ַ���Ϊ0ʱ�˳�
sed1520_ext void PrintfStr(uint8 x,uint8 y,uint8 *s,uint8 CharReverse);//��ʾ�ַ�
sed1520_ext uint8 const *getchinesecodepos(uint16 ac);
sed1520_ext uint8 const *getenglishcodepos(uint8 ac);
sed1520_ext void putimage(uint8 x,uint8 y,uint8 const *s);   //��ʾͼ���ӳ���
sed1520_ext void putsizeimage(uint8 XSIZE,uint8 YSIZE,uint8 const *s);//��ʾָ����С��ͼ���ӳ���
sed1520_ext void point(uint8 x,uint8 y,uint8 b);//����
sed1520_ext void line(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 b);
sed1520_ext void cursor_disp(uint8 x,uint8 y,uint8 b);//�����ʾ
//smg12232a2_ext void cursor_on (uint8 x,uint8 y);//����ƻ�һ��λ
//smg12232a2_ext void cursor_off (uint8 x,uint8 y);//����ƻ�һ��λ
sed1520_ext void lineto(uint8 x1,uint8 y1,uint8 b);//����(XPOS,YPOS)-(X1,Y1)��ֱ��
sed1520_ext void rect(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 b);
sed1520_ext void lcdfill(uint8 d);          //������ʾd������ֽ������ӳ���
sed1520_ext void ClearScreen(void);
sed1520_ext void lcdpos(void);                      //���������(XPOS,YPOS)�ڲ�RAM��ַ���ӳ���
sed1520_ext void SED1520_init(void);                    //Һ����ʾ��������ʼ���ӳ���
sed1520_ext void setlcdvoltage(uint8 vol);   //LCD��ѹ����
sed1520_ext void lcdwd(uint8 d);            //��ͼ�������ӳ���
sed1520_ext uint8 lcdrd(void);              //��ͼ�������ӳ���
sed1520_ext void lcdwc(uint8 c);            //��ָ���ӳ���
sed1520_ext void lcdwaitidle(void);                 //æ����ӳ���
sed1520_ext void lcdwd1(uint8 d);           //��ͼ�������ӳ���
sed1520_ext uint8 lcdrd1(void);             //��ͼ�������ӳ���
sed1520_ext void lcdwc1(uint8 c);           //��ָ���ӳ���
sed1520_ext void lcdwaitidle1(void);                //æ����ӳ���
sed1520_ext void lcdwd2(uint8 d);           //��ͼ�������ӳ���
sed1520_ext uint8 lcdrd2(void);             //��ͼ�������ӳ���
sed1520_ext void lcdwc2(uint8 c);           //��ָ���ӳ���
sed1520_ext void lcdwaitidle2(void);                //æ����ӳ���





#endif
