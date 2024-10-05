#ifndef __CALLBACK_H
#define __CALLBACK_H
#define USART2_REC_LEN 256  	//??????????????? 128
#include "stm32f1xx_hal.h"

 #define RXBUFFERSIZE  256

extern volatile uint16_t USART2_RX_STA; 
extern volatile uint16_t USART3_RX_STA; 
extern volatile uint16_t USART5_RX_STA; 

extern uint8_t USART2Byte;
extern uint8_t USART3Byte;
extern uint8_t USART5Byte;

extern uint8_t  USART2_RX_BUF[USART2_REC_LEN];

extern char Buff[255];//????
extern uint8_t Data;	//????
extern int Cnt;	//??
extern float yaw_angle;
extern volatile uint8_t TIME7_STA;
extern volatile uint8_t TIME6_STA;
int Xianfu(int value,int Amplitude);
int myabs(int a);   //È¡¾ø¶ÔÖµ

int Position_PID (int position,int target);
int Incremental_PI (int Encoder,int Target);
#endif


