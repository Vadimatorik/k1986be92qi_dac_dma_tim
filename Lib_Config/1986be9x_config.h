/**
  ******************************************************************************
  * @file    Examples\1986BE91_EVAL\1986be9x_config.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    10/07/2010
  * @brief   Library configuration file.
  ******************************************************************************
  * <br><br>
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, PHYTON SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 Phyton</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9x_CONFIG_H
#define __1986BE9x_CONFIG_H

#include "1986BE9x_lib.h"

/* Uncomment the line(s) below to define used JTAG port(s). Leave all commented
 * if there is no JTAG ports */
#define USE_JTAG_A
/* #define USE_JTAG_B */

/* Target system parameters */
/* RST_CLK generators frequencies in HZ */
#define HSI_Value       ((uint32_t)8000000)
#define HSE_Value       ((uint32_t)8000000)
#define LSI_Value       ((uint32_t)40000)
#define LSE_Value       ((uint32_t)32768)

/* RST_CLK frequencies startup timeouts settings */
#define HSEonTimeOut    ((uint16_t)0x0600)
#define LSEonTimeOut    ((uint16_t)0x0600)
#define HSIonTimeOut    ((uint16_t)0x0600)
#define LSIonTimeOut    ((uint16_t)0x0600)
#define PLLCPUonTimeOut ((uint16_t)0x0600)
#define PLLUSBonTimeOut ((uint16_t)0x0600)

#define FLASH_PROG_FREQ_MHZ                     (8.0)

/* DMA configuration parameters */
/* Number of DMA channels to use */
#define DMA_Channels_Number   32          /* This parameter is in range 1..32 */

/* Alternate Control Data Structure Usage */
/* This parameter can be a value of:
    0 = DMA_ALternateDataDisabled;
    1 = DMA_ALternateDataEnabled; */
/*#define DMA_AlternateData   0 */          /* DMA_AlternateDataDisabled */
#define DMA_AlternateData   1             /* DMA_AlternateDataEnabled */

/* Parameter run-time check support ------------------------------------------*/

/* Select one of the following values of USE_ASSERT_INFO macro to control
   parameter checking in the Standard Peripheral Library drivers:
     0 - no parameter checks ("assert_param" macro is disabled);
     1 - check enabled, source file ID and line number are available;
     2 - check enabled, source file ID, line number and checking expression
         (as string) are available (increased code size).
*/
#define USE_ASSERT_INFO    0
/* #define USE_ASSERT_INFO    1 */
/* #define USE_ASSERT_INFO    2 */

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed user's function
  *   which gets the source file ID (see 1986be9x_lib.h), line number and
  *   expression text (if USE_ASSERT_INFO == 2) of the call that failed. That
  *   function should not return. If expr is true, nothing is done.
  * @retval None
  */
#if (USE_ASSERT_INFO == 0)
  #define assert_param(expr) ((void)0)
#elif (USE_ASSERT_INFO == 1)
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed(ASSERT_INFO_FILE_ID, __LINE__))
  void assert_failed(uint32_t file_id, uint32_t line);
#elif (USE_ASSERT_INFO == 2)
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed(ASSERT_INFO_FILE_ID, __LINE__, #expr))
  void assert_failed(uint32_t file_id, uint32_t line, const uint8_t* expr);
#else
  #error "Unsupported USE_ASSERT_INFO level"
#endif /* USE_ASSERT_INFO */

#endif /* __1986BE9x_CONFIG_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_config.h */

