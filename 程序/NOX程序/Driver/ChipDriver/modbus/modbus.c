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
 函数说明： 
  －－－－－－－－－－－－－－－－－－－－－－－－－－－－
| 地址     功能码     数据  在他们再加上   CRC高   CRC低|
 --------------------------------------------------------
|        |         |        |         |         |       |                                                                           |
---------------------------------------------------------
**************************************************************/
void pack(uint8  *bufptr,uint8 bt)//解包
{
	uint8 temph,templ;
	uint16 zhi;
	uint8 *buf1;
    zhi=crc16(bufptr, bt);
    temph=(zhi&0xff00)>>8;
    templ=zhi&0xff;
    buf1=bufptr;
    *(buf1+bt)=temph;//高位在前
    *(buf1+bt+1)=templ;
}
/************************************************************** 
 函数说明： 
 判断CRC校验是否正确，err=0时校验正确，err=1时校验错误
 返回err值,shu指校验位在第几位                                                                        |
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
 函数说明： 错误异常发送 、
 cmd改变不同功能的错误码，oerr为异常码，obuff为发送缓冲区
**************************************************************/
void err_send(uint8 cmd,uint8 oerr,uint8 *obuff)
{
    *obuff=cmd;
    *(obuff+1)=oerr;
     pack(obuff,2);
}

/************************************************************** 
 函数说明： 
 读para[]的值给back03的结构体                                                                  |
---------------------------------------------------------
**************************************************************/
/*
void para_rd(back03_obj *dptr)//主机读寄存器值
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
 函数说明： 功能 0x03  接收结构体向发送结构体传数据
**************************************************************/

uint8 truck_req_to_back(req03_obj *dptr,back03_obj *pin)
{
     uint8 j;
     pin->node_addr=dptr->node_addr;//本机地址
     pin->cmd=dptr->cmd;//功能
     pin->data_addr2=dptr->data_addrl;
     j=dptr->data_len;
     pin->bytelen=j<<1;//字节数
     return pin->bytelen;
}


/************************************************************** 
 函数说明： 主机发送
 结构体向发送数据缓冲区写数
node_addr--->outbuf[0]                  地址
cmd--->outbuf[1]                        功能码
data_addr1--->outbuf[2]高+outbuf[3]低   寄存器地址
data_len--->outbuf[4]高+inbuf[5]低      寄存器值 
功能代码:  0x03      读保持寄存器
 －－－－－－－－－－－－－－－－－－－－－－－－－－－－
| 地址     功能码      地址     数据                    |
 --------------------------------------------------------
|        |         |        |         |         |       |                                                                           |
---------------------------------------------------------
**************************************************************/
#ifdef  mreq_cmd03
void mreq_cmd03(uint8  *obuf,  req03_obj *dptr)
{
    obuf[0]=dptr->node_addr;//地址
    obuf[1]=dptr->cmd;//功能
    obuf[2]=(dptr->data_addrl & 0xff00)>>8;//寄存器地址
    obuf[3]=(dptr->data_addrl & 0xff);
    obuf[4]=(dptr->data_len & 0xff00)>>8;//寄存器值
    obuf[5]=(dptr->data_len & 0xff);
    pack(obuf,6);
     beginSend(8);
}
#endif
/*
从机接收：

先判断功能码，寄存器数量(用户自己订要多少，反正最大不能超过125，125*2=250个字节数，
250+3个字节=253,3个字节别是本机地址、功能码、字节数。253+2(CRC)=255),
起启地址(用户自己订，我们这里从0开始)+寄存器数量，如果异常，则返回并送出异常码，
若正常，
则将缓冲区的内容送入结构变量中。

把接受数据缓冲区
inbuf[0]--->node_addr                地址
inbuf[1]--->cmd                      功能码
inbuf[2]高+inbuf[3]低--->data_addrl  寄存器地址
inbuf[4]高+inbuf[5]低--->data_len    寄存器数量(高位，低位算一个数)
功能代码:  0x03      读保持寄存器
 －－－－－－－－－－－－－－－－－－－－－－－－－－－－
| 地址     功能码   起始地址 寄存器编号  CRC高   CRC低   |
 --------------------------------------------------------
|        |         |        |         |         |        |                                                                           |
---------------------------------------------------------*/
uint8 srcv_cmd03(uint8 *buff, req03_obj *dptr)//读保持寄存器请求
{
	 uint16 temph,templ,j;
     uint8 Com_Err_Start;
     if(buff[1]==0x03)//功能
     {
        j=((buff[5]&0x00ff)+(buff[4]<<8));
        if(j<=125)//寄存器数量=长度主机定125*2+3+2=255
        {
           if(((buff[3])+(buff[2]<<8))<=0xffff)//寄存器数量+起始地址
           {
                dptr->node_addr=buff[0];//地址
   				 dptr->cmd=buff[1];//功能
   				 temph=(buff[2])<<8;
   				 templ=buff[3];
   				 dptr->data_addrl=temph+templ;//参数地址
   				 temph=(buff[4])<<8;
   				 templ=buff[5];
   				 dptr->data_len=temph+templ;//数据
                 Com_Err_Start=0;//正常
           }
           else
           {
               Com_Err_Start=2;//起始码+寄存器数量异常
           }
        }
        else
        {
           Com_Err_Start=3;//寄存器数量异常
        }
     }
     else
     {
        Com_Err_Start=1;//功能异常
     }
     	
     return Com_Err_Start;
}

