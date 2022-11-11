/**
  ******************************************************************************
  * @file    pt32f0xx_beep.h
  * @author  Application Team
  * @version V1.1.0
  * @date    15-September-2020   
  * @brief   
  *          
  ******************************************************************************
  * @attention
  *
  * 
  *
  * 
  * 
  * 
  *
  *      
  *
  * 
  *
  * 
  * 
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PT32F0XX_BEEP_H
#define __PT32F0XX_BEEP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "pt32f0xx.h"

/** @addtogroup PT32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup BEEP
  * @{
  */

/* Exported types ------------------------------------------------------------*/



/* Exported constants --------------------------------------------------------*/

/** @defgroup BEEP_Exported_Constants
  * @{
  */
/** 
  * @brief  BEEP Init structure definition
  */
  
typedef struct
{
  uint32_t Prescaler;                        /*!<*/				
	uint32_t Subdivide;                        /*!<*/				
}Beep_InitTypeDef;


#define BEEP_SUBDIV_X2              ((uint32_t)0x00000080)
#define BEEP_SUBDIV_X4              ((uint32_t)0x00000040)
#define BEEP_SUBDIV_X8              ((uint32_t)0x00000000)


#define IS_BEEP_SUBDIV(SUBDIV)     ((SUBDIV == BEEP_SUBDIV_X2)   || \
                                    (SUBDIV == BEEP_SUBDIV_X4)   || \
                                    (SUBDIV == BEEP_SUBDIV_X8))

#define IS_BEEP_CPSR(CPSR)         (CPSR <= ((uint32_t)0x0000001F))

/** @addtogroup BEEP_Exported_Functions
  * @{
  */
void Beep_Init(Beep_InitTypeDef* Beep_InitStruct);
void Beep_Cmd(FunctionalState NewState);
void Beep_PrescalerConfig(uint8_t Prescaler);
void Beep_SubDivConfig(uint8_t Subdivide);

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* __PT32F0XX_ANA_H */

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */ 
	
/************************(C) COPYRIGHT PENGPAI Microelectronics*****END OF FILE****/

