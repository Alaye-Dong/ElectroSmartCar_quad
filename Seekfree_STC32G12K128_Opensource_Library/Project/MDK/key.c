#include "headfile.h"
#include "key.h"

//���뿪��״̬����
uint8 sw1_status;
uint8 sw2_status;
uint8 sw3_status;

//����״̬����
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;
uint8 key5_status = 1;
uint8 key6_status = 1;
//��һ�ο���״̬����
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;
uint8 key5_last_status;
uint8 key6_last_status;

//���ر�־λ
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
    //ʹ�ô˷����ŵ����ڣ�����Ҫʹ��while(1) �ȴ������⴦������Դ�˷�
    //���水��״̬
    key1_last_status = key1_status;
    key2_last_status = key2_status;
    key3_last_status = key3_status;
    key4_last_status = key4_status;
//    key5_last_status = key5_status;
//    key6_last_status = key6_status;
    //��ȡ��ǰ����״̬
    key1_status = KEY1_PIN;
    key2_status = KEY2_PIN;
    key3_status = KEY3_PIN;
    key4_status = KEY4_PIN;
//    key5_status = KEY5_PIN;
//    key6_status = KEY6_PIN;
    //��⵽��������֮��  ���ſ���λ��־λ

    if(key1_status == 0)                      key1_flag = 1;
    if(key2_status && !key2_last_status)    key2_flag = 1;
    if(key3_status && !key3_last_status)    key3_flag = 1;
    if(key4_status && !key4_last_status)    key4_flag = 1;
//    if(key5_status && !key5_last_status)    key5_flag = 1;
//    if(key6_status && !key6_last_status)    key6_flag = 1;
    //��־λ��λ֮�󣬿���ʹ�ñ�־λִ���Լ���Ҫ�����¼�
    if(key1_flag)
    {
        key1_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
        test1++;
			g_dirControl_P = g_dirControl_P +0.05;
    }

    if(key2_flag)
    {
        key2_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
        test2++;
			g_dirControl_P = g_dirControl_P - 0.05;
    }

    if(key3_flag)
    {
        key3_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
        test3++;
			g_dirControl_D = g_dirControl_D + 0.05;
    }

    if(key4_flag)
    {
        key4_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
        test4++;
			g_dirControl_D = g_dirControl_D - 0.05;
    }
	}
