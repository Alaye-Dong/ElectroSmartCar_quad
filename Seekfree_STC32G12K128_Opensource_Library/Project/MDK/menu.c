#include "headfile.h"
uint8 menu_flag = 0;
uint8 function = 1;
uint8 function1 = 0;
uint8 function2 = 0;
uint8 function3 = 0;





//float speed_e=0.0;


void LCDLight_adc()
{
    //原始电感值
    ips114_showstr_simspi(0, 0, "aLL");
    ips114_showint16_simspi(40, 0, g_ValueOfAD[0]);
    ips114_showstr_simspi(100, 0, "aL");
    ips114_showint16_simspi(150, 0, g_ValueOfAD[1]);
    ips114_showstr_simspi(0, 1, "mid");
    ips114_showint16_simspi(40, 1, g_ValueOfAD[2]);
    ips114_showstr_simspi(100, 1, "aR");
    ips114_showint16_simspi(150, 1, g_ValueOfAD[3]);
    ips114_showstr_simspi(0, 2, "aRR");
    ips114_showint16_simspi(40, 2, g_ValueOfAD[4]);
    //归一化后电感值
    ips114_showstr_simspi(0, 3, "aLL");
    ips114_showint16_simspi(40, 3, all);
    ips114_showstr_simspi(100, 3, "aL");
    ips114_showint16_simspi(150, 3, al);
    ips114_showstr_simspi(0, 4, "mid");
    ips114_showint16_simspi(40, 4, mid);
    ips114_showstr_simspi(100, 4, "aR");
    ips114_showint16_simspi(150, 4, ar);
    ips114_showstr_simspi(0, 5, "aRR");
    ips114_showint16_simspi(40, 5, arr);
}

void LCDLight_star2()
{
//  ips114_showstr_simspi(7,0,"adc0");ips114_showint32_simspi(77,0,ADC_valu[0]);
//	ips114_showstr_simspi(7,1,"adc1");ips114_showint32_simspi(77,1,ADC_valu[1]);
//	ips114_showstr_simspi(7,2,"adc2");ips114_showint32_simspi(77,2,ADC_valu[2]);
//	ips114_showstr_simspi(7,3,"adc3");ips114_showint32_simspi(77,3,ADC_valu[3]);
//	ips114_showstr_simspi(7,4,"final0");ips114_showint32_simspi(77,4,ADC_Final[0]);
//	ips114_showstr_simspi(7,5,"final1");ips114_showint32_simspi(77,5,ADC_Final[1]);
//	ips114_showstr_simspi(7,6,"final2");ips114_showint32_simspi(77,6,ADC_Final[2]);
//	ips114_showstr_simspi(7,7,"final3");ips114_showint32_simspi(77,7,ADC_Final[3]);
//	ips114_showstr_simspi(7,8,"chabi");ips114_showint32_simspi(77,8,Parameter_EM.ADC_ALL);

}

//uint8 get_key(void)
//{
//    uint8 s1 = 0;
//    if(KEY1_PIN == 1 || KEY2_PIN == 1 || KEY3_PIN == 1 || KEY4_PIN == 1)// || KEY5_PIN == 1) //检测五向开关
//    {
//        delay_ms(100);
//        if(KEY1_PIN == 0)
//        {
//            s1 = 1;
//        }
//        else if(KEY2_PIN == 0)
//        {
//            s1 = 2;
//        }
//        else if(KEY3_PIN == 0)
//        {
//            s1 = 3;
//        }
//        else if(KEY4_PIN == 0)
//        {
//            s1 = 4;
//        }
////        else if(KEY5_PIN == 0)
////        {
////            s1 = 5;
////        }
////        else if(KEY6_PIN == 0)
////        {
////            s1 = 6;
////        }
//    }
//    while(key1_status == 0 || key2_status == 0 || key3_status == 0 || key4_status == 0 )//|| key5_status == 0 || key6_status == 0) ;
//    return s1;
//}

