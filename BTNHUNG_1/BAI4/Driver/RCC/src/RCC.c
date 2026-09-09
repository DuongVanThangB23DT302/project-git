#include "RCC.h"

#define RCC_BASE       0x40021000UL
#define RCC_APB2ENR    (*(volatile uint32_t *)(RCC_BASE + 0x18UL))

void RCC_EnableGPIOB(void)
{
    RCC_APB2ENR |= (1UL << 3); /* IOPBEN */
}
