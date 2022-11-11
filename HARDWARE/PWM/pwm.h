#ifndef _PWM_H_
#define _PWM_H_
/***********************************************Include*****************************************/
#include "pt32f0xx_conf.h"


/***********************************************Define******************************************/
#define PWM_PORT	CMSDK_PB
#define PWM_PIN		GPIO_PinSource4

#define PWM_TIM_PSC		(240 - 1)
#define PWM__TIM_PERIOD	(10000 - 1)
#define PWM_Cycle		(5000 - 1)

/***********************************************Fuction*****************************************/
void PWM_Init();
void PWM_Display();

#endif