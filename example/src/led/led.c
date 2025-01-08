#include "led.h"

#include <stdint.h>

void ledPeripheralClockEnable(volatile uint32_t* ahb1_enr, uint32_t GPIOEN_Pos)
{
    *ahb1_enr |= ( 1 << GPIOEN_Pos );
}

void ledOutputMode(volatile uint32_t* moder, uint32_t MODER_Pos)
{
    *moder |= ( 1 << MODER_Pos );
}


void ledToggle(volatile uint32_t* odr, uint32_t pin_num)
{
    *odr ^= ( 1 << pin_num );
}

