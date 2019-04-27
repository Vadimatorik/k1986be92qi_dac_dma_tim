/**
  ******************************************************************************
  * @file    1986BE9x_eeprom.c
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    11/06/2010
  * @brief   This file contains all the EEPROM firmware functions.
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
  * FILE 1986BE9x_eeprom.c
  */

/* Includes ------------------------------------------------------------------*/
#include "1986BE9x_eeprom.h"
#include "1986BE9x_config.h"

#define ASSERT_INFO_FILE_ID FILEID__1986BE9X_EEPROM_C

/** @addtogroup __1986BE9x_StdPeriph_Driver 1986BE9x Standard Peripherial Driver
  * @{
  */

/** @addtogroup EEPROM
  * @{
  */

/** @defgroup EEPROM_Private_Defines EEPROM Private Defines
  * @{
  */

#define EEPROM_REG_ACCESS_KEY           ((uint32_t)0x8AAA5551)

/** @} */ /* End of group EEPROM_Private_Defines */

/** @defgroup EEPROM_Private_Macros EEPROM Private Macros
  * @{
  */

#define IS_TWO_BYTE_ALLIGNED(ADDR)      ((ADDR & 1) == 0)
#define IS_FOUR_BYTE_ALLIGNED(ADDR)     ((ADDR & 3) == 0)

#define DELAY_LOOP_CYCLES               (8UL)
#define GET_US_LOOPS(N)                 ((uint32_t)((float)(N) * FLASH_PROG_FREQ_MHZ / DELAY_LOOP_CYCLES))

/** @} */ /* End of group EEPROM_Private_Macros */

/** @defgroup EEPROM_Private_Functions EEPROM Private Functions
  * @{
  */

__RAMFUNC static void ProgramDelay(uint32_t Loops);

#ifdef __CMCARM__

#pragma ramfunc ProgramDelay

#endif

/**
  * @brief  Program delay.
  * @param  Loops: Number of the loops.
  * @retval None.
  */
__RAMFUNC static void ProgramDelay(uint32_t Loops)
{
  volatile uint32_t i = Loops;
  for (; i > 0; i--)
  {
  }
}

/**
  * @brief  Reads the 8-bit EEPROM memory value.
  * @param  Address: The EEPROM memory byte address.
  * @param  BankSelector: Selects EEPROM Bank (Main Bank or Information Bank).
  *         This parameter can be one of the following values:
  *           @arg EEPROM_Main_Bank_Select:      The EEPROM Main Bank selector.
  *           @arg EEPROM_Info_Bank_Select:      The EEPROM Information Bank selector.
  * @retval The selected EEPROM memory value.
  */
__RAMFUNC uint8_t EEPROM_ReadByte(uint32_t Address, uint32_t BankSelector)
{
  uint32_t Data;
  uint32_t Command;
  uint32_t Shift;

  assert_param(IS_EEPROM_BANK_SELECTOR(BankSelector));

  EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
  Command = (EEPROM->CMD & EEPROM_CMD_Delay_Msk) | EEPROM_CMD_CON;
  Command |= (BankSelector == EEPROM_Info_Bank_Select) ? EEPROM_CMD_IFREN : 0;
  EEPROM->CMD = Command;
  EEPROM->ADR = Address;
  EEPROM->CMD = Command | EEPROM_CMD_XE | EEPROM_CMD_YE | EEPROM_CMD_SE;
  EEPROM->DO;   /* Idle Reading for Delay */
  EEPROM->DO;   /* Idle Reading for Delay */
  EEPROM->DO;   /* Idle Reading for Delay */
  Data = EEPROM->DO;
  Command &= EEPROM_CMD_Delay_Msk;
  EEPROM->CMD = Command;
  EEPROM->KEY = 0;

  Shift = (Address & 3) * 8;
  Data >>= Shift;
  return Data;
}

