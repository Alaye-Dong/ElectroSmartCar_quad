#include "headfile.h"

#include "anotc.h"

// cpuΪС��ģʽ�洢��Ҳ�����ڴ洢��ʱ�򣬵�λ������0�ֽڣ���λ��1�ֽ�
#define BYTE0(dwTemp) (*((char *)(&dwTemp) + 3))       // ȡ��int�ͱ����ĵ��ֽ�
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 2)) //	ȡ�洢�ڴ˱�����һ�ڴ��ֽڵ����ݣ����ֽ�
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
//        return 1; // У��ͨ��
//    else
//        return 0; // У��ʧ��
//}

void ANO_SendData(int32 target, int32 present)
{
    int i;
    uint8 sumcheck = 0;
    uint8 addcheck = 0;
    _cnt = 0;
    BUFF[_cnt++] = 0xAA;          // ֡ͷ
    BUFF[_cnt++] = 0xAF;          // Ŀ���ַ
    BUFF[_cnt++] = 0XF1;          // ������
    BUFF[_cnt++] = 0x08;          // ���ݳ���
    BUFF[_cnt++] = BYTE0(target); // ��������,С��ģʽ����λ��ǰ
    BUFF[_cnt++] = BYTE1(target); // ��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
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

//    BUFF[_cnt++] = 0xAA;          // ֡ͷ
//    BUFF[_cnt++] = 0xAF;          // Ŀ���ַ
//    BUFF[_cnt++] = 0XF1;          // ������
//    BUFF[_cnt++] = 0x0C;          // ���ݳ���
//    BUFF[_cnt++] = BYTE0(target); // ��������,С��ģʽ����λ��ǰ
//    BUFF[_cnt++] = BYTE1(target); // ��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
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

//    packet[_cnt++] = 0xAA;          // ֡ͷ
//    packet[_cnt++] = 0xFF;          // Ŀ���ַ
//    packet[_cnt++] = 0X00;          // ������
//    packet[_cnt++] = 0x03;          // ���ݳ���
//    packet[_cnt++] = 0xE2; // ��������,С��ģʽ����λ��ǰ
//    packet[_cnt++] = sum_check; // ��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
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
