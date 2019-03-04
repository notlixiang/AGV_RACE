#include "ks103.h"
#include "delay.h"
#include "myiic.h"



u8 KS103_ReadOneByte(u8 address, u8 reg)
{ 
u8 temp=0;
IIC_Start();
IIC_Send_Byte(address); //���͵͵�ַ
IIC_Wait_Ack();
IIC_Send_Byte(reg); //���͵͵�ַ
IIC_Wait_Ack();
IIC_Start();
IIC_Send_Byte(address + 1); //�������ģʽ 
IIC_Wait_Ack();
delay_us(50);  //���Ӵ˴���ͨ�ųɹ�������
temp=IIC_Read_Byte(0);  //���Ĵ��� 3
IIC_Stop();//����һ��ֹͣ���� 
return temp;
}


void KS103_WriteOneByte(u8 address,u8 reg,u8 command)
{ 
IIC_Start();
IIC_Send_Byte(address);  //����д����
IIC_Wait_Ack();
IIC_Send_Byte(reg);//���͸ߵ�ַ
IIC_Wait_Ack();
IIC_Send_Byte(command); //���͵͵�ַ
IIC_Wait_Ack();
IIC_Stop();//����һ��ֹͣ����
}
