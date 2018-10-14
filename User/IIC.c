#include "IIC.h"
#include "delay.h"
 void I2C_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
		/* ʹ���� I2C�йص�ʱ�� */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE );  

	 /* PC3-I2C_SCL��PC5-I2C_SDA*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	IIC_SCL=1;
	IIC_SDA=1;
}


 u8 IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
	return 1;
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}



//���һ�β���ʱ�ȷ��͵�ַ���ٷ���0X51
u8 takeRangeReading(u8 Slave_Address){
	
  if(IIC_Start()==0)  //��ʼ�ź�
		{IIC_Stop(); return RESET;}           

    IIC_Send_Byte(Slave_Address);   //�����豸��ַ+д�ź�
 	  if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
    delay_us(40);  
		IIC_Send_Byte(0x51);    //�ڲ��Ĵ�����ַ��
 	  if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
   
		
		IIC_Stop();   	
		return SET;
}
//����

//��ȡһ�ξ�������ʱ�ȷ��͵�ַ���ٽ������ݸ��ֽ��ٽ������ݵ��ֽ�
u8 requestRange(u8 Slave_Address,uint16_t *distance){
	u8 REG_data[2]={0,0};
	
 
if(IIC_Start()==0)  //��ʼ�ź�
		{IIC_Stop(); return RESET;}          
	 
	IIC_Send_Byte(Slave_Address);    //�����豸��ַ+д�ź�
 	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
  delay_us(40);  
	REG_data[0]=IIC_Read_Byte(1);       //�����Ĵ�������

//	IIC_Ack();               //Ӧ��

	REG_data[1]=IIC_Read_Byte(0);       //�����Ĵ�������
	
//	IIC_NAck();     //����ֹͣ�����ź�
	
	IIC_Stop();                    //ֹͣ�ź�
	distance[0]=REG_data[0]<<8|REG_data[1];
	return SET;
}
//����
//�޸ĵ�ַʱ�ȷ��͵�ַ���ٷ���0xAA�ٷ���0xA5�ٷ����µ�ַ
u8 changeAddress(u8 oldAddress, u8 newAddress){
	
	
  if(IIC_Start()==0)  //��ʼ�ź�
		{IIC_Stop(); return RESET;}           

    IIC_Send_Byte(oldAddress);   //�����豸��ַ+д�ź�
 	  if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
			delay_us(40); 
		IIC_Send_Byte(0xaa);    //ָ��
		 if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
		IIC_Send_Byte(0xa5);    //ָ��
	  if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
		IIC_Send_Byte(newAddress);    //�µ�ַ
 	  if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
   
		
		IIC_Stop();   	
		return SET;
}
//����
