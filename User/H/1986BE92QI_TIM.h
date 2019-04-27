#ifndef  TIM_H
#define TIM_H
#include "1986be9x_config.h"                                   //Стандартные.
#include "1986BE9x.h"

//----------------------------------------------------------
//Маски бит.
//----------------------------------------------------------
#define PER_CLOCK_TIMER1_ONCLK             (1<<14) //Маска разрешения тактирования таймера 1.
#define PER_CLOCK_TIMER2_ONCLK             (1<<15) //Маска разрешения тактирования таймера 1.
#define TIM_CLOCK_TIM1_CLK_EN              (1<<24) //Маска включения частоты на таймере 1.
#define SHARE_HCLK_TIMER1                   7      //Делим тактовую частоту HCLK на... (0 = не делим, 1 = /2, 2 = /4).
#define TIM_CLOCK_TIM1_BRG   (SHARE_HCLK_TIMER1<<0) //Делим частоту на таймере 1 на SHARE_HCLK_TIMER.
#define CNTRL_CNT_EN                       (1<<0)  //Маска включения таймера.
#define CNTRL_EVENT_SEL                    (1<<8)  //Маска выбора сточник события: CNT == ARR;
#define DMA_RE_CNT_ARR_EVENT_RE            (1<<1)  //Маска разрешения запроса DMA при событии CNT == ARR;
#define IE_CNT_ARR_EVENT_IE                (1<<1)  //Маска разрешения прерывания при событии CNT == ARR;
#define TIM_CLOCK_TIM2_CLK_EN              (1<<25) //Маска включения частоты на таймере 2.
#define SHARE_HCLK_TIMER2                   7      //Делим тактовую частоту HCLK на... (0 = не делим, 1 = /2, 2 = /4).
#define TIM_CLOCK_TIM2_BRG   (SHARE_HCLK_TIMER2<<8)//Делим частоту на таймере 1 на SHARE_HCLK_TIMER.

#define CH1_CNTRL_CAP_nPWM_Z               (1<<15) //Маска: какнал в режиме "захват". 
#define CH1_CNTRL_CHPSC_8                  (3<<6)  //Маска: предворительный делитель для канала на 8.
#define CHy_CNTRL2_CCR1_EN                 (1<<2)  //Маска: включить канал 1.
#define TIMERx_IE_CNT_ARR_EVENT_IE         (1<<1)  //Маска: Флага разрешения прерывания по событию совпадения CNT и ARR.
//-------------------------------------------------
//Функции
//-------------------------------------------------
void Init_TIMER1_to_DMA_and_DAC2 (void);           //Настройка таймера для "пинков" DMA.
#endif