/**
  ******************************************************************************
  * @file    pt32f0xx_uart.c
  * @author  Application Team
  * @version V1.1.0
  * @date    15-September-2020
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Universal synchronous asynchronous receiver
  *          transmitter (UART):
  *           + Initialization and Configuration
  *           + STOP Mode
  *           + Data transfers
  *           + Multi-Processor Communication
  *           + Half-duplex mode
  *           + Smartcard mode
  *           + IrDA mode
  *           + RS485 mode  
  *           + Interrupts and flags management
  *           
  *  @verbatim
 ===============================================================================
                       ##### How to use this driver #####
 ===============================================================================
    [..]
        (#) Peripheral's alternate function: 
            (++) Connect the pin to the desired peripherals' Alternate 
                 Function (AF) using GPIO_PinAFConfig() function.       
        (#) Enable the NVIC and the corresponding interrupt using the function 
            UART_ITConfig() if you need to use interrupt mode.    
        (#) Enable the UART using the UART_Cmd() function.   
    [..]
            Refer to Multi-Processor, half-duplex, Smartcard, IrDA sub-sections
            for more details.
            
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
#include "pt32f0xx_uart.h"

/** @addtogroup PT32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup UART 
  * @brief UART driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup UART_Private_Functions
  * @{
  */

/** @defgroup UART_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
          ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]
        This subsection provides a set of functions allowing to initialize the UART 
        in asynchronous and in synchronous modes.
        (+) For the asynchronous mode only these parameters can be configured: 
          (++) Baud Rate.
          (++) Word Length.
          (++) Stop Bit.
          (++) Parity: If the parity is enabled, then the MSB bit of the data written
               in the data register is transmitted but is changed by the parity bit.
               Depending on the frame length defined by the MODE[2:0] bit,
               the possible UART frame formats are as listed in the following table:

   +------------------------------------------------------------------------+     
   |   M2 bit |   M1 bit|  M0 bit   |            UART frame                 |
   |--------- |---------------------|---------------------------------------|             
   |    0     |    0    |    0      |    | SB | 8 bit data | STB |          |
   |--------- |---------|-----------|---------------------------------------|  
   |    0     |    1    |    1      |    | SB | 7 bit data | PB | STB |     |
   |--------- |---------|-----------|---------------------------------------|  
   |    1     |    0    |    0      |    | SB | 9 bit data | STB |          |
   |--------- |---------|-----------|---------------------------------------|  
   |    1     |    1    |    1      |    | SB | 8 bit data | PB | STB |     |
   +------------------------------------------------------------------------+            

          (++) Receiver/transmitter modes.
    [..] The UART_Init() function follows the UART  asynchronous configuration 
         procedure(details for the procedure are available in reference manual.

@endverbatim
  * @{
  */
/**
  * @brief  Initializes the UARTx peripheral according to the specified
  *         parameters in the UART_InitStruct .
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral. 
            @arg UART0
						@arg UART1
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure that contains
  *         the configuration information for the specified UART peripheral.
	          @param  UART_BaudRate£ºBaud rate of UART communication
                  	This parameter must be a number between 0 and 0x5B8D81.
            @param  UART_FrameLength£ºUART Frame length
                   @arg  UARTM_8D		
                   @arg  UARTM_7D_P
                   @arg  UARTM_9D
                   @arg	 UARTM_8D_W	
                   @arg	 UARTM_8D_P		
						@param  UART_StopBit: Stop bit length.
                   @arg	 UART05StopBits	
                   @arg  UART1StopBit
                   @arg  UART15StopBits
                   @arg	 UART2StopBits
						@param  UART_SampleRate: Serial communication symbol sampling rate
                   @arg  UART_SAMPLERATEX4
                   @arg  UART_SAMPLERATEX8
                   @arg	 UART_SAMPLERATEX16
					  @param  UART_RXEN: Receive enable and disable.
                   @arg  Enable
                   @arg	 Disable								 
  * @retval None
  */
