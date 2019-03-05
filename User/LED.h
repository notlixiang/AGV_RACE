/***********************************************************************
�ļ����ƣ�LED.h
��    �ܣ�led  IO��ʼ��
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
#include "main.h"
#ifndef _LED_H_
#define _LED_H_

#define LED1_OFF 		GPIO_ResetBits(GPIOE , GPIO_Pin_7)
#define LED2_OFF 		GPIO_ResetBits(GPIOE , GPIO_Pin_8)
#define LED3_OFF 		GPIO_ResetBits(GPIOE , GPIO_Pin_9)
#define LED4_OFF		GPIO_ResetBits(GPIOE , GPIO_Pin_10)


#define LED1_ON 		GPIO_SetBits(GPIOE , GPIO_Pin_7)
#define LED2_ON		GPIO_SetBits(GPIOE , GPIO_Pin_8)
#define LED3_ON 		GPIO_SetBits(GPIOE , GPIO_Pin_9)
#define LED4_ON 		GPIO_SetBits(GPIOE , GPIO_Pin_10)

void LED_Configuration(void);
void LED_Blink(void);
void One_LED_ON(unsigned char led_num);
void static LED_Delay(uint32_t nCount);
void LED_ON(void);
void LED_OFF(void);
#endif
