#ifndef __USART_PRINT_H__
#define __USART_PRINT_H__

#include <stdint.h>

void UsartPrint_Init( uint32_t apb1_freq );

void UsartPrint_Write( char c );

#endif