void UART_Init(CMSDK_UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct)
{
  uint32_t  tmpreg = 0 ,divider = 0,pclk = 0;
	System_ClocksTypeDef System_ClocksStatus;
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_BAUDRATE(UART_InitStruct->UART_BaudRate));  
  assert_param(IS_UART_WORD_LENGTH(UART_InitStruct->UART_WordLength));
  assert_param(IS_UART_STOPBITS(UART_InitStruct->UART_StopBit));
  assert_param(IS_UART_SAMPLERATE(UART_InitStruct->UART_SampleRate));	
	assert_param(IS_UART_RXSTATUS(UART_InitStruct->UART_RXEN));
	
  UARTx->RRR = UART_BRR_BRR;
  UARTx->TRR = UART_TXFR_TXFR;
	
	tmpreg &= ~(UART_CR_MODE | UART_CR_STOP | UART_CR_PBR);
	tmpreg |= (UART_InitStruct -> UART_WordLength | UART_InitStruct -> UART_StopBit | UART_InitStruct -> UART_Parity);  
	UARTx->CR = tmpreg; 
  if (UART_InitStruct -> UART_RXEN != DISABLE)
	{		
    UARTx->CR |=UART_CR_RXEN;
	}		
  else
	{		
    UARTx->CR &=~UART_CR_RXEN;
	}
		
   System_GetClocksFreq(&System_ClocksStatus);
	
	 pclk=System_ClocksStatus.PCLK_Frequency;
   tmpreg  =  (pclk) % (UART_InitStruct->UART_SampleRate * UART_InitStruct->UART_BaudRate);
   divider =  (pclk) / (UART_InitStruct->UART_SampleRate * UART_InitStruct->UART_BaudRate);
 
  if (tmpreg > ((UART_InitStruct->UART_SampleRate/2) * UART_InitStruct->UART_BaudRate))
	{
		UARTx->BRR = (uint16_t) (divider + 1);  	
	}
  else
	{
    UARTx->BRR = (uint16_t) divider; 	
	}

  switch (UART_InitStruct->UART_SampleRate)
	{

    case UART_SAMPLERATEX16 : /* 16 times sampling */
			UARTx->BRR &= ~UART_BRR_SR;
		  UARTx->BRR |=UART_BRR_SRX16;
      break;
    case UART_SAMPLERATEX8 :  /* 8 times sampling */
			UARTx->BRR &= ~UART_BRR_SR;
		  UARTx->BRR |=UART_BRR_SRX8; 
      break;
    case UART_SAMPLERATEX4 :  /* 4 times sampling */
			UARTx->BRR &= ~UART_BRR_SR;
		  UARTx->BRR |=UART_BRR_SRX4; 
      break;
    default: 
			break;   	
	} 	
} 


/**
  * @brief  Fills each UART_InitStruct member with its default value.
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure
  *         which will be initialized.
            @param  UART_BaudRate£ºBaud rate of UART communication
                  	This parameter must be a number between 0 and 0x5B8D81.
            @param  UART_FrameLength£ºUART Frame length
                   @arg  UARTM_8D		
                   @arg  UARTM_7D_P
                   @arg  UARTM_9D
                   @arg	 UARTM_8D_W	
                   @arg	 UARTM_8D_P		
						@param  UART_StopBit: Stop bit length.
                   @arg	 UART05StopBits	
                   @arg  UART1StopBit
                   @arg  UART15StopBits
                   @arg	 UART2StopBits
						@param  UART_SampleRate: Serial communication symbol sampling rate
                   @arg  UART_SAMPLERATEX4
                   @arg  UART_SAMPLERATEX8
                   @arg	 UART_SAMPLERATEX16
					  @param  UART_RXEN: Receive enable and disable.
                   @arg  Enable
                   @arg	 Disable	
						@param  UART_Parity: Parity form.						
  * @retval None
  */
void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
{
  /* USART_InitStruct members default value */
  UART_InitStruct->UART_BaudRate = 19200;
  UART_InitStruct->UART_WordLength = UARTM_8D_P;
  UART_InitStruct->UART_StopBit = UART1StopBit;
  UART_InitStruct->UART_Parity = UART_ODD_PARITY;
  UART_InitStruct->UART_RXEN = ENABLE;
  UART_InitStruct->UART_SampleRate = UART_SAMPLERATEX16;	

}

/**
  * @brief  Enables or disables the specified UART peripheral.
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral. 
            @arg UART0
						@arg UART1
  * @param  NewState: new state of the USARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
             @arg  Enable
             @arg	 Disable
  * @retval None
  */
void UART_Cmd(CMSDK_UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected UART by setting the BRUN bit in the CR register */
    UARTx->CR |= UART_CR_BRUN;
  }
  else
  {
    /* Disable the selected UART by clearing the BRUN bit in the CR register */
    UARTx->CR &= (uint32_t)~((uint32_t)UART_CR_BRUN);
  }
}

/**
  * @brief  Enables or disables the UART's  receiver.
    @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
            @arg UART0
						@arg UART1
  * @param  NewState: new state of the UART transfer direction.
  *         This parameter can be: ENABLE or DISABLE.
            @arg  Enable
            @arg	 Disable
  * @retval None
  */
void UART_RxConfig(CMSDK_UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState != DISABLE)
  {
    /* Enable the UART's transfer interface as Receiver by setting the RXEN bits 
       in the UART CR register */
    UARTx->CR |= UART_CR_RXEN;
  }
  else
  {
    /* Disable the UART's transfer interface as Receiver by setting the RXEN bits
       in the UART CR register */
    UARTx->CR &= (uint32_t)~UART_CR_RXEN;
  }
}

