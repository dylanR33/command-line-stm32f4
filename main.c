#include <stdint.h>

// Using LD2 which is connected to PA5

// Peripheral base addresses found in STM32F411RE Datasheet Section 5
#define PERIPHERALS_BASE    ( 0x40000000U )
#define AHB1_BASE           ( PERIPHERALS_BASE + 0x20000U )
#define GPIOA_BASE          ( AHB1_BASE )
#define RCC_BASE            ( AHB1_BASE + 0x3800U )

// Reset and clock control (RCC) register definitions found in reference manual section 6.3.9
#define RCC_AHB1ENR_OFFSET  ( 0x30U )
#define RCC_AHB1ENR         ( ( volatile uint32_t* )( RCC_BASE + RCC_AHB1ENR_OFFSET ) )
#define RCC_AHB1ENR_GPIOAEN ( 0x00U )

// GPIO port mode register definitions found in reference manual section 8.4.1
#define GPIO_MODER_OFFSET   ( 0x00U )
#define GPIOA_MODER         ( ( volatile uint32_t* )( GPIOA_BASE + GPIO_MODER_OFFSET ) )
#define GPIOA_MODER_MODER5 ( 10U )

// GPIO port output data register definitions found in reference manual section 8.4.6
#define GPIO_ODR_OFFSET ( 0x14U )
#define GPIO_ODR ( ( volatile uint32_t* )( GPIOA_BASE + GPIO_ODR_OFFSET ) )

#define LED_PIN 5


void main()
{
    *RCC_AHB1ENR |= ( 1 << RCC_AHB1ENR_GPIOAEN );       // Set bit zero corresponding to GPIOA.

    volatile uint32_t dummy;                            // Dummy reads to wait for peripheral clock to be enabled.
    dummy = *RCC_AHB1ENR;
    dummy = *RCC_AHB1ENR;

    *GPIOA_MODER |= ( 1 << GPIOA_MODER_MODER5 );        // Set MODER5 to 0b01 = general purpose output mode.

    while (1)
    {
        *GPIO_ODR ^= ( 1 << LED_PIN );                  // Toggle ODR5.
        for (uint32_t i = 0; i < 1000000; i++);         // Delay.
    }
}

