#include "pwm.h"

void Pwm_Init()
{
	//GPIO���Ÿ���ΪPWM
	GPIO_PinAFConfig(PWM_PORT,PWM_PIN,GPIO_AF_0);
	
	/*PWM��������*/
	//ʱ��
	PWM_TimeBaseInitTypeDef  PWM_TimeBaseInit;
	
	PWM_TimeBaseInit.ClockSel			= PCLK;
	PWM_TimeBaseInit.Prescaler			= PWM_TIM_PSC;
	PWM_TimeBaseInit.CounterMode		= PWM_CNT_MODE_UP;
	PWM_TimeBaseInit.CounterDirRv_EN	= PWM_CounterDirRv_DIS;
	PWM_TimeBaseInit.CounterReload		= PWM__TIM_PERIOD;
	
	PMW_TimeBaseInit(PWM0,&PWM_TimeBaseInit);
	
	//PWM��������
	PWM_OutputInitTypeDef PWM_OutInit;
	/*!< PWM channel 1 */
	PWM_OutInit.Channel			= PWM_CH_1;
	/*!< PWM channel output low when tc <= compare value,output high when tc > compare value */
	PWM_OutInit.OutputMode		= COMPAER_MODE2;
	/* ���û������ʹ��*/
	PWM_OutInit.ControlN		= PWM_CHNCTL_DISABLE;
	/*!< PWM channel idle output low  */
	PWM_OutInit.IdleState		= PWM_IDLE_LOW;
	/*�����������ʱ��*/
	PWM_OutInit.DeathTime		= 0;
	/*����PWM�����ռ�ձ� P = (ADVANCE_TIM_PULSE+1) / (ADVANCE_TIM_PERIOD+1)*/
	PWM_OutInit.CompareValue	= PWM_Cycle;
	
	PWM_OutputInit(PWM0,&PWM_OutInit);
	
	/*��ʱ���ж�����*/
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = TIMER0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00;
	
	NVIC_Init(&NVIC_InitStruct);
	
	//PWM�ж�ʹ��
	PWM_IntConfig(PWM0,PWM_INT_MR0,ENABLE);
	
	//��ʱ��ʹ��
	PWM_Cmd(PWM0, ENABLE);
}