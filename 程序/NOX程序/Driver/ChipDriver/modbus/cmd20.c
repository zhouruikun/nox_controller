/*
版本号REV2.1

修改时间：2012/08/11
修改作者:卢启明

修改内容

1.
void ssend_prg20(pattern *ptr,uint8 control,uint8 *obuf,back20_obj *dptr)
把这个
        ptr=p+(dptr->rec_no/3);	
	      for(i=0;i<30;ptr++,i++)//pcolor++ = prg+1,就是pcolor指向prg[1]
		    {                        //pcolor++ = prg+2,就是pcolor指向prg[2]
	 	 	   *(dptr->dataptr+i*3)=(ptr->pcmd)<<8;
			   *(dptr->dataptr+1+i*3)=ptr->step;
			   *(dptr->dataptr+2+i*3)=ptr->feelers;         
		    }
			改成这个	
      for(i=0;i<30;ptr++,i++)//pcolor++ = prg+1,就是pcolor指向prg[1]
			{                        //pcolor++ = prg+2,就是pcolor指向prg[2]
			 	*(dptr->dataptr+i*3)=((ptr+dptr->rec_no)->pcmd)<<8;
				*(dptr->dataptr+1+i*3)=(ptr+dptr->rec_no)->step;
				*(dptr->dataptr+2+i*3)=(ptr+dptr->rec_no)->feelers;         
			}

2.
把这个
		ptr=p+(dptr->rec_no/3);
	    for(i=0;i<temp1;ptr++,i++)//pcolor++ = prg+1,就是pcolor指向prg[1]
	    {                        //pcolor++ = prg+2,就是pcolor指向prg[2]
	 	   *(dptr->dataptr+i*3)=(ptr->pcmd)<<8;
		   *(dptr->dataptr+1+i*3)=ptr->step;
		   *(dptr->dataptr+2+i*3)=ptr->feelers;         
	    }	
改成这个			
    for(i=0;i<temp1;ptr++,i++)//pcolor++ = prg+1,就是pcolor指向prg[1]
		{                        //pcolor++ = prg+2,就是pcolor指向prg[2]
		 	*(dptr->dataptr+i*3)=((ptr+dptr->rec_no)->pcmd)<<8;
			*(dptr->dataptr+1+i*3)=(ptr+dptr->rec_no)->step;
			*(dptr->dataptr+2+i*3)=(ptr+dptr->rec_no)->feelers;         
		}
		      
		 
					

*/

/****************************************************************************************
author     : 卢启明
description: 把ssend_prg20程序进行升级  解决了30行以上花板读取错误的问题
version    :cmd20 V2.1
date:      : 12/08/11
***************************************************************************************/

#define  cmd20_globals
#include "cmd20.h"






uint8 deci_color_op(uint16 fileno,uint16 recno)
{
    uint8 bit0;
    uint16 cno;
    bit0=0;
    if((fileno<10)&&((recno)<1000))
    {
        if(key_strt_new==0)
        {
            cno=read_para(run_no); 
            if(cno==fileno)
            {
                bit0=1;
            }
        }			 
    }
    return bit0;
}


//将240个字节40行的程序读出 prg[0][x]所在的缓冲区，
void rd_pattern(req20_obj *preq,back20_obj *pback, pattern  *pcolor)
{
  
}

//根据读命令把指定的花型从flash中中读出写入缓冲区prg[0][x]
//寄存器的内容就是文件号。

void cmd_rd_flash(void)
{
    /*
    uint16 fileno;
    uint16 recno;
    if(deci_color_op(fileno,recno))
    {
        read_from_flash(fileno,(uint8*)&prg[0]);
    }
    */
}

void init_prg(void)
{
    /*
uint16 i;
 for(i=0;i<1000;i++)
 {
  prg[0][i].feelernum=i;
  prg[0][i].steps=i;
  prg[0][i].feederno=i&0x0f;
  }*/
}

void clr_prg(void)
{
    /*
    uint16 i;
    for(i=0;i<1000;i++)
    {
        prg[0][i].feelernum=0;
    }
    */
}


uint16  cmp_prg(void)
{
   // uint16 i;
    /*
    for(i=0;i<1000;i++)
    {
        if((prg[0][i].feelernum)!=i)break;

    }
    if(i>900)i=250;
    else i=0;
    */
    return 0;
    
}

