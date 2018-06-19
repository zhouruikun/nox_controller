#ifndef __Calculate_val_H
#define __Calculate_val_H	

#ifdef   Calculate_val_globals
#define  Calculate_val_ext
#else
#define  Calculate_val_ext  extern
#endif
u16 Sequence_buff(u16 *buff,u8 ubit,u8 chall);//buff的数据排序

void MeasureAndSend(void);
void Int_to_ascii(u8 *dptr,uint32 shu,uint8 wei);
float air_pressure(void);
float wind_speed(void);
#ifdef Calculate_val_globals

/************************************************************** 
 函数说明：
**************************************************************/ 


//Calculate_val_ext uint8 str[5];
Calculate_val_ext u32 adcadd;
//                  AD压力累加缓存
Calculate_val_ext uint16 pressure_timer_count,pressure_add_count;
//                  测量压力时定时计数    计压力AD值累加个数
Calculate_val_ext uint8 input_flag,pressure_timer1s_flag;
//                   压力值输入标志位   压力定时一秒标志位
Calculate_val_ext float ax,bx,A_valf,B_valf;


#else



Calculate_val_ext u32 adcadd;
//                  AD压力累加缓存
Calculate_val_ext uint16 pressure_timer_count,pressure_add_count;
//                  测量压力时定时计数    计压力AD值累加个数
Calculate_val_ext uint8 input_flag,pressure_timer1s_flag;
//                   压力值输入标志位   压力定时一秒标志位
Calculate_val_ext float ax,bx,A_valf,B_valf;

//Calculate_val_ext uint8 str[5],;

#endif
#endif
