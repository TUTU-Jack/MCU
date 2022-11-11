#ifndef _LED_H_
#define _LED_H_
/***********************************************Include*****************************************/
#include "pt32f0xx_conf.h"


/***********************************************Define******************************************/
#define LED_R_PORT	CMSDK_PB
#define LED_G_PORT	CMSDK_PB
#define LED_B_PORT	CMSDK_PA

#define LED_R_PIN	GPIO_Pin_4
#define LED_G_PIN	GPIO_Pin_5
#define LED_B_PIN	GPIO_Pin_8

/***********************************************Fuction*****************************************/
void LED_Init();
void TaskDisplayLED_R();
void TaskDisplayLED_G();
void TaskDisplayLED_B();

#endif