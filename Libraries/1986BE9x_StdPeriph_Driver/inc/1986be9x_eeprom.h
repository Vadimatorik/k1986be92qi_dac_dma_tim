/**
  ******************************************************************************
  * @file    1986BE9x_eeprom.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    11/06/2010
  * @brief   This file contains all the functions prototypes for the EEPROM
  *          firmware library.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, PHYTON SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 Phyton</center></h2>
  ******************************************************************************
  * FILE 1986BE9x_eeprom.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9x_EEPROM_H
#define __1986BE9x_EEPROM_H

/* Includes ------------------------------------------------------------------*/
#include "1986BE9x.h"

/** @addtogroup __1986BE9x_StdPeriph_Driver 1986BE9x Standard Peripherial Driver
  * @{
  */

/** @addtogroup EEPROM
  * @{
  */

/** @defgroup EEPROM_Exported_Types EEPROM Exported Types
  * @{
  */

/** @} */ /* End of group EEPROM_Exported_Types */

/** @defgroup EEPROM_Exported_Constants EEPROM Exported Constants
  * @{
  */

/** @defgroup EEPROM_Latency EEPROM Latency
  * @{
  */

#define EEPROM_Latency_0                ((uint32_t)0x00000000)  /*!< EEPROM 0 Latency cycle  (MCU Clock up to  25 MHz) */
#define EEPROM_Latency_1                ((uint32_t)0x00000008)  /*!< EEPROM 1 Latency cycle  (MCU Clock up to  50 MHz) */
#define EEPROM_Latency_2                ((uint32_t)0x00000010)  /*!< EEPROM 2 Latency cycles (MCU Clock up to  75 MHz) */
#define EEPROM_Latency_3                ((uint32_t)0x00000018)  /*!< EEPROM 3 Latency cycles (MCU Clock up to 100 MHz) */
#define EEPROM_Latency_4                ((uint32_t)0x00000020)  /*!< EEPROM 4 Latency cycles (MCU Clock up to 125 MHz) */
#define EEPROM_Latency_5                ((uint32_t)0x00000028)  /*!< EEPROM 5 Latency cycles (MCU Clock up to 150 MHz) */
#define EEPROM_Latency_6                ((uint32_t)0x00000030)  /*!< EEPROM 6 Latency cycles (MCU Clock up to 175 MHz) */
#define EEPROM_Latency_7                ((uint32_t)0x00000038)  /*!< EEPROM 7 Latency cycles (MCU Clock up to 200 MHz) */

/** @} */ /* End of group EEPROM_Latency */

/** @defgroup  EEPROM_Bank EEPROM Bank Selector
  * @{
  */

#define EEPROM_Main_Bank_Select         ((uint32_t)0x00000000)  /*!< EEPROM Main Bank Selector */
#define EEPROM_Info_Bank_Select         ((uint32_t)0x00000001)  /*!< EEPROM Information Bank Selector */
#define EEPROM_All_Banks_Select         ((uint32_t)0x00000002)  /*!< EEPROM All Banks Selector */

#define IS_EEPROM_BANK_SELECTOR(SEL)    (((SEL) == EEPROM_Main_Bank_Select) || \
                                         ((SEL) == EEPROM_Info_Bank_Select))

#define IS_EEPROM_ERASE_SELECTOR(SEL)   (((SEL) == EEPROM_Main_Bank_Select) || \
                                         ((SEL) == EEPROM_All_Banks_Select))

/** @} */ /* End of group EEPROM_Bank */

/** @} */ /* End of group EEPROM_Exported_Constants */

/** @defgroup EEPROM_Exported_Macros EEPROM Exported Macros
  * @{
  */

/** @} */ /* End of group EEPROM_Exported_Macros */

/** @defgroup EEPROM_Exported_Functions EEPROM Exported Functions
  * @{
  */

/** @defgroup EEPROM_Functions_allowed_to_be_located_in_Flash Functions allowed to be located in Flash
  * @{
  */

/** @} */ /* End of group EEPROM_Functions_allowed_to_be_located_in_Flash */

/** @defgroup EEPROM_Functions_not_allowed_to_be_located_in_Flash Functions not allowed to be located in Flash
  * @{
  */

#if defined ( __ICCARM__ )

  #define __RAMFUNC      __ramfunc

#else

  #define __RAMFUNC

#endif

__RAMFUNC uint8_t EEPROM_ReadByte(uint32_t Address, uint32_t BankSelector);
__RAMFUNC uint16_t EEPROM_ReadHalfWord(uint32_t Address, uint32_t BankSelector);
__RAMFUNC uint32_t EEPROM_ReadWord(uint32_t Address, uint32_t BankSelector);
__RAMFUNC void EEPROM_ErasePage(uint32_t Address, uint32_t BankSelector);
__RAMFUNC void EEPROM_EraseAllPages(uint32_t BankSelector);
__RAMFUNC void EEPROM_ProgramByte(uint32_t Address, uint32_t BankSelector, uint32_t Data);
__RAMFUNC void EEPROM_ProgramHalfWord(uint32_t Address, uint32_t BankSelector, uint32_t Data);
__RAMFUNC void EEPROM_ProgramWord(uint32_t Address, uint32_t BankSelector, uint32_t Data);

#ifdef __CMCARM__

#pragma ramfunc EEPROM_ReadByte, EEPROM_ReadHalfWord, EEPROM_ReadWord
#pragma ramfunc EEPROM_ErasePage, EEPROM_EraseAllPages
#pragma ramfunc EEPROM_ProgramByte, EEPROM_ProgramHalfWord, EEPROM_ProgramWord

#endif

/** @} */ /* End of group EEPROM_Functions_not_allowed_to_be_located_in_Flash */

/** @} */ /* End of group EEPROM_Exported_Functions */

/** @} */ /* End of group EEPROM */

/** @} */ /* End of group __1986BE9x_StdPeriph_Driver */

#endif /* __1986BE9x_EEPROM_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_eeprom.h */

