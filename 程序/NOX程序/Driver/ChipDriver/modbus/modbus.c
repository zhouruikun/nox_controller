#define modbusStruct_globals
#define modbus_globals
#define CRC_globals
#include "stm32f10x.h"
#include "datatype.h"
#include "CRC.h"

#include "dma.h"
#include "cmd21.h"
#include "cmd20.h"
#include "para.h"
#include "cmd03.h"
#include "cmd06.h"
#include "modbus.h"
/************************************************************** 
 ����˵���� 
  ��������������������������������������������������������
| ��ַ     ������     ����  �������ټ���   CRC��   CRC��|
 --------------------------------------------------------
|        |         |        |         |         |       |                                                                           |
---------------------------------------------------------
**************************************************************/
void pack(uint8  *bufptr,uint8 bt)//���
{
	uint8 temph,templ;
	uint16 zhi;
	uint8 *buf1;
    zhi=crc16(bufptr, bt);
    temph=(zhi&0xff00)>>8;
    templ=zhi&0xff;
    buf1=bufptr;
    *(buf1+bt)=temph;//��λ��ǰ
    *(buf1+bt+1)=templ;
}
/************************************************************** 
 ����˵���� 
 �ж�CRCУ���Ƿ���ȷ��err=0ʱУ����ȷ��err=1ʱУ�����
 ����errֵ,shuָУ��λ�ڵڼ�λ                                                                        |
---------------------------------------------------------
**************************************************************/

uint8 un_pack(uint8 *bufptr,uint8 by)
{
    uint8 err;
    uint16 j;
    j=crc16(bufptr,by);
    if(j== (bufptr[by+1]+((bufptr[by])<<8)))
    {
        err=0;
    }
    else
    {
        err=1;
    }
    return err;
    
}
/************************************************************** 
 ����˵���� �����쳣���� ��
 cmd�ı䲻ͬ���ܵĴ����룬oerrΪ�쳣�룬obuffΪ���ͻ�����
**************************************************************/
void err_send(uint8 cmd,uint8 oerr,uint8 *obuff)
{
    *obuff=cmd;
    *(obuff+1)=oerr;
     pack(obuff,2);
}

/************************************************************** 
 ����˵���� 
 ��para[]��ֵ��back03�Ľṹ��                                                                  |
---------------------------------------------------------
**************************************************************/
/*
void para_rd(back03_obj *dptr)//�������Ĵ���ֵ
{
    uint8 shu=0,i=0;
    shu=dptr->bytelen>>1;
    for(i=0;i<shu;i++)
    {
       dptr->para_1[i]=para[dptr->data_addr2+i];
    }
}
*/
/************************************************************** 
 ����˵���� ���� 0x03  ���սṹ�����ͽṹ�崫����
**************************************************************/

uint8 truck_req_to_back(req03_obj *dptr,back03_obj *pin)
{
     uint8 j;
     pin->node_addr=dptr->node_addr;//������ַ
     pin->cmd=dptr->cmd;//����
     pin->data_addr2=dptr->data_addrl;
     j=dptr->data_len;
     pin->bytelen=j<<1;//�ֽ���
     return pin->bytelen;
}


