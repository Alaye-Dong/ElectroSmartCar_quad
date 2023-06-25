#ifndef _KEY_H_
#define _KEY_H_

//拨码开关状态变量
extern uint8 sw1_status;
extern uint8 sw2_status;
extern uint8 sw3_status;
//开关状态变量
extern uint8 key1_status;
extern uint8 key2_status;
extern uint8 key3_status;
extern uint8 key4_status;
extern uint8 key5_status;
extern uint8 key6_status;
//上一次开关状态变量
extern uint8 key1_last_status;
extern uint8 key2_last_status;
extern uint8 key3_last_status;
extern uint8 key4_last_status;
extern uint8 key5_last_status;
extern uint8 key6_last_status;
//开关标志位
extern uint8 key1_flag;
extern uint8 key2_flag;
extern uint8 key3_flag;
extern uint8 key4_flag;
extern uint8 key5_flag;
extern uint8 key6_flag;
void key_scan();



#endif