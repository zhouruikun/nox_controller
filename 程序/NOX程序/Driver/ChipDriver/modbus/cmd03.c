
#define  cmd03_globals
#include "cmd03.h"



void para_rd(back03_obj *dptr,uint16 *dat)//�������Ĵ���ֵ
{
    uint8 i;
    uint8 send_para_len;
    send_para_len=dptr->bytelen>>1;
    switch(dptr->node_addr)
    {
    case 1:   
        break;
    case 2:
        for(i=0;i<send_para_len;i++)
        {
             dptr->para_1[i]=*(dat+dptr->data_addr2+i);
        } 
        break;
    case 9://����������

        break;

    }
}
/*
�ӻ�����
��У��CRC�Ƿ���ȷ��������1������1���жϱ�����ַ�Ƿ���ȷ��������2������2��
ѡ������0x03:srcv_cmd03(combuf_obj *combuf, req03_obj *dptr)
          0x06:srcv_cmd06(combuf_obj  *combuf, cmd06_obj *dptr)�ж��Ƿ���������
���д�Ĵ���ֵ��������͡�
*/


uint8 s_cmd03(void)
{
    uint8 j,num;
    uint8 *buff;
    uint8 *obuff;
    num=0;
    buff=get_inbuf(&com2);
    obuff=get_outbuf(&com2);
    if(un_pack(buff,6)==0)//CRCУ��
    {
        j=srcv_cmd03(buff, &req03);
        if(j==0)
        {
            truck_req_to_back(&req03,&back03);
            para_rd(&back03,&para[0]);//�ӻ����Ĵ���ֵ
            ssend_cmd03(&back03, obuff);//�ӻ�����
            num=back03.zl_len+2;
        }
        else
        {
            err_send(3,j,obuff); 
            num=4;
        }

    }
    return num;

}
//�Լ�����
uint8 s_cmd04(void)
{
    uint8 j,num;
    uint8 *buff;
    uint8 *obuff;
    num=0;
    buff=get_inbuf(&com2);
    obuff=get_outbuf(&com2);
    if(un_pack(buff,6)==0)//CRCУ��
    {
        j=srcv_cmd03(buff, &req03);
        if(j==0)
        {
            truck_req_to_back(&req03,&back03);
            para_rd(&back03,&para[0]);//�ӻ����Ĵ���ֵ
            ssend_cmd03(&back03, obuff);//�ӻ�����
            num=back03.zl_len+2;
        }
        else
        {
            err_send(3,j,obuff); 
            num=4;
        }

    }
    return num;

}
//�¶�У׼����

uint8 s_cmd05(void)
{
    uint8 j,num;
    uint8 *buff;
    uint8 *obuff;
    num=0;
    buff=get_inbuf(&com2);
    obuff=get_outbuf(&com2);
    if(un_pack(buff,6)==0)//CRCУ��
    {
        j=srcv_cmd03(buff, &req03);
        if(j==0)
        {
            truck_req_to_back(&req03,&back03);
            para_rd(&back03,&para[0]);//�ӻ����Ĵ���ֵ
            ssend_cmd03(&back03, obuff);//�ӻ�����
            num=back03.zl_len+2;
        }
        else
        {
            err_send(3,j,obuff); 
            num=4;
        }

    }
    return num;

}








