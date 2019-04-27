/**
  ******************************************************************************
  * @file    1986BE9x_rst_clk.c
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    22/06/2010
  * @brief   This file contains all the RST_CLK firmware functions.
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
  * FILE 1986BE9x_rst_clk.c
  */

/* Includes ------------------------------------------------------------------*/
#include "1986BE9x_rst_clk.h"
#include "1986BE9x_config.h"

#define ASSERT_INFO_FILE_ID FILEID__1986BE9X_RST_CLK_C

/** @addtogroup __1986BE9x_StdPeriph_Driver 1986BE9x Standard Peripherial Driver
  * @{
  */

/** @addtogroup RST_CLK
  * @{
  */

/** @defgroup RST_CLK_Private_Constants RST_CLK Private Constants
  * @{
  */

#ifndef HSI_Value
/* Typical Value of the HSI in Hz */
 #define HSI_Value                  ((uint32_t)8000000)
#endif /* HSI_Value */

#ifndef HSE_Value
/* Typical Value of the HSE in Hz */
 #define HSE_Value                  ((uint32_t)8000000)
#endif /* HSE_Value */

#ifndef LSI_Value
/* Typical Value of the LSI in Hz */
 #define LSI_Value                  ((uint32_t)40000)
#endif /* LSI_Value */

#ifndef LSE_Value
/* Typical Value of the LSE in Hz */
 #define LSE_Value                  ((uint32_t)32768)
#endif /* LSE_Value */

/* RCC_CLK registers bit address in the alias region */
#define PERIPH_BASE                 0x40000000
#define PERIPH_BB_BASE              0x42000000
#define RST_CLK_OFFSET              (RST_CLK_BASE - PERIPH_BASE)
#define BKP_OFFSET                  (BKP_BASE - PERIPH_BASE)

#define SFR_OFFSET(TP, MOD, SFR)    ((uint32_t)&((TP*)MOD)->SFR)
#define BB_ADDR(TP, MOD, SFR, BIT)  (PERIPH_BB_BASE + SFR_OFFSET(TP, MOD, SFR)*32 + BIT*4)
#define RST_CLK_BB(SFR, BIT)        BB_ADDR(RST_CLK_TypeDef, RST_CLK_OFFSET, SFR, BIT)
#define BKP_BB(SFR, BIT)            BB_ADDR(BKP_TypeDef, BKP_OFFSET, SFR, BIT)

#define FLAG_MASK                   ((uint8_t)0x1F)
#define FLAG_SFR_MASK               ((uint8_t)0xE0)

#define HSI_RDY_MASK                (1 << 23)
#define LSI_RDY_MASK                (1 << 21)
#define LSE_RDY_MASK                (1 << 13)
#define HSE_RDY_MASK                (1 << 2)
#define PLLCPU_RDY_MASK             (1 << 1)
#define PLLUSB_RDY_MASK             (1 << 0)
#define PLLCPUMUL_OFFSET            8
#define PLLCPUmulclr                (~(uint32_t)(0x0F << PLLCPUMUL_OFFSET))
#define PLLUSBMUL_OFFSET            4
#define PLLUSBmulclr                (~(uint32_t)(0x0F << PLLUSBMUL_OFFSET))
#define CPU_C1_SELclr               (~(uint32_t)0x03)
#define CPU_C3_SELclr               (~(uint32_t)0x00000F0)
#define CPU_HCLK_SELclr             (~(uint32_t)(0x03 << 8))
#define ADC_C12_SELclr              (~(uint32_t)((0x03 << 4) | 0x03))
#define ADC_C3_SEL_OFFSET           8
#define ADC_C3_SELclr               (~(uint32_t)(0x0F << ADC_C3_SEL_OFFSET))
#define HSI_SEL_OFFSET              4
#define HSI_SELclr                  (~(uint32_t)(0x0F << HSI_SEL_OFFSET))
#define HSE_SEL_OFFSET              0
#define HSE_SELclr                  (~(uint32_t)(0x0F << HSE_SEL_OFFSET))
#define USB_C1_SELclr               (~(uint32_t)0x03)

#ifndef HSEonTimeOut
/* Time out for HSE start up */
 #define HSEonTimeOut               ((uint16_t)0x0600)
#endif /* HSEonTimeOut */

#ifndef LSEonTimeOut
/* Time out for LSE start up */
 #define LSEonTimeOut               ((uint16_t)0x0600)
#endif /* LSEonTimeOut */

#ifndef HSIonTimeOut
/* Time out for HSI start up */
 #define HSIonTimeOut               ((uint16_t)0x0600)
#endif /* HSIonTimeOut */

#ifndef LSIonTimeOut
/* Time out for LSI start up */
 #define LSIonTimeOut               ((uint16_t)0x0600)
#endif /* LSIonTimeOut */

#ifndef PLLCPUonTimeOut
/* Time out for PLLCPU start up */
 #define PLLCPUonTimeOut            ((uint16_t)0x0600)
#endif /* PLLCPUonTimeOut */

#ifndef PLLUSBonTimeOut
/* Time out for PLLUSB start up */
 #define PLLUSBonTimeOut            ((uint16_t)0x0600)
#endif /* PLLUSBonTimeOut */

#define HSITRIM_OFFSET              24
#define HSITRIM_MASK                ((uint32_t)(0x3F << HSITRIM_OFFSET))

#define HSION_OFFSET                22
#define HSION_MASK                  ((uint32_t)(1 << HSION_OFFSET))
#define HSION_BB                    BKP_BB(REG_0F, HSION_OFFSET)

#define LSITRIM_OFFSET              16
#define LSITRIM_MASK                ((uint32_t)(0x1F << LSITRIM_OFFSET))

#define LSION_OFFSET                15
#define LSION_MASK                  ((uint32_t)(1 << LSION_OFFSET))
#define LSION_BB                    BKP_BB(REG_0F, LSION_OFFSET)

