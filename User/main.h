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

#include "odometer.h"
#include "StructSerial.h"

#include "stm32f4xx_it.h"
#include "stm32f4xx.h"
#include "SCI.H"
#include "NVIC.H"
#include "can.h"
#include "myiic.h"
#include "ks103.h"
//#include "IIC.h"
#include "delay.h"
#include "SysTick.H"
 #include "math.h"
#include "sys.h"


#define DOUBLEWHEEL 0

#define N1 0x01 //CAN ID of each wheel, left front wheel
#define N2 0x0C  //left back wheel
#define N3 0x04	//right back wheel
#define N4 0x02	//right front wheel

#define PI 3.14159265359

#if DOUBLEWHEEL
	#define LENGTH 0
#else
	#define LENGTH 0.670
#endif

#define WIDTH 0.495
#define RADIUS_OF_WHEEL 0.0825  //unit (m)
#define RED_RATIO 20
#define LINE_NUM 2500


#define OUT_SPEED_K 4*5*RED_RATIO*LINE_NUM/(PI*RADIUS_OF_WHEEL*1000)
#define OUT_OMEGA_K 4*5*RED_RATIO*LINE_NUM/(PI*1.0)
#define K_omega 557042.3008f

#define L_DIRECTION (1)
#define R_DIRECTION (-1) 

#define ODOM_PERIOD_MS 100


#endif

