/**
  ******************************************************************************
  * @file    system_pt32f0xx.c
  * @author  应用开发团队
  * @version V1.0.0
  * @date    2020/04/28
  * @brief   
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
  *
  *
  *
  *
  * 
  *=============================================================================
  *=============================================================================
  *        System Clock source                    | HSIRC
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                             | 24000000
  *-----------------------------------------------------------------------------
  *        HSCLK(Hz)                              | 24000000
  *-----------------------------------------------------------------------------
  *        HCLK Prescaler                         | 1
  *-----------------------------------------------------------------------------
  *        PCLK Prescaler                         | 1
  *-----------------------------------------------------------------------------
  *        HCLK Frequency(Hz)                     | 24000000
  *----------------------------------------------------------------------------
  *        PCLK Frequency(Hz)                     | 24000000
  *-----------------------------------------------------------------------------
  *        Flash Latency(WS)                      | 1
  *-----------------------------------------------------------------------------                                                                                               
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

/** @addtogroup CMSIS                                    
  * @{                                                   
  */                                                     
                                                         
/** @addtogroup pt32f0xx_system                         
  * @{                                                   
  */                                                     
                                                         
/** @addtogroup PT32F0xx_System_Private_Includes        
  * @{                                                   
  */                                                     
                                                         
#include "pt32f0xx.h"                                   
                                                         
/**                                                      
  * @}                                                   
  */                                                     
                                                         
/** @addtogroup PT32F0xx_System_Private_TypesDefinitions
  * @{                                                   
  */                                                     
                                                         
/**                                                      
  * @}                                                   
  */                                                     
                                                         
/** @addtogroup PT32F0xx_System_Private_Defines         
  * @{                                                   
  */    
	
/**                                                      
  * @}                                                   
  */ 



                                                         
/** @addtogroup PT32F0xx_System_Private_Macros          
  * @{                                                   
  */ 

//<<< Use Configuration Wizard in Context Menu >>>

/*--------------------- Clock Configuration ----------------------------------
//
//    <h> High Speed Internal RC Oscillator Configuration (24M)
//      <q0>    IOSC_24M Enable
//                <i> Default = ENABLE
//    </h>
//
//    <h> High Speed External Crystal Oscillator Configuration (4~25M)
//      <e1>    EOSC_CLK Enable
//                <i> Default = DISABLE
//        <o2>    EOSC_CLK Select
//                <0=> Crystal
//                <1=> Exterl Clk Input
//           <o3>    Frequency Rang Select
//                   <0=> 4-10MHz
//                   <1=> 10MHz-25MHz
//                   <i> Configure when using external crystal as clock source
//      </e>
//    </h>
//
//    <h> Frequency Double Clock Configuration
//      <e4>    FD_CLK Enable
//                <i> Default  = DISABLE
//        <o5>  Frequency Double Clock Source
//                <0=> Internal RC_24M
//                <1=> External Crystal
//                <2=> Internal RC_32K
//                <i> Default Frequency Double clock source = Internal RC
//                <i> Frequency Double Clock = Source clock * 2
//      </e>
//    </h>
//    <h> SystemCoreClock Configuration (HCLK)
//      <o6>    SystemCoreClock Source
//                <0=> Internal RC_24M
//                <1=> External Clock
//                <2=> Frequency Double Clock
//                <3=> Internal RC_32K
//                <i> Default SystemCoreClock source = Internal RC_24M
//      <o7>    SystemCoreClock Source Divider
//                <0=> 1
//                <1=> 2
//                <2=> 4
//                <3=> 8
//                <4=> 16
//                <5=> 32
//                <i> Default SystemCoreClock source divider = 1
//      <o8>    PCLK Divider
//                <0=> 1
//                <1=> 2
//                <2=> 4
//                <3=> 8
//                <4=> 16
//                <5=> 32
//                <i> Default PCLK divider = 1
//    </h>
//
//    <h> FLASH Configuration
//      <o9>   Wait state
//                <0=> 0 WS
//                <1=> 1 WS
//                <2=> 2 WS
//                <i> 0 WS:  1 KHz <= HCLK <= 20 MHz
//                <i> 1 WS: 20 MHz <  HCLK <= 40 MHz
//                <i> 2 WS: 40 MHz <  HCLK <= 60 MHz
//    </h>
//
//    <h> MCO Output Configuration
//      <e10>    MCO_OUTPUT Enable
//                <i> Default = DISABLE ,PA8 output systemclock
//        <o11>    MCO Output Pin Select
//                <0=> PA8
//                <1=> PB2
//        <o12>   MCO Divider
//                <0=> 1
//                <1=> 2
//                <2=> 4
//                <3=> 8
//                <4=> 16
*/