/************************************************************** 
 ����˵���� ��������
 �ṹ���������ݻ�����д��
node_addr--->outbuf[0]                  ��ַ
cmd--->outbuf[1]                        ������
data_addr1--->outbuf[2]��+outbuf[3]��   �Ĵ�����ַ
data_len--->outbuf[4]��+inbuf[5]��      �Ĵ���ֵ 
���ܴ���:  0x03      �����ּĴ���
 ��������������������������������������������������������
| ��ַ     ������      ��ַ     ����                    |
 --------------------------------------------------------
|        |         |        |         |         |       |                                                                           |
---------------------------------------------------------
**************************************************************/
#ifdef  mreq_cmd03
void mreq_cmd03(uint8  *obuf,  req03_obj *dptr)
{
    obuf[0]=dptr->node_addr;//��ַ
    obuf[1]=dptr->cmd;//����
    obuf[2]=(dptr->data_addrl & 0xff00)>>8;//�Ĵ�����ַ
    obuf[3]=(dptr->data_addrl & 0xff);
    obuf[4]=(dptr->data_len & 0xff00)>>8;//�Ĵ���ֵ
    obuf[5]=(dptr->data_len & 0xff);
    pack(obuf,6);
     beginSend(8);
}
#endif
/*
�ӻ����գ�

���жϹ����룬�Ĵ�������(�û��Լ���Ҫ���٣���������ܳ���125��125*2=250���ֽ�����
250+3���ֽ�=253,3���ֽڱ��Ǳ�����ַ�������롢�ֽ�����253+2(CRC)=255),
������ַ(�û��Լ��������������0��ʼ)+�Ĵ�������������쳣���򷵻ز��ͳ��쳣�룬
��������
�򽫻���������������ṹ�����С�

�ѽ������ݻ�����
inbuf[0]--->node_addr                ��ַ
inbuf[1]--->cmd                      ������
inbuf[2]��+inbuf[3]��--->data_addrl  �Ĵ�����ַ
inbuf[4]��+inbuf[5]��--->data_len    �Ĵ�������(��λ����λ��һ����)
���ܴ���:  0x03      �����ּĴ���
 ��������������������������������������������������������
| ��ַ     ������   ��ʼ��ַ �Ĵ������  CRC��   CRC��   |
 --------------------------------------------------------
|        |         |        |         |         |        |                                                                           |
---------------------------------------------------------*/
uint8 srcv_cmd03(uint8 *buff, req03_obj *dptr)//�����ּĴ�������
{
	 uint16 temph,templ,j;
     uint8 Com_Err_Start;
     if(buff[1]==0x03)//����
     {
        j=((buff[5]&0x00ff)+(buff[4]<<8));
        if(j<=125)//�Ĵ�������=����������125*2+3+2=255
        {
           if(((buff[3])+(buff[2]<<8))<=0xffff)//�Ĵ�������+��ʼ��ַ
           {
                dptr->node_addr=buff[0];//��ַ
   				 dptr->cmd=buff[1];//����
   				 temph=(buff[2])<<8;
   				 templ=buff[3];
   				 dptr->data_addrl=temph+templ;//������ַ
   				 temph=(buff[4])<<8;
   				 templ=buff[5];
   				 dptr->data_len=temph+templ;//����
                 Com_Err_Start=0;//����
           }
           else
           {
               Com_Err_Start=2;//��ʼ��+�Ĵ��������쳣
           }
        }
        else
        {
           Com_Err_Start=3;//�Ĵ��������쳣
        }
     }
     else
     {
        Com_Err_Start=1;//�����쳣
     }
     	
     return Com_Err_Start;
}

/*�ӻ����ͣ�
�ṹ���������ݻ�����д��
node_addr--->outbuf[0]                 ��ַ
cmd--->outbuf[1]                       ������
bytelen--->outbuf[2]                   �ֽ���
*dataptr--->outbuf[3]                   �Ĵ���ֵ
*(dataptr+1)--->outbuf[3+1]
             .
             .
             .
�ӵ�bytelen�ֽ���
���ܴ���:  0x03      �����ּĴ���
�����ַ0x0000,  �Ĵ���ֵ��ַ����ʼ��ַ+�Ĵ������=0+1=1
 ��������������������������������������������������������
| ��ַ     ������    �ֽ���  �Ĵ���ֵ    CRC��    CRC��  |
 --------------------------------------------------------
|        |         |        |         |         |        |                                                                           |
---------------------------------------------------------*/

void ssend_cmd03(back03_obj *dptr,uint8 *p)//�����ּĴ�����Ӧ
{
    uint8 shu,i;
    p[0]=dptr->node_addr;//��ַ
    p[1]=dptr->cmd;//����
    p[2]=dptr->bytelen;//�ֽ���	
    dptr->zl_len=dptr->bytelen+3;//����
    shu=dptr->bytelen>>1;//�Ĵ�������
    for(i=0;i<shu;i++)
    {
        p[3+(i<<1)]=(dptr->para_1[i] & 0xff00)>>8;
        p[4+(i<<1)]=dptr->para_1[i] & 0xff;
    }
    pack(p,dptr->zl_len);
    
    //beginSend(dptr->zl_len+2);//��������
}

