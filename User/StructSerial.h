/***********************************************************************
�ļ����ƣ�LED.h
��    �ܣ�led  IO��ʼ��
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/

#ifndef _STRUCTSERIAL_H_
#define _STRUCTSERIAL_H_

#define COMMAND_DATA_LENGTH sizeof(struct_command_data)

typedef struct struct_command_data {
	int check_front;
	
	float vx;
	float vy;
	float wz;	
	uint8_t  qr_scan;
	
	int check_back;
} struct_command_data, *struct_command_data_ptr;


#define FEEDBACK_DATA_LENGTH sizeof(struct_feedback_data)
typedef struct struct_feedback_data {
	int check_front;	
	
	float vx;
	float vy;
	float wz;	
	
	float pos_x;
	float pos_y;
	float pos_z;
	
	char qr_scan[10];
	
	int check_back;
} struct_feedback_data, *struct_feedback_data_ptr;

#endif
