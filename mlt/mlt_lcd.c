#include "mlt_lcd.h"

void SetDataBits (uint8_t value)
{
	PORTA->RXTX &= 0xFFC0;
	PORTA->RXTX |= (value & 0x3F); 
	PORTF->RXTX &= 0xFFF3;
	PORTF->RXTX |= ((value>>4) & 0x0c); 
}

void MltDelay (uint32_t value)
{
	while ((value--)!=0);
}

uint8_t ReadStatus (uint8_t Chip)
{
uint8_t data;

	Data_Dir_InputPA;
	Data_Dir_InputPF;
	if (Chip == 1) {Set_E1_Pin;}
	else {Set_E2_Pin;}
	Clr_A0_Pin;
	Set_RW_Pin;
	MltDelay(5);
	Set_Stb_Pin;
	MltDelay(5);
	data = OutputData;
	MltDelay(5);
	Clr_Stb_Pin;
	MltDelay(5);
	Clr_A0_Pin;
	Clr_RW_Pin;
	if (Chip == 1) {Clr_E1_Pin;}
	else {Clr_E2_Pin;}


	return data;
}

void DispOn (uint8_t Chip)
{
	if (Chip == 1) {Set_E1_Pin;}
	else {Set_E2_Pin;}
	Clr_A0_Pin;
	Clr_RW_Pin;
	MltDelay(5);
	Data_Dir_OutputPA;
	Data_Dir_OutputPF;
	SetDataBits (0x3F);
	MltDelay(5);
	Set_Stb_Pin;
	MltDelay(5);
	Clr_Stb_Pin;
	MltDelay(5);
	Clr_A0_Pin;
	Clr_RW_Pin;
	Data_Dir_InputPA;
	Data_Dir_InputPF;
	if (Chip == 1) {Clr_E1_Pin;}
	else {Clr_E2_Pin;}
}

void DispOff (uint8_t Chip)
{
	if (Chip == 1) {Set_E1_Pin;}
	else {Set_E2_Pin;}
	Clr_A0_Pin;
	Clr_RW_Pin;
	MltDelay(5);
	Data_Dir_OutputPA;
	Data_Dir_OutputPF;
	SetDataBits (0x3E);
	MltDelay(5);
	Set_Stb_Pin;
	MltDelay(5);
	Clr_Stb_Pin;
	MltDelay(5);
	Clr_A0_Pin;
	Clr_RW_Pin;
	Data_Dir_InputPA;
	Data_Dir_InputPF;
	if (Chip == 1) {Clr_E1_Pin;}
	else {Clr_E2_Pin;}
}

void SetPage (uint8_t Chip,uint8_t page)
{
	if (Chip == 1) {Set_E1_Pin;}
	else {Set_E2_Pin;}
	Clr_A0_Pin;
	Clr_RW_Pin;
	MltDelay(5);
	Data_Dir_OutputPA;
	Data_Dir_OutputPF;
	SetDataBits (0xB8 | page);
	MltDelay(5);
	Set_Stb_Pin;
	MltDelay(5);
	Clr_Stb_Pin;
	MltDelay(5);
	Data_Dir_InputPA;
	Data_Dir_InputPF;
	Clr_A0_Pin;
	Clr_RW_Pin;
	if (Chip == 1) {Clr_E1_Pin;}
	else {Clr_E2_Pin;}
}

void SetAdress (uint8_t Chip,uint8_t adress)
{
	if (Chip == 1) {Set_E1_Pin;}
	else {Set_E2_Pin;}
	Clr_A0_Pin;
	Clr_RW_Pin;
	MltDelay(5);
	Data_Dir_OutputPA;
	Data_Dir_OutputPF;
	SetDataBits (0x40 | adress);
	MltDelay(5);
	Set_Stb_Pin;
	MltDelay(5);
	Clr_Stb_Pin;
	MltDelay(5);
	Data_Dir_InputPA;
	Data_Dir_InputPF;
	Clr_A0_Pin;
	Clr_RW_Pin;
	if (Chip == 1) {Clr_E1_Pin;}
	else {Clr_E2_Pin;}
}

void WriteData (uint8_t Chip,uint8_t data)
{
	if (Chip == 1) {Set_E1_Pin;}
	else {Set_E2_Pin;}
	Set_A0_Pin;
	Clr_RW_Pin;
	MltDelay(5);
	Data_Dir_OutputPA;
	Data_Dir_OutputPF;
	SetDataBits (data);
	MltDelay(5);
	Set_Stb_Pin;
	MltDelay(5);
	Clr_Stb_Pin;
	MltDelay(5);
	Data_Dir_InputPA;
	Data_Dir_InputPF;
	Clr_A0_Pin;
	Clr_RW_Pin;
	if (Chip == 1) {Clr_E1_Pin;}
	else {Clr_E2_Pin;}
}