/**
  * @brief  Enables or disables the Pin(s) active level inversion.
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
            @arg UART0
						@arg UART1
  * @param  UART_InvPin: specifies the UART pin(s) to invert.
  *          This parameter can be any combination of the following values:
  *            @arg UART_InvPin_Tx: UART Tx pin active level inversion.
  *            @arg UART_InvPin_Rx: UART Rx pin active level inversion.
  * @param  NewState: new active level status for the UART pin(s).
  *          This parameter can be:
  *            @arg ENABLE: pin(s) signal values are inverted (Vdd =0, Gnd =1).
  *            @arg DISABLE: pin(s) signal works using the standard logic levels (Vdd =1, Gnd =0).
  * @note   This function has to be called before calling UART_Cmd() function.  
  * @retval None
  */

void UART_InvPinCmd(CMSDK_UART_TypeDef* UARTx, uint32_t UART_InvPin, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_INVERSTION_PIN(UART_InvPin));  
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState != DISABLE)
  {
    UARTx->CR |= UART_InvPin;
  }
  else
  {
    UARTx->CR &= (uint32_t)~UART_InvPin;
  }
}

/**
  * @brief  Sets the receiver Time Out value.
  * @param  UARTx: where x can be 0 or 1 to select the UART peripheral.
            @arg UART0
						@arg UART1
  * @param  UART_ReceiverTimeOut: specifies the Receiver Time Out value.\
            This parameter must be a number between 0 and 0xFF.
  * @retval None
  */
void UART_SetReceiverTimeOut(CMSDK_UART_TypeDef* UARTx, uint32_t UART_ReceiverTimeOut)
{    
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_TIMEOUT(UART_ReceiverTimeOut));

  /* Clear the receiver Time Out value by clearing the RTO[7:0] bits in the RTOR
     register  */
  UARTx->TOR &= (uint32_t)~((uint32_t)UART_TO_TO);
  /* Set the receiver Time Out value by setting the RTO[7:0] bits in the RTOR
     register  */
  UARTx->TOR |= UART_ReceiverTimeOut;
}

/**
  * @}
  */

/** @defgroup UART_Group8 Smartcard mode functions
 *  @brief   Smartcard mode functions 
 *
@verbatim   
 ===============================================================================
                     ##### Smartcard mode functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the UART
         Smartcard communication.
    [..] The Smartcard interface is designed to support asynchronous protocol 
         Smartcards as defined in the ISO 7816-3 standard. The UART can provide 
         a clock to the smartcard through the SCLK output. In smartcard mode, 
         SCLK is not associated to the communication but is simply derived from 
         the internal peripheral input clock through a 3-bit prescaler.
    [..] Smartcard communication is possible through the following procedure:
         (#) Configures the Smartcard Prsecaler using the UART_SetPrescaler() 
             function.
         (#) Configures the Smartcard Guard Time using the UART_SetGuardTime() 
             function.
         (#) Program the Smartcard interface using the UART_Init() function as 
             following:
             (++) Word Length = 9 Bits.
             (++) 1.5 Stop Bit.
             (++) Even parity.
             (++) BaudRate = 12096 baud.
             (++) Hardware flow control disabled (RTS and CTS signals).
             (++) Tx and Rx enabled
         (#) Optionally you can enable the parity error interrupt using 
             the UART_ITConfig() function.
         (#) Enable the Smartcard interface using the UART_SmartCardCmd() function.
         (#) Enable the UART using the UART_Cmd() function.
    [..] 
  Please refer to the ISO 7816-3 specification for more details.
    [..] 
         (@) It is also possible to choose 0.5 stop bit for receiving but it is 
             recommended to use 1.5 stop bits for both transmitting and receiving 
             to avoid switching between the two configurations.
         (@) In smartcard mode, the following bits must be kept cleared:
             (+@) EN bit in the UART_IRR register.
             (+@) OWE bits in the UART_CR register.

@endverbatim
  * @{
  */

/**
  * @brief  Sets the system clock prescaler.
  * @param  UARTx: where x can be 1, 2 or 3 to select the USART peripheral.
	          @arg UART0
						@arg UART1
  * @param  UART_Prescaler: specifies the prescaler clock.
	          This parameter must be a number between 0 and 0x05.
  * @note   This function has to be called before calling UART_Cmd() function.    
  * @retval None
  */
void UART_SetPrescaler(CMSDK_UART_TypeDef* UARTx, uint8_t UART_Prescaler)
{ 
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_PRESCALER(UART_Prescaler));
  
  /* Clear the UART prescaler */
  UARTx->ISO7816_CR &= ~UART_ISO7816CR_CLKDIV;
  /* Set the UART prescaler */
  UARTx->ISO7816_CR |= (uint32_t)((uint32_t)UART_Prescaler << 0x04);
	
}



