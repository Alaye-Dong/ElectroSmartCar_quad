#include  "headfile.h"

#ifndef __ROUND_H
#define __ROUND_H

extern int flag_r_hd;  //入环岛预测
extern int flag_c_hd;  //出环岛标志位
extern int flag_hd_Z;  //左环岛
extern int flag_hd_R;  //右环岛
extern int e_r1, e_r2;
extern int roundcount;
extern int roundcount2;
extern int roundcount3;


extern int round_number;	
extern int round1_type,round2_type,round3_type,round4_type; //-1入左环，1入右环

extern int slope_flag;

extern int obstacle_flag;
extern int obstacle_number;
extern int obstacle1_type, obstacle2_type, obstacle3_type;

extern int cross_flag;


void knn();
void Round_Deal();
void Huan_Dao_Z();
void Huan_Dao_R();

void Slope();

void Obstacle_Deal();
void Obstacle();
void Cross();
void SHIZI();
#endif