uint8_t ReadData (uint8_t Chip)
{
uint8_t data;

	if (Chip == 1) {Set_E1_Pin;}
	else {Set_E2_Pin;}
	Set_A0_Pin;
	Set_RW_Pin;
	MltDelay(5);
	Data_Dir_InputPA;
	Data_Dir_InputPF;
	SetDataBits (data);
	MltDelay(5);
	Set_Stb_Pin;
	MltDelay(5);
	data = OutputData;
	MltDelay(5);
	Clr_Stb_Pin;
	MltDelay(5);
	Clr_A0_Pin;
	Clr_RW_Pin;
	if (Chip == 1) {Clr_E1_Pin;}
	else {Clr_E2_Pin;}
	return (data);
}

void LcdInit(void)
{
uint8_t s1,s2;
 
	Clr_Res_Pin;
	MltDelay (200);
	Set_Res_Pin;
	do
	{
		s1 = ReadStatus(1) & 0x90;
		s2 = ReadStatus(2) & 0x90;
	}
	while (s1 != 0x00 && s2 != 0x00);
}

void LcdClearPage (uint8_t Chip,uint8_t Page)
{
int i;
uint8_t s1;

	SetPage (Chip,Page);
	SetAdress (Chip,0x00);

	for (i=0;i<64;i++)
	{	
		do
		{
			s1 = ReadStatus(Chip);
		} while (s1 & 0x80 != 0x00);
		WriteData (Chip,0x00);
	}
}

void LcdClearChip (uint8_t Chip)
{
int i;

	for (i=0;i<8;i++)
	{
		LcdClearPage (Chip,i);
	}
}

void LcdPutChar (uint8_t* array, int Xpos, int Ypos)
{
int chp,page,adr;
int i;
uint8_t s1;

	chp  = (int)(Xpos/8)+1;
	page = Ypos;
	adr  = (int)((Xpos % 8)*8);	

	SetPage (chp,page);
	SetAdress (chp,adr);

	for (i=0;i<8;i++)
	{	
		do
		{
			s1 = ReadStatus(chp);
		} while (s1 & 0x80 != 0x00);
		WriteData (chp,array[i]);
	}
}

void LcdPutString (uint8_t** array, int Ypos)
{
int i,j;
uint8_t s1;

	
	SetPage (1,Ypos);
	SetAdress (1,0);

	for (i=0;i<8;i++)
	{
		for (j=0;j<8;j++)
		{
		do
		{
			s1 = ReadStatus(1);
		} while (s1 & 0x80 != 0x00);
		WriteData (1,array[i][j]);
		}
	}
	
	SetPage (2,Ypos);
	SetAdress (2,0);

	for (i=0;i<8;i++)
	{
		for (j=0;j<8;j++)
		{
		do
		{
			s1 = ReadStatus(2);
		} while (s1 & 0x80 != 0x00);
		WriteData (2,array[i+8][j]);
		}
	}

}

int LcdScrollString (uint8_t** array, int Ypos, int size,int cnt)
{
int j;
uint8_t* print[16];
uint8_t  space[8]= {  0,   0,   0,   0,   0,   0,   0,   0};
	
	
	if (cnt < 15)
	{
		for (j=0;j<16;j++)
		{
			if (cnt+j < 15)
			{
				print[j] = space;
			}
			else
			{
				print[j] = array[j+cnt-15];
			}	
		}
		LcdPutString (print, Ypos);
	}
	else
	{
		for (j=0;j<16;j++)
		{
			if (cnt-15+j >= size)
			{
				print[j] = space;
			}
			else
			{
				print[j] = array[j+cnt-15];
			}	
		}
		LcdPutString (print, Ypos);
	}

	return 1;
}

void LcdPutImage (uint8_t* array, int Ypos1, int Xpos1,int Ypos2, int Xpos2)
{
int i,j,y;
int chp,page,adr;
uint8_t s1;
int cnt=0;	

	for	(i=Ypos1;i<=Ypos2;i++)
	{
		for (j=Xpos1;j<=Xpos2;j++)
		{
			chp  = (int)(j/8)+1;
			page = i;
			adr  = (int)((j % 8)*8);

			SetPage (chp,page);
			SetAdress (chp,adr);
			
			for (y=0;y<8;y++)
			{
				do
				{
					s1 = ReadStatus(chp);
				} while (s1 & 0x80 != 0x00);
				WriteData (chp,array[cnt+y]);
			}
			cnt+=8;
		}	
	}
	
}



