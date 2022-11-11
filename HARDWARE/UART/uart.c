#include "uart.h"


unsigned int nUART_Trans_Buff_LEN = 0;
char UART_Trans_Buff[256];
unsigned char pUART_Head = 0;
unsigned char pUART_Tail = 1;


void Uart_Init()
{
	//引脚复用为UART
	GPIO_PinAFConfig(UART_TX_PORT,UART_TX_PIN,GPIO_AF_3);
	GPIO_PinAFConfig(UART_RX_PORT,UART_RX_PIN,GPIO_AF_3);
	
	//UART功能配置
	UART_InitTypeDef  UART_InitStruct;
	
	UART_InitStruct.UART_BaudRate = 19200;
	UART_InitStruct.UART_WordLength = UARTM_8D;
	UART_InitStruct.UART_StopBit = UART1StopBit;
	UART_InitStruct.UART_Parity = UART_ODD_PARITY;
	UART_InitStruct.UART_RXEN = ENABLE;
	UART_InitStruct.UART_SampleRate = UART_SAMPLERATEX16;
	
	UART_Init(UART0, &UART_InitStruct);
	
	//UART中断配置
	/*
	NVIC_InitTypeDef  NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = UART0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
	*/
	
	//UART使能
	UART_Cmd(UART0, ENABLE);
	
	//UART中断使能
	//UART_ITConfig(UART0, UART_IT_RXNEIE, ENABLE);
}