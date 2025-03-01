#include "usart_print.h"

#include "stm32f4xx.h"
#include <stdint.h>

void UsartPrint_Init()
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
    USART2->BRR = 434;
    USART2->CR1 |= USART_CR1_UE | USART_CR1_TE;

    USART2->DR = 0;
    while ( !( USART2->SR & USART_SR_TC ) );
}

// TODO: incorporate DMA
void UsartPrint_Write( char c )
{
    USART2->DR = c;
    while ( !( USART2->SR & USART_SR_TC ) );
}
