/*
�汾��REV2.1

�޸�ʱ�䣺2012/08/11
�޸�����:¬����

�޸�����
1.
void ssend_prg21(pattern *ptr,uint8 *abuf,uint8 *obuf)
�����
     *(cmd_21.dataptr+i*3)=(ptr->pcmd)<<8;
	   *(cmd_21.dataptr+1+i*3)=ptr->step;
	   *(cmd_21.dataptr+2+i*3)=ptr->feelers; 
�ĳ����
     *(cmd_21.dataptr+i*3)=((ptr+cmd_21.rec_no)->pcmd)<<8;
	   *(cmd_21.dataptr+1+i*3)=(ptr+cmd_21.rec_no)->step;
		 *(cmd_21.dataptr+2+i*3)=(ptr+cmd_21.rec_no)->feelers; 
		 
		 
2.
uint8 srcv_prg21(pattern *ptr,uint8 *abuf,uint8 *outbuf)
�����	
       temp=cmd_21.rec_len/3;//��¼����
			 ptr=p+(cmd_21.rec_no)/3;//��
			 for(i=0;i<temp;ptr++,i++)//pcolor++ = prg+1,����pcolorָ��prg[1]
			 {                        //pcolor++ = prg+2,����pcolorָ��prg[2]
					ptr->pcmd=(*(cmd_21.dataptr+i*3))>>8;
					ptr->step=*(cmd_21.dataptr+1+i*3);
					ptr->feelers=*(cmd_21.dataptr+2+i*3);  

		
			 }
�ĳ����
       temp=cmd_21.rec_len/3;//��¼����
			 for(i=0;i<temp;ptr++,i++)//pcolor++ = prg+1,����pcolorָ��prg[1]
			 {                        //pcolor++ = prg+2,����pcolorָ��prg[2]
					(ptr+cmd_21.rec_no)->pcmd=(*(cmd_21.dataptr+i*3))>>8;
					(ptr+cmd_21.rec_no)->step=*(cmd_21.dataptr+1+i*3);
					(ptr+cmd_21.rec_no)->feelers=*(cmd_21.dataptr+2+i*3);     
			 }

*/


/****************************************************************************************
author     : ¬����
description: ��ssend_prg21��srcv_prg21 �Գ���������������30�����ϻ��岻�ܴ洢����
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


//��240���ֽ�40�еĳ���д��prg[0][x]���ڵĻ�������
void wr_pattern(cmd21_obj *pcmd, pattern *pcolor)
{
//uint16 rec_no;
//uint16 col_no;
  
//   col_no=rec_no/6;
//   wr_punit(&prg[0][0],&col_no);
}


/************************************************************** 
 ����˵���� �ܴӻ�����
 ����0x15        21
 1.�ȼƳ�rec_len��¼���ȣ�Ȼ��ȷ��һ֡Ϊ192���ֽڣ�180Ϊ���ݣ�
   ������ַ�����ܡ����ݳ��ȡ��ο����͡��ļ��š���¼����
   CRCһ��12���ֽڡ�����һ֡Ϊ����180+12��192
   �磺prg[0].......prg[99]�ṹ������, dataptr[0]......dataptr[299]
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
   Ҳ����˵100��ṹ�����飽100*3��һ������dataptr[300]
   prg[30]=dataptr[90]=outbuf[180]
 2.�������192Ϊһ֡Ҫ����֡temp=��¼����/90,��������¼����-temp*90
   ��90�����ļ�֡���꣬�ٷ���������90��һ֡��
**************************************************************/

