#include "headfile.h"

uint8 date_buff[100]; //eeprom数据数组
void eeprom_init()
{
    iap_init();									//初始化EEPROM;

    iap_read_bytes(0x00, date_buff, 100);		//从EEPROM中读取数据

///****不用eeprom直接赋值****/
//    g_dirControl_P		= 16.7;//read_float(0);
//    g_dirControl_D    = 15;//read_float(1);
//	  angle_kp1     		= 0.425;//read_float(2);

//    Motor_Kp_L 			  = 45;//read_float(3);
//    Motor_Ki_L      	= 5.7;//read_float(4);
//	
//    Motor_Kp_R      	= 45;//read_float(5);
//    Motor_Ki_R     		= 5.7;//read_float(6);
	
/****用eeprom赋值****/	
		Motor_Kp_L 			= read_float(0);
		Motor_Ki_L      	= read_float(1);
		Motor_Kp_R      	= read_float(2);
		Motor_Ki_R     	= read_float(3);
		angle_kp1     		= read_float(4);
		ZX_kp						= read_float(5);
		ZX_kd						= read_float(6);
		g_dirControl_P	= read_float(7);
		g_dirControl_D   = read_float(8);
	
}
void save_int(int32 input, uint8 value_bit)
{
    uint8 i;
    uint8 begin = value_bit * 4;
    uint8* p = (uint8*)&input;
    for(i = 0; i < 4; i++)
    {
        date_buff[begin++] = *(p + i);
    }
    extern_iap_write_bytes(0x00, date_buff, 100);
}

int32 read_int(uint8 value_bit)
{
    uint8 i;
    uint8 begin = value_bit * 4;
    int32 output;
    uint8* p = (uint8*)&output;;
    for(i = 0; i < 4; i++)
    {
        *(p + i) = date_buff[begin++];
    }
    return output;
}

void save_float(float input, uint8 value_bit)
{
    uint8 i;
    uint8 begin = value_bit * 4;
    uint8* p = (uint8*)&input;
    for(i = 0; i < 4; i++)
    {
        date_buff[begin++] = *(p + i);
    }
    extern_iap_write_bytes(0x00, date_buff, 100);
}
float read_float(uint8 value_bit)
{
    uint8 i;
    uint8 begin = value_bit * 4;
    float output;
    uint8* p = (uint8*)&output;;
    for(i = 0; i < 4; i++)
    {
        *(p + i) = date_buff[begin++];
    }
    return output;
}