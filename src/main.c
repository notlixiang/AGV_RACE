#include "main.h"
////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	LED_Init();
	GPIO_SetBits( GPIOB, GPIO_Pin_0);
	while(1)
	{
		GPIO_ResetBits( GPIOB, GPIO_Pin_0);
		GPIO_WriteBit( GPIOF, GPIO_Pin_12, Bit_RESET); //> 千斤顶
		GPIO_WriteBit( GPIOF, GPIO_Pin_13, Bit_RESET); //> 千斤顶
		GPIO_WriteBit( GPIOF, GPIO_Pin_11, Bit_RESET); //> 充电继电器
		GPIO_WriteBit( GPIOG, GPIO_Pin_12, Bit_RESET); //> 备用输出
		GPIO_WriteBit( GPIOG, GPIO_Pin_13, Bit_RESET); //> 备用输出
		GPIO_WriteBit( GPIOG, GPIO_Pin_14, Bit_RESET); //> 备用输出
		GPIO_WriteBit( GPIOG, GPIO_Pin_15, Bit_RESET); //> 备用输出
		
		GPIO_WriteBit( GPIOF, GPIO_Pin_14, Bit_RESET); //> 指示灯
		GPIO_WriteBit( GPIOF, GPIO_Pin_15, Bit_RESET); //> 指示灯
		GPIO_WriteBit( GPIOG, GPIO_Pin_0, Bit_RESET); //> 指示灯
		GPIO_WriteBit( GPIOG, GPIO_Pin_1, Bit_RESET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_7, Bit_RESET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_8, Bit_RESET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_9, Bit_RESET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_10, Bit_RESET); //> 指示灯
		
		GPIO_WriteBit( GPIOB, GPIO_Pin_6, Bit_RESET); //> 超声
		GPIO_WriteBit( GPIOB, GPIO_Pin_7, Bit_RESET); //> 超声
		
		GPIO_WriteBit( GPIOF, GPIO_Pin_0, Bit_RESET); //> I2C
		GPIO_WriteBit( GPIOF, GPIO_Pin_1, Bit_RESET); //> I2C
		
		GPIO_WriteBit( GPIOD, GPIO_Pin_4, Bit_RESET);
		GPIO_WriteBit( GPIOD, GPIO_Pin_5, Bit_RESET);
		
		GPIO_WriteBit( GPIOD, GPIO_Pin_1, Bit_RESET); //> CANt
		
		GPIO_WriteBit( GPIOA, GPIO_Pin_9, Bit_RESET);
		GPIO_WriteBit( GPIOB, GPIO_Pin_10, Bit_RESET);		
		
		delay_ms(3000);
		
		
		GPIO_SetBits( GPIOB, GPIO_Pin_0);
		GPIO_WriteBit( GPIOF, GPIO_Pin_12, Bit_SET); //> 千斤顶
		GPIO_WriteBit( GPIOF, GPIO_Pin_13, Bit_SET); //> 千斤顶
		GPIO_WriteBit( GPIOF, GPIO_Pin_11, Bit_SET); //> 充电继电器
		GPIO_WriteBit( GPIOG, GPIO_Pin_12, Bit_SET); //> 备用输出
		GPIO_WriteBit( GPIOG, GPIO_Pin_13, Bit_SET); //> 备用输出
		GPIO_WriteBit( GPIOG, GPIO_Pin_14, Bit_SET); //> 备用输出
		GPIO_WriteBit( GPIOG, GPIO_Pin_15, Bit_SET); //> 备用输出
		
		GPIO_WriteBit( GPIOF, GPIO_Pin_14, Bit_SET); //> 指示灯
		GPIO_WriteBit( GPIOF, GPIO_Pin_15, Bit_SET); //> 指示灯
		GPIO_WriteBit( GPIOG, GPIO_Pin_0, Bit_SET); //> 指示灯
		GPIO_WriteBit( GPIOG, GPIO_Pin_1, Bit_SET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_7, Bit_SET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_8, Bit_SET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_9, Bit_SET); //> 指示灯
		GPIO_WriteBit( GPIOE, GPIO_Pin_10, Bit_SET); //> 指示灯
		
		GPIO_WriteBit( GPIOB, GPIO_Pin_6, Bit_SET); //> 超声
		GPIO_WriteBit( GPIOB, GPIO_Pin_7, Bit_SET); //> 超声
		
		GPIO_WriteBit( GPIOF, GPIO_Pin_0, Bit_SET); //> I2C
		GPIO_WriteBit( GPIOF, GPIO_Pin_1, Bit_SET); //> I2C
		
		GPIO_WriteBit( GPIOD, GPIO_Pin_4, Bit_SET);
		GPIO_WriteBit( GPIOD, GPIO_Pin_5, Bit_SET);
		
		GPIO_WriteBit( GPIOD, GPIO_Pin_1, Bit_SET); //> CANt
		
		GPIO_WriteBit( GPIOA, GPIO_Pin_9, Bit_SET);
		GPIO_WriteBit( GPIOB, GPIO_Pin_10, Bit_SET);
		
		delay_ms(3000);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
