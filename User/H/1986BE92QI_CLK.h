#ifndef  CLK_H
#define CLK_H
#include "1986be9x_config.h"                                   //Стандартные.
#include "1986BE9x.h"

//-------------------------------------------------
//Маски бит.
//-------------------------------------------------
#define HCLK_SEL(CPU_C3)       (1<<8)
#define CPU_C1_SEL(HSE)        (1<<1)
#define CPU_C2_SEL(CPU_C2_SEL) (1<<2)
#define PCLK_EN(RST_CLK)       (1<<4)
#define HS_CONTROL(HSE_ON)     (1<<0)
#define REG_0F(HSI_ON)        ~(1<<22)
#define RTC_CS(ALRF)           (1<<2)
#define PCLK(BKP)              (1<<27)

#define RST_CLK_ON_Clock()       RST_CLK->PER_CLOCK |= PCLK_EN(RST_CLK)                 //Включаем тактирование контроллера тактовой частоты (по умолчанию включено).
#define HSE_Clock_ON()           RST_CLK->HS_CONTROL = HS_CONTROL(HSE_ON)               //Разрешаем использование HSE генератора. 
#define HSE_Clock_OffPLL()       RST_CLK->CPU_CLOCK  = CPU_C1_SEL(HSE)|HCLK_SEL(CPU_C3);//Настраиваем "путь" сигнала и включаем тактирование от HSE генератора.

#define PLL_CONTROL_PLL_CPU_ON  (1<<2)                                                  //PLL включена. 
#define PLL_CONTROL_PLL_CPU_PLD (1<<3)                                                  //Бит перезапуска PLL.

//-------------------------------------------------
//SysTick.
//-------------------------------------------------
#define CLKSOURCE (1<<2)                          //Указывает источник синхросигнала: 0 - LSI, 1 - HCLK.
#define TCKINT    (1<<1)                          //Разрешает запрос на прерывание от системного таймера.
#define ENABLE    (1<<0)                          //Разрешает работу таймера.

//-------------------------------------------------
//Функции
//-------------------------------------------------
void HSE_PLL (uint8_t PLL_multiply);              //Сюда передаем частоту в разах "в 2 раза" например (умножитель).
void Init_SysTick (void);                         //Инициализируем системный таймер.
void SysTick_Handler (void);                      //Прерывание от системного таймера.
#endif