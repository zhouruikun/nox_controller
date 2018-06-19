#ifndef _CAN_H_
#define _CAN_H_
#include "stm32f10x.h"
 
void  CAN1_Com_init(void);
int CAN1_Tx_msg(CanTxMsg TxMessage);
int CAN1_Tx_data(void);
void  CAN1_Rx_Data(CanRxMsg RxMessage);

#endif