/************************************************************** 
 ����˵���� �������գ�
inbuf[0]--->node_addr                 ��ַ
inbuf[1]--->cmd                       ������
inbuf[2]--->bytelen                   �ֽ���
inbuf[3]--->*dataptr                  �Ĵ���ֵ
inbuf[3+1]--->*(dataptr+1)
             .
             .
             .
�ӵ�bytelen�ֽ���
���ܴ���:  0x03      �����ּĴ���
 ��������������������������������������������������������
| ��ַ     ������      ��ַ     ����                    |
 --------------------------------------------------------
|        |         |        |         |         |       |                                                                           |
---------------------------------------------------------
**************************************************************/
#ifdef   mback_cmd03
uint8 mback_cmd03(uint8 *abuf,  back03_obj *dptr)
{
    uint8 i,temp;
    uint8 Com_Err_Start;
    if(*(abuf+1)==3)//����
    {   

        dptr->node_addr=abuf[0];//��ַ
        dptr->cmd=abuf[1];//����
        dptr->bytelen=abuf[2];//�ֽ���
        temp=dptr->bytelen>>1;
        for(i=0;i<temp;i++)
        {
           *(dptr->para_1+i)=((abuf[3+i*2]<<8)+abuf[3+1+i*2]);
        }
        Com_Err_Start=0;         
    }
    else
    {
        Com_Err_Start=1;//�����쳣
    }
     return Com_Err_Start;	 
}
#endif
/*
uint32  bit8_to_bit32(uint8 *p)
{ 
    dat.temp2[0] = *(p+3);
	dat.temp2[1] = *(p+2);
	dat.temp2[2] = *(p+1);
	dat.temp2[3] = *p;
	return dat.temp1;
}
 */
//void set_ecw_valve(uint16 para_addr,uint32 para_val)
#ifdef  para_wr16
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
/************************************************************** 
 ����˵���� ��������
 ����0x10
**************************************************************/
#ifndef mback_cmd16
uint8  mback_cmd16(cmd16_obj *dptr,uint8 *p)
{
   uint8 Com_Err_Start;
   if(*(p+1)==0x10)//����
   {
       dptr->node_addr=*p;//��ַ
       dptr->cmd=*(p+1);//������
       dptr->strat_address=(*(p+2)<<8)+(*(p+3));//��ʼ��ַ
       dptr->data_len=(*(p+4)<<8)+(*(p+5));//�Ĵ������� 
       Com_Err_Start=0;//����
   }
   else
   {
       Com_Err_Start=1;//�����쳣
   }
   return Com_Err_Start;
   
}

