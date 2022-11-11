#include "timer.h"




void Timer_Init()
{
	/*��ʱ����������*/
	TIM_TimeBaseInitTypeDef TimeBaseInit;
	
	//��ʱ��ʱ��ԴΪϵͳʱ�� 24MHZ
	//��ʱ��Ԥ��Ƶϵ��
	TimeBaseInit.Prescaler		= TIM_PSC;
	//��ʱ������ģʽ
	TimeBaseInit.CounterMode 	= TIM_CNT_MODE_UP;
	//��ʱ��ʱ��Ƶ��
	TimeBaseInit.MatchValue 	= TIM_PERIOD;
	//��ʱ������ֵ����
	TimeBaseInit.OVRSTEN		= ENABLE;
	
	TIM_TimeBaseInit(TIM3, &TimeBaseInit);
	
	//��ʱ��ʹ��
	TIM_Cmd(TIM3, ENABLE);
	
	
	
	/*��ʱ���ж�����*/
	NVIC_InitTypeDef NVIC_InitStruct;
	
	//�ж�Դ
	NVIC_InitStruct.NVIC_IRQChannel = TIMER3_IRQn;
	//�ж����ȼ�
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00;
	//�ж�Դʹ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
	
	//��ʱ���ж�ʹ��
	TIM_ITConfig(TIM3, TIM_INT_MR0, ENABLE);
	
}