/**
  * @brief  Sets the specified UART guard time.
  * @param  UARTx: where x can be 0 or 1 to select the UART peripheral.
            @arg UART0
						@arg UART1
  * @param  UART_GuardTime: specifies the guard time.
            Interval between sending two consecutive data frames.
  * @retval None
  */	
void UART_SetGuardTime(CMSDK_UART_TypeDef* UARTx, uint8_t UART_GuardTime)
{    
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));

  /* Clear the UART Guard time */
  UARTx->GTR &= ~UART_GTR_GTR;
  /* Set the UART guard time */
  UARTx->GTR |= (uint8_t)UART_GuardTime;
}

/**
  * @brief  Enables or disables the UART's Smart Card mode.  
  * @param  UARTx: where x can be 0 or 1  to select the UART peripheral.
            @arg UART0
						@arg UART1
  * @param  NewState: new state of the Smart Card mode.
  *         This parameter can be: ENABLE or DISABLE.
            @arg  ENABLE
            @arg  DISABLE
  * @retval None
  */
void UART_SmartCardCmd(CMSDK_UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the SC mode by setting the EN bit in the ISO7816CR register */
    UARTx->ISO7816_CR |= UART_ISO7816CR_EN;
  }
  else
  {
    /* Disable the SC mode by clearing the EN bit in the ISO7816CR register */
    UARTx->ISO7816_CR &= (uint32_t)~((uint32_t)UART_ISO7816CR_EN);
  }
}

/**
  * @}
  */

/** @defgroup UART_Group4 Data transfers functions
 *  @brief   Data transfers functions 
 *
@verbatim   
 ===============================================================================
                    ##### Data transfers functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage 
         the UART data transfers.
    [..] During an UART reception, data shifts in least significant bit first 
         through the RX pin. When a transmission is taking place, a write instruction to 
         the UART_TDR register stores the data in the shift register.
    [..] The read access of the UART_RDR register can be done using 
         the UART_ReceiveData() function and returns the RDR value.
         Whereas a write access to the UART_TDR can be done using UART_SendData()
         function and stores the written data into Buffer.

@endverbatim
  * @{
  */

/**
  * @brief  Transmits single data through the UARTx peripheral.
  * @param  UARTx: where x can be from 0 or 1 to select the UART peripheral.
	          @arg UART0
						@arg UART1
  * @param  Data: the data to transmit.
  * @retval None
  */
void UART_SendData(CMSDK_UART_TypeDef* UARTx, uint16_t Data)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_DATA(Data)); 
  /* While the TxFIFO contain 8 characters. */
  while((UARTx->SR & UART_ISR_TXF)); 
  /* Transmit Data */
  UARTx->BR = (Data & (uint16_t)0x01FF);
}

/**
  * @brief  Transmits single string through the UARTx peripheral.
  * @param  UARTx: where x can be from 0 or 1 to select the UART peripheral.
            @arg UART0
						@arg UART1
  * @param  String: Pointer to the string to transmit.
  * @retval None
  */
void UART_StringSend(CMSDK_UART_TypeDef* UARTx, uint8_t *String)
{

  while(*String != '\0')
	{	
    while((UARTx->SR & UART_ISR_TXF)); 
    UART_SendData(UARTx, *String);
		String++;	
	}
  UART_SendData(UARTx, 0x00);
  
}


/**
  * @brief  Returns the most recent received data by the UARTx peripheral.
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
            @arg UART0
						@arg UART1
  * @retval The received data.
  */
uint16_t UART_ReceiveData(CMSDK_UART_TypeDef* UARTx)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx)); 
  /* Receive Data */
  return (uint16_t)(UARTx->BR & (uint16_t)0x01FF);
}

/**
  * @brief  Whether the receiver has timed out when receiving string.
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
            @arg UART0
						@arg UART1
  * @Data   Data: Pointer to the receivde data.
  * @param  UART_ReceiverTimeOut: The time out period.
  * @retval Is there a timeout.
  */
uint16_t UART_ReceiveData_Timeout(CMSDK_UART_TypeDef* UARTx, uint16_t *Data, uint32_t UART_ReceiverTimeOut)
{
  uint16_t wStatus;
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx)); 
  /* Reload the Timeout counter */	
  UART_SetReceiverTimeOut(UARTx, UART_ReceiverTimeOut);
  /* while the RxFIFO is empty and no Timeoutidle */	
	while (!((wStatus=UARTx->SR) & (UART_ISR_TOIDLE|UART_ISR_RXHF|UART_ISR_RXNE)));
  /* Receive Data */
	*Data = (uint16_t)(UARTx->BR & (uint16_t)0x01FF); 
  return (wStatus);
}

/**
  * @brief  Returns the most recent received string by the UARTx peripheral
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
            @arg UART0
						@arg UART1
  * @Data   Data: Pointer to the reveive data.
  * @retval The received data.
  */
