#ifndef __DIRECTION_H__
#define __DIRECTION_H__



#include  "common.h"
#include  "headfile.h"
#include "direction.h"
/************�ⲿ��������******/
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
extern int16 flag_go;      //�����־
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
extern uint16 stop_time;//ɲ��ʱ��
extern uint16 stop_flag;//ͣ����־
extern int8 dire_garage;//���ⷽ��
extern uint16 set_redout;
extern int8 slow_flag;
extern uint8 g_stopFlag;
extern float g_rolControl_P;             //���P
extern float g_rolControl_D;             //���D
extern int16 g_fastControl_P;            //ֱ��P
extern int16 g_fastControl_D;            //ֱ��D
extern int16 motorg_dirControl_P;            //�������P
extern int16 motorg_dirControl_D;	       //�������D
extern float motorg_fDirectionControlOut;//�������������

extern int Hall;

extern int direction_pwm;

//*****��������*****//
void Read_ADC();
void InductorNormal();
void DirectionControl();
#endif