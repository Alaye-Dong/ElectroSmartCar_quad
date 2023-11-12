#include "headfile.h"


/*
 * 系统频率，可查看board.h中的 FOSC 宏定义修改。
 * board.h文件中FOSC的值设置为0,则程序自动设置系统频率为33.1776MHZ
 * 在board_init中,已经将P54引脚设置为复位
 * 如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可
 */

void main()
{
    board_init();			// 初始化寄存器,勿删除此句代码。
		
    adc_init(ADC_P00,ADC_SYSclk_DIV_2);    //ADC初始化
    adc_init(ADC_P01,ADC_SYSclk_DIV_2);
    adc_init(ADC_P05,ADC_SYSclk_DIV_2);
    adc_init(ADC_P06,ADC_SYSclk_DIV_2);
    adc_init(ADC_P11,ADC_SYSclk_DIV_2);
    adc_init(ADC_P13,ADC_SYSclk_DIV_2);
    
    pwm_init(PWM1, 17000, 0);
    pwm_init(PWM2, 17000, 0);
    
    gpio_mode(P6_7, GPO_PP); //蜂鸣器
    BEEP = 0;
    lcd_init();
    
    gpio_mode(P6_4, GPO_PP);//电机
    gpio_mode(P6_0, GPO_PP);//电机
    
    EnableGlobalIRQ();		//开启总中断
    
    pwm_init(PWMB_CH1_P74, 50, 692);//舵机 最大765   最小625
    ctimer_count_init(CTIM0_P34);   
    ctimer_count_init(CTIM3_P04);
				  
    while(imu660ra_init())				//六轴陀螺仪初始化
    {
        delay_ms(500);
        printf("imu660ra init try again.\r\n");
    }

    dl1a_init();
				
	//eeprom_init();	//eeprom初始化
    
    pit_timer_ms(TIM_4, 5);
    
    BEEP = 1;
    delay_ms(10);
    BEEP = 0;
    //Dispay_Codename = 4; //初次启动直进菜单4页方便查看
			
    while(1) 
    {
		if(Start_Flag != 1 )//|| DEBUG_MODE != -1
		{
			Keystroke_Scan();
			Keystroke_Menu();
		}
    }
}