uint16_t UART_StringReceive(CMSDK_UART_TypeDef* UARTx, uint8_t *Data)
{
  uint8_t *pSTRING;
  uint16_t wStatus;
  pSTRING=Data;
  do
  {
    /* while the RxFIFO is empty and no Timeoutidle */		
    while (!((wStatus=UARTx->SR) & (UART_ISR_RXHF|UART_ISR_RXNE)));// 
    /* Read the Receive Buffer */			
    *(pSTRING++) = (uint8_t)UARTx->BR; 
  }
	
	while((*(pSTRING - 1)!=0x0D)&(*(pSTRING - 1)!='\0'));
  *(pSTRING - 1)='\0';
	
  return wStatus;
}

/**
  * @brief  This function the loop back mode of the selected UART.
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
            @arg UART0
						@arg UART1
  * @param  NewState: new active level status for the UART pin(s).
  *         This parameter can be:
  *         @arg ENABLE: Loop back mode .
  *         @arg DISABLE: Normal communication mode .
  * @retval None
  */
void UART_LoopBackConfig(CMSDK_UART_TypeDef* UARTx, FunctionalState NewStatus)
{
	
	if (NewStatus != DISABLE)
  {
    UARTx->CR |= UART_CR_LPB;
  }
  else
  {
    UARTx->CR &= ~UART_CR_LPB;
  }

}

/**
  * @brief  This function reset the Rx and the Tx FIFOs
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
            @arg UART0
						@arg UART1
  * @param  FIFO: Transmit FIFO or receive FIFO for the UART .
  *         This parameter can be:
  *         @arg Rx_FIFO: Receive FIFO .
  *         @arg Tx_FIFO: Transmit FIFO .
  * @retval None.
  */
void UART_FifoReset(CMSDK_UART_TypeDef * UARTx,  UART_FifoTypeDef FIFO)
{

  switch (FIFO)
  {
       case Rx_FIFO : UARTx->RRR=UART_RXFR_RXFR;break;
       case Tx_FIFO : UARTx->TRR=UART_TXFR_TXFR;break;
  }
}

/**
  * @}
  */

/** @defgroup UART_Group9 IrDA mode functions
 *  @brief   IrDA mode functions 
 *
@verbatim   
 ===============================================================================
                        ##### IrDA mode functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the UART
         IrDA communication.
    [..] IrDA is a half duplex communication protocol. If the Transmitter is busy, 
         any data on the IrDA receive line will be ignored by the IrDA decoder 
         and if the Receiver is busy, data on the TX from the UART to IrDA will 
         not be encoded by IrDA. While receiving data, transmission should be 
         avoided as the data to be transmitted could be corrupted.
    [..] IrDA communication is possible through the following procedure:
         (#) Program the Baud rate, Word length = 8 bits, Stop bits, Parity, 
             Transmitter/Receiver modes the UART_Init() function.
         (#) Configures the IrDA pulse width by configuring the prescaler using  
             the UART_SetDutyCycle() function.
         (#) Enable the IrDA using the UART_IrDACmd() function.
         (#) Enable the UART using the UART_Cmd() function.         
    [..]
    (@) A pulse of width less than two and greater than one PSC period(s) may or 
        may not be rejected.
    (@) The receiver set up time should be managed by software. The IrDA physical 
        layer specification specifies a minimum of 10 ms delay between 
        transmission and reception (IrDA is a half duplex protocol).
    (@) In IrDA mode, the following bits must be kept cleared:
        (+@) EN  bits in the ISO7816CR register.
				(+@) OWE bits in the UART_CR register.

@endverbatim
  * @{
  */


/**
  * @brief  Enables or disables the UART's IrDA interface.
  * @param  UARTx: where x can be 0 to select the UART peripheral.
	          @arg UART0
						@arg UART1
  * @param  NewState: new state of the IrDA mode.
  *          This parameter can be: ENABLE or DISABLE.
	          @arg  ENABLE
            @arg  DISABLE
  * @retval None
  */
void UART_IrDACmd(CMSDK_UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_0_PERIPH(UARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the IrDA mode by setting the EN bit in the IRR register */
    UARTx->IR_CR |= UART_IRR_EN;
  }
  else
  {
    /* Disable the IrDA mode by clearing the EN bit in the IRR register */
    UARTx->IR_CR &= (uint32_t)~((uint32_t)UART_IRR_EN);
  }
}

/**
  * @brief  Configures the IrDA's Pin polarity
  * @param  UARTx: where x can be 0 to select the UART peripheral.
            @arg UART0
						@arg UART1
  * @param  NewState: new defined levels for the USART data.
  *          This parameter can be:
  *         @arg ENABLE: pin(s) signal values are inverted (Vdd =0, Gnd =1).                       
  *         @arg DISABLE£ºpin(s) signal works using the standard logic levels (Vdd =1, Gnd =0).

  * @note   This function has to be called before calling UART_Cmd() function.  
  * @retval None
  */
