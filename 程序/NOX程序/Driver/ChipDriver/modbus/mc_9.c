#define mc_9_globals  1 
#include "datatype.h"
#include "mc_9.h"
#include "pattern_para.h" 


/*
 －－－－－－－－－－－－－－－－－－－－－－－－－－－－
| 地址     功能码     数据  在他们再加上   CRC高   CRC低|
 --------------------------------------------------------
|        |         |        |         |         |       |                                                                           |
---------------------------------------------------------
用于从机发发送
sizeof()计算出校验位
*/
/*
void pack(uint8  *bufptr,uint8 shu)//解包
{
	uint8 temph,templ;
	uint16 zhi;
	uint8 *buf1;
    zhi=crc16(bufptr, shu);
    temph=(zhi&0xff00)>>8;
    templ=zhi&0xff;
    buf1=bufptr;
    *(buf1+shu)=temph;
    *(buf1+shu+1)=templ;
}*/
/*
判断CRC校验是否正确，err=0时校验正确，err=1时校验错误
返回err值,shu指校验位在第几位
*/
/*
uint8 un_pack(uint8 *bufptr,uint8 shu)
{
    uint8 err;
    uint16 j;
    j=crc16(bufptr,shu);
    if(j== (bufptr[shu+1]+((bufptr[shu])<<8)))
    {
        err=0;
    }
    else
    {
        err=1;
    }
    return err;
    
}
*/
/*
错误发送
*/
/*
void start_err(combuf_obj  *combuf, com_err *dptr)
{
	combuf->outbuf[0]=dptr->oerr;//异常
}
*/

/*
错误异常发送 、
cmd改变不同功能的错误码，oerr为异常码，obuff为发送缓冲区
*/
/*
void err_send(uint8 cmd,uint8 oerr,uint8 *obuff)
{
	*obuff=cmd;
	*(obuff+1)=oerr;
	 pack(obuff,2);
}
*/

 /************************************************************** 
 函数说明： 主机接收
 功能0x14        20
**************************************************************/

uint8 mback_cmd20(uint8 *abuf,  back20_obj *dptr)
{
      uint8 i, temp;
      uint8 Com_Err_Start;
      if(*(abuf+1)==20)//功能0x15
      {
         temp=*(abuf+2);//响应数据长度
         if(temp>=7 && temp<=0xf5)
         {
             temp=*(abuf+3);//文件响应长度
             if(temp>=7 && temp<=0xf5)
             {
                  dptr->node_addr=*abuf;     //本机地址
                  dptr->fun_num=*(abuf+1);   //功能码
                  dptr->data_byte=*(abuf+2); //响应数据长度
                  dptr->file_len=*(abuf+3);  //文件响应长度
                  dptr->reftype=*(abuf+4);   //参考类型
                  temp=(dptr->file_len-1)>>1;
				  
                  for(i=0;i<temp;i++)
                  {
                      *(dptr->dataptr+i)=(*(abuf+5+i*2)<<8)+*(abuf+5+1+i*2); 
                  }
                  Com_Err_Start=0;
             }
         }
      }
      else
      {
         Com_Err_Start=1;
      }    
      return Com_Err_Start;
}

/************************************************************** 
 函数说明： 主机发送
 功能0x14        20
**************************************************************/

void  mreq_cmd20(req20_obj *dptr,  uint8 *obuf)
{
     *obuf=dptr->slave_addr;                  //地址
     *(obuf+1)=dptr->fun_num;                 //功能码
     *(obuf+2)=dptr->filebyte;                //字节数
     *(obuf+3)=dptr->reftype;                 //参考类型
     *(obuf+4)=(dptr->fileno & 0xff00)>>8;    //文件号高
     *(obuf+5)=(dptr->fileno & 0xff);         //文件号低
     *(obuf+6)=(dptr->rec_no & 0xff00)>>8;    //记录号高
     *(obuf+7)=(dptr->rec_no & 0xff);         //记录号低
     *(obuf+8)=(dptr->rec_len & 0xff00)>>8;   //记录长度高
     *(obuf+9)=(dptr->rec_len & 0xff);        //记录长度低
	 pack(obuf,10);

}

