#include "key.h"


void Key_Init()
{
	//GPIO �ж�����(�½����жϴ�����
	GPIO_TriTypeConfig(Key_PORT, Key_PIN,GPIOTI_Trigger_Falling);
	//���ⲿ���������������ڲ�����
	
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = PA_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00;
	NVIC_Init(&NVIC_InitStruct);
	
	//�ж�ʹ��
	GPIO_ITConfig(CMSDK_PA, GPIO_IT_ITE11, ENABLE);
}