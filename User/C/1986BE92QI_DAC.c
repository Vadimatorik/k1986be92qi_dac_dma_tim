#include "1986BE92QI_DAC.h"
void DAC_Init (void)
{
	RST_CLK->PER_CLOCK |= PCLK_EN(DAC);             //Включаем тактирование ЦАП.
	DAC->CFG = CFG_Cfg_ON_DAC1;                     //Включаем ЦАП2. Ассинхронно. От внутреннего источника.
}