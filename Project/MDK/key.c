#include "key.h"

////定义按键引脚
//#define KEY1_PIN    P71
//#define KEY2_PIN    P70	
//#define KEY3_PIN    P72
//#define KEY4_PIN    P73
////定义拨码开关引脚
//#define SW1_PIN		 P76
//#define SW2_PIN     P75

//定义按键代号
#define KeystrokeONE 1
#define KeystrokeTWO 2
#define KeystrokeTHREE 3
#define KeystrokeFOUR 4

//拨码开关状态变量 ON为0
uint8 sw1_status;
uint8 sw2_status;

//开关状态变量
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;

//上一次开关状态变量
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;

//开关标志位
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;

int Dispay_Codename = 0;       //显示页面代号
int This_Codename = 0;			//本页面编号
uint8 KeystrokeLabel = 0;			//按压状态
uint8 CursorRow= 0; //光标所在行号
uint8 MenuNextFlag = 0; //光标所指菜单进入标志位
uint8 target_value_bit = 0;



void Keystroke_Scan(void)
{

    //获取拨码开关状态
    sw1_status = SW1_PIN;
    sw2_status = SW2_PIN;

    //使用此方法优点在于，不需要使用while(1) 等待，避免处理器资源浪费
    //保存按键状态
    key1_last_status = key1_status;
    key2_last_status = key2_status;
    key3_last_status = key3_status;
    key4_last_status = key4_status;
    //读取当前按键状态
    key1_status = KEY1_PIN;
    key2_status = KEY2_PIN;
    key3_status = KEY3_PIN;
    key4_status = KEY4_PIN;


    //检测到按键按下之后  并放开置位标志位
    if(key1_status && !key1_last_status)    key1_flag = 1;
    if(key2_status && !key2_last_status)    key2_flag = 1;
    if(key3_status && !key3_last_status)    key3_flag = 1;
    if(key4_status && !key4_last_status)    key4_flag = 1;

    //标志位置位之后，可以使用标志位执行自己想要做的事件
    KeystrokeLabel = 0;
    if(key1_flag)   
    {
        key1_flag = 0;//使用按键之后，应该清除标志位
        KeystrokeLabel = 1;
    }

    if(key2_flag)   
    {
        key2_flag = 0;//使用按键之后，应该清除标志位
        KeystrokeLabel = 2;
    }

    if(key3_flag)   
    {
        key3_flag = 0;//使用按键之后，应该清除标志位
        KeystrokeLabel = 3;
    }

    if(key4_flag)   
    {
        key4_flag = 0;//使用按键之后，应该清除标志位
        KeystrokeLabel = 4;
    }

}



void Cursor(void)
{		
    uint8 i;
    MenuNextFlag = 0;

    while(MenuNextFlag == 0)
    {		
        Keystroke_Scan();

        switch(KeystrokeLabel)
        {
            case 1:
                    CursorRow--;
                    break;                   
            case 2:
                    CursorRow++;
                    break;                    
            case 3:
                    MenuNextFlag = 1;
                    break;
            case 4:
                    MenuNextFlag = -1;
                    break;                    
        }
        
        for (i = 0; i < 10; i++)
        {
            if(i == CursorRow)
            {
                lcd_showstr(0, CursorRow, ">");
            }
            else
            {
                lcd_showstr(0, i, " ");
            }
        }

        //箭头限位
        if (CursorRow < 0)
        {
            CursorRow= 0;
        }
        else if (CursorRow > 9)
        {
            CursorRow= 0;
        }
            
    }
		
}
				
