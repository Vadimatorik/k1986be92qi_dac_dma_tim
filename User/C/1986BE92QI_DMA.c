#include "1986BE92QI_DMA.h"

struct DAC_ST
{
    uint32_t Destination_end_pointer;                                     //Указатель конца данных приемника.
    uint32_t Source_end_pointer;                                          //Указатель конца данных источника
    uint32_t channel_cfg;                                                 //Конфигурация канала.
    uint32_t NULL;                                                        //Пустая ячейка. 
} 

__align(1024) DAC_ST;                                                   //Выравниваем массив структур по 1024 байта. 
struct DAC_ST DAC_ST_ADC[32+32];                                        //Создаем массив структур для всех каналов. 

uint16_t C_4[100] = {0x7FF, 0x803, 0x808, 0x80C, 0x810, 0x815, 0x819, 0x81D, 0x821, 0x825, 0x828, 0x82C, 0x82F, 0x832, 0x835, 0x838, 0x83A, 0x83C, 0x83E, 0x840, 0x842, 0x843, 0x844, 0x844, 0x845, 0x845, 0x845, 0x844, 0x844, 0x843, 0x842, 0x840, 0x83E, 0x83C, 0x83A, 0x838, 0x835, 0x832, 0x82F, 0x82C, 0x828, 0x825, 0x821, 0x81D, 0x819, 0x815, 0x810, 0x80C, 0x808, 0x803, 0x7FF, 0x7FB, 0x7F6, 0x7F2, 0x7EE, 0x7E9, 0x7E5, 0x7E1, 0x7DD, 0x7D9, 0x7D6, 0x7D2, 0x7CF, 0x7CC, 0x7C9, 0x7C6, 0x7C4, 0x7C2, 0x7C0, 0x7BE, 0x7BC, 0x7BB, 0x7BA, 0x7BA, 0x7B9, 0x7B9, 0x7B9, 0x7BA, 0x7BA, 0x7BB, 0x7BC, 0x7BE, 0x7C0, 0x7C2, 0x7C4, 0x7C6, 0x7C9, 0x7CC, 0x7CF, 0x7D2, 0x7D6, 0x7D9, 0x7DD, 0x7E1, 0x7E5, 0x7E9, 0x7EE, 0x7F2, 0x7F6, 0x7FB};

//Источник/приемник = 16 бит, отправляем/принимаем = 16 бит, защиты нет, 50 передач, пинг-понг.
uint32_t DMA_DAC_InitST_PR  = dst_src|src_inc|src_size|dst_size|n_minus_1|cycle_ctrl;
uint32_t DMA_DAC_InitST_ALT = dst_src|src_inc|src_size|dst_size|n_minus_1|cycle_ctrl;

//-------------------------------------------------
//Настраиваем DMA для связки с DAC.
//-------------------------------------------------
void DMA_to_DAC_and_TIM1 (void) 
{
  //Настраиваем первичную структуру.
  DAC_ST_ADC[10-1].Destination_end_pointer = (uint32_t)C_4 + (sizeof(C_4))/2 - 1;       //Указатель на последний элемент середины массива (C_4 - массив значений синусоидального сигнала в 100 значений).
  DAC_ST_ADC[10-1].Source_end_pointer = (uint32_t)&(DAC->DAC2_DATA);                    //Указатель на последний (не меняется) адрес приемника (регистр данных DAC).
  DAC_ST_ADC[10-1].channel_cfg = (uint32_t)(DMA_DAC_InitST_PR);                         //Структура настройки первичной структуры.
  DAC_ST_ADC[10-1].NULL = (uint32_t)0;                                                  //Пустая ячейка.
  //Настройка альтернативной структуры. 
  DAC_ST_ADC[10-1+32].Destination_end_pointer = (uint32_t)C_4 + sizeof(C_4) - 1;        //Указатель на последний элемент массива (C_4 - массив значений синусоидального сигнала в 100 значений).
  DAC_ST_ADC[10-1+32].Source_end_pointer = (uint32_t)&(DAC->DAC2_DATA);                 //Указатель на последний (не меняется) адрес приемника (регистр данных DAC).
  DAC_ST_ADC[10-1+32].channel_cfg = (uint32_t)(DMA_DAC_InitST_ALT);                     //Структура настройки альтернативной структуры.
  DAC_ST_ADC[10-1+32].NULL = (uint32_t)0;                                               //Пустая ячейка.
  
  //Настраиваем контроллер DMA.
  RST_CLK->PER_CLOCK|=PCLK_EN_DMA;                                                      //Включаем тактирование DMA.
  DMA->CTRL_BASE_PTR = (uint32_t)&DAC_ST_ADC;                                           //Указываем адрес массива структур. 
  DMA->CFG = CFG_master_enable;                                                         //Разрешаем работу DMA.
    
  //Настраиваем канал. 
  DMA->CHNL_ENABLE_SET   = 1<<10;                                                       //Разрешаем работу 10 канала.
}

#define ST_Play_P           (DAC_ST_ADC[10-1].channel_cfg    & (1023<<4))               //Для проверки колличества оставшихся передачь в первичной сруктуре.
#define ST_Play_ALT         (DAC_ST_ADC[10-1+32].channel_cfg & (1023<<4))               //Для проверки колличества оставшихся передачь в альтернативной сруктуре.
void Timer2_IRQHandler (void)                                                           //Меняем структуры.
{
    if ((ST_Play_P == 0) && (ST_Play_ALT <= (48<<4))) //Если прошли первую половину и уже начата передача второй - переключиться на 2-ю.	
  	DAC_ST_ADC[10-1].channel_cfg = (uint32_t)(DMA_DAC_InitST_PR); 
    if ((ST_Play_ALT == 0) && (ST_Play_P <= (48<<4)))
  	DAC_ST_ADC[10-1+32].channel_cfg = (uint32_t)(DMA_DAC_InitST_ALT); 
    DMA->CHNL_ENABLE_SET   = 1<<10; 
    TIMER2->STATUS=0;    
}