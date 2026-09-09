#include "RCC.h"

#define RCC_BASE       0x40021000UL
#define RCC_APB2ENR    (*(volatile uint32_t *)(RCC_BASE + 0x18UL))

#define AFIO_BASE      0x40010000UL
#define AFIO_MAPR      (*(volatile uint32_t *)(AFIO_BASE + 0x04UL))

void RCC_EnableGPIOA(void)
{
    RCC_APB2ENR |= (1UL << 2); /* IOPAEN */
}

void RCC_EnableAFIO(void)
{
    RCC_APB2ENR |= (1UL << 0); /* AFIOEN */
}

void AFIO_DisableJTAGAndSWD(void)
{
    /* SWJ_CFG[2:0] = 100: disable JTAG-DP and SW-DP.
       Required because PA13, PA14 and PA15 are used as GPIO outputs. */
    AFIO_MAPR &= ~(7UL << 24);
    AFIO_MAPR |=  (4UL << 24);
}
