#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "stm32f1xx.h"

#define ENCODER1_TIM htim2
#define ENCODER2_TIM htim4
#define ENCODER3_TIM htim5
#define ENCODER4_TIM htim8
#define GAP_TIM     htim7
#define GAP1_TIM     htim6

#define PWM_TIM     htim3


#define MOTOR_SPEED_RERATIO 1000    
#define PULSE_PRE_ROUND 11  //maichong
#define RADIUS_OF_TYRE 34  //lunzibanjin
#define LINE_SPEED_C RADIUS_OF_TYRE * RADIUS_OF_TYRE * 3.14;
#define RELOADVALUE1 __HAL_TIM_GetAutoreload(&ENCODER1_TIM)    
#define COUNTERNUM1 __HAL_TIM_GetCounter(&ENCODER1_TIM)      
#define RELOADVALUE2 __HAL_TIM_GetAutoreload(&ENCODER2_TIM)    
#define COUNTERNUM2 __HAL_TIM_GetCounter(&ENCODER2_TIM)       
#define RELOADVALUE3 __HAL_TIM_GetAutoreload(&ENCODER3_TIM)    
#define COUNTERNUM3 __HAL_TIM_GetCounter(&ENCODER3_TIM)       
#define RELOADVALUE4 __HAL_TIM_GetAutoreload(&ENCODER3_TIM)    
#define COUNTERNUM4 __HAL_TIM_GetCounter(&ENCODER3_TIM)       



extern float Speed1 ;
extern float Speed2 ;
extern float Speed3 ;
extern float Speed4 ;
extern float MotorSpeed1;
extern float MotorSpeed2;
extern float MotorSpeed3;
extern float MotorSpeed4;
typedef struct _Motor
{
    int32_t lastCount;   
    int32_t totalCount;  
    int16_t overflowNum; 
    float speed;         
    uint8_t direct;  
	  float MotorSpeed;
}Motor;
void Motor_Init(void);
void MotorControll(int spd1,int spd2,int spd3,int spd4);

#endif
