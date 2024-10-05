#include <stdio.h>
#include "main.h"
#include "usart.h"
#include "tim.h"
#include "gpio.h"
#include "motor.h"
#include "callback.h"

Motor motor1;
Motor motor2;
Motor motor3;
Motor motor4;
int TimerCount = 0;
float Speed1;
float Speed2;
float Speed3;
float Speed4;
float MotorSpeed1;
float MotorSpeed2;
float MotorSpeed3;
float MotorSpeed4;
void Motor_Init(void)
{
      HAL_TIM_Encoder_Start(&ENCODER1_TIM, TIM_CHANNEL_ALL);      //????????
    __HAL_TIM_ENABLE_IT(&ENCODER1_TIM,TIM_IT_UPDATE);           //????????????,?????
	    HAL_TIM_Encoder_Start(&ENCODER2_TIM, TIM_CHANNEL_ALL);      //????????
    __HAL_TIM_ENABLE_IT(&ENCODER2_TIM,TIM_IT_UPDATE);           //????????????,?????
	    HAL_TIM_Encoder_Start(&ENCODER3_TIM, TIM_CHANNEL_ALL);      //????????
    __HAL_TIM_ENABLE_IT(&ENCODER3_TIM,TIM_IT_UPDATE);           //????????????,?????
	    HAL_TIM_Encoder_Start(&ENCODER4_TIM, TIM_CHANNEL_ALL);      //????????
    __HAL_TIM_ENABLE_IT(&ENCODER4_TIM,TIM_IT_UPDATE);           //????????????,?????
    HAL_TIM_Base_Start_IT(&GAP_TIM);                       //??100ms?????
    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_1);            //??PWM
    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_2);            //??PWM
	  HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_3);            //??PWM
    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_4);            //??PWM
    __HAL_TIM_SET_COUNTER(&ENCODER1_TIM, 10000);                //????????????10000
	  __HAL_TIM_SET_COUNTER(&ENCODER2_TIM, 10000);                //????????????10000
    __HAL_TIM_SET_COUNTER(&ENCODER3_TIM, 10000);                //????????????10000
    __HAL_TIM_SET_COUNTER(&ENCODER4_TIM, 10000);                //????????????10000



    motor1.lastCount = 0;                                   //????????
    motor1.totalCount = 0;
    motor1.overflowNum = 0;                                  
    motor1.speed = 0;
    motor1.direct = 0;
		motor1.MotorSpeed=0;
		
		motor2.lastCount = 0;                                   //????????
    motor2.totalCount = 0;
    motor2.overflowNum = 0;                                  
    motor2.speed = 0;
    motor2.direct = 0;
		motor2.MotorSpeed=0;


		motor3.lastCount = 0;                                   //????????
    motor3.totalCount = 0;
    motor3.overflowNum = 0;                                  
    motor3.speed = 0;
    motor3.direct = 0;
		motor3.MotorSpeed=0;

		
		motor4.lastCount = 0;                                   //????????
    motor4.totalCount = 0;
    motor4.overflowNum = 0;                                  
    motor4.speed = 0;
    motor4.direct = 0;
		motor4.MotorSpeed=0;

}
void MotorControll(int Spd1,int Spd2,int Spd3,int Spd4){
 		if(Spd1>5){
			 HAL_GPIO_WritePin(GPIOC, AI1_Pin, GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOC, AI2_Pin, GPIO_PIN_RESET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_1,myabs(Spd1));
		}
		else if (Spd1 <-5){
			 HAL_GPIO_WritePin(GPIOC, AI1_Pin, GPIO_PIN_RESET);
			 HAL_GPIO_WritePin(GPIOC, AI2_Pin, GPIO_PIN_SET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_1,myabs(Spd1));
		}
		else {
			 HAL_GPIO_WritePin(GPIOC, AI1_Pin, GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOC, AI2_Pin, GPIO_PIN_SET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_1,0);
		}
		
		
	 if(Spd2>5){
			 HAL_GPIO_WritePin(GPIOC, BI1_Pin, GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOC, BI2_Pin, GPIO_PIN_RESET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_2,myabs(Spd2));
		}
		else if (Spd2 <-5){
			 HAL_GPIO_WritePin(GPIOC, BI1_Pin, GPIO_PIN_RESET);
			 HAL_GPIO_WritePin(GPIOC, BI2_Pin, GPIO_PIN_SET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_2,myabs(Spd2));
		}
		else {
			 HAL_GPIO_WritePin(GPIOC, BI1_Pin, GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOC, BI2_Pin, GPIO_PIN_SET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_2,0);
		}
		
		
	 if(Spd3>5){
			 HAL_GPIO_WritePin(GPIOC, CI1_Pin, GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOC, CI2_Pin, GPIO_PIN_RESET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_3,myabs(Spd3));
		}
		else if (Spd3 <-5){
			 HAL_GPIO_WritePin(GPIOC, CI1_Pin, GPIO_PIN_RESET);
			 HAL_GPIO_WritePin(GPIOC, CI2_Pin, GPIO_PIN_SET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_3,myabs(Spd3));
		}
		else {
			 HAL_GPIO_WritePin(GPIOC, CI1_Pin, GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOC, CI2_Pin, GPIO_PIN_SET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_3,0);
		}
		
		
		if(Spd4>5){
			 HAL_GPIO_WritePin(GPIOC, DI1_Pin, GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOC, DI2_Pin, GPIO_PIN_RESET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_4,myabs(Spd4));
		}
		else if (Spd4 <-5){
			 HAL_GPIO_WritePin(GPIOC, DI1_Pin, GPIO_PIN_RESET);
			 HAL_GPIO_WritePin(GPIOC, DI2_Pin, GPIO_PIN_SET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_4,myabs(Spd4));
		}
		else {
			 HAL_GPIO_WritePin(GPIOC, DI1_Pin, GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOC, DI2_Pin, GPIO_PIN_SET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_4,0);
		}		
		
		
}

