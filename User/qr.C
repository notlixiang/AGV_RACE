/********************/
#include "main.h"

void send_to_scanner(unsigned char *send_buff) {
    UART4_Send_Data(send_buff, 9);
}

void send_read_command(void) {
	//unsigned char buff[9]={0x7e,0x00,0x07,0x01,0x00,0x00,0x00,0xab,0xcd};
//	unsigned char buff[9]={0x7E, 0x00 ,0x07, 0x01, 0x00, 0x0A, 0x01 ,0xEE, 0x8A};	
//	send_to_scanner(buff);
//	
	unsigned char buff_set_9600[10]={0x7e,0x00,0x08,0x02,0x00,0x2A,0x39,0x01,0xA7,0xEA};
//	send_to_scanner(buff_set_9600);
	
	unsigned char buff_query_baud_rate[10]={0x7e,0x00,0x07,0x01,0x00,0x2A,0x02,0xD8,0x0F};
//	send_to_scanner(buff_query_baud_rate);
	
		unsigned char buff_query_output_mode[10]={0x7e,0x00,0x07,0x01,0x00,0x0D,0x01,0xab,0xcd};
	send_to_scanner(buff_query_output_mode);
	
				unsigned char buff_set_output_mode[10]={0x7e,0x00,0x08,0x01,0x00,0x0D,0xEC,0xab,0xcd};
	//send_to_scanner(buff_set_output_mode);
}

void send_set_command(void) {
	//unsigned char buff[9]={0x7e,0x00,0x07,0x01,0x00,0x00,0x00,0xab,0xcd};
//	unsigned char buff[9]={0x7E, 0x00 ,0x07, 0x01, 0x00, 0x0A, 0x01 ,0xEE, 0x8A};	
//	send_to_scanner(buff);
//	
//	unsigned char buff_set_9600[10]={0x7e,0x00,0x08,0x02,0x00,0x2A,0x39,0x01,0xA7,0xEA};
//	send_to_scanner(buff_set_9600);
//	0x7E 0x00 0x08 0x01 0x00 0x0D 0x3E 0xAB 0xCD
	unsigned char buff_set_serial_out[10]={0x7e,0x00,0x07,0x01,0x00,0x2A,0x02,0xD8,0x0F};
	send_to_scanner(buff_set_serial_out);
	
}

void scanner_init(void) {
    UART4_Configuration();

    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

}
extern char qr_scan_fbk[10];
void scanner_triggger(void) {
	UART4_rec_counter=0;
    GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_RESET);
		delay_ms(2);
	delay_ms(2000);
    GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
	memcpy((unsigned char*)qr_scan_fbk, (unsigned char*)UART4_buff, UART4_rec_counter);	
}
