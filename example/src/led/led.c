#include "led.h"

#include <stdint.h>
#include "stm32f4xx.h"

void ledPeripheralClockEnable(RCC_TypeDef* ResClkCtrl, uint32_t GPIOEN_Pos)
{
    ResClkCtrl->AHB1ENR |= ( 1 << GPIOEN_Pos );
}

void ledOutputMode(GPIO_TypeDef* GPIO, uint32_t MODER_Pos)
{
    GPIO->MODER |= ( 1 << MODER_Pos );
}

void ledToggle(GPIO_TypeDef* GPIO, uint32_t pin_num)
{
    GPIO->ODR ^= ( 1 << pin_num );
}
