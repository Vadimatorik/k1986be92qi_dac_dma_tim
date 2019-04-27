#include "main.h"

int main (void)
{
  HSE_Clock_ON();                                  //Разрешаем использование HSE генератора. 
  HSE_Clock_OffPLL();                              //Настраиваем "путь" сигнала и включаем тактирование от HSE генератора.
  Buzzer_out_DAC_init();                           //Настраиваем порт для ЦАП.
  DAC_Init();                                      //Настраиваем ЦАП.
  DMA_to_DAC_and_TIM1();                           //Настраиваем DMA для работы с DAC2 через таймер 1.
  Init_TIMER1_to_DMA_and_DAC2();                   //Настраиваем таймер 1.
    
  while (1) 
        {                    
        }
}