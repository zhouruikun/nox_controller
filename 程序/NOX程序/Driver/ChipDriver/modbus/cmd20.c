/*
�汾��REV2.1

�޸�ʱ�䣺2012/08/11
�޸�����:¬����

�޸�����

1.
void ssend_prg20(pattern *ptr,uint8 control,uint8 *obuf,back20_obj *dptr)
�����
        ptr=p+(dptr->rec_no/3);	
	      for(i=0;i<30;ptr++,i++)//pcolor++ = prg+1,����pcolorָ��prg[1]
		    {                        //pcolor++ = prg+2,����pcolorָ��prg[2]
	 	 	   *(dptr->dataptr+i*3)=(ptr->pcmd)<<8;
			   *(dptr->dataptr+1+i*3)=ptr->step;
			   *(dptr->dataptr+2+i*3)=ptr->feelers;         
		    }
			�ĳ����	
      for(i=0;i<30;ptr++,i++)//pcolor++ = prg+1,����pcolorָ��prg[1]
			{                        //pcolor++ = prg+2,����pcolorָ��prg[2]
			 	*(dptr->dataptr+i*3)=((ptr+dptr->rec_no)->pcmd)<<8;
				*(dptr->dataptr+1+i*3)=(ptr+dptr->rec_no)->step;
				*(dptr->dataptr+2+i*3)=(ptr+dptr->rec_no)->feelers;         
			}

2.
�����
		ptr=p+(dptr->rec_no/3);
	    for(i=0;i<temp1;ptr++,i++)//pcolor++ = prg+1,����pcolorָ��prg[1]
	    {                        //pcolor++ = prg+2,����pcolorָ��prg[2]
	 	   *(dptr->dataptr+i*3)=(ptr->pcmd)<<8;
		   *(dptr->dataptr+1+i*3)=ptr->step;
		   *(dptr->dataptr+2+i*3)=ptr->feelers;         
	    }	
�ĳ����			
    for(i=0;i<temp1;ptr++,i++)//pcolor++ = prg+1,����pcolorָ��prg[1]
		{                        //pcolor++ = prg+2,����pcolorָ��prg[2]
		 	*(dptr->dataptr+i*3)=((ptr+dptr->rec_no)->pcmd)<<8;
			*(dptr->dataptr+1+i*3)=(ptr+dptr->rec_no)->step;
			*(dptr->dataptr+2+i*3)=(ptr+dptr->rec_no)->feelers;         
		}
		      
		 
					

*/

/****************************************************************************************
author     : ¬����
description: ��ssend_prg20�����������  �����30�����ϻ����ȡ���������
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


//��240���ֽ�40�еĳ������ prg[0][x]���ڵĻ�������
void rd_pattern(req20_obj *preq,back20_obj *pback, pattern  *pcolor)
{
  
}

//���ݶ������ָ���Ļ��ʹ�flash���ж���д�뻺����prg[0][x]
//�Ĵ��������ݾ����ļ��š�

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
 ����˵���� �ܴӻ�����
 ����0x14       20
 �����ݶ����յ�prg[]�ṹ��������ȥ
 ��dataptr[0]..dataptr[299]���� prg[0]...prg[99]
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
 ��Ϊ��¼����Ϊ90��Ҫ��һ���������ṹ���������3
**************************************************************/


uint8 srcv_prg20(uint8 *abuf,uint8 *outbuf)
{

    req20_obj req_20;
    uint8 temp;
    uint8 Com_Err_Start;
    if(un_pack(abuf,10)==0)//CRCУ��
    {
        temp=srcv_cmd20(abuf, &req_20);
        if(temp==0)
        {	
            truck_req20_to_back20(&req_20,&back20);
            Com_Err_Start=(*(abuf+4)<<8)+*(abuf+5);
        }
        else 
        {
            err_send1(0x94,temp,outbuf);//�쳣����
            Com_Err_Start=0xff;
        }		 
    }
    return Com_Err_Start;
}


