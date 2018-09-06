/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_conf.h 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Library configuration file.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_CONF_H
#define __STM32F10x_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "global_config.h"

/* Uncomment/Comment the line below to enable/disable peripheral header file inclusion */
#if defined __INIT_ADC__ && __INIT_ADC__ == TRUE
#include "stm32f10x_adc.h"
#endif
#if defined __INIT_BKP__ && __INIT_BKP__ == TRUE
#include "stm32f10x_bkp.h"
#endif
#if defined __INIT_CAN__ && __INIT_CAN__ == TRUE
#include "stm32f10x_can.h"
#endif
#if defined __INIT_CEC__ && __INIT_CEC__ == TRUE
#include "stm32f10x_cec.h"
#endif
#if defined __INIT_CRC__ && __INIT_CRC__ == TRUE
#include "stm32f10x_crc.h"
#endif
#if defined __INIT_DAC__ && __INIT_DAC__ == TRUE
#include "stm32f10x_dac.h"
#endif
#if defined __INIT_DBGMCU__ && __INIT_DBGMCU__ == TRUE
#include "stm32f10x_dbgmcu.h"
#endif
#if defined __INIT_DMA__ && __INIT_DMA__ == TRUE
#include "stm32f10x_dma.h"
#endif
#if defined __INIT_EXIT__ && __INIT_EXIT__ == TRUE
#include "stm32f10x_exti.h"
#endif
#if defined __INIT_FLASH__ && __INIT_FLASH__ == TRUE
#include "stm32f10x_flash.h"
#endif
#if defined __INIT_FSMC__ && __INIT_FSMC__ == TRUE
#include "stm32f10x_fsmc.h"
#endif
#if defined __INIT_GPIO__ && __INIT_GPIO__ == TRUE
#include "stm32f10x_gpio.h"
#endif
#if defined __INIT_I2C__ && __INIT_I2C__ == TRUE
#include "stm32f10x_i2c.h"
#endif
#if defined __INIT_IWDG__ && __INIT_IWDG__ == TRUE
#include "stm32f10x_iwdg.h"
#endif
#if defined __INIT_PWR__ && __INIT_PWR__ == TRUE
#include "stm32f10x_pwr.h"
#endif
#if defined __INIT_RCC__ && __INIT_RCC__ == TRUE
#include "stm32f10x_rcc.h"
#endif
#if defined __INIT_RTC__ && __INIT_RTC__ == TRUE
#include "stm32f10x_rtc.h"
#endif
#if defined __INIT_SDIO__ && __INIT_SDIO__ == TRUE
#include "stm32f10x_sdio.h"
#endif
#if defined __INIT_SPI__ && __INIT_SPI__ == TRUE
#include "stm32f10x_spi.h"
#endif
#if defined __INIT_TIM__ && __INIT_TIM__ == TRUE
#include "stm32f10x_tim.h"
#endif
#if defined __INIT_USART__ && __INIT_USART__ == TRUE
#include "stm32f10x_usart.h"
#endif
#if defined __INIT_WWDG__ && __INIT_WWDG__ == TRUE
#include "stm32f10x_wwdg.h"
#endif

#include "misc.h" /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1 */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __STM32F10x_CONF_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/



