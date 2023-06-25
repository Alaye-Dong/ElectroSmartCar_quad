#include "pid.h"
#include "headfile.h"

int last_err1, last_err2 = 0;
int speed;
float Target_speed1, Target_speed2;
float cha_err1, cha_err2;
float g_dirControl_P = 1.925;         //直道控制P 0.8
float g_dirControl_D = 0.245;	        //直道控制D	2.4
float Motor_Kp_L = 2.0, Motor_Ki_L = 2.21; //55 5.7
float Motor_Kp_R = 2.79, Motor_Ki_R = 2.10; //37 0.3
float angle_kp1 = 0.425;
float price_PWM;
float v_angle;
int error2, error_pre2;
int error1,error_pre;
float ZX_kp = 0.10; //0.1
float ZX_kd = 0.00;
void dir_pid()      //转向环位置式
{

    cha_err2 = g_fDirectionError[0] * 2.1 + (g_fDirectionError[0] - last_err2) * 1; //
  	last_err2 = g_fDirectionError[0];
	if(g_ValueOfAD[2]<=0&&g_ValueOfAD[3]<=0)
	{
	  Target_speed1 = 0;//speed - price_PWM; //1.5
    Target_speed2 = 0;//speed + price_PWM; //0.8

	
	}
	else
	{
	if(g_ValueOfAD[5]>75&&g_ValueOfAD[0]>75)
	{
	cha_err1 = cha_err2;
	Target_speed1 = 130 - cha_err1*0.01;
    Target_speed2 = 130 + cha_err1*0.01;
	
	}
else
{
 if(g_ValueOfAD[2]<=25&&(g_ValueOfAD[2]<g_ValueOfAD[3]))
{
  cha_err1 = -71;
 Target_speed1 = 115 - cha_err1*0.15;
    Target_speed2 = 115 + cha_err1*0.15;
}
else if(g_ValueOfAD[3]<=25&&g_ValueOfAD[2]!=0&&(g_ValueOfAD[3]<g_ValueOfAD[1]))
{
  cha_err1 = 73;
 Target_speed1 = 115 - cha_err1*0.15;
    Target_speed2 = 115 + cha_err1*0.15;
}
else
{
	if(zhidaoflag>=90)
	{
	  Target_speed1 = 140 - cha_err1*0.15;
    Target_speed2 = 140 + cha_err1*0.15;
		cha_err1 = (0.20*g_fDirectionError[2] * g_dirControl_P + (g_fDirectionError[2] - last_err1) * g_dirControl_D*1.25);
	  last_err1 = g_fDirectionError[2]; 
	}
	else
	{
	cha_err1 = (g_fDirectionError[2] * g_dirControl_P + (g_fDirectionError[2] - last_err1) * g_dirControl_D);
	last_err1 = g_fDirectionError[2];
	Target_speed1 = 115 - cha_err1*0.15;
    Target_speed2 = 115 + cha_err1*0.15;
	}
}
 }  
}


	}
void Target_speed()
{
    
    
  
}





void speedL_pid()  //左轮速度内环pid
{  
	
	 error2=(int)(Target_speed2-speed2);	
	 duty2=duty2+(error2-error_pre2)*Motor_Kp_L+error2*Motor_Ki_L;
   error_pre2=error2;	 
	if(duty2>=8000) duty2=8000;//限幅
  else if(duty2<=-3500) duty2=-3500;
	
}

void speedR_pid()  //右轮速度内环pid
{ 
	 
	 error1=(int)(Target_speed1-speed1);
	 duty1=duty1+(error1-error_pre)*Motor_Kp_R+error1*Motor_Ki_R;
   error_pre=error1;	 
	if(duty1>=7000) duty1=7000;//限幅
  else if(duty1<=-3500) duty1=-3500;
	
	
}

void mpu660_PID()
{
     imu660ra_get_gyro();
    v_angle = imu660ra_gyro_transition(imu660ra_gyro_z);

}

