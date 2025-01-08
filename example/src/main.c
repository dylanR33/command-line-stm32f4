#include <stdint.h>

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "led.h"

#define LED_PIN 5


void main()
{

    HAL_Init();


    RCC_TypeDef* rcc = (RCC_TypeDef*)RCC;
    ledPeripheralClockEnable(&(rcc->AHB1ENR), RCC_AHB1ENR_GPIOAEN_Pos);

    volatile uint32_t dummy;    // Dummy reads to wait for peripheral clock to be enabled.
    dummy = rcc->AHB1ENR;
    dummy = rcc->AHB1ENR;

    GPIO_TypeDef* gpio_a = (GPIO_TypeDef*)GPIOA;
    ledOutputMode(&(gpio_a->MODER), GPIO_MODER_MODER5_Pos);

    while (1)
    {
        ledToggle(&(gpio_a->ODR), LED_PIN);
        for (uint32_t i = 0; i < 100000; i++);   // Delay.
    }
}

