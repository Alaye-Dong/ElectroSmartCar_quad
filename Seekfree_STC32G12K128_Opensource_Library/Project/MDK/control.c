#include "headfile.h"
#include "control.h"

int duty1 = 0, duty2 = 0;
uint8 Ring_state = 0;



 


void Control(void)
{
if(duty1>0)
		{
		 pwm_duty(PWM1, duty1);
		DIR1 = 1;
		}
		else
		{
		pwm_duty(PWM1, duty1*-1);
		DIR1 = 0;
		}
		
		if(duty2>0)
		{
		 pwm_duty(PWM2, duty2);
		DIR2 = 0;
		}
		else
		{
		pwm_duty(PWM2, duty2*-1);
		DIR2 = 1;
		}
		
		
		

	}
