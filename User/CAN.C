/***********************************************************************
文件名称：CAN.C
功    能：
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/
#include "main.h"
#include "can.h"

unsigned char CAN1_data[8];
unsigned char can1_rec_flag = 0;

extern int32_t speed_read_value[4];
extern int32_t position_read_value[4];
int write_speed_value(int IDX,int32_t speed_value);
int write_position_value(int IDX,int32_t position_value);

CanRxMsg RxMessage;
//格式： 波特率  CAN_SJW 	CAN_BS1  CAN_BS2 CAN_Prescaler 参考CAN_Baud_Process(unsigned int Baud,CAN_InitTypeDef *CAN_InitStructure)
const unsigned int CAN_baud_table[CAN_BAUD_NUM][5] = 
{
//波特率， CAN_SJW，   CAN_BS1，    CAN_BS2，CAN_Prescaler 
	{5,   CAN_SJW_1tq,CAN_BS1_13tq,CAN_BS2_2tq,450},		//未通			
	{10,  CAN_SJW_1tq,CAN_BS1_6tq,CAN_BS2_2tq, 400},		//未通			
	{15,  CAN_SJW_1tq,CAN_BS1_13tq,CAN_BS2_2tq,150},		//15K  未通
	{20,  CAN_SJW_1tq,CAN_BS1_6tq, CAN_BS2_2tq,200},		//20k //未通
	{25,  CAN_SJW_1tq,CAN_BS1_6tq, CAN_BS2_8tq,112},		//25k  未通
	{40,  CAN_SJW_1tq,CAN_BS1_6tq, CAN_BS2_2tq,100},		//40k  未通
	{50,  CAN_SJW_1tq,CAN_BS1_6tq, CAN_BS2_8tq,56},			//50k	ok
	{62,  CAN_SJW_1tq,CAN_BS1_13tq,CAN_BS2_2tq,36},			//62.5k
	{80,  CAN_SJW_1tq,CAN_BS1_6tq, CAN_BS2_2tq,50},			//80k   未通
	{100, CAN_SJW_1tq,CAN_BS1_6tq, CAN_BS2_8tq,28},			//100K	ok
	{125, CAN_SJW_1tq,CAN_BS1_13tq, CAN_BS2_2tq,18},		//125K 未通
	{200, CAN_SJW_1tq,CAN_BS1_6tq, CAN_BS2_8tq,14},			//200K  ok
	{250, CAN_SJW_1tq,CAN_BS1_15tq,CAN_BS2_5tq,8},		    //250k  ok
	{400, CAN_SJW_1tq,CAN_BS1_15tq, CAN_BS2_5tq,5},			//400K  ok
	{500, CAN_SJW_1tq,CAN_BS1_15tq,CAN_BS2_5tq,4},			//500K	ok
	{666, CAN_SJW_1tq,CAN_BS1_5tq, CAN_BS2_2tq,8},			//未通
	{800, CAN_SJW_1tq,CAN_BS1_8tq, CAN_BS2_3tq,14},			//800K 未通
	{1000,CAN_SJW_1tq,CAN_BS1_15tq,CAN_BS2_5tq,2},			//1000K	ok
};
/***********************************************************************
函数名称：CAN_Configuration(void)
功    能：完成can的配置
输入参数：
输出参数：
编写时间：
编 写 人：
注    意：
***********************************************************************/
void CAN_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	/* CAN GPIOs configuration **************************************************/

	/* Enable GPIO clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* Configure CAN RX and TX pins */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Connect CAN pins to AF9 */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN1); 

	/* CAN configuration ********************************************************/  
	/* Enable CAN clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	/* CAN register init */
	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);

	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = ENABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;



	CAN_Baud_Process(500,&CAN_InitStructure);
	CAN_Init(CAN1, &CAN_InitStructure);

	CAN_FilterInitStructure.CAN_FilterNumber = 0;	   //CAN1滤波器号从0到13

	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;	   //滤波屏蔽模式
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;	//不屏蔽任何ID
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;		//不屏蔽任何ID
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;	  // /*!< Specifies the FIFO (0 or 1) which will be assigned to the filter.
													  //This parameter can be a value of @ref CAN_filter_FIFO */
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure); 

	/* Enable FIFO 0 message pending Interrupt */
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}
/***********************************************************************
函数名称：CCAN_Baud_Process(unsigned int Baud,CAN_InitTypeDef *CAN_InitStructure)
功    能：计算波特率，返回
编写时间：2013.4.25
编 写 人：
注    意：CAN时钟为42M
CAN_SJW : CAN_SJW_1tq - CAN_SJW_4tq	  不能比任何一相位缓冲段长
CAN_BS1 : CAN_BS1_1tq - CAN_BS1_16tq
CAN_BS2 : CAN_BS2_1tq - CAN_BS2_8tq
CAN_Prescaler : 1 - 1024
	配置说明：
CAN_SJW + CAN_BS1 / (CAN_SJW + CAN_BS1 + CAN_BS2)
	0.75     baud > 800k
	0.80     baud > 500k
	0.875    baud <= 500k
	baud = 42M / (CAN_SJW + CAN_BS1 + CAN_BS2) / CAN_Prescaler
***********************************************************************/
void CAN_Baud_Process(unsigned int Baud,CAN_InitTypeDef *CAN_InitStructure)
{
	unsigned int i = 0;
	for(i = 0;i < CAN_BAUD_NUM;i ++)
	{
		if(Baud == CAN_baud_table[i][0])
		{
			CAN_InitStructure->CAN_SJW = CAN_baud_table[i][1];
			CAN_InitStructure->CAN_BS1 = CAN_baud_table[i][2];
			CAN_InitStructure->CAN_BS2 = CAN_baud_table[i][3];
			CAN_InitStructure->CAN_Prescaler = CAN_baud_table[i][4];
			return;	
		}
	}	
}
/***********************************************************************
函数名称：CAN1_RX0_IRQHandler(void)
功    能：CAN1中断函数
输入参数：
输出参数：CAN1_data[8]
编写时间：
编 写 人：
注    意：
***********************************************************************/
void CAN1_RX0_IRQHandler(void)
{
//	CanRxMsg RxMessage;
	unsigned int i = 0;
	int32_t temp_value=0;
	RxMessage.StdId = 0x00;//状态清零
	RxMessage.ExtId = 0x00;
	RxMessage.IDE = 0;
	RxMessage.DLC = 0;
	RxMessage.FMI = 0;
	
		for (i = 0; i < 8; i++)
	{
		RxMessage.Data[i] = 0x00;//缓冲区清零
	}	
	
	for(i = 0;i < 8;i ++)
	{
		CAN1_data[i] = 	RxMessage.Data[i];
	}
	
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	
	if(((RxMessage.StdId>>4)&0xff)==0x58)//收到反馈
	{
		temp_value=RxMessage.Data[7]*0x01000000+RxMessage.Data[6]*0x010000+RxMessage.Data[5]*0x0100+RxMessage.Data[4]*0x01;
		if(((RxMessage.StdId>>0)&0x0f)==N1)
		{
			if(RxMessage.Data[0]==0x43&&RxMessage.Data[1]==0x69&&RxMessage.Data[2]==0x60)//速度
			{
				write_speed_value(0,temp_value);
			}
			else if(RxMessage.Data[0]==0x43&&RxMessage.Data[1]==0x40&&RxMessage.Data[2]==0x22)//位置
			{
				write_position_value(0,temp_value);
			}
		}
		else if(((RxMessage.StdId>>0)&0x0f)==N2)
		{
			if(RxMessage.Data[0]==0x43&&RxMessage.Data[1]==0x69&&RxMessage.Data[2]==0x60)//速度
			{
				write_speed_value(1,temp_value);
			}
			else if(RxMessage.Data[0]==0x43&&RxMessage.Data[1]==0x40&&RxMessage.Data[2]==0x22)//位置
			{
				write_position_value(1,temp_value);
			}
		}
		else if(((RxMessage.StdId>>0)&0x0f)==N3)
		{
			if(RxMessage.Data[0]==0x43&&RxMessage.Data[1]==0x69&&RxMessage.Data[2]==0x60)//速度
			{
				write_speed_value(2,temp_value);
			}
			else if(RxMessage.Data[0]==0x43&&RxMessage.Data[1]==0x40&&RxMessage.Data[2]==0x22)//位置
			{
				write_position_value(2,temp_value);
			}
		}
		else if(((RxMessage.StdId>>0)&0x0f)==N4)
		{
			if(RxMessage.Data[0]==0x43&&RxMessage.Data[1]==0x69&&RxMessage.Data[2]==0x60)//速度
			{
				write_speed_value(3,temp_value);
			}
			else if(RxMessage.Data[0]==0x43&&RxMessage.Data[1]==0x40&&RxMessage.Data[2]==0x22)//位置
			{
				write_position_value(3,temp_value);
			}
		}
	}
	
	
	
	can1_rec_flag = 1;
	CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);  /* 清除挂起中断 */
}


