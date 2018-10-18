/***********************************************************************
�ļ����ƣ�SCI.h
��    �ܣ�
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺
***********************************************************************/
#ifndef  _SCI_H_
#define  _SCI_H_
#include "main.h"

#define RS232_REC_BUFF_SIZE				25
#define RS232_END_FLAG1	0x01		//RS232һ�����ݽ�����־1 
#define RS232_END_FLAG2	0x01			//RS232һ�����ݽ�����־2 
typedef struct __FILE FILE;

extern volatile unsigned char RS232_REC_Flag ;
extern volatile unsigned char RS232_buff[RS232_REC_BUFF_SIZE] ;//���ڽ�������
extern volatile unsigned int RS232_rec_counter ;//����RS232���ռ���

#define UART4_REC_BUFF_SIZE				50
extern volatile unsigned char UART4_REC_Flag ;
extern volatile unsigned char UART4_buff[UART4_REC_BUFF_SIZE];//用于接收数据
extern volatile unsigned int UART4_rec_counter;//用于RS232接收计数


void RS232_Send_Data(unsigned char *send_buff,unsigned int length);
static void RS485_Delay(uint32_t nCount);
void USART_Configuration(void);
void UART4_Configuration(void);
void UART4_Send_Data(unsigned char *send_buff,unsigned int length);

#endif
