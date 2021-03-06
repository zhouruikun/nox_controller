#ifndef __SPI1_H
#define __SPI1_H			 


/*----------------FM25CL64����--------------------*/
#define  WREN_INST           0x06     //дʹ��
#define  WRDI_INST           0x04     //д��ֹ
#define  RDSR_INST           0x05     //��״̬�Ĵ���
#define  WRSR_INST           0x01     //д״̬�Ĵ���
#define  WRITE_INST          0x02     //д����
#define  READ_INST           0x03     //������

/*----------------CSƬѡ�ź�--------------------*/
#define FLASH_CS_0			GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define FLASH_CS_1			GPIO_SetBits(GPIOA,GPIO_Pin_4)

/*-----------------Ӧ�ú���---------------------*/
void SPI1_init(void);	//��ʼ��SPI

u8 SPI1_ReadByte(void);	    //�����ֽ�
u8 SPI1_WriteByte(u8 byte);	//�����ֽ�

void wren_cmd(void); //дʹ��
void wrdi_cmd(void);//д��ֹ
u8 rdsr_cmd(void);//��״̬�Ĵ���
void wrsr_cmd(u8 status);//д״̬�Ĵ���
void wrpara(uint16 reg_addr,uint16 reg_val);//д�ֽ�
void write_fm2564(void *ram_addr,uint16 len,uint16 fram_addr);//д���ݴ�
uint16 read_para(uint16 reg_addr); //���ֽ�
void read_fm2564(void *ram_addr,uint16 len,uint16 fram_addr);  //�����ݴ�



#endif

