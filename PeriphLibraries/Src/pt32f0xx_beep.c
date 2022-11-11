/**
  ******************************************************************************
  * @file    pt32f0xx_beep.c
  * @author  Application Team
  * @version V1.1.0
  * @date    15-September-2020  
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Buzzer driver peripheral:
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
#include "pt32f0xx_beep.h"

/** @addtogroup PT32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup Buzzer 
  * @brief Buzzer driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/** @defgroup Buzzer_Group1 Configuration of the Buzzer computation unit functions
 *  @brief   Configuration of the Buzzer  unit functions 
 *
@verbatim
 ===============================================================================
                     ##### Buzzer configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */
/** @defgroup Buzzer_Private_Functions
  * @{
  */
/**
  * @brief  Initializes the beep peripheral according to 
  *         the specified parameters in the Beep_InitStruct.
  * @param  Beep_InitStruct:Buzzer initialization structure.
            @param  Subdivide
						        @arg  BEEP_SUBDIV_X2
                    @arg  BEEP_SUBDIV_X4
                    @arg	BEEP_SUBDIV_X8									
						@param  Prescaler	       
  * @retval None
  */	
void Beep_Init(Beep_InitTypeDef* Beep_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_BEEP_SUBDIV(Beep_InitStruct->Subdivide));
  assert_param(IS_BEEP_CPSR(Beep_InitStruct->Prescaler));
  /*  */
  tmpreg = BEEP->CR;
  /*  */
  tmpreg &= (uint32_t)~(uint32_t)(BEEP_CR_CPSR | BEEP_CR_SUBDIV);
  /*  */
  tmpreg  |= ((uint32_t)(Beep_InitStruct->Subdivide));
	tmpreg  |= ((uint32_t)((Beep_InitStruct->Prescaler)<<0x01));

  BEEP->CR = tmpreg;	
}

/**
  * @brief  Enables or disables the  BEEP peripheral.
  * @param  NewState: new state of the USARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
            @arg   ENABLE
            @arg   DISABLE
  * @retval None
  */
void Beep_Cmd(FunctionalState NewState)
{ 
	/* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    BEEP->CR |= BEEP_CR_EN;
  }
  else
  {
    BEEP->CR &= (uint32_t)~((uint32_t)BEEP_CR_EN);
  }
}


/**
  * @brief  Set the clock pre-division factor of buzzer
  * @param  Prescaler:Clock predivision factor.
  * @retval 
  */
void Beep_PrescalerConfig(uint8_t Prescaler)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_BEEP_CPSR(Prescaler));
  /*  */
  tmpreg = BEEP->CR;
  /*  */
  tmpreg &= (uint32_t)~(uint32_t)(BEEP_CR_CPSR);
  /*  */
	tmpreg  |= ((uint32_t)(Prescaler<<0x01));
  /* Write to CRC CR */
  BEEP->CR = tmpreg;	
}

/**
  * @brief  Select the output frequency of buzzer 
  * @param  Subdivide: output frequency
						 @arg  BEEP_SUBDIV_X2
             @arg  BEEP_SUBDIV_X4
             @arg	 BEEP_SUBDIV_X8	            
  * @param 
  * @retval 
  */
void Beep_SubDivConfig(uint8_t Subdivide)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_BEEP_SUBDIV(Subdivide));
  tmpreg = BEEP->CR;
  tmpreg &= (uint32_t)~(uint32_t)(BEEP_CR_SUBDIV);
	tmpreg  |= ((uint32_t)(Subdivide));
  BEEP->CR = tmpreg;	
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
