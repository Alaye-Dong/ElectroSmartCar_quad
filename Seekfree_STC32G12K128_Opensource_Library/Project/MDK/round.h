#include  "headfile.h"

#ifndef __ROUND_H
#define __ROUND_H

extern int flag_r_hd;  //入环岛预测
extern int flag_c_hd;  //出环岛标志位
extern int flag_hding1, flag_hding2; //环岛内循迹标志位
extern int flag_hd_Z;  //左环岛
extern int flag_hd_R;  //右环岛
extern float hdcha_err;
extern int e_r1, e_r2;
extern int HD;
extern int roundcount;
extern int roundcount2;
extern int XJ;
extern int CK_count;
extern int CK_count2;
void knn();
void Huan_Dao_Z();
void Huan_Dao_R();
void CHUKU();
void RuKu();
void obstacle();
#endif