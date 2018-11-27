
#include "main.h"

float odometer_x=0;
float odometer_y=0;
float odometer_z=0;

extern float AGV_OUT_SPEED_K ;
extern float AGV_SHAPE_K ;

void odometer_reset(void)
{
odometer_x=0;
odometer_y=0;
odometer_z=0;
}
void odometer_update_by_xyz(float vx,float vy,float wz,float delta_t)
{
	odometer_x+=vx*delta_t;
	odometer_y+=vy*delta_t;
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
	float wz_temp=(omega_1_tmp+omega_2_tmp-omega_3_tmp-omega_4_tmp)/(4.0*AGV_OUT_SPEED_K*AGV_SHAPE_K);
	
	odometer_update_by_xyz(vx_temp,vy_temp,wz_temp,delta_t);	
	
}
