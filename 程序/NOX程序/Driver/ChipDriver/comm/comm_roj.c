
#define comm_roj_globals
#include "datatype.h"
#include "dispbuf.h"
#include "barmenu.h"
#include "cn_en.h"
#include "language_select.h"
#include "lp_disp_char.h"
#include "roj_struct.h"
#include "public_parabuf.h"
#include "comm_roj.h"
#include "comm.h"
#include "menux_para_addrx.h"
#include "MenuxParaxDefine.h"
#include "variable_define.h"
#include "label.h"
#include "hander_disp_tab.h"
#include "key.h"
/************************************************************** 
 函数说明：roj 握手        
           
**************************************************************/


uint8 shake_hands(uint8 *ptr)//握手
{
	uint8 err=0,i,key;
    
   // uint8 temp1;
	for(i=0;i<2;i++)
	{
		
		err=direct_read_remote_parm_noerr(0x80,0x80,i+1,1);
        //direct_read_remote_parm_noerr(read_weft_length_cmd,read_weft_length_cmd,i+1,1);//读取纬长
		//roj_read_remote_shake_hands(i+1,&err);
		if(err==0)//正确
		{        
            if(i==0)
            {
                
                shake_hands_count1=0;  
                *(ptr+i)=1+i; 
            }                    
            if(i==1)  
            {

                shake_hands_count2=0; 
                *(ptr+i)=1+i;                 
            }  
                                       
		}
        else
        {
            key=key_scan_nowait();
            if(key!=0xff)
            {
                break;
            }
            err=direct_read_remote_parm_noerr(0x80,0x80,i+1,1);
            if(err==0)//正确
            {
                if(i==0)
                {
                    shake_hands_count1=0;  
                    *(ptr+i)=1+i; 
                }                    
                if(i==1)  
                {
                    shake_hands_count2=0; 
                    *(ptr+i)=1+i;                 
                }
                
            } 
            else
            {
                if(i==0)
                {
                    shake_hands_count1++;
                    if(shake_hands_count1>=2)
                    {
                        //read_feeder1_flag=1;
                        shake_hands_count1=0;
                        *(ptr+i)=0;
                    }
                }
                if(i==1)
                {
                    shake_hands_count2++;
                    if(shake_hands_count2>=2)
                    {
                        //read_feeder2_flag=1;
                        shake_hands_count2=0;
                        *(ptr+i)=0;
                    }
                }
                
            }                
        }
        
        key=key_scan_nowait();
        if(key!=0xff)
        {
            break;
        }
	}
	return key;
}


uint8 shake_hands_init(uint8 *ptr)//握手
{
	uint8 err=0,i,j;
    for(j=0;j<1;j++)
    {
        for(i=0;i<2;i++)
        {
            
            err=direct_read_remote_parm_noerr(0x80,0x80,i+1,1);
            //direct_read_remote_parm_noerr(read_weft_length_cmd,read_weft_length_cmd,i+1,1);//读取纬长
            //roj_read_remote_shake_hands(i+1,&err);
            if(err==0)//正确
            {   
                if(i==0)
                {
                    shake_hands_count1=0;  
                    *(ptr+i)=i+1; 
                }                    
                if(i==1)  
                {
                    shake_hands_count2=0;  
                    *(ptr+i)=i+1; 
                }                    
                                           
            }
            else
            {
                err=direct_read_remote_parm_noerr(0x80,0x80,i+1,1);
                if(err==0)//正确
                {
                    if(i==0)
                    {
                        shake_hands_count1=0;  
                        *(ptr+i)=1; 
                    }                    
                    if(i==1)  
                    {
                        shake_hands_count2=0;  
                        *(ptr+i)=2; 
                    }
                    
                } 
                else
                {
                    if(i==0)
                    {
                        shake_hands_count1++;
                        if(shake_hands_count1>=2)
                        {
                            shake_hands_count1=0;
                            *(ptr+i)=0;
                        }
                    }
                    if(i==1)
                    {
                        shake_hands_count2++;
                        if(shake_hands_count2>=2)
                        {
                            shake_hands_count2=0;
                            *(ptr+i)=0;
                        }
                    }
                    
                }                
            }
            
        }
    }
        
	return err;
}
/************************************************************** 
 函数说明      测试电机
                                        
**************************************************************/

uint8 Text_motor(uint16 row)
{
     uint8 err=0;
	 //roj_write_remote_para(parameter_addr(row),get_addr(row),local_addr(row),1,0xc1,&err);
     write_remote_para16(parameter_addr(row),local_addr(row),para[get_addr(row)],&err);	
     if(err==1)
     {
        	 
     } 
	 return err;
}

/************************************************************** 
 函数说明     退出  测试电机
                                        
**************************************************************/

uint8 Exit_text_motor(uint16 row)
{
     uint8 err=0;
	 //roj_write_remote_para(0,0xf3,local_addr(row),0,0xc2,&err);
     write_remote_para16(parameter_addr(row),local_addr(row),para[get_addr(row)],&err);	
     if(err==1)
     {
        	 
     } 
	 return err;
}

