#include "headfile.h"
#include "direction.h"
#include "math.h"


int zhidaoflag = 0;


//直道两横50 两斜35 中间70

/**********全局变量定义********/

float g_fDirectionError[5];	     //方向偏差（g_fDirectionError[0]为一对水平电感的差比和偏差）
float g_fDirectionError_dot[3];  //方向偏差微分（g_fDirectionError_dot[0]为一对水平电感的差比和偏差微分）

int16 g_ValueOfAD[9] = {0};       //获取的电感值
int16 g_ValueOfADFilter[5] = {0};




/******************************************************************/

void Read_ADC(void)
{
    int16  i, j, k, temp;
    int16  ad_valu[9][5], ad_valu1[9], ad_sum[9];
    int16  ValueOfADOld[9], ValueOfADNew[9];

//*******************************电感值滤波处理*******************************//
    for(i = 0; i < 5; i++)
    {
			 ad_valu[0][i] = adc_once(ADC_P11, ADC_12BIT);   //zui you
        ad_valu[1][i] = adc_once(ADC_P05, ADC_12BIT);   //zhong jian
        ad_valu[2][i] = adc_once(ADC_P00, ADC_12BIT);  	 //横
        ad_valu[3][i] = adc_once(ADC_P13, ADC_12BIT);   //横
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
//			   ad_valu[7][i]=adc_once(ADC_P15,ADC_12BIT);      //第二排横
//         ad_valu[8][i]=adc_once(ADC_P02,ADC_12BIT);			  //
    }


    /*=========================冒泡排序升序==========================*///舍弃最大值和最小值
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 5; j++)
        {
            for(k = 0; k < 5 - j; k++)
            {
                if(ad_valu[i][k] > ad_valu[i][k + 1])      //前面的比后面的大  则进行交换
                {
                    temp = ad_valu[i][k + 1];
                    ad_valu[i][k + 1] = ad_valu[i][k];
                    ad_valu[i][k] = temp;
                }
            }
        }
    }

    /*===========================中值滤波=================================*/
    for(i = 0; i < 9; i++) //求中间三项的和
    {
        ad_sum[i] = ad_valu[i][1] + ad_valu[i][2] + ad_valu[i][3];
        ad_valu1[i] = ad_sum[i] / 3;
    }


    for(i = 0; i < 9; i++)      //将数值中个位数除掉
    {
        g_ValueOfAD[i] = (int16)(ad_valu1[i] / 10 * 10);

        //采集梯度平滑，每次采集最大变化40
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
		leftP =  (float)(diangan[0] - 1.0) / (1730.0 - 10.0) * 100.0;		// 电感归一化
				
		leftV = (float)(diangan[2] - 1.0) / (2150.0 - 10.0) * 100.0;		// 电感归一化!!!2500
		rightV = (float)(diangan[3] - 1.0) / (2400.0 - 10.0) * 100.0;		// 电感归一化	除数越大越往左 右值变小 2400 3150
		
    leftS = (float)(diangan[4] - 1.0) / (2280.0 - 10.0) * 100.0; //xie (3200 OK)
		rightP =  (float)(diangan[1] - 1.0) / (2280.0 - 10.0) * 100.0;		// 电感归一化xie(3200 OK)

		
	  (g_ValueOfAD[0]) = (leftP < 0) ? 0 : leftP;           //归一化后限制输出幅度
		(g_ValueOfAD[0]) = (leftP > 100) ? 100 : leftP;				//归一化后限制输出幅度
		(g_ValueOfAD[2]) = (rightV < 0) ? 0 : rightV;					//归一化后限制输出幅度
		(g_ValueOfAD[2]) = (rightV > 100) ? 100 : rightV;			//归一化后限制输出幅度
	  (g_ValueOfAD[3]) = (leftV < 0) ? 0 : leftV;						//归一化后限制输出幅度
		(g_ValueOfAD[3]) = (leftV > 100) ? 100 : leftV;				//归一化后限制输出幅度
		(g_ValueOfAD[1]) = (rightP < 0) ? 0 : rightP;					//归一化后限制输出幅度
		(g_ValueOfAD[1]) = (rightP > 100) ? 100 : rightP;			//归一化后限制输出幅度		
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
 * file *		            方向控制
 *		一般情况下：用两水平电感的差比和作为偏差
 *             在环岛时中：用量垂直电感的差比和作为偏差
 *
 *		        电感值对应变量
 *
 *   g_ValueOfAD[0]：1500		          g_ValueOfAD[1]：1500
 *      (水平左电感)		                    （水平右电感）
 *          g_ValueOfAD[2]：3400	    g_ValueOfAD[3]：3400
 *	       （垂直左电感）	              （垂直右电感）
 * date *		     2020
 *************************************************************************/

void DirectionControl(void)
{

    static float g_fDirectionErrorTemp[2][5];
    InductorNormal();
    g_fDirectionError[0] = (float)(sqrt(g_ValueOfAD[2]) - sqrt(g_ValueOfAD[3])) * 100 / (sqrt(g_ValueOfAD[3]) + sqrt(g_ValueOfAD[2])); //水平电感的差比和作为偏差为偏差
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
    g_fDirectionError_dot[0] = 5 * (g_fDirectionErrorTemp[0][0] - g_fDirectionErrorTemp[0][3]); //水平电感的偏差微分
		

}