/***********************************************************************
�ļ����ƣ�SysTick.C
��    �ܣ�
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
#include "main.h"
 __IO uint32_t TimingDelay;
unsigned char time_flag = 0;

  /* Setup SysTick Timer for 1 msec interrupts.
     ------------------------------------------
    1. The SysTick_Config() function is a CMSIS function which configure:
       - The SysTick Reload register with value passed as function parameter.
       - Configure the SysTick IRQ priority to the lowest value (0x0F).
       - Reset the SysTick Counter register.
       - Configure the SysTick Counter clock source to be Core Clock Source (HCLK).
       - Enable the SysTick Interrupt.
       - Start the SysTick Counter.
    
    2. You can change the SysTick Clock source to be HCLK_Div8 by calling the
       SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8) just after the
       SysTick_Config() function call. The SysTick_CLKSourceConfig() is defined
       inside the misc.c file.

    3. You can change the SysTick IRQ priority by calling the
       NVIC_SetPriority(SysTick_IRQn,...) just after the SysTick_Config() function 
       call. The NVIC_SetPriority() is defined inside the core_cm3.h file.

    4. To adjust the SysTick time base, use the following formula:
                            
         Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)
    
       - Reload Value is the parameter to be passed for SysTick_Config() function
       - Reload Value should not exceed 0xFFFFFF
   */
/***********************************************************************
�������ƣ�SysTick_Configuration(void)
��    �ܣ� 1ms�ж�һ��
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
void SysTick_Configuration(void)
{
	if (SysTick_Config(SystemCoreClock / 1000))
	{ 
		/* Capture error */ 
		while (1);
	}
}


/***********************************************************************
�������ƣ�Delay(__IO uint32_t nTime)
��    �ܣ� ��ʱ����λms
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
void Delay(__IO uint32_t nTime)
{ 
	TimingDelay = nTime;
	while(TimingDelay != 0);
}
/***********************************************************************
�������ƣ�TimingDelay_Decrement(void)
��    �ܣ� ��ʱ������
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺ ���жϺ��������
***********************************************************************/
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}
/***********************************************************************
�������ƣ�SysTick_Handler(void)
��    �ܣ� SysTick�жϺ���
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
void SysTick_Handler(void)
{
	static unsigned cpu_led_counter = 0;
	
	TimingDelay_Decrement();//������ʱ
	cpu_led_counter ++;
	if(cpu_led_counter >= 500)
	{
		time_flag = 1;
		cpu_led_counter = 0;
	}
}
