#include "datatype.h"
#include "roj_struct.h"
#include <includes.h>


/**************************************************************
 函数说明： 主机发送握手命令
 RojWrite_obj 结构体可以向成员写数据
 *buffer 为发送缓冲区
 返回 发送缓冲区的个数
**************************************************************/
uint8 master_shake_hands_send(uint8 *buffer,RojWrite_obj *dptr)
{
	*(buffer+0)=dptr->start;//头
	*(buffer+1)=dptr->node_addr;//本机地址
	*(buffer+2)=dptr->len;//长度
	*(buffer+3)=dptr->cmd;//功能码
	*(buffer+4)=dptr->end;//结束
    return 5;
}
/**************************************************************
 函数说明： 主机握手接收
 *buffer 接收缓冲区
 *(dptr->para_data+0x80)接收到 para[0x80]
**************************************************************/
uint8 master_shake_hands_rcv(uint8 node_addr,uint8 *buffer,RojWrite_obj *dptr,uint16 *ptr)
{
	uint8 Com_Err_Start;
	dptr->para_data=ptr;
	Com_Err_Start=0;
	if(*(buffer+1)==node_addr)
	{
		if(*(buffer+0)==2)//等于头
		{
			if(*(buffer+3)==0x15)//正确
			{
				if(*(buffer+4)==4)
				{
					//正确结束
					*(dptr->para_data+0x80)=0x0015;
					Com_Err_Start=0;
				}
			}
			else if(*(buffer+3)==0x40)//正确//错误
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
 函数说明： 主机读取发送
 RojWrite_obj 结构体可以向成员写数据
 *buffer 为发送缓冲区
 返回 发送缓冲区的个数
**************************************************************/
uint8 master_read_send(uint8 *buffer,RojWrite_obj *dptr)
{
	*(buffer+0)=dptr->start;//头
	*(buffer+1)=dptr->node_addr;//本机地址
	*(buffer+2)=dptr->len;//长度
	*(buffer+3)=dptr->cmd;//功能码
	*(buffer+4)=dptr->data_addr;//地址
	*(buffer+5)=dptr->end;//结束
	return 6;
}
/**************************************************************
 函数说明： 主机接收
 *buffer 接收缓冲区
 *(dptr->para_data+0x80)接收到 para[0x80]
**************************************************************/
uint8 master_read_back(uint8 *buffer,RojWrite_obj *dptr,uint16 *ptr)
{
	uint8 Com_Err_Start,i;
	dptr->para_data=ptr;
	if(*(buffer+0)==2)//头
	{
		if(*(buffer+3)==0x12)//功能码
		{
			switch(*(buffer+2)-2)
			{
				case 1:
					*(dptr->para_data+dptr->save_data_addr)=*(buffer+5);
					break;
				case 2:
					switch(*(buffer+4))
				    {
						case 0x01://纬长
						case 0x22://读光电参数
						case 0x90://织机转速
						case 0x91://预留
						case 0xf4://指棒关角度
						case 0xf5://关角度1
						case 0xf6://关角度参考
						case 0xf7://控制方式
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
                case 6://传感器AD值 0x25
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
 函数说明： 主机写测试发送
 RojWrite_obj 结构体可以向成员写数据
 *buffer 为发送缓冲区
 返回send_num 发送缓冲区的个数
**************************************************************/
uint8 master_write_send(uint8 *buffer,RojWrite_obj *dptr,uint16 *ptr)
{
	uint8 send_num;
	dptr->para_data=ptr;
	*(buffer+0)=dptr->start;//头
	*(buffer+1)=dptr->node_addr;//本机地址
	*(buffer+2)=dptr->len;//长度
	*(buffer+3)=dptr->cmd;//功能码
	*(buffer+4)=dptr->data_addr;//地址
	switch(dptr->len-2)
	{
		case 0:
			*(buffer+4)=*(dptr->para_data+dptr->save_data_addr);;//喷气退出测试
		    *(buffer+5)=dptr->end;//结束
		    send_num=6;
			break;
		case 1:
			*(buffer+5)=*(dptr->para_data+dptr->save_data_addr);
		    *(buffer+6)=dptr->end;//结束
		    send_num=7;
			break;
		case 2:
			*(buffer+5)=(*(dptr->para_data+dptr->save_data_addr) & 0xff00)>>8;
		    *(buffer+6)=*(dptr->para_data+dptr->save_data_addr) & 0x00ff;
		    *(buffer+7)=dptr->end;//结束
		    send_num=8;
			break;
		case 6:
			*(buffer+5)=0;
		    *(buffer+6)=0;
		    *(buffer+7)=0;
		    *(buffer+8)=0;
		    *(buffer+9)=(*(dptr->para_data+dptr->save_data_addr) & 0xff00)>>8;
		    *(buffer+10)=*(dptr->para_data+dptr->save_data_addr) & 0x00ff;
		    *(buffer+11)=dptr->end;//结束
		    send_num=12;
		    break;
	}
	return send_num;
}
/**************************************************************
 函数说明： 主机写返回
 *buffer 为接收缓冲区
 返回0 对
 返回1 错
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



