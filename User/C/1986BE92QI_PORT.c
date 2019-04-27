#include "1986BE92QI_PORT.h"
void Buzzer_out_init (void)
{
	RST_CLK->PER_CLOCK |= PER_CLOCK_PORTE;          //Включаем тактирование порта E.
	PORTE->OE |= PORT_OE_OUT_PORTE_0;               //Выход. 
	PORTE->ANALOG |= ANALOG_EN_DIGITAL_PORTE_0;     //Цифровой.
	PORTE->PWR |= PWR_MAX_PORTE_0;                  //Максимальная скорость (около 10 нс).
}

void Buzzer_out_DAC_init (void)
{
	RST_CLK->PER_CLOCK |= PER_CLOCK_PORTE;          //Включаем тактирование порта E.
	PORTE->OE |= PORT_OE_OUT_PORTE_0;               //Выход. 
	PORTE->ANALOG = 0;                              //Аналоговый.
	PORTE->PWR |= PWR_MAX_PORTE_0;                  //Максимальная скорость (около 10 нс).
}