#include "MilFlash.h"
#include "1986BE9x.h"

void WriteFLASH(uint32_t ADR, uint32_t DATA)
{	
int i;	  
uint32_t status;
    /* Configure PORTA pins 0..15 for inout ExtBus data  */
	PORTA->OE = 0xFFFFFFFF;
	PORTB->OE = 0xFFFFFFFF;
	
HWREG(0x10000000 + 0x555*4) = 0xAAAAAAAA;
HWREG(0x10000000 + 0x2AA*4) = 0x55555555;
HWREG(0x10000000 + 0x555*4) = 0xA0A0A0A0;
HWREG(ADR) = DATA;

for (i=0;i<1000;i++){}
	PORTA->OE = 0x00000000;
	PORTB->OE = 0x00000000;
do status = HWREG(ADR);
while ((status & 0x80808080) == ((~DATA) & 0x80808080));
		  
}

uint32_t ReadFLASH(uint32_t ADR)
{
	PORTA->OE = 0x00000000;
	PORTB->OE = 0x00000000;		  
return (HWREG(ADR));
}

void EraseFullFLASH(void)
{
uint32_t status;
	PORTA->OE = 0xFFFFFFFF;
	PORTB->OE = 0xFFFFFFFF;
HWREG(0x10000000 + 0x555*4) = 0xAAAAAAAA;
HWREG(0x10000000 + 0x2AA*4) = 0x55555555;
HWREG(0x10000000 + 0x555*4) = 0x80808080;
HWREG(0x10000000 + 0x555*4) = 0xAAAAAAAA;
HWREG(0x10000000 + 0x2AA*4) = 0x55555555;
HWREG(0x10000000 + 0x555*4) = 0x10101010;

	PORTA->OE = 0x00000000;
	PORTB->OE = 0x00000000;
do status = HWREG(0x10000000);
while ((status & 0x80808080) != 0x80808080);
}
