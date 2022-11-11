#ifndef _UART_H_
#define _UART_H_
/***********************************************Include*****************************************/
#include "pt32f0xx_conf.h"


/***********************************************Define******************************************/
#define UART_RX_PORT	CMSDK_PA
#define UART_TX_PORT	CMSDK_PB

#define UART_RX_PIN		GPIO_PinSource15
#define UART_TX_PIN		GPIO_PinSource6


/***********************************************Fuction*****************************************/
void Uart_Init();

#endif