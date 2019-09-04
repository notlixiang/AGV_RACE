/***********************************************************************
?l??????LED.C
??    ???led  IO??'??
??????2013.4.25
?? ? ???
?    ??
***********************************************************************/
#include "main.h"

/***********************************************************************
?????????LED_Configuration(void)
??    ??????LED??????
?????????
?????????
??????2013.4.25
?? ? ???
?    ??
***********************************************************************/
void LED_Configuration(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Enable the GPIO_LED Clock */
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE , ENABLE); 						 
			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOF , ENABLE); 						 
			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
		//> 指示灯
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> 输出模式
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> 开漏输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> 无上拉下拉
  	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> 输出模式
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> 开漏输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> 无上拉下拉
  	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> 输出模式
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> 开漏输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> 无上拉下拉
  	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> 输出模式
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> 开漏输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> 无上拉下拉
  	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> 输出模式
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> 开漏输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> 无上拉下拉
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> 输出模式
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> 开漏输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> 无上拉下拉
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> 输出模式
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> 开漏输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> 无上拉下拉
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> 输出模式
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> 开漏输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> 无上拉下拉
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/***********************************************************************
?????????LED_Blink(void)
??    ??????LED???
?????????
?????????
??????2013.4.25
?? ? ???
?    ??
***********************************************************************/
void LED_Blink(void)
{
	/*****??????led??******/
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
	LED_Delay(0x4fffff);
	/*****???????led??******/
	LED1_ON;
	LED2_ON;
	LED3_ON;
	LED4_ON;
	LED_Delay(0x4fffff);
}

void LED_ON(void)
{

//	LED1_ON;
//	LED2_ON;
//	LED3_ON;
//	LED4_ON;
	
		GPIO_WriteBit( GPIOF, GPIO_Pin_14, Bit_RESET); //> 指示灯
		GPIO_WriteBit( GPIOF, GPIO_Pin_15, Bit_RESET); //> 指示灯
		GPIO_WriteBit( GPIOG, GPIO_Pin_0, Bit_RESET); //> 指示灯
		GPIO_WriteBit( GPIOG, GPIO_Pin_1, Bit_RESET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_7, Bit_RESET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_8, Bit_RESET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_9, Bit_RESET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_10, Bit_RESET); //> 指示灯
		
}

void LED_OFF(void)
{

//	LED1_OFF;
//	LED2_OFF;
//	LED3_OFF;
//	LED4_OFF;
	GPIO_WriteBit( GPIOF, GPIO_Pin_14, Bit_SET); //> 指示灯
		GPIO_WriteBit( GPIOF, GPIO_Pin_15, Bit_SET); //> 指示灯
		GPIO_WriteBit( GPIOG, GPIO_Pin_0, Bit_SET); //> 指示灯
		GPIO_WriteBit( GPIOG, GPIO_Pin_1, Bit_SET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_7, Bit_SET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_8, Bit_SET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_9, Bit_SET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_10, Bit_SET); //> 指示灯
	
}
/***********************************************************************
?????????One_LED_ON(unsigned char led_num)
??    ?????????h??LED??
?????????
?????????
??????2013.4.25
?? ? ???
?    ??
***********************************************************************/
void One_LED_ON(unsigned char led_num)
{	
	/*****??????led??******/
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
	switch(led_num)
	{
		case 1:
		{
			LED1_ON;
			break;
		}
		case 2:
		{
			LED2_ON;
			break;		
		}
		case 3:
		{
			LED3_ON;
			break;		
		}
		case 4:
		{
			LED4_ON;
			break;		
		}
		default:
		{
			break;	
		}
	}		
}

void static LED_Delay(uint32_t nCount)
{ 
  while(nCount > 0)
  { 
  	  nCount --;   
  }
}

void Charging_Switch_ON(void)//PF11
{
	GPIO_WriteBit( GPIOF, GPIO_Pin_11, Bit_RESET);
}
	
void Charging_Switch_OFF(void)//PF11
{
	GPIO_WriteBit( GPIOF, GPIO_Pin_11, Bit_SET);
}
	