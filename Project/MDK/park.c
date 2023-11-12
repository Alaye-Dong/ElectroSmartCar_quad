#include "headfile.h"
#include "park.h"

//int DEBUG_MODE = 1;
int Start_Flag = 0; //为1则发车出库
int XJ = 0;
int garage_out_direction = 1; //出库方向 -1左出库 1右出库
int Hall = 0;
int roundcount_k = 0, roundcount2_k = 0;
int ruku_encoder_round_after_flag = 0;

int CK_count = 0;
int CK_count2 = 0;


void CHUKU()
{	
	if(Start_Flag != 0 && CK_count2>=0 && CK_count2<=1100)
	{
		if(garage_out_direction == 1)
		{
			cha_err1 = +70;
			Target_speed1 =150;//右轮
			Target_speed2 =180;//右轮
		}
		else if(garage_out_direction == -1)
		{
			cha_err1 = -70;
			Target_speed1 =180;//右轮
			Target_speed2 =150;//右轮
		}
	}
	
	else if(Start_Flag == 1)
	{
		XJ=1;
	}
	
}

void RuKu()
{
	roundcount = (ctimer_count_read(CTIM0_P34)+ctimer_count_read(CTIM3_P04))*0.15;
	roundcount2 = roundcount2 + roundcount;
	if(roundcount2>=0 && roundcount2<=1000) //1300
	{
		BEEP = 1;
		Target_speed1 = -50;
		Target_speed2 = -50;
		cha_err1 = 0;
	}
	else
	{
		roundcount_k = (ctimer_count_read(CTIM0_P34)+ctimer_count_read(CTIM3_P04))*0.15;
		roundcount2_k = roundcount2_k + roundcount_k;
	
		if(roundcount2_k>=0 && roundcount2_k<=4000)
		{
			Target_speed1 = -50;
			Target_speed2 = -50;
			BEEP = 1;
		}
		else
		{
			mpu660_angle();
			if(abs(angle) <= 80)
			{
				Target_speed1 = 70;
				Target_speed2 = 70;
				if(garage_out_direction == 1)
				{
					cha_err1 = 72;
				}
				else if(garage_out_direction == -1)
				{
					cha_err1= -72;
				}
			}
			else
			{
				BEEP = 0;
				Target_speed1 = 0;
				Target_speed2 = 0;
				cha_err1 = 0;
			}
		}
	}		
}

//入库，倒车入库式
void RuKu_Back_Into()
{
	roundcount =(ctimer_count_read(CTIM0_P34)+ctimer_count_read(CTIM3_P04))*0.1;
	roundcount2 = roundcount2 + roundcount;
	if(roundcount2>=0&&roundcount2<=1000) //速度150 匹配1000		 速度165 匹配1300？
	{
		BEEP = 1;
		Target_speed1 = 50; //速度150 匹配-100		速度165 匹配-200？
		Target_speed2 = 50;
		cha_err1 = 0;
	}
	else if(roundcount2<9000&&roundcount2>1000)
	{
		mpu660_angle();	
		BEEP = 1;
		switch(garage_out_direction)
		{
			case 1:
//					Target_speed1 = -120;
//					Target_speed2 = -160;
					cha_err1 = 72;
					if(abs(angle)<=90)
					{
						Target_speed1 = -120;
						Target_speed2 = -160;	
					}
					else 
					{
						BEEP = 0;
						Target_speed1 = 0;
						Target_speed2 = 0;
						cha_err1 = 0;
					}
					break;
					
			case -1:
//					Target_speed1 = -160;
//					Target_speed2 = -120;
					cha_err1 = -72;
					if(abs(angle)<=90)
					{
						Target_speed1 = -160;
						Target_speed2 = -120;	
					}
					else 
					{
						BEEP = 0;
						Target_speed1 = 0;
						Target_speed2 = 0;
						cha_err1 = 0;
					}
					break;
		}
	}
}





//入库，出圆环编码器正车入库式
void RuKu_Encoder_Round_After()
{
    roundcount =(ctimer_count_read(CTIM0_P34)+ctimer_count_read(CTIM3_P04))*0.1;
	roundcount2 = roundcount2 + roundcount;
    
    switch(ruku_encoder_round_after_flag)
    {
        case 0: 
                break;
        
        case 1:
                Ordinary_trace();
                if(roundcount2 > 2000)
                {
                    ruku_encoder_round_after_flag = 2;
                }
                break;
                
        case 2:
                mpu660_angle();	
                BEEP = 1;
        
                cha_err1 = 72;
                if(abs(angle)<=90)
                {
                    Target_speed1 = -160;
                    Target_speed2 = -120;	
                }
                else 
                {
                    BEEP = 0;
                    Target_speed1 = 0;
                    Target_speed2 = 0;
                    cha_err1 = 0;
                }
                break;        
    }
}



//跑两圈控制变量还原函数
int park_number = 0;
void Re_Start()
{
	roundcount = (ctimer_count_read(CTIM0_P34)+ctimer_count_read(CTIM3_P04))*0.15;
	roundcount2 = roundcount2 + roundcount;
	Ordinary_trace();
	if(roundcount2 > 1000)
	{
		Hall = 0;
		roundcount2 = 0;
		round_number = 0;
		obstacle_number = 0;
		park_number++;
	}
}



//isr:

//	else if(Hall==1)
//	{	
//		if(park_number == 1)
//		{
//			Re_Start();
//		}
//		else if(park_number == 2)
//		{
//			RuKu();
//		}
//	} 