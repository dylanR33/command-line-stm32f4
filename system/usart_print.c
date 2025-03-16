#include "usart_print.h"

#include "stm32f4xx.h"
#include <stdint.h>


#define OVERSAMPLING_16 16

#define OVERSAMPLING_8  8

#define BAUD 115200

static uint32_t CalculateBRR( uint32_t apb1_freq );

void UsartPrint_Init( uint32_t apb1_freq )
{
    // Enable USART2 clock
    RCC->APB1ENR |= ( 1 << RCC_APB1ENR_USART2EN_Pos );
    
    // Dummy reads
    RCC->APB1ENR = RCC->APB1ENR;
    RCC->APB1ENR = RCC->APB1ENR;

    // Enable GPIOA clock
    RCC->AHB1ENR |= ( 1 << RCC_AHB1ENR_GPIOAEN_Pos );

    // Dummy reads
    RCC->APB1ENR = RCC->APB1ENR;
    RCC->APB1ENR = RCC->APB1ENR;

    // Set PA2 and PA3 to alternate function mode
    GPIOA->MODER &= ~( GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk  );
    GPIOA->MODER |= ( 0b10 << GPIO_MODER_MODE2_Pos ) | ( 0b10 << GPIO_MODER_MODE3_Pos );

    // Set PA2 and PA3 to USART2
    GPIOA->AFR[0] &= ~( GPIO_AFRL_AFRL2 | GPIO_AFRL_AFRL3 );
    GPIOA->AFR[0] |= ( ( 7 <<  GPIO_AFRL_AFSEL2_Pos ) | ( 7 << GPIO_AFRL_AFSEL3_Pos ) );

    // Set baud rate, enable usart and tx
    USART2->BRR = CalculateBRR( apb1_freq );
    USART2->CR1 |= USART_CR1_UE | USART_CR1_TE;

    USART2->DR = 0;
    while ( !( USART2->SR & USART_SR_TC ) );
}

static uint32_t CalculateBRR( uint32_t apb1_freq )
{
    uint8_t oversampling = 0;
    if ( USART2->CR1 & USART_CR1_OVER8_Msk )
        oversampling = OVERSAMPLING_8;
    else
        oversampling = OVERSAMPLING_16;

    return ( apb1_freq / ( oversampling * BAUD ) ) << 4;
}

void UsartPrint_Write( char c )
{
    USART2->DR = c;
    while ( !( USART2->SR & USART_SR_TC ) );
}
