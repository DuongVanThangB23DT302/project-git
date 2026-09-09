#ifndef RCC_H
#define RCC_H

#include <stdint.h>

void RCC_EnableGPIOA(void);
void RCC_EnableAFIO(void);
void AFIO_DisableJTAGAndSWD(void);

#endif