uint8 get_res(void)
{
    uint8 flag;
    init_at45();
    RTCIni(); 
    init_prg();
    //write_to_flash(5,(uint8*)&prg[0][0]);
    clr_prg();
    //read_from_flash(5,(uint8*)&prg[0][0]);
    init_prg();
    flag=cmp_prg();
    return flag;
}



/************************************************************** 
 函数说明： 总从机接收
 功能0x14       20
 把数据都接收到prg[]结构体数组中去
 把dataptr[0]..dataptr[299]符给 prg[0]...prg[99]
 	--	prg[0]|-->pcmd                dataptr[0] 
   |	      |-->step                dataptr[1]
   |	      |-->feelers             dataptr[2]
   |30		  .                       .
   |		  .                       .
   |		  .                       .
   --  prg[1d]|-->pcmd                dataptr[87]
	          |-->step                dataptr[88] 
	          |-->feelers	          dataptr[89]
			 
			 
   --  prg[1e]|-->pcmd                dataptr[90]
   |          |-->step                dataptr[91]
   |          |-->feelers             dataptr[92]
   |30		  .
   |		  .
   |		  .
   --  prg[3b]|-->pcmd                dataptr[177]
	          |-->step                dataptr[178]
	          |-->feelers			  dataptr[179] 
			 
			 
   --  prg[3c]|-->pcmd                dataptr[180]
   |          |-->step                dataptr[181]
   |	      |-->feelers             dataptr[182]
   |30	    	 .
   |			 .
   |			 .
   -- prg[59]|-->pcmd                 dataptr[267]
	         |-->step                 dataptr[268]
	         |-->feelers			  dataptr[269] 
			 
   -- prg[5a]|-->pcmd                 dataptr[270]
   |         |-->step                 dataptr[271]
   |         |-->feelers              dataptr[272]
   |		 .
   |		 .
   |10		 .
   |  prg[62]|-->pcmd                 dataptr[294]
   |         |-->step                 dataptr[295]
   |         |-->feelers			  dataptr[296] 
   -- prg[63]|-->pcmd                 dataptr[297]
	         |-->step                 dataptr[298]
	         |-->feelers			  dataptr[299] 		 		 
 因为记录长度为90，要把一般数组存入结构体数组除上3
**************************************************************/


uint8 srcv_prg20(uint8 *abuf,uint8 *outbuf)
{

    req20_obj req_20;
    uint8 temp;
    uint8 Com_Err_Start;
    if(un_pack(abuf,10)==0)//CRC校验
    {
        temp=srcv_cmd20(abuf, &req_20);
        if(temp==0)
        {	
            truck_req20_to_back20(&req_20,&back20);
            Com_Err_Start=(*(abuf+4)<<8)+*(abuf+5);
        }
        else 
        {
            err_send1(0x94,temp,outbuf);//异常发送
            Com_Err_Start=0xff;
        }		 
    }
    return Com_Err_Start;
}


/************************************************************** 
 函数说明： 总从机发送
 功能0x14        20
 1.先计出rec_len记录长度，然后确定一帧为192个字节，180为数据，
   本机地址、功能、数据长度、参考类型、文件号、记录长度
   CRC一共12个字节。所以一帧为数据180+12＝192
   如：prg[0].......prg[99]结构体数组, dataptr[0]......dataptr[299]
       prg[0]|-->pcmd               dataptr[0]
             |-->step               dataptr[1]
             |-->feelers            dataptr[2]
	   prg[1]|-->pcmd               dataptr[3]
             |-->step               dataptr[4]
             |-->feelers	        dataptr[5]
			 .                         .
			 .                         .
			 .	                       .
	  prg[99]|-->pcmd               dataptr[297]
             |-->step               dataptr[298]
             |-->feelers		    dataptr[299]
   也就是说100组结构体数组＝100*3组一般数组dataptr[300]
   prg[30]=dataptr[90]=outbuf[180]
 2.计算出以192为一帧要发几帧temp=记录长度/90,余数＝记录长度-temp*90
   把90整除的几帧发完，再发余下少于90的一帧。
**************************************************************/

