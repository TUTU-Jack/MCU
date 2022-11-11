/***********************************************Include*****************************************/
#include "LED.h"


/***********************************************Fuction*****************************************/
void LED_Init()
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*ѡ��Ҫ���Ƶ�GPIO����*/
	GPIO_InitStructure.GPIO_Pin = LED_R_PIN;	

	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_OType_PP;   

	/*���ÿ⺯������ʼ��GPIO*/
	GPIO_Init(LED_R_PORT, &GPIO_InitStructure);	
	
	/*ѡ��Ҫ���Ƶ�GPIO����*/
	GPIO_InitStructure.GPIO_Pin = LED_G_PIN;	

	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_OType_PP;   

	/*���ÿ⺯������ʼ��GPIO*/
	GPIO_Init(LED_G_PORT, &GPIO_InitStructure);	
	
	/*ѡ��Ҫ���Ƶ�GPIO����*/
	GPIO_InitStructure.GPIO_Pin = LED_B_PIN;	

	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_OType_PP;   

	/*���ÿ⺯������ʼ��GPIO*/
	GPIO_Init(LED_B_PORT, &GPIO_InitStructure);	
	
	/*�ر�LED_R*/
	GPIO_SetBits(LED_R_PORT,LED_R_PIN);
	
	/*�ر�LED_G*/
	GPIO_SetBits(LED_G_PORT,LED_G_PIN);
		 
    /*�ر�LED_B*/
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