#define PLLCPUON_BB                 RST_CLK_BB(PLL_CONTROL, 2)
#define PLLCPUPLD_BB                RST_CLK_BB(PLL_CONTROL, 3)
#define PLLUSBON_BB                 RST_CLK_BB(PLL_CONTROL, 0)
#define PLLUSBRLD_BB                RST_CLK_BB(PLL_CONTROL, 1)

#define CPU_C2_SEL_BB               RST_CLK_BB(CPU_CLOCK, 2)
#define USB_C2_SEL_BB               RST_CLK_BB(USB_CLOCK, 2)
#define USB_C3_SEL_BB               RST_CLK_BB(USB_CLOCK, 4)
#define USB_CLK_EN_BB               RST_CLK_BB(USB_CLOCK, 8)
#define ADC_CLK_EN_BB               RST_CLK_BB(ADC_MCO_CLOCK, 13)
#define HSI_RTC_EN_BB               RST_CLK_BB(RTC_CLOCK, 9)
#define HSE_RTC_EN_BB               RST_CLK_BB(RTC_CLOCK, 8)
#define CPU_C1_SEL0_BB              RST_CLK_BB(CPU_CLOCK, 0)
#define CPU_C1_SEL1_BB              RST_CLK_BB(CPU_CLOCK, 1)
#define USB_C1_SEL0_BB              RST_CLK_BB(USB_CLOCK, 0)
#define USB_C1_SEL1_BB              RST_CLK_BB(USB_CLOCK, 1)

/** @} */ /* End of group RST_CLK_Private_Constants */

/** @defgroup RST_CLK_Private_Functions RST_CLK Private Functions
  * @{
  */

/**
  * @brief  Set the RST_CLK clock configuration to the default reset state.
  * @param  None
  * @retval None
  */
void RST_CLK_DeInit(void)
{
  RST_CLK_WarmDeInit();
  /* Reset REG_0F bits to zero but HSION bit */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_BKP, ENABLE);
  BKP->REG_0F |= (uint32_t)((1<<22)|(1<<15)); /* HSION & LSION */
  BKP->REG_0F &= (uint32_t)((1<<22)|(1<<15));
}

/**
  * @brief  Set the RST_CLK clock configuration to the default reset state except for
  *         the backup domain REG_0F register.
  * @param  None
  * @retval None
  */
void RST_CLK_WarmDeInit(void)
{
  /* Prepare HSI clk */
  RST_CLK_HSIcmd(ENABLE);
  RST_CLK_HSIstatus();
  RST_CLK_CPUclkSelection(RST_CLK_CPUclkHSI);

  /* Reset CPU_CLOCK bits */
  RST_CLK->CPU_CLOCK   &= (uint32_t)0x00000000;

  /* Reset PLL_CONTROL bits */
  RST_CLK->PLL_CONTROL &= (uint32_t)0x00000000;

  /* Reset HSEON and HSEBYP bits */
  RST_CLK->HS_CONTROL  &= (uint32_t)0x00000000;

  /* Reset USB_CLOCK bits */
  RST_CLK->USB_CLOCK   &= (uint32_t)0x00000000;

  /* Reset ADC_MCO_CLOCK bits */
  RST_CLK->ADC_MCO_CLOCK   &= (uint32_t)0x00000000;

  /* Reset RTC_CLOCK bits */
  RST_CLK->RTC_CLOCK   &= (uint32_t)0x00000000;

  /* Reset all clock but RTC_CLK bit */
  RST_CLK->PER_CLOCK   = (uint32_t)PCLK_BIT(RST_CLK_BASE) | (uint32_t)PCLK_BIT(BKP_BASE);
}

/**
  * @brief  RST_CLK_HSEconfig - HSE (High Speed External) clock mode and source selection
  * @param  RST_CLK_HSE - mode selector
  *         @arg RST_CLK_HSE_OFF    -  switch off HSE clock generator
  *         @arg RST_CLK_HSE_ON     -  switch on HSE clock generator
  *         @arg RST_CLK_HSE_Bypass -  use external clock source
  * @retval None
  */
void RST_CLK_HSEconfig(uint32_t RST_CLK_HSE)
{
  /* Check the parameters */
  assert_param(IS_RST_CLK_HSE(RST_CLK_HSE));
  /* Reset HSEON and HSEBYP bits before configuring the HSE */
  RST_CLK->HS_CONTROL &= ~((uint32_t)(RST_CLK_HSE_ON | RST_CLK_HSE_Bypass));
  /* Configure HSE (RCC_HSE_OFF is already covered by the code section above) */
  switch (RST_CLK_HSE)
  {
    case RST_CLK_HSE_ON:
      /* Set HSEON bit */
      RST_CLK->HS_CONTROL |= RST_CLK_HSE_ON;
      break;

    case RST_CLK_HSE_Bypass:
      /* Set HSEBYP and HSEON bits */
      RST_CLK->HS_CONTROL |= RST_CLK_HSE_ON | RST_CLK_HSE_Bypass;
      break;

    default:
      break;
  }
}

/**
  * @brief  RST_CLK_HSEstatus - HSE clock status
  * @param  None
  * @retval enum ErrorStatus - SUCCESS if HSE clock is ready, else ERROR
  */
ErrorStatus RST_CLK_HSEstatus(void)
{
  __IO uint32_t startCounter = 0;
  ErrorStatus state;
  FlagStatus flag;

  /* Wait until HSE is ready or time out is occure */
  do
  {
    flag = RST_CLK_GetFlagStatus(RST_CLK_FLAG_HSERDY);
    startCounter++;
  } while ((startCounter < HSEonTimeOut) && (flag == RESET));

  if (RST_CLK_GetFlagStatus(RST_CLK_FLAG_HSERDY) != RESET)
  {
    state = SUCCESS;
  }
  else
  {
    state = ERROR;
  }
  return state;
}

/**
  * @brief  RST_CLK_LSEconfig - LSE (Low Speed External) clock mode and source selection
  * @param  RST_CLK_LSE - mode selector
  *         @arg RST_CLK_LSE_OFF    -  switch off LSE clock generator
  *         @arg RST_CLK_LSE_ON     -  switch on LSE clock generator
  *         @arg RST_CLK_LSE_Bypass -  use external clock source
  * @retval None
  */
