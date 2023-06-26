#include "key.h"

////定义按键引脚
//#define KEY1_PIN    P71//P71
//#define KEY2_PIN    P70//P70	
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

uint8 key1_count;
uint8 key2_count;
uint8 key3_count;
uint8 key4_count;

uint8 test1=0,test2=0,test3=0,test4=0;
uint8 param1_1, param1_2, param3 , param4 = 0;

int Dispay_Codename = 0;       //显示页面代号
int This_Codename = 0;			//本页面编号
uint8 KeystrokeLabel = 0;			//按压状态
uint8 CursorRow= 0; //光标所在行号
uint8 MenuNextFlag = 0; //光标所指菜单进入标志位

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
				key1_count++;
		}

		if(key2_flag)   
		{
				key2_flag = 0;//使用按键之后，应该清除标志位
				KeystrokeLabel = 2;
				key2_count++;
		}

		if(key3_flag)   
		{
				key3_flag = 0;//使用按键之后，应该清除标志位
				KeystrokeLabel = 3;
				key3_count++;
		}

		if(key4_flag)   
		{
				key4_flag = 0;//使用按键之后，应该清除标志位
				KeystrokeLabel = 4;
				key4_count++;
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
		
		}
		
}

void Cursor(void)
{		
		int i;
		MenuNextFlag = 0;
		
		while(MenuNextFlag == 0)
		{		
				Keystroke_Scan();
		
				if (KeystrokeLabel == 1)
				{
						CursorRow--;
						for (i = 0; i < 10; i++)
						{
						if(i == CursorRow)
						lcd_showstr(0, CursorRow, ">");
						else
						lcd_showstr(0, i, " ");
						}
				}
				
				if (KeystrokeLabel == 2)
				{
						CursorRow++;
						for (i = 0; i < 10; i++)
						{
						if(i == CursorRow)
						lcd_showstr(0, CursorRow, ">");
						else
						lcd_showstr(0, i, " ");
						}
				}
				
				if (KeystrokeLabel == 3)
				{
						//CursorRow = 0;
						MenuNextFlag = 1;
				}
				
				if (KeystrokeLabel == 4)
				{
						MenuNextFlag = -1;
				}
				
		}
		
}
				
void KeystrokeLabel_Switch( float change_unit, uint8 value_bit)	//temp_value, 上一页， +-的单位值, 扇区存储的位置编号
{		
			static float tem_value;
			
			//eeprom_init();
iap_read_bytes(0x00, date_buff, 100);		//从EEPROM中读取数据
Motor_Kp_L 			= read_float(0);
Motor_Ki_L      	= read_float(1);
Motor_Kp_R      	= read_float(2);
Motor_Ki_R     	= read_float(3);
angle_kp1     		= read_float(4);
ZX_kp						= read_float(5);
ZX_kd						= read_float(6);
g_dirControl_P	= read_float(7);
g_dirControl_D   = read_float(8);		

		lcd_showfloat(11*8,6,tem_value,2,2);
		Keystroke_Scan();
			if (sw1_status == 0)
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
		lcd_showstr(1*8,1,"Speed");
		lcd_showstr(1*8,2,"Angle");
		lcd_showstr(1*8,3,"Direction");
		lcd_showstr(1*8,4,"Electrical");
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
    }
}

void Keystroke_Menu_ONE(void) //1
{		
		lcd_showstr(1*8,1,"Mot_Kp_L");
		lcd_showstr(1*8,2,"Mot_Ki_L");
		lcd_showstr(1*8,3,"Mot_Kp_R");
		lcd_showstr(1*8,4,"Mot_Ki_R");
		
		lcd_showfloat(11*8,1,Motor_Kp_L,2,2);
		lcd_showfloat(11*8,2,Motor_Ki_L,2,2);
		lcd_showfloat(11*8,3,Motor_Kp_R,2,2);
		lcd_showfloat(11*8,4,Motor_Ki_R,2,2);
		
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
		
		lcd_showstr(1*8,1,"Mot_Kp_L"); //&
		lcd_showstr(1*8,2,"Mot_Ki_L");
		lcd_showstr(1*8,3,"Mot_Kp_R");
		lcd_showstr(1*8,4,"Mot_Ki_R");
		lcd_showstr(0,1,"&"); //&标志提示
		
		lcd_showfloat(11*8,1,Motor_Kp_L,2,2); //&
		lcd_showfloat(11*8,2,Motor_Ki_L,2,2);
		lcd_showfloat(11*8,3,Motor_Kp_R,2,2);
		lcd_showfloat(11*8,4,Motor_Ki_R,2,2);
		
		KeystrokeLabel_Switch(0.01, 0);
		
		
}

