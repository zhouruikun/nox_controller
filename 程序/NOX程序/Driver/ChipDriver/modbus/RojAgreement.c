#include "datatype.h"
#include "roj_struct.h"
#include <includes.h>


/**************************************************************
 ����˵���� ����������������
 RojWrite_obj �ṹ��������Աд����
 *buffer Ϊ���ͻ�����
 ���� ���ͻ������ĸ���
**************************************************************/
uint8 master_shake_hands_send(uint8 *buffer,RojWrite_obj *dptr)
{
	*(buffer+0)=dptr->start;//ͷ
	*(buffer+1)=dptr->node_addr;//������ַ
	*(buffer+2)=dptr->len;//����
	*(buffer+3)=dptr->cmd;//������
	*(buffer+4)=dptr->end;//����
    return 5;
}
/**************************************************************
 ����˵���� �������ֽ���
 *buffer ���ջ�����
 *(dptr->para_data+0x80)���յ� para[0x80]
**************************************************************/
uint8 master_shake_hands_rcv(uint8 node_addr,uint8 *buffer,RojWrite_obj *dptr,uint16 *ptr)
{
	uint8 Com_Err_Start;
	dptr->para_data=ptr;
	Com_Err_Start=0;
	if(*(buffer+1)==node_addr)
	{
		if(*(buffer+0)==2)//����ͷ
		{
			if(*(buffer+3)==0x15)//��ȷ
			{
				if(*(buffer+4)==4)
				{
					//��ȷ����
					*(dptr->para_data+0x80)=0x0015;
					Com_Err_Start=0;
				}
			}
			else if(*(buffer+3)==0x40)//��ȷ//����
			{
				//Com_Err_Start=1;
				if(*(buffer+5)==4 || *(buffer+6)==4)
				{
					*(dptr->para_data+0x80)=(*(buffer+3)<<8)+*(buffer+4);
					Com_Err_Start=0;
				}
			}
		}
		else
		{
			Com_Err_Start=1;
		}
	}
	else
	{
		Com_Err_Start=1;
	}
	
	return Com_Err_Start;
}
/**************************************************************
 ����˵���� ������ȡ����
 RojWrite_obj �ṹ��������Աд����
 *buffer Ϊ���ͻ�����
 ���� ���ͻ������ĸ���
**************************************************************/
uint8 master_read_send(uint8 *buffer,RojWrite_obj *dptr)
{
	*(buffer+0)=dptr->start;//ͷ
	*(buffer+1)=dptr->node_addr;//������ַ
	*(buffer+2)=dptr->len;//����
	*(buffer+3)=dptr->cmd;//������
	*(buffer+4)=dptr->data_addr;//��ַ
	*(buffer+5)=dptr->end;//����
	return 6;
}
/**************************************************************
 ����˵���� ��������
 *buffer ���ջ�����
 *(dptr->para_data+0x80)���յ� para[0x80]
**************************************************************/
uint8 master_read_back(uint8 *buffer,RojWrite_obj *dptr,uint16 *ptr)
{
	uint8 Com_Err_Start,i;
	dptr->para_data=ptr;
	if(*(buffer+0)==2)//ͷ
	{
		if(*(buffer+3)==0x12)//������
		{
			switch(*(buffer+2)-2)
			{
				case 1:
					*(dptr->para_data+dptr->save_data_addr)=*(buffer+5);
					break;
				case 2:
					switch(*(buffer+4))
				    {
						case 0x01://γ��
						case 0x22://��������
						case 0x90://֯��ת��
						case 0x91://Ԥ��
						case 0xf4://ָ���ؽǶ�
						case 0xf5://�ؽǶ�1
						case 0xf6://�ؽǶȲο�
						case 0xf7://���Ʒ�ʽ
							*(dptr->para_data+dptr->save_data_addr)=(*(buffer+5)<<8)+*(buffer+6);
							break;
						case 0x21:
							for(i=0;i<2;i++)
						    {
								*(dptr->para_data+dptr->save_data_addr+i)=*(buffer+5+i);
							}
							*(dptr->para_data+dptr->save_data_addr)=(*(buffer+5)<<8)+*(buffer+6);
						//default:
						//	*(dptr->para_data+dptr->save_data_addr)=*(buffer+6);
						//	break;
					}		    
				    break;
                case 6://������ADֵ 0x25
					if(*(buffer+4)==0x25)
					{
						*(dptr->para_data+dptr->save_data_addr)=(*(buffer+9)<<8)+*(buffer+10);
					}
                    else if(*(buffer+4)==0x21)		
					{
                        for(i=0;i<6;i++)
						{
							*(dptr->para_data+dptr->save_data_addr+i)=*(buffer+5+i);
						}
					}						
                    break;	
                default:
					if(*(buffer+4)==0x21)		
					{
						for(i=0;i<12;i++)
                        {
                            *(dptr->para_data+dptr->save_data_addr+i)=0;
                        }
                        for(i=0;i<(*(buffer+2)-2);i++)
						{
							*(dptr->para_data+dptr->save_data_addr+i)=*(buffer+5+i);
						}
					}	
                    break;					
			}
			Com_Err_Start=0;
		}
		else
		{
			Com_Err_Start=1;
		}
	}
	else
	{
		Com_Err_Start=1;
	}
	return Com_Err_Start;
}
/**************************************************************
 ����˵���� ����д���Է���
 RojWrite_obj �ṹ��������Աд����
 *buffer Ϊ���ͻ�����
 ����send_num ���ͻ������ĸ���
**************************************************************/
uint8 master_write_send(uint8 *buffer,RojWrite_obj *dptr,uint16 *ptr)
{
	uint8 send_num;
	dptr->para_data=ptr;
	*(buffer+0)=dptr->start;//ͷ
	*(buffer+1)=dptr->node_addr;//������ַ
	*(buffer+2)=dptr->len;//����
	*(buffer+3)=dptr->cmd;//������
	*(buffer+4)=dptr->data_addr;//��ַ
	switch(dptr->len-2)
	{
		case 0:
			*(buffer+4)=*(dptr->para_data+dptr->save_data_addr);;//�����˳�����
		    *(buffer+5)=dptr->end;//����
		    send_num=6;
			break;
		case 1:
			*(buffer+5)=*(dptr->para_data+dptr->save_data_addr);
		    *(buffer+6)=dptr->end;//����
		    send_num=7;
			break;
		case 2:
			*(buffer+5)=(*(dptr->para_data+dptr->save_data_addr) & 0xff00)>>8;
		    *(buffer+6)=*(dptr->para_data+dptr->save_data_addr) & 0x00ff;
		    *(buffer+7)=dptr->end;//����
		    send_num=8;
			break;
		case 6:
			*(buffer+5)=0;
		    *(buffer+6)=0;
		    *(buffer+7)=0;
		    *(buffer+8)=0;
		    *(buffer+9)=(*(dptr->para_data+dptr->save_data_addr) & 0xff00)>>8;
		    *(buffer+10)=*(dptr->para_data+dptr->save_data_addr) & 0x00ff;
		    *(buffer+11)=dptr->end;//����
		    send_num=12;
		    break;
	}
	return send_num;
}
/**************************************************************
 ����˵���� ����д����
 *buffer Ϊ���ջ�����
 ����0 ��
 ����1 ��
**************************************************************/
uint8 master_write_back(uint8 *buffer)
{
	uint8 Com_Err_Start;
	if(*(buffer+0)==2)
	{
		if(*(buffer+4)==4)
		{
			if(*(buffer+3)==0x06)
			{
				Com_Err_Start=0;
			}
			else if(*(buffer+3)==0x15)
			{
				Com_Err_Start=1;
			}
		}
		else
		{
			Com_Err_Start=1;
		}
	}
	else
	{
		Com_Err_Start=1;
	}
	return Com_Err_Start;
}