/*从机发送：
结构体向发送数据缓冲区写数
node_addr--->outbuf[0]                 地址
cmd--->outbuf[1]                       功能码
bytelen--->outbuf[2]                   字节数
*dataptr--->outbuf[3]                   寄存器值
*(dataptr+1)--->outbuf[3+1]
             .
             .
             .
加到bytelen字节数
功能代码:  0x03      读保持寄存器
如起地址0x0000,  寄存器值地址＝起始地址+寄存器编号=0+1=1
 －－－－－－－－－－－－－－－－－－－－－－－－－－－－
| 地址     功能码    字节数  寄存器值    CRC高    CRC低  |
 --------------------------------------------------------
|        |         |        |         |         |        |                                                                           |
---------------------------------------------------------*/

void ssend_cmd03(back03_obj *dptr,uint8 *p)//读保持寄存器响应
{
    uint8 shu,i;
    p[0]=dptr->node_addr;//地址
    p[1]=dptr->cmd;//功能
    p[2]=dptr->bytelen;//字节数	
    dptr->zl_len=dptr->bytelen+3;//长度
    shu=dptr->bytelen>>1;//寄存器数量
    for(i=0;i<shu;i++)
    {
        p[3+(i<<1)]=(dptr->para_1[i] & 0xff00)>>8;
        p[4+(i<<1)]=dptr->para_1[i] & 0xff;
    }
    pack(p,dptr->zl_len);
    
    //beginSend(dptr->zl_len+2);//发送数据
}

