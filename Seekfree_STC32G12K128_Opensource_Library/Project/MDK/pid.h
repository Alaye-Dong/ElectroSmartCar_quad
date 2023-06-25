#include  "headfile.h"

#ifndef __PID_H
#define __PID_H


extern float Motor_Kp_L , Motor_Ki_L ; //55 5.7
extern float Motor_Kp_R , Motor_Ki_R ; //37 0.3
extern float angle_kp1 ;
extern int e_r2;
extern float v_angle;
extern int last_err1;
extern int last_err2;
extern int16 Abs(int16 value);
extern float Target_speed1, Target_speed2;
extern float cha_err1, cha_err2;
extern int duty1, duty2, speed;
extern float price_PWM;
extern int dutymax;
extern float ZX_kp;
extern float ZX_kd;
extern float angle;
void dir_pid();
void speedR_pid();
void Control(void);
void mpu660_PID();
void Direction_out(void);
void Target_speed();
void Target_speed_hd();
int Incremental_PI_1(int Encoder1, float Target1);
int Incremental_PI_2(int Encoder2, float Target2);
void speedL_pid();
#endif