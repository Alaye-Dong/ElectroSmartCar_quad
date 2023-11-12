#include  "headfile.h"

#ifndef __ANOTC_H
#define __ANOTC_H

void ANO_SendData(int32 target, int32 present);
uint8 ANO_ParseParam(uint8* packet, uint8* param_id, int32* param_value);
void ANO_SendCheckFrame(uint8* packet, uint8 sum_check, uint8 add_check);
void ANO_SendDataMore(int32 target, int32 present_1, int32 present_2);

#endif