/************************************************************** 
 函数说明： 主机接收：
inbuf[0]--->node_addr                 地址
inbuf[1]--->cmd                       功能码
inbuf[2]--->bytelen                   字节数
inbuf[3]--->*dataptr                  寄存器值
inbuf[3+1]--->*(dataptr+1)
             .
             .
             .
加到bytelen字节数
功能代码:  0x03      读保持寄存器
 －－－－－－－－－－－－－－－－－－－－－－－－－－－－
| 地址     功能码      地址     数据                    |
 --------------------------------------------------------
|        |         |        |         |         |       |                                                                           |
---------------------------------------------------------
**************************************************************/
#ifdef   mback_cmd03
uint8 mback_cmd03(uint8 *abuf,  back03_obj *dptr)
{
    uint8 i,temp;
    uint8 Com_Err_Start;
    if(*(abuf+1)==3)//功能
    {   

        dptr->node_addr=abuf[0];//地址
        dptr->cmd=abuf[1];//功能
        dptr->bytelen=abuf[2];//字节数
        temp=dptr->bytelen>>1;
        for(i=0;i<temp;i++)
        {
           *(dptr->para_1+i)=((abuf[3+i*2]<<8)+abuf[3+1+i*2]);
        }
        Com_Err_Start=0;         
    }
    else
    {
        Com_Err_Start=1;//功能异常
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
/************************************************************** 
 函数说明： 主机接收
 功能0x10
**************************************************************/
#ifndef mback_cmd16
uint8  mback_cmd16(cmd16_obj *dptr,uint8 *p)
{
   uint8 Com_Err_Start;
   if(*(p+1)==0x10)//功能
   {
       dptr->node_addr=*p;//地址
       dptr->cmd=*(p+1);//功能码
       dptr->strat_address=(*(p+2)<<8)+(*(p+3));//起始地址
       dptr->data_len=(*(p+4)<<8)+(*(p+5));//寄存器数量 
       Com_Err_Start=0;//正常
   }
   else
   {
       Com_Err_Start=1;//功能异常
   }
   return Com_Err_Start;
   
}

#endif
/*主机发送：
结构体向发送数据缓冲区写数
node_addr--->outbuf[0]                 地址
cmd--->outbuf[1]                       功能码
data_addr--->outbuf[2]高+outbuf[3]低   寄存器地址
content--->outbuf[4]高+inbuf[5]低      寄存器数量

功能代码:  0x10      写单路寄存器
 －－－－－－－－－－－－－－－－－－－－－－－－－－－－
| 地址     功能码      地址     数据                    |
 --------------------------------------------------------
|        |         |        |         |         |       |      |
---------------------------------------------------------*/
#ifndef  mreq_cmd16
void mreq_cmd16(uint8 *buff, cmd16_obj *dptr){
    uint8 i;
    buff[0]=dptr->node_addr;//地址
    buff[1]=dptr->cmd;//功能
    buff[2]=((dptr->strat_address) & 0xff00)>>8;//寄存器地址
    buff[3]=(dptr->strat_address & 0xff);
    buff[4]=((dptr->data_len) & 0xff00)>>8;//寄存器数量
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
#ifndef  ssend_cmd16
void ssend_cmd16(cmd16_obj *dptr,uint8 *p)//读保持寄存器响应
{
    *p=dptr->node_addr;//地址
    *(p+1)=dptr->cmd;//功能码
    *(p+2)=(dptr->strat_address&0xff00)>>8;//起始地址高
    *(p+3)=dptr->strat_address&0xff;//起始地址低
    *(p+4)=(dptr->data_len&0xff00)>>8;//寄存器数量高
    *(p+5)=dptr->data_len&0xff;//寄存器数量低
    pack(p,6);
    dptr->data_len=8;
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
#ifndef    srcv_cmd16
uint8  srcv_cmd16(uint8 *buff, cmd16_obj *dptr)//写单个寄存器从机请求
{
    uint16 j,temp,i;
    uint8 Com_Err_Start;
    if(buff[1]==0x10)//功能
    {
        j=(buff[5]+(buff[4]<<8));
        if(j>=1 && j<=0x7b)//寄存器数量
        {
             temp=(buff[3]+(buff[2]<<8));
             temp=j+temp;//起始地址+寄存器数量
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
                 Com_Err_Start=0;//正常
             }

        }
        else//寄存器数量异常
        {
         Com_Err_Start=3;
        }
    }
    else //功能异常
    {
       Com_Err_Start=1;
    }
    return Com_Err_Start;
}

#endif

/*
从机接收：
由inbuf向struct送数

先判断功能码，寄存器值,寄存器地址，如果异常，则返回并送出异常码，若正常，
则将缓冲区的内容送入结构变量中。


把接受数据缓冲区
inbuf[0]--->node_addr                地址
inbuf[1]--->cmd                     功能码
inbuf[2]高+inbuf[3]低--->data_addr  寄存器地址
inbuf[4]高+inbuf[5]低--->content    寄存器值
功能代码:  0x06      写单路寄存器
 －－－－－－－－－－－－－－－－－－－－－－－－－－－－
|本机地址 功能码 寄存器地址 寄存器值   CRC高   CRC低     |
 --------------------------------------------------------
|        |       |         |         |        |          |                                                                           |
--------------------------------------------------------- */

uint8  srcv_cmd06(uint8 *buff, cmd06_obj *dptr)//写单个寄存器从机请求
{
    uint16 temph,templ;
    uint8 Com_Err_Start;
    if(buff[1]==0x06)//功能
    {
     
         if(((buff[3]+(buff[2]<<8))>=0) && ((buff[3]+(buff[2]<<8))<=0xffff))//寄存器地址
         {
             //处理
             dptr->node_addr=buff[0];//地址
             dptr->cmd=buff[1];//功能
             temph=(buff[2])<<8;
             templ=buff[3];
             dptr->data_addr=temph+templ;//寄存器地址
             temph=(buff[4])<<8;
             templ=buff[5];
             dptr->content=temph+templ;//寄存器值                
             Com_Err_Start=0;//正常
        }
        else
        {
             Com_Err_Start=2;//寄存器地址
        }         

    }
    else
    {
     Com_Err_Start=1;//功能异常
    }
    return Com_Err_Start;
}


//可以得到在哪个寄器地址存放着的寄存器值是多少

/*
void para_wr(cmd06_obj *dptr,uint16 *dat)//从机写寄存器值
{
    switch(dptr->data_addr)
    {
    case 0x4e://读
        break;
    case 0x4f://写
        break;
    default:
        dat[dptr->data_addr]=dptr->content;//
        break;
        
    }
    
}
*/
/*从机发送：
结构体向发送数据缓冲区写数
node_addr--->outbuf[0]                 地址
cmd--->outbuf[1]                       功能码
data_addr--->outbuf[2]高+outbuf[3]低   寄存器地址
content--->outbuf[4]高+inbuf[5]低      寄存器值
功能代码:  0x06      写单路寄存器
 －－－－－－－－－－－－－－－－－－－－－－－－－－－－
|本机地址 功能码 寄存器地址 寄存器值   CRC高   CRC低     |
 --------------------------------------------------------
|        |       |         |         |        |          |                                                                           |
--------------------------------------------------------- */

void ssend_cmd06(cmd06_obj *dptr, uint8 *buff)//写单个寄存器从机响应
{
    buff[0]=dptr->node_addr;//地址
    buff[1]=dptr->cmd;//功能
    buff[2]=((dptr->data_addr) & 0xff00)>>8;//寄存器地址
    buff[3]=((dptr->data_addr) & 0xff);
    buff[4]=((dptr->content) & 0xff00)>>8;//寄存器值
    buff[5]=((dptr->content) & 0xff);
    dptr->zl_len=6;//数据长度
    pack(buff,6);
}

/************************************************************** 
 函数说明： 03读取数据
**************************************************************/
/*
void rcv_modbus(uint8 *buff,uint8 *obuff,uint8 node_addr)
{
    uint8 j=0;
    //if((buff[receive_count-1]==0x0D) && (buff[receive_count])==0X0A)
    //if(receive_count>7)
    //{
            if(buff[6]==2)j=11;//16写一个数据
            else if(buff[6]==4)j=13;//16写2个数据
            if((buff[1]==3) && (ModbusRxCount==8))//先判断功能码，再判断接收个数
            {
                ModbusRxCount=0;
                if(*buff==node_addr)//本机地址
                {
                    if(un_pack(buff,6)==0)//CRC校验
                    {
                        j=srcv_cmd03(buff, &req03);//从机接收并判断
                        if(j==0)//判断数据是否正确
                        {
                            truck_req_to_back(&req03,&back03);//把结构体req03的值给back03
                            para_rd(&back03);//从机读寄存器值
                            ssend_cmd03(&back03, obuff);//从机发送  
                            //Uart1_PutCharString(obuff,back03.zl_len+2);
                            Start_USART_DMASend(USART2,obuff,back03.zl_len+2);
                        }
                        else
                        {
                            err_send(0x83,j,obuff);//异常发送 
                        }                        
                    }
                }
            }
            else if((buff[1]==6) && (ModbusRxCount==8))
            {
                ModbusRxCount=0;
                if(*buff==node_addr)//本机地址
                {
                    if(un_pack(buff,6)==0)//CRC校验
                    {
                         j=srcv_cmd06(buff, &cmd06);//从机接收并判断
                         if(j==0)//判断数据是否正确
                         {
                             para_wr(&cmd06,&para[0]);//从机写寄存器值
                             ssend_cmd06(&cmd06, obuff);//从机发送                                 
                             //Uart1_PutCharString(obuff,cmd06.zl_len+2);
                             Start_USART_DMASend(USART2,obuff,cmd06.zl_len+2);
                         }
                         else
                         {
                              err_send(0x86,j,obuff);//异常发送 
                         }                     
                    }
                }    
            }
            else if((buff[1]==16) && (ModbusRxCount==j ))
            {
                ModbusRxCount=0;
                if(*buff==node_addr)//本机地址
                {
                    if(un_pack(buff,ModbusRxCount-2)==0)//CRC校验
                    {

                        j=srcv_cmd16(buff, &cmd16);//从机接收并判断
                        if(j==0)//判断数据是否正确
                        {
                            para_wr16(&cmd16);//从机写寄存器值                              
                            ssend_cmd16(&cmd16,obuff );//从机发送   
                            //Uart1_PutCharString(obuff,6+2);
                            Start_USART_DMASend(USART2,obuff,6+2);
                        }
                        else
                        {
                            err_send(0x90,j,obuff);//异常发送 
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
