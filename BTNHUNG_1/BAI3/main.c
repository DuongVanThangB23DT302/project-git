#include <stdint.h>
#include "GPIO.h"
#include "RCC.h"

int main(void)
{
    uint8_t input_data;
    uint8_t inverted_data;
    uint8_t pin;

    RCC_EnableGPIOA();
    RCC_EnableAFIO();

    /* PA0..PA7: input pull-up. Each button connects its pin to GND. */
    for (pin = 0U; pin < 8U; ++pin)
    {
        GPIO_ConfigInputPullUp(GPIOA, pin);
    }

    /* PA13, PA14 and PA15 are debug pins after reset.
       Disable SWJ so all PA8..PA15 can operate as normal GPIO outputs. */
    AFIO_DisableJTAGAndSWD();

    /* PA8..PA15: output push-pull. */
    for (pin = 8U; pin < 16U; ++pin)
    {
        GPIO_ConfigOutputPushPull(GPIOA, pin);
    }

    while (1)
    {
        /* Read PA0..PA7. */
        input_data = GPIO_ReadLow8(GPIOA);

        /* Invert each bit: 0 -> 1, 1 -> 0. */
        inverted_data = (uint8_t)(~input_data);

        /* Write bit0..bit7 to PA8..PA15 respectively. */
        GPIO_WriteHigh8(GPIOA, inverted_data);
    }
}