int Xianfu(int value,int Amplitude)
{	
	int temp;
	if(value>Amplitude) temp = Amplitude;
	else if(value<-Amplitude) temp = -Amplitude;
	else temp = value;
	return temp;
			
}

int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//???????,??????
{
    if(htim->Instance==GAP_TIM.Instance)//???????,????????
    {		TIME7_STA=1;
        motor1.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER1_TIM);//??????(??),????0,??????1
        motor1.totalCount = COUNTERNUM1 + motor1.overflowNum * RELOADVALUE1;//?????????????????????????
        motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 10;//???????
        //motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 10 * LINE_SPEED_C//?????????????
        motor1.lastCount = motor1.totalCount; //?????????
			  Speed1= motor1.speed;
			  TimerCount++;
				if(TimerCount %5 == 0)//?10ms????
				{
					motor1.totalCount = (short)__HAL_TIM_GET_COUNTER(&ENCODER1_TIM);
					motor2.totalCount = (short)__HAL_TIM_GET_COUNTER(&ENCODER2_TIM);
					motor3.totalCount = (short)__HAL_TIM_GET_COUNTER(&ENCODER3_TIM);
					motor4.totalCount = (short)__HAL_TIM_GET_COUNTER(&ENCODER4_TIM);
					__HAL_TIM_SET_COUNTER(&ENCODER1_TIM,0);
					__HAL_TIM_SET_COUNTER(&ENCODER2_TIM,0);
					__HAL_TIM_SET_COUNTER(&ENCODER3_TIM,0);
					__HAL_TIM_SET_COUNTER(&ENCODER4_TIM,0);
					motor1.speed = (float)motor1.totalCount/9.6/11/4;
					motor2.speed = (float)motor2.totalCount/9.6/11/4;
					motor3.speed = (float)motor3.totalCount/9.6/11/4;
					motor4.speed = (float)motor4.totalCount/9.6/11/4;
					Speed1 = motor1.speed;
					Speed2 = motor2.speed;
					Speed3 = motor3.speed;
					Speed4 = motor4.speed;

					TimerCount=0;
				}		
    }
		if(htim->Instance==GAP1_TIM.Instance)//???????,????????
		{
		TIME6_STA=1;
		}
}

