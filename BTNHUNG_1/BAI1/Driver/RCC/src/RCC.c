#include "RCC.h"

#define RCC_BASE       0x40021000UL
#define RCC_APB2ENR    (*(volatile uint32_t *)(RCC_BASE + 0x18UL))

void RCC_EnableGPIOA(void)
{
    /* IOPAEN - APB2 bit 2 */
    RCC_APB2ENR |= (1UL << 2);
}

void RCC_EnableGPIOC(void)
{
    /* IOPCEN - APB2 bit 4 */
    RCC_APB2ENR |= (1UL << 4);
}