void Keystroke_Menu_ONE_Two(void)  //12
{		
	
		This_Codename = 12;
		
		lcd_showstr(1*8,1,"Mot_Kp_L");
		lcd_showstr(1*8,2,"Mot_Ki_L");	 //&	
		lcd_showstr(1*8,3,"Mot_Kp_R");
		lcd_showstr(1*8,4,"Mot_Ki_R");
		lcd_showstr(0,2,"&"); //&标志提示
		
		lcd_showfloat(11*8,1,Motor_Kp_L,2,2); 
		lcd_showfloat(11*8,2,Motor_Ki_L,2,2);	//&
		lcd_showfloat(11*8,3,Motor_Kp_R,2,2);
		lcd_showfloat(11*8,4,Motor_Ki_R,2,2);
		
		KeystrokeLabel_Switch(0.01, 1);
}

void Keystroke_Menu_ONE_Three(void)  //13	
{
		
		This_Codename = 13;
		
		lcd_showstr(1*8,1,"Mot_Kp_L");
		lcd_showstr(1*8,2,"Mot_Ki_L");	 	
		lcd_showstr(1*8,3,"Mot_Kp_R");		//&
		lcd_showstr(1*8,4,"Mot_Ki_R");
		lcd_showstr(0,3,"&"); //&
		
		lcd_showfloat(11*8,1,Motor_Kp_L,2,2); 
		lcd_showfloat(11*8,2,Motor_Ki_L,2,2);	
		lcd_showfloat(11*8,3,Motor_Kp_R,2,2);//&
		lcd_showfloat(11*8,4,Motor_Ki_R,2,2);
		
		KeystrokeLabel_Switch(0.01, 2);
}

void Keystroke_Menu_ONE_Four(void)  //14
{		
		static float temp_value;
		eeprom_init();
		This_Codename = 14;
		
		lcd_showstr(1*8,1,"Mot_Kp_L");
		lcd_showstr(1*8,2,"Mot_Ki_L");	 	
		lcd_showstr(1*8,3,"Mot_Kp_R");
		lcd_showstr(1*8,4,"Mot_Ki_R");	//&
		lcd_showstr(0,4,"&"); //&
		
		lcd_showfloat(11*8,1,Motor_Kp_L,2,2); 
		lcd_showfloat(11*8,2,Motor_Ki_L,2,2);	
		lcd_showfloat(11*8,3,Motor_Kp_R,2,2);
		lcd_showfloat(11*8,4,Motor_Ki_R,2,2);	//&
		
    KeystrokeLabel_Switch(0.01, 3);
}


void Keystroke_Menu_TWO(void) //2
{		
		lcd_showstr(1*8,1,"angle_kp1");
		lcd_showstr(1*8,2," ");
		lcd_showstr(1*8,3," ");
		lcd_showstr(1*8,4," ");
		
		lcd_showfloat(11*8,1,angle_kp1,2,2);
//		lcd_showfloat(11*8,2, ,2,2);
//		lcd_showfloat(11*8,3, ,2,2);
//		lcd_showfloat(11*8,4, ,2,2);
		
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
				//case......
		}

}

void Keystroke_Menu_TWO_One(void)  //21		&angle_kp1
{

		This_Codename = 21;			//本页面编号
		
		lcd_showstr(1*8,1,"angle_kp1"); //&
		lcd_showstr(1*8,2," ");
		lcd_showstr(1*8,3," ");
		lcd_showstr(1*8,4," ");
		lcd_showstr(0,1,"&"); //&
		
		lcd_showfloat(11*8,1,angle_kp1,2,2);
//		lcd_showfloat(11*8,2, ,2,2);
//		lcd_showfloat(11*8,3, ,2,2);
//		lcd_showfloat(11*8,4, ,2,2);
		
		KeystrokeLabel_Switch(0.01, 4);
}		

