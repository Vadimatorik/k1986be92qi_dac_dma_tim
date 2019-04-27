   /* */

/*
	const uint32_t MES[12] = {191, 180, 170, 161, 152, 143, 135, 128, 120, 114, 107, 101};
int main (void)
{
	Buzzer_out_init();                               //Инициализируем пин, пин звукового генератора. 
	Init_SysTick_micro();                            //Инициализируем системный таймер для счета мллисекунд. 
  while (1)                                        //Создаем колебания с частотой 130.82 гц.
	{
		
		}
	}
	
	
}
*/

/*
void Led_init (void)
{
  RST_CLK->PER_CLOCK |=(1<<23);                   //Включаем тактирование порта C.
	PORTC->OE |= 1;                                 //Порт - выход.
	PORTC->ANALOG |= 1;                             //Порт - цифоровой. 
	PORTC->PWR |= 1;                                //Порт - медленный режим.
}
*/

/*
void Init_SysTick_milli (void)                    //Прерывание раз в миллисекунду. 
{
	SysTick->LOAD = (8000000/1000)-1;              
	SysTick->CTRL |= CLKSOURCE|TCKINT|ENABLE;
}*/





/*
//if (Delay_dec) Delay_dec--;
void Delay (uint32_t Delay_Data)                  //Функция задержки на основе SysTick таймера. 
{
	Delay_dec = Delay_Data;
	while (Delay_dec) {};
}
*/

/*
void Block (void)                                //Подпрограмма ожидания (защиты).
{
	PORTC->RXTX |= 1;
	Delay_ms (1000);
	PORTC->RXTX = 0;
	Delay_ms (1000);
}*/



	//Init_SysTick();                               //Инициализируем системный таймер. 
	
	//Led_init();                                     //Инициализируем ножку 0 порта C для светодиода. 
	//Block();                                        //Подпрограмма ожидания (защиты).
	//HSE_Clock_ON();                                 //Разрешаем использование HSE генератора. 
	//HSE_PLL(1);                                     //Включаем тактирование с умножением 2
	
	//uint8_t PLL_Data = 1;                           //Здесь храним коэффициент умножения. 
	
//const uint32_t MES[13] = {191, 180, 170, 161, 152, 143, 135, 128, 120, 114, 107, 101, 96};