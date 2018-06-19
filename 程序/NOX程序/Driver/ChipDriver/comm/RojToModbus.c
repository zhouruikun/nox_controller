/*
 * RojToModbus.c
 *
 *  Created on: 2013-1-18
 *      Author: lqm_8
 */
#define ROJTOMODBUS_globals
#include "stm32f10x.h"
#include "datatype.h"
#include "modbusstruct.h"
#include "modbus.h"
#include "rojtomodbus.h"
/****************************************************************************************
author     : lqm_8
description:��MODBUSЭ��ת����ROJЭ��
            *mbufΪmodbus���룬*rbufΪroj��� ,*tempbufΪ�����������
version    :ModbusToRoj v1.0.0
date:      : 13/01/18
***************************************************************************************/
uint8 ModbusToRoj(uint8 *mbuf,uint8 *tempbuf,uint8 *rbuf)
{//   roj       modbus
    uint8 num;
    uint16 temp,i;
    temp=((*(mbuf+2)<<8)+*(mbuf+3));
    *(rbuf+1)=*(mbuf+0);//������ַ
    *(rbuf+0)=2;//ͷ
    switch(temp)//��ַ
    {
        case 0x80://����
            *(rbuf+2)=1;//����;
            *(rbuf+3)=0xb0;//�Ĵ��ַ
            *(rbuf+4)=4;//����
            num=5;
            break;
        case 0x81://��ȡ�汾��
            //case 0xdf:
            //case 0xdc:
            *(rbuf+2)=1;//����;
            *(rbuf+3)=0xd7;//�Ĵ��ַ
            *(rbuf+4)=4;//����
            num=5;
            break;
        default:
            if(*(mbuf+1)==3)//��
            {
                *(rbuf+2)=2;//����
                *(rbuf+3)=0x11;//������
                *(rbuf+4)=((*(mbuf+2)<<8)+*(mbuf+3))&0x00ff;//�Ĵ��ַ
                *(rbuf+5)=4;//����
                num=6;
            }
            else if(*(mbuf+1)==6)//д�����
            {
                switch(temp)//������ַ
                {
                case 0xf1:
                case 0xf2:
                    *(rbuf+3)=0xc1;//������
                    *(rbuf+4)=(((*(mbuf+2)<<8)+*(mbuf+3))&0x00ff)&0x0f;//�Ĵ��ַ
                    break;
                case 0xf3:
                    *(rbuf+3)=0xc2;//������
                    //*(rbuf+4)=(((*(mbuf+2)<<8)+*(mbuf+3))&0x00ff)&0x0f;//�Ĵ��ַ
                    break;
                default:
                    *(rbuf+3)=0x12;//������
                    *(rbuf+4)=((*(mbuf+2)<<8)+*(mbuf+3))&0x00ff;//�Ĵ��ַ
                    break;
                }
                if(*(mbuf+4)==0)//8λ����
                {
                    if(*(rbuf+3)==0xc2)
                    {
                        *(rbuf+2)=2;//������
                        *(rbuf+4)=*(mbuf+5);
                    }
                    else
                    {
                        *(rbuf+2)=3;//������
                        for(i=0;i<(*(rbuf+2)-2);i++)
                        {
                            *(rbuf+5+i)=*(mbuf+5+i);
                        }
                    }
                }
                else//16λ����
                {
                    *(rbuf+2)=4;//������
                    for(i=0;i<(*(rbuf+2)-2);i++)
                    {
                        *(rbuf+5+i)=*(mbuf+4+i);
                    }
                }
                *(rbuf+5+(*(rbuf+2)-2))=4;
                num=6+(*(rbuf+2)-2);
            }
            break;
    }
    for(i=0;i<8;i++)
    {
        *(tempbuf+i)=*(mbuf+i);
    }
    return num;
}
/****************************************************************************************
author     : lqm_8
description:��ROJЭ��ת����MODBUSЭ��
            *rbufΪroj���룬*mbufΪmodbus��� *vecbufΪMODBUS���յ�����
version    :ModbusToRoj v1.0.0
date:      : 13/01/18
***************************************************************************************/