/**
  * @brief  Reads the 16-bit EEPROM memory value.
  * @param  Address: The EEPROM memory half word address (two byte aligned).
  * @param  BankSelector: Selects EEPROM Bank (Main Bank or Information Bank).
  *         This parameter can be one of the following values:
  *           @arg EEPROM_Main_Bank_Select:      The EEPROM Main Bank selector.
  *           @arg EEPROM_Info_Bank_Select:      The EEPROM Information Bank selector.
  * @retval The selected EEPROM memory value.
  */
__RAMFUNC uint16_t EEPROM_ReadHalfWord(uint32_t Address, uint32_t BankSelector)
{
  uint32_t Data;
  uint32_t Command;
  uint32_t Shift;

  assert_param(IS_EEPROM_BANK_SELECTOR(BankSelector));
  assert_param(IS_TWO_BYTE_ALLIGNED(Address));

  EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
  Command = (EEPROM->CMD & EEPROM_CMD_Delay_Msk) | EEPROM_CMD_CON;
  Command |= (BankSelector == EEPROM_Info_Bank_Select) ? EEPROM_CMD_IFREN : 0;
  EEPROM->CMD = Command;
  EEPROM->ADR = Address;
  EEPROM->CMD = Command | EEPROM_CMD_XE | EEPROM_CMD_YE | EEPROM_CMD_SE;
  EEPROM->DO;   /* Idle Reading for Delay */
  EEPROM->DO;   /* Idle Reading for Delay */
  EEPROM->DO;   /* Idle Reading for Delay */
  Data = EEPROM->DO;
  Command &= EEPROM_CMD_Delay_Msk;
  EEPROM->CMD = Command;
  EEPROM->KEY = 0;

  Shift = (Address & 2) * 8;
  Data >>= Shift;
  return Data;
}

/**
  * @brief  Reads the 32-bit EEPROM memory value.
  * @param  Address: The EEPROM memory word address (four byte aligned).
  * @param  BankSelector: Selects EEPROM Bank (Main Bank or Information Bank).
  *         This parameter can be one of the following values:
  *           @arg EEPROM_Main_Bank_Select:      The EEPROM Main Bank selector.
  *           @arg EEPROM_Info_Bank_Select:      The EEPROM Information Bank selector.
  * @retval The selected EEPROM memory value.
  */
__RAMFUNC uint32_t EEPROM_ReadWord(uint32_t Address, uint32_t BankSelector)
{
  uint32_t Command;
  uint32_t Data;

  assert_param(IS_EEPROM_BANK_SELECTOR(BankSelector));
  assert_param(IS_FOUR_BYTE_ALLIGNED(Address));

  EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
  Command = (EEPROM->CMD & EEPROM_CMD_Delay_Msk) | EEPROM_CMD_CON;
  Command |= (BankSelector == EEPROM_Info_Bank_Select) ? EEPROM_CMD_IFREN : 0;
  EEPROM->CMD = Command;
  EEPROM->ADR = Address;
  EEPROM->CMD = Command | EEPROM_CMD_XE | EEPROM_CMD_YE | EEPROM_CMD_SE;
  EEPROM->DO;   /* Idle Reading for Delay */
  EEPROM->DO;   /* Idle Reading for Delay */
  EEPROM->DO;   /* Idle Reading for Delay */
  Data = EEPROM->DO;
  Command &= EEPROM_CMD_Delay_Msk;
  EEPROM->CMD = Command;
  EEPROM->KEY = 0;
  return Data;
}

/**
  * @brief  Erases one page of the selected EEPROM memory bank.
  * @param  Address: Page Address in the EEPROM memory.
  * @param  BankSelector: Selects EEPROM Bank (Main Bank or Information Bank).
  *         This parameter can be one of the following values:
  *           @arg EEPROM_Main_Bank_Select:      The EEPROM Main Bank selector.
  *           @arg EEPROM_Info_Bank_Select:      The EEPROM Information Bank selector.
  * @retval None
  */
