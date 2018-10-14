/***********************************************************************
�ļ����ƣ�CAN.H
��    �ܣ�
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/

#ifndef _CAN_H_
#define _CAN_H_
#include "stdint.h"
#include "stm32f4xx_can.h"
#define CAN_BAUD_NUM    18		//�������ò����ʸ���

extern unsigned char CAN1_data[8];
extern unsigned char can1_rec_flag;
extern CanRxMsg RxMessage;

void CAN_IO_Configuration(void);
void CAN_Configuration(void);
void CAN1_WriteData(unsigned int ID, uint8_t *data,int len);
void CAN_Baud_Process(unsigned int Baud,CAN_InitTypeDef *CAN_InitStructure);


#endif
