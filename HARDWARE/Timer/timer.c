#include "timer.h"




void Timer_Init()
{
	/*定时器功能配置*/
	TIM_TimeBaseInitTypeDef TimeBaseInit;
	
	//定时器时钟源为系统时钟 24MHZ
	//定时器预分频系数
	TimeBaseInit.Prescaler		= TIM_PSC;
	//定时器计数模式
	TimeBaseInit.CounterMode 	= TIM_CNT_MODE_UP;
	//定时器时钟频率
	TimeBaseInit.MatchValue 	= TIM_PERIOD;
	//定时器计数值清零
	TimeBaseInit.OVRSTEN		= ENABLE;
	
	TIM_TimeBaseInit(TIM3, &TimeBaseInit);
	
	//定时器使能
	TIM_Cmd(TIM3, ENABLE);
	
	
	
	/*定时器中断配置*/
	NVIC_InitTypeDef NVIC_InitStruct;
	
	//中断源
	NVIC_InitStruct.NVIC_IRQChannel = TIMER3_IRQn;
	//中断优先级
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00;
	//中断源使能
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
	
	//定时器中断使能
	TIM_ITConfig(TIM3, TIM_INT_MR0, ENABLE);
	
}


