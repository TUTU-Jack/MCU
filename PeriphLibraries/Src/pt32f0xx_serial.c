/*********************************************************************************************************//**
 * @file    pt32f0xx_serial.c
  * @author  Application Team
  * @version V1.1.0
  * @date    15-September-2020
 * @brief   This file provides all the Low level serial routines for pangu01
 *************************************************************************************************************

 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "pt32f0xx.h"



/** @defgroup SERIAL SERIAL
  * @brief Serial related functions
  * @{
  */

/*********************************************************************************************************//**
 * @brief  Put char to UART.
 * @param  ch: The char put to UART.
 * @retval The char put to UART.
 ************************************************************************************************************/
uint16_t SERIAL_PutChar(uint8_t ch)
{

  while ((UART0->SR & UART_ISR_TXF)); 
  UART0->BR = ch;	

  return ch;
}

/*********************************************************************************************************//**
 * @brief  Get char from UART.
 * @retval The char got from UART.
 ************************************************************************************************************/
uint16_t SERIAL_GetChar(void)
{

  while ((UART0->SR & UART_ISR_RXNE)==0); // Wait if Receive Holding register is empty
  return (UART0->BR);
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