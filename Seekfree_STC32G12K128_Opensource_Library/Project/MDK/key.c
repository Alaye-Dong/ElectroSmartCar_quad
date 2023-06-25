#include "headfile.h"
#include "key.h"

//拨码开关状态变量
uint8 sw1_status;
uint8 sw2_status;
uint8 sw3_status;

//开关状态变量
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;
uint8 key5_status = 1;
uint8 key6_status = 1;
//上一次开关状态变量
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;
uint8 key5_last_status;
uint8 key6_last_status;

//开关标志位
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;
uint8 key5_flag;
uint8 key6_flag;
uint8 test1 = 0, test2 = 0, test3 = 0, test4 = 0, test5 = 0, test6 = 0;

void key_scan()
{
    sw1_status = SW1_PIN;
    sw2_status = SW2_PIN;
//    sw3_status = SW3_PIN;
    //使用此方法优点在于，不需要使用while(1) 等待，避免处理器资源浪费
    //保存按键状态
    key1_last_status = key1_status;
    key2_last_status = key2_status;
    key3_last_status = key3_status;
    key4_last_status = key4_status;
//    key5_last_status = key5_status;
//    key6_last_status = key6_status;
    //读取当前按键状态
    key1_status = KEY1_PIN;
    key2_status = KEY2_PIN;
    key3_status = KEY3_PIN;
    key4_status = KEY4_PIN;
//    key5_status = KEY5_PIN;
//    key6_status = KEY6_PIN;
    //检测到按键按下之后  并放开置位标志位

    if(key1_status == 0)                      key1_flag = 1;
    if(key2_status && !key2_last_status)    key2_flag = 1;
    if(key3_status && !key3_last_status)    key3_flag = 1;
    if(key4_status && !key4_last_status)    key4_flag = 1;
//    if(key5_status && !key5_last_status)    key5_flag = 1;
//    if(key6_status && !key6_last_status)    key6_flag = 1;
    //标志位置位之后，可以使用标志位执行自己想要做的事件
    if(key1_flag)
    {
        key1_flag = 0;//使用按键之后，应该清除标志位
        test1++;
			g_dirControl_P = g_dirControl_P +0.05;
    }

    if(key2_flag)
    {
        key2_flag = 0;//使用按键之后，应该清除标志位
        test2++;
			g_dirControl_P = g_dirControl_P - 0.05;
    }

    if(key3_flag)
    {
        key3_flag = 0;//使用按键之后，应该清除标志位
        test3++;
			g_dirControl_D = g_dirControl_D + 0.05;
    }

    if(key4_flag)
    {
        key4_flag = 0;//使用按键之后，应该清除标志位
        test4++;
			g_dirControl_D = g_dirControl_D - 0.05;
    }
	}