/************************************************************** 
 函数说明： 主机发送
 功能0x15        21
**************************************************************/

void  mreq_cmd21(cmd21_obj *dptr, uint8 *obuf )
{
     uint8 i;
     //uint16 temp;
     *obuf=dptr->node_addr;  //本机地址
     *(obuf+1)=dptr->fun_num;//功能码
     *(obuf+2)=dptr->data_l; //数据长度
     *(obuf+3)=dptr->reftype;//参考类型
     *(obuf+4)=(dptr->fileno & 0xff00)>>8;//文件号
     *(obuf+5)=dptr->fileno & 0xff;
     *(obuf+6)=(dptr->rec_no & 0xff00)>>8;//记录号
     *(obuf+7)=dptr->rec_no & 0xff;
     *(obuf+8)=(dptr->rec_len & 0xff00)>>8;//记录长度
     *(obuf+9)=dptr->rec_len & 0xff;
	 //temp=dptr->rec_len-1; 
     for(i=0;i<dptr->rec_len;i++)//记录数据90*2＝180
     {
         *(obuf+10+i*2)=(*(dptr->dataptr+i) & 0xff00)>>8;
         *(obuf+10+1+i*2)=*(dptr->dataptr+i) & 0xff;
     }
	 
     pack(obuf,dptr->rec_len*2+10);//90*2+10=190
}

/************************************************************** 
 函数说明： 主机接收
 功能0x15        21
**************************************************************/

uint8  mback_cmd21(cmd21_obj *dptr, uint8 *abuf )
{
   uint16 temp;
   uint8 j,i;
   uint8 Com_Err_Start;
   if(*(abuf+1)==0x15)//功能
   {
      if(*(abuf+2)>=7 && *(abuf+2)<=245)//字节数
      {
         if(*(abuf+3)==6)//参考类型
         {
            j=((*(abuf+5)+(*(abuf+4)<<8)));
            if(j<=9)//文件号
            {
               j=(*(abuf+7)+(*(abuf+6)<<8));
               //if(j<=0x270f)//记录号＝起始地址
               //{
                  temp=*(abuf+9)+(*(abuf+8)<<8);
                  if((temp+j)<=0xffff) 
                  {
                     dptr->node_addr=*(abuf+0);
                     dptr->fun_num=*(abuf+1);
                     dptr->data_l=*(abuf+2);
                     dptr->reftype=*(abuf+3);
                     dptr->fileno=((*(abuf+4)<<8)+*(abuf+5));
                     dptr->rec_no=((*(abuf+6)<<8)+*(abuf+7)); 
                     dptr->rec_len=((*(abuf+8)<<8)+*(abuf+9)); 
					      for(i=0;i<dptr->rec_len;i++)//记录长度
                     {
                         *(dptr->dataptr+i)= (abuf[10+i*2]<<8)+abuf[10+1+i*2];
                     }
                     Com_Err_Start=0;
                  } 
               //}
               //else//记录号异常
               //{
               //   Com_Err_Start=2;
               //}   
            }
            else//文件号异常
            {
               Com_Err_Start=2;
            }   
         }
         else//参考类型异常
         {
            Com_Err_Start=2;
         }
      }
      else//字节数异常
      {
         Com_Err_Start=3;
      }      
   }
   else//功能异常 
   {
      Com_Err_Start=1;
   }
   return Com_Err_Start;
}


