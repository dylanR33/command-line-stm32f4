#include <stdint.h>
#include "stm32f4xx.h"

#define LED_PIN 5



void main()
{
    RCC->AHB1ENR |= ( 1 << RCC_AHB1ENR_GPIOAEN_Pos );       // Set bit zero corresponding to GPIOA.

    volatile uint32_t dummy;                            // Dummy reads to wait for peripheral clock to be enabled.
    dummy = RCC->AHB1ENR;
    dummy = RCC->AHB1ENR;

    GPIOA->MODER |= ( 1 << GPIO_MODER_MODER5_Pos );        // Set MODER5 to 0b01 = general purpose output mode.

    while (1)
    {
        GPIOA->ODR ^= ( 1 << LED_PIN );                  // Toggle ODR5.
        for (uint32_t i = 0; i < 1000000; i++);         // Delay.
    }
}

