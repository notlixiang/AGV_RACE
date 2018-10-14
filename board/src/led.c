#include "led.h"

void LED_Init(void)
{
  	GPIO_InitTypeDef  GPIO_InitStructure;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;         //PB0
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	
	//> ǧ�ﶥ
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	//> ���̵���
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	//> �������
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	//> ָʾ��
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	
	//> ����
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//> eeprom
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	//> 485ͨѶ
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //> 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //> ����ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//> CANͨѶ
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //> ����ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//> 232ͨѶ
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;         
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //> ���ģʽ
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //> ��©���
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //> ����������
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	
	

}

void LEDOff(Led_Def Led)//LED��
{
  	LED_PORT[Led]->BSRRL=LED_PIN[Led];
}

void LEDOn(Led_Def Led)//LED��
{
  	LED_PORT[Led]->BSRRH=LED_PIN[Led];  
}

void LEDTog(Led_Def Led)//LED״̬��ת
{
  	LED_PORT[Led]->ODR^=LED_PIN[Led];
}



