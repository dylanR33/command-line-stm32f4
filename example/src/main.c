#include <stdint.h>
#include "stm32f4xx.h"
#include "led.h"

#define LED_PIN 5


void main()
{
    ledPeripheralClockEnable(RCC, RCC_AHB1ENR_GPIOAEN_Pos);

    volatile uint32_t dummy;                            // Dummy reads to wait for peripheral clock to be enabled.
    dummy = RCC->AHB1ENR;
    dummy = RCC->AHB1ENR;

    ledOutputMode(GPIOA, GPIO_MODER_MODER5_Pos);

    while (1)
    {
        ledToggle(GPIOA, LED_PIN);
        for (uint32_t i = 0; i < 100000; i++);         // Delay.
    }
}

