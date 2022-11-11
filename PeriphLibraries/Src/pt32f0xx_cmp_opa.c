/**
  ******************************************************************************
  * @file    pt32f0xx_cmp_opa.c
  * @author  Application Team
  * @version V1.1.0
  * @date    15-September-2020 
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog comparators and operational amplifiers peripheral:
  *           + Initialization and Configuration
  *           + 
  *           + Interrupts and flags management
  *
  *  @verbatim
================================================================================
                      ##### How to use this driver #####
================================================================================
    [..]


  *  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "pt32f0xx_cmp_opa.h"

/** @addtogroup PT32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup Comparators&Operational Amplifier
  * @brief CMP&OPA driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup CMP&OPA_Private_Functions
  * @{
  */

/** @defgroup CMP&OPA_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim
 ===============================================================================
          ##### Initialization and Configuration functions #####
 ===============================================================================
    [..] This section provides functions allowing to:

   
@endverbatim
  * @{
  */

/**
  * @brief  Initializes the CMPOPA peripheral according to the specified parameters
  *         in the CMPOPA_InitStruct.
  * @note   This function is used to configure the global features of the CMPOPA.
  * @param  CMPOPAx: where x can be 0,1 to select the CMPOPA peripheral.
	          @arg  CMPOPA0
						@arg  CMPOPA1
  * @param  CMPOPA_InitStruct: pointer to an CMPOPA_InitTypeDef structure that contains 
  *         the configuration information for the specified CMPOPA peripheral.
	          @param  CMP_PosInputSEL£ºComparator positive input selection.
						        @arg  CMP_REFSEL_PIN
                    @arg  CMP_REFSEL_DAC
                    @arg  CMP_REFSEL_BG										
						@param  CMP_FilterSampling£º
						        @arg  CMP_FSTIMES_NONE
										@arg  CMP_FSTIMES_X2
										@arg  CMP_FSTIMES_X4
										@arg  CMP_FSTIMES_X8
										@arg  CMP_FSTIMES_X16
										@arg  CMP_FSTIMES_X32
										@arg  CMP_FSTIMES_X64
						@param  CMP_HSMode£ºHigh speed mode enable control.
						        @arg  DISABLE
										@arg  ENABLE
						@param  CMP_PolarityReversal£ºOutput polarity selection of comparator.
						        @arg  DISABLE
										@arg  ENABLE										
  * @retval None
  */
void CMP_Init(CMSDK_CMPOPA_TypeDef* CMPOPAx, CMPOPA_InitTypeDef* CMPOPA_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_CMPOPA_ALL_PERIPH(CMPOPAx));
  assert_param(IS_CMP_REFSEL(CMPOPA_InitStruct->CMP_PosInputSEL));
	assert_param(IS_CMP_FSTIMES(CMPOPA_InitStruct->CMP_FilterSampling));
  assert_param(IS_FUNCTIONAL_STATE(CMPOPA_InitStruct->CMP_HSMode));
	assert_param(IS_FUNCTIONAL_STATE(CMPOPA_InitStruct->CMP_PolarityReversal));
  tmpreg = CMPOPAx->CR1;
  tmpreg &= (uint32_t)~(uint32_t)(CMPOPA_CR1_REFSEL | CMPOPA_CR1_FS);
  tmpreg  |= ((uint32_t)((CMPOPA_InitStruct->CMP_PosInputSEL) | (CMPOPA_InitStruct->CMP_FilterSampling)));
	tmpreg  |= ((uint32_t)(((CMPOPA_InitStruct->CMP_PosInputSEL)<<0x07) | ((CMPOPA_InitStruct->CMP_FilterSampling)<<0x08)));
  CMPOPAx->CR1 = tmpreg;
	
	
}

/**
  * @brief  Fills each CMPOPA_InitStruct member with its default value.
  * @note   This function is used to initialize the global features of the CMPOPA.
  * @param  CMPOPA_InitStruct: pointer to an ADC_InitTypeDef structure which will 
  *         be initialized.
	          @param  CMP_PosInputSEL£ºComparator positive input selection.
						        @arg  CMP_REFSEL_PIN
                    @arg  CMP_REFSEL_DA
                    @arg  CMP_REFSEL_BG										
						@param  CMP_FilterSampling£º
						        @arg  CMP_FSTIMES_NONE
										@arg  CMP_FSTIMES_X2
										@arg  CMP_FSTIMES_X4
										@arg  CMP_FSTIMES_X8
										@arg  CMP_FSTIMES_X16
										@arg  CMP_FSTIMES_X32
										@arg  CMP_FSTIMES_X64
						@param  CMP_HSMode£ºHigh speed mode enable control.
						        @arg  DISABLE
										@arg  ENABLE
						@param  CMP_PolarityReversal£ºOutput polarity selection of comparator.
						        @arg  DISABLE
										@arg  ENABLE	
  * @retval None
  */
