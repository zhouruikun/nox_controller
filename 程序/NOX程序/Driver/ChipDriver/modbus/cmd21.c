/*
版本号REV2.1

修改时间：2012/08/11
修改作者:卢启明

修改内容
1.
void ssend_prg21(pattern *ptr,uint8 *abuf,uint8 *obuf)
把这个
     *(cmd_21.dataptr+i*3)=(ptr->pcmd)<<8;
	   *(cmd_21.dataptr+1+i*3)=ptr->step;
	   *(cmd_21.dataptr+2+i*3)=ptr->feelers; 
改成这个
     *(cmd_21.dataptr+i*3)=((ptr+cmd_21.rec_no)->pcmd)<<8;
	   *(cmd_21.dataptr+1+i*3)=(ptr+cmd_21.rec_no)->step;
		 *(cmd_21.dataptr+2+i*3)=(ptr+cmd_21.rec_no)->feelers; 
		 
		 
2.
uint8 srcv_prg21(pattern *ptr,uint8 *abuf,uint8 *outbuf)
把这个	
       temp=cmd_21.rec_len/3;//记录长度
			 ptr=p+(cmd_21.rec_no)/3;//改
			 for(i=0;i<temp;ptr++,i++)//pcolor++ = prg+1,就是pcolor指向prg[1]
			 {                        //pcolor++ = prg+2,就是pcolor指向prg[2]
					ptr->pcmd=(*(cmd_21.dataptr+i*3))>>8;
					ptr->step=*(cmd_21.dataptr+1+i*3);
					ptr->feelers=*(cmd_21.dataptr+2+i*3);  

		
			 }
改成这个
       temp=cmd_21.rec_len/3;//记录长度
			 for(i=0;i<temp;ptr++,i++)//pcolor++ = prg+1,就是pcolor指向prg[1]
			 {                        //pcolor++ = prg+2,就是pcolor指向prg[2]
					(ptr+cmd_21.rec_no)->pcmd=(*(cmd_21.dataptr+i*3))>>8;
					(ptr+cmd_21.rec_no)->step=*(cmd_21.dataptr+1+i*3);
					(ptr+cmd_21.rec_no)->feelers=*(cmd_21.dataptr+2+i*3);     
			 }

*/


/****************************************************************************************
author     : 卢启明
description: 把ssend_prg21，srcv_prg21 对程序进行升级解决了30行以上花板不能存储问题
version    :cmd21 V2.1
date:      : 12/08/11
***************************************************************************************/
#define cmd21_globals
#define pattern_para_globals
#include "cmd21.h"




void cmd_ins(void)
{
    /*
    uint16 fileno;
    uint16 recno;
    if(deci_color_op(fileno,recno))
    {  
        insert(&prg[0][0],recno);
    }*/
}

void cmd_del(void)
{
    /*
    uint16 fileno;
    uint16 recno;
    if(deci_color_op(fileno,recno))
    {
        del(&prg[0][0],recno);
    }*/
}


//将240个字节40行的程序写入prg[0][x]所在的缓冲区，
void wr_pattern(cmd21_obj *pcmd, pattern *pcolor)
{
//uint16 rec_no;
//uint16 col_no;
  
//   col_no=rec_no/6;
//   wr_punit(&prg[0][0],&col_no);
}


