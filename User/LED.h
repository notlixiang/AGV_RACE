/***********************************************************************
�ļ����ƣ�LED.h
��    �ܣ�led  IO��ʼ��
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/

#ifndef _LED_H_
#define _LED_H_

#define LED1_OFF 		GPIO_ResetBits(GPIOB , GPIO_Pin_0)
#define LED2_OFF 		GPIO_ResetBits(GPIOB , GPIO_Pin_1)
#define LED3_OFF 		GPIO_ResetBits(GPIOB , GPIO_Pin_2)
#define LED4_OFF		GPIO_ResetBits(GPIOF , GPIO_Pin_11)


#define LED1_ON 		GPIO_SetBits(GPIOB , GPIO_Pin_0)
#define LED2_ON		GPIO_SetBits(GPIOB , GPIO_Pin_1)
#define LED3_ON 		GPIO_SetBits(GPIOB , GPIO_Pin_2)
#define LED4_ON 		GPIO_SetBits(GPIOF , GPIO_Pin_11)

void LED_Configuration(void);
void LED_Blink(void);
void One_LED_ON(unsigned char led_num);
void static LED_Delay(uint32_t nCount);
void LED_ON(void);
void LED_OFF(void);
#endif
