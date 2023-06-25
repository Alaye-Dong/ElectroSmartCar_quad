#include  "headfile.h"

#ifndef __ENCODER_H
#define __ENCODER_H

extern int16 speed1;//±àÂëÆ÷¶ÁÈ¡Âö³å
extern int16 speed2;
extern float encoder_integral;
extern float encoder;
extern int16 count_flag;
void read_encoder();
#endif