/***********************************************************************
�ļ����ƣ�SCI.h
��    �ܣ�
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺
***********************************************************************/
#ifndef  _SCI_H_
#define  _SCI_H_


#define RS232_REC_BUFF_SIZE				25
#define RS232_END_FLAG1	0x01		//RS232һ�����ݽ�����־1 
#define RS232_END_FLAG2	0x01			//RS232һ�����ݽ�����־2 
typedef struct __FILE FILE;

extern volatile unsigned char RS232_REC_Flag ;
extern volatile unsigned char RS232_buff[RS232_REC_BUFF_SIZE] ;//���ڽ�������
extern volatile unsigned int RS232_rec_counter ;//����RS232���ռ���

void RS232_Send_Data(unsigned char *send_buff,unsigned int length);
static void RS485_Delay(uint32_t nCount);
void USART_Configuration(void);


void USART6_Configuration(void);
extern volatile unsigned char USART6_REC_Flag ;
extern volatile unsigned char USART6_buff[RS232_REC_BUFF_SIZE];//用于接收数据
extern volatile unsigned int USART6_rec_counter ;//用于RS232接收计数
#endif