void RST_CLK_LSEconfig(uint32_t RST_CLK_LSE)
{
  /* Check the parameters */
  assert_param(IS_RST_CLK_LSE(RST_CLK_LSE));
  /* Reset LSEON and LSEBYP bits before configuring the LSE */
  BKP->REG_0F &= ~((uint32_t)(RST_CLK_LSE_ON | RST_CLK_LSE_Bypass));
  switch (RST_CLK_LSE)
  {
    case RST_CLK_LSE_ON:
      /* Set LSEON bit */
      BKP->REG_0F |= RST_CLK_LSE_ON;
      break;

    case RST_CLK_LSE_Bypass:
      /* Set LSEBYP and LSEON bits */
      BKP->REG_0F |= (RST_CLK_LSE_ON | RST_CLK_LSE_Bypass);
      break;

    default:
      break;
  }
}

/**
  * @brief  RST_CLK_LSEstatus - LSE clock status
  * @param  None
  * @retval enum ErrorStatus - SUCCESS if LSE clock is ready, else ERROR
  */
ErrorStatus RST_CLK_LSEstatus(void)
{
  __IO uint32_t startCounter = 0;
  ErrorStatus state;
  FlagStatus flag;

 /* Wait until LSE is ready or time out is occure */
 do
  {
    flag = RST_CLK_GetFlagStatus(RST_CLK_FLAG_LSERDY);
    startCounter++;
  } while ((startCounter < LSEonTimeOut) && (flag == RESET));

  if (RST_CLK_GetFlagStatus(RST_CLK_FLAG_LSERDY) != RESET)
  {
    state = SUCCESS;
  }
  else
  {
    state = ERROR;
  }
  return state;
}

/**
  * @brief  RST_CLK_HSIcmd:  HSI (High Speed Internal) clock mode selection
  * @param  NewState: mode selector - DISABLE, ENABLE
  *         @arg DISABLE:   switch off HSI clock generator
  *         @arg ENABLE:    switch on HSI clock generator
  * @retval None
  */
void RST_CLK_HSIcmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) HSION_BB = (uint32_t)NewState;
}

/**
  * @brief  RST_CLK_HSIadjust: HSI clock frequency adjustment by HSITRIM setting
  * @param  HSItrimValue
  *         This parameter must be a number between 0 and 0x0F.
  * @retval None
  */
void RST_CLK_HSIadjust(uint8_t HSItrimValue)
{
  uint32_t temp;
  /* Check the parameters */
  assert_param(IS_RCC_CLK_HSI_TRIM_VALUE(HSItrimValue));
  temp = BKP->REG_0F;
  /* Clear HSITRIM[5:0] bits */
  temp &= ~HSITRIM_MASK;
  /* Set the HSITRIM[5:0] bits according to HSItrimValue value */
  temp |= (uint32_t)HSItrimValue << HSITRIM_OFFSET;
  /* Store the new value */
  BKP->REG_0F = temp;
}

/**
  * @brief  RST_CLK_HSIstatus: HSI clock status
  * @param  None
  * @retval enum ErrorStatus: SUCCESS if HSI clock is ready, else ERROR
  */
ErrorStatus RST_CLK_HSIstatus(void)
{
  __IO uint32_t startCounter = 0;
  ErrorStatus state;
  FlagStatus flag;

  /* Wait until HSI is ready or time out is occure */
  do
  {
    flag = RST_CLK_GetFlagStatus(RST_CLK_FLAG_HSIRDY);
    startCounter++;
  } while ((startCounter < HSIonTimeOut) && (flag == RESET));

  if (RST_CLK_GetFlagStatus(RST_CLK_FLAG_HSIRDY) != RESET)
  {
    state = SUCCESS;
  }
  else
  {
    state = ERROR;
  }
  return state;
}

/**
  * @brief  RST_CLK_LSIcmd:  LSI (High Speed Internal) clock mode selection
  * @param  NewState: mode selector - DISABLE, ENABLE
  *         @arg DISABLE:   switch off LSI clock generator
  *         @arg ENABLE:    switch on LSI clock generator
  * @retval None
  */
void RST_CLK_LSIcmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) LSION_BB = (uint32_t)NewState;
}

/**
  * @brief  RST_CLK_LSIstatus - LSI clock status
  * @param  None
  * @retval enum ErrorStatus - SUCCESS if LSI clock is ready, else ERROR
  */
ErrorStatus RST_CLK_LSIstatus(void)
{
  __IO uint32_t startCounter = 0;
  ErrorStatus state;
  FlagStatus flag;

  /* Wait until LSI is ready or time out is occure */
  do
  {
    flag = RST_CLK_GetFlagStatus(RST_CLK_FLAG_LSIRDY);
    startCounter++;
  } while ((startCounter < LSIonTimeOut) && (flag == RESET));

  if (RST_CLK_GetFlagStatus(RST_CLK_FLAG_LSIRDY) != RESET)
  {
    state = SUCCESS;
  }
  else
  {
    state = ERROR;
  }
  return (state);
}

