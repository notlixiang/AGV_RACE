
#include "main.h"

float odometer_x=0;
float odometer_y=0;
float odometer_z=0;

extern float AGV_OUT_SPEED_K ;
extern float AGV_SHAPE_K ;

unsigned char odom_buff[100];

void odometer_reset(void)
{
odometer_x=0;
odometer_y=0;
odometer_z=0;
}
void odometer_update_by_xyz(float vx,float vy,float wz,float delta_t)
{
//	odometer_x+=vx*delta_t;
//	odometer_y+=vy*delta_t;
//	odometer_z+=wz*delta_t;
//	
	
//	odometer_x=vx*delta_t+odometer_x*cos(wz*delta_t/1000.0)-odometer_y*sin(wz*delta_t/1000.0);
//	odometer_y=vy*delta_t+odometer_x*sin(wz*delta_t/1000.0)+odometer_y*cos(wz*delta_t/1000.0);
//	odometer_z+=wz*delta_t;
	
	odometer_x=odometer_x+vx*delta_t*cos(odometer_z/1000.0)-vy*delta_t*sin(odometer_z/1000.0);
	odometer_y=odometer_y+vx*delta_t*sin(odometer_z/1000.0)+vy*delta_t*cos(odometer_z/1000.0);
	odometer_z+=wz*delta_t;
	
}

void odometer_update_by_wheels(float omega_1,float omega_2,float omega_3,float omega_4,float delta_t)
{
	int32_t omega_1_tmp = (int32_t)(L_DIRECTION*1*omega_1);
	int32_t omega_2_tmp = (int32_t)(L_DIRECTION*1*omega_2);
	int32_t omega_3_tmp = (int32_t)(R_DIRECTION*1*omega_3);
	int32_t omega_4_tmp = (int32_t)(R_DIRECTION*1*omega_4);
	
	float vx_temp=(omega_1_tmp+omega_2_tmp+omega_3_tmp+omega_4_tmp)/(4.0*AGV_OUT_SPEED_K);
	float vy_temp=(omega_1_tmp-omega_2_tmp+omega_3_tmp-omega_4_tmp)/(4.0*AGV_OUT_SPEED_K);
	float wz_temp=-(omega_1_tmp+omega_2_tmp-omega_3_tmp-omega_4_tmp)/(4.0*AGV_OUT_SPEED_K*AGV_SHAPE_K);
	
	
	sprintf(odom_buff, "ODOMDTU x %d, y %d ,z %d,DTUODOM\r\n\0", 
	(int)vx_temp,
		//(int)(sin(PI/4.0)*1000),
	(int)vy_temp,
	(int)wz_temp);
	
//	sprintf(odom_buff, "ODOMDTU w1 %d, w2 %d ,w3 %d, w4 %d,DTUODOM\r\n\0", 
//	(int)omega_1, 
//	(int)omega_2,
//	(int)omega_3,
//	(int)omega_4);
	

	//RS232_Send_Data(odom_buff,strlen(odom_buff));
	
	
	odometer_update_by_xyz(vx_temp,vy_temp,wz_temp,delta_t);	
	
}

void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//定时器3中断服务函数
extern int32_t speed_read_value[4];//??????

void TIM3_IRQHandler(void)
{
	float omega_1=speed_read_value[0];//K_omega*1000.0;
	float omega_2=speed_read_value[1];//K_omega*1000.0;
	float omega_3=speed_read_value[2];//K_omega*1000.0;
	float omega_4=speed_read_value[3];//K_omega*1000.0;
	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		odometer_update_by_wheels( omega_1,omega_2,omega_3,omega_4,ODOM_PERIOD_MS/1000.0);
			delay_ms(26);
 	sprintf(odom_buff, "ODOMDTU x %d, y %d ,z %d,DTUODOM\r\n\0", 
	(int)odometer_x,
		//(int)(sin(PI/4.0)*1000),
	(int)odometer_y,
	(int)odometer_z);
	

	RS232_Send_Data(odom_buff,strlen(odom_buff));
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}
