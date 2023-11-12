#include  "headfile.h"

#ifndef __PID_H
#define __PID_H

extern float g_dirControl_P;
extern float g_dirControl_D;

extern float Motor_Kp_L , Motor_Ki_L ; \
extern float Motor_Kp_R , Motor_Ki_R ; 
extern float angle_kp1 ;


extern float last_err1;
extern float last_err2;

extern float Target_speed1, Target_speed2;
extern float cha_err1, cha_err2;
extern int duty1, duty2, speed;

extern int normal_speed, round_speed;


extern float v_angle;
extern float angle;

extern float y_v_angle;
extern float angle_y;



void dir_pid();
void speedL_pid();
void speedR_pid();
void Control(void);
void Target_speed();

void mpu660_PID();
void mpu660_angle() ;
void IMU660ra_Angle_Y_V_Filter();
void IMU660ra_Angle_Y();

void Ordinary_trace();





#endif