/************************************************************** 
 函数说明： 总从机发送
 功能0x15        21
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

uint8 ssend_prg21(pattern *ptr,uint8 *abuf,uint8 *obuf)
{
    cmd21_obj cmd_21;

    uint8 i,num;
    uint8 temp1;
    //写功能21，prg[100]以例
    cmd_21.node_addr=*abuf;     //本机地址                                          改
    cmd_21.fun_num=*(abuf+1);    //功能码                                           改
    cmd_21.data_l=*(abuf+2);     //三组数据的长度 一组三个数据pcmd ，step，feelers  改
    cmd_21.reftype=*(abuf+3);    //参考类型                                         改
    cmd_21.fileno=(*(abuf+4)<<8)+*(abuf+5);  //文件号                               改
    cmd_21.rec_no=(*(abuf+6)<<8)+*(abuf+7);      //记录号prg[记录号]                改
    cmd_21.rec_len=(*(abuf+8)<<8)+*(abuf+9);      //记录长度  
    temp1=cmd_21.rec_len/3;
    for(i=0;i<temp1;ptr++,i++)//pcolor++ = prg+1,就是pcolor指向prg[1]
    {                        //pcolor++ = prg+2,就是pcolor指向prg[2]
        *(cmd_21.dataptr+i*3)=((ptr+cmd_21.rec_no)->pcmd)<<8;
        *(cmd_21.dataptr+1+i*3)=(ptr+cmd_21.rec_no)->step;
        *(cmd_21.dataptr+2+i*3)=(ptr+cmd_21.rec_no)->feelers; 
    }
    ssend_cmd21(obuf, &cmd_21);//从机发送
    num=cmd_21.rec_len*2+12;
    //init_send(com0,(cmd_21.rec_len*2+12));
    // OS_ENTER_CRITICAL();
    // uart_send(com0,UART0_BASE);
    //  OS_EXIT_CRITICAL();
    // OSSemPend(uart0SemPtr,30, &err);	   // 定时20ms*15=300ms
    //beginSend(192);//前面10个字节,数据30*3＝90组数据再*2=180个字节,两个CRC
    //10+90+2=192个字节	
    return num;
}

uint8 srcv_prg21(pattern *ptr,uint8 *abuf,uint8 *outbuf)
{
    cmd21_obj cmd_21;
    uint8 i,temp,Com_Err_Start;
    uint16 len;
    len=(*(abuf+8)<<8)+*(abuf+9);
    if(un_pack(abuf,(len*2+10))==0)//CRC校验len*2+10
    {

        len=mback_cmd21(&cmd_21,abuf);//主机接收功能21
        if(len==0)
        {
            temp=cmd_21.rec_len/3;//记录长度
            for(i=0;i<temp;ptr++,i++)//pcolor++ = prg+1,就是pcolor指向prg[1]
            {                        //pcolor++ = prg+2,就是pcolor指向prg[2]
                (ptr+cmd_21.rec_no)->pcmd=(*(cmd_21.dataptr+i*3))>>8;
                (ptr+cmd_21.rec_no)->step=*(cmd_21.dataptr+1+i*3);
                (ptr+cmd_21.rec_no)->feelers=*(cmd_21.dataptr+2+i*3);     
            }
            Com_Err_Start=(*(abuf+4)<<8)+*(abuf+5);//返回几号花板
        }
        else
        {
            err_send1(0x95,len,outbuf);//异常发送 
            Com_Err_Start=0xff;
        }	   
    }//while(ok==0)
    return Com_Err_Start;
}


/************************************************************** 
 函数说明：从机接收 也就是写入数据到prg[0-99]
 功能0x15        21
 把接收到的数据存入flash,然后发回给主机
 如：将主机prg[0-99]的数据发给从机，从机接收了prg[0-99]的数据存入
 flash，并将prg[0-99]数据返回给主机。
 pattern1为花板号，存入flash的几号花板是由pattren1定
 就是把主机几号花板的所有数据传给控制箱花板号的所有数据
**************************************************************/
uint8 write_prg_to_flash(void)
{
    uint8 *inbuf,*outbuf,num;
    uint8 pattren1; 
    inbuf=get_inbuf(&com2);
    outbuf=get_outbuf(&com2);

    //dis_for_led();
    //if(get_end_rec(2,com2.rxbuf)==1)
    {
        pattren1=srcv_prg21(&prg[0][0],inbuf,outbuf);//从机接收 出错返回1，正常时返回花板号
    }
    if(pattren1!=0xff)//正常进入发存数据和返回
    { 
    //write_to_flash(pattren1,(uint8*)&prg[0][0]);//存值，将prg[100]的存入Pattren1号花板的flash
    //    dis_rev_led();
  
       num= ssend_prg21(&prg[0][0],inbuf,outbuf);//从机发送,返回到主机的数据
       //Start_USART_DMASend(USART2,outbuf,num);
    //	dis_base_led();		
    }  
//	else
//	{
//	   	Com_Err_Start=1;
//	}
//	return Com_Err_Start;
//}
    return num;
}




