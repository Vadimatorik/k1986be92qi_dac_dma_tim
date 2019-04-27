/* Includes ------------------------------------------------------------------*/
#include "1986BE9x_it.h"
#include "mlt_lcd.h"
#include "font.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/ 
int extern count_title;
int extern MenuMainItem;
int extern CursorPosItem;
char extern UartFlag;
char extern Can1Flag;
char extern Can2Flag;
char extern TestLedDone;
char extern LedFlag;

int count_main = 0;

uint8_t* main_string[]  = 
{
	 cyr_O,  cyr_t,  cyr_l,  cyr_a,  cyr_d,  cyr_o, cyr_ch,  cyr_n,  cyr_y, cyr_jj,
	sym_sp,  cyr_k,  cyr_o,  cyr_m,  cyr_p,  cyr_l,  cyr_e,  cyr_k,  cyr_t, sym_sp,
	 cyr_m,  cyr_i,  cyr_k,  cyr_r,  cyr_o,  cyr_k,  cyr_o,  cyr_n,  cyr_t,  cyr_r,
	 cyr_o,  cyr_l,  cyr_l,  cyr_e,  cyr_r,  cyr_o,  cyr_v, sym_sp,  dig_1,  dig_9,
	 dig_8,  dig_6,  cyr_V,  cyr_E,	 dig_9,  dig_1,  cyr_T,  dig_1, sym_pt, sym_sp,
	 cyr_Z,  cyr_A,  cyr_O, sym_sp,  cyr_P,  cyr_K,  cyr_K, sym_sp,  cyr_M,  cyr_i,
	 cyr_l,  cyr_a,  cyr_n,  cyr_d,	 cyr_r, sym_pt, sym_sp, lat_w,	 lat_w,	 lat_w,
	sym_pt,  lat_m,  lat_i,  lat_l,  lat_a,  lat_n,  lat_d,  lat_r, sym_pt,	 lat_r,
	 lat_u
};

uint8_t* menu_string[] =
{
sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,lat_L,lat_E,lat_D,lat_S,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,
sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,lat_U,lat_A,lat_R,lat_T,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,
sym_sp,sym_sp,sym_sp,sym_sp,lat_C,lat_A,lat_N,sym_sp,dig_1,dig_2,dig_5,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,
sym_sp,sym_sp,sym_sp,sym_sp,lat_C,lat_A,lat_N,sym_sp,dig_5,dig_0,dig_0,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,
sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,lat_F,lat_L,lat_A,lat_S,lat_H,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,
sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,lat_R,lat_A,lat_M,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,
sym_sp,sym_sp,sym_sp,sym_sp,lat_E,lat_T,lat_H,lat_E,lat_R,lat_N,lat_E,lat_T,sym_sp,sym_sp,sym_sp,sym_sp
};
uint8_t* uart_string[]  =
{
	sym_sp,cyr_T,cyr_e,cyr_s,cyr_t,sym_sp,lat_C,lat_O,lat_M,sym_sp,cyr_p,cyr_o,cyr_r,lat_t,cyr_a,sym_sp
};
uint8_t* can_string[]  =
{
	sym_sp,cyr_T,cyr_e,cyr_s,cyr_t,sym_sp,lat_C,lat_A,lat_N,sym_sp,cyr_p,cyr_o,cyr_r,lat_t,cyr_a,sym_sp
};
uint8_t* flash_string[]  =
{
sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,lat_F,lat_L,lat_A,lat_S,lat_H,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp
};
uint8_t* ram_string[]  =
{
	sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,lat_R,lat_A,lat_M,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp
};
uint8_t* eth_string[]  =
{
	sym_sp,sym_sp,sym_sp,sym_sp,lat_E,lat_T,lat_H,lat_E,lat_R,lat_N,lat_E,lat_T,sym_sp,sym_sp,sym_sp,sym_sp
};
uint8_t* module_string[]  =
{
	sym_sp,sym_sp,sym_sp,cyr_T,cyr_e,cyr_s,cyr_t,sym_sp,cyr_M,cyr_o,cyr_d,cyr_u,cyr_l,cyr_ya,sym_sp,sym_sp
};
uint8_t* led_string[]  =
{
	cyr_T,cyr_e,cyr_s,cyr_t,sym_sp,cyr_I,cyr_n,cyr_d,cyr_i,cyr_k,cyr_a,cyr_t,cyr_o,cyr_r,cyr_o,cyr_v
};
uint8_t* empty_string[]  =
{
	sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp
};

uint8_t* pass_string[]  =
{
	sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,cyr_P,cyr_r,cyr_o,cyr_sh,cyr_e,cyr_l,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp
};
uint8_t* fail_string[]  =
{
	sym_sp,sym_sp,sym_sp,cyr_N,cyr_e,sym_sp,cyr_p,cyr_r,cyr_o,cyr_sh,cyr_e,cyr_l,sym_sp,sym_sp,sym_sp,sym_sp
};
uint8_t* finish_string[]  =
{
	sym_sp,sym_sp,sym_sp,sym_sp,sym_sp,cyr_G,cyr_o,cyr_t,cyr_o,cyr_v,cyr_o,sym_sp,sym_sp,sym_sp,sym_sp,sym_sp
};

