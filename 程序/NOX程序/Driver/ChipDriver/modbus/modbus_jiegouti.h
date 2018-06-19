#ifndef _modbus_jiegouti_H_
#define _modbus_jiegouti_H_

#ifdef   modbus_jiegouti_globals
#define  modbus_jiegouti_ext
#else
#define  modbus_jiegouti_ext  extern   
#endif

typedef struct	 
{
        uint8  node_addr;//��ַ             1
        uint8  cmd;//������                 2
        uint16   data_addr;//�Ĵ�����ַ     3��4
        uint16   content;//�Ĵ���ֵ         5��6
        uint8  zl_len;                    //7 
}cmd06_obj;

typedef struct{
            uint8  node_addr;//������ַ     8
            uint8 cmd;//������              9
            uint16 data_addrl;//�Ĵ�����ַ  10,11
            uint16 data_len;//�Ĵ�������    12
}req03_obj;

typedef struct{
            uint8  node_addr;//������ַ     13
            uint8  cmd;//������             14
            uint8  bytelen;//�ֽ�           15
   			uint16 data_addr2;//���ͼĴ�����ַ  16
	        uint16 in_data_adrr;//���ռĴ�����ַ
   			uint8  zl_len;                //17
   			//uint16 para[5];//����           18,19,20,21,22,23,24,25,26,27
            //uint16 at[5];
			uint16 para_1[100];
            }back03_obj;

typedef struct{
            uint8 slave_addr;//�ӻ���ַ    28
            uint8 fun_num;//����           29
            uint8 filebyte;//�ֽ���        30
            uint8 reftype;//�ο�����       31
            uint16 fileno;//�ļ���         32,33
            uint16 rec_no;//��¼��         34,35
            uint16 rec_len;//��¼����      36,37
            }req20_obj;

typedef struct{
            uint8 node_addr;//������ַ     38
            uint8 fun_num;//������         39
            uint8 data_byte;//��Ӧ���ݳ��� 40
            uint8 file_len;//�ļ���Ӧ����  41
            uint8 reftype;//�ο�����       42
            uint16 dataptr[100];//��¼���� Ҫ��3�ı����Ŵ�
            uint16 fileno;//�ļ���         61,62
            uint16 rec_no;//��¼��         63,64
			uint16 rec_len;//��¼����      65,66
           }back20_obj;

typedef struct{
            uint8 node_addr;//������ַ     67
            uint8 fun_num;//������         68
            uint8 data_l;//���ݳ���        69
            uint8 reftype;//�ο�����       70
            uint16 fileno;//�ļ���         71,72
            uint16 rec_no;//��¼��         73,74
            uint16 rec_len;//��¼����      75
            uint16  dataptr[100];//��¼����,Ҫ��3�ı����Ŵ�
            }cmd21_obj;

typedef struct{
			  uint8  node_addr;//������ַ
              uint8  cmd;//������
              uint16  strat_address;//��ʼ��ַ 
			  uint16  data_len;//�Ĵ�������
			  uint8 byte;//�ֽ���
			  uint16 dataptr[2];//ֵ
              }cmd16_obj;


modbus_jiegouti_ext cmd06_obj cmd06;
modbus_jiegouti_ext req03_obj req03;
modbus_jiegouti_ext back03_obj back03;
modbus_jiegouti_ext req20_obj  req20;
modbus_jiegouti_ext back20_obj back20;
modbus_jiegouti_ext cmd21_obj cmd21;
modbus_jiegouti_ext cmd16_obj cmd16;

#endif

