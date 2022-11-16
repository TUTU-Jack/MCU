#ifndef _ADC_H_
#define _ADC_H_
/***********************************************Include*****************************************/
#include "pt32f0xx_conf.h"


/***********************************************Define******************************************/
#define USHORT			unsigned char
#define M_Vcom_PORT		CMSDK_PA
#define M_Vcom_PIN		GPIO_Pin_0
#define M_Vcom_Channel	ADC_Channel_0

#define M_S0_PORT		CMSDK_PA
#define M_S0_PIN		GPIO_Pin_7


#define M_S1_PORT		CMSDK_PB
#define M_S1_PIN		GPIO_Pin_7

#define M_S2_PORT		CMSDK_PA
#define M_S2_PIN		GPIO_Pin_6

#define M_S3_PORT		CMSDK_PB
#define M_S3_PIN		GPIO_Pin_0


/**********************************************Varible*******************************************/


/***********************************************Fuction*****************************************/
void InitADC();
USHORT GetSampleValue(USHORT nSELECTID);

#endif