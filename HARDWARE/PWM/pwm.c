#include "pwm.h"

void Pwm_Init()
{
	//GPIO引脚复用为PWM
	GPIO_PinAFConfig(PWM_PORT,PWM_PIN,GPIO_AF_0);
	
	/*PWM功能配置*/
	//时基
	PWM_TimeBaseInitTypeDef  PWM_TimeBaseInit;
	
	PWM_TimeBaseInit.ClockSel			= PCLK;
	PWM_TimeBaseInit.Prescaler			= PWM_TIM_PSC;
	PWM_TimeBaseInit.CounterMode		= PWM_CNT_MODE_UP;
	PWM_TimeBaseInit.CounterDirRv_EN	= PWM_CounterDirRv_DIS;
	PWM_TimeBaseInit.CounterReload		= PWM__TIM_PERIOD;
	
	PMW_TimeBaseInit(PWM0,&PWM_TimeBaseInit);
	
	//PWM功能配置
	PWM_OutputInitTypeDef PWM_OutInit;
	/*!< PWM channel 1 */
	PWM_OutInit.Channel			= PWM_CH_1;
	/*!< PWM channel output low when tc <= compare value,output high when tc > compare value */
	PWM_OutInit.OutputMode		= COMPAER_MODE2;
	/* 配置互补输出使能*/
	PWM_OutInit.ControlN		= PWM_CHNCTL_DISABLE;
	/*!< PWM channel idle output low  */
	PWM_OutInit.IdleState		= PWM_IDLE_LOW;
	/*互补输出死区时间*/
	PWM_OutInit.DeathTime		= 0;
	/*配置PWM输出的占空比 P = (ADVANCE_TIM_PULSE+1) / (ADVANCE_TIM_PERIOD+1)*/
	PWM_OutInit.CompareValue	= PWM_Cycle;
	
	PWM_OutputInit(PWM0,&PWM_OutInit);
	
	/*定时器中断配置*/
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = TIMER0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00;
	
	NVIC_Init(&NVIC_InitStruct);
	
	//PWM中断使能
	PWM_IntConfig(PWM0,PWM_INT_MR0,ENABLE);
	
	//定时器使能
	PWM_Cmd(PWM0, ENABLE);
}