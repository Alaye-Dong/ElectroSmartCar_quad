#include "headfile.h"


/*
 * ϵͳƵ�ʣ��ɲ鿴board.h�е� FOSC �궨���޸ġ�
 * board.h�ļ���FOSC��ֵ����Ϊ0,������Զ�����ϵͳƵ��Ϊ33.1776MHZ
 * ��board_init��,�Ѿ���P54��������Ϊ��λ
 * �����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����
 */

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
    
    gpio_mode(P6_7, GPO_PP); //������
    BEEP = 0;
    lcd_init();
    
    gpio_mode(P6_4, GPO_PP);//���
    gpio_mode(P6_0, GPO_PP);//���
    
    EnableGlobalIRQ();		//�������ж�
    
    pwm_init(PWMB_CH1_P74, 50, 692);//��� ���765   ��С625
    ctimer_count_init(CTIM0_P34);   
    ctimer_count_init(CTIM3_P04);
				  
    while(imu660ra_init())				//���������ǳ�ʼ��
    {
        delay_ms(500);
        printf("imu660ra init try again.\r\n");
    }

    dl1a_init();
				
	//eeprom_init();	//eeprom��ʼ��
    
    pit_timer_ms(TIM_4, 5);
    
    BEEP = 1;
    delay_ms(10);
    BEEP = 0;
    //Dispay_Codename = 4; //��������ֱ���˵�4ҳ����鿴
			
    while(1) 
    {
		if(Start_Flag != 1 )//|| DEBUG_MODE != -1
		{
			Keystroke_Scan();
			Keystroke_Menu();
		}
    }
}

