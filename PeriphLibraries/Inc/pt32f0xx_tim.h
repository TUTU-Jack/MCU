/**
  ******************************************************************************
  * @file    pt32f0xx_tim.h
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
#ifndef __PT32F0XX_TIM_H
#define __PT32F0XX_TIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "pt32f0xx.h"

/** @addtogroup PT32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup PWM
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

   
   
/** 
  * @brief  PWM Init Structure definition  
  */ 



/** @defgroup PWM_Count Mode 
  * @{
  */ 
#define TIM_CNT_MODE_UP                ((uint32_t)0x00000000) 
#define TIM_CNT_MODE_DOWN              ((uint32_t)0x00000008) 


#define TIM_INT_MR0                    TIM_MCR_MR0I

#define TIM_FLAG_MR0                   TIM_ISR_OV


#define IS_TIM_ALL_PERIPH(PERIPH)            (((PERIPH) == TIM2) || ((PERIPH) == TIM3) || \
                                              ((PERIPH) == TIM4))
																			
#define IS_TIM_COUNTER_MATCH(VALUE)          ((VALUE) <= 0xFFFF)
				
#define IS_TIM_COUNTER_VALUE(COUNTERVALUE)   ((COUNTERVALUE) <= 0xFFFF)

#define IS_TIM_PRESCALER(PRESCALER)          ((PRESCALER) <= 0xFF)

#define IS_TIM_COUNTERMODE(COUNTERMODE)      (((COUNTERMODE) == TIM_CNT_MODE_UP) || \
                                              ((COUNTERMODE) == TIM_CNT_MODE_DOWN))     

#define IS_TIM_INT(TIM_INT)                  ((TIM_INT)  == TIM_INT_MR0) 

#define IS_TIM_FLAG(TIM_FLAG)                ((TIM_FLAG) == TIM_FLAG_MR0)
	
/**
 * @brief Definition of PWM timebase init structure.
 */

 
typedef struct
{ 
  uint16_t           MatchValue;            /*!< Period (Value for MR0 register)             */
  uint8_t            Prescaler;             /*!< Prescaler (Value for PR register)           */
  uint8_t            CounterMode;           /*!< Counter mode up-counting or down-counting   */
	FunctionalState    OVRSTEN;               /*!< Match Rest Count   */
} TIM_TimeBaseInitTypeDef;




/* Exported functions --------------------------------------------------------------------------------------*/

/** @defgroup PWM_Exported_Functions PWM exported functions
  * @{
  */

void TIM_TimeBaseInit(CMSDK_TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TimeBaseInit);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TimeBaseInit);
void TIM_PrescalerConfig(CMSDK_TIM_TypeDef* TIMx, uint8_t Prescaler);
void TIM_SetCounterMatch(CMSDK_TIM_TypeDef* TIMx, uint16_t Reload);
void TIM_SetCounter(CMSDK_TIM_TypeDef* TIMx, uint16_t Counter);
uint16_t TIM_GetCounter(CMSDK_TIM_TypeDef* TIMx);
uint16_t TIM_GetPrescaler(CMSDK_TIM_TypeDef* TIMx);
uint16_t TIM_GetPrescalerCnt(CMSDK_TIM_TypeDef* TIMx);
void TIM_CounterModeConfig(CMSDK_TIM_TypeDef* TIMx, uint8_t CounterMode);
void TIM_UpdateCmd(CMSDK_TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_Cmd(CMSDK_TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_ITConfig(CMSDK_TIM_TypeDef* TIMx, uint32_t TIM_IT, FunctionalState NewState);
FlagStatus TIM_GetFlagStatus(CMSDK_TIM_TypeDef* TIMx, uint32_t TIM_FLAG);
void TIM_ClearFlag(CMSDK_TIM_TypeDef* TIMx, uint32_t TIM_FLAG);



#ifdef __cplusplus
}
#endif

#endif /* __PT32F0XX_PWM_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************(C) COPYRIGHT PENGPAI Microelectronics*****END OF FILE****/