/**
  * @brief  Configures the CPU_PLL clock source and multiplication factor.
  * @param  RST_CLK_CPU_PLLsource: specifies the PLL entry clock source.
  *         @arg RST_CLK_CPU_PLLsrcHSIdiv1: HSI oscillator clock is selected as CPU_PLL clock entry
  *         @arg RST_CLK_CPU_PLLsrcHSIdiv2: HSI oscillator clock divided by 2 is selected as CPU_PLL clock entry
  *         @arg RST_CLK_CPU_PLLsrcHSEdiv1: HSE oscillator clock is selected as CPU_PLL clock entry
  *         @arg RST_CLK_CPU_PLLsrcHSEdiv2: HSE oscillator clock divided by 2 is selected as CPU_PLL clock entry
  * @param  RST_CLK_CPU_PLLmul: specifies the PLL multiplication factor.
  *         This parameter must be a number between 0 and 15.
  *           @arg RST_CLK_CPU_PLLmul1
  *           @arg RST_CLK_CPU_PLLmul2
  *           @arg RST_CLK_CPU_PLLmul3
  *           @arg RST_CLK_CPU_PLLmul4
  *           @arg RST_CLK_CPU_PLLmul5
  *           @arg RST_CLK_CPU_PLLmul6
  *           @arg RST_CLK_CPU_PLLmul7
  *           @arg RST_CLK_CPU_PLLmul8
  *           @arg RST_CLK_CPU_PLLmul9
  *           @arg RST_CLK_CPU_PLLmul10
  *           @arg RST_CLK_CPU_PLLmul11
  *           @arg RST_CLK_CPU_PLLmul12
  *           @arg RST_CLK_CPU_PLLmul13
  *           @arg RST_CLK_CPU_PLLmul14
  *           @arg RST_CLK_CPU_PLLmul15
  *           @arg RST_CLK_CPU_PLLmul16
  * @retval None
  */
void RST_CLK_CPU_PLLconfig(uint32_t RST_CLK_CPU_PLLsource, uint32_t RST_CLK_CPU_PLLmul)
{
  uint32_t temp;

  /* Check the parameters */
  assert_param(IS_RST_CLK_CPU_PLL_SOURCE(RST_CLK_CPU_PLLsource));
  assert_param(IS_RST_CLK_CPU_PLL_MUL(RST_CLK_CPU_PLLmul));

  /* Select CPUPLL source */
  temp = RST_CLK->CPU_CLOCK;
  /* Clear CPU_C1_SEL bits */
  temp &= CPU_C1_SELclr;
  /* Set the CPU_C1_SEL bits */
  temp |= RST_CLK_CPU_PLLsource;
  /* Store the new value */
  RST_CLK->CPU_CLOCK = temp;

  /* Set CPUPLL multiplier */
  temp = RST_CLK->PLL_CONTROL;
  /* Clear PLLMUL[3:0] bits */
  temp &= PLLCPUmulclr;
  /* Set the PLLMUL[3:0] bits */
  temp |= (RST_CLK_CPU_PLLmul<<PLLCPUMUL_OFFSET);
  /* Store the new value */
  RST_CLK->PLL_CONTROL = temp;

  if ( *(__IO uint32_t *) PLLCPUON_BB)
  {
     *(__IO uint32_t *) PLLCPUPLD_BB = (uint32_t)0x01;
  }
}

/**
  * @brief  Select the CPU_PLL output as input for CPU_C3_SEL or bypass the CPU_PLL.
  * @param  UsePLL: usage state of the CPU_PLL. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RST_CLK_CPU_PLLuse(FunctionalState UsePLL)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(UsePLL));

  *(__IO uint32_t *) CPU_C2_SEL_BB = (uint32_t)UsePLL;
}

/**
  * @brief  Enables or disables the CPU_PLL.
  * @param  NewState: new state of the CPU_PLL. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RST_CLK_CPU_PLLcmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) PLLCPUON_BB = (uint32_t)NewState;
}

/**
  * @brief  RST_CLK_CPU_PLLstatus: CPU_PLL status
  * @param  None
  * @retval enum ErrorStatus: SUCCESS if CPU_PLL output clock is ready, else ERROR
  */
ErrorStatus RST_CLK_CPU_PLLstatus(void)
{
  __IO uint32_t startCounter = 0;
  ErrorStatus state;
  FlagStatus flag;

  /* Wait until CPUPLL is ready or time out is occure */
  do
  {
    flag = RST_CLK_GetFlagStatus(RST_CLK_FLAG_PLLCPURDY);
    startCounter++;
  } while ((startCounter < PLLCPUonTimeOut) && (flag == RESET));

  if (RST_CLK_GetFlagStatus(RST_CLK_FLAG_PLLCPURDY) != RESET)
  {
    state = SUCCESS;
  }
  else
  {
    state = ERROR;
  }
  return state;
}

/**
  * @brief  RST_CLK_CPUclkPrescaler: configures the CPU_C3_SEL division factor switch.
  * @param  CPUclkDivValue: specifies the CPU_PLL clock division factor.
  *         @arg RST_CLK_CPUclkDIV1
  *         @arg RST_CLK_CPUclkDIV2
  *         @arg RST_CLK_CPUclkDIV4
  *         @arg RST_CLK_CPUclkDIV8
  *         @arg RST_CLK_CPUclkDIV16
  *         @arg RST_CLK_CPUclkDIV32
  *         @arg RST_CLK_CPUclkDIV64
  *         @arg RST_CLK_CPUclkDIV128
  *         @arg RST_CLK_CPUclkDIV256
  * @retval None
  */
void RST_CLK_CPUclkPrescaler(uint32_t CPUclkDivValue)
{
  uint32_t temp;

  /* Check the parameters */
  assert_param(IS_RST_CLK_CPUclkDIV(CPUclkDivValue));

  temp = RST_CLK->CPU_CLOCK;
  /* Clear CPU_C3_SEL bits */
  temp &= CPU_C3_SELclr;
  /* Set the CPU_C3_SEL bits */
  temp |= CPUclkDivValue;
  /* Store the new value */
  RST_CLK->CPU_CLOCK = temp;
}

/**
  * @brief  RST_CLK_CPUclkSelection: select the CPU clock source.
  * @param  CPU_CLK: specifies the CPU clock source.
  *         @arg RST_CLK_CPUclkHSI
  *         @arg RST_CLK_CPUclkCPU_C3
  *         @arg RST_CLK_CPUclkLSE
  *         @arg RST_CLK_CPUclkLSI
  * @retval None
  */
