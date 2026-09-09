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

void GPIO_ConfigInputPullUp(GPIO_TypeDef *GPIOx, uint8_t pin);
void GPIO_ConfigOutputPushPull(GPIO_TypeDef *GPIOx, uint8_t pin);
uint8_t GPIO_ReadLow8(GPIO_TypeDef *GPIOx);
void GPIO_WriteHigh8(GPIO_TypeDef *GPIOx, uint8_t value);

#endif
