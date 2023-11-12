#include "headfile.h"
#include "round.h"

int e_r1 = 0, e_r2 = 0;
int flag_r_hd = 0; //入环岛预测
int flag_c_hd = 0; //出环岛标志位

int flag_hd_Z = 0; //左环岛
int flag_hd_R = 0; //右环岛
int roundcount = 0;
int roundcount2 = 0;
int roundcount3 = 0;

int round_number = 0;	

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int round_number_MAX = 2;   //环岛最大数量！！！
int round1_type = 1,round2_type = -1,round3_type = 1,round4_type = -1; //-1入左环，1入右环
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int real_obstacle_flag = 0;
int obstacle_flag = 0;
int obstacle_number = 0;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int obstacle_number_MAX = 1;    //避障最大数量！！！
int obstacle1_type = 1, obstacle2_type = -1, obstacle3_type = 0;//已关闭，若启用Obstacle_Deal，由obstacle_type决定的障碍处理，-1为坡道，1为路障
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int slope_flag = 0;
float Gyro_Pitch_Angle = 0;

int cross_flag = 0;


void knn(void)
{                   	
	e_r1 = pow(65 - g_ValueOfAD[2], 2) + pow(65 - g_ValueOfAD[3], 2) 
			+ pow(100 - g_ValueOfAD[1], 2) + pow(20 - g_ValueOfAD[4], 2)
			+ pow(50 - g_ValueOfAD[5], 2) + pow(50 - g_ValueOfAD[0], 2);
			
	e_r2 = pow(100 - g_ValueOfAD[2], 2) + pow(100 - g_ValueOfAD[3], 2) 
			+ pow(100 - g_ValueOfAD[1], 2) + pow(100 - g_ValueOfAD[4], 2)
			+pow(30 - g_ValueOfAD[5], 2)+pow(30 - g_ValueOfAD[0], 2);
		
	if(e_r2<1000&&g_ValueOfAD[2]>=80&&g_ValueOfAD[3]>=80&&abs(g_ValueOfAD[5]-g_ValueOfAD[0])<=15)       //环岛识别
	{
		flag_r_hd = 1;
	}
	
     
	if(P26==0&&Hall!=1)     //霍尔识别
	{
		Hall=1;
	}	
	
	if(flag_r_hd==0 && g_ValueOfAD[5]>90 && g_ValueOfAD[0]>90
		&& (g_ValueOfAD[4]+g_ValueOfAD[1])>90 && abs(v_angle)<=30 )     //十字识别
	{		
		cross_flag = 1;
	}
	
	if(obstacle_flag==0 && obstacle_number<obstacle_number_MAX && (dl1a_distance_mm<=850 && dl1a_distance_mm>=300
		&& g_ValueOfAD[2]>=40 && g_ValueOfAD[3]>=40  && abs(v_angle)<=12))      //障碍识别
	{
		obstacle_flag = 1;
	}
	
//    else if(round_number == round_number_MAX)
//    {   
//        ruku_encoder_round_after_flag = 1;
//    }
}

void Round_Deal()
{   
    if(round_number>=round_number_MAX) //环岛最大数量
	{
        flag_r_hd = 0;
	}
    
	else if(flag_r_hd == 1 && round_number == 0)
	{
		if (round1_type == -1)
		{
			Huan_Dao_Z(400);
		}
		else if (round1_type == 1)
		{
			Huan_Dao_R(450);
		}
	}
		
	else if(flag_r_hd == 1 && round_number == 1)
	{
		if (round2_type == -1)
		{
			Huan_Dao_Z(400);
		}
		else if (round2_type == 1)
		{
			Huan_Dao_R(450);
		}
	}
	
	else if(flag_r_hd == 1 && round_number == 2)
	{
		if (round2_type == -1)
		{
			Huan_Dao_Z(400);
		}
		else if (round2_type == 1)
		{
			Huan_Dao_R(450);
		}
	}	
	
    else if(flag_r_hd == 1 && round_number == 3)
	{
		if (round2_type == -1)
		{
			Huan_Dao_Z(400);
		}
		else if (round2_type == 1)
		{
			Huan_Dao_R(450);
		}
	}	
	
}

