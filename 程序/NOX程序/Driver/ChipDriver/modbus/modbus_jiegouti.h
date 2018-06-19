#ifndef _modbus_jiegouti_H_
#define _modbus_jiegouti_H_

#ifdef   modbus_jiegouti_globals
#define  modbus_jiegouti_ext
#else
#define  modbus_jiegouti_ext  extern   
#endif

typedef struct	 
{
        uint8  node_addr;//地址             1
        uint8  cmd;//功能码                 2
        uint16   data_addr;//寄存器地址     3，4
        uint16   content;//寄存器值         5，6
        uint8  zl_len;                    //7 
}cmd06_obj;

typedef struct{
            uint8  node_addr;//本机地址     8
            uint8 cmd;//功能码              9
            uint16 data_addrl;//寄存器地址  10,11
            uint16 data_len;//寄存器数量    12
}req03_obj;

typedef struct{
            uint8  node_addr;//本机地址     13
            uint8  cmd;//功能码             14
            uint8  bytelen;//字节           15
   			uint16 data_addr2;//发送寄存器地址  16
	        uint16 in_data_adrr;//接收寄存器地址
   			uint8  zl_len;                //17
   			//uint16 para[5];//数据           18,19,20,21,22,23,24,25,26,27
            //uint16 at[5];
			uint16 para_1[100];
            }back03_obj;

typedef struct{
            uint8 slave_addr;//从机地址    28
            uint8 fun_num;//功能           29
            uint8 filebyte;//字节数        30
            uint8 reftype;//参考类型       31
            uint16 fileno;//文件号         32,33
            uint16 rec_no;//记录号         34,35
            uint16 rec_len;//记录长度      36,37
            }req20_obj;

typedef struct{
            uint8 node_addr;//本机地址     38
            uint8 fun_num;//功能码         39
            uint8 data_byte;//响应数据长度 40
            uint8 file_len;//文件响应长度  41
            uint8 reftype;//参考类型       42
            uint16 dataptr[100];//记录数据 要以3的倍数放大
            uint16 fileno;//文件号         61,62
            uint16 rec_no;//记录号         63,64
			uint16 rec_len;//记录长度      65,66
           }back20_obj;

typedef struct{
            uint8 node_addr;//本机地址     67
            uint8 fun_num;//功能码         68
            uint8 data_l;//数据长度        69
            uint8 reftype;//参考类型       70
            uint16 fileno;//文件号         71,72
            uint16 rec_no;//记录号         73,74
            uint16 rec_len;//记录长度      75
            uint16  dataptr[100];//记录数据,要以3的倍数放大
            }cmd21_obj;

typedef struct{
			  uint8  node_addr;//本机地址
              uint8  cmd;//功能码
              uint16  strat_address;//起始地址 
			  uint16  data_len;//寄存器数量
			  uint8 byte;//字节数
			  uint16 dataptr[2];//值
              }cmd16_obj;


modbus_jiegouti_ext cmd06_obj cmd06;
modbus_jiegouti_ext req03_obj req03;
modbus_jiegouti_ext back03_obj back03;
modbus_jiegouti_ext req20_obj  req20;
modbus_jiegouti_ext back20_obj back20;
modbus_jiegouti_ext cmd21_obj cmd21;
modbus_jiegouti_ext cmd16_obj cmd16;

#endif

