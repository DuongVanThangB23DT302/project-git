#include <stdint.h>
#include "GPIO.h"
#include "RCC.h"

#define BUTTON_PIN  0U   /* PB0, button to GND, internal pull-up enabled */
#define LED_PIN     1U   /* PB1, external LED through 220-330 ohm to GND */
#define DEBOUNCE_COUNT  30000UL

static void delay_debounce(void)
{
    volatile uint32_t i;
    for (i = 0U; i < DEBOUNCE_COUNT; ++i)
    {
        __asm volatile ("nop");
    }
}

int main(void)
{
    uint8_t led_state = 0U;
    uint8_t button_was_pressed = 0U;

    RCC_EnableGPIOB();

    GPIO_ConfigInputPullUp(GPIOB, BUTTON_PIN);
    GPIO_ConfigOutputPushPull(GPIOB, LED_PIN);
    GPIO_WritePin(GPIOB, LED_PIN, led_state);

    while (1)
    {
        /* With pull-up: PB0=0 when pressed, PB0=1 when released. */
        if (GPIO_ReadPin(GPIOB, BUTTON_PIN) == 0U)
        {
            if (button_was_pressed == 0U)
            {
                delay_debounce();
                if (GPIO_ReadPin(GPIOB, BUTTON_PIN) == 0U)
                {
                    button_was_pressed = 1U;
                }
            }
        }
        else
        {
            /* Toggle exactly once after a valid press has been released. */
            if (button_was_pressed != 0U)
            {
                delay_debounce();
                if (GPIO_ReadPin(GPIOB, BUTTON_PIN) != 0U)
                {
                    led_state ^= 1U;
                    GPIO_WritePin(GPIOB, LED_PIN, led_state);
                    button_was_pressed = 0U;
                }
            }
        }
    }
}