void Huan_Dao_Z(int round_into_waiting_distance)
{
	
	Target_speed1 = round_speed - cha_err1*0.12; 
	Target_speed2 = round_speed + cha_err1*0.12;
  
	roundcount =(ctimer_count_read(CTIM0_P34)+ctimer_count_read(CTIM3_P04))*0.1;
	roundcount2 = roundcount2 + roundcount;
	if(roundcount2<=round_into_waiting_distance && roundcount2>=0) //小圆小大圆大 半径50cm
	{
		cha_err1 = 0.2*g_fDirectionError[2] * g_dirControl_P + (g_fDirectionError[2] - last_err1) * g_dirControl_D*0.4;
		last_err1 = g_fDirectionError[2];
	}
	else if(roundcount2>round_into_waiting_distance)//&&roundcount2<=25000&&flag_c_hd==0)
	{
		mpu660_angle();	

		if(abs(angle)<=60)
		{
			BEEP = 1;
			cha_err1 = -70;
		}
		
		else if(g_ValueOfAD[3]==0 && g_ValueOfAD[2] == 0)
		{
			Target_speed1 = 0;
			Target_speed2 = 0;
		}
		
		else if(abs(angle)<=270&&abs(angle)>50)
		{
			Ordinary_trace();
		}
		
		else if(abs(angle)<=315&&abs(angle)>280)
		{
			//BEEP = 1;
			cha_err1 = -50;
			//roundcount3 = roundcount2;
		}
		
		else if(abs(angle)<=350&&abs(angle)>325)
		{
			Ordinary_trace();
		}
		
		else 
		{
			//Ordinary_trace();
			//if(roundcount2 > roundcount3+1000)
			//{				
				//BEEP = 0;
				angle = 0;
				roundcount2=0;
				roundcount3=0;
				round_number++;
				flag_r_hd = 0;
			//}
		}
			
	}
}

void Huan_Dao_R(int round_into_waiting_distance)
{   

	Target_speed1 = round_speed - cha_err1*0.12; 
	Target_speed2 = round_speed + cha_err1*0.12;
	
	roundcount =(ctimer_count_read(CTIM0_P34)+ctimer_count_read(CTIM3_P04))*0.1;
	roundcount2 = roundcount2 + roundcount;
	if(roundcount2<=round_into_waiting_distance && roundcount2>=0)	//半径60cm
	{
		cha_err1 = 0.2*g_fDirectionError[2] * g_dirControl_P + (g_fDirectionError[2] - last_err1) * g_dirControl_D*0.4;
		last_err1 = g_fDirectionError[2];
	}
	else if(roundcount2>round_into_waiting_distance)//&&roundcount2<=25000&&flag_c_hd==0
	{
		mpu660_angle() ;	

		if(abs(angle)<=55)
		{
			BEEP = 1;
			cha_err1 = +64;
		}
		
		else if(g_ValueOfAD[3]==0 && g_ValueOfAD[2] == 0)
		{
			Target_speed1 = 0;
			Target_speed2 = 0;
		}
		
		else if(abs(angle)<=280&&abs(angle)>55)
		{
			Ordinary_trace();
		}
		else if(abs(angle)<=325&&abs(angle)>280)
		{
			//BEEP = 1;
			cha_err1 = +50;
			//roundcount3 = roundcount2;
		}
		
		else if(abs(angle)<=350&&abs(angle)>325)
		{
			Ordinary_trace();
		
		}
		
		else 
		{
			//Ordinary_trace();
			//if(roundcount2 > roundcount3+1000)
			//{				
				//BEEP = 0;
            angle = 0;
            roundcount2=0;
            roundcount3=0;
            round_number++;
            flag_r_hd = 0;

			//}
		}

	}
}

