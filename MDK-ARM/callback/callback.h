#ifndef __CALLBACK_H
#define __CALLBACK_H
#define USART2_REC_LEN 256  	//??????????????? 128
#include "stm32f1xx_hal.h"

 #define RXBUFFERSIZE  256

extern uint16_t USART2_RX_STA; 
extern uint8_t USART2Byte;
extern uint8_t  USART2_RX_BUF[USART2_REC_LEN];

extern uint8_t  USART2Byte;
extern char Buff[255];//????
extern uint8_t Data;	//????
extern int Cnt;	//??
extern float yaw_angle;
#endif


