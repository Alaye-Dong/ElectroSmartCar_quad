#include "headfile.h"
#include "encoder.h"
int16 speed1;//��������ȡ����
int16 speed2;
float encoder_integral = 0;
float encoder = 0;
int16 count_flag = 0;
	
void read_encoder()
{
	if(DIRR == 1)//����
		{
			speed1 = ctimer_count_read(CTIM0_P34)*-1;
		}
		else
		{
			speed1 = ctimer_count_read(CTIM0_P34) ;
		}
		
		if(DIRL == 1)  //����ߵ�ƽ����ת
		{
			speed2 = ctimer_count_read(CTIM3_P04) ;
		}
		else        //����͵�ƽ����ת
		{
			speed2 = ctimer_count_read(CTIM3_P04)*-1 ;
			
		}
		ctimer_count_clean(CTIM0_P34);
	  ctimer_count_clean(CTIM3_P04);//�������
	
			
		
}
