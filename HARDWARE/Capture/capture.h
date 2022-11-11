#ifndef _CAPTURE_H_
#define _CAPTURE_H_
/***********************************************Include*****************************************/
#include "pt32f0xx_conf.h"


/***********************************************Define******************************************/
  
#define Capture_PORT	CMSDK_PA
#define Capture_PIN		GPIO_PinSource11

#define Capture_TIM_PSC			239
#define Capture_TIM_PERIOD		0xFFFF	


/***********************************************Fuction*****************************************/
void Capture_Init();

#endif