void KeystrokeLabel_Switch(float change_unit, uint8 value_bit)	//temp_value, 上一页， +-的单位值, 扇区存储的位置编号
{		
    static float tem_value;
    lcd_showfloat(11*8,6,tem_value,2,2);
    //eeprom_init();
    iap_read_bytes(0x00, date_buff, 100);		//从EEPROM中读取数据
    Motor_Kp_L 		= read_float(0);
    Motor_Ki_L      	= read_float(1);
    Motor_Kp_R      	= read_float(2);
    Motor_Ki_R     	= read_float(3);
    angle_kp1     	= read_float(4);

    g_dirControl_P	= read_float(7);
    g_dirControl_D    = read_float(8);		

    Keystroke_Scan();
    
    if (sw1_status == 0)
    {
        change_unit *= 10; 
    }
    if (sw1_status == 0 && sw2_status == 0)
    {
        change_unit *= 10; 
    }
    
    switch(KeystrokeLabel)
    {
        case 0 :
                Dispay_Codename = This_Codename;
                break;
                    
        case KeystrokeONE :
                tem_value += change_unit;	
                save_float(tem_value,value_bit);
                Dispay_Codename = This_Codename;		
                break;
        case KeystrokeTWO :
                tem_value -= change_unit;			
                save_float(tem_value,value_bit);
                Dispay_Codename = This_Codename;		
                break;
                    
        case KeystrokeTHREE :
                Dispay_Codename /= 10; //返回上一页
                lcd_clear(WHITE);
                break;
        case KeystrokeFOUR :
                Dispay_Codename = 0;	//返回第0页
                lcd_clear(WHITE);
                break;
    }
}
void Keystroke_Special_Value(int* parameter)
{
    Keystroke_Scan();
    switch(KeystrokeLabel)
    {
        case 0 :
                Dispay_Codename = This_Codename;
                break;
                
        case KeystrokeONE :
                *parameter = -1;
                Dispay_Codename = This_Codename;		
                break;
        case KeystrokeTWO :
                *parameter = 1;
                Dispay_Codename = This_Codename;		
                break;
                
        case KeystrokeTHREE :
                Dispay_Codename /= 10; //返回上一页
                lcd_clear(WHITE);
                break;
        case KeystrokeFOUR :
                Dispay_Codename = 0;	//返回第0页
                lcd_clear(WHITE);
                break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      菜单目录
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       启用while来显示目标页面  在每个页面按键按键后都会改变到对应页面，此函数用于更新屏幕显示
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Menu(void)
{
    switch(Dispay_Codename)
    {
        case 0:
            Keystroke_Menu_HOME();
            break;
            
        case 1:
            Keystroke_Menu_ONE(); 
            break;
        case 11:
            Keystroke_Menu_ONE_One();
            break;
        case 12:
            Keystroke_Menu_ONE_Two();
            break;
        case 13:
            Keystroke_Menu_ONE_Three();
            break;
        case 14:
            Keystroke_Menu_ONE_Four();
            break;
            
        case 2:
            Keystroke_Menu_TWO();
            break;
        case 21:
            Keystroke_Menu_TWO_One();
            break;
        case 22:
            Keystroke_Menu_TWO_Two();
            break;
        case 23:
            Keystroke_Menu_TWO_Three();
            break;
        case 24:
            Keystroke_Menu_TWO_Four();
            break;
            
        case 3:
            Keystroke_Menu_THREE();
            break;
        case 31:
            Keystroke_Menu_THREE_One();
            break;
        case 32:
            Keystroke_Menu_THREE_Two();
            break;
        case 33:
            Keystroke_Menu_THREE_Three();
            break;
        case 34:
            Keystroke_Menu_THREE_Four();
            break;
            
        case 4:
            Keystroke_Menu_FOUR();
            break;

        case 5:
            Keystroke_Menu_FIVE();
            break;
        case 51:
            Keystroke_Menu_FIVE_One();
            break;
        case 52:
            Keystroke_Menu_FIVE_Two();
            break;
        case 53:
            Keystroke_Menu_FIVE_Three();
            break;
        case 54:
            Keystroke_Menu_FIVE_Four();
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      总菜单目录
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       此页面为编号为0
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Menu_HOME(void)    //0
{
    lcd_showstr(1*8,1,"Start");
    lcd_showstr(1*8,2,"AI_Round");
    lcd_showstr(1*8,3,"AI_Obstacle");
    lcd_showstr(1*8,4,"Electrical");
    lcd_showstr(1*8,5,"PID_Speed");
    
    Cursor(); 

    switch(CursorRow)
    {
        case 0 :
                Dispay_Codename = 0;
                break;
						
        case 1 :
                Dispay_Codename = 1;
                lcd_clear(WHITE);
                CursorRow = 0;
                break;
        case 2 :
                Dispay_Codename = 2;
                lcd_clear(WHITE);
                CursorRow = 0;
                break;
        case 3 :
                Dispay_Codename = 3;
                lcd_clear(WHITE);
                CursorRow = 0;
                break;
        case 4 :
                Dispay_Codename = 4;
                lcd_clear(WHITE);
                CursorRow = 0;
                break;
				
        case 5 :
                Dispay_Codename = 5;
                lcd_clear(WHITE);
                CursorRow = 0;
                break;
						
    }
}
/*///////////////////////////////////////
    Start
*////////////////////////////////////////
void Menu_ONE_Display(uint8 control_line)
{
    lcd_showstr(1*8,1,"Start_Flag");
    lcd_showstr(1*8,2,"Out_Direction");
    //lcd_showstr(1*8,3,"DEBUG_MODE");    
    lcd_showint32(14*8,1,Start_Flag,1);
    lcd_showint32(14*8,2,garage_out_direction,1);
    //lcd_showint32(14*8,3,DEBUG_MODE,1);    
    lcd_showstr(0,control_line,"&"); //&标志提示
}

void Keystroke_Menu_ONE(void) //1
{		
    Menu_ONE_Display(-1);
    Cursor();
    
    if (MenuNextFlag == -1)
    {
        CursorRow = -1;
    }
    
    switch(CursorRow)
    {		
        case -1 :
                Dispay_Codename = 0;
                lcd_clear(WHITE);
                break;
        case 0 :
                Dispay_Codename = 1;
                break;
                
        case 1 :
                Dispay_Codename = 11;
            // lcd_clear(WHITE);
                break;
        case 2 :
                Dispay_Codename = 12;
                lcd_clear(WHITE);
                break;
        case 3 :
                Dispay_Codename = 13;
                lcd_clear(WHITE);
                break;
        case 4 :
                Dispay_Codename = 14;
                lcd_clear(WHITE);
                break;
        //case......
    }
}

void Keystroke_Menu_ONE_One(void)  //11
{		
    This_Codename = 11;			//本页面编号
    Menu_ONE_Display(1);
    Keystroke_Special_Value(&Start_Flag);
}

void Keystroke_Menu_ONE_Two(void)  //12
{		
    This_Codename = 12;
    Menu_ONE_Display(2);
    Keystroke_Special_Value(&garage_out_direction);
}

void Keystroke_Menu_ONE_Three(void)  //13	
{
    This_Codename = 13;
    Menu_ONE_Display(3);
    //Keystroke_Special_Value(&DEBUG_MODE);

}

void Keystroke_Menu_ONE_Four(void)  //14
{		
    This_Codename = 14;
    Menu_ONE_Display(4);
		
}

/*////////////////////////////////////
    AI_Round
*////////////////////////////////////
void Menu_TWO_Display(uint8 control_line)
{
    lcd_showstr(1*8,1,"round1_type");
    lcd_showstr(1*8,2,"round2_type");
    lcd_showstr(1*8,3,"round3_type");
    lcd_showstr(1*8,4,"round4_type");
    lcd_showstr(1*8,5,"round_num_MAX");

    lcd_showint32(14*8,1,round1_type,1);
    lcd_showint32(14*8,2,round2_type,1);
    lcd_showint32(14*8,3,round3_type,1);
    lcd_showint32(14*8,4,round4_type,1);
    lcd_showint32(14*8,5,round_number_MAX,1);
    
    lcd_showstr(0,control_line,"&"); //&标志提示
}

void Keystroke_Menu_TWO(void) //2
{		
    Menu_TWO_Display(-1);
    Cursor();
    
    if (MenuNextFlag == -1)
    {
            CursorRow = -1;
    }
    
    switch(CursorRow)
    {		
            case -1 :
                    Dispay_Codename = 0;
                    lcd_clear(WHITE);
                    break;
            case 0 :
                    Dispay_Codename = 2;
                    break;
                    
            case 1 :
                    Dispay_Codename = 21;
                // lcd_clear(WHITE);
                    break;
            case 2 :
                    Dispay_Codename = 22;
                    lcd_clear(WHITE);
                    break;
            case 3 :
                    Dispay_Codename = 23;
                    lcd_clear(WHITE);
                    break;
            case 4 :
                    Dispay_Codename = 24;
                    lcd_clear(WHITE);
                    break;
                    
            case 6 :
                    Dispay_Codename = 26;
                    lcd_clear(WHITE);
                    break;
            case 7 :
                    Dispay_Codename = 27;
                    lcd_clear(WHITE);
                    break;
            case 8 :
                    Dispay_Codename = 28;
                    lcd_clear(WHITE);
                    break;		
                    
            //case......
    }

}

void Keystroke_Menu_TWO_One(void) //21
{
    This_Codename = 21;			//本页面编号
    Menu_TWO_Display(1);
    Keystroke_Special_Value(&round1_type);
}
void Keystroke_Menu_TWO_Two(void)  //22
{
    This_Codename = 22;			//本页面编号
    Menu_TWO_Display(2);
    Keystroke_Special_Value(&round2_type);
}
void Keystroke_Menu_TWO_Three(void)  //23
{
    This_Codename = 23;			//本页面编号
    Menu_TWO_Display(3);
    Keystroke_Special_Value(&round3_type);
}
void Keystroke_Menu_TWO_Four(void)  //24
{
    This_Codename = 24;			//本页面编号
    Menu_TWO_Display(4);
    Keystroke_Special_Value(&round4_type);
}

void Menu_THREE_Display(uint8 control_line)
{
    lcd_showstr(1*8,1,"obsta1_type");
    lcd_showstr(1*8,2,"obsta2_type");
    lcd_showstr(1*8,3,"obsta3_type");
    lcd_showstr(1*8,4,"obsta_num_MAX");
    
    lcd_showint32(14*8,1,obstacle1_type,1);
    lcd_showint32(14*8,2,obstacle2_type,1);
    lcd_showint32(14*8,3,obstacle3_type,1);
    lcd_showint32(14*8,4,obstacle_number_MAX,1);

    lcd_showstr(0,control_line,"&"); //&标志提示
}

/*/////////////////////////////////
    AI_Obstacle1
*//////////////////////////////////
void Keystroke_Menu_THREE(void) //3
{		
		Menu_THREE_Display(-1);
		
		Cursor();
		
		if (MenuNextFlag == -1)
		{
				CursorRow = -1;
		}
		
		switch(CursorRow)
		{		
				case -1 :
						Dispay_Codename = 0;
						lcd_clear(WHITE);
						break;
				case 0 :
						Dispay_Codename = 3;
						break;
						
				case 1 :
						Dispay_Codename = 31;
					// lcd_clear(WHITE);
						break;
				case 2 :
						Dispay_Codename = 32;
						lcd_clear(WHITE);
						break;
				case 3 :
						Dispay_Codename = 33;
						lcd_clear(WHITE);
						break;
				case 4 :
						Dispay_Codename = 34;
						lcd_clear(WHITE);
						break;
				//case......
		}

}

void Keystroke_Menu_THREE_One(void)  //31
{
    This_Codename = 31;			//本页面编号
    Menu_THREE_Display(1);
    Keystroke_Special_Value(&obstacle1_type);
}

void Keystroke_Menu_THREE_Two(void)  //32
{		
    This_Codename = 32;			//本页面编号
    Menu_THREE_Display(2);
    Keystroke_Special_Value(&obstacle2_type);
}

void Keystroke_Menu_THREE_Three(void)  //33
{		
    This_Codename = 33;			//本页面编号
    Menu_THREE_Display(3);
    Keystroke_Special_Value(&obstacle3_type);
}

void Keystroke_Menu_THREE_Four(void)  //34
{		
    This_Codename = 34;			//本页面编号
    Menu_THREE_Display(4);
    
}
/*////////////////////////////////
    Electrical
*////////////////////////////////
void Keystroke_Menu_FOUR(void) //4
{
    lcd_showint32(5,0,g_ValueOfAD[0],4);//左竖		
    lcd_showint32(10*8,0,g_ValueOfAD[5],4);   //右竖	
    lcd_showstr(6*8,0,"|05"); 		
    lcd_showint32(5,1,g_ValueOfAD[3],4);  //左横	
    lcd_showint32(10*8,1,g_ValueOfAD[2],4);  //右横
    lcd_showstr(6*8,1,"-32"); 
    lcd_showint32(5,2,g_ValueOfAD[4],4);//	左斜		  
    lcd_showint32(10*8,2,g_ValueOfAD[1],4);  // 右斜
    lcd_showstr(6*8,2,"/41"); 
    
    lcd_showfloat(5,3,Target_speed1,4,0);		
    lcd_showfloat(5*8,3,servo,3,0);
    lcd_showfloat(10*8,3,Target_speed2,4,0);

    lcd_showint32(65,5,roundcount2,5);
    lcd_showfloat(5,5,roundcount2_k,4,0);

    lcd_showfloat(5,6,v_angle,4,3); 
    lcd_showfloat(65,6,angle,4,2); 

    lcd_showfloat(5,7,y_v_angle,4,3); 
    lcd_showfloat(65,7,angle_y,4,2);
    
    lcd_showint32(5,8,e_r1,5);
    lcd_showint32(65,8,e_r2,5);
    
    lcd_showfloat(5,9,dl1a_distance_mm,4,0);      
    lcd_showint32(8*8, 9, obstacle_flag, 1);
    lcd_showint32(10*8, 9, obstacle_number, 1);
    lcd_showint32(12*8, 9, cross_flag, 1);
    
    
    Keystroke_Scan();
    switch(KeystrokeLabel)
    {
        case 0 :
                Dispay_Codename = 4;
                break;

        case KeystrokeFOUR :
                Dispay_Codename = 0;		//返回第0页
                lcd_clear(WHITE);
                break;
    }
}

/*//////////////////////////////////
    PID_Speed
*//////////////////////////////////
void Menu_FIVE_Display(uint8 control_line)
{
    lcd_showstr(1*8,1,"gd_P"); 
    lcd_showfloat(65,1,g_dirControl_P,2,3);
    lcd_showstr(1*8,2,"gd_D"); 
    lcd_showfloat(65,2,g_dirControl_D,2,3);

    lcd_showstr(1*8,3,"normalS"); 
    lcd_showint32(65,3,normal_speed, 3);
    lcd_showstr(1*8,4,"round_S"); 
    lcd_showint32(65,4,round_speed, 3);
    lcd_showstr(1*8,9,"servo"); 
    lcd_showfloat(65,9,servo,3,0);
    
    lcd_showstr(0,control_line,"&"); //&标志提示
}

void Keystroke_Menu_FIVE(void) //5
{		
    Menu_FIVE_Display(-1);		
    Cursor();
    
    if (MenuNextFlag == -1)
    {
            CursorRow = -1;
    }
    
    switch(CursorRow)
    {		
        case -1 :
                Dispay_Codename = 0;
                lcd_clear(WHITE);
                break;
        case 0 :
                Dispay_Codename = 5;
                break;
                
        case 1 :
                Dispay_Codename = 51;
                lcd_clear(WHITE);
                break;
        case 2 :
                Dispay_Codename = 52;
                lcd_clear(WHITE);
                break;
        case 3 :
                Dispay_Codename = 53;
                lcd_clear(WHITE);
                break;
        case 4 :
                Dispay_Codename = 54;
                lcd_clear(WHITE);
                break;
        //case......
    }

}

void Keystroke_Menu_FIVE_One(void)  //51
{
    float change_unit = 0.001;
    This_Codename = 51;			//本页面编号
    Menu_FIVE_Display(1);		

    Keystroke_Scan();
    if (sw1_status == 0)
    {
        change_unit = 0.01; 
    }
    if (sw1_status == 0 && sw2_status == 0)
    {
        change_unit = 0.1; 
    }

    switch(KeystrokeLabel)
    {
        case 0 :
                Dispay_Codename = This_Codename;
                break;
                
        case KeystrokeONE :
                g_dirControl_P += change_unit;	
                Dispay_Codename = This_Codename;		
                break;
        case KeystrokeTWO :
                g_dirControl_P -= change_unit;			
                Dispay_Codename = This_Codename;		
                break;
                        
        case KeystrokeTHREE :
            Dispay_Codename /= 10; //返回上一页
            lcd_clear(WHITE);
            break;
        case KeystrokeFOUR :
            Dispay_Codename = 0;	//返回第0页
            lcd_clear(WHITE);
            break;
    }

}

void Keystroke_Menu_FIVE_Two(void)  //52
{
		float change_unit = 0.001;
		This_Codename = 52;			//本页面编号
		Menu_FIVE_Display(2);		
		Keystroke_Scan();
		if (sw1_status == 0)
		{
			change_unit = 0.01; 
		}
		if (sw1_status == 0 && sw2_status == 0)
		{
			change_unit = 0.1; 
		}

		switch(KeystrokeLabel)
    {
        case 0 :
						Dispay_Codename = This_Codename;
						break;
						
				case KeystrokeONE :
						g_dirControl_D += change_unit;	
						Dispay_Codename = This_Codename;		
						break;
        case KeystrokeTWO :
						g_dirControl_D -= change_unit;			
						Dispay_Codename = This_Codename;		
						break;
						
        case KeystrokeTHREE :
            Dispay_Codename /= 10; //返回上一页
            lcd_clear(WHITE);
            break;
        case KeystrokeFOUR :
            Dispay_Codename = 0;	//返回第0页
            lcd_clear(WHITE);
            break;
    }
}

void Keystroke_Menu_FIVE_Three(void)  //53
{
		float change_unit = 0.001;
		This_Codename = 53;			//本页面编号
		Menu_FIVE_Display(3);			
		Keystroke_Scan();
		if (sw1_status == 0)
		{
			change_unit = 0.01; 
		}
		if (sw1_status == 0 && sw2_status == 0)
		{
			change_unit = 0.1; 
		}

		switch(KeystrokeLabel)
    {
        case 0 :
						Dispay_Codename = This_Codename;
						break;
						
//				case KeystrokeONE :
//						g_fDirectionError_2_proportion_1 += change_unit;	
//						Dispay_Codename = This_Codename;		
//						break;
//        case KeystrokeTWO :
//						g_fDirectionError_2_proportion_1 -= change_unit;			
//						Dispay_Codename = This_Codename;		
//						break;
						
        case KeystrokeTHREE :
            Dispay_Codename /= 10; //返回上一页
            lcd_clear(WHITE);
            break;
        case KeystrokeFOUR :
            Dispay_Codename = 0;	//返回第0页
            lcd_clear(WHITE);
            break;
    }
}

void Keystroke_Menu_FIVE_Four(void)  //54
{
		float change_unit = 0.001;
		This_Codename = 54;			//本页面编号
		Menu_FIVE_Display(4);		
		
	
		Keystroke_Scan();
		if (sw1_status == 0)
		{
			change_unit = 0.01; 
		}
		if (sw1_status == 0 && sw2_status == 0)
		{
			change_unit = 0.1; 
		}

		switch(KeystrokeLabel)
    {
        case 0 :
						Dispay_Codename = This_Codename;
						break;
						
//				case KeystrokeONE :
//						g_fDirectionError_2_proportion_2 += change_unit;	
//						Dispay_Codename = This_Codename;		
//						break;
//        case KeystrokeTWO :
//						g_fDirectionError_2_proportion_2 -= change_unit;			
//						Dispay_Codename = This_Codename;		
//						break;
						
        case KeystrokeTHREE :
            Dispay_Codename /= 10; //返回上一页
            lcd_clear(WHITE);
            break;
        case KeystrokeFOUR :
            Dispay_Codename = 0;	//返回第0页
            lcd_clear(WHITE);
            break;
    }
}