//void menu1(void)
//{
//    if(menu_flag == 0)
//    {
//        if(function == 1)
//        {
//            int8 static s1 = 0, s2 = 0;
//            s1 = get_key();
//            if(s1 != 0)
//            {
//                if(s1 == down)
//                {
//                    s2 += 1;
//                    if(s2 >= 8)
//                        s2 = 8;
//                    ips114_showstr_simspi(0, s2 - 1, "   ");
//                }
//                else if(s1 == up)
//                {
//                    s2 -= 1;
//                    if(s2 <= 0)
//                        s2 = 0;
//                    ips114_showstr_simspi(0, s2 + 1, "   ");
//                }
//            }
//            ips114_showstr_simspi(0, s2, "-->");
//            ips114_showstr_simspi(30, 0, "adc_display");
//            ips114_showstr_simspi(30, 1, "adc_display");
//            ips114_showstr_simspi(30, 2, "sports_pid");
//            ips114_showstr_simspi(30, 3, "speed_pid");
//            ips114_showstr_simspi(30, 4, "angle_pid");
//            if(s1 == certain)
//            {
//                switch(s2) //次界面功能号
//                {
//                case 0:
//                    function1 = 1; //tft_display界面
//                    ips114_clear_simspi(BLACK);
//                    break;
//                case 1:
//                    function1 = 2;
//                    ips114_clear_simspi(BLACK);
//                    break;
//                case 2:
//                    function1 = 3; //dir_pid界面
//                    ips114_clear_simspi(BLACK);
//                    break;
//                case 3:
//                    function1 = 4;
//                    ips114_clear_simspi(BLACK);
//                    break;
//                default:
//                    break;
//                }
//                s1 = 0;
//                s2 = 0;
//                function = 2;
//                lcd_clear_simspi(BLACK);
//            }
//        }
//        if(function1 != 0)
//        {
//            switch(function1) //次页面功能号
//            {
//            case 1:
//                adc_display();
//                break;
//            case 2:
//                ;
//                break;
//            case 3:
//                sports_param();
//                break;


//            }
//        }



//    }
//}

//void adc_display(void)
//{
//    static uint8 s1 = 0;
//    if(function1 == 1)
//    {
//        LCDLight_adc(); //显示函数
//        s1 = get_key();
//        if(s1 == back)
//        {
//            s1 = 0;
//            function = 1;
//            function1 = 0;
//            ips114_clear_simspi(BLACK);
//        }
//    }
//}