void UART_IrDAInvPinCmd(CMSDK_UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_0_PERIPH(UARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the binary data inversion feature by setting the DATAINV bit in 
       the CR2 register */
    UARTx->IR_CR |= UART_IRR_EN;
  }
  else
  {
    /* Disable the binary data inversion feature by clearing the DATAINV bit in 
       the CR2 register */
    UARTx->IR_CR &= (uint32_t)~((uint32_t)UART_IRR_EN);
  }
}

/**
  * @brief  Duty cycle control of infrared transmission.
  * @param  UARTx: where x can be 0,1 to select the USART peripheral.
            @arg UART0
						@arg UART1
  * @param  UART_DutyCycle: Infrared duty cycle.
            This parameter is between 0 and 0x64.
  * @retval None
  */
void UART_SetDutyCycle(CMSDK_UART_TypeDef* UARTx, uint8_t UART_DutyCycle)
{ 
  /* Check the parameters */
  assert_param(IS_USART_0_PERIPH(UARTx));
  assert_param(IS_UART_DUTYCYCLE(UART_DutyCycle));
  
  /* Clear the IrDA's modulation PWM duty cycle */
  UARTx->IRTX_PWMC &= ~UART_IRPWMC_IRPWMC;
  /* Set the IrDA's modulation PWM duty cycle*/
  UARTx->IRTX_PWMC |= (uint32_t)((uint32_t)UART_DutyCycle);
	
}


/**
  * @}
  */
/** @defgroup UART_Group7 Halfduplex mode function
 *  @brief   Half-duplex mode function 
 *
@verbatim   
 ===============================================================================
                   ##### Half-duplex mode function #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the UART
         Half-duplex communication.
    [..] The UART can be configured to follow a single-wire half-duplex protocol 
         where the TX and RX lines are internally connected.
    [..] UART Half duplex communication is possible through the following procedure:
         (#) Program the Baud rate, Word length, Stop bits, Parity, Mode transmitter 
             or Mode receiver and hardware flow control values using the UART_Init()
            function.
         (#) Enable the half duplex mode using UART_HalfDuplexCmd() function.
         (#) Enable the UART using the UART_Cmd() function.
         -@- The RX pin is no longer used.
         -@- In Half-duplex mode the following bits must be kept cleared:
             (+@) EN  bits in the ISO7816CR register.
						 (+@) EN  bits in the ISO7816CR register.

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the UART's Half Duplex communication.
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.   
	          @arg UART0
						@arg UART1
  * @param  NewState: new state of the UART Communication.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_HalfDuplexCmd(CMSDK_UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the Half-Duplex mode by setting the OWE bit in the CR register */
    UARTx->CR |= UART_CR_OWE;
  }
  else
  {
    /* Disable the Half-Duplex mode by clearing the OWE bit in the CR register */
    UARTx->CR  &= (uint32_t)~((uint32_t)UART_CR_OWE);
  }
}

/**
  * @brief  Enables or disables the UART's transmitter or receiver.
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
            @arg UART0
						@arg UART1
  * @param  UART_Direction: specifies the UART direction.
  *          This parameter can be any combination of the following values:
  *         @arg UART_Mode_Tx: USART Transmitter
  *         @arg UART_Mode_Rx: USART Receiver
  * @param  NewState: new state of the USART transfer direction.
  *         This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void UART_HalfDuplex_DirectionModeCmd(CMSDK_UART_TypeDef* UARTx, uint32_t UART_DirectionMode)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_MODE(UART_DirectionMode));

  switch (UART_DirectionMode)
  {
    /* Enable the UART's transfer interface as Transmitter by setting the OWD bits 
       in the UART CR register */		
    case UART_Mode_Tx : 
			UARTx->CR |= UART_CR_OWD;
		  break;
    /* Disable the UART's transfer interface as Receiver by clearing OWD bits
       in the UART CR register */		
    case UART_Mode_Rx : 
			UARTx->CR &= (uint32_t)~UART_CR_OWD;
		  break;
    default : 
			break;
  }	
	
}
/**
  * @}
  */