#define IOSC_24M_ENABLE               (1)     /*!< 0: DISABLE,  1: ENABLE                                               */
#define EOSC_CLK_ENABLE               (0)     /*!< 0: DISABLE,  1: ENABLE                                               */  
#define EOSC_CLK_SEL                  (0)     /*!< 0: CRYSATL,  1: EXTERL CLK                                               */      
#define EOSC_FRE_SEL                  (1)     /*!< 0: 4-10MHz,  1: 10M-20MHz                                            */     
#define FD_CLK_ENABLE                 (0)     /*!< 0: DISABLE,  1: ENABLE                                               */
#define FD_CLK_SRC                    (1)     /*!< 0: IOCS_24M, 1: EXT_CLK  2:IOSC_32K                                  */
#define HCLK_SRC                      (0)     /*!< 0: IOCS_24M, 1: EXT_CLK  2:FD_CLK   3:IOSC_32K                       */
#define HCLK_DIV                      (0)     /*!< 0: DIV1,     1: DIV2,    2: DIV4,   3: DIV8,   4: DIV16,  5: DIV32    */
#define PCLK_DIV                      (0)     /*!< 0: DIV1,     1: DIV2,    2: DIV4,   3: DIV8,   4: DIV16,  5: DIV32    */
#define FLASH_Latency                 (1)     /*!< 0: 0 WS,     1: 1 WS,    2: 2 WS,                                     */
#define MCO_ENABLE                    (0)     /*!< 0: DISABLE,  1: ENABLE                                               */  
#define MCO_PINSEL                    (0)     /*!< 0: PA8,      1: PB2,                                                */
#define MCO_DIV                       (1)     /*!< 0: DIV1,     1: DIV2,    2: DIV4,   3: DIV8,   4: DIV16,  5: DIV32    */       


/**                                                      
  * @}                                                   
  */                                                     
                                                         
/** @addtogroup PT32F0xx_System_Private_Variables       
  * @{                                                   
  */     
uint32_t SystemCoreClock    = 24000000;
/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */
	
/** @addtogroup STM32F0xx_System_Private_Functions
  * @{
  */

/**
  * @brief  
  *         
  *         
  * @param  None
  * @retval None
  */	


void Wait_ClockReady(void)
{
  volatile int delay;
	
	for (delay=0;delay<200;delay++);
}


/**
  * @brief  
  *         
  *         
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
   uint32_t tmpreg = 0;
  /* Timeout for crystal oscillator Vibration*/

#if (EOSC_CLK_ENABLE == 1)
	
 #if (EOSC_CLK_SEL == 0)
  uint32_t timeout = EOSC_TIMEOUT; 	
  /* PF0 used as CRYSTAL_IN,PF1 used as CRYSTAL_OUT */
	CMSDK_PF->ALTFUNCSET &= ~(GPIO_AFS1_AFS0|GPIO_AFS1_AFS1);
	CMSDK_PF->ALTFUNCSET |= (GPIO_AF_0 << (GPIO_PinSource0*4));	
	CMSDK_PF->ALTFUNCSET |= (GPIO_AF_0 << (GPIO_PinSource1*4));
  /* Set crystal feedback resistance as 200Kohm  */
	CMSDK_ANAMIX->EOSC_CON2 &= ~ANAMIX_EOSCCON2_EOSCFBRES;
	CMSDK_ANAMIX->EOSC_CON2 |= ANAMIX_EOSCCON2_EOSCFBRES_220K;
  
  if(EOSC_FRE_SEL == 0)
	CMSDK_ANAMIX->EOSC_CON2 &= ~ANAMIX_EOSCCON1_EOSCRANG;
	
  /* Enable extern crystal */	
	CMSDK_ANAMIX->EOSC_CON1 &= ~ANAMIX_EOSCCON1_EXCLKEN;
	CMSDK_ANAMIX->EOSC_CON1 |= ANAMIX_EOSCCON1_EOSCEN;
	/* Enable extern crystal */	
  while(((CMSDK_ANAMIX->EOSC_CON1 & ANAMIX_EOSCCON1_EOSCWORK_READY) == 0)&& (timeout != 0))
		{
      timeout--;
		}			
 #endif
		
 #if (EOSC_CLK_SEL == 1)
		
	CMSDK_ANAMIX->EOSC_CON1  &= ~ANAMIX_EOSCCON1_EOSCEN;
	CMSDK_ANAMIX->EOSC_CON1 |= ANAMIX_EOSCCON1_EXCLKEN;		

 #endif		
		
#else
		
  /* Disable external crystal */	
  CMSDK_ANAMIX->EOSC_CON1 &= ~(ANAMIX_EOSCCON1_EOSCEN | ANAMIX_EOSCCON1_EXCLKEN);
		

#endif	