void RST_CLK_CPUclkSelection(uint32_t CPU_CLK)
{
  uint32_t temp;

  /* Check the parameters */
  assert_param(IS_RST_CPU_CLK(CPU_CLK));

  temp = RST_CLK->CPU_CLOCK;
  /* Clear CPU_C3_SEL bits */
  temp &= CPU_HCLK_SELclr;
  /* Set the CPU_C3_SEL bits */
  temp |= CPU_CLK;
  /* Store the new value */
  RST_CLK->CPU_CLOCK = temp;
}

/**
  * @brief  Configures the USB_PLL clock source and multiplication factor.
  * @param  RST_CLK_USB_PLLsource: specifies the PLL entry clock source.
  *         @arg RST_CLK_USB_PLLsrcHSIdiv1: HSI oscillator clock is selected as USB_PLL clock entry
  *         @arg RST_CLK_USB_PLLsrcHSIdiv2: HSI oscillator clock divided by 2 is selected as USB_PLL clock entry
  *         @arg RST_CLK_USB_PLLsrcHSEdiv1: HSE oscillator clock is selected as USB_PLL clock entry
  *         @arg RST_CLK_USB_PLLsrcHSEdiv2: HSE oscillator clock divided by 2 is selected as USB_PLL clock entry
  * @param  RST_CLK_USB_PLLmul: specifies the PLL multiplication factor.
  *         This parameter must be a number between 0 and 15.
  *           @arg RST_CLK_USB_PLLmul1
  *           @arg RST_CLK_USB_PLLmul2
  *           @arg RST_CLK_USB_PLLmul3
  *           @arg RST_CLK_USB_PLLmul4
  *           @arg RST_CLK_USB_PLLmul5
  *           @arg RST_CLK_USB_PLLmul6
  *           @arg RST_CLK_USB_PLLmul7
  *           @arg RST_CLK_USB_PLLmul8
  *           @arg RST_CLK_USB_PLLmul9
  *           @arg RST_CLK_USB_PLLmul10
  *           @arg RST_CLK_USB_PLLmul11
  *           @arg RST_CLK_USB_PLLmul12
  *           @arg RST_CLK_USB_PLLmul13
  *           @arg RST_CLK_USB_PLLmul14
  *           @arg RST_CLK_USB_PLLmul15
  *           @arg RST_CLK_USB_PLLmul16
  * @retval None
  */
void RST_CLK_USB_PLLconfig(uint32_t RST_CLK_USB_PLLsource, uint32_t RST_CLK_USB_PLLmul)
{
  uint32_t temp;

  /* Check the parameters */
  assert_param(IS_RST_CLK_USB_PLL_SOURCE(RST_CLK_USB_PLLsource));
  assert_param(IS_RST_CLK_USB_PLL_MUL(RST_CLK_USB_PLLmul));

  /* Select USBPLL source */
  temp = RST_CLK->USB_CLOCK;
  /* Clear USB_C1_SEL bits */
  temp &= USB_C1_SELclr;
  /* Set the USB_C1_SEL bits */
  temp |= RST_CLK_USB_PLLsource;
  /* Store the new value */
  RST_CLK->USB_CLOCK = temp;

  /* Set USBPLL multiplier */
  temp = RST_CLK->PLL_CONTROL;
  /* Clear PLLMUL[3:0] bits */
  temp &= PLLUSBmulclr;
  /* Set the PLLMUL[3:0] bits */
  temp |= (RST_CLK_USB_PLLmul<<PLLUSBMUL_OFFSET);
  /* Store the new value */
  RST_CLK->PLL_CONTROL = temp;

  if ( *(__IO uint32_t *) PLLUSBON_BB)
  {
    *(__IO uint32_t *) PLLUSBRLD_BB  = (uint32_t)0x01;
  }
}

/**
  * @brief  Select the USBPLL output as input for USB_C3_SEL or bypass the USB_PLL.
  * @param  UsePLL: usage state of the USB_PLL. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RST_CLK_USB_PLLuse(FunctionalState UsePLL)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(UsePLL));

  *(__IO uint32_t *) USB_C2_SEL_BB = (uint32_t)UsePLL;
}

/**
  * @brief  Enables or disables the USB_PLL.
  * @param  NewState: new state of the USB_PLL. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RST_CLK_USB_PLLcmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) PLLUSBON_BB = (uint32_t)NewState;
}

/**
  * @brief  RST_CLK_USB_PLLstatus: USB_PLL status
  * @param  None
  * @retval enum ErrorStatus: SUCCESS if USB_PLL output clock is ready, else ERROR
  */
ErrorStatus RST_CLK_USB_PLLstatus(void)
{
  __IO uint32_t startCounter = 0;
  ErrorStatus state;
  FlagStatus flag;

  /* Wait until USBPLL is ready or time out is occure */
  do
  {
    flag = RST_CLK_GetFlagStatus(RST_CLK_FLAG_PLLUSBRDY);
    startCounter++;
  } while ((startCounter < PLLUSBonTimeOut) && (flag == RESET));

  if (RST_CLK_GetFlagStatus(RST_CLK_FLAG_PLLUSBRDY) != RESET)
  {
    state = SUCCESS;
  }
  else
  {
    state = ERROR;
  }
  return state;
}

/**
  * @brief  Enables or disables the USB_CLK prescaler.
  * @param  NewState: new state of the USB_CLK prescaler.
  *         @arg ENABLE: USB_C2 divided by 2
  *         @arg DISABLE: USB_C2 not divided
  * @retval None
  */
void RST_CLK_USBclkPrescaler(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) USB_CLK_EN_BB = (uint32_t)NewState;
}

/**
  * @brief  Enables or disables the USB_CLK clock.
  * @param  NewState: new state of the USB_CLK.
  *         @arg ENABLE
  *         @arg DISABLE
  * @retval None
  */
void RST_CLK_USBclkEnable(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) USB_C3_SEL_BB = (uint32_t)NewState;
}

