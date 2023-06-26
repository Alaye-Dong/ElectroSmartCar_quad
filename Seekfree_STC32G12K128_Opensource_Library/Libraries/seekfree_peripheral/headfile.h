#ifndef __HEADFILE_H_
#define __HEADFILE_H_


#define PWM1 PWMA_CH4P_P66  //左轮
#define PWM2 PWMA_CH2P_P62  //右轮PWMA_CH2P_P62
#define DIR2 P60  // DIR1=1 正转
#define DIR1 P64  
#define BEEP  P74
#define HALL_PIN P33
#define DIRL P53 //编码器左轮
#define DIRR P35 //编码器右轮

//五向开关
#define KEY1_PIN    P71
#define KEY2_PIN    P70
#define KEY3_PIN    P72
#define KEY4_PIN    P73
#define SW1_PIN     P75
#define SW2_PIN     P76



#include "isr.h"
#include <string.h>
#include <stdio.h>
#include "intrins.h"
//------STC32G SDK等
#include "STC32Gxx.h"
#include "board.h"
#include "common.h"

//------逐飞科技单片机外设驱动头文件
#include "zf_uart.h"
#include "zf_gpio.h"
#include "zf_iic.h"
#include "zf_adc.h"
#include "zf_spi.h"
#include "zf_tim.h"
#include "zf_pwm.h"
#include "zf_nvic.h"
#include "zf_exti.h"
#include "zf_delay.h"
#include "zf_eeprom.h"

//------逐飞科技产品驱动头文件
#include "SEEKFREE_FONT.h"
#include "SEEKFREE_18TFT.h"

#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_TSL1401.h"
#include "SEEKFREE_IPS114_SPI.h"
#include "SEEKFREE_MPU6050.h"
#include "SEEKFREE_OLED.h"
#include "SEEKFREE_ABSOLUTE_ENCODER.h"
#include "SEEKFREE_WIRELESS.h"
#include "SEEKFREE_PRINTF.h"
#include "SEEKFREE_AT24C02.h"
#include "SEEKFREE_BLUETOOTH_CH9141.h"
#include "SEEKFREE_WIRELESS_CH573.h"
#include "SEEKFREE_CONFIG.h"
#include "SEEKFREE_IMU660RA.h"
#include "SEEKFREE_IMU963RA.h"
#include "SEEKFREE_DL1A.h"


#include "key.h"
#include "direction.h"
#include "anotc.h"
#include "math.h"
#include "menu.h"
#include "PID.h"
#include "park.h"
#include "round.h"
#include "control.h"
#include "encoder.h"
#include "eeprom.h"
#endif