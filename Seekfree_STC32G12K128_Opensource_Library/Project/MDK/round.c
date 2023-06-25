#include "headfile.h"
#include "round.h"

int e_r1, e_r2;
int cd_time_1 = 0;
int flag_in_round = 0; //入环岛预测
int flag_out_round = 0; //出环岛标志位
int flag_hding1 = 0; //环岛内循迹标志位
int flag_hding2 = 0; //出环岛辅助标志位
int flag_hd_Z = 0; //左环岛
int flag_hd_R = 0; //右环岛
int roundcount = 0;
int roundcount2 = 0;
int CK_count=0;
int CK_count2=0;
int e_r2;
int XJ=0;
int HD = 0;
int flag_hd_Z_2;
int	count_OUT = 800;
int count_IN = 400;
int count_R = 150;
void knn(void)
{

    float mask[2][5] = {100, 100, 100, 70,
		                    	100		 
                        , 100, 6, 6, 100, 91
                       };//三叉
    e_r1 = pow(mask[0][0] - g_ValueOfAD[2], 2) + pow(mask[0][1] - g_ValueOfAD[3], 2) + pow(mask[0][2] - g_ValueOfAD[1], 2) + pow(mask[0][3] - g_ValueOfAD[4], 2);
		e_r2 = pow(100 - g_ValueOfAD[2], 2) + pow(100 - g_ValueOfAD[3], 2) + pow(100 - g_ValueOfAD[1], 2) + pow(100 - g_ValueOfAD[4], 2)+pow(8 - g_ValueOfAD[5], 2)+pow(8 - g_ValueOfAD[0], 2);
		
	 if(e_r1<=450&&flag_in_round==0&&g_ValueOfAD[2]>=75&&g_ValueOfAD[3]>=75&&g_ValueOfAD[1]>=80&&flag_hd_R==0)
	 {
	   flag_hd_R = 1;
	   flag_in_round = 1;
	   
	 }
	if(e_r2<1000&&g_ValueOfAD[2]>=75&&g_ValueOfAD[3]>=75&&flag_hd_Z==0&&flag_hd_R==2)	
	{
	   flag_hd_Z = 1;
	
	}		
								 
											 
  //  e_r2 = pow(mask[1][0] - all, 2) + pow(mask[1][1] - al, 2) + pow(mask[1][2] - mid, 2) + pow(mask[1][3] - ar, 2) + pow(mask[1][4] - arr, 2);
}

void RuKu()
{

     roundcount =(ctimer_count_read(CTIM0_P34)+ctimer_count_read(CTIM3_P04))*0.1;
	   roundcount2 = roundcount2 + roundcount;
	if(roundcount2>=0&&roundcount2<=1000)
	{
	
	
	 Target_speed1 = 120;
   Target_speed2 = 120;
	cha_err1 = 0;
	}
	else if(roundcount2<3800&&roundcount2>800)
	{
	
	Target_speed1 = -120;
   Target_speed2 = -120;
	
	cha_err1 = 70;
		
		}
	else if(roundcount2>=3800)
	{
	
	Target_speed1 = 0;
   Target_speed2 = 0;
	
	cha_err1 = 0;
		
		}
	


}
void Huan_Dao_Z()
{

	 Target_speed1 = 110;
   Target_speed2 = 110;
  if(flag_hd_Z==1)
	{
			roundcount =(ctimer_count_read(CTIM0_P34)+ctimer_count_read(CTIM3_P04))*0.1;
	   roundcount2 = roundcount2 + roundcount;
		if(roundcount2<=200&&roundcount2>=0)
		{
		   cha_err1 = 0.2*g_fDirectionError[2] * g_dirControl_P + (g_fDirectionError[2] - last_err1) * g_dirControl_D*0.4;
		    last_err1 = g_fDirectionError[2];
		
		}
		else if(roundcount2>200&&roundcount2<=2500)
		{
		 cha_err1 = -55;
		
		}
		else if(roundcount2>2500&&roundcount2<=6000)
		 
	 {
	 
	  cha_err1 = 2.5*g_fDirectionError[2] * g_dirControl_P + (g_fDirectionError[2] - last_err1) * g_dirControl_D*1;
		    last_err1 = g_fDirectionError[2];
	 
	 }
	  else if(roundcount2>6000)
	 {
	 flag_hd_Z = 2;
	 flag_in_round = 0;
	 roundcount2 = 0;

	 }
	 }

   


}
void Huan_Dao_R()
{
	 Target_speed1 = 110 - cha_err1*0.15;
   Target_speed2 = 110 + cha_err1*0.15;
   
	 if(flag_hd_R==1)
	 {
		 
	roundcount =(ctimer_count_read(CTIM0_P34)+ctimer_count_read(CTIM3_P04))*0.1;
	   roundcount2 = roundcount2 + roundcount;
		if(roundcount2<=1000&&roundcount2>=0)
		{
		 cha_err1 = 0.2*g_fDirectionError[2] * g_dirControl_P + (g_fDirectionError[2] - last_err1) * g_dirControl_D*0.4;
		    last_err1 = g_fDirectionError[2];
		
		}
		else if(roundcount2>1000&&roundcount2<=2500)
		{
		 cha_err1 = +53;
		
				}
		else if(roundcount2>2500&&roundcount2<=7000)
		{
		 cha_err1 = 2.3*g_fDirectionError[2] * g_dirControl_P + (g_fDirectionError[2] - last_err1) * g_dirControl_D*1;
		    last_err1 = g_fDirectionError[2];
		
		}
	 
	 else if(roundcount2>7000)
	 {
	 flag_hd_R = 2;
	 flag_in_round = 0;
	 roundcount2 = 0;
	 }
	 }
	
 }

 void obstacle()
{
	roundcount =(ctimer_count_read(CTIM0_P34)+ctimer_count_read(CTIM3_P04))*0.1;
	roundcount2 = roundcount2 + roundcount;
	
	if(roundcount2>=0&&roundcount2<=1000)
	{
		
		Target_speed1 =-30;
   Target_speed2 = -30;
}
	else if(roundcount2>1000&&roundcount2<=2500)
		
	{
	 Target_speed1 =50;
   Target_speed2 =50;
   cha_err1 = 56;
	}
	else if(roundcount2<6000&&roundcount2>2500)
		
	{
	 Target_speed1 =50;
   Target_speed2 =50;
  cha_err1 = -60;
		
	}
	else
	{
	HD = 0;
		roundcount2=0;
	}

}
void CHUKU()
{	
	if(CK_count2>=0&&CK_count2<=1000)
	{
  	cha_err1 = +60;
   Target_speed1 =100;
   Target_speed2 =100;
	}
	else
{
    XJ=1;


}
}