/**
  * @brief  RST_CLK_ADCclkSelection: select the ADC clock source.
  * @param  ADC_CLK: specifies the ADC_C2 clock source.
  *         @arg  RST_CLK_ADCclkCPU_C1
  *         @arg  RST_CLK_ADCclkUSB_C1
  *         @arg  RST_CLK_ADCclkCPU_C2
  *         @arg  RST_CLK_ADCclkUSB_C2
  *         @arg  RST_CLK_ADCclkLSE
  *         @arg  RST_CLK_ADCclkLSI
  *         @arg  RST_CLK_ADCclkHSI_C1
  * @retval None
  */
void RST_CLK_ADCclkSelection(uint32_t ADC_CLK)
{
  uint32_t temp;

  /* Check the parameters */
  assert_param(IS_RST_CLK_ADCclk(ADC_CLK));

  /* Select ADC_CLK source */
  temp = RST_CLK->ADC_MCO_CLOCK;
  /* Clear ADC_C1,C2 SEL bits */
  temp &= ADC_C12_SELclr;
  /* Set the ADC_C1,C2 SEL bits */
  temp |= ADC_CLK;
  /* Store the new value */
  RST_CLK->ADC_MCO_CLOCK = temp;
}

/**
  * @brief  RST_CLK_ADCclkPrescaler: configures the ADC_C3_SEL division factor switch.
  * @param  ADCclkDivValue: specifies the ADC_C2 clock division factor.
  *         This parameter must be a number between 0 and 15.
  *           @arg RST_CLK_ADCclkDIV1
  *           @arg RST_CLK_ADCclkDIV2
  *           @arg RST_CLK_ADCclkDIV3
  *           @arg RST_CLK_ADCclkDIV4
  *           @arg RST_CLK_ADCclkDIV5
  *           @arg RST_CLK_ADCclkDIV6
  *           @arg RST_CLK_ADCclkDIV7
  *           @arg RST_CLK_ADCclkDIV8
  *           @arg RST_CLK_ADCclkDIV9
  *           @arg RST_CLK_ADCclkDIV10
  *           @arg RST_CLK_ADCclkDIV11
  *           @arg RST_CLK_ADCclkDIV12
  *           @arg RST_CLK_ADCclkDIV13
  *           @arg RST_CLK_ADCclkDIV14
  *           @arg RST_CLK_ADCclkDIV15
  *           @arg RST_CLK_ADCclkDIV16
  * @retval None
  */
void RST_CLK_ADCclkPrescaler(uint32_t ADCclkDivValue)
{
  uint32_t temp;

  /* Check the parameters */
  assert_param(IS_RST_CLK_ADCclkDivValue(ADCclkDivValue));

  temp = RST_CLK->ADC_MCO_CLOCK;
  /* Clear ADC_C3_SEL bits */
  temp &= ADC_C3_SELclr;
  /* Set the ADC_C3_SEL bits */
  temp |= ADCclkDivValue<<ADC_C3_SEL_OFFSET;
  /* Store the new value */
  RST_CLK->ADC_MCO_CLOCK = temp;
}

/**
  * @brief  Enables or disables the ADC_CLK clock.
  * @param  NewState: new state of the ADC_CLK.
  *         @arg ENABLE
  *         @arg DISABLE
  * @retval None
  */
void RST_CLK_ADCclkEnable(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) ADC_CLK_EN_BB = (uint32_t)NewState;
}

/**
  * @brief  RST_CLK_HSIclkPrescaler: configures the HSI_C1_SEL division factor switch.
  * @param  HSIclkDivValue: specifies the HSI clock division factor.
  *         This parameter must be a number between 0 and 15.
  *           @arg RST_CLK_HSIclkDIV1
  *           @arg RST_CLK_HSIclkDIV2
  *           @arg RST_CLK_HSIclkDIV3
  *           @arg RST_CLK_HSIclkDIV4
  *           @arg RST_CLK_HSIclkDIV5
  *           @arg RST_CLK_HSIclkDIV6
  *           @arg RST_CLK_HSIclkDIV7
  *           @arg RST_CLK_HSIclkDIV8
  *           @arg RST_CLK_HSIclkDIV9
  *           @arg RST_CLK_HSIclkDIV10
  *           @arg RST_CLK_HSIclkDIV11
  *           @arg RST_CLK_HSIclkDIV12
  *           @arg RST_CLK_HSIclkDIV13
  *           @arg RST_CLK_HSIclkDIV14
  *           @arg RST_CLK_HSIclkDIV15
  *           @arg RST_CLK_HSIclkDIV16
  * @retval None
  */
void RST_CLK_HSIclkPrescaler(uint32_t HSIclkDivValue)
{
  uint32_t temp;

  /* Check the parameters */
  assert_param(IS_RST_CLK_HSIclkDivValue(HSIclkDivValue));

  temp = RST_CLK->RTC_CLOCK;
  /* Clear HSI_SEL bits */
  temp &= HSI_SELclr;
  /* Set the HSI_SEL bits */
  temp |= HSIclkDivValue<<HSI_SEL_OFFSET;
  /* Store the new value */
  RST_CLK->RTC_CLOCK = temp;
}

/**
  * @brief  RST_CLK_RTC_HSIclkEnable: enables or disables the RTCHSI clock.
  * @param  NewState: new state of the HSI_RTC_EN.
  *         @arg ENABLE
  *         @arg DISABLE
  * @retval None
  */
void RST_CLK_RTC_HSIclkEnable(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) HSI_RTC_EN_BB = (uint32_t)NewState;
}

/**
  * @brief  RST_CLK_HSEclkPrescaler: configures the HSE_C1_SEL division factor switch.
  * @param  HSEclkDivValue: specifies the HSE clock division factor.
  *         This parameter must be a number between 0 and 15.
  *           @arg RST_CLK_HSEclkDIV1
  *           @arg RST_CLK_HSEclkDIV2
  *           @arg RST_CLK_HSEclkDIV3
  *           @arg RST_CLK_HSEclkDIV4
  *           @arg RST_CLK_HSEclkDIV5
  *           @arg RST_CLK_HSEclkDIV6
  *           @arg RST_CLK_HSEclkDIV7
  *           @arg RST_CLK_HSEclkDIV8
  *           @arg RST_CLK_HSEclkDIV9
  *           @arg RST_CLK_HSEclkDIV10
  *           @arg RST_CLK_HSEclkDIV11
  *           @arg RST_CLK_HSEclkDIV12
  *           @arg RST_CLK_HSEclkDIV13
  *           @arg RST_CLK_HSEclkDIV14
  *           @arg RST_CLK_HSEclkDIV15
  *           @arg RST_CLK_HSEclkDIV16
  * @retval None
  */