__RAMFUNC void EEPROM_ErasePage(uint32_t Address, uint32_t BankSelector)
{
  uint32_t Command;
  uint32_t Offset;

  assert_param(IS_EEPROM_BANK_SELECTOR(BankSelector));

  EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
  Command = (EEPROM->CMD & EEPROM_CMD_Delay_Msk) | EEPROM_CMD_CON;
  Command |= (BankSelector == EEPROM_Info_Bank_Select) ? EEPROM_CMD_IFREN : 0;
  EEPROM->CMD = Command;

  for (Offset = 0; Offset < (4 << 2); Offset += 4)
  {
    EEPROM->ADR = Address + Offset;             /* Page Address */
    EEPROM->DI = 0;
    Command |= EEPROM_CMD_XE | EEPROM_CMD_ERASE;
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(5));              /* Wait for 5 us */
    Command |= EEPROM_CMD_NVSTR;
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(40000));          /* Wait for 40 ms */
    Command &= ~EEPROM_CMD_ERASE;
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(5));              /* Wait for 5 us */
    Command &= ~(EEPROM_CMD_XE | EEPROM_CMD_NVSTR);
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(1));              /* Wait for 1 us */
  }
  Command &= EEPROM_CMD_Delay_Msk;
  EEPROM->CMD = Command;
  EEPROM->KEY = 0;
}

/**
  * @brief  Erases all pages of the selected EEPROM memory bank.
  * @param  BankSelector: Selects EEPROM Bank (Main Bank or Information Bank).
  *         This parameter can be one of the following values:
  *           @arg EEPROM_Main_Bank_Select:      The EEPROM Main Bank selector.
  *           @arg EEPROM_All_Banks_Select:      The EEPROM All Banks selector.
  * @retval None
  */
__RAMFUNC void EEPROM_EraseAllPages(uint32_t BankSelector)
{
  uint32_t Command;
  uint32_t Offset;

  assert_param(IS_EEPROM_ERASE_SELECTOR(BankSelector));

  EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
  Command = (EEPROM->CMD & EEPROM_CMD_Delay_Msk) | EEPROM_CMD_CON | EEPROM_CMD_IFREN;
  Command |= (BankSelector == EEPROM_All_Banks_Select) ? EEPROM_CMD_IFREN : 0;
  EEPROM->CMD = Command;

  for (Offset = 0; Offset < (4 << 2); Offset += 4)
  {
    EEPROM->ADR = Offset;
    EEPROM->DI = 0;
    Command |= EEPROM_CMD_XE | EEPROM_CMD_MAS1 | EEPROM_CMD_ERASE;
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(5));                /* Wait for 5 us */
    Command |= EEPROM_CMD_NVSTR;
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(40000));            /* Wait for 40 ms */
    Command &= ~EEPROM_CMD_ERASE;
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(100));              /* Wait for 100 us */
    Command &= ~(EEPROM_CMD_XE | EEPROM_CMD_MAS1 | EEPROM_CMD_NVSTR);
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(1));                /* Wait for 1 us */
  }
  Command &= EEPROM_CMD_Delay_Msk;
  EEPROM->CMD = Command;
  EEPROM->KEY = 0;
}

/**
  * @brief  Programs the 8-bit EEPROM memory value.
  * @param  Address: The EEPROM memory byte address.
  * @param  BankSelector: Selects EEPROM Bank (Main Bank or Information Bank).
  *         This parameter can be one of the following values:
  *           @arg EEPROM_Main_Bank_Select:      The EEPROM Main Bank selector.
  *           @arg EEPROM_Info_Bank_Select:      The EEPROM Information Bank selector.
  * @param  Data: The data value to be programmed.
  * @retval None
  */
__RAMFUNC void EEPROM_ProgramByte(uint32_t Address, uint32_t BankSelector, uint32_t Data)
{
  uint32_t Mask;
  uint32_t Tmp;
  uint32_t Shift;

  assert_param(IS_EEPROM_BANK_SELECTOR(BankSelector));

  Shift = (Address & 3) * 8;
  Data = Data << Shift;
  Mask = 0xFF << Shift;
  Tmp = EEPROM_ReadWord(Address, BankSelector);
  EEPROM_ProgramWord(Address, BankSelector, (Tmp & ~Mask) | (Data & Mask));
}

