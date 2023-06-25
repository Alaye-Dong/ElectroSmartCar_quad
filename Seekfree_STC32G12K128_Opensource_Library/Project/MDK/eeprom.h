#include  "headfile.h"

#ifndef __EEPROM_H
#define __EEPROM_H


void EepromWrite(void);
void EepromRead(void);

extern uint8 date_buff[100]; //eeprom数据数组
void eeprom_init();

void save_int(int32 input, uint8 value_bit);
int32 read_int(uint8 value_bit);
void save_float(float input, uint8 value_bit);
float read_float(uint8 value_bit);


#endif