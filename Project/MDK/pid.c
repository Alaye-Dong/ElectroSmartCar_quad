#include "pid.h"
#include "headfile.h"

float last_err1 = 0, last_err2 = 0;
float Target_speed1 = 0, Target_speed2 = 0;
float cha_err1 = 0, cha_err2 = 0;

float g_dirControl_P = 1.925;         //直道控制P 0.8
float g_dirControl_D = 0.285;	        //直道控制D	2.4
float Motor_Kp_L = 2.0, Motor_Ki_L = 2.21; //55 5.7
float Motor_Kp_R = 2.79, Motor_Ki_R = 2.10; //37 0.3
float angle_kp1 = 0.425;

int error2 = 0, error_pre2 = 0;
int error1 = 0, error_pre = 0;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!
int normal_speed = 150, round_speed = 150;  // 普通速度，环岛速度
float v_angle_P = 0.13, y_v_angle_P = 0.25;    //  慢速150 0.13 0.3 快速165 0.18 0.25
//!!!!!!!!!!!!!!!!!!!!!!!!!!!

float v_angle = 0;
float angle = 0;//积分角度
float now_x = 0,gr = 0;

float y_v_angle = 0;
float angle_y = 0;
float now_y = 0,gr_y = 0;

void dir_pid()      //转向环位置式
{

    cha_err2 = g_fDirectionError[0] * 2.1 + (g_fDirectionError[0] - last_err2) * 1; //
    last_err2 = g_fDirectionError[0];
    if(g_ValueOfAD[2]<=0&&g_ValueOfAD[3]<=0)//停车
    {
        Target_speed1 = 0;//speed - price_PWM; //1.5
        Target_speed2 = 0;//speed + price_PWM; //0.8

    }
    else
    {
        angle = 0;
        Ordinary_trace();
    }  
}

void Target_speed()
{ 	
    //慢速150 0.13 0.3 快速165 0.18 0.25
    Target_speed1 = normal_speed - abs(v_angle)*v_angle_P -abs(y_v_angle)*y_v_angle_P  - cha_err1*0.2;	
    Target_speed2 = normal_speed - abs(v_angle)*v_angle_P -abs(y_v_angle)*y_v_angle_P  + cha_err1*0.2;
    
    BEEP = 0;	
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

void mpu660_PID() //角速度，角度计算
{
    float v_angle_array[5],temp;
    int i,j;
    imu660ra_get_gyro();
    
    for(i = 0; i < 5 - 1; i++)
    {
            v_angle_array[i] = imu660ra_gyro_transition(imu660ra_gyro_z);
    }
    
    for(i = 0; i < 5 - 1; i++)
    {
        for(j = 0; j < 5 - 1 - i; j++)
        {
            if(v_angle_array[j] > v_angle_array[j + 1])
                {
                    temp = v_angle_array[j];
                    v_angle_array[j] = v_angle_array[j + 1];
                    v_angle_array[j + 1] = temp;
                }
        }		
    }
    
    v_angle=(float)(v_angle_array[1]+v_angle_array[2]+v_angle_array[3])/3;
        
    
    if(abs(g_ValueOfAD[2]-g_ValueOfAD[2])<=15&&g_ValueOfAD[2]>=45&&g_ValueOfAD[2]>=45)
    {
        angle_kp1 = 0.12;
    }
    else
    {
        angle_kp1 = 0.03;
    }

}

void IMU660ra_Angle_Y_V_Filter()	//Y轴角速度角度获取滤波
{
    float y_v_angle_array[5],temp;
    int i,j;
    imu660ra_get_gyro();

    for(i = 0; i < 5 - 1; i++)
    {
            y_v_angle_array[i] = imu660ra_gyro_transition(imu660ra_gyro_y);
    }

    for(i = 0; i < 5 - 1; i++)
    {
        for(j = 0; j < 5 - 1 - i; j++)
        {
            if(y_v_angle_array[j] > y_v_angle_array[j + 1])
                {
                    temp = y_v_angle_array[j];
                    y_v_angle_array[j] = y_v_angle_array[j + 1];
                    y_v_angle_array[j + 1] = temp;
                }
        }		
    }

    y_v_angle=(float)(y_v_angle_array[1]+y_v_angle_array[2]+y_v_angle_array[3])/3;
}

void mpu660_angle() 
{
    mpu660_PID();
    gr = v_angle;
    now_x = gr; //根据设置换算
    angle += (now_x) * 0.005; //积分：角速度*积分时间10ms
}

void IMU660ra_Angle_Y()
{
	IMU660ra_Angle_Y_V_Filter();
    gr_y = y_v_angle;
    now_y = gr_y; //根据设置换算
    angle_y += (now_y) * 0.005; //积分：角速度*积分时间10ms
}

void Ordinary_trace()  //普通循迹
{ 
		mpu660_PID();
		IMU660ra_Angle_Y_V_Filter();

		if(g_ValueOfAD[2]<=15&&(g_ValueOfAD[2]<g_ValueOfAD[3]))
		{
			//BEEP = 1;
			cha_err1 = -73;
			Target_speed();
		}
		else if(g_ValueOfAD[3]<=15&&g_ValueOfAD[2]!=0&&(g_ValueOfAD[3]<g_ValueOfAD[2]))
		{   
				//BEEP = 1;
				cha_err1 = 74;
				Target_speed();
		}
		else
		{
				BEEP = 0;
				cha_err1 = (g_fDirectionError[2] * g_dirControl_P + (g_fDirectionError[2] - last_err1) * g_dirControl_D)+v_angle*angle_kp1;
				last_err1 = g_fDirectionError[2];
				Target_speed();
		}
}
