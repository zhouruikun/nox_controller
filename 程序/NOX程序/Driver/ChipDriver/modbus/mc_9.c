#define mc_9_globals  1 
#include "datatype.h"
#include "mc_9.h"
#include "pattern_para.h" 


/*
 ��������������������������������������������������������
| ��ַ     ������     ����  �������ټ���   CRC��   CRC��|
 --------------------------------------------------------
|        |         |        |         |         |       |                                                                           |
---------------------------------------------------------
���ڴӻ�������
sizeof()�����У��λ
*/
/*
void pack(uint8  *bufptr,uint8 shu)//���
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
�ж�CRCУ���Ƿ���ȷ��err=0ʱУ����ȷ��err=1ʱУ�����
����errֵ,shuָУ��λ�ڵڼ�λ
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
������
*/
/*
void start_err(combuf_obj  *combuf, com_err *dptr)
{
	combuf->outbuf[0]=dptr->oerr;//�쳣
}
*/

/*
�����쳣���� ��
cmd�ı䲻ͬ���ܵĴ����룬oerrΪ�쳣�룬obuffΪ���ͻ�����
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
 ����˵���� ��������
 ����0x14        20
**************************************************************/

uint8 mback_cmd20(uint8 *abuf,  back20_obj *dptr)
{
      uint8 i, temp;
      uint8 Com_Err_Start;
      if(*(abuf+1)==20)//����0x15
      {
         temp=*(abuf+2);//��Ӧ���ݳ���
         if(temp>=7 && temp<=0xf5)
         {
             temp=*(abuf+3);//�ļ���Ӧ����
             if(temp>=7 && temp<=0xf5)
             {
                  dptr->node_addr=*abuf;     //������ַ
                  dptr->fun_num=*(abuf+1);   //������
                  dptr->data_byte=*(abuf+2); //��Ӧ���ݳ���
                  dptr->file_len=*(abuf+3);  //�ļ���Ӧ����
                  dptr->reftype=*(abuf+4);   //�ο�����
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
 ����˵���� ��������
 ����0x14        20
**************************************************************/

void  mreq_cmd20(req20_obj *dptr,  uint8 *obuf)
{
     *obuf=dptr->slave_addr;                  //��ַ
     *(obuf+1)=dptr->fun_num;                 //������
     *(obuf+2)=dptr->filebyte;                //�ֽ���
     *(obuf+3)=dptr->reftype;                 //�ο�����
     *(obuf+4)=(dptr->fileno & 0xff00)>>8;    //�ļ��Ÿ�
     *(obuf+5)=(dptr->fileno & 0xff);         //�ļ��ŵ�
     *(obuf+6)=(dptr->rec_no & 0xff00)>>8;    //��¼�Ÿ�
     *(obuf+7)=(dptr->rec_no & 0xff);         //��¼�ŵ�
     *(obuf+8)=(dptr->rec_len & 0xff00)>>8;   //��¼���ȸ�
     *(obuf+9)=(dptr->rec_len & 0xff);        //��¼���ȵ�
	 pack(obuf,10);

}

/************************************************************** 
 ����˵���� ��������
 ����0x15        21
**************************************************************/

void  mreq_cmd21(cmd21_obj *dptr, uint8 *obuf )
{
     uint8 i;
     //uint16 temp;
     *obuf=dptr->node_addr;  //������ַ
     *(obuf+1)=dptr->fun_num;//������
     *(obuf+2)=dptr->data_l; //���ݳ���
     *(obuf+3)=dptr->reftype;//�ο�����
     *(obuf+4)=(dptr->fileno & 0xff00)>>8;//�ļ���
     *(obuf+5)=dptr->fileno & 0xff;
     *(obuf+6)=(dptr->rec_no & 0xff00)>>8;//��¼��
     *(obuf+7)=dptr->rec_no & 0xff;
     *(obuf+8)=(dptr->rec_len & 0xff00)>>8;//��¼����
     *(obuf+9)=dptr->rec_len & 0xff;
	 //temp=dptr->rec_len-1; 
     for(i=0;i<dptr->rec_len;i++)//��¼����90*2��180
     {
         *(obuf+10+i*2)=(*(dptr->dataptr+i) & 0xff00)>>8;
         *(obuf+10+1+i*2)=*(dptr->dataptr+i) & 0xff;
     }
	 
     pack(obuf,dptr->rec_len*2+10);//90*2+10=190
}

/************************************************************** 
 ����˵���� ��������
 ����0x15        21
**************************************************************/

uint8  mback_cmd21(cmd21_obj *dptr, uint8 *abuf )
{
   uint16 temp;
   uint8 j,i;
   uint8 Com_Err_Start;
   if(*(abuf+1)==0x15)//����
   {
      if(*(abuf+2)>=7 && *(abuf+2)<=245)//�ֽ���
      {
         if(*(abuf+3)==6)//�ο�����
         {
            j=((*(abuf+5)+(*(abuf+4)<<8)));
            if(j<=9)//�ļ���
            {
               j=(*(abuf+7)+(*(abuf+6)<<8));
               //if(j<=0x270f)//��¼�ţ���ʼ��ַ
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
					      for(i=0;i<dptr->rec_len;i++)//��¼����
                     {
                         *(dptr->dataptr+i)= (abuf[10+i*2]<<8)+abuf[10+1+i*2];
                     }
                     Com_Err_Start=0;
                  } 
               //}
               //else//��¼���쳣
               //{
               //   Com_Err_Start=2;
               //}   
            }
            else//�ļ����쳣
            {
               Com_Err_Start=2;
            }   
         }
         else//�ο������쳣
         {
            Com_Err_Start=2;
         }
      }
      else//�ֽ����쳣
      {
         Com_Err_Start=3;
      }      
   }
   else//�����쳣 
   {
      Com_Err_Start=1;
   }
   return Com_Err_Start;
}


uint8  srcv_cmd20(uint8 *buff, req20_obj *dptr)//д�����Ĵ����ӻ�����
{
   uint16 i,temp;
   uint8 Com_Err_Start,j;
   if(buff[1]==0x14)//����
   {
      if(buff[2]>=7 && buff[2]<=245)//�ֽ���
      {
         if(buff[3]==6)//�ο�����
         {
            j=(buff[5]+(buff[4]<<8));
            if(j<=9)//�ļ���
            {
               j=(buff[7]+(buff[6]<<8));
               //if(j<=0x270f)//��¼�ţ���ʼ��ַ
               //{
                  if(((buff[9]+(buff[8]<<8))+j)<=0xffff) 
                  {
                     dptr->slave_addr=buff[0];
                     dptr->fun_num=buff[1];
                     dptr->filebyte=buff[2];
					 temp=dptr->filebyte/7;
					 for(i=0;i<temp;i++)
					 {
	                     dptr->reftype=buff[3+i*7];                  //�ο�����
	                     dptr->fileno=((buff[4+i*7]<<8)+buff[5+i*7]);	 //�ļ���
	                     dptr->rec_no=((buff[6+i*7]<<8)+buff[7+i*7]); 	 //��¼��
	                     dptr->rec_len=((buff[8+i*7]<<8)+buff[9+i*7]);	 //��¼����
	                     
					}
					Com_Err_Start=0;//����
                  } 
               //}
              // else//��¼���쳣
              // {
              //    Com_Err_Start=2;
              // }   
            }
            else//�ļ����쳣
            {
               Com_Err_Start=2;
            }   
         }
         else//�ο������쳣
         {
            Com_Err_Start=2;
         }
      }
      else//�ֽ����쳣
      {
         Com_Err_Start=3;
      }      
   }
   else//�����쳣 
   {
      Com_Err_Start=1;
   }
   return Com_Err_Start;
}
 

void ssend_cmd20(back20_obj *dptr,uint8 *p)//�����ּĴ�����Ӧ
{
   uint8 shu,j;
   *p=dptr->node_addr;//��ַ
   *(p+1)=dptr->fun_num;//������
   *(p+2)=dptr->data_byte;//��Ӧ���ݳ���
   *(p+3)=dptr->file_len;//�ļ���Ӧ����
   *(p+4)=dptr->reftype;//�ο�����
   shu=((dptr->file_len-1)>>1);
   for(j=0;j<shu;j++)
   {
       *(p+5+j*2)=(*(dptr->dataptr+j) & 0xff00)>>8;
       *(p+5+1+j*2)=*(dptr->dataptr+j) & 0xff;
   }
   pack(p,dptr->data_byte+3);//90*2+10=190
   
}

void ssend_cmd21(uint8 *buff, cmd21_obj *dptr)//д�����Ĵ����ӻ���Ӧ
{
    uint8 i;
    *(buff)=dptr->node_addr;//������ַ 
    *(buff+1)=dptr->fun_num;//������
    *(buff+2)=dptr->data_l;//���ݳ���(�ֽ���)
    *(buff+3)=dptr->reftype;//�ο�����
    *(buff+4)=((dptr->fileno & 0xff00)>>8);//�ļ���
    *(buff+5)=dptr->fileno &0xff;
    *(buff+6)=((dptr->rec_no & 0xff00)>>8);//��¼��
    *(buff+7)=dptr->rec_no &0xff;
    *(buff+8)=((dptr->rec_len & 0xff00)>>8);//��¼����
    *(buff+9)=dptr->rec_len &0xff;
    for(i=0;i<dptr->rec_len;i++)    
    {
         *(buff+10+i*2)=(*(dptr->dataptr+i) & 0xff00)>>8;//��λ
         *(buff+10+1+i*2)=*(dptr->dataptr+i)&0xff;//��λ
    }
	pack(buff,dptr->rec_len*2+10);//90*2+10=190
}

/*
�����쳣���� ��
cmd�ı䲻ͬ���ܵĴ����룬oerrΪ�쳣�룬obuffΪ���ͻ�����
*/

void err_send1(uint8 cmd,uint8 oerr,uint8 *obuff)
{
	*obuff=cmd;
	*(obuff+1)=oerr;
	 pack(obuff,2);
}

/************************************************************** 
 ����˵���� ���� 20  ���սṹ�����ͽṹ�崫����
**************************************************************/

void truck_req20_to_back20(req20_obj *dptr,back20_obj *pin)
{
    pin->node_addr=dptr->slave_addr;
    pin->fun_num=dptr->fun_num;
    if(dptr->filebyte/7==1)//ֻ��1������ʱ
    {
       pin->data_byte=(dptr->rec_len<<1)+2;
    }
    else//��������
    {
    }
    //pin->data_byte=(dptr->filebyte<<1)+2;//��Ӧ���ݳ���
    pin->file_len=(dptr->rec_len<<1)+1;
    pin->reftype=dptr->reftype;
    pin->fileno=dptr->fileno;
    pin->rec_no=dptr->rec_no;
	 pin->rec_len=dptr->rec_len;
}


