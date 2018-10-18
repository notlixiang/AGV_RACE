/***********************************************************************
文件名称：main.h
功    能： 
编写时间：
编 写 人：
注    意：
***********************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_

#include "stm32f4xx_it.h"
#include "stm32f4xx.h"
#include <stdlib.h>
#include "led.h"
#include <stdint.h>
#include "qr.h"
#include "sci.h"
#include "delay.h"
#include "string.h"

#define N1 0x01 //CAN ID of each wheel, left front wheel
#define N2 0x0C  //left back wheel
#define N3 0x04	//right back wheel
#define N4 0x02	//right front wheel

#define PI 3.14159265359

#endif

