#include "1986BE92QI_CLK.h"

void HSE_PLL (uint8_t PLL_multiply)                                                              //Сюда передаем частоту в разах "в 2 раза" например. 
{
	RST_CLK->PLL_CONTROL  = RST_CLK->PLL_CONTROL&(~(0xF<<8));                                      //Удаляем старое значение.
	RST_CLK->PLL_CONTROL |= PLL_CONTROL_PLL_CPU_ON|((PLL_multiply-1)<<8)|PLL_CONTROL_PLL_CPU_PLD;  //Включаем PLL и включаем умножение в X раз, а так же перезапускаем PLL.
	RST_CLK->CPU_CLOCK   |= HCLK_SEL(CPU_C3)|CPU_C2_SEL(CPU_C2_SEL)|CPU_C1_SEL(HSE);               //Настриваем "маршрут" частоты через PLL и включаем тактирование от HSE.
}

void Init_SysTick (void)                          
{
   SysTick->LOAD = 80000000/261.63/100-1;                 
   SysTick->CTRL |= CLKSOURCE|TCKINT|ENABLE;
}

volatile uint16_t Loop = 0;
volatile uint32_t Delay_dec = 0; 
void SysTick_Handler (void)
{
	
}
