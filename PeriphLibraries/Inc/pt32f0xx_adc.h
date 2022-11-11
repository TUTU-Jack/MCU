/**
  ******************************************************************************
  * @file    pt32f0xx_adc.h
  * @author  Application Team
  * @version V1.1.0
  * @date    15-September-2020   
  * @brief   This file contains all the functions prototypes for the ADC firmware 
  *          library
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
#ifndef __PT32F0XX_ADC_H
#define __PT32F0XX_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "pt32f0xx.h"

/** @addtogroup PT32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  ADC Init structure definition
  */
  
typedef struct
{

  FunctionalState ADC_ContinuousConvMode;   /*!< Specifies whether the conversion is performed in
                                                 Continuous or Single mode.
                                                 This parameter can be set to ENABLE or DISABLE. */
  uint32_t ADC_ExternalTrigConv;            /*!< Defines the external trigger used to start the analog
                                                 to digital conversion of regular channels. This parameter
                                                 can be a value of @ref ADC_external_trigger_sources_for_channels_conversion */			
	
	FunctionalState ADC_HighSpeedSampMode;     /*!<Specifies whether the conversion is performed in
                                                 High Speed or Low Speed Sampling mode.*/		
	
  uint32_t ADC_DataAlign;                   /*!< Specifies whether the ADC data alignment is left or right.
                                                 This parameter can be a value of @ref ADC_data_align */
}ADC_InitTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants
  * @{
  */ 
#define IS_ADC_ALL_PERIPH(PERIPH)                  ((PERIPH) == ADC)


  
/** @defgroup ADC_ClockDiv
  * @{
  */ 
#define ADC_ClockMode_SynClkDiv                0x00000000   /*!<  Synchronous clock mode no divided*/
#define ADC_ClockMode_SynClkDiv2               0x00000100   /*!<  Synchronous clock mode divided by 2 */
#define ADC_ClockMode_SynClkDiv4               0x00000200   /*!<  Synchronous clock mode divided by 4 */
#define ADC_ClockMode_SynClkDiv8               0x00000300   /*!<  Synchronous clock mode divided by 8 */
#define IS_ADC_CLOCKMODE(CLOCK) (((CLOCK) == ADC_ClockMode_SynClkDiv)  ||\
				                         ((CLOCK) == ADC_ClockMode_SynClkDiv2) ||\
				                         ((CLOCK) == ADC_ClockMode_SynClkDiv4) ||\
				                         ((CLOCK) == ADC_ClockMode_SynClkDiv8))

/**
  * @}
  */ 


/** @defgroup ADC_external_trigger_sources_for_channels_conversion
  * @{
  */ 

/* TIM0 */
#define ADC_ExternalTrigConv_Timer0               ((uint32_t)0x00000004)

/* TIM1 */
#define ADC_ExternalTrigConv_Timer1               ((uint32_t)0x00000014)

/* TIM2 */
#define ADC_ExternalTrigConv_Timer2               ((uint32_t)0x00000024)

/* TIM3 */
#define ADC_ExternalTrigConv_Timer3               ((uint32_t)0x00000034)

/* Software */
#define ADC_ExternalTrigConv_Software             ((uint32_t)0x00000000)

#define ADC_ExternalTrigConv_EXTRising            ((uint32_t)0x00000008)    

#define IS_ADC_EXTERNAL_TRIG_CONV(CONV) (((CONV) == ADC_ExternalTrigConv_Timer0)   ||\
                                         ((CONV) == ADC_ExternalTrigConv_Timer1)   ||\
                                         ((CONV) == ADC_ExternalTrigConv_Timer2)   ||\
                                         ((CONV) == ADC_ExternalTrigConv_Timer3)   ||\
                                         ((CONV) == ADC_ExternalTrigConv_Software) ||\
                                         ((CONV) == ADC_ExternalTrigConv_EXTRising))



/**
  * @}
  */ 

/** @defgroup ADC_data_align 
  * @{
  */ 
  
#define ADC_DataAlign_Right                        ((uint32_t)0x00000000)
#define ADC_DataAlign_Left                         ADC_CR_ALIGN

#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DataAlign_Right) || \
                                  ((ALIGN) == ADC_DataAlign_Left))
/**
  * @}
  */


/** @defgroup ADC_channels 
  * @{
  */ 
  
