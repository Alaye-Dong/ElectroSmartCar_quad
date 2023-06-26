#include "headfile.h"


/*
 * 系统频率，可查看board.h中的 FOSC 宏定义修改。
 * board.h文件中FOSC的值设置为0,则程序自动设置系统频率为33.1776MHZ
 * 在board_init中,已经将P54引脚设置为复位
 * 如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可
 */

int d = 0;
int servo = 0;
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
		gpio_mode(P7_4, GPO_PP); //蜂鸣器
		BEEP = 0;
		lcd_init();
		gpio_mode(P6_4, GPO_PP);//电机
		gpio_mode(P6_0, GPO_PP);//电机
		EnableGlobalIRQ();		//开启总中断
		pwm_init(PWMB_CH1_P74, 50, 692);//最大765   最小625
		ctimer_count_init(CTIM0_P34);
		ctimer_count_init(CTIM3_P04);
				  
//    while(imu660ra_init())				//六轴陀螺仪初始化
// 	  {
//		   delay_ms(500);
//	   	 printf("imu660ra init try again.\r\n");
//    	}

		dl1a_init();	// 初始化DL1A(TOF)
		pit_timer_ms(TIM_4, 5);
		eeprom_init();	//EEPROM操作初始化
   
    while(1)
    {
			Keystroke_Scan();
			Keystroke_Menu();
			
//		//key_scan();
//		lcd_showfloat(5,0,g_ValueOfAD[2],4,2);  //右横
//		lcd_showfloat(65,0,g_ValueOfAD[3],4,2);  //左横
//		lcd_showfloat(5,1,g_ValueOfAD[5],4,2);	//右竖？
//		lcd_showfloat(65,1,g_ValueOfAD[0],4,2);   //左竖
//		lcd_showfloat(65,2,g_ValueOfAD[1],4,2);  //左斜
//		lcd_showfloat(5,2,g_ValueOfAD[4],4,2);	//右斜


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

