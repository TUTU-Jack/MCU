/*********************************************************************************************************//**
 * @file    pt32f0xx_retarget.c
  * @author  Application Team
  * @version V1.1.0
  * @date    15-September-2020
 * @brief   Retarget layer for target-dependent low level functions.
 *************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "pt32f0xx.h"

#if defined (__CC_ARM)
  #pragma import(__use_no_semihosting_swi)
#endif

#include <stdio.h>

#if defined (__CC_ARM)
  #include <rt_misc.h>
#endif



/**
  * @}
  */

/* Global variables ----------------------------------------------------------------------------------------*/
/** @defgroup RETARGET_Global_Variable Retarget global variables
  * @{
  */
#if defined (__CC_ARM)
struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;
#endif
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup RETARGET_Exported_Functions Retarget exported functions
  * @{
  */

int __backspace(FILE *stream)
{
  return 0;
}

int fputc (int ch, FILE *f)
{

  return (SERIAL_PutChar(ch));

}

int fgetc (FILE *f)
{

  return (SERIAL_GetChar());

}



void _sys_exit(int return_code)
{
label:  goto label;  /* endless loop                                                                        */
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

/************************(C) COPYRIGHT PENGPAI Microelectronics*****END OF FILE****/