#define ADC_Channel_0                              ADC_CR_CHSEL_0
#define ADC_Channel_1                              ADC_CR_CHSEL_1
#define ADC_Channel_2                              ADC_CR_CHSEL_2
#define ADC_Channel_3                              ADC_CR_CHSEL_3
#define ADC_Channel_4                              ADC_CR_CHSEL_4
#define ADC_Channel_5                              ADC_CR_CHSEL_5
#define ADC_Channel_6                              ADC_CR_CHSEL_6
#define ADC_Channel_7                              ADC_CR_CHSEL_7
#define ADC_Channel_8                              ADC_CR_CHSEL_8
#define ADC_Channel_9                              ADC_CR_CHSEL_9
#define ADC_Channel_10                             ADC_CR_CHSEL_10 
#define ADC_Channel_11                             ADC_CR_CHSEL_11 


#define IS_ADC_CHANNEL(CHANNEL)         (((CHANNEL) == ADC_Channel_0) ||\
                                         ((CHANNEL) == ADC_Channel_1) ||\
                                         ((CHANNEL) == ADC_Channel_2) ||\
                                         ((CHANNEL) == ADC_Channel_3) ||\
                                         ((CHANNEL) == ADC_Channel_4) ||\
                                         ((CHANNEL) == ADC_Channel_5) ||\
                                         ((CHANNEL) == ADC_Channel_6) ||\
                                         ((CHANNEL) == ADC_Channel_7) ||\
                                         ((CHANNEL) == ADC_Channel_8) ||\
                                         ((CHANNEL) == ADC_Channel_9) ||\
                                         ((CHANNEL) == ADC_Channel_10)||\
                                         ((CHANNEL) == ADC_Channel_11))
/**
  * @}
  */ 
  
/** @defgroup ADC_interrupts_definition 
  * @{
  */ 

#define ADC_IT_EOC                                 ADC_CR_EOCIE
 
#define IS_ADC_CONFIG_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFFFBFF) == (uint32_t)RESET))

#define IS_ADC_GET_IT(IT)    ((IT) == ADC_IT_EOC)                     

#define IS_ADC_CLEAR_IT(IT)  (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFFFBFF) == (uint32_t)RESET))

/**
  * @}
  */ 

/** @defgroup ADC_flags_definition 
  * @{
  */ 
  
#define ADC_FLAG_ADRDY                             ADC_SR_ADRDY
#define ADC_FLAG_EOC                               ADC_SR_EOC


#define IS_ADC_CLEAR_FLAG(FLAG) (((FLAG) != (uint32_t)RESET) && (((FLAG) & 0xFFFFFFFC) == (uint32_t)RESET))

#define IS_ADC_GET_FLAG(FLAG) (((FLAG) == ADC_FLAG_ADRDY)   || ((FLAG) == ADC_FLAG_EOC))     
                               
/**
  * @}
  */
  
/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

/*  Function used to set the ADC configuration to the default reset state *****/


/* Initialization and Configuration functions *********************************/ 


/* This Function is obsolete and maintained for legacy purpose only.
   ADC_ClockModeConfig() function should be used instead */


/* Power saving functions *****************************************************/





/* Channels Configuration functions *******************************************/



/* Interrupts and flags management functions **********************************/

void ADC_Init(CMSDK_ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_Cmd(CMSDK_ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ClockModeConfig(CMSDK_ADC_TypeDef* ADCx, uint32_t ADC_ClockMode);
void ADC_HighSampModeCmd(CMSDK_ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ChannelConfig(CMSDK_ADC_TypeDef* ADCx, uint32_t ADC_Channel);
void ADC_ContinuousModeCmd(CMSDK_ADC_TypeDef* ADCx, FunctionalState NewState);
uint32_t ADC_GetCalibrationFactor(CMSDK_ADC_TypeDef* ADCx);
void ADC_StopOfConversion(CMSDK_ADC_TypeDef* ADCx);
void ADC_StartOfConversion(CMSDK_ADC_TypeDef* ADCx);
uint16_t ADC_GetConversionValue(CMSDK_ADC_TypeDef* ADCx);
void ADC_ITConfig(CMSDK_ADC_TypeDef* ADCx, uint32_t ADC_IT, FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(CMSDK_ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
void ADC_ClearFlag(CMSDK_ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
ITStatus ADC_GetITStatus(CMSDK_ADC_TypeDef* ADCx, uint32_t ADC_IT);


#ifdef __cplusplus
}
#endif

#endif /*__PT32F0XX_ADC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************(C) COPYRIGHT PENGPAI Microelectronics*****END OF FILE****/
