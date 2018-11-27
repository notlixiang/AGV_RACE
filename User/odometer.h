/***********************************************************************
�ļ����ƣ�LED.h
��    �ܣ�led  IO��ʼ��
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/

#ifndef _ODOMETER_H_
#define _ODOMETER_H_


void odometer_reset(void);
void odometer_update_by_xyz(float vx,float vy,float wz,float delta_t);
void odometer_update_by_wheels(float omega_1,float omega_2,float omega_3,float omega_4,float delta_t);

#endif
