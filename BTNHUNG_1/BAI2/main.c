#include <stdint.h>
#include "GPIO.h"
#include "RCC.h"

#define LED_DELAY_COUNT  180000UL

static void delay(volatile uint32_t count)
{
    while (count-- != 0U)
    {
        __asm volatile ("nop");
    }
}

int main(void)
{
    uint8_t pin;

    RCC_EnableGPIOA();

    /* Cau hinh PA0...PA7 la Output Push-Pull 2 MHz. */
    for (pin = 0U; pin < 8U; ++pin)
    {
        GPIO_ConfigOutputPushPull(GPIOA, pin);
    }

    GPIO_WriteLow8(GPIOA, 0x00U);

    while (1)
    {
        /* Trai -> phai: PA0 -> PA7 */
        for (pin = 0U; pin < 8U; ++pin)
        {
            GPIO_WriteLow8(GPIOA, (uint8_t)(1U << pin));
            delay(LED_DELAY_COUNT);
        }

        /* Phai -> trai: PA6 -> PA1.
         * Bo PA7 va PA0 tai hai dau de tranh sang lap 2 lan lien tiep.
         */
        for (pin = 6U; pin > 0U; --pin)
        {
            GPIO_WriteLow8(GPIOA, (uint8_t)(1U << pin));
            delay(LED_DELAY_COUNT);
        }
    }
}
