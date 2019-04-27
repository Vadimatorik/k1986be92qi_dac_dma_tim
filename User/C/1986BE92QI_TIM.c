#include "1986BE92QI_TIM.h"
void Init_TIMER1_to_DMA_and_DAC2 (void)
{
  RST_CLK->PER_CLOCK |= PER_CLOCK_TIMER1_ONCLK|PER_CLOCK_TIMER2_ONCLK;                   //Включаем тактирование таймера 1 и 2.
  RST_CLK->TIM_CLOCK = 0;                                                                //Отключаем тактирование таймеров.
    
  //У нас 8000000 Гц/261.63/100 = 305.
  TIMER1->ARR = 305;                                                                     //Считаем до...
  TIMER1->DMA_RE |= DMA_RE_CNT_ARR_EVENT_RE;                                             //Разрешаем пинать DMA.

  TIMER2->ARR = 305*25;                                                                  //После передачи половины массива.
  TIMER2->IE  = TIMERx_IE_CNT_ARR_EVENT_IE;                                              //Прерывание по достижении границы. 
  TIMER2->STATUS=0;                                                                      //Сбрасываем флаги прерываний. 
  NVIC->ISER[0] = 1<<15;                                                                 //Разрешили прерывание от таймера 2.
    
  TIMER1->CNTRL = CNTRL_CNT_EN;                                                          //Разрешаем работу таймеров.
  TIMER2->CNTRL = CNTRL_CNT_EN;      
    
  RST_CLK->TIM_CLOCK = TIM_CLOCK_TIM1_CLK_EN|TIM_CLOCK_TIM2_CLK_EN;                      //Подаем тактовый сигнал на таймеры.
}