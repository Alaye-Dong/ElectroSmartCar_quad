#include "headfile.h"


/*
 * ϵͳƵ�ʣ��ɲ鿴board.h�е� FOSC �궨���޸ġ�
 * board.h�ļ���FOSC��ֵ����Ϊ0,������Զ�����ϵͳƵ��Ϊ33.1776MHZ
 * ��board_init��,�Ѿ���P54��������Ϊ��λ
 * �����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����
 */

int d = 0;
int servo = 0;
void main()
{
    board_init();			// ��ʼ���Ĵ���,��ɾ���˾���롣

		adc_init(ADC_P00,ADC_SYSclk_DIV_2);    //ADC��ʼ��
		adc_init(ADC_P01,ADC_SYSclk_DIV_2);
		adc_init(ADC_P05,ADC_SYSclk_DIV_2);
		adc_init(ADC_P06,ADC_SYSclk_DIV_2);
		adc_init(ADC_P11,ADC_SYSclk_DIV_2);
		adc_init(ADC_P13,ADC_SYSclk_DIV_2);
		pwm_init(PWM1, 17000, 0);
		pwm_init(PWM2, 17000, 0);
		gpio_mode(P7_4, GPO_PP); //������
		BEEP = 0;
		lcd_init();
		gpio_mode(P6_4, GPO_PP);//���
		gpio_mode(P6_0, GPO_PP);//���
		EnableGlobalIRQ();		//�������ж�
		pwm_init(PWMB_CH1_P74, 50, 692);//���765   ��С625
		ctimer_count_init(CTIM0_P34);
		ctimer_count_init(CTIM3_P04);
				  
//    while(imu660ra_init())				//���������ǳ�ʼ��
// 	  {
//		   delay_ms(500);
//	   	 printf("imu660ra init try again.\r\n");
//    	}

		dl1a_init();	// ��ʼ��DL1A(TOF)
		pit_timer_ms(TIM_4, 5);
		eeprom_init();	//EEPROM������ʼ��
   
    while(1)
    {
			Keystroke_Scan();
			Keystroke_Menu();
			
//		//key_scan();
//		lcd_showfloat(5,0,g_ValueOfAD[2],4,2);  //�Һ�
//		lcd_showfloat(65,0,g_ValueOfAD[3],4,2);  //���
//		lcd_showfloat(5,1,g_ValueOfAD[5],4,2);	//������
//		lcd_showfloat(65,1,g_ValueOfAD[0],4,2);   //����
//		lcd_showfloat(65,2,g_ValueOfAD[1],4,2);  //��б
//		lcd_showfloat(5,2,g_ValueOfAD[4],4,2);	//��б


//		lcd_showfloat(5,4,roundcount2,4,2);   //
//		lcd_showfloat(65,3,Target_speed1,4,2);  //
//		lcd_showfloat(5,3,Target_speed2,4,2);//
//		lcd_showfloat(5,8,v_angle,4,2);//
//		lcd_showfloat(5,6,e_r2,4,2);//
//		lcd_showfloat(65,6,e_r1,4,2);//
//		lcd_showfloat(5,7,dl1a_distance_mm,4,2);
//		lcd_showfloat(65,7,CK_count2,4,2);
//		
//		lcd_showfloat(5,9,HALL_PIN,4,2);
    }
}