uint8_t* bottom_string[]  =
{
	cyr_M,  cyr_i,	 cyr_l,  cyr_a,  cyr_n,  cyr_d,	 cyr_r
};
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}
/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
/*******************************************************************************
* Function Name  : MemManage_Handler
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}
/*******************************************************************************
* Function Name  : BusFault_Handler
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
/*******************************************************************************
* Function Name  : UsageFault_Handler
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
/*******************************************************************************
* Function Name  : SVC_Handler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVC_Handler(void)
{
}
/*******************************************************************************
* Function Name  : DebugMon_Handler
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMon_Handler(void)
{
}
/*******************************************************************************
* Function Name  : PendSV_Handler
* Description    : This function handles Debug PendSV exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSV_Handler(void)
{
}
/*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Handler(void)
{
}
/*******************************************************************************
* Function Name  : CAN1_IRQHandler
* Description    : This function handles CAN1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN1_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : CAN2_IRQHandler
* Description    : This function handles CAN2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN2_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : USB_IRQHandler
* Description    : This function handles USB global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : DMA_IRQHandler
* Description    : This function handles DMA global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : UART1_IRQHandler
* Description    : This function handles UART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART1_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : UART2_IRQHandler
* Description    : This function handles UART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART2_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : SSP1_IRQHandler
* Description    : This function handles SSP1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP1_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : I2C_IRQHandler
* Description    : This function handles I2C global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : POWER_IRQHandler
* Description    : This function handles POWER global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void POWER_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : WWDG_IRQHandler
* Description    : This function handles WWDG global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : Timer1_IRQHandler
* Description    : This function handles Timer1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer1_IRQHandler(void)
{
int i;
	TIMER1->STATUS = 0;

	if (count_title == 0)
	{
		count_title = 1;
		
		LcdPutImage (icon_mil, 0, 0,1, 1);

		LcdPutChar (cyr_M, 8, 0);  LcdPutChar (cyr_i, 9, 0);  LcdPutChar (cyr_l, 10, 0);
		LcdPutChar (cyr_a, 11, 0); LcdPutChar (cyr_n, 12, 0); LcdPutChar (cyr_d, 13, 0);
		LcdPutChar (cyr_r, 14, 0);
  	}

	//scroll main string
	while (!LcdScrollString (main_string,7,81,count_main));
	count_main++;
	if (count_main == 97) count_main = 0;
	//
	if (UartFlag == 1)
	{
		LcdPutString (empty_string, 3); LcdPutChar (sym_sp, 15, 3);
		LcdPutString (uart_string, 4); LcdPutChar (sym_sp, 15, 4);
		LcdPutString (empty_string, 5); LcdPutChar (sym_sp, 15, 5);
		
	}
	else if (Can1Flag == 1)
	{
		LcdPutString (empty_string, 3); LcdPutChar (sym_sp, 15, 3);
		LcdPutString (can_string, 4); LcdPutChar (sym_sp, 15, 4);
		LcdPutString (empty_string, 5); LcdPutChar (sym_sp, 15, 5);
	}
	else if (Can2Flag == 1)
	{
		LcdPutString (empty_string, 3); LcdPutChar (sym_sp, 15, 3);
		LcdPutString (can_string, 4); LcdPutChar (sym_sp, 15, 4);
		LcdPutString (empty_string, 5); LcdPutChar (sym_sp, 15, 5);
	}
	else if (LedFlag == 1)
	{
		LcdPutString (led_string, 3);
		LcdPutString (empty_string, 4); LcdPutChar (sym_sp, 15, 4);
		if (TestLedDone == 1) 
		{
			LcdPutString (finish_string, 5); LcdPutChar (sym_sp, 15, 5);
		}
		else 
		{
			LcdPutString (empty_string, 5); LcdPutChar (sym_sp, 15, 5);
		} 
	}
	else
	{
		if (CursorPosItem == 0)
		{
			for (i=0;i<16;i++) LcdPutChar(menu_string[16*(MenuMainItem+0)+i],i,3);
			for (i=0;i<16;i++) LcdPutChar(menu_string[16*(MenuMainItem+1)+i],i,4);
			for (i=0;i<16;i++) LcdPutChar(menu_string[16*(MenuMainItem+2)+i],i,5);
			LcdPutChar (cursor, 15, 3);
		}
		if (CursorPosItem == 1)
		{
			for (i=0;i<16;i++) LcdPutChar(menu_string[16*(MenuMainItem-1)+i],i,3);
			for (i=0;i<16;i++) LcdPutChar(menu_string[16*(MenuMainItem+0)+i],i,4);
			for (i=0;i<16;i++) LcdPutChar(menu_string[16*(MenuMainItem+1)+i],i,5);
			LcdPutChar (cursor, 15, 4);
		}
		if (CursorPosItem == 2)
		{
			for (i=0;i<16;i++) LcdPutChar(menu_string[16*(MenuMainItem-2)+i],i,3);
			for (i=0;i<16;i++) LcdPutChar(menu_string[16*(MenuMainItem-1)+i],i,4);
			for (i=0;i<16;i++) LcdPutChar(menu_string[16*(MenuMainItem+0)+i],i,5);
			LcdPutChar (cursor, 15, 5);
		}
	}
}
/*******************************************************************************
* Function Name  : Timer2_IRQHandler
* Description    : This function handles Timer2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer2_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : Timer3_IRQHandler
* Description    : This function handles Timer3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer3_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : ADC_IRQHandler
* Description    : This function handles ADC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : COMPARATOR_IRQHandler
* Description    : This function handles COMPARATOR global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void COMPARATOR_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : SSP2_IRQHandler
* Description    : This function handles SSP2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP2_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : BACKUP_IRQHandler
* Description    : This function handles BACKUP global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BACKUP_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : EXT_INT1_IRQHandler
* Description    : This function handles EXT_INT1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT1_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : EXT_INT2_IRQHandler
* Description    : This function handles EXT_INT2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT2_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : EXT_INT3_IRQHandler
* Description    : This function handles EXT_INT3 global interrupt request. 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT3_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : EXT_INT4_IRQHandler
* Description    : This function handles EXT_INT4 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT4_IRQHandler(void)
{
}
