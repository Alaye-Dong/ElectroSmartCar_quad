#ifndef __DIRECTION_H__
#define __DIRECTION_H__



#include  "common.h"
#include  "headfile.h"
#include "direction.h"
/************外部变量申明******/
extern unsigned int data diangan[9];
extern float g_dirControl_P;
extern float g_dirControl_D;
extern int sanchayou;
extern float all, al, mid, arr, ar;
extern int t;
extern int d;
extern int servo;
extern int zhidaoflag;
extern int s_r;
extern int e_r1;
extern int16 a_r;
extern int16 g_roundControl_P;
extern int16 g_roundControl_D;
extern float g_fDirectionError[5];
extern float g_fDirectionError_dot[3];
extern float g_fDirectionControlOut;
extern int16 g_ValueOfAD[9];
extern int16 g_ValueOfADFilter[5];
extern int16 flag_go;      //出库标志
extern int16 angle_round;
extern int16 direction_round;
extern int16 flag_timeintoround;
extern int16 g_distance[5];
extern int16 g_Infrared[5];
extern uint16 g_rellaydistance;
extern uint16 g_rinfrared;
extern uint16 set_distance;
extern int16 g_ValueOfADError;
extern uint16 ui_ValueOfADError;
extern uint16 stop_time;//刹车时间
extern uint16 stop_flag;//停车标志
extern int8 dire_garage;//出库方向
extern uint16 set_redout;
extern int8 slow_flag;
extern uint8 g_stopFlag;
extern float g_rolControl_P;             //弯道P
extern float g_rolControl_D;             //弯道D
extern int16 g_fastControl_P;            //直道P
extern int16 g_fastControl_D;            //直道D
extern int16 motorg_dirControl_P;            //方向控制P
extern int16 motorg_dirControl_D;	       //方向控制D
extern float motorg_fDirectionControlOut;//电机方向控制输出

extern int Hall;

extern int direction_pwm;

//*****函数声明*****//
void Read_ADC();
void InductorNormal();
void DirectionControl();
#endif