void Keystroke_Menu_THREE(void) //3
{		
		lcd_showstr(1*8,1,"ZX_kp"); 
		lcd_showstr(1*8,2,"ZX_kd");
		lcd_showstr(1*8,3,"g_dirControl_P");
		lcd_showstr(1*8,4,"g_dirControl_D");
	
		lcd_showfloat(11*8,1,ZX_kp,2,2); 
		lcd_showfloat(11*8,2,ZX_kd,2,2);
		lcd_showfloat(11*8,3,g_dirControl_P,2,2);
		lcd_showfloat(11*8,4,g_dirControl_D,2,2);
		
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
		
		lcd_showstr(1*8,1,"ZX_kp"); //&
		lcd_showstr(1*8,2,"ZX_kd");
		lcd_showstr(1*8,3,"g_dir_P");
		lcd_showstr(1*8,4,"g_dir_D");
		lcd_showstr(0,1,"&"); 
		
		lcd_showfloat(11*8,1,ZX_kp,2,2); //&
		lcd_showfloat(11*8,2,ZX_kd,2,2);
		lcd_showfloat(11*8,3,g_dirControl_P,2,2);
		lcd_showfloat(11*8,4,g_dirControl_D,2,2);
		
    KeystrokeLabel_Switch(0.01, 5);
}

void Keystroke_Menu_THREE_Two(void)  //32
{		
		This_Codename = 32;			//本页面编号
		
		lcd_showstr(1*8,1,"ZX_kp"); 
		lcd_showstr(1*8,2,"ZX_kd");//&
		lcd_showstr(1*8,3,"g_dir_P");
		lcd_showstr(1*8,4,"g_dir_D");
		lcd_showstr(0,2,"&"); 
		
		lcd_showfloat(11*8,1,ZX_kp,2,2); 
		lcd_showfloat(11*8,2, ZX_kd,2,2);//&
		lcd_showfloat(11*8,3,g_dirControl_P,2,2);
		lcd_showfloat(11*8,4,g_dirControl_D,2,2);
		
     KeystrokeLabel_Switch(0.01, 6);
}

void Keystroke_Menu_THREE_Three(void)  //33
{		
		This_Codename = 33;			//本页面编号
		
		lcd_showstr(1*8,1,"ZX_kp"); 
		lcd_showstr(1*8,2,"ZX_kd");
		lcd_showstr(1*8,3,"g_dir_P");//&
		lcd_showstr(1*8,4,"g_dir_D");
		lcd_showstr(0,3,"&"); //&
		
		lcd_showfloat(11*8,1,ZX_kp,2,2); 
		lcd_showfloat(11*8,2, ZX_kd,2,2);
		lcd_showfloat(11*8,3,g_dirControl_P,2,2);
		lcd_showfloat(11*8,4,g_dirControl_D,2,2);
		
     KeystrokeLabel_Switch(0.01, 7);
}

void Keystroke_Menu_THREE_Four(void)  //34
{		
		This_Codename = 34;			//本页面编号
		
		lcd_showstr(1*8,1,"ZX_kp"); 
		lcd_showstr(1*8,2,"ZX_kd");
		lcd_showstr(1*8,3,"g_dir_P");
		lcd_showstr(1*8,4,"g_dir_D");//&
		lcd_showstr(0,4,"&"); //&
		
		lcd_showfloat(11*8,1,ZX_kp,2,2); 
		lcd_showfloat(11*8,2, ZX_kd,2,2);
		lcd_showfloat(11*8,3,g_dirControl_P,2,2);
		lcd_showfloat(11*8,4,g_dirControl_D,2,2);//&
		
     KeystrokeLabel_Switch(0.01, 8);
}

void Keystroke_Menu_FOUR(void) //4
{
		lcd_showfloat(65,1,g_ValueOfAD[0],4,2);   //右竖
		lcd_showfloat(65,2,g_ValueOfAD[1],4,2);  //右斜
		lcd_showfloat(5,0,g_ValueOfAD[2],4,2);  //左横
		lcd_showfloat(65,0,g_ValueOfAD[3],4,2);  //右横
		lcd_showfloat(5,2,g_ValueOfAD[4],4,2);//左斜
		lcd_showfloat(5,1,g_ValueOfAD[5],4,2);//左竖   

		lcd_showfloat(65,6,servo,4,2);
		lcd_showfloat(5,7,g_dirControl_P,4,2);
		lcd_showfloat(65,7,g_dirControl_D,4,2);
		
		Keystroke_Scan();
		switch(KeystrokeLabel)
		{
				case 0 :
						Dispay_Codename = 4;
						break;
//				case KeystrokeONE :
//						Dispay_Codename = 41;
//					 lcd_clear(WHITE);
//						break;
//				case KeystrokeTWO :
//						Dispay_Codename = 42;
//						lcd_clear(WHITE);
//						break;
//				case KeystrokeTHREE :
//						Dispay_Codename = 43;
//						lcd_clear(WHITE);
//						break;
				case KeystrokeFOUR :
						Dispay_Codename = 0;		//返回第0页
						lcd_clear(WHITE);
						break;
		}
}


