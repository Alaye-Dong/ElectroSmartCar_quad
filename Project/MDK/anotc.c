#include "headfile.h"

#include "anotc.h"

// cpu为小端模式存储，也就是在存储的时候，低位被存在0字节，高位在1字节
#define BYTE0(dwTemp) (*((char *)(&dwTemp) + 3))       // 取出int型变量的低字节
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 2)) //	取存储在此变量下一内存字节的内容，高字节
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 0))

uint8 BUFF[30];

uint8 _cnt = 0;

//static uint8 ANO_CalCheck(uint8 *packet)
//{
//    int i;
//    uint8 sumcheck = 0;
//    uint8 addcheck = 0;

//    for (i = 0; i < packet[3] + 4; i++)
//    {
//        sumcheck += packet[i];
//        addcheck += sumcheck;
//    }

//    if (sumcheck == packet[packet[3] + 4] && addcheck == packet[packet[3] + 5])
//        return 1; // 校验通过
//    else
//        return 0; // 校验失败
//}

void ANO_SendData(int32 target, int32 present)
{
    int i;
    uint8 sumcheck = 0;
    uint8 addcheck = 0;
    _cnt = 0;
    BUFF[_cnt++] = 0xAA;          // 帧头
    BUFF[_cnt++] = 0xAF;          // 目标地址
    BUFF[_cnt++] = 0XF1;          // 功能码
    BUFF[_cnt++] = 0x08;          // 数据长度
    BUFF[_cnt++] = BYTE0(target); // 数据内容,小段模式，低位在前
    BUFF[_cnt++] = BYTE1(target); // 需要将字节进行拆分，调用上面的宏定义即可。
    BUFF[_cnt++] = BYTE2(target);
    BUFF[_cnt++] = BYTE3(target);
    BUFF[_cnt++] = BYTE0(present);
    BUFF[_cnt++] = BYTE1(present);
    BUFF[_cnt++] = BYTE2(present);
    BUFF[_cnt++] = BYTE3(present);

    for(i = 0; i < BUFF[3] + 4; i++)
    {
        sumcheck += BUFF[i];
        addcheck += sumcheck;
    }
    BUFF[_cnt++] = sumcheck;
    BUFF[_cnt++] = addcheck;

    wireless_uart_send_buff(BUFF, (uint16)_cnt);
//    uart_write_buffer(WIRELESS_UART_INDEX, BUFF, _cnt);
    // uart_write_buffer(DEBUG_UART_INDEX, BUFF, _cnt);
}

//void ANO_SendDataMore(int32 target, int32 present_1, int32 present_2)
//{
//    int i;
//    uint8 sumcheck = 0;
//    uint8 addcheck = 0;
//    uint8 _cnt = 0;

//    BUFF[_cnt++] = 0xAA;          // 帧头
//    BUFF[_cnt++] = 0xAF;          // 目标地址
//    BUFF[_cnt++] = 0XF1;          // 功能码
//    BUFF[_cnt++] = 0x0C;          // 数据长度
//    BUFF[_cnt++] = BYTE0(target); // 数据内容,小段模式，低位在前
//    BUFF[_cnt++] = BYTE1(target); // 需要将字节进行拆分，调用上面的宏定义即可。
//    BUFF[_cnt++] = BYTE2(target);
//    BUFF[_cnt++] = BYTE3(target);
//    BUFF[_cnt++] = BYTE0(present_1);
//    BUFF[_cnt++] = BYTE1(present_1);
//    BUFF[_cnt++] = BYTE2(present_1);
//    BUFF[_cnt++] = BYTE3(present_1);
//    BUFF[_cnt++] = BYTE0(present_2);
//    BUFF[_cnt++] = BYTE1(present_2);
//    BUFF[_cnt++] = BYTE2(present_2);
//    BUFF[_cnt++] = BYTE3(present_2);

//    for (i = 0; i < BUFF[3] + 4; i++)
//    {
//        sumcheck += BUFF[i];
//        addcheck += sumcheck;
//    }
//    BUFF[_cnt++] = sumcheck;
//    BUFF[_cnt++] = addcheck;

////    uart_write_buffer(WIRELESS_UART_INDEX , BUFF, _cnt);
//    // uart_write_buffer(DEBUG_UART_INDEX , BUFF, _cnt);
//}

//uint8 ANO_ParseParam(uint8 *packet, uint8 *param_id, int32 *param_value)
//{
//    uint8 index = 0;
//    if (packet[0] == 0xAA)
//    {
//        if (packet[1] == 0xff)
//        {
//            if (packet[2] == 0xe2)
//            {
//                if (packet[3] == 0x06)
//                {
//                    *param_id = *((uint16 *)(packet + 4));
//                    *param_value = *((int32 *)(packet + 6));
//                    if(ANO_CalCheck(packet))
//                    {
//                        if((*((uint16 *)(packet + 4))) == 0x00)
//                        {
////                            Flag_CmdStop = 1;
//                        }
//                        return 1;
//                    }
//                }
//            }
//        }
//    }

//    return 0;
//}

//void ANO_SendCheckFrame(uint8 *packet, uint8 sum_check, uint8 add_check)
//{
//    int i;
//    uint8 sumcheck = 0;
//    uint8 addcheck = 0;
//    uint8 _cnt = 0;

//    packet[_cnt++] = 0xAA;          // 帧头
//    packet[_cnt++] = 0xFF;          // 目标地址
//    packet[_cnt++] = 0X00;          // 功能码
//    packet[_cnt++] = 0x03;          // 数据长度
//    packet[_cnt++] = 0xE2; // 数据内容,小段模式，低位在前
//    packet[_cnt++] = sum_check; // 需要将字节进行拆分，调用上面的宏定义即可。
//    packet[_cnt++] = add_check;

//    for (i = 0; i < packet[3] + 4; i++)
//    {
//        sumcheck += packet[i];
//        addcheck += sumcheck;
//    }
//    packet[_cnt++] = sumcheck;
//    packet[_cnt++] = addcheck;

////   uart_write_buffer(WIRELESS_UART_INDEX , packet, _cnt);
//    // uart_write_buffer(DEBUG_UART_INDEX , packet, _cnt);
//}
