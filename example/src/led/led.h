#ifndef __LED_H__
#define __LED_H__

#include "stm32f4xx.h"
#include <stdint.h>


void ledPeripheralClockEnable(RCC_TypeDef* ResClkCtrl, uint32_t GPIOEN_Pos);

void ledOutputMode(GPIO_TypeDef* GPIO, uint32_t MODER_Pos);

void ledToggle(GPIO_TypeDef* GPIO, uint32_t pin_num);

#endif
