/**
  ******************************************************************************
  * @file    pt32f0xx_ana.c
  * @author  Application Team
  * @version V1.1.0
  * @date    15-September-2020 
  * @brief   This file provides firmware functions to manage the following 
  *          
  *          
  *         
  *           
  *          
  *
 @verbatim

 ===============================================================================
                        ##### ANA specific features #####
 ===============================================================================


 @endverbatim
  
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
#include "pt32f0xx_ana.h"

/** @addtogroup PT32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup ANA 
  * @brief ANA driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup ANA_Private_Functions
  * @{
  */



void AnaMix_EOSCAutoAmpConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable Automatic amplitude adjustment of external crystal oscillator */
    CMSDK_ANAMIX->EOSC_CON1 |= ANAMIX_EOSCCON1_AUTOAMP;
  }
  else
  {
    /* Disable Automatic amplitude adjustment of external crystal oscillator */
    CMSDK_ANAMIX->EOSC_CON1 &= (uint16_t)~ANAMIX_EOSCCON1_AUTOAMP;
  }
}





/************************(C) COPYRIGHT PENGPAI Microelectronics*****END OF FILE****/
