#include  "headfile.h"

#ifndef __PARK_H
#define __PARK_H

//extern int DEBUG_MODE;
extern int Start_Flag;
extern int XJ;
extern int garage_out_direction;
extern int Hall;

extern int roundcount2_k;

extern int ruku_encoder_round_after_flag;

extern int CK_count;
extern int CK_count2;

void CHUKU();
void RuKu();
void RuKu_Back_Into();
void RuKu_Encoder_Round_After();
void Re_Start();

#endif