uint8 ssend_prg20(pattern *ptr,uint8 control,uint8 *obuf,back20_obj *dptr)
{

    pattern *p; 
    uint8 i,num;
    uint8 temp1;
    //功能20读以prg[100]以例
    p=ptr;//将ptr指针的首地址给p
    ptr=p;//将p指针的首地址给ptr
    if(dptr->rec_len>=90)
    {
        //truck_back_20_to_back20(&back20);
        dptr->node_addr=9;     //本机地址
        dptr->fun_num=0x14;    //功能码
        dptr->data_byte=90*2+2;//90*2+2     //三组数据的长度 一组三个数据pcmd ，step，feelers
        dptr->file_len=90*2+1;//90*2+1;
        dptr->reftype=0x06;    //参考类型

        for(i=0;i<30;ptr++,i++)//pcolor++ = prg+1,就是pcolor指向prg[1]
        {                        //pcolor++ = prg+2,就是pcolor指向prg[2]
            *(dptr->dataptr+i*3)=((ptr+dptr->rec_no)->pcmd)<<8;
            *(dptr->dataptr+1+i*3)=(ptr+dptr->rec_no)->step;
            *(dptr->dataptr+2+i*3)=(ptr+dptr->rec_no)->feelers;         
        }

        ssend_cmd20(&back20,obuf);//读保持寄存器响应从机发送
        num=dptr->data_byte+5;
        //init_send(com0,dptr->data_byte+5);

        //OS_ENTER_CRITICAL();
        //uart_send(com0,UART0_BASE);
        //OS_EXIT_CRITICAL();
        //OSSemPend(uart0SemPtr,30, &err);	   // 定时20ms*15=300ms	
        //beginSend(187);//前面10个字节,数据30*3＝90组数据再*2=180个字节,两个CRC
               //10+90+2=192个字节	   	

    }//if(temp!=0)	
    else//temp=0
    {
        dptr->node_addr=9;     //本机地址
        dptr->fun_num=0x14;    //功能码
        dptr->data_byte=dptr->rec_len*2+2;     //三组数据的长度 一组三个数据pcmd ，step，feelers
        dptr->file_len=dptr->rec_len*2+1;
        dptr->reftype=0x06;    //参考类型		
        temp1=dptr->rec_len/3;  

        for(i=0;i<temp1;ptr++,i++)//pcolor++ = prg+1,就是pcolor指向prg[1]
        {                        //pcolor++ = prg+2,就是pcolor指向prg[2]
            *(dptr->dataptr+i*3)=((ptr+dptr->rec_no)->pcmd)<<8;
            *(dptr->dataptr+1+i*3)=(ptr+dptr->rec_no)->step;
            *(dptr->dataptr+2+i*3)=(ptr+dptr->rec_no)->feelers;         
        }

        ssend_cmd20(&back20,obuf);//读保持寄存器响应从机发送
        num=dptr->data_byte+5;
        //init_send(com0,dptr->data_byte+5);

        //OS_ENTER_CRITICAL();
        //uart_send(com0,UART0_BASE);
        //OS_EXIT_CRITICAL();
        //OSSemPend(uart0SemPtr,30, &err);	   // 定时20ms*15=300ms
        //beginSend(dptr->rec_len*2+7);
    } 
    return num;
   
}





/************************************************************** 
 函数说明：从机接收 也就是从prg[0-99]读取数据发给主机
 功能0x14        20
 接收到的为读取数据命令，
 如：先从flash那里读取几号花板的数据，存入prg[0-99]中，然后发
 送给主机。
 pattern1为花板号，发送几号花板是由pattren1定
 就是把主机几号花板的所有数据传给控制箱花板号的所有数据
**************************************************************/

uint8 read_prg_from_flash(void)
{
    uint8 *inbuf,*outbuf,num;
    uint8 pattren1;  
    inbuf=get_inbuf(&com2);
    outbuf=get_outbuf(&com2);
    
    //if(get_end_rec(2,com2.rxbuf)==1)//串口接收完成标志位
    {
        pattren1=srcv_prg20(inbuf,outbuf);//从机接收
    }
    if(pattren1!=0xff)
    { 

        //read_from_flash(pattren1,(uint8*)&prg[0][0]);//读flash的数据到prg[]
        //init_prg(); 
        num=ssend_prg20(&prg[0][0],pattren1,outbuf,&back20);//从机发送
        //Start_USART_DMASend(USART2,outbuf,num);
        //Com_Err_Start=0;		
    }  
    else
    {
   // Com_Err_Start=1;
    }
    return num;
}








