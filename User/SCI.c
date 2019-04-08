
#include "main.H"
#include "SCI.H"
/*********************************************************************
文件名称：SCI.C
功    能：重载printf
编写时间：2018.3.15
编 写 人：MZM
注    意：
***********************************************************************/  
#if SYSTEM_SUPPORT_OS
#include "includes.h"				
#endif
#if 1
#pragma import(__use_no_semihosting)             
             
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
  
void _sys_exit(int x) 
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0); 
	USART1->DR = (u8) ch;      
	return ch;
}
#endif


/***********************************************************************
文件名称：SCI.C
功    能：完成对usart1和usart2的操作
编写时间：2012.11.22
编 写 人：
注    意：本例程是通过判断两个特定的字符来确定一帧数据是否结束的。
USART1 时钟 : RCC_APB2PeriphClockCmd
USART1~6 时钟 :RCC_APB1PeriphClockCmd
***********************************************************************/

volatile unsigned char RS232_REC_Flag = 0;
volatile unsigned char RS232_buff[RS232_REC_BUFF_SIZE];//用于接收数据
volatile unsigned int RS232_rec_counter = 0;//用于RS232接收计数

volatile unsigned char UART4_REC_Flag = 0;
volatile unsigned char UART4_buff[UART4_REC_BUFF_SIZE];//用于接收数据
volatile unsigned int UART4_rec_counter = 0;//用于RS232接收计数

static void RS485_Delay(uint32_t nCount);


void USART_Configuration(void)
{ 
	
	GPIO_InitTypeDef GPIO_InitStructure;//定义GPIO_InitTypeDef类型的结构体成员GPIO_InitStructure

	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct;
	//使能需要用到的GPIO管脚时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOD, ENABLE);
	//使能USART1 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	///复位串口1
	USART_DeInit(USART1);
	
	USART_StructInit(&USART_InitStructure);//载入默认USART参数
	USART_ClockStructInit(&USART_ClockInitStruct);//载入默认USART参数        
	//配置串口1的管脚 PA8 USART1_EN PA9 USART1_TX PA10 USART1_RX    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    //复用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);        //管脚PA9复用为USART1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;        
	GPIO_Init(GPIOA, &GPIO_InitStructure);                                                                                                                 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	USART_ClockInit(USART1,&USART_ClockInitStruct);


	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure); 

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);        ///////接收中断使能
	USART_ClearITPendingBit(USART1, USART_IT_TC);//清除中断TC位
	USART_Cmd(USART1,ENABLE);//最后使能串?
}

/***********************************************************************
函数名称：void USART1_IRQHandler(void) 
功    能：完成SCI的数据的接收，并做标识
输入参数：
输出参数：
编写时间：2012.11.22
编 写 人：
注    意  RS232用的是USART1.
***********************************************************************/
extern char* back_cmd;
void USART1_IRQHandler(void)  
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{	
		RS232_buff[RS232_rec_counter] = USART1->DR;//
		RS232_rec_counter ++;
/********以RS232_END_FLAG1和RS232_END_FLAG2定义的字符作为一帧数据的结束标识************/
		if(RS232_rec_counter >= 3)	//只有接收到2个数据以上才做判断
		{
			if(RS232_buff[RS232_rec_counter - 2] == back_cmd[0] && 
				RS232_buff[RS232_rec_counter - 1] == back_cmd[1] && 
				RS232_buff[RS232_rec_counter - 0] == back_cmd[2] ) 	//帧起始标志   
			{
				RS232_REC_Flag = 1;
			}
		}
		if(RS232_rec_counter >= RS232_REC_BUFF_SIZE)//超过接收缓冲区大小
		{
			RS232_rec_counter = 0;
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET) 
	{
        USART_ClearITPendingBit(USART1, USART_IT_TXE);           /* Clear the USART transmit interrupt                  */
    }	
}

