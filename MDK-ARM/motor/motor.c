#include <stdio.h>
#include "main.h"
#include "usart.h"
#include "tim.h"
#include "gpio.h"
#include "motor.h"
#include "callback.h"

tPid pidMotor1Speed;
tPid pidMotor2Speed;
tPid pidMotor3Speed;
tPid pidMotor4Speed;

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
	PID_init();
}

void MotorSet(float Spd1,float Spd2,float Spd3,float Spd4){
	pidMotor1Speed.target_val=Spd1;
	pidMotor2Speed.target_val=Spd2;
	pidMotor3Speed.target_val=Spd3;
	pidMotor4Speed.target_val=Spd4;
}

void MotorControll(float Spd1,float Spd2,float Spd3,float Spd4){
 		if(Spd1>5.0){
			 HAL_GPIO_WritePin(GPIOC, AI1_Pin, GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOC, AI2_Pin, GPIO_PIN_RESET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_1,myabs(Spd1));
		}
		else if (Spd1 <-5.0){
			 HAL_GPIO_WritePin(GPIOC, AI1_Pin, GPIO_PIN_RESET);
			 HAL_GPIO_WritePin(GPIOC, AI2_Pin, GPIO_PIN_SET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_1,myabs(Spd1));
		}
		else {
			 HAL_GPIO_WritePin(GPIOC, AI1_Pin, GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOC, AI2_Pin, GPIO_PIN_SET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_1,0);
		}
		
		
	 	if(Spd2>5.0){
			 HAL_GPIO_WritePin(GPIOC, BI1_Pin, GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOC, BI2_Pin, GPIO_PIN_RESET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_2,myabs(Spd2));
		}
		else if (Spd2 <-5.0){
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
		else if (Spd3 <-5.0){
			 HAL_GPIO_WritePin(GPIOC, CI1_Pin, GPIO_PIN_RESET);
			 HAL_GPIO_WritePin(GPIOC, CI2_Pin, GPIO_PIN_SET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_3,myabs(Spd3));
		}
		else {
			 HAL_GPIO_WritePin(GPIOC, CI1_Pin, GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOC, CI2_Pin, GPIO_PIN_SET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_3,0);
		}
		
		
		if(Spd4>5.0){
			 HAL_GPIO_WritePin(GPIOC, DI1_Pin, GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOC, DI2_Pin, GPIO_PIN_RESET);
			 __HAL_TIM_SetCompare(&PWM_TIM,TIM_CHANNEL_4,myabs(Spd4));
		}
		else if (Spd4 <-5.0){
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

void PID_init()
{
	pidMotor1Speed.actual_val=0.0;
	pidMotor1Speed.target_val=0.00;
	pidMotor1Speed.err=0.0;
	pidMotor1Speed.err_last=0.0;
	pidMotor1Speed.err_sum=0.0;
	pidMotor1Speed.Kp=0;
	pidMotor1Speed.Ki=0;
	pidMotor1Speed.Kd=0;
	
	pidMotor2Speed.actual_val=0.0;
	pidMotor2Speed.target_val=0.00;
	pidMotor2Speed.err=0.0;
	pidMotor2Speed.err_last=0.0;
	pidMotor2Speed.err_sum=0.0;
	pidMotor2Speed.Kp=0;
	pidMotor2Speed.Ki=0;
	pidMotor2Speed.Kd=0;

	pidMotor3Speed.actual_val=0.0;
	pidMotor3Speed.target_val=0.00;
	pidMotor3Speed.err=0.0;
	pidMotor3Speed.err_last=0.0;
	pidMotor3Speed.err_sum=0.0;
	pidMotor3Speed.Kp=0;
	pidMotor3Speed.Ki=0;
	pidMotor3Speed.Kd=0;

	pidMotor4Speed.actual_val=0.0;
	pidMotor4Speed.target_val=0.00;
	pidMotor4Speed.err=0.0;
	pidMotor4Speed.err_last=0.0;
	pidMotor4Speed.err_sum=0.0;
	pidMotor4Speed.Kp=0;
	pidMotor4Speed.Ki=0;
	pidMotor4Speed.Kd=0;
}

float P_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;//传递真实值
	pid->err = pid->target_val - pid->actual_val;//当前误差=目标值-真实值
	//比例控制调节   输出=Kp*当前误差
	pid->actual_val = pid->Kp*pid->err;
	return pid->actual_val;
}
//比例P 积分I 控制函数
float PI_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;//传递真实值
	pid->err = pid->target_val - pid->actual_val;//当前误差=目标值-真实值
	pid->err_sum += pid->err;//误差累计值 = 当前误差累计和
	//使用PI控制 输出=Kp*当前误差+Ki*误差累计值
	pid->actual_val = pid->Kp*pid->err + pid->Ki*pid->err_sum;
	
	return pid->actual_val;
}
// PID控制函数
float PID_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;//传递真实值
	pid->err = pid->target_val - pid->actual_val; //当前误差=目标值-真实值
	pid->err_sum += pid->err;//误差累计值 = 当前误差累计和
	//使用PID控制 输出 = Kp*当前误差  +  Ki*误差累计值 + Kd*(当前误差-上次误差)
	pid->actual_val = pid->Kp*pid->err + pid->Ki*pid->err_sum + pid->Kd*(pid->err - pid->err_last);
	//保存上次误差: 这次误差赋值给上次误差
	pid->err_last = pid->err;
	
	return pid->actual_val;
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
			  TimerCount++;
				if(TimerCount %5 == 0)//?10ms????
				{
					int32_t Count1 = (short)__HAL_TIM_GET_COUNTER(&ENCODER1_TIM);
					int32_t Count2 = (short)__HAL_TIM_GET_COUNTER(&ENCODER2_TIM);
					int32_t Count3 = (short)__HAL_TIM_GET_COUNTER(&ENCODER3_TIM);
					int32_t Count4 = (short)__HAL_TIM_GET_COUNTER(&ENCODER4_TIM);
					__HAL_TIM_SET_COUNTER(&ENCODER1_TIM,0);
					__HAL_TIM_SET_COUNTER(&ENCODER2_TIM,0);
					__HAL_TIM_SET_COUNTER(&ENCODER3_TIM,0);
					__HAL_TIM_SET_COUNTER(&ENCODER4_TIM,0);
					float speed1 = (float)Count1/9.6/11/4;
					float speed2 = (float)Count2/9.6/11/4;
					float speed3 = (float)Count3/9.6/11/4;
					float speed4 = (float)Count4/9.6/11/4;
					Speed1 = speed1;
					Speed2 = speed2;
					Speed3 = speed3;
					Speed4 = speed4;
					TimerCount=0;
				}

				if(TimerCount %10 ==0)//每20ms一次
				{
				MotorControll(PID_realize(&pidMotor1Speed,Speed1),PID_realize(&pidMotor2Speed,Speed2),
							PID_realize(&pidMotor3Speed,Speed3),PID_realize(&pidMotor4Speed,Speed4));
		    	TimerCount=0;
				}
	


    }
	if(htim->Instance==GAP1_TIM.Instance)//???????,????????
		{
		TIME6_STA=1;
		}
}

