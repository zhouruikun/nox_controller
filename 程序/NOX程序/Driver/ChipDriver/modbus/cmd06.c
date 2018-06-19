#define public_function_globals
#define  cmd06_globals
#define para_globals
#include "cmd06.h"
#include "AT24C02.h"
#include "adc.h"
#include "DAC.h"
#include "Calculate_val.h"
extern u8 SelfTestFlag;	
extern u8 OffsetAdjFlag; 

void para_wr(cmd06_obj *dptr,uint16 *dat)//从机写寄存器值
{
    switch(dptr->node_addr)
    {
        case 2:
        dat[dptr->data_addr]=dptr->content;
        switch(dptr->data_addr)
        {
					case 1:   		 MCP4822_WriteValue(MCP4822_CH_A,MCP4822_GATE_ON,MCP4822_SHDN_OFF,Flux_DA1/1.22 );break;
					case 6:   		 MCP4822_WriteValue(MCP4822_CH_B,MCP4822_GATE_ON,MCP4822_SHDN_OFF,Flux_DA2/1.22 );break;
					case 11:   		 MCP4822_WriteValue(MCP4822_CH_C,MCP4822_GATE_ON,MCP4822_SHDN_OFF,Flux_DA3/1.22 );break;
					case 16:   		 MCP4822_WriteValue(MCP4822_CH_D,MCP4822_GATE_ON,MCP4822_SHDN_OFF,Flux_DA4/1.22 );break;
         default:
          break;
        }
        break;

        
    }
        
}

uint8 s_cmd06(void)
{
    uint8 j,num;
    uint8 *buff;
    uint8 *obuff;
    num=0;
    buff=get_inbuf(&com2);
    obuff=get_outbuf(&com2);
    if(un_pack(buff,6)==0)//CRC校验
    {
        j=srcv_cmd06(buff, &cmd06);
        if(j==0)
        {
            para_wr(&cmd06,&para[0]);//从机写寄存器值
            ssend_cmd06(&cmd06,obuff);//从机发送                                 
            //pack(obuff,6);
            num=cmd06.zl_len+2;
        }
        else
        {
            err_send(6,j,obuff);
            num=4;
        }

    }
    return num;

}