int write_speed_value(int IDX,int32_t speed_value)
{
	speed_read_value[IDX]=speed_value;
	return 0;
}
int write_position_value(int IDX,int32_t position_value)
{
	position_read_value[IDX]=position_value;
	return 0;
}

/***********************************************************************
函数名称：CAN1_WriteData(void)
功    能：CAN1发送函数
输入参数：ID和CAN1_data
输出参数：
编写时间：
编 写 人：
注    意： 扩展数据帧，8字节长度，ID
***********************************************************************/
void CAN1_WriteData(unsigned int ID, uint8_t *data,int len)
{
		
	unsigned int i;
	uint8_t transmit_mailbox = 0;
	CanTxMsg TxMessage;
	
	TxMessage.StdId = ID;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA; /* 设置为数据帧 */
	TxMessage.DLC = len;            /* 数据长度, can报文规定最大的数据长度为8字节 */
	for(i = 0;i < 8; i ++)
	{
		TxMessage.Data[i] = data[i];
	}
	transmit_mailbox = CAN_Transmit(CAN1,&TxMessage);  /* 返回这个信息请求发送的邮箱号0,1,2或没有邮箱申请发送no_box */	
	while((CAN_TransmitStatus(CAN1, transmit_mailbox)  !=  CANTXOK) && (i  !=  0xffFF))
	{
		i ++;
	}
}