uint8 ssend_prg21(pattern *ptr,uint8 *abuf,uint8 *obuf)
{
    cmd21_obj cmd_21;

    uint8 i,num;
    uint8 temp1;
    //д����21��prg[100]����
    cmd_21.node_addr=*abuf;     //������ַ                                          ��
    cmd_21.fun_num=*(abuf+1);    //������                                           ��
    cmd_21.data_l=*(abuf+2);     //�������ݵĳ��� һ����������pcmd ��step��feelers  ��
    cmd_21.reftype=*(abuf+3);    //�ο�����                                         ��
    cmd_21.fileno=(*(abuf+4)<<8)+*(abuf+5);  //�ļ���                               ��
    cmd_21.rec_no=(*(abuf+6)<<8)+*(abuf+7);      //��¼��prg[��¼��]                ��
    cmd_21.rec_len=(*(abuf+8)<<8)+*(abuf+9);      //��¼����  
    temp1=cmd_21.rec_len/3;
    for(i=0;i<temp1;ptr++,i++)//pcolor++ = prg+1,����pcolorָ��prg[1]
    {                        //pcolor++ = prg+2,����pcolorָ��prg[2]
        *(cmd_21.dataptr+i*3)=((ptr+cmd_21.rec_no)->pcmd)<<8;
        *(cmd_21.dataptr+1+i*3)=(ptr+cmd_21.rec_no)->step;
        *(cmd_21.dataptr+2+i*3)=(ptr+cmd_21.rec_no)->feelers; 
    }
    ssend_cmd21(obuf, &cmd_21);//�ӻ�����
    num=cmd_21.rec_len*2+12;
    //init_send(com0,(cmd_21.rec_len*2+12));
    // OS_ENTER_CRITICAL();
    // uart_send(com0,UART0_BASE);
    //  OS_EXIT_CRITICAL();
    // OSSemPend(uart0SemPtr,30, &err);	   // ��ʱ20ms*15=300ms
    //beginSend(192);//ǰ��10���ֽ�,����30*3��90��������*2=180���ֽ�,����CRC
    //10+90+2=192���ֽ�	
    return num;
}

uint8 srcv_prg21(pattern *ptr,uint8 *abuf,uint8 *outbuf)
{
    cmd21_obj cmd_21;
    uint8 i,temp,Com_Err_Start;
    uint16 len;
    len=(*(abuf+8)<<8)+*(abuf+9);
    if(un_pack(abuf,(len*2+10))==0)//CRCУ��len*2+10
    {

        len=mback_cmd21(&cmd_21,abuf);//�������չ���21
        if(len==0)
        {
            temp=cmd_21.rec_len/3;//��¼����
            for(i=0;i<temp;ptr++,i++)//pcolor++ = prg+1,����pcolorָ��prg[1]
            {                        //pcolor++ = prg+2,����pcolorָ��prg[2]
                (ptr+cmd_21.rec_no)->pcmd=(*(cmd_21.dataptr+i*3))>>8;
                (ptr+cmd_21.rec_no)->step=*(cmd_21.dataptr+1+i*3);
                (ptr+cmd_21.rec_no)->feelers=*(cmd_21.dataptr+2+i*3);     
            }
            Com_Err_Start=(*(abuf+4)<<8)+*(abuf+5);//���ؼ��Ż���
        }
        else
        {
            err_send1(0x95,len,outbuf);//�쳣���� 
            Com_Err_Start=0xff;
        }	   
    }//while(ok==0)
    return Com_Err_Start;
}


/************************************************************** 
 ����˵�����ӻ����� Ҳ����д�����ݵ�prg[0-99]
 ����0x15        21
 �ѽ��յ������ݴ���flash,Ȼ�󷢻ظ�����
 �磺������prg[0-99]�����ݷ����ӻ����ӻ�������prg[0-99]�����ݴ���
 flash������prg[0-99]���ݷ��ظ�������
 pattern1Ϊ����ţ�����flash�ļ��Ż�������pattren1��
 ���ǰ��������Ż�����������ݴ��������仨��ŵ���������
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
        pattren1=srcv_prg21(&prg[0][0],inbuf,outbuf);//�ӻ����� ������1������ʱ���ػ����
    }
    if(pattren1!=0xff)//�������뷢�����ݺͷ���
    { 
    //write_to_flash(pattren1,(uint8*)&prg[0][0]);//��ֵ����prg[100]�Ĵ���Pattren1�Ż����flash
    //    dis_rev_led();
  
       num= ssend_prg21(&prg[0][0],inbuf,outbuf);//�ӻ�����,���ص�����������
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