/***********************************************************************
函数名称：RS232_Send_Data(unsigned char *send_buff,unsigned int length)
功    能：RS232发送字符串
输入参数：send_buff:待发送的数据指针；length：发送的数据长度（字符个数）
输出参数：
编写时间：2012.11.22
编 写 人：
注    意：
***********************************************************************/
void RS232_Send_Data(unsigned char *send_buff,unsigned int length)
{
 	unsigned int i = 0;
	for(i = 0;i < length;i ++)
	{			
		USART1->DR = send_buff[i];
		while((USART1->SR&0X40)==0);	
	}	
}

/***********************************************************************
函数名称：void RS485_Delay(uint32_t nCount)
功    能：RS485收发延时函数
输入参数：
输出参数：
编写时间：2012.11.22
编 写 人：
注    意：
***********************************************************************/
// static void RS485_Delay(uint32_t nCount)
// { 
//   while(nCount > 0)
//   { 
//   	  nCount --;   
//   }
// }


void UART4_Configuration(void)
{ 
	
	GPIO_InitTypeDef GPIO_InitStructure;//定义GPIO_InitTypeDef类型的结构体成员GPIO_InitStructure

	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct;
	//使能需要用到的GPIO管脚时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	//使能USART1 时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	///复位串口1
	USART_DeInit(UART4);
	
	USART_StructInit(&USART_InitStructure);//载入默认USART参数
	USART_ClockStructInit(&USART_ClockInitStruct);//载入默认USART参数        
	//配置串口1的管脚 PA8 USART1_EN PA9 USART1_TX PA10 USART1_RX    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    //复用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4);        //管脚PA9复用为USART1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;        
	GPIO_Init(GPIOC, &GPIO_InitStructure);                                                                                                                 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4);
	
	USART_ClockInit(UART4,&USART_ClockInitStruct);


	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4,&USART_InitStructure); 

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);        ///////接收中断使能
	USART_ClearITPendingBit(UART4, USART_IT_TC);//清除中断TC位
	USART_Cmd(UART4,ENABLE);//最后使能串?


}

void UART4_Send_Data(unsigned char *send_buff,unsigned int length)
{
 	unsigned int i = 0;
	for(i = 0;i < length;i ++)
	{			
		UART4->DR = send_buff[i];
		while((UART4->SR&0X40)==0);	
	}	
}

void UART4_IRQHandler(void)  
{
	USART_ClearFlag(UART4,USART_FLAG_TC);
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{	
		UART4_buff[UART4_rec_counter] = UART4->DR;//
//		RS232_Send_Data(UART4_buff+UART4_rec_counter,1);
		UART4_rec_counter ++;
/********以RS232_END_FLAG1和RS232_END_FLAG2定义的字符作为一帧数据的结束标识************/
//		if(UART4_rec_counter >= 2)	//只有接收到2个数据以上才做判断
//		{
//			if(UART4_buff[RS232_rec_counter - 1] == RS232_END_FLAG1 && RS232_buff[RS232_rec_counter - 1] == RS232_END_FLAG2) 	//帧起始标志   
//			{
//				RS232_REC_Flag = 1;
//			}
//		}
		if(UART4_rec_counter >= UART4_REC_BUFF_SIZE)//超过接收缓冲区大小
		{
			UART4_rec_counter = 0;
		}
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
	}
	if (USART_GetITStatus(UART4, USART_IT_TXE) != RESET) 
	{
        USART_ClearITPendingBit(UART4, USART_IT_TXE);           /* Clear the USART transmit interrupt                  */
  }	
}

unsigned int crc_cal_by_bit(unsigned char *ptr, unsigned int len) {
    unsigned int crc = 0;
    while (len-- != 0) {
        for (unsigned char i = 0x80; i != 0; i /= 2) {
            crc *= 2;
            if ((crc & 0x10000) !=
                0) //上一位CRC乘2后，若首位是1，则除以0x11021 
                crc ^= 0x11021;
            if ((*ptr & i) != 0) //如果本位是1，那么CRC = 上一位的CRC + 本位/CRC_CCITT 
                crc ^= 0x1021;
        }
        ptr++;
    }
    return crc;
}

