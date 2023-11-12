#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include  "headfile.h"
#include "direction.h"
/************外部变量申明******/
extern unsigned int data diangan[9];


extern float g_fDirectionError[5];
extern float g_fDirectionError_dot[3];

extern int16 g_ValueOfAD[9];
extern int16 g_ValueOfADFilter[5];


extern int zhidaoflag;


//*****函数声明*****//
void Read_ADC();
void InductorNormal();
void DirectionControl();
#endif