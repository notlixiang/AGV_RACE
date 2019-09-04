#include "main.h"


float speed_cmd[3]={0};

float speed_fbk[3]={0};	
float pos_fbk[3]={0};	
float a_fbk[3]={0};
float g_fbk[3]={0};
float yaw_fbk=0;
float ultra_sound_signal_fbk[12]={0};
//char qr_scan_fbk[10]={0};
float voltage_fbk=0;
float displacement_sensor_voltage_fbk=0;
uint8_t charging_status_fbk=0;
uint8_t infrared_fbk[6];
char qr_scan_fbk[QR_LENGTH]="init";

void send_struct_feedback_serial(void){
	struct_feedback_data feedback;
	struct_feedback_data* feedback_ptr=&feedback;
	char* feedback_ptr_char=(char*)feedback_ptr;
	
	char fbk_buff[150];
	int i=0;
	for(i=0;i<3;i++){		
	feedback.speed_fbk[i]=speed_fbk[i];
	feedback.pos_fbk[i]=pos_fbk[i];
	feedback.a_fbk[i]=a_fbk[i];
	feedback.g_fbk[i]=g_fbk[i];
	}	
	feedback.yaw_fbk=yaw_fbk;
//	speed_fbk[0]+=1.0;
	for(i=0;i<12;i++){		
	feedback.ultra_sound_signal_fbk[i]=ultra_sound_signal_fbk[i];
	}
	feedback.voltage_fbk=voltage_fbk;	
	feedback.displacement_sensor_voltage_fbk=displacement_sensor_voltage_fbk;
	//	printf("%f\n",displacement_sensor_voltage_fbk);	
	feedback.charging_status_fbk=charging_status_fbk;	
	for(i=0;i<6;i++){		
	feedback.infrared_fbk[i]=infrared_fbk[i];
	}
	for(i=0;i<10;i++){		
	feedback.qr_scan_fbk[i]=qr_scan_fbk[i];
	}
	
	feedback.check_front_fbk=CHECK_FRONT_FBK;
	feedback.check_back_fbk=CHECK_BACK_FBK;
	
	fbk_buff[0]='F';
	fbk_buff[1]='B';
	fbk_buff[2]='K';
	fbk_buff[FEEDBACK_DATA_LENGTH+3+0]='f';
	fbk_buff[FEEDBACK_DATA_LENGTH+3+1]='b';
	fbk_buff[FEEDBACK_DATA_LENGTH+3+2]='k';
	fbk_buff[FEEDBACK_DATA_LENGTH+3+3]='\0';
	fbk_buff[FEEDBACK_DATA_LENGTH+3+4]='\n';
	
	memcpy(fbk_buff+3, feedback_ptr_char, FEEDBACK_DATA_LENGTH);
	
	RS232_Send_Data(fbk_buff,FEEDBACK_DATA_LENGTH+8);
}

