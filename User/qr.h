/***********************************************************************
�ļ����ƣ�LED.h
��    �ܣ�led  IO��ʼ��
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/

#ifndef _QR_H_
#define _QR_H_

#include "main.h"

void send_to_scanner(unsigned char *send_buff);

void scanner_init(void);

void scanner_triggger(void) ;

#endif
