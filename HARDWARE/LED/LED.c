/***********************************************Include*****************************************/
#include "LED.h"


/***********************************************Fuction*****************************************/
void LED_Init()
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*选择要控制的GPIO引脚*/
	GPIO_InitStructure.GPIO_Pin = LED_R_PIN;	

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_OType_PP;   

	/*调用库函数，初始化GPIO*/
	GPIO_Init(LED_R_PORT, &GPIO_InitStructure);	
	
	/*选择要控制的GPIO引脚*/
	GPIO_InitStructure.GPIO_Pin = LED_G_PIN;	

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_OType_PP;   

	/*调用库函数，初始化GPIO*/
	GPIO_Init(LED_G_PORT, &GPIO_InitStructure);	
	
	/*选择要控制的GPIO引脚*/
	GPIO_InitStructure.GPIO_Pin = LED_B_PIN;	

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_OType_PP;   

	/*调用库函数，初始化GPIO*/
	GPIO_Init(LED_B_PORT, &GPIO_InitStructure);	
	
	/*关闭LED_R*/
	GPIO_SetBits(LED_R_PORT,LED_R_PIN);
	
	/*关闭LED_G*/
	GPIO_SetBits(LED_G_PORT,LED_G_PIN);
		 
    /*关闭LED_B*/
	GPIO_SetBits(LED_B_PORT,LED_B_PIN);
	
}


void TaskDisplayLED_R()
{
	GPIO_ReverseBits(LED_R_PORT,LED_R_PIN);
	uint8_t string[] = "LED_R	";
	UART_StringSend(UART0,string);
}

void TaskDisplayLED_G()
{
	GPIO_ReverseBits(LED_G_PORT,LED_G_PIN);
	uint8_t string[] = "LED_G	";
	UART_StringSend(UART0,string);
}

void TaskDisplayLED_B()
{
	GPIO_ReverseBits(LED_B_PORT,LED_B_PIN);
	uint8_t string[] = "LED_B	";
	UART_StringSend(UART0,string);
}
