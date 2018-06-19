

#define  cmd16_globals
#include  "cmd16.h"
//#include "config.h"


/************************************************************** 
 ����˵���� �ӻ�����
 �ṹ���������ݻ�����д��
 node_addr--->outbuf[0]                     ��ַ
 fun_num--->outbuf[1]                       ������
 strat_address&0xff00>>8--->outbuf[2]��     ��ʼ��ַ
 strat_address&0xff--->outbuf[3]��                    
 data_len&0xff00>>8--->outbuf[4]��          �Ĵ�������
 data_len&0xff--->outbuf[5]��                                          
                          һ��8�ֽ�
 ��������������������������������������������������
| ������ַ ������  ��ʼ��ַ �Ĵ�������  CRC��  CRC��|
 ---------------------------------------------------
|        |       |         |           |      |     |                                                      |
----------------------------------------------------
 ���ܴ���:  0x10   ʮ����16    д����Ĵ���
**************************************************************/
#ifdef  ssend_cmd16
void ssend_cmd16(cmd16_obj *dptr,uint8 *p)//�����ּĴ�����Ӧ
{
uint8 *outbuf;
   *p=dptr->node_addr;//��ַ
   *(p+1)=dptr->cmd;//������
   *(p+2)=(dptr->strat_address&0xff00)>>8;//��ʼ��ַ��
   *(p+3)=dptr->strat_address&0xff;//��ʼ��ַ��
   *(p+4)=(dptr->data_len&0xff00)>>8;//�Ĵ���������
   *(p+5)=dptr->data_len&0xff;//�Ĵ���������
    dptr->data_len=8;
   pack(outbuf,6);
   //beginSend(8);//��������
}
#endif
/************************************************************** 
 ����˵���� �ӻ�����  ��inbuf��struct����
 ���жϹ�����-->�ֽ���-->�ο�����-->�ļ���-->��ʼ��ַ-->��ʼ��ַ
 +�Ĵ����� ,����쳣�򷵻ز��ͳ��쳣�룬���������򽫻�����������
 ����ṹ�����С�

 inbuf[0]-->node_addr                    ������ַ
 inbuf[1]-->cmd                          ����
 inbuf[2]��+inbuf[3]��-->strat_address   ��ʼ��ַ
 inbuf[4]��+inbuf[5]��-->data_len        �Ĵ�������
 inbuf[6]-->byte                         �ֽ���
 inbuf[7]��+inbuf[8]��-->dataptr[1]      �Ĵ���ֵ
 inbuf[9]��+inbuf[10]��-->dataptr[2]
 inbuf[11]��+inbuf[12]��-->dataptr[3]
 ���ܴ���:  0x10  ʮ����16               д����Ĵ���  
                         һ��15���ֽ�     
  ��������������������������������������������������������������������
| ������ַ ������ ��ʼ��ַ �Ĵ������� �ֽ��� �Ĵ���ֵ1 2 3  CRC��  CRC�� |
 ----------------------------------------------------------------------
|        |       |        |          |      |       |  |   |      |      |                                                      |
----------------------------------------------------------------------
**************************************************************/
#ifdef    srcv_cmd16
uint8  srcv_cmd16(uint8 *buff, cmd16_obj *dptr)//д�����Ĵ����ӻ�����
{
   uint16 j,temp,i;
   uint8 Com_Err_Start;
   if(buff[1]==0x10)//����
   {
      j=(buff[5]+(buff[4]<<8));
     temp=(buff[3]+(buff[2]<<8));
     if(temp<=0xffff)//��ʼ��ַ
     {
         temp=j+temp;//��ʼ��ַ+�Ĵ�������
         if(temp>=1 && temp<=0xffff)
         {
             dptr->node_addr=buff[0];
             dptr->cmd=buff[1];
             dptr->strat_address=((buff[2]<<8)+buff[3]);
             dptr->data_len=((buff[4]<<8)+buff[5]);
             dptr->byte=*(buff+6);
             for(i=0;i<j;i++)
             {
                 *(dptr->dataptr+i)= (buff[7+i*2]<<8)+buff[7+1+i*2];
             }
             Com_Err_Start=0;//����
         }
     }
     else//��ʼ��ַ�쳣
     {
         Com_Err_Start=2;
     }
     
   }
   else //�����쳣
   {
       Com_Err_Start=1;
   }
   return Com_Err_Start;
}

#endif

#ifndef  para_wr16
/************************************************************** 
 ����˵���� ���� 16 д�ļ���¼  
 �����յ���3�����ݴ���������ȥ
 �ļ���	��¼��	��¼����	

**************************************************************/

void para_wr16(cmd16_obj *dptr)
{
   uint8 i;
   for(i=0;i<dptr->data_len;i++)
   {
       para[dptr->strat_address+i]=*(dptr->dataptr+i);
   }
}
#endif

uint8 s_cmd16(void)
{
    uint8 j,num;
    uint8 *buff;
    uint8 *obuff;
    num=0;
    buff=get_inbuf(&com1);
    obuff=get_outbuf(&com1);
    if(un_pack(buff,11)==0)//CRCУ��
    {
        
           j=srcv_cmd16(buff, &cmd16);//�ӻ����ղ��ж�
           if(j==0)//�ж������Ƿ���ȷ
           {
               para_wr16(&cmd16);//�ӻ�д�Ĵ���ֵ                              
                ssend_cmd16(&cmd16,obuff );//�ӻ�����  
                num=cmd16.data_len;               
           }
           else
           {
               err_send(0x90,j,obuff);//�쳣���� 
           }	                     
                             
    }
    return num;
}