void RST_CLK_HSEclkPrescaler(uint32_t HSEclkDivValue)
{
  uint32_t temp;

  /* Check the parameters */
  assert_param(IS_RST_CLK_HSEclkDivValue(HSEclkDivValue));

  temp = RST_CLK->RTC_CLOCK;
  /* Clear HSE_SEL bits */
  temp &= HSE_SELclr;
  /* Set the HSE_SEL bits */
  temp |= HSEclkDivValue<<HSE_SEL_OFFSET;
  /* Store the new value */
  RST_CLK->RTC_CLOCK = temp;
}

/**
  * @brief  RST_CLK_RTC_HSEclkEnable: enables or disables the RTCHSE clock.
  * @param  NewState: new state of the HSE_RTC_EN.
  *         @arg ENABLE
  *         @arg DISABLE
  * @retval None
  */
void RST_CLK_RTC_HSEclkEnable(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) HSE_RTC_EN_BB = (uint32_t)NewState;
}

/**
  * @brief  RST_CLK_RTC_HSEclkEnable: enables or disables the RTCHSE clock.
  * @param  RST_CLK_PCLK: specifies the peripheral to gates its clock.
  *         This parameter can be any combination of the following values:
  *           @arg RST_CLK_PCLK_CAN1, RST_CLK_PCLK_CAN2, RST_CLK_PCLK_USB, RST_CLK_PCLK_EEPROM,
  *                RST_CLK_PCLK_RST_CLK, RST_CLK_PCLK_DMA, RST_CLK_PCLK_UART1, RST_CLK_PCLK_UART2,
  *                RST_CLK_PCLK_SPI1, RST_CLK_PCLK_I2C, RST_CLK_PCLK_POWER,
  *                RST_CLK_PCLK_WWDG, RST_CLK_PCLK_IWDG, RST_CLK_PCLK_TIMER1, RST_CLK_PCLK_TIMER2,
  *                RST_CLK_PCLK_TIMER3, RST_CLK_PCLK_ADC, RST_CLK_PCLK_DAC, RST_CLK_PCLK_COMP,
  *                RST_CLK_PCLK_SPI2, RST_CLK_PCLK_PORTA, RST_CLK_PCLK_PORTB, RST_CLK_PCLK_PORTC,
  *                RST_CLK_PCLK_PORTD, RST_CLK_PCLK_PORTE, RST_CLK_PCLK_BKP, RST_CLK_PCLK_PORTF,
  *                RST_CLK_PCLK_EXT_BUS_CNTRL
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RST_CLK_PCLKcmd(uint32_t RST_CLK_PCLK, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_RST_CLK_PCLK(RST_CLK_PCLK));
  if (NewState != DISABLE)
  {
    RST_CLK->PER_CLOCK |= RST_CLK_PCLK;
  }
  else
  {
    RST_CLK->PER_CLOCK &= ~RST_CLK_PCLK;
  }
}

/**
  * @brief  RST_CLK_GetClocksFreq: Put the frequencies of different on chip clocks
  *         in *RST_CLK_Clocks structure.
  * @param  RST_CLK_Clocks: pointer to a RST_CLK_ClocksTypeDef structure that will hold
  *         the clocks frequencies.
  * @retval None
  */