/** @defgroup UART_Group12 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim   
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to configure the 
         UART Interrupts sources, Requests and check or clear the flags or pending bits status. 
         The user should identify which mode will be used in his application to 
         manage the communication: Polling mode, Interrupt mode.

 *** Polling Mode ***
 ====================
    [..] In Polling Mode, the UART communication can be managed by these flags:
         (#) UART_FLAG_RXNE: to indicate the status of the Receiver FIFO buffer non-empty flag
         (#) UART_FLAG_RXHF: to indicate the status of the Receiver FIFO buffer half-full flag.
         (#) UART_FLAG_RXF: to indicate the status of the Receiver FIFO buffer full flag.
         (#) UART_FLAG_TONE: to indicate the status of the Receiver FIFO buffer cleared timeout flag.
         (#) UART_FLAG_TOIDLE: to indicate the status of the Receiver FIFO buffer idel flag.
         (#) UART_FLAG_PERR: to indicate the status of the Parity error flag.
         (#) UART_FLAG_FERR: to indicate the status of the Frame error flag.
         (#) UART_FLAG_OVERR: to indicate the status of the Receiver FIFO buffer overflow flag.
         (#) UART_FLAG_TXE: to indicate the status of the Transmitter FIFO buffer empty flag.
         (#) UART_FLAG_TXHE: to indicate the status of the Transmitter FIFO buffer half-empty flag.
         (#) UART_FLAG_TXF: to indicate the status of the Transmitter FIFO buffer full flag.
         (#) UART_FLAG_TXEND: to indicate the status of the Transfer completed flag 
             bit status.
    [..] In this Mode it is advised to use the following functions:
         (+) FlagStatus UART_GetFlagStatus(CMSDK_UART_TypeDef* UARTx, uint16_t UART_FLAG).
         (+) void UART_ClearFlag(CMSDK_UART_TypeDef* UARTx, uint16_t UART_FLAG).

 *** Interrupt Mode ***
 ======================
    [..] In Interrupt Mode, the UART communication can be managed by 8 interrupt 
         sources 
         (+) Interrupt Source:
             (##) UART_IT_RXNEIE: specifies the interrupt source for Receiver FIFO buffer non-empty interrupt.
             (##) UART_IT_RXHFIE: specifies the interrupt source for Receiver FIFO buffer half-full interrupt.
             (##) UART_IT_RXFIE: specifies the interrupt source for Receiver FIFO buffer full interrupt.
             (##) UART_IT_TONEIE: specifies the interrupt source for Receive Receiver FIFO buffer cleared timeout interrupt.
             (##) UART_IT_TOIDLEIE: specifies the interrupt source for Receiver FIFO buffer idel interrupt.
             (##) UART_IT_PERRIE: specifies the interrupt source for Parity error interrupt.
             (##) UART_IT_FERRIE: specifies the interrupt source for Frame error interrupt.
             (##) UART_IT_OVERRIE: specifies the interrupt source for Receiver FIFO buffer overflow interrupt.
             (##) UART_IT_TXEIE: specifies the interrupt source for Transmitter FIFO buffer empty interrupt.
             (##) UART_IT_TXHEIE: specifies the interrupt source for Transmitter FIFO buffer half-empty interrupt.
             (##) UART_IT_TXFIE: specifies the interrupt source for Transmitter FIFO buffer full interrupt.
             (##) UART_IT_TXENDIE: specifies the interrupt source for Transfer completed interrupt
                  (Frame error, noise error, overrun error)
             -@@- Some parameters are coded in order to use them as interrupt 
                 source or as pending bits.
    [..] In this Mode it is advised to use the following functions:
         (+) UART_ITConfig(CMSDK_UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState)
         (+) FlagStatus UART_GetFlagStatus(CMSDK_UART_TypeDef* UARTx, uint16_t UART_FLAG).
         (+) void UART_ClearFlag(CMSDK_UART_TypeDef* UARTx, uint16_t UART_FLAG).

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified UART interrupts.
  * @param  UARTx: where x can be from 1 to 8 to select the UART peripheral.
  * @param  UART_IT: specifies the UART interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg UART_IT_RXNEIE: specifies the interrupt source for Receiver FIFO buffer non-empty interrupt.                                        
  *            @arg UART_IT_RXHFIE: specifies the interrupt source for Receiver FIFO buffer half-full interrupt.                                        
  *            @arg UART_IT_RXFIE: specifies the interrupt source for Receiver FIFO buffer full interrupt.                                              
  *            @arg UART_IT_TONEIE: specifies the interrupt source for Receive Receiver FIFO buffer cleared timeout interrupt.                          
  *            @arg UART_IT_TOIDLEIE: specifies the interrupt source for Receiver FIFO buffer idel interrupt.                                           
  *            @arg UART_IT_PERRIE: specifies the interrupt source for Parity error interrupt.                                                          
  *            @arg UART_IT_FERRIE: specifies the interrupt source for Frame error interrupt.                                                           
  *            @arg UART_IT_OVERRIE: specifies the interrupt source for Receiver FIFO buffer overflow interrupt.                                        
  *            @arg UART_IT_TXEIE: specifies the interrupt source for Transmitter FIFO buffer empty interrupt.                                          
  *            @arg UART_IT_TXHEIE: specifies the interrupt source for Transmitter FIFO buffer half-empty interrupt.                                    
  *            @arg UART_IT_TXFIE: specifies the interrupt source for Transmitter FIFO buffer full interrupt.                                           
  *            @arg UART_IT_TXENDIE: specifies the interrupt source for Transfer completed interrupt
  * @param  NewState: new state of the specified USARTx interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_ITConfig(CMSDK_UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState)
{

  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_CONFIG_IT(UART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    UARTx->IER |= UART_IT;
  }
  else
  {
    UARTx->IER &= ~UART_IT;
  }
}


/**
  * @brief  Checks whether the specified UART flag is set or not.
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
  * @param  UART_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg UART_FLAG_RXNE:  Receiver FIFO buffer non-empty flag.
  *            @arg UART_FLAG_RXHF:  Receiver FIFO buffer half-full flag.
  *            @arg UART_FLAG_RXF:   Receiver FIFO buffer full.
  *            @arg UART_FLAG_TONE:  Receiver FIFO buffer cleared timeout.
  *            @arg UART_FLAG_TOIDLE:  Receiver FIFO buffer idel.
  *            @arg UART_FLAG_PERR:  Parity error.
  *            @arg UART_FLAG_FERR:  Frame error.
  *            @arg UART_FLAG_OVERR: Receiver FIFO buffer overflow.
  *            @arg UART_FLAG_TXE:   Transmitter FIFO buffer empty.
  *            @arg UART_FLAG_TXHE:  Transmitter FIFO buffer half-empty.
  *            @arg UART_FLAG_TXF:   Transmitter FIFO buffer full.
  *            @arg UART_FLAG_TXEND: Transfer completed.
  * @retval The new state of UART_FLAG (SET or RESET).
  */
