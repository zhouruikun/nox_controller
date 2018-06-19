#include "stm32f10x.h"
#include "datatype.h"
#include "pattern_wr.h"
#include "modbus.h"
uint8 W_R_prg_or_buffer(u8 *inbuff,u8 *outbuff,pattern *pg)
{
    u8 k=0,m,j,read_cnt,write_cnt;
    u16 data_lengh,data;u16 data_P_send[256];
    u8 revert_data_lengh;//发送串口数据长度 
    //u8 flag_pattern_operation;
    //flag_pattern_operation=0;
    if(inbuff[0]==0x63)
    {     
        if(inbuff[1]==0x10)
	{
            write_cnt=(inbuff[5]+(inbuff[4]<<8));
            write_cnt= write_cnt*2; 
            if(un_pack(inbuff,write_cnt+7)==0)//CRC校验               
            { 
                data_lengh=((inbuff[2]<<8)+inbuff[3])/3;
                pg=pg+data_lengh;
                for(k=0;k<write_cnt;k=k+6)
                {
                    pg=pg+1;
                    pg->pcmd=(inbuff[7+k+1])+(inbuff[7+k]<<8);
                    if(inbuff[7+k]==0x45) 
                    {
                        
                    }//flag_pattern_operation=0;
                    pg->step=((inbuff[7+k+2]<<8)+inbuff[7+k+3]);
                    pg->feelers=((inbuff[7+k+4]<<8)+inbuff[7+k+5]);
                
                }                   
                outbuff[0]=inbuff[0];
                outbuff[1]=inbuff[1];  
                outbuff[2]=inbuff[2];  
                outbuff[3]=inbuff[3];  
                outbuff[4]=inbuff[4];  
                outbuff[5]=inbuff[5];
                pack(outbuff,6);	               
                
                //--------------------------------------------------发送串口数据
                revert_data_lengh=8;    //发送串口数据长度
                //flag_Usart_Send_Data=1;//开发送串口数据标志  
            }
                
	}
        else if(inbuff[1]==0x03)
        {
            if(un_pack(inbuff,6)==0)//CRC校验
            {

                data=(inbuff[3]+(inbuff[2]<<8));
                read_cnt=(inbuff[5]+(inbuff[4]<<8));
                read_cnt= read_cnt;
                outbuff[0]=inbuff[0];
                outbuff[1]=inbuff[1]; 
                outbuff[2]=read_cnt<<1;
                if(data) data=data/3;                    
                pg=pg+data;
                for(k=0;k<read_cnt;k=k+3)        
                {
                    pg=pg+1;  
                    data_P_send[3+k]=pg->pcmd;
                    data_P_send[3+k+1]=pg->step;    
                    data_P_send[3+k+2]=pg->feelers;
                }                    
                for(m=0;m<read_cnt;m=m+3)
                {
                    j=m*2;          
                    outbuff[3+j+1]=data_P_send[3+m];  
                    outbuff[3+j]=data_P_send[3+m]>>8;        
                    if(outbuff[3+j]==0x45)
                    {
                       
                    } //flag_pattern_operation=0;
                    outbuff[3+j+3]=data_P_send[3+m+1];
                    outbuff[3+j+2]=data_P_send[3+m+1]>>8;
                    outbuff[3+j+5]=data_P_send[3+m+2];
                    outbuff[3+j+4]=data_P_send[3+m+2]>>8;
                }                  
                read_cnt=read_cnt*2;
                pack(outbuff,read_cnt+3);  
                revert_data_lengh=read_cnt+5;    //发送串口数据长度
                //flag_Usart_Send_Data=1;//开发送串口数据标志
                                      
            }     
         }

    }  
    return revert_data_lengh;
}