uint8  srcv_cmd20(uint8 *buff, req20_obj *dptr)//写单个寄存器从机请求
{
   uint16 i,temp;
   uint8 Com_Err_Start,j;
   if(buff[1]==0x14)//功能
   {
      if(buff[2]>=7 && buff[2]<=245)//字节数
      {
         if(buff[3]==6)//参考类型
         {
            j=(buff[5]+(buff[4]<<8));
            if(j<=9)//文件号
            {
               j=(buff[7]+(buff[6]<<8));
               //if(j<=0x270f)//记录号＝起始地址
               //{
                  if(((buff[9]+(buff[8]<<8))+j)<=0xffff) 
                  {
                     dptr->slave_addr=buff[0];
                     dptr->fun_num=buff[1];
                     dptr->filebyte=buff[2];
					 temp=dptr->filebyte/7;
					 for(i=0;i<temp;i++)
					 {
	                     dptr->reftype=buff[3+i*7];                  //参考类型
	                     dptr->fileno=((buff[4+i*7]<<8)+buff[5+i*7]);	 //文件号
	                     dptr->rec_no=((buff[6+i*7]<<8)+buff[7+i*7]); 	 //记录号
	                     dptr->rec_len=((buff[8+i*7]<<8)+buff[9+i*7]);	 //记录长度
	                     
					}
					Com_Err_Start=0;//正常
                  } 
               //}
              // else//记录号异常
              // {
              //    Com_Err_Start=2;
              // }   
            }
            else//文件号异常
            {
               Com_Err_Start=2;
            }   
         }
         else//参考类型异常
         {
            Com_Err_Start=2;
         }
      }
      else//字节数异常
      {
         Com_Err_Start=3;
      }      
   }
   else//功能异常 
   {
      Com_Err_Start=1;
   }
   return Com_Err_Start;
}
 

void ssend_cmd20(back20_obj *dptr,uint8 *p)//读保持寄存器响应
{
   uint8 shu,j;
   *p=dptr->node_addr;//地址
   *(p+1)=dptr->fun_num;//功能码
   *(p+2)=dptr->data_byte;//响应数据长度
   *(p+3)=dptr->file_len;//文件响应长度
   *(p+4)=dptr->reftype;//参考类型
   shu=((dptr->file_len-1)>>1);
   for(j=0;j<shu;j++)
   {
       *(p+5+j*2)=(*(dptr->dataptr+j) & 0xff00)>>8;
       *(p+5+1+j*2)=*(dptr->dataptr+j) & 0xff;
   }
   pack(p,dptr->data_byte+3);//90*2+10=190
   
}

void ssend_cmd21(uint8 *buff, cmd21_obj *dptr)//写单个寄存器从机响应
{
    uint8 i;
    *(buff)=dptr->node_addr;//本机地址 
    *(buff+1)=dptr->fun_num;//功能码
    *(buff+2)=dptr->data_l;//数据长度(字节数)
    *(buff+3)=dptr->reftype;//参考类型
    *(buff+4)=((dptr->fileno & 0xff00)>>8);//文件号
    *(buff+5)=dptr->fileno &0xff;
    *(buff+6)=((dptr->rec_no & 0xff00)>>8);//记录号
    *(buff+7)=dptr->rec_no &0xff;
    *(buff+8)=((dptr->rec_len & 0xff00)>>8);//记录长度
    *(buff+9)=dptr->rec_len &0xff;
    for(i=0;i<dptr->rec_len;i++)    
    {
         *(buff+10+i*2)=(*(dptr->dataptr+i) & 0xff00)>>8;//高位
         *(buff+10+1+i*2)=*(dptr->dataptr+i)&0xff;//低位
    }
	pack(buff,dptr->rec_len*2+10);//90*2+10=190
}

/*
错误异常发送 、
cmd改变不同功能的错误码，oerr为异常码，obuff为发送缓冲区
*/

void err_send1(uint8 cmd,uint8 oerr,uint8 *obuff)
{
	*obuff=cmd;
	*(obuff+1)=oerr;
	 pack(obuff,2);
}

/************************************************************** 
 函数说明： 功能 20  接收结构体向发送结构体传数据
**************************************************************/

void truck_req20_to_back20(req20_obj *dptr,back20_obj *pin)
{
    pin->node_addr=dptr->slave_addr;
    pin->fun_num=dptr->fun_num;
    if(dptr->filebyte/7==1)//只有1组数据时
    {
       pin->data_byte=(dptr->rec_len<<1)+2;
    }
    else//多组数据
    {
    }
    //pin->data_byte=(dptr->filebyte<<1)+2;//响应数据长度
    pin->file_len=(dptr->rec_len<<1)+1;
    pin->reftype=dptr->reftype;
    pin->fileno=dptr->fileno;
    pin->rec_no=dptr->rec_no;
	 pin->rec_len=dptr->rec_len;
}