FlagStatus UART_GetFlagStatus(CMSDK_UART_TypeDef* UARTx, uint32_t UART_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_FLAG(UART_FLAG));
  
  if ((UARTx->SR & UART_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the UARTx's pending flags.
  * @param  UARTx: where x can be from 0 to 1 to select the USART peripheral. 
            @arg UART0
						@arg UART1
  * @param  UART_FLAG: specifies the flag to clear.
  *         This parameter can be any combination of the following values:
  *         @arg UART_CLEAR_FLAG_PERR:  Parity error.
  *         @arg UART_CLEAR_FLAG_FERR:  Frame error.
  *         @arg UART_CLEAR_FLAG_OVERR: Receiver FIFO buffer overflow.
  * @retval None
  */
void UART_ClearFlag(CMSDK_UART_TypeDef* UARTx, uint32_t UART_CLEAR_FLAG)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_CLEAR_FLAG(UART_CLEAR_FLAG));
     
  UARTx->SR = UART_CLEAR_FLAG;
}

/**
  * @brief  Checks whether the UATR interrupt has occurred or not.
  * @param  UARTx: where x can be from 0 to 1 to select the USART peripheral. 
            @arg UART0
						@arg UART1
  * @param  UART_IT: specifies the UART interrupt source to check. 
  *         This parameter can be one of the following values:
  *            @arg UART_IT_RXNEIE: specifies the interrupt source for Receiver FIFO buffer non-empty interrupt.                                        
  *            @arg UART_IT_RXHFIE: specifies the interrupt source for Receiver FIFO buffer half-full interrupt.                                        
  *            @arg UART_IT_RXFIE: specifies the interrupt source for Receiver FIFO buffer full interrupt.                                              
  *            @arg UART_IT_TONEIE: specifies the interrupt source for Receive Receiver FIFO buffer cleared timeout interrupt.                          
  *            @arg UART_IT_TOIDLEIE: specifies the interrupt source for Receiver FIFO buffer idel interrupt.                                           
  *            @arg UART_IT_PERRIE: specifies the interrupt source for Parity error interrupt.                                                          
  *            @arg UART_IT_FERRIE: specifies the interrupt source for Frame error interrupt.                                                           
  *            @arg UART_IT_OVERRIE: specifies the interrupt source for Receiver FIFO buffer overflow interrupt.                                        
  *            @arg UART_IT_TXEIE: specifies the interrupt source for Transmitter FIFO buffer empty interrupt.                                          
  *            @arg UART_IT_TXHEIE: specifies the interrupt source for Transmitter FIFO buffer half-empty interrupt.                                    
  *            @arg UART_IT_TXFIE: specifies the interrupt source for Transmitter FIFO buffer full interrupt.                                           
  *            @arg UART_IT_TXENDIE: specifies the interrupt source for Transfer completed interrupt
  * @retval The new state of UART_IT (SET or RESET).
  */

ITStatus UART_GetITStatus(CMSDK_UART_TypeDef* UARTx,uint32_t UART_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_GET_IT(UART_IT));

  /* Get the UART_IT enable bit status */
  enablestatus = (uint32_t)(UARTx->IER & UART_IT); 

  /* Check the status of the specified ADC interrupt */
  if (((uint32_t)(UARTx->SR & UART_IT) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    /* UART_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* UART_IT is reset */
    bitstatus = RESET;
  }
  /* Return the UART_IT status */
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