/************************************************************** 
 ����˵���� �ܴӻ�����
 ����0x14        20
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

uint8 ssend_prg20(pattern *ptr,uint8 control,uint8 *obuf,back20_obj *dptr)
{

    pattern *p; 
    uint8 i,num;
    uint8 temp1;
    //����20����prg[100]����
    p=ptr;//��ptrָ����׵�ַ��p
    ptr=p;//��pָ����׵�ַ��ptr
    if(dptr->rec_len>=90)
    {
        //truck_back_20_to_back20(&back20);
        dptr->node_addr=9;     //������ַ
        dptr->fun_num=0x14;    //������
        dptr->data_byte=90*2+2;//90*2+2     //�������ݵĳ��� һ����������pcmd ��step��feelers
        dptr->file_len=90*2+1;//90*2+1;
        dptr->reftype=0x06;    //�ο�����

        for(i=0;i<30;ptr++,i++)//pcolor++ = prg+1,����pcolorָ��prg[1]
        {                        //pcolor++ = prg+2,����pcolorָ��prg[2]
            *(dptr->dataptr+i*3)=((ptr+dptr->rec_no)->pcmd)<<8;
            *(dptr->dataptr+1+i*3)=(ptr+dptr->rec_no)->step;
            *(dptr->dataptr+2+i*3)=(ptr+dptr->rec_no)->feelers;         
        }

        ssend_cmd20(&back20,obuf);//�����ּĴ�����Ӧ�ӻ�����
        num=dptr->data_byte+5;
        //init_send(com0,dptr->data_byte+5);

        //OS_ENTER_CRITICAL();
        //uart_send(com0,UART0_BASE);
        //OS_EXIT_CRITICAL();
        //OSSemPend(uart0SemPtr,30, &err);	   // ��ʱ20ms*15=300ms	
        //beginSend(187);//ǰ��10���ֽ�,����30*3��90��������*2=180���ֽ�,����CRC
               //10+90+2=192���ֽ�	   	

    }//if(temp!=0)	
    else//temp=0
    {
        dptr->node_addr=9;     //������ַ
        dptr->fun_num=0x14;    //������
        dptr->data_byte=dptr->rec_len*2+2;     //�������ݵĳ��� һ����������pcmd ��step��feelers
        dptr->file_len=dptr->rec_len*2+1;
        dptr->reftype=0x06;    //�ο�����		
        temp1=dptr->rec_len/3;  

        for(i=0;i<temp1;ptr++,i++)//pcolor++ = prg+1,����pcolorָ��prg[1]
        {                        //pcolor++ = prg+2,����pcolorָ��prg[2]
            *(dptr->dataptr+i*3)=((ptr+dptr->rec_no)->pcmd)<<8;
            *(dptr->dataptr+1+i*3)=(ptr+dptr->rec_no)->step;
            *(dptr->dataptr+2+i*3)=(ptr+dptr->rec_no)->feelers;         
        }

        ssend_cmd20(&back20,obuf);//�����ּĴ�����Ӧ�ӻ�����
        num=dptr->data_byte+5;
        //init_send(com0,dptr->data_byte+5);

        //OS_ENTER_CRITICAL();
        //uart_send(com0,UART0_BASE);
        //OS_EXIT_CRITICAL();
        //OSSemPend(uart0SemPtr,30, &err);	   // ��ʱ20ms*15=300ms
        //beginSend(dptr->rec_len*2+7);
    } 
    return num;
   
}





/************************************************************** 
 ����˵�����ӻ����� Ҳ���Ǵ�prg[0-99]��ȡ���ݷ�������
 ����0x14        20
 ���յ���Ϊ��ȡ�������
 �磺�ȴ�flash�����ȡ���Ż�������ݣ�����prg[0-99]�У�Ȼ��
 �͸�������
 pattern1Ϊ����ţ����ͼ��Ż�������pattren1��
 ���ǰ��������Ż�����������ݴ��������仨��ŵ���������
**************************************************************/

uint8 read_prg_from_flash(void)
{
    uint8 *inbuf,*outbuf,num;
    uint8 pattren1;  
    inbuf=get_inbuf(&com2);
    outbuf=get_outbuf(&com2);
    
    //if(get_end_rec(2,com2.rxbuf)==1)//���ڽ�����ɱ�־λ
    {
        pattren1=srcv_prg20(inbuf,outbuf);//�ӻ�����
    }
    if(pattren1!=0xff)
    { 

        //read_from_flash(pattren1,(uint8*)&prg[0][0]);//��flash�����ݵ�prg[]
        //init_prg(); 
        num=ssend_prg20(&prg[0][0],pattren1,outbuf,&back20);//�ӻ�����
        //Start_USART_DMASend(USART2,outbuf,num);
        //Com_Err_Start=0;		
    }  
    else
    {
   // Com_Err_Start=1;
    }
    return num;
}








