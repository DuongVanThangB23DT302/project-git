#include "GPIO.h"

void GPIO_ConfigOutputPushPull(GPIO_TypeDef *GPIOx, uint8_t pin)
{
    volatile uint32_t *config_reg;
    uint32_t shift;

    if (pin < 8U)
    {
        config_reg = &GPIOx->CRL;
        shift = (uint32_t)pin * 4U;
    }
    else
    {
        config_reg = &GPIOx->CRH;
        shift = ((uint32_t)pin - 8U) * 4U;
    }

    /* MODE = 10: Output 2 MHz; CNF = 00: General-purpose push-pull */
    *config_reg &= ~(0xFUL << shift);
    *config_reg |=  (0x2UL << shift);
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

void GPIO_WriteLow8(GPIO_TypeDef *GPIOx, uint8_t value)
{
    uint32_t odr = GPIOx->ODR;
    odr &= ~0xFFUL;
    odr |= (uint32_t)value;
    GPIOx->ODR = odr;
}
