#include "1986BE9x.h"

#define HWREG(x)                                                              \
        (*((volatile unsigned long *)(x)))

void WriteFLASH(uint32_t ADR, uint32_t DATA);
uint32_t ReadFLASH(uint32_t ADR);
void EraseFullFLASH(void);
void EraseSectorFLASH(uint32_t sector);
uint8_t DataCompare(uint32_t *mem);
uint8_t NullCompare(uint32_t *mem);
