/********************/
#include "main.h"

void send_to_scanner(unsigned char *send_buff) {
    UART4_Send_Data(send_buff, 9);
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

void scanner_triggger(void) {
    GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_RESET);
		delay_ms(2);
    GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
}
