#include "GPIO.h"

static volatile uint32_t *GPIO_GetConfigRegister(GPIO_TypeDef *GPIOx,
                                                  uint8_t pin,
                                                  uint32_t *shift)
{
    if (pin < 8U)
    {
        *shift = (uint32_t)pin * 4U;
        return &GPIOx->CRL;
    }

    *shift = ((uint32_t)pin - 8U) * 4U;
    return &GPIOx->CRH;
}

void GPIO_ConfigInputPullUp(GPIO_TypeDef *GPIOx, uint8_t pin)
{
    uint32_t shift;
    volatile uint32_t *reg = GPIO_GetConfigRegister(GPIOx, pin, &shift);

    /* STM32F1: MODE=00, CNF=10 => input pull-up/pull-down (0x8). */
    *reg &= ~(0xFUL << shift);
    *reg |=  (0x8UL << shift);

    /* ODR=1 selects pull-up. */
    GPIOx->ODR |= (1UL << pin);
}

void GPIO_ConfigOutputPushPull(GPIO_TypeDef *GPIOx, uint8_t pin)
{
    uint32_t shift;
    volatile uint32_t *reg = GPIO_GetConfigRegister(GPIOx, pin, &shift);

    /* MODE=10: output 2 MHz; CNF=00: general-purpose push-pull. */
    *reg &= ~(0xFUL << shift);
    *reg |=  (0x2UL << shift);
}

uint8_t GPIO_ReadLow8(GPIO_TypeDef *GPIOx)
{
    return (uint8_t)(GPIOx->IDR & 0xFFUL);
}

void GPIO_WriteHigh8(GPIO_TypeDef *GPIOx, uint8_t value)
{
    uint32_t odr = GPIOx->ODR;
    odr &= ~0xFF00UL;
    odr |= ((uint32_t)value << 8);
    GPIOx->ODR = odr;
}