#if (FD_CLK_ENABLE == 1)
  CMSDK_ANAMIX->FD_CON &= ~ANAMIX_FDCON_FDEN;	
  #if (FD_CLK_SRC == 0 )
    #if (IOSC_24M_ENABLE == 0)
      #error "FD_CLK clock source issue: IOSC_24M has not been enabled"
    #else
		  /* Select IOSC_24M as the multiplier clock source   */	
			 CMSDK_SYSCON->SYSCLK &= ~SYSCON_SYSCLK_FDCLKSEL;
		   CMSDK_SYSCON->SYSCLK |= SYSCON_SYSCLK_FDCLKSEL_24MIOSC;
    #endif
  #endif
		
  #if (FD_CLK_SRC == 1 )
	  #if (EOSC_CLK_ENABLE == 0)
		  #error "FD_CLK clock source issue: EOSC_CLK has not been enabled"
		#else	  
		  /* Select external clock as the multiplier clock source   */	
			 CMSDK_SYSCON->SYSCLK &= ~SYSCON_SYSCLK_FDCLKSEL;
		   CMSDK_SYSCON->SYSCLK |= SYSCON_SYSCLK_FDCLKSEL_EXTCLK;
		#endif
  #endif
	
  #if (FD_CLK_SRC == 2 )
		  /* Select IOSC_32K as the multiplier clock source   */	
			 CMSDK_SYSCON->SYSCLK &= ~SYSCON_SYSCLK_FDCLKSEL;
		   CMSDK_SYSCON->SYSCLK |= SYSCON_SYSCLK_FDCLKSEL_32KIOSC;
  #endif		
  CMSDK_ANAMIX->FD_CON |= ANAMIX_FDCON_FDEN;	 		
#else
  CMSDK_ANAMIX->FD_CON &= ~ANAMIX_FDCON_FDEN;		    			
#endif

	/* Sets the code latency value.*/	
  tmpreg = CMSDK_FLASH->ACR;
  tmpreg &= (uint32_t) (~((uint32_t)FLASH_ACR_LATENCY));
  tmpreg |= FLASH_Latency;
  CMSDK_FLASH->ACR = tmpreg;
	
#if (HCLK_SRC == 0 )	 
  #if (IOSC_24M_ENABLE == 0)
	  #error "System clock source issue: IOSC_24M has not been enabled"
  #else		 	 
    CMSDK_SYSCON->SYSCLK &= ~SYSCON_SYSCLK_SYSCLKSEL;
	  CMSDK_SYSCON->SYSCLK |= SYSCON_SYSCLK_SYSCLKSEL_24MIOSC;	 
  #endif 
#endif

#if (HCLK_SRC == 1 )	 
  #if (EOSC_CLK_ENABLE == 0)
	  #error "System clock source issue: EOSC_CLK has not been enabled"
  #else
    CMSDK_SYSCON->SYSCLK &= ~SYSCON_SYSCLK_SYSCLKSEL;
	  CMSDK_SYSCON->SYSCLK |= SYSCON_SYSCLK_SYSCLKSEL_EXTCLK;	 	
  #endif
#endif

#if (HCLK_SRC == 2 )	 
  #if (FD_CLK_ENABLE == 0)
	  #error "System clock source issue: FD_CLK_ENABLE has not been enabled"
  #else		 	 
    CMSDK_SYSCON->SYSCLK &= ~SYSCON_SYSCLK_SYSCLKSEL;
	  CMSDK_SYSCON->SYSCLK |= SYSCON_SYSCLK_SYSCLKSEL_DCLK;	 
 #endif
 
#endif

#if (HCLK_SRC == 3 )	 	 
    CMSDK_SYSCON->SYSCLK &= ~SYSCON_SYSCLK_SYSCLKSEL;
	  CMSDK_SYSCON->SYSCLK |= SYSCON_SYSCLK_SYSCLKSEL_32KIOSC;		 
#endif
  /* set HCLK prescaler */	
  CMSDK_SYSCON->SYSCLK &= ~SYSCON_SYSCLK_HCLKDIV;
	CMSDK_SYSCON->SYSCLK |= HCLK_DIV; 
  /* set PCLK prescaler */ 
  CMSDK_SYSCON->SYSCLK &= ~SYSCON_SYSCLK_PCLKDIV;
	CMSDK_SYSCON->SYSCLK |= PCLK_DIV; 	 	 
  if((CMSDK_SYSCON->SYSCLK & SYSCON_SYSCLK_SYSCLKSEL) != HCLK_SRC)
	{
    /* clock switch fail */ 
		while(1);		
	}

#if (IOSC_24M_ENABLE == 1)
    /* enable osc 24M */	
  CMSDK_ANAMIX->IOSC_24M_CON |= ANAMIX_IOSC24MCON_IOSCEN;			
#else	
    /* disable osc 24M */	
  CMSDK_ANAMIX->IOSC_24M_CON &= ~ANAMIX_IOSC24MCON_IOSCEN;				
#endif
	 
#if (MCO_ENABLE == 1)	 
	 
    /* Select Alternate function as MCO pin begin */
	 #if (MCO_PINSEL == 0)
	 
	 CMSDK_PA->ALTFUNCSET1 |= (1<<0);
	 
   #endif	 
	 
	 #if (MCO_PINSEL == 1)
	 
	 CMSDK_PB->ALTFUNCSET |= (2<<8);
	 
   #endif	 	
	  /* Select Alternate function as MCO pin END */		 
CMSDK_ANAMIX->MCO_DIV_CON &= ~ANAMIX_MCODIVCON;
CMSDK_ANAMIX->MCO_DIV_CON |= MCO_DIV; 
	 
#endif
	 
	 
}

//<<< end of configuration section >>>
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
