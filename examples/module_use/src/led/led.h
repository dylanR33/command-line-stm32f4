#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>

void ledPeripheralClockEnable(volatile uint32_t* ahb1_enr, uint32_t GPIOEN_Pos);

void ledOutputMode(volatile uint32_t* moder, uint32_t MODER_Pos);

void ledToggle(volatile uint32_t* odr, uint32_t pin_num);

#endif
