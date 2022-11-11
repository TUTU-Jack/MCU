#include "capture.h"



void Capture_Init()
{
	//GPIO����Ϊ���벶��ģʽ
	GPIO_PinAFConfig(Capture_PORT,Capture_PIN,GPIO_AF_1);
	
	
	/*���벶��ģʽ��������*/
	
	/*ʱ��*/
	
	PWM_TimeBaseInitTypeDef	PWM_TimeBaseInit;
	
	PWM_TimeBaseInit.ClockSel			= PCLK;
	PWM_TimeBaseInit.Prescaler			= Capture_TIM_PSC;
	
	PWM_TimeBaseInit.CounterMode		= PWM_CNT_MODE_UP;
	PWM_TimeBaseInit.CounterDirRv_EN	= PWM_CounterDirRv_DIS;
	
	PWM_TimeBaseInit.CounterReload		= Capture_TIM_PERIOD;
	
	PMW_TimeBaseInit(PWM1, &PWM_TimeBaseInit);

	//ʱ���ж�����
	
	/*ʹ��TIMER1��NVIC������*/
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIMER1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x01;
	NVIC_Init(&NVIC_InitStruct);
	
	/*ʹ�ܶ�ʱ��TC�����ؼĴ���MR0ƥ��ʱ�������ж�*/	
	PWM_IntConfig(PWM1, PWM_INT_MR0, ENABLE);
	
	
	//����ģʽ
	/*TIMER1ͨ��4���������ز����ܴ�*/
	PWM_RE_CaptureConfig(PWM1, PWM_CH_4, ENABLE);
	/*TIMER1ͨ��4�����ز����ж�ʹ��*/
	PWM_IntConfig(PWM1, PWM_INT_CAP4, ENABLE);
	
	//��ʱ��ʹ��(�ڴ������У��ɰ��������жϿ�ʼ����
	//PWM_Cmd(PWM1,ENABLE);
	
}


