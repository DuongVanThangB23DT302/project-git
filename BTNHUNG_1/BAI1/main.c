#include <stdint.h>
#include "GPIO.h"
#include "RCC.h"

/* STM32F103 sau reset chay HSI 8 MHz.
 * Gia tri nay tao tre xap xi 1 giay o -O0.
 * Tang gia tri -> chop cham hon; giam -> chop nhanh hon.
 */
#define LED_DELAY_COUNT  900000UL

static void delay(volatile uint32_t count)
{
    while (count-- != 0U)
    {
        __asm volatile ("nop");
    }
}

int main(void)
{
    RCC_EnableGPIOC();
    GPIO_ConfigOutputPushPull(GPIOC, 13U);

    while (1)
    {
        /* LED onboard Blue Pill PC13 thuong active-low. */
        GPIO_WritePin(GPIOC, 13U, 0U);  /* LED sang */
        delay(LED_DELAY_COUNT);

        GPIO_WritePin(GPIOC, 13U, 1U);  /* LED tat */
        delay(LED_DELAY_COUNT);
    }
}
