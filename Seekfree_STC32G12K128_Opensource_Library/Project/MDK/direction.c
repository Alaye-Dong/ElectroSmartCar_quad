#include "headfile.h"
#include "direction.h"
#include "math.h"


int zhidaoflag = 0;


//ֱ������50 ��б35 �м�70

/**********ȫ�ֱ�������********/

float g_fDirectionError[5];	     //����ƫ�g_fDirectionError[0]Ϊһ��ˮƽ��еĲ�Ⱥ�ƫ�
float g_fDirectionError_dot[3];  //����ƫ��΢�֣�g_fDirectionError_dot[0]Ϊһ��ˮƽ��еĲ�Ⱥ�ƫ��΢�֣�

int16 g_ValueOfAD[9] = {0};       //��ȡ�ĵ��ֵ
int16 g_ValueOfADFilter[5] = {0};




/******************************************************************/

void Read_ADC(void)
{
    int16  i, j, k, temp;
    int16  ad_valu[9][5], ad_valu1[9], ad_sum[9];
    int16  ValueOfADOld[9], ValueOfADNew[9];

//*******************************���ֵ�˲�����*******************************//
    for(i = 0; i < 5; i++)
    {
			 ad_valu[0][i] = adc_once(ADC_P11, ADC_12BIT);   //zui you
        ad_valu[1][i] = adc_once(ADC_P05, ADC_12BIT);   //zhong jian
        ad_valu[2][i] = adc_once(ADC_P00, ADC_12BIT);  	 //��
        ad_valu[3][i] = adc_once(ADC_P13, ADC_12BIT);   //��
        ad_valu[4][i] = adc_once(ADC_P06, ADC_12BIT);   //zui zuo
 		    ad_valu[5][i] = adc_once(ADC_P01, ADC_12BIT);// 05     /
//        ad_valu[0][i] = adc_once(ADC_P00, ADC_12BIT);   //zui you
//        ad_valu[1][i] = adc_once(ADC_P01, ADC_12BIT);   //zhong jian
//        ad_valu[2][i] = adc_once(ADC_P13, ADC_12BIT);  	 //you    xie
//        ad_valu[3][i] = adc_once(ADC_P06, ADC_12BIT);   //zui zuo
//        ad_valu[4][i] = adc_once(ADC_P11, ADC_12BIT);   //zui zuo
// 		    ad_valu[5][i] = adc_once(ADC_P05, ADC_12BIT);// 05     //zuo   xie
//			   ad_valu[5][i]=adc_once(ADC_P13,ADC_12BIT);      //zuo   shu
//			   ad_valu[6][i]=adc_once(ADC_P14,ADC_12BIT);      //zuo   heng
//			   ad_valu[7][i]=adc_once(ADC_P15,ADC_12BIT);      //�ڶ��ź�
//         ad_valu[8][i]=adc_once(ADC_P02,ADC_12BIT);			  //
    }


    /*=========================ð����������==========================*///�������ֵ����Сֵ
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 5; j++)
        {
            for(k = 0; k < 5 - j; k++)
            {
                if(ad_valu[i][k] > ad_valu[i][k + 1])      //ǰ��ıȺ���Ĵ�  ����н���
                {
                    temp = ad_valu[i][k + 1];
                    ad_valu[i][k + 1] = ad_valu[i][k];
                    ad_valu[i][k] = temp;
                }
            }
        }
    }

    /*===========================��ֵ�˲�=================================*/
    for(i = 0; i < 9; i++) //���м�����ĺ�
    {
        ad_sum[i] = ad_valu[i][1] + ad_valu[i][2] + ad_valu[i][3];
        ad_valu1[i] = ad_sum[i] / 3;
    }


    for(i = 0; i < 9; i++)      //����ֵ�и�λ������
    {
        g_ValueOfAD[i] = (int16)(ad_valu1[i] / 10 * 10);

        //�ɼ��ݶ�ƽ����ÿ�βɼ����仯40
        ValueOfADOld[i] = g_ValueOfADFilter[i];
        ValueOfADNew[i] = g_ValueOfAD[i];

        if(ValueOfADNew[i] >= ValueOfADOld[i])
            g_ValueOfADFilter[i] = ((ValueOfADNew[i] - ValueOfADOld[i]) > 50 ? (ValueOfADOld[i] + 50) : ValueOfADNew[i]);
        else
            g_ValueOfADFilter[i] = ((ValueOfADNew[i] - ValueOfADOld[i]) < -60 ? (ValueOfADOld[i] - 60) : ValueOfADNew[i]);
    }

}