#endif
/*�������ͣ�
�ṹ���������ݻ�����д��
node_addr--->outbuf[0]                 ��ַ
cmd--->outbuf[1]                       ������
data_addr--->outbuf[2]��+outbuf[3]��   �Ĵ�����ַ
content--->outbuf[4]��+inbuf[5]��      �Ĵ�������

���ܴ���:  0x10      д��·�Ĵ���
 ��������������������������������������������������������
| ��ַ     ������      ��ַ     ����                    |
 --------------------------------------------------------
|        |         |        |         |         |       |      |
---------------------------------------------------------*/
#ifndef  mreq_cmd16
void mreq_cmd16(uint8 *buff, cmd16_obj *dptr){
    uint8 i;
    buff[0]=dptr->node_addr;//��ַ
    buff[1]=dptr->cmd;//����
    buff[2]=((dptr->strat_address) & 0xff00)>>8;//�Ĵ�����ַ
    buff[3]=(dptr->strat_address & 0xff);
    buff[4]=((dptr->data_len) & 0xff00)>>8;//�Ĵ�������
    buff[5]=(dptr->data_len & 0xff);   
    buff[6]=dptr->byte;
    for(i=0;i<dptr->data_len;i++)
    {
        buff[7+(i<<1)]=(dptr->dataptr[i]&0xff00)>>8;
        buff[7+1+(i<<1)]=dptr->dataptr[i]&0xff;
    }
    pack(buff,dptr->byte+7);
    //beginSend(dptr->byte+9);
}
#endif

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
#ifndef  ssend_cmd16
void ssend_cmd16(cmd16_obj *dptr,uint8 *p)//�����ּĴ�����Ӧ
{
    *p=dptr->node_addr;//��ַ
    *(p+1)=dptr->cmd;//������
    *(p+2)=(dptr->strat_address&0xff00)>>8;//��ʼ��ַ��
    *(p+3)=dptr->strat_address&0xff;//��ʼ��ַ��
    *(p+4)=(dptr->data_len&0xff00)>>8;//�Ĵ���������
    *(p+5)=dptr->data_len&0xff;//�Ĵ���������
    pack(p,6);
    dptr->data_len=8;
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
#ifndef    srcv_cmd16
uint8  srcv_cmd16(uint8 *buff, cmd16_obj *dptr)//д�����Ĵ����ӻ�����
{
    uint16 j,temp,i;
    uint8 Com_Err_Start;
    if(buff[1]==0x10)//����
    {
        j=(buff[5]+(buff[4]<<8));
        if(j>=1 && j<=0x7b)//�Ĵ�������
        {
             temp=(buff[3]+(buff[2]<<8));
             temp=j+temp;//��ʼ��ַ+�Ĵ�������
             if(temp>=1)
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
        else//�Ĵ��������쳣
        {
         Com_Err_Start=3;
        }
    }
    else //�����쳣
    {
       Com_Err_Start=1;
    }
    return Com_Err_Start;
}

#endif

/*
�ӻ����գ�
��inbuf��struct����

���жϹ����룬�Ĵ���ֵ,�Ĵ�����ַ������쳣���򷵻ز��ͳ��쳣�룬��������
�򽫻���������������ṹ�����С�


�ѽ������ݻ�����
inbuf[0]--->node_addr                ��ַ
inbuf[1]--->cmd                     ������
inbuf[2]��+inbuf[3]��--->data_addr  �Ĵ�����ַ
inbuf[4]��+inbuf[5]��--->content    �Ĵ���ֵ
���ܴ���:  0x06      д��·�Ĵ���
 ��������������������������������������������������������
|������ַ ������ �Ĵ�����ַ �Ĵ���ֵ   CRC��   CRC��     |
 --------------------------------------------------------
|        |       |         |         |        |          |                                                                           |
--------------------------------------------------------- */

uint8  srcv_cmd06(uint8 *buff, cmd06_obj *dptr)//д�����Ĵ����ӻ�����
{
    uint16 temph,templ;
    uint8 Com_Err_Start;
    if(buff[1]==0x06)//����
    {
     
         if(((buff[3]+(buff[2]<<8))>=0) && ((buff[3]+(buff[2]<<8))<=0xffff))//�Ĵ�����ַ
         {
             //����
             dptr->node_addr=buff[0];//��ַ
             dptr->cmd=buff[1];//����
             temph=(buff[2])<<8;
             templ=buff[3];
             dptr->data_addr=temph+templ;//�Ĵ�����ַ
             temph=(buff[4])<<8;
             templ=buff[5];
             dptr->content=temph+templ;//�Ĵ���ֵ                
             Com_Err_Start=0;//����
        }
        else
        {
             Com_Err_Start=2;//�Ĵ�����ַ
        }         

    }
    else
    {
     Com_Err_Start=1;//�����쳣
    }
    return Com_Err_Start;
}


//���Եõ����ĸ�������ַ����ŵļĴ���ֵ�Ƕ���

/*
void para_wr(cmd06_obj *dptr,uint16 *dat)//�ӻ�д�Ĵ���ֵ
{
    switch(dptr->data_addr)
    {
    case 0x4e://��
        break;
    case 0x4f://д
        break;
    default:
        dat[dptr->data_addr]=dptr->content;//
        break;
        
    }
    
}
*/
/*�ӻ����ͣ�
�ṹ���������ݻ�����д��
node_addr--->outbuf[0]                 ��ַ
cmd--->outbuf[1]                       ������
data_addr--->outbuf[2]��+outbuf[3]��   �Ĵ�����ַ
content--->outbuf[4]��+inbuf[5]��      �Ĵ���ֵ
���ܴ���:  0x06      д��·�Ĵ���
 ��������������������������������������������������������
|������ַ ������ �Ĵ�����ַ �Ĵ���ֵ   CRC��   CRC��     |
 --------------------------------------------------------
|        |       |         |         |        |          |                                                                           |
--------------------------------------------------------- */

void ssend_cmd06(cmd06_obj *dptr, uint8 *buff)//д�����Ĵ����ӻ���Ӧ
{
    buff[0]=dptr->node_addr;//��ַ
    buff[1]=dptr->cmd;//����
    buff[2]=((dptr->data_addr) & 0xff00)>>8;//�Ĵ�����ַ
    buff[3]=((dptr->data_addr) & 0xff);
    buff[4]=((dptr->content) & 0xff00)>>8;//�Ĵ���ֵ
    buff[5]=((dptr->content) & 0xff);
    dptr->zl_len=6;//���ݳ���
    pack(buff,6);
}

/************************************************************** 
 ����˵���� 03��ȡ����
**************************************************************/
/*
void rcv_modbus(uint8 *buff,uint8 *obuff,uint8 node_addr)
{
    uint8 j=0;
    //if((buff[receive_count-1]==0x0D) && (buff[receive_count])==0X0A)
    //if(receive_count>7)
    //{
            if(buff[6]==2)j=11;//16дһ������
            else if(buff[6]==4)j=13;//16д2������
            if((buff[1]==3) && (ModbusRxCount==8))//���жϹ����룬���жϽ��ո���
            {
                ModbusRxCount=0;
                if(*buff==node_addr)//������ַ
                {
                    if(un_pack(buff,6)==0)//CRCУ��
                    {
                        j=srcv_cmd03(buff, &req03);//�ӻ����ղ��ж�
                        if(j==0)//�ж������Ƿ���ȷ
                        {
                            truck_req_to_back(&req03,&back03);//�ѽṹ��req03��ֵ��back03
                            para_rd(&back03);//�ӻ����Ĵ���ֵ
                            ssend_cmd03(&back03, obuff);//�ӻ�����  
                            //Uart1_PutCharString(obuff,back03.zl_len+2);
                            Start_USART_DMASend(USART2,obuff,back03.zl_len+2);
                        }
                        else
                        {
                            err_send(0x83,j,obuff);//�쳣���� 
                        }                        
                    }
                }
            }
            else if((buff[1]==6) && (ModbusRxCount==8))
            {
                ModbusRxCount=0;
                if(*buff==node_addr)//������ַ
                {
                    if(un_pack(buff,6)==0)//CRCУ��
                    {
                         j=srcv_cmd06(buff, &cmd06);//�ӻ����ղ��ж�
                         if(j==0)//�ж������Ƿ���ȷ
                         {
                             para_wr(&cmd06,&para[0]);//�ӻ�д�Ĵ���ֵ
                             ssend_cmd06(&cmd06, obuff);//�ӻ�����                                 
                             //Uart1_PutCharString(obuff,cmd06.zl_len+2);
                             Start_USART_DMASend(USART2,obuff,cmd06.zl_len+2);
                         }
                         else
                         {
                              err_send(0x86,j,obuff);//�쳣���� 
                         }                     
                    }
                }    
            }
            else if((buff[1]==16) && (ModbusRxCount==j ))
            {
                ModbusRxCount=0;
                if(*buff==node_addr)//������ַ
                {
                    if(un_pack(buff,ModbusRxCount-2)==0)//CRCУ��
                    {

                        j=srcv_cmd16(buff, &cmd16);//�ӻ����ղ��ж�
                        if(j==0)//�ж������Ƿ���ȷ
                        {
                            para_wr16(&cmd16);//�ӻ�д�Ĵ���ֵ                              
                            ssend_cmd16(&cmd16,obuff );//�ӻ�����   
                            //Uart1_PutCharString(obuff,6+2);
                            Start_USART_DMASend(USART2,obuff,6+2);
                        }
                        else
                        {
                            err_send(0x90,j,obuff);//�쳣���� 
                        }                     
                                         
                    }
                }
            }
            else if(buff[1]==0x14)
            {
                read_prg_from_flash();
            }
            else if(buff[1]==0x15)
            {
                write_prg_to_flash();
            }
    //}    
}
*/