void Slope() //坡道
{
	if(obstacle_flag == 1 && slope_flag == 0)
	{
		slope_flag = 1;
	}
	switch (slope_flag)
	{
		case 1:	//上坡预备 
//				Target_speed1 = 80 -abs(v_angle)*0.155- cha_err1*0.24;
//				Target_speed2 = 80 -abs(v_angle)*0.155+ cha_err1*0.24;
			Ordinary_trace();
			
			IMU660ra_Angle_Y();
			Gyro_Pitch_Angle = angle_y;
			if(Gyro_Pitch_Angle>=10)
			{
//						obstacle_number++;
//						obstacle_flag = 0;
					slope_flag = 2;		
			}
			break;
			
		case 2:	//坡后半段
//				Target_speed1 = 60 -abs(v_angle)*0.155- cha_err1*0.24;
//				Target_speed2 = 60 -abs(v_angle)*0.155+ cha_err1*0.24;
			Ordinary_trace();
			
			roundcount =(ctimer_count_read(CTIM0_P34)+ctimer_count_read(CTIM3_P04))*0.1;
			roundcount2 = roundcount2 + roundcount;
			
			if(roundcount2>3000) //出坡
			{
					slope_flag = 0;
					roundcount2 = 0;
					obstacle_number++;
					obstacle_flag = 0;	
					BEEP = 0;
			}
			break;
	}
}



void Obstacle_Deal()
{   
    if(obstacle_number>=obstacle_number_MAX)
	{
	  obstacle_flag = 0;
	}
    
	else if(obstacle_flag == 1 && obstacle_number == 0)
	{
		if (obstacle1_type == -1)
		{
			Slope();
		}
		else if (obstacle1_type == 1)
		{
			Obstacle();
		}
	}
		
	else if(obstacle_flag == 1 && obstacle_number == 1)
	{
		if (obstacle2_type == -1)
		{
			Slope();
		}
		else if (obstacle2_type == 1)
		{
			Obstacle();
		}
	}
	
	else if(obstacle_flag == 1 && obstacle_number == 2)
	{
		if (obstacle3_type == -1)
		{
			Slope();
		}
		else if (obstacle3_type == 1)
		{
			Obstacle();
		}
	}
    
}


void Obstacle()
{
	roundcount =(ctimer_count_read(CTIM0_P34)+ctimer_count_read(CTIM3_P04))*0.1;
	roundcount2 = roundcount2 + roundcount;
	
	switch(obstacle_flag)
	{
		case 1: //避让驶出
                BEEP = 1;
				Target_speed1 = 50 - cha_err1*0.2; 
				Target_speed2 = 50 + cha_err1*0.2;
				cha_err1 = 70;
				mpu660_angle();	
				if(roundcount2>3000 || abs(angle)>50)	
				{   
                    BEEP = 0;
					roundcount3 = roundcount2;
					angle = 0;
					obstacle_flag = 2;
				}
				break;
                
		case 2:	//完毕驶回
				Target_speed1 = 100 - cha_err1*0.12; 
				Target_speed2 = 100 + cha_err1*0.12;
				cha_err1 = -60;
				mpu660_angle();	
				if( (roundcount2>=roundcount3+1000 && g_ValueOfAD[0]+g_ValueOfAD[5]>=30) ||  abs(angle)>90 )
				{
					BEEP = 1;
					obstacle_number++;
					angle = 0;
					roundcount2 = 0;
					roundcount3 = 0;
					obstacle_flag = 0;					
					//obstacle_flag = 3;	//调试用
				}
				break;
                
		case 3:	//调试用
				Target_speed1 = 0; 
				Target_speed2 = 0;
				
				break;
	}
				
}



void Cross()
{		
	roundcount =(ctimer_count_read(CTIM0_P34)+ctimer_count_read(CTIM3_P04))*0.1;
	roundcount2 = roundcount2 + roundcount;
	if(roundcount2<=1000)
	{   
		BEEP = 1;
		cha_err1 = (1.1*g_fDirectionError[0] * g_dirControl_P + (g_fDirectionError[0] - last_err1) * g_dirControl_D*1.4)+v_angle*0.15; //
		last_err1 =g_fDirectionError[0];
		Target_speed1 = 155- abs(v_angle)*0.1-abs(y_v_angle)*0.5- cha_err1*0.1;
		Target_speed2 =  155 - abs(v_angle)*0.1-abs(y_v_angle)*0.5+ cha_err1*0.1;
	}
	else
	{
		roundcount2 = 0;
		cross_flag = 0;
	}
}

