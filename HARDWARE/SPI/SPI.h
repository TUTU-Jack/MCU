#ifndef _SPI_H_
#define _SPI_H_
/***********************************************Include*****************************************/
#include "pt32f0xx_conf.h"


/***********************************************Define******************************************/
#define M_SPI_MOSI_PORT		CMSDK_PB
#define M_SPI_MOSI_PIN		GPIO_PinSource5

#define M_SPI_MISO_PORT		CMSDK_PB
#define M_SPI_MISO_PIN		GPIO_PinSource4

#define M_SPI_CLK_PORT		CMSDK_PB
#define M_SPI_CLK_PIN		GPIO_PinSource3

#define M_SPI_SS_PORT		CMSDK_PA
#define M_SPI_SS_PIN		GPIO_PinSource15


/**********************************************Varible*******************************************/


/***********************************************Fuction*****************************************/
void InitSPI();
#endif