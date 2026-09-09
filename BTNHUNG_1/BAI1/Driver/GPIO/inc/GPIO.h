#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef struct
{
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef *)0x40010800UL)
#define GPIOC ((GPIO_TypeDef *)0x40011000UL)

void GPIO_ConfigOutputPushPull(GPIO_TypeDef *GPIOx, uint8_t pin);
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t state);
void GPIO_WriteLow8(GPIO_TypeDef *GPIOx, uint8_t value);

#endif
