#include  "headfile.h"

#ifndef __MENU_H
#define __MENU_H

#include "common.h"
#include "SEEKFREE_18TFT.h"


void LCDLight_adc();
void LCDLight_star2();
//�������Ʒ��� ������Ƴ���� ������Ļ
#define up      3  //key1 ѡ���
#define down    1
#define expand  4  //key1 ���ڱ���expand
#define cut     2  //cut
#define certain 5  //key2 ȷ����
#define back    6  //key4 ���ؼ�

uint8 get_key(void);
void menu1(void);
void adc_display(void);
void sports_param(void);
#endif