unsigned int data diangan[9];
short leftP = 0, leftV = 0, rightV = 0, rightP = 0, leftS = 0, rightS = 0, middle = 0, second_leftp = 0, second_rightp = 0;
void InductorNormal(void)
{
    Read_ADC();
    diangan[0]=g_ValueOfAD[0];    	
    diangan[1]=g_ValueOfAD[1];			
    diangan[2]=g_ValueOfAD[2]; 		
    diangan[3]=g_ValueOfAD[3];
    diangan[4]=g_ValueOfAD[4];
    diangan[5]=g_ValueOfAD[5];	
//	  diangan[6]=g_ValueOfAD[6];	
//	  diangan[7]=g_ValueOfAD[7];
//    diangan[8]=g_ValueOfAD[8];	
		rightS = (float)(diangan[5] - 1.0) / (1640.0 - 10.0) * 100.0;	
		leftP =  (float)(diangan[0] - 1.0) / (1730.0 - 10.0) * 100.0;		// ��й�һ��
				
		leftV = (float)(diangan[2] - 1.0) / (2150.0 - 10.0) * 100.0;		// ��й�һ��!!!2500
		rightV = (float)(diangan[3] - 1.0) / (2400.0 - 10.0) * 100.0;		// ��й�һ��	����Խ��Խ���� ��ֵ��С 2400 3150
		
    leftS = (float)(diangan[4] - 1.0) / (2280.0 - 10.0) * 100.0; //xie (3200 OK)
		rightP =  (float)(diangan[1] - 1.0) / (2280.0 - 10.0) * 100.0;		// ��й�һ��xie(3200 OK)

		
	  (g_ValueOfAD[0]) = (leftP < 0) ? 0 : leftP;           //��һ���������������
		(g_ValueOfAD[0]) = (leftP > 100) ? 100 : leftP;				//��һ���������������
		(g_ValueOfAD[2]) = (rightV < 0) ? 0 : rightV;					//��һ���������������
		(g_ValueOfAD[2]) = (rightV > 100) ? 100 : rightV;			//��һ���������������
	  (g_ValueOfAD[3]) = (leftV < 0) ? 0 : leftV;						//��һ���������������
		(g_ValueOfAD[3]) = (leftV > 100) ? 100 : leftV;				//��һ���������������
		(g_ValueOfAD[1]) = (rightP < 0) ? 0 : rightP;					//��һ���������������
		(g_ValueOfAD[1]) = (rightP > 100) ? 100 : rightP;			//��һ���������������		
    (g_ValueOfAD[4]) = (leftS < 0) ? 0 : leftS;
	  (g_ValueOfAD[4]) = (leftS > 100) ? 100 : leftS;
		(g_ValueOfAD[5]) = (rightS < 0) ? 0 : rightS;
	  (g_ValueOfAD[5]) = (rightS > 100) ? 100 : rightS;
//		(g_ValueOfAD[6]) = (middle < 0) ? 0 : middle;
//	  (g_ValueOfAD[6]) = (middle > 100) ? 100 : middle;
//		(g_ValueOfAD[7]) = (second_leftp < 0) ? 0 : second_leftp;
//	  (g_ValueOfAD[7]) = (second_leftp > 100) ? 100 : second_leftp;
//		(g_ValueOfAD[8]) = (second_rightp < 0) ? 0 : second_rightp;
//	  (g_ValueOfAD[8]) = (second_rightp > 100) ? 100 : second_rightp;
}


/************************************************************************
 * file *		            �������
 *		һ������£�����ˮƽ��еĲ�Ⱥ���Ϊƫ��
 *             �ڻ���ʱ�У�������ֱ��еĲ�Ⱥ���Ϊƫ��
 *
 *		        ���ֵ��Ӧ����
 *
 *   g_ValueOfAD[0]��1500		          g_ValueOfAD[1]��1500
 *      (ˮƽ����)		                    ��ˮƽ�ҵ�У�
 *          g_ValueOfAD[2]��3400	    g_ValueOfAD[3]��3400
 *	       ����ֱ���У�	              ����ֱ�ҵ�У�
 * date *		     2020
 *************************************************************************/

void DirectionControl(void)
{

    static float g_fDirectionErrorTemp[2][5];
    InductorNormal();
    g_fDirectionError[0] = (float)(sqrt(g_ValueOfAD[2]) - sqrt(g_ValueOfAD[3])) * 100 / (sqrt(g_ValueOfAD[3]) + sqrt(g_ValueOfAD[2])); //ˮƽ��еĲ�Ⱥ���Ϊƫ��Ϊƫ��
    g_fDirectionError[1] = (float)(sqrt(g_ValueOfAD[5]) - sqrt(g_ValueOfAD[0])) * 100 / (sqrt(g_ValueOfAD[5]) + sqrt(g_ValueOfAD[0]));
    g_fDirectionError[2] = (float)(0.8*(sqrt(g_ValueOfAD[2]) - sqrt(g_ValueOfAD[3]))+
			                            0.4*(sqrt(g_ValueOfAD[4]) - sqrt(g_ValueOfAD[1]))) * 100 / 
			                                                  (0.8*(sqrt(g_ValueOfAD[3]) + sqrt(g_ValueOfAD[2]))+0.4*abs(sqrt(g_ValueOfAD[4]) - sqrt(g_ValueOfAD[1])));
		g_fDirectionError[3] = (float)(g_ValueOfAD[5] - g_ValueOfAD[0]);
																												
    g_fDirectionErrorTemp[0][4] = g_fDirectionErrorTemp[0][3];
    g_fDirectionErrorTemp[0][3] = g_fDirectionErrorTemp[0][2];
    g_fDirectionErrorTemp[0][2] = g_fDirectionErrorTemp[0][1];
    g_fDirectionErrorTemp[0][1] = g_fDirectionErrorTemp[0][0];
    g_fDirectionErrorTemp[0][0] = g_fDirectionError[0];
    g_fDirectionError_dot[0] = 5 * (g_fDirectionErrorTemp[0][0] - g_fDirectionErrorTemp[0][3]); //ˮƽ��е�ƫ��΢��
		

}