#include "key.h"


void Key_Init()
{
	//GPIO 中断配置(下降沿中断触发）
	GPIO_TriTypeConfig(Key_PORT, Key_PIN,GPIOTI_Trigger_Falling);
	//有外部上拉，无需配置内部上拉
	
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = PA_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00;
	NVIC_Init(&NVIC_InitStruct);
	
	//中断使能
	GPIO_ITConfig(CMSDK_PA, GPIO_IT_ITE11, ENABLE);
}