//void sports_param()
//{
//    static int16 s1 = 0, s2 = 0;
//    if(function1 == 3 && function2 == 0)
//    {
//        s1 = get_key();
//        if(s1 != 0)
//        {
//            if(s1 == down)
//            {
//                s2 += 1;
//                if(s2 >= 9)s2 = 9;
//                ips114_showstr_simspi(0, s2 - 1, "   ");
//            }
//            else if(s1 == up)
//            {
//                s2 -= 1;
//                if(s2 <= 0)s2 = 0;
//                ips114_showstr_simspi(0, s2 + 1, "   ");
//            }
//        }
//        ips114_showstr_simspi(0, s2, "-->");
//        ips114_showstr_simspi(30, 0, "g_dirControl_P");
//        ips114_showstr_simspi(30, 1, "g_dirControl_d");
//        ips114_showstr_simspi(30, 2, "angle_kp");
//        ips114_showstr_simspi(30, 3, "Motor_Kp_L");
//        ips114_showstr_simspi(30, 4, "Motor_Ki_L");
//				ips114_showstr_simspi(30, 5, "Motor_Kp_R");
//        ips114_showstr_simspi(30, 6, "Motor_Ki_R");
//        if(function == 2 && s1 == back)
//        {
//            ips114_clear_simspi(BLACK);
//            function = 1;
//            function1 = 0;
//        }
//        else if(s1 == certain)
//        {
//            switch(s2)//次页面功能号
//            {
//            case 0 :
//                function2 = 1;
//                break;
//            case 1 :
//                function2 = 2;
//                break;
//            case 2 :
//                function2 = 3;
//                break;
//            case 3 :
//                function2 = 4;
//                break;
//						case 4 :
//                function2 = 5;
//                break;
//					  case 5 :
//                function2 = 6;
//                break;
//						case 6 :
//                function2 = 7;
//                break;
//            default:
//                break;
//            }
//            s1 = 0;
//            s2 = 0;
//            ips114_clear_simspi(BLACK);
//        }
//    }
//    else if(function1 == 3 && function2 != 0)
//    {
//        static float num = 0.0;
//        s1 = get_key();
//        if(s1 != 0)
//        {
//            if(s2 == 0)
//                num = 0.01;
//            else if(s2 == 1)
//                num = 0.1;
//            else if(s2 == 2)
//                num = 1;
//            else if(s2 == 3)
//                num = 10;
//            if(s1 == down)
//            {
//                switch(function2)
//                {
//                case 1 :
//                    g_dirControl_P = g_dirControl_P - num;
//                    break;
//                case 2 :
//                    g_dirControl_D = g_dirControl_D - num;
//                    break;
//                case 3 :
//                    angle_kp1 = angle_kp1 - num;
//                    break;
//                case 4 :
//                    Motor_Kp_L = Motor_Kp_L - num;
//                    break;
//								case 5 :
//                    Motor_Ki_L = Motor_Ki_L - num;
//                    break;
//								case 6 :
//                    Motor_Kp_R = Motor_Kp_R - num;
//                    break;
//								case 7 :
//                    Motor_Ki_R = Motor_Ki_R - num;
//                    break;
//                default :
//                    break;
//                }
//            }
//            else if(s1 == up)
//            {
//                switch(function2)
//                {
//                 case 1 :
//                    g_dirControl_P = g_dirControl_P + num;
//                    break;
//                case 2 :
//                    g_dirControl_D = g_dirControl_D + num;
//                    break;
//                case 3 :
//                    angle_kp1 = angle_kp1 + num;
//                    break;
//                case 4 :
//                    Motor_Kp_L = Motor_Kp_L + num;
//                    break;
//								case 5 :
//                    Motor_Ki_L = Motor_Ki_L + num;
//                    break;
//								case 6 :
//                    Motor_Kp_R = Motor_Kp_R + num;
//                    break;
//								case 7 :
//                    Motor_Ki_R = Motor_Ki_R + num;
//                    break;
//                default :
//                    break;
//                }
//            }
//            else if(s1 == expand)
//            {
//                s2++;
//                if(s2 > 4)s2 = 4;
//            }
//            else if(s1 == cut)
//            {
//                s2--;
//                if(s2 < 0)s2 = 0;
//            }
//        }
//        switch(function2)
//        {
//        case 1 :
//            ips114_showfloat_simspi(20, 0, g_dirControl_P, 3, 3);
//            break;
//        case 2 :
//            ips114_showfloat_simspi(20, 0, g_dirControl_D, 3, 3);
//            break;
//        case 3 :
//            ips114_showfloat_simspi(20, 0, angle_kp1, 3, 3);
//            break;
//        case 4 :
//            ips114_showfloat_simspi(20, 0, Motor_Kp_L, 3, 3);
//            break;
//        case 5 :
//            ips114_showfloat_simspi(20, 0, Motor_Ki_L, 3, 3);
//            break;
//        case 6 :
//            ips114_showfloat_simspi(20, 0, Motor_Kp_R, 3, 3);
//            break;
//        case 7 :
//            ips114_showfloat_simspi(20, 0, Motor_Ki_R, 3, 3);
//            break;				
//        default :
//            break;
//        }
//        if(s1 == back)
//        {
//            s1 = 0, s2 = 0;
//            function2 = 0;
//            ips114_clear_simspi(BLACK);
//        }
//        else if(s1 == certain) //读取记忆存储
//        {
//				save_float(g_dirControl_P,0);
//				save_float(g_dirControl_D,1);
//				save_float(angle_kp1,2);
//				save_float(Motor_Kp_L,3);
//				save_float(Motor_Ki_L,4);
//				save_float(Motor_Kp_R,5);
//				save_float(Motor_Ki_R,6);
//				ips114_clear_simspi(BLACK);
//        }
//    }
//}


