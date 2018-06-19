#ifndef combas_h
#define combas_h
#ifdef combas_gbl
#define combas_ext
#else
#define combas_ext extern
#endif

typedef struct com_obj_tag *com_obj;

//fifo=8;
combas_ext com_obj init_com_obj(void);
// int_noÎªÖÐ¶Ï±àºÅ
combas_ext void init_send(com_obj com1,uint8 len);
combas_ext void uart_send(com_obj  com1,uint32 uart_addr);

combas_ext void uart_rcv(com_obj com1,uint32 uart_addr);

combas_ext void rtu_start_timing(com_obj com1);

combas_ext void ClrRcvFIFO(uint32 uart_addr);

combas_ext uint8 *get_inbuf(com_obj com1);
combas_ext uint8 *get_outbuf(com_obj com1);


combas_ext uint8 get_sd_len(com_obj com1);
combas_ext uint8 get_end_rec(com_obj com1);

combas_ext uint32 UART_RXFF_Get(unsigned long ulBase);
combas_ext uint32 UART_TXFE_Get(unsigned long ulBase);
combas_ext uint32 UART_BE_Get(unsigned long ulBase);
combas_ext void UART_O_CTL_Set(unsigned long ulBase,unsigned long ulControl);

#endif

