#ifndef _para_h
#define _para_h

#ifdef   para_globals
#define  para_ext
#else
#define  para_ext  extern
#endif
						
#define PID_AUX_flag  0X01
#define PID_REF_flag  0X02
 
//#define T0PTR   144.676   //1600  CYCLE
//#define nrpm    8

//#define min  (60000000/T0PTR)*nrpm     // 3317758    //  4561920      // 0x3f4800    //600s

//para_ext  parameter para_temp[200];  //read twice and cmp only

#define   para_size  32
para_ext  unsigned short para[para_size];      //at 0x0000  ---800---0x320   1)read twice and verify ,readonly after power   
#define   get_para(x)  para[x]   //can be changed to para[x].parameter easily
#define   set_para(x,y)  para[x]=y
 /*  parameter definition***********************************************/
#define Flux_AD1             para[0]//流量计1AD输入    输入范围0--5000  单位mV
#define Flux_DA1             para[1]//流量计1DA输出    输出范围0--5000  单位mV
#define Flux_Gata1           para[2]//流量计1伐控   0x0001:输出+15V  0x0002:输出-15V   其他：输出0V 
#define Flux_Save11          para[3]// 保留
#define Flux_Save12          para[4]// 保留
#define Flux_AD2             para[5]//
#define Flux_DA2             para[6]//
#define Flux_Gata2           para[7]// 
#define Flux_Save21          para[8]// 
#define Flux_Save22          para[9]// 
#define Flux_AD3             para[10]//
#define Flux_DA3             para[11]//
#define Flux_Gata3           para[12]// 
#define Flux_Save31          para[13]// 
#define Flux_Save32          para[14]// 
#define Flux_AD4             para[15]//
#define Flux_DA4             para[16]//
#define Flux_Gata4           para[17]// 
#define Flux_Save41          para[18]// 
#define Flux_Save42          para[19]// 
#define Filt_ratio					 para[20]// 
#define samp_time    				 para[21]// 
 


#endif