void CMP_StructInit(CMPOPA_InitTypeDef* CMPOPA_InitStruct)
{

  CMPOPA_InitStruct->CMP_PosInputSEL = CMP_REFSEL_PIN;

  CMPOPA_InitStruct->CMP_FilterSampling =CMP_FSTIMES_NONE;
	
	CMPOPA_InitStruct->CMP_HSMode = DISABLE;
	
	CMPOPA_InitStruct->CMP_PolarityReversal= DISABLE;

}

/**
  * @brief  Enables or disables the specified CMPOPA peripheral.
  * @param  CMPOPAx: where x can be 1 to select the CMPOPAx peripheral.
	          @arg  CMPOPA0
						@arg  CMPOPA1
  * @param  NewState: new state of the CMPOPAx peripheral. 
  *         @arg ENABLE 
            @arg DISABLE
  * @retval None
  */
void CMPOPA_Cmd(CMSDK_CMPOPA_TypeDef* CMPOPAx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CMPOPA_ALL_PERIPH(CMPOPAx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    CMPOPAx->CR1 |= (uint32_t)CMPOPA_CR1_EN;
  }
  else
  {
    CMPOPAx->CR1 &= (uint32_t)~((uint32_t)CMPOPA_CR1_EN);
  }
}

/**
  * @brief  Enables or disables the OPA mode.
  * @param  CMPOPAx: where x can be 1 to select the CMPOPAx peripheral.
	          @arg  CMPOPA0
						@arg  CMPOPA1
  * @param  NewState: new state of the CMPOPAx peripheral. 
  *         @arg ENABLE 
            @arg DISABLE
  * @retval None
  */
void CMPOPA_OPA_Config(CMSDK_CMPOPA_TypeDef* CMPOPAx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CMPOPA_ALL_PERIPH(CMPOPAx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    CMPOPAx->CR2 |= (uint32_t)CMPOPA_CR2_OPAEN;
  }
  else
  {
    CMPOPAx->CR2 &= (uint32_t)~((uint32_t)CMPOPA_CR2_OPAEN);
  }
}

/**
  * @brief  Configure CMPOPA initialization delay.
  * @param  CMPOPA: where x can be 1 to select the CMPOPA peripheral.
            @arg CMPOPA0
            @arg CMPOPA1
  * @param  CMPOPA_InitaDelay: Initialization delay time configuration.  ( 0~0x3FFF)    
            This parameter is between 0 and 0~0x3FFF.
  * @retval None
  */
void CMPOPA_SetInitDelayValue(CMSDK_CMPOPA_TypeDef* CMPOPAx, uint32_t CMPOPA_InitaDelay)
{
  /* Check the parameters */
  assert_param(IS_CMPOPA_ALL_PERIPH(CMPOPAx));
	assert_param(IS_CMPOPA_INITDELAY_VALUE(CMPOPA_InitaDelay));
  CMPOPAx->INITDELAY = CMPOPA_InitaDelay;

}

/**
  * @brief  Comparator DAC input data.
  * @param  CMPOPA: where x can be 1 to select the CMPOPA peripheral.
            @arg CMPOPA0
            @arg CMPOPA1
    @param  CMPOPA_DACValue:DAC input data.
            This parameter is between 0 and 0x1F.
  * @retval None
  */
void CMP_SetDACValue(CMSDK_CMPOPA_TypeDef* CMPOPAx, uint32_t CMPOPA_DACValue)
{
  /* Check the parameters */
  assert_param(IS_CMPOPA_ALL_PERIPH(CMPOPAx));
  assert_param(IS_CMPOPA_DAC_VALUE(CMPOPA_DACValue));	
  CMPOPAx->DAC = CMPOPA_DACValue;

}





/** @defgroup CMP&OPA_Group2 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions.
 *
@verbatim   
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================

  *** Flags and Interrupts for Comparators ***
  =====================================================
    [..]
        (+)Flags :
           (##) CMP_FLAG_FALL : This flag is set when Comparator has a falling edge output.
           (##) CMP_FLAG_RISE : This flag is set when Comparator has a rising edge output.
           (##) CMP_FLAG_FALL_WEAK : This flag is set when Comparator has a falling edge output in the sleep mode.
           (##) CMP_FLAG_RISE_WEAK : This flag is set when Comparator has a falling edge output	in the sleep mode.					
        (+)Interrupts :
           (##) CMPOPA_IE_FALL : This flag is set when Comparator has a falling edge output.
           (##) CMPOPA_IE_RISE : This flag is set when Comparator has a rising edge output.
           (##) CMPOPA_IE_FALL_WEAK : This flag is set when Comparator has a falling edge output in the sleep mode.
           (##) CMPOPA_IE_RISE_WEAK : This flag is set when Comparator has a falling edge output	in the sleep mode.

    [..] The user should identify which mode will be used in his application to 
         manage the CMP&OPA events: Polling mode or Interrupt mode.
  
    [..] In the Polling Mode it is advised to use the following functions:
         (+) CMP_GetFlagStatus() : to check if flags events occur.
         (+) CMP_ClearFlag()     : to clear the flags events.
  
    [..] In the Interrupt Mode it is advised to use the following functions:
         (+) CMP_ITConfig()       : to enable or disable the interrupt source.
         (+) CMP_GetITStatus()    : to check if Interrupt occurs.

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified CMPOPA interrupts.
  * @param  CMPOPA: where x can be 1 to select the CMPOPA peripheral.
            @arg  CMPOPA0
            @arg  CMPOPA1
  * @param  CMP_IT: specifies the CMPOPA interrupt sources to be enabled or disabled.
  *         @arg  CMPOPA_IE_FALL
	          @arg  CMPOPA_IE_RISE
	          @arg  CMPOPA_IE_FALL_WEAK
						@arg  CMPOPA_IE_RISE_WEAK	
  * @param  NewState: new state of the specified CMPOPA interrupts.
  *         @arg  ENABLE 
  *         @arg  DISABLE
  * @retval None
  */
