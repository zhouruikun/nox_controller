

#define  cmd16_globals
#include  "cmd16.h"
//#include "config.h"


/************************************************************** 
 函数说明： 从机发送
 结构体向发送数据缓冲区写数
 node_addr--->outbuf[0]                     地址
 fun_num--->outbuf[1]                       功能码
 strat_address&0xff00>>8--->outbuf[2]高     起始地址
 strat_address&0xff--->outbuf[3]低                    
 data_len&0xff00>>8--->outbuf[4]高          寄存器数量
 data_len&0xff--->outbuf[5]低                                          
                          一共8字节
 －－－－－－－－－－－－－－－－－－－－－－－－－
| 本机地址 功能码  起始地址 寄存器数量  CRC高  CRC低|
 ---------------------------------------------------
|        |       |         |           |      |     |                                                      |
----------------------------------------------------
 功能代码:  0x10   十进制16    写多个寄存器
**************************************************************/
#ifdef  ssend_cmd16
void ssend_cmd16(cmd16_obj *dptr,uint8 *p)//读保持寄存器响应
{
uint8 *outbuf;
   *p=dptr->node_addr;//地址
   *(p+1)=dptr->cmd;//功能码
   *(p+2)=(dptr->strat_address&0xff00)>>8;//起始地址高
   *(p+3)=dptr->strat_address&0xff;//起始地址低
   *(p+4)=(dptr->data_len&0xff00)>>8;//寄存器数量高
   *(p+5)=dptr->data_len&0xff;//寄存器数量低
    dptr->data_len=8;
   pack(outbuf,6);
   //beginSend(8);//发送数据
}
#endif
/************************************************************** 
 函数说明： 从机接收  由inbuf向struct送数
 先判断功能码-->字节数-->参考类型-->文件号-->起始地址-->起始地址
 +寄存器数 ,如果异常则返回并送出异常码，若正常，则将缓冲区的内容
 送入结构变量中。

 inbuf[0]-->node_addr                    本机地址
 inbuf[1]-->cmd                          功能
 inbuf[2]高+inbuf[3]低-->strat_address   起始地址
 inbuf[4]高+inbuf[5]低-->data_len        寄存器数量
 inbuf[6]-->byte                         字节数
 inbuf[7]高+inbuf[8]低-->dataptr[1]      寄存器值
 inbuf[9]高+inbuf[10]低-->dataptr[2]
 inbuf[11]高+inbuf[12]低-->dataptr[3]
 功能代码:  0x10  十进制16               写多个寄存器  
                         一共15个字节     
  －－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
| 本机地址 功能码 起始地址 寄存器数量 字节数 寄存器值1 2 3  CRC高  CRC低 |
 ----------------------------------------------------------------------
|        |       |        |          |      |       |  |   |      |      |                                                      |
----------------------------------------------------------------------
**************************************************************/
#ifdef    srcv_cmd16
uint8  srcv_cmd16(uint8 *buff, cmd16_obj *dptr)//写单个寄存器从机请求
{
   uint16 j,temp,i;
   uint8 Com_Err_Start;
   if(buff[1]==0x10)//功能
   {
      j=(buff[5]+(buff[4]<<8));
     temp=(buff[3]+(buff[2]<<8));
     if(temp<=0xffff)//起始地址
     {
         temp=j+temp;//起始地址+寄存器数量
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
             Com_Err_Start=0;//正常
         }
     }
     else//起始地址异常
     {
         Com_Err_Start=2;
     }
     
   }
   else //功能异常
   {
       Com_Err_Start=1;
   }
   return Com_Err_Start;
}

#endif

#ifndef  para_wr16
/************************************************************** 
 函数说明： 功能 16 写文件记录  
 将接收到的3组数据存入数组中去
 文件号	记录号	记录长度	

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
    if(un_pack(buff,11)==0)//CRC校验
    {
        
           j=srcv_cmd16(buff, &cmd16);//从机接收并判断
           if(j==0)//判断数据是否正确
           {
               para_wr16(&cmd16);//从机写寄存器值                              
                ssend_cmd16(&cmd16,obuff );//从机发送  
                num=cmd16.data_len;               
           }
           else
           {
               err_send(0x90,j,obuff);//异常发送 
           }	                     
                             
    }
    return num;
}


