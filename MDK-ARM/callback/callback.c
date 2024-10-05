#include <stdio.h>
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "callback.h"
#include "tim.h"

uint8_t  USART2_RX_BUF[USART2_REC_LEN];
float yaw_angle;
uint8_t  USART2Byte;
uint8_t  USART3Byte;
uint8_t  USART5Byte;

char Buff[255];//????
uint8_t Data;	//????
int Cnt = 0;	//??

volatile uint8_t TIME7_STA=0;
volatile uint8_t TIME6_STA=0;
volatile uint16_t USART2_RX_STA=0; 
volatile uint16_t USART3_RX_STA=0; 
volatile uint16_t USART5_RX_STA=0; 

char RxBuffer[RXBUFFERSIZE]; 
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		if(Data == 0x58) 
		{				
			Cnt = 0;
		}		
		Buff[Cnt]=Data;		//??¼????????
		Cnt++;						//????????????1 
		
		if(Buff[0] == 0x58 && Buff[1] == 0x59&& Cnt>5)
			{
				printf("\ngetdata\n");
				HAL_UART_Transmit_IT(&huart1, (uint8_t *)Buff, Cnt);//???????
				//HAL_UART_Transmit_IT(&huart2, (uint8_t *)Buff, Cnt);//?????
				Cnt = 0;
			}
		HAL_UART_Receive_IT(&huart1, &Data, sizeof(Data));//??????
	}
	
	else if(huart == &huart2)
	{
		
		if(USART2Byte == 0x55) 
		{				
			USART2_RX_STA = 0;
		}				
		USART2_RX_BUF[USART2_RX_STA]=USART2Byte;		//??¼????????
		USART2_RX_STA++;						//????????????1 
		if(USART2_RX_STA>=11)//????????
		{
			if( USART2_RX_BUF[0]==0x55 && USART2_RX_BUF[1]==0x53 )//??????? ????
			{				
				//printf("startr");
			USART2_RX_STA=0x8000;
			uint16_t yawH = USART2_RX_BUF[7];
			uint16_t yawL = USART2_RX_BUF[6];
			uint16_t yaw = (yawH << 8) | yawL;
			yaw_angle = ((float)yaw / 32768.0) * 180.0;
			}
			else 
			{
				USART2_RX_STA = 0;
			}
		}
		HAL_UART_Receive_IT(&huart2,&USART2Byte,1);
	}
	else if (huart == &huart3){USART3_RX_STA=1;}
	else if (huart == &huart5){USART5_RX_STA=1;}
}


