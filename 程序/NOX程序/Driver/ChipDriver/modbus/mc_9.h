#ifndef _mc_9_h
#define _mc_9_h

#ifdef   mc_9_globals
#define  mc_9_ext
#else
#define  mc_9_ext  extern
#endif
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


mc_9_ext req20_obj  req20;
mc_9_ext back20_obj back20;
mc_9_ext cmd21_obj cmd21;


mc_9_ext void pack(uint8  *bufptr,uint8 shu);//解包
mc_9_ext uint8 un_pack(uint8 *bufptr,uint8 shu);
mc_9_ext void err_send(uint8 cmd,uint8 oerr,uint8 *obuff);
//master cmd20
mc_9_ext uint8 mback_cmd20(uint8 *abuf,  back20_obj *dptr);
mc_9_ext void  mreq_cmd20(req20_obj *dptr,  uint8 *obuf);

//master cmd21
mc_9_ext void  mreq_cmd21(cmd21_obj *dptr, uint8 *obuf );
mc_9_ext uint8 mback_cmd21(cmd21_obj *dptr, uint8 *abuf );

//slave cmd20
mc_9_ext uint8 srcv_cmd20(uint8 *buff, req20_obj *dptr);//写单个寄存器从机请求
mc_9_ext void ssend_cmd20(back20_obj *dptr,uint8 *p);//读保持寄存器响应
mc_9_ext void truck_req20_to_back20(req20_obj *dptr,back20_obj *pin);

//slave cmd21,the srcv_cmd21 is the same as mback_cmd21
mc_9_ext void ssend_cmd21(uint8 *buff, cmd21_obj *dptr);//写单个寄存器从机响应
//		uint8 mback_cmd21(cmd21_obj *dptr, uint8 *abuf );

mc_9_ext void err_send1(uint8 cmd,uint8 oerr,uint8 *obuff);


#endif