void CMP_ITConfig(CMSDK_CMPOPA_TypeDef* CMPOPAx, uint32_t CMP_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CMPOPA_ALL_PERIPH(CMPOPAx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_CMP_CONFIG_IT(CMP_IT)); 

  if (NewState != DISABLE)
  {
    /* Enable the selected CMP interrupts */
    CMPOPAx->IE |= CMP_IT;
  }
  else
  {
    /* Disable the selected CMP interrupts */
    CMPOPAx->IE &= (~(uint32_t)CMP_IT);
  }
}

/**
  * @brief  Checks whether the specified CMPOPA flag is set or not.
  * @param  CMPOPAx: where x can be 0,1 to select the CMPOPA peripheral.
            @arg CMPOPA0
            @arg CMPOPA1
  * @param  CMP_FLAG: specifies the flag to check. 
  *         This parameter can be one of the following values:
  *         @arg CMP_FLAG_FALL
  *         @arg CMP_FLAG_RISE
            @arg CMP_FLAG_FALL_WEAK
            @arg CMP_FLAG_RISE_WEAK
  * @retval The new state of CMP_FLAG (SET or RESET).
  */
FlagStatus CMP_GetFlagStatus(CMSDK_CMPOPA_TypeDef* CMPOPAx, uint32_t CMP_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_CMPOPA_ALL_PERIPH(CMPOPAx));
  assert_param(IS_CMP_GET_FLAG(CMP_FLAG));
  /* Check the status of the specified ADC flag */
  if ((CMPOPAx->EIS & CMP_FLAG) != (uint32_t)RESET)
  {
    /* CMP_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* CMP_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the CMP_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the CMP's pending flags.
  * @param  CMPOPAx: where x can be 0,1 to select the CMPOPA peripheral.
            @arg CMPOPA0
            @arg CMPOPA1
  * @param  CMP_FLAG: specifies the flag to clear.  
            @arg CMP_FLAG_FALL
            @arg CMP_FLAG_RISE
            @arg CMP_FLAG_FALL_WEAK
            @arg CMP_FLAG_RISE_WEAK 
  * @retval None
  */
void CMP_ClearFlag(CMSDK_CMPOPA_TypeDef* CMPOPAx, uint32_t CMP_FLAG)
{
  /* Check the parameters */
  assert_param(IS_CMPOPA_ALL_PERIPH(CMPOPAx));
  assert_param(IS_CMP_CLEAR_FLAG(CMP_FLAG));

  /* Clear the selected CMP flags */
  CMPOPAx->EIS = (uint32_t)CMP_FLAG;
}

/**
  * @brief  Checks whether the specified CMPOPA interrupt has occurred or not.
  * @param  CMPOPAx: where x can be 1 to select the CMPOPA peripheral.
            @arg CMPOPA0
            @arg CMPOPA1
  * @param  CMP_IT: specifies the CMPOPA interrupt source to check.
  *         This parameter can be one of the following values:
  *         @arg  CMP_IT_FALL
            @arg  CMP_IT_RISE
            @arg  CMP_IT_FALL_WEAK
            @arg  CMP_IT_RISE_WEAK 
  * @retval The new state of CMP_IT (SET or RESET).
  */
ITStatus CMP_GetITStatus(CMSDK_CMPOPA_TypeDef* CMPOPAx, uint32_t CMP_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_CMPOPA_ALL_PERIPH(CMPOPAx));
  assert_param(IS_CMP_GET_IT(CMP_IT));

  /* Get the CMP_IT enable bit status */
  enablestatus = (uint32_t)(CMPOPAx->IE & CMP_IT); 

  /* Check the status of the specified CMP interrupt */
  if (((uint32_t)(CMPOPAx->EIS & CMP_IT) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    /* CMP_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* CMP_IT is reset */
    bitstatus = RESET;
  }
  /* Return the CMP_IT status */
  return  bitstatus;
}

/**
  * @}
  */

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