void RST_CLK_GetClocksFreq(RST_CLK_FreqTypeDef* RST_CLK_Clocks)
{
  uint32_t cpu_c1_freq, cpu_c2_freq, cpu_c3_freq;
  uint32_t usb_c1_freq, usb_c2_freq, usb_c3_freq;
  uint32_t adc_c1_freq, adc_c2_freq, adc_c3_freq;
  uint32_t hsi_c1_freq, hse_c1_freq;
  uint32_t pll_mul;

  /* Check the parameter */
  assert_param(RST_CLK_Clocks != 0);

  /* Compute CPU_CLK, USB_CLK, ADC_CLK, RTCHSI, RTCHSE clocks frequencies */

  /* Compute CPU_CLK frequency */

  /* Determine CPU_C1 frequency */
  if (*(__IO uint32_t *) CPU_C1_SEL1_BB)
  {
    cpu_c1_freq = HSE_Value;
  }
  else
  {
    cpu_c1_freq = HSI_Value;
  }

  if (*(__IO uint32_t *) CPU_C1_SEL0_BB)
  {
    cpu_c1_freq /= 2;
  }

  /* Determine CPU_C2 frequency */
  cpu_c2_freq = cpu_c1_freq;

  if (*(__IO uint32_t *) CPU_C2_SEL_BB != 0)
  {
    /* Determine CPU PLL output frequency */
    pll_mul = ((RST_CLK->PLL_CONTROL >> RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos) & (uint32_t)0x0F) + 1;
    cpu_c2_freq *= pll_mul;
  }

  /*Select CPU_CLK from HSI, CPU_C3, LSE, LSI cases */
  switch ((RST_CLK->CPU_CLOCK >> RST_CLK_CPU_CLOCK_HCLK_SEL_Pos) & (uint32_t)0x03)
  {
    case 0 :
      /* HSI */
      RST_CLK_Clocks->CPU_CLK_Frequency = HSI_Value;
      break;
    case 1 :
      /* CPU_C3 */
      /* Determine CPU_C3 frequency */
      if (( RST_CLK->CPU_CLOCK >> RST_CLK_USB_CLOCK_CPU_C3_SEL_Pos & (uint32_t)0x08) == 0x00)
      {
        cpu_c3_freq = cpu_c2_freq;
      }
      else
      {
        cpu_c3_freq = cpu_c2_freq/(1 << ((RST_CLK->CPU_CLOCK >> RST_CLK_USB_CLOCK_CPU_C3_SEL_Pos & (uint32_t)0x07) + 1));
      }
      RST_CLK_Clocks->CPU_CLK_Frequency = cpu_c3_freq;
      break;
    case 2 :
      /* LSE */
      RST_CLK_Clocks->CPU_CLK_Frequency = LSE_Value;
      break;
    default : /* case 3 */
      /* LSI */
      RST_CLK_Clocks->CPU_CLK_Frequency = LSI_Value;
      break;
  }

  /* Compute USB_CLK frequency */

  /* Determine USB_C1 frequency */
  if (*(__IO uint32_t *) USB_C1_SEL1_BB)
  {
    usb_c1_freq = HSE_Value;
  }
  else
  {
    usb_c1_freq = HSI_Value;
  }

  if (*(__IO uint32_t *) USB_C1_SEL0_BB)
  {
    usb_c1_freq /= 2;
  }

  /* Determine USB_C2 frequency */
  usb_c2_freq = usb_c1_freq;

  if (*(__IO uint32_t *) USB_C2_SEL_BB != 0)
  {
    /* Determine USB PLL output frequency */
    pll_mul = ((RST_CLK->PLL_CONTROL >> RST_CLK_PLL_CONTROL_PLL_USB_MUL_Pos) & (uint32_t)0x0F) + 1;
    usb_c2_freq *= pll_mul;
  }

  /* Determine USB_C3 frequency */
  usb_c3_freq = usb_c2_freq;
  if (*(__IO uint32_t *) USB_C3_SEL_BB != 0)
  {
    usb_c3_freq /= 2;
  }

  RST_CLK_Clocks->USB_CLK_Frequency = usb_c3_freq;

  /* Compute RTCHSE_CLK frequency */
  hsi_c1_freq = HSI_Value/((RST_CLK->RTC_CLOCK >> RST_CLK_RTC_CLOCK_HSI_SEL_Pos & (uint32_t)0x0F) + 1);
  RST_CLK_Clocks->RTCHSI_Frequency = hsi_c1_freq;

  /* Compute RTCHSI_CLK frequency */
  hse_c1_freq = HSE_Value/((RST_CLK->RTC_CLOCK >> RST_CLK_RTC_CLOCK_HSE_SEL_Pos & (uint32_t)0x0F) + 1);
  RST_CLK_Clocks->RTCHSE_Frequency = hse_c1_freq;

  /* Compute ADC_CLK frequency */

  /* Select ADC_C1 from CPU_C1, LSI, USB_C1, CPU_C2, USB_C2 cases */
  switch ((RST_CLK->ADC_MCO_CLOCK >> RST_CLK_ADC_MCO_CLOCK_ADC_C1_SEL_Pos) & (uint32_t)0x03)
  {
    case 0 :
      /* CPU_C1 */
      adc_c1_freq = cpu_c1_freq;
      break;
    case 1 :
      /* USB_C1 */
      adc_c1_freq = usb_c1_freq;
      break;
    case 2 :
      /* CPU_C2 */
      adc_c1_freq = cpu_c2_freq;
      break;
    default : /* case 3 */
      /* USB_C2 */
      adc_c1_freq = usb_c2_freq;
      break;
  }

  /* Select ADC_C2 from LSE, LSI, ADC_C1, HSI_C1 cases */
  switch ((RST_CLK->ADC_MCO_CLOCK >> RST_CLK_ADC_MCO_CLOCK_ADC_C2_SEL_Pos) & (uint32_t)0x03)
  {
    case 0 :
      /* LSE */
      adc_c2_freq = LSE_Value;
      break;
    case 1 :
      /* LSI */
      adc_c2_freq = LSI_Value;
      break;
    case 2 :
      /* ADC_C1 */
      adc_c2_freq = adc_c1_freq;
      break;
    default : /* case 3 */
      /* HSI_C1 */
      adc_c2_freq = hsi_c1_freq;
      break;
  }

  adc_c3_freq = adc_c2_freq /((RST_CLK->ADC_MCO_CLOCK >> RST_CLK_ADC_MCO_CLOCK_ADC_C3_SEL_Pos & (uint32_t)0x0F) + 1);
  RST_CLK_Clocks->ADC_CLK_Frequency = adc_c3_freq;
}

/**
  * @brief  Checks whether the specified RCC flag is set or not.
  * @param  RST_CLK_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *           @arg RST_CLK_FLAG_HSIRDY
  *                RST_CLK_FLAG_LSIRDY
  *                RST_CLK_FLAG_HSERDY
  *                RST_CLK_FLAG_LSERDY
  *                RST_CLK_FLAG_PLLCPURDY
  *                RST_CLK_FLAG_PLLUSBRDY
  * @retval The new state of RCC_FLAG (SET or RESET).
  */
FlagStatus RST_CLK_GetFlagStatus(uint32_t RST_CLK_FLAG)
{
  uint32_t statusreg;
  FlagStatus bitstatus;

  /* Check the parameters */
  assert_param(IS_RST_CLK_FLAG(RST_CLK_FLAG));

  /* Get the register */
  if ((FLAG_SFR_MASK & RST_CLK_FLAG) == (uint32_t)0x20) /* The flag to check is in CLOCK_STATUS register */
  {
    statusreg = RST_CLK->CLOCK_STATUS;
  }
  else                                                  /* The flag to check is in REG_0F register */
  {
    statusreg = BKP->REG_0F;
  }

  /* Get the flag status on proper position */
  if ((statusreg & ((uint32_t)1 << (RST_CLK_FLAG & FLAG_MASK))) != (uint32_t)0x00)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the flag status */
  return bitstatus;
}

/** @} */ /* End of group RST_CLK_Private_Functions */

/** @} */ /* End of group RST_CLK */

/** @} */ /* End of group __1986BE9x_StdPeriph_Driver */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_rst_clk.c */

