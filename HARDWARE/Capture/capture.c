#include "capture.h"



void Capture_Init()
{
	//GPIO复用为输入捕获模式
	GPIO_PinAFConfig(Capture_PORT,Capture_PIN,GPIO_AF_1);
	
	
	/*输入捕获模式功能配置*/
	
	/*时基*/
	
	PWM_TimeBaseInitTypeDef	PWM_TimeBaseInit;
	
	PWM_TimeBaseInit.ClockSel			= PCLK;
	PWM_TimeBaseInit.Prescaler			= Capture_TIM_PSC;
	
	PWM_TimeBaseInit.CounterMode		= PWM_CNT_MODE_UP;
	PWM_TimeBaseInit.CounterDirRv_EN	= PWM_CounterDirRv_DIS;
	
	PWM_TimeBaseInit.CounterReload		= Capture_TIM_PERIOD;
	
	PMW_TimeBaseInit(PWM1, &PWM_TimeBaseInit);

	//时基中断配置
	
	/*使能TIMER1的NVIC控制器*/
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIMER1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x01;
	NVIC_Init(&NVIC_InitStruct);
	
	/*使能定时器TC和重载寄存器MR0匹配时产生的中断*/	
	PWM_IntConfig(PWM1, PWM_INT_MR0, ENABLE);
	
	
	//捕获模式
	/*TIMER1通道4脉冲上升沿捕获功能打开*/
	PWM_RE_CaptureConfig(PWM1, PWM_CH_4, ENABLE);
	/*TIMER1通道4脉冲沿捕获中断使能*/
	PWM_IntConfig(PWM1, PWM_INT_CAP4, ENABLE);
	
	//定时器使能(在此例程中，由按键触发中断开始捕获）
	//PWM_Cmd(PWM1,ENABLE);
	
}