uint8 RojToModbus(uint8 *rbuf,uint8 *vecbuf,uint8 *mbuf)
{
    uint8 i;
    uint8 num=0;
    *(mbuf+0)=*(rbuf+1);//������ַ
    if(*(rbuf+3)==0x12)//������
    {
        *(mbuf+1)=0x03;//������
        switch(*(rbuf+4))
        {
            
            case 0x02:
            case 0x03:
            case 0x04:
            case 0x05:
            case 0x06:
            case 0x0f:
            case 0x0e:
            case 0x0b:
            case 0x10:
            case 0x14:
            case 0xe2:
            case 0xe3:
            case 0xe5:
            case 0x15:
            case 0x11:
            case 0x12:
            case 0x0d:
           
                *(mbuf+2)=2;//�ֽ���
                *(mbuf+3)=0;//����
                *(mbuf+4)=*(rbuf+5);
                pack(mbuf,3+*(mbuf+2));//���
                num=5+*(mbuf+2);
                break;
            case 0x01:
            case 0x22:
            case 0xf4:
            case 0xf5:
            case 0xf6:
            case 0xf7://����2   
            
                *(mbuf+2)=(*(rbuf+2)-2);//�ֽ���
                for(i=0;i<*(mbuf+2);i++)
                {
                    *(mbuf+3+i)=*(rbuf+5+i);//����
                //*(mbuf+4)=*(rbuf+6);
                }
                pack(mbuf,3+*(mbuf+2));//���
                num=5+*(mbuf+2);
                break;
            case 0x25:
                *(mbuf+2)=2;//�ֽ���
                for(i=0;i<2;i++)
                {
                    *(mbuf+3+i)=*(rbuf+9+i);
                }
                pack(mbuf,3+*(mbuf+2));//���
                num=5+*(mbuf+2);
                break;   
            default:   
                num=0;
                break;
        }
         
    }
    else
    {
        switch(*(rbuf+3))//������ַ
        {
            case 0x15:
                if(*(vecbuf+3)==0x80)//�����޹���
                {
                    *(mbuf+1)=3;//������
                    *(mbuf+2)=2;//�ֽ���
                    *(mbuf+3)=0;
                    *(mbuf+4)=*(rbuf+3);
                    pack(mbuf,5);//���
                    num=7;
                }
                else//�������ݳ�����
                {
                    if(*(vecbuf+1)==6)//д��ʱ��
                    {
                        *(mbuf+1)=6;//������
                        *(mbuf+2)=*(vecbuf+2);
                        *(mbuf+3)=*(vecbuf+3);
                        *(mbuf+4)=0xe0;
                        *(mbuf+5)=0x00;
                        pack(mbuf,6);//���
                        num=8;
                    }
                    if(*(vecbuf+1)==3)
                    {
                        *(mbuf+1)=3;//������
                        *(mbuf+2)=2;//�ֽ���
                        *(mbuf+3)=0xe0;
                        *(mbuf+4)=0x00; 
                        pack(mbuf,5);//���
                        num=7;
                    }
                      
                }
                
                break;
            case 0x40:
                if(*(vecbuf+3)==0x80)//���ִ���
                {
                    *(mbuf+1)=3;//����
                    *(mbuf+2)=2;//�ֽ���
                    *(mbuf+3)=*(rbuf+3);
                    *(mbuf+4)=*(rbuf+4);
                }
                pack(mbuf,5);//���
                num=7;
                break;
            case 0x06:
                if(*(vecbuf+1)==0x06)//д
                {
                    for(i=0;i<8;i++)
                    {
                        *(mbuf+i)=*(vecbuf+i);
                    }
                }
                num=8;
                break;
            case 0xd7:
                if(*(vecbuf+3)==0x81)//
                {
                *(mbuf+1)=3;//����
                *(mbuf+2)=2;//�ֽ���
                *(mbuf+3)=*(rbuf+4);
                *(mbuf+4)=*(rbuf+5);
                }
                pack(mbuf,5);//���
                num=7;
                break;
            default:
                num=0;
            break;
        }
    }
    return num;
}

