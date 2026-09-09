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

    /* MODE=00, CNF=10: input pull-up/pull-down. */
    *reg &= ~(0xFUL << shift);
    *reg |=  (0x8UL << shift);

    /* ODR=1 => pull-up. */
    GPIOx->ODR |= (1UL << pin);
}

void GPIO_ConfigOutputPushPull(GPIO_TypeDef *GPIOx, uint8_t pin)
{
    uint32_t shift;
    volatile uint32_t *reg = GPIO_GetConfigRegister(GPIOx, pin, &shift);

    /* MODE=10: output 2 MHz; CNF=00: push-pull. */
    *reg &= ~(0xFUL << shift);
    *reg |=  (0x2UL << shift);
}

uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint8_t pin)
{
    return (uint8_t)((GPIOx->IDR >> pin) & 1UL);
}

void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t state)
{
    if (state != 0U)
    {
        GPIOx->BSRR = (1UL << pin);
    }
    else
    {
        GPIOx->BRR = (1UL << pin);
    }
}
