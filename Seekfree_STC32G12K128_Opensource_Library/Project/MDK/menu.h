#include  "headfile.h"

#ifndef __MENU_H
#define __MENU_H

#include "common.h"
#include "SEEKFREE_18TFT.h"


void LCDLight_adc();
void LCDLight_star2();
//按键控制返回 拨码控制出入库 开关屏幕
#define up      3  //key1 选择键
#define down    1
#define expand  4  //key1 调节倍数expand
#define cut     2  //cut
#define certain 5  //key2 确定键
#define back    6  //key4 返回键

uint8 get_key(void);
void menu1(void);
void adc_display(void);
void sports_param(void);
#endif