/**
  * @brief  Programs the 16-bit EEPROM memory value.
  * @param  Address: The EEPROM memory half word address (two byte aligned).
  * @param  BankSelector: Selects EEPROM Bank (Main Bank or Information Bank).
  *         This parameter can be one of the following values:
  *           @arg EEPROM_Main_Bank_Select:      The EEPROM Main Bank selector.
  *           @arg EEPROM_Info_Bank_Select:      The EEPROM Information Bank selector.
  * @param  Data: The data value to be programmed.
  * @retval None
  */
__RAMFUNC void EEPROM_ProgramHalfWord(uint32_t Address, uint32_t BankSelector, uint32_t Data)
{
  uint32_t Mask;
  uint32_t Tmp;
  uint32_t Shift;

  assert_param(IS_EEPROM_BANK_SELECTOR(BankSelector));
  assert_param(IS_TWO_BYTE_ALLIGNED(Address));

  Shift = (Address & 2) * 8;
  Data = Data << Shift;
  Mask = 0xFFFF << Shift;
  Tmp = EEPROM_ReadWord(Address, BankSelector);
  EEPROM_ProgramWord(Address, BankSelector, (Tmp & ~Mask) | (Data & Mask));
}

/**
  * @brief  Programs the 32-bit EEPROM memory value.
  * @param  Address: The EEPROM memory word address (four byte aligned).
  * @param  BankSelector: Selects EEPROM Bank (Main Bank or Information Bank).
  *         This parameter can be one of the following values:
  *           @arg EEPROM_Main_Bank_Select:      The EEPROM Main Bank selector.
  *           @arg EEPROM_Info_Bank_Select:      The EEPROM Information Bank selector.
  * @param  Data: The data value to be programmed.
  * @retval None
  */
__RAMFUNC void EEPROM_ProgramWord(uint32_t Address, uint32_t BankSelector, uint32_t Data)
{
  uint32_t Command;

  assert_param(IS_EEPROM_BANK_SELECTOR(BankSelector));
  assert_param(IS_FOUR_BYTE_ALLIGNED(Address));

  EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
  BankSelector = (BankSelector == EEPROM_Info_Bank_Select) ? EEPROM_CMD_IFREN : 0;
  Command = EEPROM->CMD & EEPROM_CMD_Delay_Msk;
  Command |= EEPROM_CMD_CON | BankSelector;
  EEPROM->CMD = Command;
  EEPROM->ADR = Address;
  EEPROM->DI  = Data;
  Command |= EEPROM_CMD_XE | EEPROM_CMD_PROG;
  EEPROM->CMD = Command;
  ProgramDelay(GET_US_LOOPS(5));                /* Wait for 5 us */
  Command |= EEPROM_CMD_NVSTR;
  EEPROM->CMD = Command;
  ProgramDelay(GET_US_LOOPS(10));               /* Wait for 10 us */
  Command |= EEPROM_CMD_YE;
  EEPROM->CMD = Command;
  ProgramDelay(GET_US_LOOPS(40));               /* Wait for 40 us */
  Command &= ~EEPROM_CMD_YE;
  EEPROM->CMD = Command;
  Command &= ~EEPROM_CMD_PROG;
  EEPROM->CMD = Command;
  ProgramDelay(GET_US_LOOPS(5));                /* Wait for 5 us */
  Command &= ~(EEPROM_CMD_XE | EEPROM_CMD_NVSTR);
  EEPROM->CMD = Command;
  ProgramDelay(GET_US_LOOPS(1));                /* Wait for 1 us */

  EEPROM->CMD = Command & EEPROM_CMD_Delay_Msk;
  EEPROM->KEY = 0;
}

/** @} */ /* End of group EEPROM_Private_Functions */

/** @} */ /* End of group EEPROM */

/** @} */ /* End of group __1986BE9x_StdPeriph_Driver */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_eeprom.c */

